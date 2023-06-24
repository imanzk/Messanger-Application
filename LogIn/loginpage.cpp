#include "loginpage.h"
#include "ui_loginpage.h"

LogInPage::LogInPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInPage)
{
    ui->setupUi(this);

    OKpushButton=false;
    CancelpushButton=false;

    connect(ui->OKpushButton,SIGNAL(clicked()),this ,SLOT(LinkerLogIn()));
}

LogInPage::~LogInPage()
{
    delete ui;
}

void LogInPage::on_CancelpushButton_clicked() //It is a slot
{
    CancelpushButton=true;
    emit _click();
}

void LogInPage::OKpushButton_clicked() //It is not a slot
{
    OKpushButton=true;
    emit _click();
}

void LogInPage::LinkerLogIn() //Getting , Creating , Sending and Getting , Analysing , Outputing , finally OKpushButton_clicked()
{
    try
    {
        QJsonObject info= Get_UserData();
        QString http= Http_creator(info);
        QJsonObject information_received=(HttpRequest::Http_request_operation(http));
        QString stream=Http_analyser(information_received); //and store token if it is suited
        Output_LogIn(stream);
        OKpushButton_clicked();
    }
    catch(const QString Error)
    {
        ui->ErrorLabel->setStyleSheet("color: red");
        ui->ErrorLabel->setText(Error);
    }
}

QJsonObject LogInPage::Get_UserData()
{
    //information

    username=ui->UsernameLineEdit->text();
    password=ui->PasswordLineEdit->text();

    QJsonObject information = {
        {"username",username} , {"password",password}
    };

    if(username.isEmpty()||password.isEmpty())
    {
        QString error="Please fill out the blanks.";
        throw error;
    }
    else if(username.contains(" "))
    {
        QString error="Username is unvalid.";
        throw error;
    }

    else
    return information;
}

QString LogInPage::Http_creator(const QJsonObject &Information_toSend)
{
     QString url_commands ;

     url_commands += "login?";
     url_commands += "username=";
     url_commands += Information_toSend.value("username").toString();
     url_commands += "&";
     url_commands += "password=";
     url_commands += Information_toSend.value("password").toString();

     return url_commands;
}

QString LogInPage::Http_analyser(const QJsonObject &information)
{
   QString code=information.value("code").toString();

   //::::::::::this condition is not logicaly it is a code problem from the server but I have to handle it:::::::
   if(information.value("message").toString()=="You are already logged in!")
   {
       QString error=information.value("message").toString();
       throw error;
   }
   //:::::::::::::::::::::::::::::::::::::::::::

   else if(code=="200"){
        //store info of the user
        FilesOP::CreateProfile();
        FilesOP::SetUsername(username);
        FilesOP::SetPassword(password);
        FilesOP::SetToken(information.value("token").toString());

        QString message=information.value("message").toString();
        return message;
    }
    else
   {
       QString Error=information.value("message").toString();
       throw Error;
   }
}

//It prints success message on the ErrorLabel
void LogInPage::Output_LogIn(const QString &stream)
{
    ui->ErrorLabel->setStyleSheet("color: green");
    ui->ErrorLabel->setText(stream);
}







