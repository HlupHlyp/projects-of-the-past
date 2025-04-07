#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>
#include <twactions.h>
#include <QStringList>
#include <contractswindow.h>

namespace Ui {
class StaffWindow;
}

class StaffWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StaffWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~StaffWindow();
signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

    void on_btnBack_2_clicked();

    TableData getData();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

    void on_leLastnameSearch_textChanged(const QString &arg1);

    void on_leNameSearch_textChanged(const QString &arg1);

    void on_lePatronymicSearch_textChanged(const QString &arg1);

    void on_leEmailSearch_textChanged(const QString &arg1);

    void on_lePhoneSearch_textChanged(const QString &arg1);

    void on_lePostSearch_textChanged(const QString &arg1);

    void on_twStaff_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::StaffWindow *ui;
    TableData data;
    ContractsWindow *contractsWindow;
};

#endif // ADMINWINDOW_H
