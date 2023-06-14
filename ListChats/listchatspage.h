#ifndef LISTCHATSPAGE_H
#define LISTCHATSPAGE_H

#include "HttpRequest/httprequest.h"
#include <QWidget>
#include <QObject>

namespace Ui {
class ListChatsPage;
}

class ListChatsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ListChatsPage(QWidget *parent = nullptr);
    ~ListChatsPage();

private:
    Ui::ListChatsPage *ui;
    HttpRequest *Request;
public:
//Two attributes to switch between pages
    bool Search_pushButton;
    bool Setting_pushButton;
    int Item_pushButton[2]; // First section for click status on listWidget, Second for the index of selection


signals:
    void _click(); //to the Administrator
public slots:
//    void LinkerListChats(); //The Head of all we do, this is activated by clicking on OKpushButton
public:
//    QString Http_creator(const QJsonObject&);
//    QString Http_analyser(const QJsonObject&);
//    void Output_SignUp(const QString &);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_Search_pushButton_clicked();
    void on_Setting_pushButton_clicked();
};

#endif // LISTCHATSPAGE_H
