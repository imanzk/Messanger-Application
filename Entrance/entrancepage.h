#ifndef ENTRANCEPAGE_H
#define ENTRANCEPAGE_H

#include <QWidget>

namespace Ui {
class EntrancePage;
}

class EntrancePage : public QWidget
{
    Q_OBJECT

public:
    explicit EntrancePage(QWidget *parent = nullptr);
    ~EntrancePage();

    bool LoginPage;
    bool SignupPage;
private slots:
    void on_Login_pushButton_clicked();
    void on_Signup_pushButton_clicked();
private:
    Ui::EntrancePage *ui;
signals:
    void _click();
};

#endif // ENTRANCEPAGE_H
