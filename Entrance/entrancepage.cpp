#include "entrancepage.h"
#include "ui_entrancepage.h"

EntrancePage::EntrancePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntrancePage)
{
    ui->setupUi(this);

    LoginPage=false;
    SignupPage=false;
}

EntrancePage::~EntrancePage()
{
    delete ui;
}

void EntrancePage::on_Login_pushButton_clicked()
{
    LoginPage=true;
    emit _click();
}


void EntrancePage::on_Signup_pushButton_clicked()
{
    SignupPage=true;
    emit _click();
}

