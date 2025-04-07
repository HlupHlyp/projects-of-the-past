#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <buyerswindow.h>
#include <staffwindow.h>
#include <itemswindow.h>
#include <contractswindow.h>
#include <distributorswindow.h>
#include <authorwindow.h>
#include <ordersWindow.h>
#include <distrepswindow.h>
#include <QSqlDatabase>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~AdminWindow();
signals:
    void prevWindow();
private slots:
    void on_btnExit_clicked();

    void on_btnBuyers_clicked();

    void on_btnStaff_clicked();

    void on_btnItems_clicked();

    void on_btnDistributors_clicked();

    void on_btnOrders_clicked();

    void on_btnDistrReps_clicked();

    void on_btnStaff_2_clicked();

    void on_btnBuyers_2_clicked();

private:
    Ui::AdminWindow *ui;
    BuyersWindow *buyersWindow;
    StaffWindow *staffWindow;
    ItemsWindow *itemsWindow;
    DistributorsWindow *distributorsWindow;
    OrdersWindow *ordersWindow;
    DistRepsWindow *distrepsWindow;
    ContractsWindow *contractsWindow;
    AuthorWindow *authorWindow;
};

#endif // ADMINWINDOW_H
