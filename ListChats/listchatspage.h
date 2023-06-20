#ifndef LISTCHATSPAGE_H
#define LISTCHATSPAGE_H

#include <QWidget>
#include <QObject>
#include "threadlist.h"
#include <QJsonObject>

namespace Ui {
class ListChatsPage;
}

class ListChatsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ListChatsPage(QWidget *parent = nullptr);
    ~ListChatsPage();
    ThreadList *threadlist;

private:
    Ui::ListChatsPage *ui;

private:
    //to store what are shown on the listwidget and to figure out which Item is clicked respectively
    QStringList printedlist;
public:
    //getter for printed list
    QStringList GetPrintedlist();

public:
//Two attributes to switch between pages
    bool Search_pushButton;
    bool Setting_pushButton;
    int Item_pushButton[2]; // First section for click status on listWidget, Second for the index of selection


signals:
    void _click(); //to the Administrator
public slots:
    void Add_Group_Item(const QJsonObject newData);
    void Add_User_Item(const QJsonObject newData);
    void Add_Channel_Item(const QJsonObject newDate);
//    void LinkerListChats(); //The Head of all we do, this is activated by clicking on OKpushButton
public:
    //to recovery previous info and show when we get in listchats page
    void Recovery();

    //It prints unprinted Item
    void Add_Item(const QString name);

    //it makes pushbutton attributes to false
    void MakeFalse();

//    QString Http_creator(const QJsonObject&);
//    QString Http_analyser(const QJsonObject&);
//    void Output_SignUp(const QString &);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_Search_pushButton_clicked();
    void on_Setting_pushButton_clicked();
};

#endif // LISTCHATSPAGE_H
