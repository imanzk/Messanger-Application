#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>

namespace Ui {
class SearchPage;
}

class SearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

private:
    Ui::SearchPage *ui;
};

#endif // SEARCHPAGE_H
