#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    Vlayout = new QVBoxLayout;
    Width_Spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Preferred);
    Height_Spacer = new QSpacerItem(0,0, QSizePolicy::Preferred, QSizePolicy::Preferred);
    Spacer = new QSpacerItem(0,0, QSizePolicy::Preferred, QSizePolicy::Expanding);

    Vlayout->addItem(Spacer);
    ui->scrollArea->setLayout(Vlayout);

}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::make(QString username,QString text)
{
    label_username=new QLabel(username);
    text_username=new QLabel;

    text_username->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    text_username->setWordWrap(true);
    text_username->setStyleSheet("background-color: rgb(255, 255, 255);");

    label_username->setFont(QFont("Arial", 10, QFont::Bold, false));
    text_username->setFont(QFont("Arial", 11));

    text_username->setText(text);

    h_layout=new QHBoxLayout;
    v_layout_username=new QVBoxLayout;
    v_layout_text=new QVBoxLayout;

    v_layout_username->addWidget(label_username);

    v_layout_text->addWidget(text_username);
    v_layout_text->addItem(Width_Spacer);
    v_layout_text->addItem(Height_Spacer);

    h_layout->addLayout(v_layout_username);
    h_layout->addLayout(v_layout_text);
    h_layout->addItem(Width_Spacer);

    Vlayout->addLayout(h_layout);

}


