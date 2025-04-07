#ifndef DISTRIBUTORSWINDOW_H
#define DISTRIBUTORSWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>
#include <twactions.h>

namespace Ui {
class DistributorsWindow;
}


class DistributorsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DistributorsWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~DistributorsWindow();
    void renew();

    TableData getData();
    //Request request(QString request_text);
    //QString searchString();
signals:
    void prevWindow();
private slots:

    void on_btnBack_clicked();

    void on_leINNSearch_textEdited(const QString &arg1);

    void on_leNameSearch_textEdited(const QString &arg1);

    void on_btnDelete_clicked();

    void on_btnAdd_clicked();

    void on_btnChange_clicked();

    void on_twDistributors_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::DistributorsWindow *ui;
    QSqlDatabase *dbconn;
    TableData data;
};

#endif // ADMINWINDOW_H
