#ifndef ORDERSWINDOW_H
#define ORDERSWINDOW_H

#include <QWidget>
#include <buyerswindow.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDate>
#include <twactions.h>

namespace Ui {
class OrdersWindow;
}

class OrdersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~OrdersWindow();
signals:
    void prevWindow();
private slots:

    void on_btnBack_2_clicked();
    void SCDProducts(); // SCD - Set Constant Data

    void SCDOrders(); // SCD - Set Constant Data

    void SCDBuyers(); // SCD - Set Constant Data

    void SCDOrderComposition(); // SCD - Set Constant Data

    TableData GDProducts(); // GD - GET DATA

    TableData GDOrders(); // GD - GET DATA

    TableData GDBuyers(); // GD - GET DATA

    void buyersRenew(); // GD - GET DATA

    void orderCompositionRenew(); // GD - GET DATA

    void productsRenew();

    void ordersRenew();

    void LoadCmbs();

    void on_cmbPrTypeSearch_currentTextChanged(const QString &arg1);

    void on_cmbPrGenreSearch_currentTextChanged(const QString &arg1);

    void on_lePrNameSearch_textChanged(const QString &arg1);

    void on_leEmailSearch_textChanged(const QString &arg1);

    void on_cmbPaySearch_currentTextChanged(const QString &arg1);

    void on_cmbSendSearch_currentTextChanged(const QString &arg1);

    QDate String2Date(QString date);

    void on_deLeftDateSearch_userDateChanged(const QDate &date);

    void on_deRightDateSearch_userDateChanged(const QDate &date);

    void on_twOrders_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_twItems_itemDoubleClicked(QTableWidgetItem *item);

    void on_twComposition_itemDoubleClicked(QTableWidgetItem *item);

    void on_twBuyers_itemDoubleClicked(QTableWidgetItem *item);

    void on_btnAdd_3_clicked();

    QString Date2String(QDate date);

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

    void on_btnAdd_4_clicked();

private:
    Ui::OrdersWindow *ui;
    BuyersWindow *buyersWindow;
    QSqlDatabase *dbconn;
    TableData products;
    TableData buyers;
    TableData orders;
    TableData composition;
    bool firstGen;
};

#endif // ORDERSWINDOW_H

