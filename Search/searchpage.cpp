#include "searchpage.h"
#include "ui_searchpage.h"

SearchPage::SearchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPage)
{
    ui->setupUi(this);
    setWindowTitle("Search");
}

SearchPage::~SearchPage()
{
    delete ui;
}

void SearchPage::Linker() //taskes: getting data, creating http request, analysing http request
{
    try {
        QString data = GetData();
        //if user exists between our contacts :
        if(FilesOP::Group_Exist(data))
        {
            FilesOP::SetDst(data);
            commandLinkButton_clicked();
            return;
        }
        QString url = HttpCreator(data , "group");
        QJsonObject receivedInfo = HttpRequest::Http_request_operation(url);
        QString output = HttpAnalyser(receivedInfo);
        Make_New(data,"group");
        commandLinkButton_clicked();
    }
    catch (...){
        try{
           QString data = GetData();
           //if user exists between our contacts :
           if(FilesOP::Channel_Exist(data))
           {
               FilesOP::SetDst(data);
               commandLinkButton_clicked();
               return;
           }
           QString url = HttpCreator(data , "channel");
           QJsonObject receivedInfo = HttpRequest::Http_request_operation(url);
           QString output = HttpAnalyser(receivedInfo);
           Make_New(data,"channel");
           commandLinkButton_clicked();
        }
        catch (...) {
            try{
               QString data = GetData();
               //if user exists between our contacts :
               if(FilesOP::User_Exist(data))
               {
                   FilesOP::SetDst(data);
                   commandLinkButton_clicked();
                   return;
               }
               QString url = HttpCreator(data , "user");
               QJsonObject receivedInfo = HttpRequest::Http_request_operation(url);
               QString output = HttpAnalyser(receivedInfo);
               Make_New(data,"user");
               commandLinkButton_clicked();
            }
            catch (...) {
               ui->ErrorLabel->setText("Error");
            }
        }
    }
}

QString SearchPage::GetData()
{
    return ui->lineEdit->text();
}
QString SearchPage::HttpCreator(const QString &data , const QString command)
{
    if(command=="user")
    {
        return "sendmessage"+command+"?"+"token="+FilesOP::GetToken()+"&dst="+data+"&body=**New User**";
    }
    else {
        return "join"+command+"?"+"token="+FilesOP::GetToken()+"&"+command+"_name="+data;
    }
}
QString SearchPage::HttpAnalyser(const QJsonObject& data)
{
    if(data["code"].toString()!="200"){
        throw 0;
    }
    else return "OK";
}
void SearchPage::Make_New(const QString& data,const QString command){
    if(command == "group") FilesOP::Create_Group_File(data);
    else if(command== "channel") FilesOP::Create_Channel_File(data);
    else if(command== "user") FilesOP::Create_User_File(data);
    //after creating a file now we have to set dst
    FilesOP::SetDst(data);
}

void SearchPage::on_commandLinkButton_clicked()
{
    Linker();
}

void SearchPage::commandLinkButton_clicked(){
    emit _click();
}
