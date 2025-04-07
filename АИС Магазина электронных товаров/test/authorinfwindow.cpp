#include "authorinfwindow.h"
#include "ui_authorinfwindow.h"

authorInfWindow::authorInfWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::authorInfWindow)
{
    ui->setupUi(this);
}
authorInfWindow::~authorInfWindow()
{
    delete ui;
}


void authorInfWindow::on_btnBack_clicked()
{

}
