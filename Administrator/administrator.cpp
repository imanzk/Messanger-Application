#include "administrator.h"

Administrator::Administrator(QObject *parent)
    : QObject{parent}
{
    stackedWidget=new QStackedWidget;
//Intialize to null
   signup=nullptr;
   login=nullptr;
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
        WidgetSelection(login,400,400);
    }
    else //SignUpPage is true
    {
        Signup_New();
        WidgetSelection(signup,400,400);
    }
}
void Administrator::Signup_Func()
{
    if(signup->OKpushButton)
    {
       //Go again to entrance page
       Entrance_New();
       WidgetSelection(entrance, 400, 400);
    }
    else if(signup->CancelpushButton)
    {
       //Go again to entrance page too :)
       Entrance_New();
       WidgetSelection(entrance, 400, 400);
    }
}
void Administrator::Login_Func()
{
    if(login->OKpushButton)
    {
       //Go to a empty list
    }
    else if(login->CancelpushButton)
    {
       //Go to entrance page
       Entrance_New();
       WidgetSelection(entrance, 400, 400);
    }
}

/***************News***************/

void Administrator::Entrance_New()
{
    if(entrance)
    {
      entrance_list.push_back(entrance);
    }
    entrance=new EntrancePage;
    connect(entrance,SIGNAL(_click()),this,SLOT(Entrance_Func()));
}
void Administrator::Signup_New()
{
    if(signup)
    {
      signup_list.push_back(signup);
    }
    signup=new SignUpPage;
    connect(signup,SIGNAL(_click()),this,SLOT(Signup_Func()));
}
void Administrator::Login_New()
{
    if(login)
    {
        login_list.push_back(login);
    }
    login=new LogInPage;
    connect(login,SIGNAL(_click()),this,SLOT(Login_Func()));
}







