#include "SignUp/signuppage.h"
#include "ui_signuppage.h"

SignUpPage::SignUpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpPage)
{
    ui->setupUi(this);
    Request = new HttpRequest;
    NextPage=false;
    BackPage=false;
    connect(ui->OKpushButton,SIGNAL(clicked()),this ,SLOT(LinkerSignUp()));
}

SignUpPage::~SignUpPage()
{
    delete ui;
    delete Request;
}
void SignUpPage::on_CancelpushButton_clicked()
{
    BackPage=true;
}

void SignUpPage::LinkerSignUp() //Getting , Creating , Sending and Getting , Analysing , Outputing
{
    try
    {
        QJsonObject info= Get_UserData();
        QString http= Http_creator(info);
        QJsonObject information_received=(Request->Http_request_operation(http));
        QString stream=Http_analyser(information_received);
        Output_SignUp(stream);
    }
    catch(const QString Error)
    {
        ui->ErrorLabel->setStyleSheet("color: red");
        ui->ErrorLabel->setText(Error);
    }
}

QJsonObject SignUpPage::Get_UserData()
{
    //information
    QString username;
    QString password;
    QString first_name;
    QString last_name;

    ui->UsernameLineEdit->text();
    ui->PasswordLineEdit->text();
    ui->FirstnameLineEdit->text();
    ui->LastnameLineEdit->text();
    QJsonObject information = {
        {"username",username} , {"password",password} , {"firstname",first_name} ,
        {"lastname",last_name}
    };
    return information;
}

QString SignUpPage::Http_creator(const QJsonObject &Information_toSend)
{
     QString url_commands ;

     url_commands += "signup?";
     url_commands += "username=";
     url_commands += Information_toSend.value("username").toString();
     url_commands += "&";
     url_commands += "password=";
     url_commands += Information_toSend.value("password").toString();
     url_commands += "&";
     url_commands += "firstname=";
     url_commands += Information_toSend.value("firstname").toString();
     url_commands += "&";
     url_commands += "lastname=";
     url_commands += Information_toSend.value("lastname").toString();

     return url_commands;
}

QString SignUpPage::Http_analyser(const QJsonObject &information)
{
    if(information.value("code")==200){
        return "You successfully signed up.";
    }
    else if(information.value("code")==204){
        QString error="Your username already exists.";
        throw error;
    }
    else{
        QString error="Unknown Error";
        throw error;
    }
}

void SignUpPage::Output_SignUp(const QString &stream)
{
    ui->ErrorLabel->setStyleSheet("color: green");
    ui->ErrorLabel->setText(stream);
    QThread::sleep(3);
    NextPage=true;
}

















