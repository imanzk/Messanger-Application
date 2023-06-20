#ifndef THREADLIST_H
#define THREADLIST_H

#include <QThread>
#include <QObject>
#include "FilesOP/filesop.h"
#include "HttpRequest/httprequest.h"


class ThreadList : public QThread
{
Q_OBJECT

public:
    explicit ThreadList(QObject *parent = nullptr);
    //to start
    void run() override;
    bool stop;
    //to do operations
    void Linker(const QString command);

    //operations
    QString HttpCreator(const QString command);
    void Analyser_userlist(const QJsonObject);
    void Analyser_grouplist(const QJsonObject);
    void Analyser_channellist(const QJsonObject);

signals:

    void newUser(const QJsonObject);
    void newGroup(const QJsonObject);
    void newChannel(const QJsonObject);
};

#endif // THREADLIST_H
