#include "authorwindow.h"
#include "ui_authorwindow.h"

AuthorWindow::AuthorWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::AuthorWindow)
{
    ui->setupUi(this);
}
AuthorWindow::~AuthorWindow()
{
    delete ui;
}


void AuthorWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow();
}

