#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui{
class Admin;
}
class Admin: public QWidget
{
    Q_OBJECT

public:
    Admin(QWidget *parent = 0);
    ~Admin();
signals:
    void prevWindow();
private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
