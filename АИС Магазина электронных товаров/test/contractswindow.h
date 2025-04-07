#ifndef CONTRACTSWINDOW_H
#define CONTRACTSWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>
#include <twactions.h>

#include <QStringList>

namespace Ui {
class ContractsWindow;
}

class ContractsWindow : public QWidget
{
    Q_OBJECT
    friend class DistRepsWindow;
public:
    explicit ContractsWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~ContractsWindow();
    void renew();
    TableData data;
signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

    TableData getData();

    void on_cmbDistributorSearch_currentTextChanged(const QString &arg1);

    void on_cmbStaffSearch_currentTextChanged(const QString &arg1);

    void on_cmbDistReprSearch_currentTextChanged(const QString &arg1);

    void on_cmbProductSearch_currentTextChanged(const QString &arg1);

    void on_twContracts_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::ContractsWindow *ui;
    QSqlDatabase *dbconn;
};

#endif // ADMINWINDOW_H


