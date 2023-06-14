#include <QApplication>
#include "Administrator/administrator.h"
#include "ListChats/listchatspage.h"
#include "Chat/chatpage.h"
#include "Settings/settingspage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Administrator admin;

//    ChatPage chat;
//    chat.show();

//    ListChatsPage List;
//    List.show();

    SettingsPage setting;
    setting.show();

//    ChatPage chat;
//    chat.show();

//    ListChatsPage List;
//    List.show();

//    SettingsPage setting;
//    setting.show();

    return app.exec();
}




















