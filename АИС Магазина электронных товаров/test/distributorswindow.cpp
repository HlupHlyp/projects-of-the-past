#include "distributorswindow.h"
#include "ui_distributorswindow.h"

DistributorsWindow::DistributorsWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DistributorsWindow)
{
    ui->setupUi(this);
    this->data.dbconn = dbconn;
    this->data.table = ui->twDistributors;
    this->data.tableName = QString("Distributors");
    this->data.numColumns = 5;
    this->data.numArgs= 5;
    this->data.numSearchArgs = 2;
    this->data.numAddArgs = 4;

    QString cols[] = {QString("ID"), QString("Компания"), QString("ИНН"), QString("ЧС"), QString("Телефон")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 240, 120, 50, 150};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("distributor_id"), QString("distr_name"), QString("inn"),
                      QString("blacklist"), QString("phone")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString searchArgs[] = {QString("distr_name"), QString("inn")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("distr_name"), QString("inn"), QString("blacklist"), QString("phone")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    twActions::markUp(this->getData());
    twActions::renew(this->getData());
    int rowCount = data.table->rowCount();
    for(int i=0;i<rowCount;i++){
        if(data.table->item(i,3)->text() == "true")
            (*data.table).setItem(i,3,new QTableWidgetItem("✓"));
        else (*data.table).setItem(i,3,new QTableWidgetItem("✗"));
    }
}

DistributorsWindow::~DistributorsWindow()
{
    delete ui;
}

void DistributorsWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}

TableData DistributorsWindow::getData()
{
    QString searchVals[] = {QString(ui->leNameSearch->text()),
                            QString(ui->leINNSearch->text())};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    QString cbBlackList = QString("");
    if(ui->cbBlackList->isChecked())
        cbBlackList = QString("true");
    else
        cbBlackList = QString("false");

    QString addVals[] = {QString("'" + ui->leName->text() + "'"), QString("'" + ui->leINN->text() + "'"),
                            cbBlackList, QString("'" + ui->lePhone->text() + "'")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}

void DistributorsWindow::on_leINNSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistributorsWindow::on_leNameSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistributorsWindow::on_btnDelete_clicked()
{
    twActions::del(this->getData());
}

void DistributorsWindow::on_btnAdd_clicked()
{
    twActions::add(this->getData());
}

void DistributorsWindow::on_btnChange_clicked()
{
    twActions::edit(this->getData());
    twActions::renew(this->getData());
}

void DistributorsWindow::on_twDistributors_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    ui->leName->setText(data.table->item(data.table->currentRow(),1)->text());
    ui->leINN->setText(data.table->item(data.table->currentRow(),2)->text());
    ui->lePhone->setText(data.table->item(data.table->currentRow(),4)->text());
    QString blacklist = QString(data.table->item(data.table->currentRow(),3)->text());
    if(blacklist == "✓") ui->cbBlackList->setChecked(true);
    else ui->cbBlackList->setChecked(false);
}
