#include "filesop.h"

FilesOP::FilesOP(QObject *parent)
    : QFile{parent}
{

}
//to return number of messages
int FilesOP::ReturnNumberMessages(const QJsonObject& data){
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
    } else ; //the folder exists before
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
    } else ; //the folder exists before
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
    } else ; //the folder exists before
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
   QDir dir("Users\\");
   QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
   QJsonObject jsonObject;

   for ( int i = 0 ; i < listfiles.size() ; i ++)
   {
       QJsonObject block;
       block["src"]=listfiles[i];
       jsonObject["block " + QString::number(i)]=block;
   }
   return jsonObject;
}
QJsonObject FilesOP::Get_Groups_List()
{
   QDir dir("Groups\\");
   QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
   QJsonObject jsonObject;

   for ( int i = 0 ; i < listfiles.size() ; i ++)
   {
      QJsonObject block;
      block["group_name"]=listfiles[i];
      jsonObject["block " + QString::number(i)]=block;
   }
   return jsonObject;
}
QJsonObject FilesOP::Get_Channels_List()
{
    QDir dir("Channels\\");
    QStringList listfiles = dir.entryList(QStringList() << "*", QDir::Files);
    QJsonObject jsonObject;

    for ( int i = 0 ; i < listfiles.size() ; i ++)
    {
       QJsonObject block;
       block["channel_name"]=listfiles[i];
       jsonObject["block " + QString::number(i)]=block;
    }
    return jsonObject;
}

//To store messages
void FilesOP::Store_User_Messages(const QJsonObject data , const QString user_name)
{
    //to get json file to edit it
    QJsonObject jsonObj=Get_User_Messages(user_name);

    const int numberOld=ReturnNumberMessages(jsonObj);
    const int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        //we add blocks of data json object to jsonObj to store in the json file
        jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Users\\"+user_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
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
    const int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        //we add blocks of data json object to jsonObj to store in the json file
        jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Groups\\"+group_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
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
    const int numberNew=ReturnNumberMessages(data);

    for (int i = 0;i < numberNew ; i++)
    {
        //we add blocks of data json object to jsonObj to store in the json file
        jsonObj["block "+QString::number(i+numberOld)]=data["block "+QString::number(i)];
    }
    //to edit the message of the jsonObj
    jsonObj["message"]="There Are -"+QString::number(numberOld+numberNew)+"- Message";

    //to open the file to write in it
    QDir dir;
    QString path = dir.path();
    QFile file(path+"\\Channels\\"+channel_name+".json");
    if(!file.open(QIODevice::WriteOnly))
    {
        QString Error = "Failed to create the file";
        throw Error;
    }
    QJsonDocument doc(jsonObj);
    file.write(doc.toJson());
    file.close();
}













































































