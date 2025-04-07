#ifndef DISTREPSWINDOW_H
#define DISTREPSWINDOW_H

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
class DistRepsWindow;
}

class DistRepsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DistRepsWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~DistRepsWindow();
    void renew();
signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

    TableData getData();

    void on_leLastnameSearch_textEdited(const QString &arg1);

    void on_cmbDistributorSearch_currentTextChanged(const QString &arg1);

    void on_twDistReps_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_leEmailSearch_textEdited(const QString &arg1);

    void on_lePhoneSearch_textEdited(const QString &arg1);

    void on_leNameSearch_textEdited(const QString &arg1);

    void on_lePatronymicSearch_textEdited(const QString &arg1);

    void on_lePostSearch_textEdited(const QString &arg1);

    void on_btnBack_2_clicked();

private:
    Ui::DistRepsWindow *ui;
    QSqlDatabase *dbconn;
    TableData data;
    ContractsWindow *contractsWindow;
};

#endif // ADMINWINDOW_H
