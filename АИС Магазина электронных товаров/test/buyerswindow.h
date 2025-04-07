#ifndef BUYERSWINDOW_H
#define BUYERSWINDOW_H


#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>
#include <twactions.h>
#include <QStringList>


namespace Ui {
class BuyersWindow;
}

class BuyersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BuyersWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~BuyersWindow();
signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();
    TableData getData();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

    void on_leLastnameSearch_textChanged(const QString &arg1);

    void on_leNameSearch_textChanged(const QString &arg1);

    void on_lePatronymicSearch_textChanged(const QString &arg1);

    void on_leEmailSearch_textChanged(const QString &arg1);

    void on_lePhoneSearch_textChanged(const QString &arg1);

    void on_twBuyers_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::BuyersWindow *ui;
    QSqlDatabase *dbconn;
    TableData data;
};

#endif // ADMINWINDOW_H
