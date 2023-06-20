#include "listchatspage.h"
#include "ui_listchatspage.h"

ListChatsPage::ListChatsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListChatsPage)
{
    ui->setupUi(this);
    threadlist = new ThreadList(this);

    Setting_pushButton=false;
    Search_pushButton=false;
    Item_pushButton[0]=0;
    Item_pushButton[1]=0;
    //
    connect(threadlist,SIGNAL(newUser(const QJsonObject)),this,SLOT(Add_User_Item(const QJsonObject)));
    connect(threadlist,SIGNAL(newGroup(const QJsonObject)),this,SLOT(Add_Group_Item(const QJsonObject)));
    connect(threadlist,SIGNAL(newChannel(const QJsonObject)),this,SLOT(Add_Channel_Item(const QJsonObject)));
}
ListChatsPage::~ListChatsPage()
{
    threadlist->terminate();
    delete ui;
    delete threadlist;

}

/**********pushButton Slots*****************/

void ListChatsPage::on_listWidget_clicked(const QModelIndex &index)
{
    Item_pushButton[0]=1;
    Item_pushButton[1]=index.row();
    emit _click();
}


void ListChatsPage::on_Search_pushButton_clicked()
{
   Search_pushButton=true;
   emit _click();
}


void ListChatsPage::on_Setting_pushButton_clicked()
{
   Setting_pushButton=true;
   emit _click();
}


/***************Add Item slots*****************/
void ListChatsPage::Add_Group_Item(const QJsonObject newData)
{
    int size = FilesOP::ReturnNumberMessages(newData);
    for(int i =0 ; i<size ; i ++)
    {
        QJsonObject block;
        block = newData["block "+QString::number(i)].toObject();
        Add_Item(block.value("group_name").toString());
    }
}
void ListChatsPage::Add_User_Item(const QJsonObject newData)
{

    int size = FilesOP::ReturnNumberMessages(newData);
    for(int i =0 ; i<size ; i ++)
    {
        QJsonObject block;
        block = newData["block "+QString::number(i)].toObject();
        Add_Item(block.value("src").toString());
    }
}
void ListChatsPage::Add_Channel_Item(const QJsonObject newData)
{
    int size = FilesOP::ReturnNumberMessages(newData);
    for(int i =0 ; i<size ; i ++)
    {
        QJsonObject block;
        block = newData["block "+QString::number(i)].toObject();
        Add_Item(block.value("channel_name").toString());
    }
}

//
void ListChatsPage::Add_Item(const QString name)
{
  if(!printedlist.contains(name))
  {
    printedlist << name;
    QListWidgetItem *item=new QListWidgetItem(name);
    item->setBackground(QColor(255, 255, 255));
    QFont font("Helvetica", 11);
    item->setFont(font);
    ui->listWidget->addItem(item);
  }
}

//
void ListChatsPage::Recovery()
{
    QJsonObject jsonObject=FilesOP::Get_Users_List();
    int size = FilesOP::ReturnNumberMessages(jsonObject);
    for ( int i = 0 ; i < size ; i ++)
    {
        QJsonObject block=jsonObject["block "+QString::number(i)].toObject();
        block["src"]=block["src"].toString().remove(".json");
        Add_Item(block["src"].toString());
    }
    jsonObject=FilesOP::Get_Groups_List();
    size = FilesOP::ReturnNumberMessages(jsonObject);
    for ( int i = 0 ; i < size ; i ++)
    {
        QJsonObject block=jsonObject["block "+QString::number(i)].toObject();
        block["group_name"]=block["group_name"].toString().remove(".json");
        Add_Item(block["group_name"].toString());
    }
    jsonObject=FilesOP::Get_Channels_List();
    size = FilesOP::ReturnNumberMessages(jsonObject);
    for ( int i = 0 ; i < size ; i ++)
    {
        QJsonObject block=jsonObject["block "+QString::number(i)].toObject();
        block["channel_name"]=block["channel_name"].toString().remove(".json");
        Add_Item(block["channel_name"].toString());
    }
}

//
void ListChatsPage::MakeFalse()
{
    Setting_pushButton=false;
    Search_pushButton=false;
    Item_pushButton[0]=0;
    Item_pushButton[1]=0;
}

//get printedlist
QStringList ListChatsPage::GetPrintedlist(){return printedlist;}



















