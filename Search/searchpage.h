#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>
#include "HttpRequest/httprequest.h"
#include "FilesOP/filesop.h"

namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

signals:
    void _click();
public slots:
    void Linker(); //The Head of all we do, this is activated by clicking on commandlinkButton
public:

    QString GetData();
    QString HttpCreator(const QString& , const QString command);
    QString HttpAnalyser(const QJsonObject&);
    void Make_New(const QString&,const QString command); // to make new channel , group or user and initialize dst
    void commandLinkButton_clicked(); //to send signal to the administrator

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::SearchPage *ui;
};

#endif // SEARCHPAGE_H
