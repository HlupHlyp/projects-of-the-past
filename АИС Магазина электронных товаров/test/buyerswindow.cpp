#include "buyerswindow.h"
#include "ui_buyerswindow.h"
#include "QTextStream"


BuyersWindow::BuyersWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyersWindow)
{
    ui->setupUi(this);

    this->data.dbconn = dbconn;
    this->data.table = ui->twBuyers;
    this->data.tableName = QString("buyers");
    this->data.numColumns = 6;
    this->data.numArgs= 6;
    this->data.numSearchArgs = 5;
    this->data.numAddArgs = 5;

    QString cols[] = {QString("ID"), QString("Фамилия"), QString("Имя"),
                      QString("Отчество"), QString("Email"), QString("Телефон")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 120, 120, 150, 220, 150};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("buyer_id"), QString("last_name"), QString("first_name"),
                      QString("patronymic"), QString("email"), QString("phone")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString searchArgs[] = {QString("last_name"), QString("first_name"),
                            QString("patronymic"), QString("email"), QString("phone")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("last_name"), QString("first_name"),
                         QString("patronymic"), QString("email"), QString("phone")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    twActions::markUp(this->getData());
    twActions::renew(this->getData());
}

BuyersWindow::~BuyersWindow()
{
    delete ui;
}

void BuyersWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}

TableData BuyersWindow::getData()
{
    QString searchVals[] = {QString(ui->leLastnameSearch->text()), QString(ui->leNameSearch->text()),
                           QString(ui->lePatronymicSearch->text()), QString(ui->leEmailSearch->text()),
                           QString(ui->lePhoneSearch->text())};

    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    QString addVals[] = {QString("'" + ui->leLastname->text() + "'"), QString("'" + ui->leName->text() + "'"),
                         QString("'" + ui->lePatronymic->text() + "'"), QString("'" + ui->leEmail->text() + "'"),
                         QString("'" + ui->lePhone->text() + "'")};

    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}


void BuyersWindow::on_btnAdd_clicked()
{
    twActions::add(this->getData());
    twActions::renew(this->getData());
}

void BuyersWindow::on_btnDelete_clicked()
{
    twActions::del(this->getData());
    twActions::renew(this->getData());
}

void BuyersWindow::on_btnChange_clicked()
{
    twActions::edit(this->getData());
    twActions::renew(this->getData());
}

void BuyersWindow::on_leLastnameSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void BuyersWindow::on_leNameSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void BuyersWindow::on_lePatronymicSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void BuyersWindow::on_leEmailSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void BuyersWindow::on_lePhoneSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void BuyersWindow::on_twBuyers_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    ui->leLastname->setText(data.table->item(data.table->currentRow(),1)->text());
    ui->leName->setText(data.table->item(data.table->currentRow(),2)->text());
    ui->lePatronymic->setText(data.table->item(data.table->currentRow(),3)->text());
    ui->leEmail->setText(data.table->item(data.table->currentRow(),4)->text());
    ui->lePhone->setText(data.table->item(data.table->currentRow(),5)->text());
}
