#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUrl>
#include <QCoreApplication>

class HttpRequest : public QWidget
{
    Q_OBJECT
public:
    HttpRequest(QWidget *parent = nullptr);
    ~HttpRequest();
private:
    QUrl URL;
    QNetworkAccessManager *Manager;
    QNetworkReply *Reply;

public:
    QJsonObject Http_request_operation(const QString&);//Read and write, reply is returned

};

#endif // HTTPREQUEST_H
