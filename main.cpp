#include "SignUp/signuppage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignUpPage w;
    w.show();
    return a.exec();
}
