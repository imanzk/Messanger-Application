#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <iostream>
#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QScreen>
#include <QGuiApplication>

#include "SignUp/signuppage.h"
#include "Entrance/entrancepage.h"
#include "LogIn/loginpage.h"
#include "ListChats/listchatspage.h"
#include "Settings/settingspage.h"
#include "Chat/chatpage.h"
#include "Search/searchpage.h"

class Administrator : public QObject
{
    Q_OBJECT
public:
    explicit Administrator(QObject *parent = nullptr);
    ~Administrator();
    //To select widget page and size of it into stacked widget and to show
    void WidgetSelection(QWidget *PageWidget);

    //To initialize new objects and related slots and signals
    void Entrance_New();
    void Login_New();
    void Signup_New();
    void ListChats_Set(); //It is more different than others
    void Settings_New();
    void Chat_New();
    void Search_New();

private:
    QStackedWidget *stackedWidget;

//    //to store unused heap address to clear at the end
//    QList <EntrancePage*> entrance_list;
//    QList <SignUpPage*> signup_list;
//    QList <LogInPage*> login_list;
////    std::vector <ListChatsPage*> listchats_list; //we just have one listchats in our program
//    QList <SettingsPage*> settings_list;
//    QList <ChatPage*> chat_list;

    //Declaring objects to work
    EntrancePage *entrance;
    SignUpPage *signup;
    LogInPage *login;
    ListChatsPage *listchats;
    SettingsPage *settings;
    ChatPage *chat;
    SearchPage *search;

public slots:
    //Functions to do for each obj:
    void Entrance_Func();
    void Signup_Func();
    void Login_Func();
    void Listchats_Func();
    void Settings_Func();
    void Chat_Func();
    void Search_Func();

signals:
    void _finish();
};

#endif // ADMINISTRATOR_H
