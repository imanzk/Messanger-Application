#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QEventLoop>
#include <QScreen>
#include <QGuiApplication>

#include "SignUp/signuppage.h"
#include "Entrance/entrancepage.h"
#include "LogIn/loginpage.h"
#include "ListChats/listchatspage.h"
#include "Thread/thread.h"

class Administrator : public QObject
{
    Q_OBJECT
public:
    explicit Administrator(QObject *parent = nullptr);
    ~Administrator();
    //To select widget page and size of it into stacked widget and to show
    void WidgetSelection(QWidget *PageWidget,const int parameter1, const int parameter2 );

    //To initialize new objects and related slots and signals
    void Entrance_New();
    void Login_New();
    void Signup_New();
    void ListChats_New();

private:
    QStackedWidget *stackedWidget;

    //to store unused heap address to clear at the end
    std::vector <EntrancePage*> entrance_list;
    std::vector <SignUpPage*> signup_list;
    std::vector <LogInPage*> login_list;
    std::vector <ListChatsPage*> listchats_list;

    //Declaring objects to work
    EntrancePage *entrance;
    SignUpPage *signup;
    LogInPage *login;
    ListChatsPage *listchats;

public slots:
    //Functions to do for each obj:
    void Entrance_Func();
    void Signup_Func();
    void Login_Func();
    void Listchats_Func();

};

#endif // ADMINISTRATOR_H
