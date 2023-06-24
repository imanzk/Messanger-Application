#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QListWidgetItem>
#include "threadchat.h"


namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();

    ThreadChat *threadchat;

    /*because of we have just one object from chatpage in our all program so each time we
    have to customize it*/
//    void Customize();

    //to show each message
    void ShowMessagesManager(const QJsonObject info); // it manages two bottom methods
    void ShowMessage(const QString username,const QString text ,const QString time);
    void ShowMyMessage(const QString text , const QString time);

    //if we pass a day, it shows the new day date and it always return the time of the message
    QString ShowEachDay(const QString date_time);

    //to recovery and show previous information
    void Recovery();

private:
    Ui::ChatPage *ui;
    QListWidgetItem *item;
    QDate recentDate;//it has recent date messages and works with ShowEachDay method
    int numberOFprintedMessage;
    bool once; //when we get in the chat page , it goes to the last messages
public slots:
    //a slot to get new messages and show them
    void NewMessagesSlot(const QJsonObject receivedInfo);

public :
    //to send messages:
    void Linker_send(const QString body);
    QString HttpCreator_send(const QString body);
    void Analyser(const QJsonObject);
private slots:
    void on_Sendpushbutton_clicked();
    void on_Backpushbutton_clicked();

signals:
    void _click(); //it is connected to administrator
};


#endif // CHATPAGE_H
