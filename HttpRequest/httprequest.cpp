#include "HttpRequest/httprequest.h"
#define ADDRESS "http://api.barafardayebehtar.ml:8080/"

HttpRequest::HttpRequest(QWidget *parent) :  QWidget(parent)
{
    Manager = new QNetworkAccessManager;
}
HttpRequest::~HttpRequest()
{
    delete Manager;
    delete Reply;
}

QJsonObject HttpRequest::Http_request_operation(const QString &url)
{
   QJsonObject jsonObj;
   URL = ADDRESS+url;

   Reply = Manager->get(QNetworkRequest(URL));

   QEventLoop loop;
   QObject::connect(Reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
   loop.exec();

   if (Reply->error() != QNetworkReply::NoError)
       {
          QString Error="ERROR : ";
          Error+=Reply->errorString();
          throw Error;
       }
   else
       {  //Getting data and convert it to json object
          QByteArray data = Reply->readAll();
          QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
          jsonObj = jsonDoc.object();
       }
   return jsonObj;
}

