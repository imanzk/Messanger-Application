#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include "HttpRequest/httprequest.h"
#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QThread>

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
    HttpRequest *Request;

    //Two attributes to switch between pages
    bool NextPage;
    bool BackPage;
private slots:
    void on_CancelpushButton_clicked();
public slots:
    void LinkerSignUp(); //The Head of all we do, this is activated by clicking on OKpushButton
public:
    QJsonObject Get_UserData();
    QString Http_creator(const QJsonObject&);
    QString Http_analyser(const QJsonObject&);
    void Output_SignUp(const QString &);

};

#endif // SIGNUPPAGE_H
