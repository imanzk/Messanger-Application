#include "listchatspage.h"
#include "ui_listchatspage.h"

ListChatsPage::ListChatsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListChatsPage)
{
    ui->setupUi(this);
}

ListChatsPage::~ListChatsPage()
{
    delete ui;
}

/**********Slots*****************/

void ListChatsPage::on_listWidget_clicked(const QModelIndex &index)
{

}


void ListChatsPage::on_Search_pushButton_clicked()
{

}


void ListChatsPage::on_Setting_pushButton_clicked()
{

}

/********************************/




