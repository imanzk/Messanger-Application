#include "threadlist.h"

ThreadList::ThreadList(QObject *parent)
    : QThread{parent}
{
    stop=false;

    FilesOP::Create_Users_Folder();
    FilesOP::Create_Channels_Folder();
    FilesOP::Create_Groups_Folder();

}

void ThreadList::run()
{
    while(!stop)
    {
        Linker("getuserlist");
        QThread::sleep(2);
    }
}

//to manage operations
void ThreadList::Linker(const QString command)
{
   try{
     QString url=HttpCreator(command);
     QJsonObject information=HttpRequest::Http_request_operation(url);
     if(information["code"]=="401")
     {
         QString Error=information["message"].toString();
         throw Error;
     }
     if(command=="getuserlist") Analyser_userlist(information);
     else if(command=="getchannellist") Analyser_channellist(information);
     else Analyser_grouplist(information);


    }
   catch(QString Error){
        qDebug() << Error;
    }
}

//operations
QString ThreadList::HttpCreator(const QString command)
{
    return command+"?"+"token="+FilesOP::GetToken();
}

//
void ThreadList::Analyser_userlist(const QJsonObject information)
{
    QJsonObject newData;
    int temp=0;
    int size=FilesOP::ReturnNumberMessages(information);
    for(int i = 0 ; i < size ; i++)
    {
        QJsonObject block;
        block=information.value("block "+QString::number(i)).toObject();
        if(!FilesOP::User_Exist(block["src"].toString()))
        {
            FilesOP::Create_User_File(block["src"].toString());
            newData["block "+QString::number(temp)] = information.value("block "+QString::number(i));
            temp++;
        }
    }
    newData["message"]="You Chat With -"+QString::number(temp)+"- User";
    if(temp)
      emit newUser(newData);
}
void ThreadList::Analyser_grouplist(const QJsonObject information)
{
    QJsonObject newData;

    int temp=0;
    int size=FilesOP::ReturnNumberMessages(information);
    for(int i = 0 ; i < size ; i++)
    {
        QJsonObject block;
        block=information.value("block "+QString::number(i)).toObject();
        if(!FilesOP::Group_Exist(block["group_name"].toString()))
        {
            FilesOP::Create_Group_File(block["group_name"].toString());
            newData["block "+QString::number(temp)] = information.value("block "+QString::number(i));
            temp++;
        }
    }
    newData["message"]="You Are in -"+QString::number(temp)+"- Group";
    if(temp)
      emit newGroup(newData);
}
void ThreadList::Analyser_channellist(const QJsonObject information)
{
    QJsonObject newData;

    int temp=0;
    int size=FilesOP::ReturnNumberMessages(information);
    for(int i = 0 ; i < size ; i++)
    {
        QJsonObject block;
        block=information.value("block "+QString::number(i)).toObject();
        if(!FilesOP::Channel_Exist(block["channel_name"].toString()))
        {
            FilesOP::Create_Channel_File(block["channel_name"].toString());
            newData["block "+QString::number(temp)] = information.value("block "+QString::number(i));
            temp++;
        }
    }
    newData["message"]="You Are in -"+QString::number(temp)+"- Channel";
    if(temp)
       emit newChannel(newData);
}
























