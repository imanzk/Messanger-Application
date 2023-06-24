#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include "HttpRequest/httprequest.h"
#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QThread>
#include <Windows.h>

namespace Ui {
class SignUpPage;
}

class SignUpPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpPage(QWidget *parent = nullptr);
    ~SignUpPage();

private:
    Ui::SignUpPage *ui;

public:
//Two attributes to switch between pages
    bool OKpushButton;
    bool CancelpushButton;

    //it is activated with Output_SignUp func
    void OKpushButton_clicked();
private slots:
    void on_CancelpushButton_clicked();
//    void on_OKpushButton_clicked();

signals:
    void _click();
public slots:
    void LinkerSignUp(); //The Head of all we do, this is activated by clicking on OKpushButton
public:
    QJsonObject Get_UserData();
    QString Http_creator(const QJsonObject&);
    QString Http_analyser(const QJsonObject&);
    void Output_SignUp(const QString &);

};

#endif // SIGNUPPAGE_H
