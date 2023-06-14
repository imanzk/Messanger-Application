QT       += core gui
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Administrator/administrator.cpp \
    Chat/chatpage.cpp \
    Entrance/entrancepage.cpp \
    HttpRequest/httprequest.cpp \
    ListChats/listchatspage.cpp \
    LogIn/loginpage.cpp \
    Search/searchpage.cpp \
    Settings/settingspage.cpp \
    SignUp/signuppage.cpp \
    Thread/thread.cpp \
    main.cpp

HEADERS += \
    Administrator/administrator.h \
    Chat/chatpage.h \
    Entrance/entrancepage.h \
    HttpRequest/httprequest.h \
    ListChats/listchatspage.h \
    LogIn/loginpage.h \
    Search/searchpage.h \
    Settings/settingspage.h \
    SignUp/signuppage.h \
    Thread/thread.h

FORMS += \
    Chat/chatpage.ui \
    Entrance/entrancepage.ui \
    ListChats/listchatspage.ui \
    LogIn/loginpage.ui \
    Search/searchpage.ui \
    Settings/settingspage.ui \
    SignUp/signuppage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
