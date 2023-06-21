#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include "FilesOP/filesop.h"
#include "HttpRequest/httprequest.h"

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

private slots:
    void on_BackpushButton_clicked();
    void on_LogoutpushButton_clicked();

private:
    Ui::SettingsPage *ui;

public:
//Two attributes to switch between pages
    bool LogoutpushButton;
    bool BackpushButton;
    bool CreatepushButton;


signals:
    void _click();
public slots:
    void Linker(); //The Head of all we do, this is activated by clicking on Create
public:
    //These are related to make a channel or a group
    QJsonObject GetData(); //the data to create channel or group
    QString HttpCreator(const QJsonObject&);
    QString HttpAnalyser(const QJsonObject&);

    void CreatepushButton_clicked(); //it makes createpushbutton attribute true and emits signal
};

#endif // SETTINGSPAGE_H
