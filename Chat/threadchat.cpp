#include "threadchat.h"

ThreadChat::ThreadChat(QObject *parent)
    : QThread{parent}
{
   stop=false;
}

void ThreadChat::run()
{
   while(!stop)
   {
       Linker();
       QThread::sleep(1);
   }
}

void ThreadChat::Linker()
{
    try {
       QJsonObject jsonObj = FilesOP::GetDst();
       QString command = "get"+jsonObj["status"].toString()+"chats";
       QString url = HttpCreator(command);
       QJsonObject receivedInfo = HttpRequest::Http_request_operation(url);
       Analyser(receivedInfo);
       emit newMessages(receivedInfo);
    }
    catch (const QString Error) {
       qDebug() << Error;
    }
}

QString ThreadChat::HttpCreator(const QString command)
{
    QJsonObject dst_info = FilesOP::GetDst();
    QString dst = dst_info["dst"].toString();
    QString url = command + "?token=" + FilesOP::GetToken() + "&dst=" + dst;

    return url;
}

void ThreadChat::Analyser(const QJsonObject receivedInfo)
{
    QJsonObject jsonObj = FilesOP::GetDst();
    const QString dst = jsonObj["dst"].toString();
    const QString status = jsonObj["status"].toString();
    if (receivedInfo["code"].toString()!="200")
    {
        QString Error = jsonObj["message"].toString();
        throw Error;
    }
    else
    {
        //we clear the file and store new messages
        FilesOP::WriteOnlyMessages(receivedInfo , dst);
    }
}













