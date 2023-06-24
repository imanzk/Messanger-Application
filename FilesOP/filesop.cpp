#include "filesop.h"

FilesOP::FilesOP(QObject *parent)
    : QFile{parent}
{

}
//to return number of messages
int FilesOP::ReturnNumberMessages(const QJsonObject& data)
{
    //to get how many messages we have till now
    QString message = data.value("message").toString();
    int startindex = message.indexOf('-') + 1; // Find the index of the first ( - )
    int endindex = message.indexOf('-', startindex); // Find the index of the second one
    QString numberstr = message.mid(startindex, endindex - startindex);
    return numberstr.toInt();
}

//To Create Folders
void FilesOP::Create_Users_Folder()
{
    QDir dir;
    QString dirName = "Users";
    if (!dir.exists(dirName)) {

        bool success = dir.mkpath(dirName);

        if (success);
        else {
            QString Error = "Error creating folder.";
            throw Error;
        }
    }
//    else ; //the folder exists before
}
void FilesOP::Create_Groups_Folder()
{
    QDir dir;
    QString dirName = "Groups";
    if (!dir.exists(dirName)) {

        bool success = dir.mkpath(dirName);

        if (success);
        else {
            QString Error = "Error creating folder.";
            throw Error;
        }
    }
//    else ; //the folder exists before
}
void FilesOP::Create_Channels_Folder()
{
    QDir dir;
    QString dirName = "Channels";
    if (!dir.exists(dirName)) {

        bool success = dir.mkpath(dirName);

        if (success);
        else {
            QString Error = "Error creating folder.";
            throw Error;
        }
    }
    //else the folder exists before
}

//To Create new
void FilesOP::Create_User_File(const QString user_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Users/" + user_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.close();
}
void FilesOP::Create_Channel_File(const QString channel_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Channels/" + channel_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.close();
}
void FilesOP::Create_Group_File(const QString group_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Groups/" + group_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.close();
}

//To Get previous info before getting in ChatListPage
QJsonObject FilesOP::Get_Messages(const QString name)
{
    QJsonObject data;
    if(FilesOP::User_Exist(name)) data = FilesOP::Get_User_Messages(name);
    else if(FilesOP::Group_Exist(name)) data = FilesOP::Get_Group_Messages(name);
    else data = FilesOP::Get_Channel_Messages(name);
    return data;
}
QJsonObject FilesOP::Get_User_Messages(const QString user_name)
{
   QDir dir;
   QString path = dir.path();
   QFile file(path+"/Users/"+user_name+".json");

   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       QString Error = "Failed to read the file";
       throw Error;
   }

   QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
   QJsonObject jsonObj = jsonDoc.object();

   file.close();

   return jsonObj;
}
QJsonObject FilesOP::Get_Group_Messages(const QString group_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path+"/Groups/"+group_name+".json");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString Error = "Failed to read the file";
        throw Error;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = jsonDoc.object();

    file.close();

    return jsonObj;
}
QJsonObject FilesOP::Get_Channel_Messages(const QString channel_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path+"/Channels/"+channel_name+".json");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString Error = "Failed to read the file";
        throw Error;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = jsonDoc.object();

    file.close();

    return jsonObj;
}

//To get list of chats when we get in ListChatsPage
QJsonObject FilesOP::Get_Users_List()
{
   QDir dir("Users/");
   QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
   int size = listfiles.size();
   QJsonObject jsonObject;

   for ( int i = 0 ; i < size ; i ++)
   {
       QJsonObject block;
       listfiles[i].remove(".json");
       block["src"]=listfiles[i];
       jsonObject["block " + QString::number(i)]=block;
   }
   jsonObject["message"]="You Chat With -"+QString::number(size)+"- User";

   return jsonObject;
}
QJsonObject FilesOP::Get_Groups_List()
{
   QDir dir("Groups/");
   QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
   int size=listfiles.size();
   QJsonObject jsonObject;

   for ( int i = 0 ; i < size ; i ++)
   {
      QJsonObject block;
      listfiles[i].remove(".json");
      block["group_name"]=listfiles[i];
      jsonObject["block " + QString::number(i)]=block;
   }
   jsonObject["message"]="You Are in -"+QString::number(size)+"- Group";

   return jsonObject;
}
QJsonObject FilesOP::Get_Channels_List()
{
    QDir dir("Channels/");
    QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
    int size = listfiles.size();
    QJsonObject jsonObject;

    for ( int i = 0 ; i < size ; i ++)
    {
       QJsonObject block;
       listfiles[i].remove(".json");
       block["channel_name"]=listfiles[i];
       jsonObject["block " + QString::number(i)]=block;
    }
    jsonObject["message"]="You Are in -"+QString::number(size)+"- Channel";

    return jsonObject;
}

//To store messages
void FilesOP::Store_Messages(const QJsonObject data, const QString name)
{
    if(User_Exist(name))
    {
        Store_User_Messages(data,name);
    }
    else if(Group_Exist(name))
    {
        Store_Group_Messages(data,name);
    }
    else
    {
        Store_Channel_Messages(data,name);
    }
}
void FilesOP::Store_User_Messages(const QJsonObject data , const QString user_name)
{
    //to get json file to edit it
    QJsonObject jsonObj=Get_User_Messages(user_name);

    const int numberOld=ReturnNumberMessages(jsonObj);
    int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        QJsonObject block = data["block "+QString::number(i)].toObject();
        if(!block["body"].toString().isEmpty()) //if message isn't empty
        {
           //we add blocks of data json object to jsonObj to store in the json file
           jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
        }
        else
        {//else decrease the number of i and numberNew to control blocks of jsonObj
            i--; numberNew--;
        }
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Users\\"+user_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
}
void FilesOP::Store_Group_Messages(const QJsonObject data ,const QString group_name)
{
    //to get json file to edit it
    QJsonObject jsonObj=Get_Group_Messages(group_name);

    const int numberOld=ReturnNumberMessages(jsonObj);
    int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        QJsonObject block = data["block "+QString::number(i)].toObject();
        if(!block["body"].toString().isEmpty()) //if message isn't empty
        {
           //we add blocks of data json object to jsonObj to store in the json file
           jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
        }
        else
        {//else decrease the number of i and numberNew to control blocks of jsonObj
            i--; numberNew--;
        }
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Groups\\"+group_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
}
void FilesOP::Store_Channel_Messages(const QJsonObject data ,const QString channel_name)
{
    //to get json file to edit it
    QJsonObject jsonObj=Get_Channel_Messages(channel_name);

    const int numberOld=ReturnNumberMessages(jsonObj);
    int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        QJsonObject block = data["block "+QString::number(i)].toObject();
        if(!block["body"].toString().isEmpty()) //if message isn't empty
        {
           //we add blocks of data json object to jsonObj to store in the json file
           jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
        }
        else
        {//else decrease the number of i and numberNew to control blocks of jsonObj
            i--; numberNew--;
        }
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Channels\\"+channel_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
}

//if it exist returns true
bool FilesOP::User_Exist(const QString user_name)
{
    QString filename=user_name;
    QJsonObject list = Get_Users_List();
    int number=ReturnNumberMessages(list);
    for (int i = 0 ; i<number; i++)
    {
       QJsonObject block=list.value("block "+QString::number(i)).toObject();
       if(block.value("src").toString()==filename)
           return true;
    }
    return false;
}
bool FilesOP::Channel_Exist(const QString channel_name)
{
    QString filename=channel_name;
    QJsonObject list = Get_Channels_List();
    int number=ReturnNumberMessages(list);
    for (int i = 0 ; i<number; i++)
    {
       QJsonObject block=list.value("block "+QString::number(i)).toObject();
       if(block.value("channel_name").toString()==filename)
           return true;
    }
    return false;
}
bool FilesOP::Group_Exist(const QString group_name)
{
    QString filename=group_name;
    QJsonObject list = Get_Groups_List();
    int number=ReturnNumberMessages(list);
    for (int i = 0 ; i<number; i++)
    {
       QJsonObject block=list.value("block "+QString::number(i)).toObject();
       if(block.value("group_name").toString()==filename)
           return true;
    }
    return false;
}

//When we log out
void FilesOP::Remove_Users_List()
{
    QDir dir("Users");
    if (dir.exists()) {
        if (dir.removeRecursively());
        else {
            QString Error = "Error to remove folder";
            throw Error;
        }
    } else ;//folder doesn't exist
}
void FilesOP::Remove_Groups_List()
{
    QDir dir("Groups");
    if (dir.exists()) {
        if (dir.removeRecursively());
        else {
            QString Error = "Error to remove folder";
            throw Error;
        }
    } else ;//folder doesn't exist
}
void FilesOP::Remove_Channels_List()
{
    QDir dir("Channels");
    if (dir.exists()) {
        if (dir.removeRecursively());
        else {
            QString Error = "Error to remove folder";
            throw Error;
        }
    } else ;//folder doesn't exist
}

//to work with profile
void FilesOP::CreateProfile()
{
    QDir dir;
    QString dirName = "Profile";
    if (!dir.exists(dirName)) {

        bool success = dir.mkpath(dirName);

        if (success);
        else {
            QString Error = "Error creating folder.";
            throw Error;
        }
    } else ; //the folder exists before
}
void FilesOP::RemoveProfile()
{
    QDir dir("Profile");
    if (dir.exists()) {
        if (dir.removeRecursively());
        else {
            QString Error = "Error to remove folder";
            throw Error;
        }
    } else ;//folder doesn't exist
}
bool FilesOP::ExistProfile()
{
    QDir dir("Profile");
    if (dir.exists()) {
        return true;
    } else return false;//folder doesn't exist
}

//get and set token
void FilesOP::SetToken(const QString token)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"token.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.write(token.toUtf8());
    file.close();
}
QString FilesOP::GetToken()
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"token.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        QString Error = "Failed to Read the file";
        throw Error;
    }
    QString token=file.readAll();
    file.close();
    return token;
}

//get and set username
void FilesOP::SetUsername(const QString username)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"username.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.write(username.toUtf8());
    file.close();
}
QString FilesOP::GetUsername()
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"username.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        QString Error = "Failed to Read the file";
        throw Error;
    }
    QString username=file.readAll();
    file.close();
    return username;
}

//get and set password
void FilesOP::SetPassword(const QString password)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"password.txt");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    file.write(password.toUtf8());
    file.close();
}
QString FilesOP::GetPassword()
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "\\Profile\\"+"password.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        QString Error = "Failed to Read the file";
        throw Error;
    }
    QString password=file.readAll();
    file.close();
    return password;
}

//To get and write dst
void FilesOP::SetDst(const QString _dst)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path+"/Profile/dst.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    QString status = Status(_dst);
    QJsonObject jsonObj;
    //adding informations:
    jsonObj["dst"]=_dst;
    jsonObj["status"]=status;
    //
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
}
QJsonObject FilesOP::GetDst()
{
    QDir dir;
    QString path = dir.path();
    QFile file(path+"/Profile/dst.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = jsonDoc.object();

    return jsonObj;
}
QString FilesOP::Status(const QString dst)
{
    if(User_Exist(dst)) return "user";
    else if(Group_Exist(dst)) return "group";
    else if(Channel_Exist(dst))return "channel";
    else
    {
        QString error = "dst doesn't exist.";
        throw error;
    }
}

//QCoreApplication::ApplicationDirPassth


//to clear
void FilesOP::Clear_Messages(const QString name)
{
    if(User_Exist(name)) FilesOP::Clear_User_Messages(name);
    else if(Group_Exist(name)) FilesOP::Clear_Group_Messages(name);
    else FilesOP::Clear_Channel_Messages(name);
}
void FilesOP::Clear_User_Messages(const QString user_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Users/" + user_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    file.close();
}
void FilesOP::Clear_Channel_Messages(const QString channel_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Channels/" + channel_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    file.close();
}
void FilesOP::Clear_Group_Messages(const QString group_name)
{
    QDir dir;
    QString path = dir.path();
    QFile file(path + "/Groups/" + group_name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }
    file.close();
}

//to get time and number of messages of the last messages

QJsonObject FilesOP::LastTimeMessages(QString name)
{
    QJsonObject jsonObj;
    if(User_Exist(name))
        jsonObj = Get_User_Messages(name);
    else if(Group_Exist(name))
        jsonObj = Get_Group_Messages(name);
    else
        jsonObj = Get_Channel_Messages(name);


    const int size = ReturnNumberMessages(jsonObj);

    if(!size)
    {
        QString Error = "There is nothing in the file";
        throw Error;
    }

    int numberOFMessagesInTheLastTime = 1; //at least there is one message in the last time
    bool once = false;
    QDateTime lastDateTime;

    for(int i = size - 1 ; ; i --) //size - 1 is code of the last block
    {
        QJsonObject block = jsonObj["block "+QString::number(i)].toObject();
        QString dateString = block["date"].toString();
        QDateTime dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");

        if(!once)
        {//to initialize to compare in other steps
            once = true;
            lastDateTime = dateTime;
            continue;
        }

        if(lastDateTime != dateTime)
        {
            break;
        }
        else //we have another message in the same last date time
        {
            numberOFMessagesInTheLastTime++;
        }
    }

    QJsonObject last_time_messages;
    last_time_messages["date"] = lastDateTime.toString("yyyy-MM-dd hh:mm:ss");

    last_time_messages["message"]= "There Are -"+
            QString::number(numberOFMessagesInTheLastTime) +"- Messages";

     return last_time_messages;
}

//to get time and number of messages of the first messages
QJsonObject FilesOP::FirstTimeMessages(const QJsonObject messages)
{
    const int size = ReturnNumberMessages(messages);

    if(!size)
    {
        QString Error = "There is nothing in the messages";
        throw Error;
    }

    int numberOFMessagesInTheFirstTime = 1; //at least there is one message in the first time
    bool once = false;
    QDateTime FirstDateTime;

    for(int i = 0 ; ; i ++)
    {
        QJsonObject block = messages["block "+QString::number(i)].toObject();
        QString dateString = block["date"].toString();
        QDateTime dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");

        if(!once)
        {//to initialize to compare in other steps
            once = true;
            FirstDateTime = dateTime;
            continue;
        }

        if(FirstDateTime != dateTime)
        {
            break;
        }
        else //we have another message in the same last date time
        {
            numberOFMessagesInTheFirstTime++;
        }
    }

    QJsonObject first_time_messages;
    first_time_messages["date"] = FirstDateTime.toString("yyyy-MM-dd hh:mm:ss");

    first_time_messages["message"]= "There Are -"+
            QString::number(numberOFMessagesInTheFirstTime) +"- Messages";

     return first_time_messages;
}

//this method shows you the number of messages in the given datetime
int FilesOP::numberOFmessagesINtheTime(const QJsonObject jsonObj,const QString dateString)
{
    const int size = ReturnNumberMessages(jsonObj);
    int numberOFMessages = 0;
    QDateTime date_time_org = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");

    for(int i = 0; i < size ; i ++)
    {
        QJsonObject block = jsonObj["block "+QString::number(i)].toObject();
        QString dateString = block["date"].toString();
        QDateTime dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");

        if(dateTime == date_time_org) numberOFMessages++;
    }
    return numberOFMessages;
}

//it clears the related file and inserts data in it
void FilesOP::WriteOnlyMessages(const QJsonObject data, const QString name)
{
    QDir dir;
    QString path = dir.path();
    if(User_Exist(name)) path += "/Users/" ;
    else if (Group_Exist(name)) path += "/Groups/";
    else path += "/Channels/";

    QFile file(path + name +".json");

    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to open the file";
        throw Error;
    }

    QJsonDocument doc(data);
    file.write(doc.toJson());

    file.close();
}









































