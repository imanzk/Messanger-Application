#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QScrollArea>
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();

    void make(QString username,QString text );

private:
    Ui::ChatPage *ui;
    QVBoxLayout *Vlayout;
    QSpacerItem *Width_Spacer;
    QSpacerItem *Height_Spacer;
    QSpacerItem *Spacer;
    //attributes
    QLabel *label_username;
    QLabel *text_username;
    QHBoxLayout *h_layout;
    QVBoxLayout *v_layout_username;
    QVBoxLayout *v_layout_text;
};

#endif // CHATPAGE_H
