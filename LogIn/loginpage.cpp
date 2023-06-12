#include "loginpage.h"
#include "ui_loginpage.h"

LogInPage::LogInPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInPage)
{
    ui->setupUi(this);

    Request = new HttpRequest;

    OKpushButton=false;
    CancelpushButton=false;

    connect(ui->OKpushButton,SIGNAL(clicked()),this ,SLOT(LinkerLogIn()));
}

LogInPage::~LogInPage()
{
    delete ui;
    delete Request;
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
        QJsonObject information_received=(Request->Http_request_operation(http));
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
    QString username;
    QString password;

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
    if(information.value("code")=="200"){
        //store token
        token = information.value("token").toString();
        QString message="You loged in successfully.";
        return message;
    }
    else if(information.value("code")=="204"){
        QString error="Your are already loged in!";
        throw error;
    }
    else if(information.value("code")=="404"){
        QString error="User Not Found";
        throw error;
    }
    else if(information.value("code")=="401"){
        QString error="Password is not Correct!";
        throw error;
    }
    else{
        QString error="Unknown Error";
        throw error;
    }
}

//It prints success message on the ErrorLabel
void LogInPage::Output_LogIn(const QString &stream)
{
    ui->ErrorLabel->setStyleSheet("color: green");
    ui->ErrorLabel->setText(stream);
    OKpushButton=true;
    Sleep(1000);
}







