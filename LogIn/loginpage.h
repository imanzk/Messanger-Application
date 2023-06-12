#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "HttpRequest/httprequest.h"
#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QThread>
#include <Windows.h>

namespace Ui {
class LogInPage;
}

class LogInPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

private:
    Ui::LogInPage *ui;
    HttpRequest *Request;
public:
//Two attributes to switch between pages
    bool OKpushButton;
    bool CancelpushButton;

    //it is activated with Output_LogIn func
    void OKpushButton_clicked();
private slots:
    void on_CancelpushButton_clicked();
//    void on_OKpushButton_clicked();

signals:
    void _click();
public slots:
    void LinkerLogIn(); //The Head of all we do, this is activated by clicking on OKpushButton
public:
    //To store token
    QString token;

    QJsonObject Get_UserData();
    QString Http_creator(const QJsonObject&);
    QString Http_analyser(const QJsonObject&);
    void Output_LogIn(const QString &);

};

#endif // LOGINPAGE_H
