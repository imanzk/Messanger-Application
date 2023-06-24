#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    threadchat = new ThreadChat;
    ui->listWidget->setWordWrap(true);
    item=nullptr;

    threadchat->stop=false;
    threadchat->start();

    //set title for chat page
    QJsonObject jsonObj=FilesOP::GetDst();
    ui->Usernamelabel->setText(jsonObj["dst"].toString());

    recentDate = QDate(1,1,1); //initialized
    numberOFprintedMessage = 0;
    once = false;

    //it gets new messages from threadchat
    connect(threadchat,SIGNAL(newMessages(const QJsonObject)),this , SLOT(NewMessagesSlot(const QJsonObject)));

}

ChatPage::~ChatPage()
{
    threadchat->terminate();
    delete ui;
    delete threadchat;
}

//void ChatPage::Customize()
//{

//    //to empty heap memory

//    threadchat->stop=false;
//    threadchat->start();

//    //set title for chat page
//    QJsonObject jsonObj=FilesOP::GetDst();
//    ui->Usernamelabel->setText(jsonObj["dst"].toString());
//    recentDate = QDate(1,1,1); //initialized
//}

void ChatPage::NewMessagesSlot(const QJsonObject receivedInfo)
{
    QJsonObject jsonObj = FilesOP::GetDst();
    QString dst = jsonObj["dst"].toString();

//    const int number_previousData=FilesOP::ReturnNumberMessages(FilesOP::Get_Messages(dst));
    const int number_receivedData=FilesOP::ReturnNumberMessages(receivedInfo);

    //now we create a data of unprinted data to print
    QJsonObject unprinted;
    for(int i = numberOFprintedMessage; i<number_receivedData;i++)
    {
        unprinted["block "+QString::number(i-numberOFprintedMessage)] = receivedInfo["block "+
                QString::number(i)];
    }
    unprinted["message"]="There Are -"+
            QString::number(number_receivedData-numberOFprintedMessage)
            +"- Messages";

    ShowMessagesManager(unprinted);
}
//to show messages
void ChatPage::ShowMessagesManager(const QJsonObject info)
{
    QJsonObject jsonObj=FilesOP::GetDst();
    QString dst = jsonObj["dst"].toString();
    QString status= jsonObj["status"].toString();

    int size=FilesOP::ReturnNumberMessages(info);
    for(int i = 0 ;i<size; i++)
    {
        numberOFprintedMessage++;
        QJsonObject block = info["block "+QString::number(i)].toObject();
        if(block["src"]!=FilesOP::GetUsername())
        {
            if(status=="user")
            {
                ShowMessage("",block["body"].toString(),block["date"].toString());
            }
            else if(status=="group")
            {
                ShowMessage(block["src"].toString(),block["body"].toString(),block["date"].toString());
            }
            else //status == "channel"
            {
                ShowMessage(block["src"].toString(),block["body"].toString(),block["date"].toString());
            }
        }
        else //the message is for me
            ShowMyMessage(block["body"].toString(),block["date"].toString());
    }
    if(!once&&item)
    {
        ui->listWidget->scrollToItem(item);
        once = true;
    }
}
void ChatPage::ShowMyMessage(const QString text, const QString datetime)
{
    QString time=ShowEachDay(datetime);

    item = new QListWidgetItem(text);
    ui->listWidget->addItem(item);
    item->setBackground(QBrush(Qt::green));
    item->setForeground(QBrush(Qt::black));
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    item = new QListWidgetItem(time);
    ui->listWidget->addItem(item);
    item->setForeground(QBrush(Qt::gray));
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
}
void ChatPage::ShowMessage(const QString username,const QString text,const QString datetime)
{
    QString time=ShowEachDay(datetime);
    qDebug()<<username;
    if(username != "") item = new QListWidgetItem(username);
    item->setBackground(QBrush(Qt::white));
    item->setForeground(QBrush(Qt::gray));
    ui->listWidget->addItem(item);

    item = new QListWidgetItem(text);
    ui->listWidget->addItem(item);

    item->setBackground(QBrush(Qt::white));
    item->setForeground(QBrush(Qt::black));

    item = new QListWidgetItem(time);
    ui->listWidget->addItem(item);
    item->setForeground(QBrush(Qt::gray));
}
QString ChatPage::ShowEachDay(const QString date_time)
{
    QDateTime qdatetime = QDateTime::fromString(date_time, "yyyy-MM-dd hh:mm:ss");
    QDate date = qdatetime.date();
    QTime time = qdatetime.time();

    if(recentDate.daysTo(date) >= 1 ) //if it passes more than a days so it shows the new date
    {
        recentDate=date; //recentDate is updated.

        item = new QListWidgetItem (date.toString());
        ui->listWidget->addItem(item);

        item->setForeground(QBrush(Qt::gray));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    return time.toString("hh:mm");
}
//to recovery
void ChatPage::Recovery()
{
    //to figure out the kind of dst
    QJsonObject infoDst= FilesOP::GetDst();
    QString dst = infoDst["dst"].toString();
    QString status = infoDst["status"].toString();

    //
    QJsonObject previousMessages;
    if(status=="user")previousMessages = FilesOP::Get_User_Messages(dst);
    else if (status=="group")previousMessages = FilesOP::Get_Group_Messages(dst);
    else previousMessages = FilesOP::Get_Channel_Messages(dst);

    ShowMessagesManager(previousMessages);
}

//to send messages:
void ChatPage::on_Sendpushbutton_clicked()
{
    QString text = ui->MessagePlaintext->toPlainText();
    ui->MessagePlaintext->clear(); // we clear it when we sent our message
    Linker_send(text);
}

void ChatPage::Linker_send(const QString body)
{
    try {
        QString url = HttpCreator_send(body);
        QJsonObject receivedInfo = HttpRequest::Http_request_operation(url);
        Analyser(receivedInfo); //it throws if a fault happends
        //now we want to show our messages and set the time of the message
//        QDateTime currentDateTime = QDateTime::currentDateTime();
//        QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
//        ShowMyMessage(body,formattedDateTime);
        //note that new messages in the thread will print our message
    }
    catch (const QString Error) {
        //now you cant send message anymore because you're not admin of the channel
        ui->MessagePlaintext->setReadOnly(true);
        ui->MessagePlaintext->setPlainText(Error);
        ui->MessagePlaintext->setStyleSheet("background-color:rgb(255, 255, 255);color:rgb(255, 0, 0);");
        ui->Sendpushbutton->disconnect();
    }
}
QString ChatPage::HttpCreator_send(const QString body)
{
    QJsonObject jsonObj = FilesOP::GetDst();
    QString dst = jsonObj["dst"].toString();
    QString status = jsonObj["status"].toString();
    QString url = "";
    url = "sendmessage" + status + "?token="+FilesOP::GetToken()+"&dst="+dst + "&body=" +body;
    return url;
}
void ChatPage::Analyser(const QJsonObject receivedInfo)
{
    if(receivedInfo["code"]!="200")
    {
       //if we are not the admin of the channel
       throw receivedInfo["message"].toString();
    }
}

//
void ChatPage::on_Backpushbutton_clicked()
{
    threadchat->stop=true;
    emit _click();
}

