#ifndef FILESOP_H
#define FILESOP_H

#include <QFile>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

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
    static QJsonObject Get_Messages(const QString name);//its manager
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

    //clear files
    static void Clear_Messages(const QString name); //it manages three bottom methods
    static void Clear_User_Messages(const QString user_name);
    static void Clear_Group_Messages(const QString channel_name);
    static void Clear_Channel_Messages(const QString group_name);

    //To store messages
    static void Store_Messages(const QJsonObject data, const QString name);//it is manager of the three botto method
    static void Store_User_Messages(const QJsonObject data ,const QString user_name);
    static void Store_Group_Messages(const QJsonObject data , const QString group_name);
    static void Store_Channel_Messages(const QJsonObject data , const QString channel_name);

    //we use it when a new person may send message to us for the first time
    static bool User_Exist(const QString user_name);
    /*we use these when we want to join to a channel or group*/
    static bool Channel_Exist(const QString channel_name);
    static bool Group_Exist(const QString group_name);

    //When we log out
    static void Remove_Users_List();
    static void Remove_Groups_List();
    static void Remove_Channels_List();

    //to return number of messages
    static int ReturnNumberMessages(const QJsonObject& data);

    //create profile folder to store token and username and password of the user into it
    static void CreateProfile();
    static void RemoveProfile();
    static bool ExistProfile();

    //To get and write token
    static QString GetToken();
    static void SetToken(const QString );

    //To get and write username
    static QString GetPassword();
    static void SetPassword(const QString );

    //To get and write username
    static QString GetUsername();
    static void SetUsername(const QString );

    //To get and write dst
    static QJsonObject GetDst();
    static void SetDst(const QString _dst);
    //it specifies the status of dst (user , group or channel) with searching in files
    static QString Status(const QString dst);

    //to get time and number of messages of the last messages
    static QJsonObject LastTimeMessages(const QString name);
    //to get time and number of messages of the first messages
    static QJsonObject FirstTimeMessages(const QJsonObject messages);

    //this method shows you the number of messages in the given datetime
    static int numberOFmessagesINtheTime(const QJsonObject jsonObj, const QString dateString);

    //it clears the related file and inserts data in it
    static void WriteOnlyMessages(const QJsonObject data, const QString name);
};

#endif // FILESOP_H
























