#include "SignUp/signuppage.h"
#include "ui_signuppage.h"

SignUpPage::SignUpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpPage)
{
    ui->setupUi(this);

    Request = new HttpRequest;

    OKpushButton=false;
    CancelpushButton=false;

    connect(ui->OKpushButton,SIGNAL(clicked()),this ,SLOT(LinkerSignUp()));
}

SignUpPage::~SignUpPage()
{
    delete ui;
    delete Request;
}

void SignUpPage::on_CancelpushButton_clicked() //It is a slot
{
    CancelpushButton=true;
    emit _click();
}

void SignUpPage::OKpushButton_clicked() //It is not a slot
{
    OKpushButton=true;
    emit _click();
}


void SignUpPage::LinkerSignUp() //Getting , Creating , Sending and Getting , Analysing , Outputing , finally OKpushButton_clicked()
{
    try
    {
        QJsonObject info= Get_UserData();
        QString http= Http_creator(info);
        QJsonObject information_received=(Request->Http_request_operation(http));
        QString stream=Http_analyser(information_received);
        //if inputs and outputs were Ok , continue
        Output_SignUp(stream);
        OKpushButton_clicked();
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

    username=ui->UsernameLineEdit->text();
    password=ui->PasswordLineEdit->text();
    first_name=ui->FirstnameLineEdit->text();
    last_name=ui->LastnameLineEdit->text();
    QJsonObject information = {
        {"username",username} , {"password",password} , {"firstname",first_name} ,
        {"lastname",last_name}
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
    QString code=information.value("code").toString();
    if(code=="200"){
        QString message=information.value("message").toString();
        return message;
    }
    else if(code=="204"){
        QString error=information.value("message").toString();
        throw error;
    }
    else{
        QString error="Unknown Error";
        throw error;
    }
}

//It prints success message on the ErrorLabel
void SignUpPage::Output_SignUp(const QString &stream)
{
    ui->ErrorLabel->setStyleSheet("color: green");
    ui->ErrorLabel->setText(stream);
    OKpushButton=true;
    Sleep(1000);
}


















