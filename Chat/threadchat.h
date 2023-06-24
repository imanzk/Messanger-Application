#ifndef THREADCHAT_H
#define THREADCHAT_H

#include <QThread>
#include <QObject>
#include "FilesOP/filesop.h"
#include "HttpRequest/httprequest.h"

class ThreadChat : public QThread
{
    Q_OBJECT
public:
    explicit ThreadChat(QObject *parent = nullptr);
    //to start
    bool stop;
    void run() override;

    //to do operations
    void Linker(); //if bool is false , it gets messages when we haven't been in the chat page

    //operations
    QString HttpCreator(const QString command);
    void Analyser(const QJsonObject); //to store to the files and emit newMessages signal

signals:

    void newMessages(const QJsonObject);
};

#endif // THREADCHAT_H
