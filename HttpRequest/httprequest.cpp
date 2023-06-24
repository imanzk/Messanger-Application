#include "HttpRequest/httprequest.h"
#define ADDRESS "http://api.barafardayebehtar.ml:8080/"

HttpRequest::HttpRequest(QWidget *parent) :  QWidget(parent)
{

}
HttpRequest::~HttpRequest()
{

}

QJsonObject HttpRequest::Http_request_operation(const QString &url)
{
   QUrl URL;

   QJsonObject jsonObj;
   URL = ADDRESS+url;

   QNetworkAccessManager Manager;
   QNetworkReply *Reply;

   Reply = Manager.get(QNetworkRequest(URL));
//   reply_list.append(Reply);
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

