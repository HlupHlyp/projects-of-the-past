#ifndef AUTHORWINDOW_H
#define AUTHORWINDOW_H

#include <QWidget>
#include <twactions.h>

namespace Ui {
class AuthorWindow;
}

class AuthorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorWindow(QWidget *parent = nullptr);
    ~AuthorWindow();

signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

private:
    Ui::AuthorWindow  *ui;
    TableData data;
};


#endif // AUTHORWINDOW_H
