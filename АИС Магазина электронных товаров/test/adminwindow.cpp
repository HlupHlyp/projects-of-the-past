#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    buyersWindow = new BuyersWindow(dbconn);
    connect(buyersWindow, &BuyersWindow::prevWindow, this, &AdminWindow::show);
    staffWindow = new StaffWindow(dbconn);
    connect(staffWindow, &StaffWindow::prevWindow, this, &AdminWindow::show);
    itemsWindow = new ItemsWindow(dbconn);
    connect(itemsWindow, &ItemsWindow::prevWindow, this, &AdminWindow::show);
    distributorsWindow = new DistributorsWindow(dbconn);
    connect(distributorsWindow, &DistributorsWindow::prevWindow, this, &AdminWindow::show);
    ordersWindow = new OrdersWindow(dbconn);
    connect(ordersWindow, &OrdersWindow::prevWindow, this, &AdminWindow::show);
    distrepsWindow = new DistRepsWindow(dbconn);
    connect(distrepsWindow, &DistRepsWindow::prevWindow, this, &AdminWindow::show);
    contractsWindow = new ContractsWindow(dbconn);
    connect(contractsWindow, &ContractsWindow::prevWindow, this, &AdminWindow::show);
    authorWindow = new AuthorWindow();
    connect(authorWindow, &AuthorWindow::prevWindow, this, &AdminWindow::show);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_btnExit_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}


void AdminWindow::on_btnBuyers_clicked()
{
    buyersWindow->show();
    this->close();
}

void AdminWindow::on_btnStaff_clicked()
{
    staffWindow->show();
    this->close();
}

void AdminWindow::on_btnItems_clicked()
{
    itemsWindow->show();
    this->close();
}

void AdminWindow::on_btnDistributors_clicked()
{
    distributorsWindow->show();
    this->close();
}

void AdminWindow::on_btnOrders_clicked()
{
    ordersWindow->show();
    this->close();
}

void AdminWindow::on_btnDistrReps_clicked()
{
    distrepsWindow->show();
    this->close();
}

void AdminWindow::on_btnStaff_2_clicked()
{
    contractsWindow->show();
    this->close();
}

void AdminWindow::on_btnBuyers_2_clicked()
{
    authorWindow->show();
    this->close();
}
