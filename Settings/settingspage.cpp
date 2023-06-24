#include "settingspage.h"
#include "ui_settingspage.h"

SettingsPage::SettingsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
    LogoutpushButton=false;
    BackpushButton=false;
    CreatepushButton=false;

    //to initialize labels
    ui->UsernameLable->setText("username : " + FilesOP::GetUsername());
    ui->TokenLabel->setText("token : " + FilesOP::GetToken());

    connect (ui->CreatePushButton , SIGNAL(clicked()), this ,SLOT(Linker()));
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::on_BackpushButton_clicked()
{
   BackpushButton=true;
   emit _click();
}

void SettingsPage::on_LogoutpushButton_clicked()
{
   QString command="logout?username="+FilesOP::GetUsername()+"&password="+FilesOP::GetPassword();
   QJsonObject jsonObj = HttpRequest::Http_request_operation(command);

   try {
       if(jsonObj["code"]!="200") throw;
   } catch (...) {
       qDebug()<<jsonObj["message"];
       return;
   }

   FilesOP::RemoveProfile();
   FilesOP::Remove_Channels_List();
   FilesOP::Remove_Groups_List();
   FilesOP::Remove_Users_List();

   LogoutpushButton=true;
   emit _click();
}

void SettingsPage::Linker()
{
    try {
        QJsonObject info = GetData();
        QString http = HttpCreator(info);
        QJsonObject received_info=HttpRequest::Http_request_operation(http);
        QString output = HttpAnalyser(received_info);
        Make_New(info);
        CreatepushButton_clicked();
    }
    catch (const QString error) {
        ui->ErrorLabel->setText(error);
    }
}

QJsonObject SettingsPage::GetData()
{
    QString name=ui->NameLineEdit->text();

    if(name.isEmpty())
    {
        QString error="Please fill out the blank.";
        throw error;
    }
    else if (ui->NameLineEdit->text().trimmed().length() == 0) {
        QString error="Name is Unvalid.";
        throw error;
    }

    QString title=ui->TitleLineEdit->text();
    QString status;
    if(ui->radioButtonChannel->isChecked()){
        status="channel";
    }
    else if(ui->radioButtonGroup->isChecked()){
        status="group";
    }
    else
    {
        QString Error="Choose Group or Channel.";
        throw Error;
    }

    QJsonObject newly;
    newly["name"]=name;
    newly["title"]=title;
    newly["status"]=status;

    return newly;
}
QString SettingsPage::HttpCreator(const QJsonObject& info)
{
    if(info["status"].toString()=="channel")
    {
        return "createchannel?token="+ FilesOP::GetToken() +
                "&channel_name="+info["name"].toString()+"&channel_title="+info["title"].toString();
    }
    else //status is group
    {
        return "creategroup?token="+ FilesOP::GetToken() +
                "&group_name="+info["name"].toString()+"&group_title="+info["title"].toString();
    }
}
QString SettingsPage::HttpAnalyser(const QJsonObject& info)
{
    if(info["code"]=="200"){
        QString stream = info["message"].toString();
        return stream;
    }
    else
    {
        QString error = info["message"].toString();
        throw error;
    }
}
void SettingsPage::Make_New(const QJsonObject& info)
{
    QString name = info["name"].toString();
    QString status = info["status"].toString();
    if(status == "group") FilesOP::Create_Group_File(name);
    else if(status == "channel") FilesOP::Create_Channel_File(name);
    //after creating a file now we have to set dst
    FilesOP::SetDst(name);
}
void SettingsPage::CreatepushButton_clicked()
{
    CreatepushButton=true;
    emit _click();
}
