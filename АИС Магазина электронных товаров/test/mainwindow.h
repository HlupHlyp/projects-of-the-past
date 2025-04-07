#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <adminwindow.h>
#include <ordersWindow.h>
#include <QComboBox>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <twactions.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    // Слоты от кнопок главного окна

    void on_btnEnter_4_clicked();

    void on_btnExit_5_clicked();

private:
    Ui::MainWindow *ui;
    // второе и третье окна
    AdminWindow *menuWindow;
    OrdersWindow *ordersWindow;
    QSqlDatabase dbconn;
};

#endif // MAINWINDOW_H
