#ifndef ITEMSWINDOW_H
#define ITEMSWINDOW_H


#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>
#include <twactions.h>
#include <QPixmap>
#include <QTableWidget>
#include <QBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
const int IMAGE_VMARGIN = 10;

namespace Ui {
class ItemsWindow;
}

class ItemsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsWindow(QSqlDatabase *dbconn, QWidget *parent = nullptr);
    ~ItemsWindow();
signals:
    void prevWindow();
private slots:

    void on_btnBack_2_clicked();
    TableData getData();
    void renew();

    void on_cmbTypeSearch_currentTextChanged(const QString &arg1);

    void on_leNameSearch_textChanged(const QString &arg1);

    void loadCmbs();

    void on_cmbGenreSearch_currentTextChanged(const QString &arg1);

    void on_twItems_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_btnBackSpace_clicked();

    void on_btnAddGenre_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnChange_clicked();

private:
    Ui::ItemsWindow *ui;
    TableData data;
    QSqlDatabase *dbconn;
    bool firstGen;
};

#endif // ADMINWINDOW_H
