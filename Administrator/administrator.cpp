#include "administrator.h"

Administrator::Administrator(QObject *parent)
    : QObject{parent}
{
   stackedWidget=new QStackedWidget;
   listchats=new ListChatsPage;

   connect(listchats,SIGNAL(_click()),this,SLOT(Listchats_Func()));

   stackedWidget->addWidget(listchats);

//Intialize to null
   signup=nullptr;
   login=nullptr;
   settings=nullptr;
   entrance=nullptr;
   chat=nullptr;
   search=nullptr;
   listchats = nullptr;
//to resize
   QRect rect;
   rect.setBottomRight (QPoint(400,400));
   stackedWidget->setGeometry (rect);
//to set position
   QScreen *screen = QGuiApplication::primaryScreen();
   QRect screenGeometry = screen->geometry();
   QPoint center = screenGeometry.center();
   stackedWidget->move(center - stackedWidget->rect().center());


   // to Start:

   //if user logged in before , don't open Entrance page ,go to listchats instead
   if(FilesOP::ExistProfile())
   {
       ListChats_Set();
   }
   else{
       Entrance_New();
   }
}

Administrator::~Administrator()
{
    //I comment the following loop becuase we just have one listchats in our program

//    for(int i = 0;i < (int)listchats_list.size() ;i++)
//    {
//        delete listchats_list[i];
//    }

//    for(int i = 0;i < (int)entrance_list.size() ;i++)
//    {
//        delete entrance_list[i];
//    }
//    for(int i = 0;i < (int)signup_list.size() ;i++)
//    {
//        delete signup_list[i];
//    }
//    for(int i = 0;i < (int)login_list.size() ;i++)
//    {
//        delete login_list[i];
//    }
//    for(int i = 0;i < (int)settings_list.size() ;i++)
//    {
//        delete settings_list[i];
//    }
//    for(int i = 0;i < (int)settings_list.size() ;i++)
//    {
//        delete settings_list[i];
//    }
    if(chat)delete chat;
    if(entrance)delete entrance;
    if(signup)delete signup;
    if(login)delete login;
    if(listchats)delete listchats;
    if(search)delete search;
    delete stackedWidget;
}

void Administrator::WidgetSelection(QWidget *PageWidget)
{
//to set
    stackedWidget->setCurrentWidget(PageWidget);
//to show
    stackedWidget->show();
}

/************Functions**********/

void Administrator::Entrance_Func()
{

    if(entrance->LoginPage)
    {
        Login_New();
    }
    else //SignUpPage is true
    {
        Signup_New();
    }
}
void Administrator::Signup_Func()
{
    if(signup->OKpushButton)
    {
       //Go to entrance page
       Entrance_New();
    }
    else if(signup->CancelpushButton)
    {
       //Go again to entrance page :)
       Entrance_New();
    }
}
void Administrator::Login_Func()
{
    if(login->OKpushButton)
    {
        if(listchats) {
            stackedWidget->removeWidget(listchats);
            delete listchats;
            listchats=nullptr;
        }
        ListChats_Set();
    }
    else if(login->CancelpushButton)
    {
       //Go to entrance page 
       Entrance_New();
    }
}
void Administrator::Listchats_Func()
{
    if(listchats->Search_pushButton)
    {
        Search_New();
        listchats->Customize();//because of huge reason :/
    }
    else if(listchats->Setting_pushButton)
    {        
        listchats->threadlist->stop=true; //to stop running
        Settings_New();
    }
    else if(listchats->Item_pushButton)//listchats->Item_pushButton is true
    {
        listchats->threadlist->stop=true; //to stop running
        Chat_New();
    }
}
void Administrator::Settings_Func()
{
    if(settings->BackpushButton)
    {  //back to the listchats
        ListChats_Set();//to start running
    }
    else if(settings->LogoutpushButton)
    {   //the program goes to the Entrance page
        listchats->threadlist->stop=true;
        Entrance_New();
    }
    else if(settings->CreatepushButton)
    {
        Chat_New();
    }
}
void Administrator::Chat_Func()
{
    chat -> threadchat -> stop = true; //it doesn't continue
    //back to the listchats
    ListChats_Set(); //to start running
}
void Administrator::Search_Func()
{
    search->hide();
    listchats->threadlist->stop=true;
    Chat_New();
}

/***************News***************/

void Administrator::Entrance_New()
{
    if(entrance)
    {
        stackedWidget->removeWidget(entrance);
        delete entrance;
    }
    entrance=new EntrancePage;
    stackedWidget->addWidget(entrance);
    stackedWidget->setWindowTitle("Entrance");
    WidgetSelection(entrance);
//    entrance_list.append(entrance);
    connect(entrance,SIGNAL(_click()),this,SLOT(Entrance_Func()));
}
void Administrator::Signup_New()
{
    if(signup)
    {
        stackedWidget->removeWidget(signup);
        delete signup;
    }
    signup=new SignUpPage;
    stackedWidget->addWidget(signup);
    WidgetSelection(signup);
    stackedWidget->setWindowTitle("Sign up");
//    signup_list.append(signup);
    connect(signup,SIGNAL(_click()),this,SLOT(Signup_Func()));
}
void Administrator::Login_New()
{
    if(login)
    {
        stackedWidget->removeWidget(login);
        delete login;
    }
    login=new LogInPage;
    stackedWidget->addWidget(login);
    WidgetSelection(login);
    stackedWidget->setWindowTitle("Log in");
//    login_list.append(login);
    connect(login,SIGNAL(_click()),this,SLOT(Login_Func()));
}
void Administrator::ListChats_Set()
{
    if(!listchats)
    {
        listchats=new ListChatsPage;
        stackedWidget->addWidget(listchats);
        connect(listchats,SIGNAL(_click()),this,SLOT(Listchats_Func()));
    }
    WidgetSelection(listchats);
    listchats->Customize();
    stackedWidget->setWindowTitle(FilesOP::GetUsername());
    //If something is in our files, it shows it
    listchats->Recovery();
}
void Administrator::Settings_New()
{
    if(settings)
    {
        stackedWidget->removeWidget(settings);
        delete settings;
    }
    settings=new SettingsPage;
    stackedWidget->addWidget(settings);
    WidgetSelection(settings);
    connect(settings,SIGNAL(_click()),this,SLOT(Settings_Func()));
}
void Administrator::Chat_New()
{
    if(chat)
    {
        stackedWidget->removeWidget(chat);
        delete chat;
    }
    chat=new ChatPage;
    stackedWidget->addWidget(chat);
    WidgetSelection(chat);

    chat->Recovery();
    chat->threadchat->start();

    connect(chat,SIGNAL(_click()),this,SLOT(Chat_Func()));
}
void Administrator::Search_New() //we don't want it to show on stackedwidget
{
    if(search)
    {
        delete search;
    }
    search = new SearchPage;
    search->show();

    connect(search,SIGNAL(_click()),this,SLOT(Search_Func()));
}




