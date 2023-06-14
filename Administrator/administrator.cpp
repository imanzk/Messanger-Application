#include "administrator.h"

Administrator::Administrator(QObject *parent)
    : QObject{parent}
{
   stackedWidget=new QStackedWidget;
//Intialize to null
   signup=nullptr;
   login=nullptr;
   listchats=nullptr;
//Start
   entrance=new EntrancePage;
   WidgetSelection(entrance, 400, 400);
   connect(entrance,SIGNAL(_click()),this,SLOT(Entrance_Func()));
}

Administrator::~Administrator()
{
    delete stackedWidget;

    for(int i = 0;i < (int)entrance_list.size() ;i++)
    {
        delete entrance_list[i];
    }
    for(int i = 0;i < (int)signup_list.size() ;i++)
    {
        delete signup_list[i];
    }
    for(int i = 0;i < (int)login_list.size() ;i++)
    {
        delete login_list[i];
    }
}

void Administrator::WidgetSelection(QWidget *PageWidget,const int parameter1, const int parameter2 )
{
//to set
    stackedWidget->addWidget(PageWidget);
    stackedWidget->setCurrentWidget(PageWidget);
//to resize
    QRect rect;
    rect.setBottomRight (QPoint(parameter1,parameter2));
    stackedWidget->setGeometry (rect);
//to set position
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    QPoint center = screenGeometry.center();
    stackedWidget->move(center - stackedWidget->rect().center());
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
       //Go to the listchats page
       ListChats_New();
    }
    else if(login->CancelpushButton)
    {
       //Go to entrance page
       Entrance_New();
    }
}
void Administrator::Listchats_Func()
{

}
/***************News***************/

void Administrator::Entrance_New()
{
    entrance=new EntrancePage;
    WidgetSelection(entrance, 400, 400);
    entrance_list.push_back(entrance);
    connect(entrance,SIGNAL(_click()),this,SLOT(Entrance_Func()));
}
void Administrator::Signup_New()
{
    signup=new SignUpPage;
    WidgetSelection(signup,400,400);
    signup_list.push_back(signup);
    connect(signup,SIGNAL(_click()),this,SLOT(Signup_Func()));
}
void Administrator::Login_New()
{
    login=new LogInPage;
    WidgetSelection(login,400,400);
    login_list.push_back(login);
    connect(login,SIGNAL(_click()),this,SLOT(Login_Func()));
}
void Administrator::ListChats_New()
{
    listchats=new ListChatsPage;
    WidgetSelection(listchats,400,400);
    listchats_list.push_back(listchats);
    connect(listchats,SIGNAL(_click()),this,SLOT(Listchats_Func()));
}






