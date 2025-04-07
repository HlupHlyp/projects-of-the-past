#include "admin.h"
#include "ui_admin.h"
Admin::Admin(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

//void Admin::on_pushButton_clicked()
//{
//   this->close();      // Закрываем окно
//    emit firstWindow(); // И вызываем сигнал на открытие главного окна
//}
