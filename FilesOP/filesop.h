#ifndef FILESOP_H
#define FILESOP_H

#include <QFile>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

class FilesOP : public QFile
{


public:

    explicit FilesOP(QObject *parent = nullptr);

    //function to use from outside

    //To Create Folders
    static void Create_Users_Folder();
    static void Create_Groups_Folder();
    static void Create_Channels_Folder();

    //To Create new
    static void Create_User_File(const QString user_name);
    static void Create_Channel_File(const QString channel_name);
    static void Create_Group_File(const QString group_name);

    //To Get previous info before getting in ChatListPage
    static QJsonObject Get_User_Messages(const QString user_name);
    static QJsonObject Get_Group_Messages(const QString group_name);
    static QJsonObject Get_Channel_Messages(const QString channel_name);

    //To get recently received and sent messages when we are in ChatPage (Optional)
    static QJsonObject Get_User_Recently(const QString user_name , const QDateTime datetime);
    static QJsonObject Get_Group_Recently(const QString group_name , const QDateTime datetime);
    static QJsonObject Get_Channel_Recently(const QString channel_name , const QDateTime datetime);

    //To get list of chats when we get in ListChatsPage
    static QJsonObject Get_Users_List();
    static QJsonObject Get_Groups_List();
    static QJsonObject Get_Channels_List();

    //To store messages
    static void Store_User_Messages(const QJsonObject data ,const QString user_name);
    static void Store_Group_Messages(const QJsonObject data , const QString group_name);
    static void Store_Channel_Messages(const QJsonObject data , const QString channel_name);

    //When we want to figure out if this chat exists before
    static bool Search_User(const QString user_name);
    static bool Search_Channel(const QString channel_name);
    static bool Search_Group(const QString group_name);

    //When we log out
    static void Remove_Users_List();
    static void Remove_Groups_List();
    static void Remove_Channels_List();

    //to return number of messages
    static int ReturnNumberMessages(const QJsonObject& data);

};

#endif // FILESOP_H
























