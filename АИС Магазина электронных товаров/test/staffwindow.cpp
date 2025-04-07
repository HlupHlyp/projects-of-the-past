#include "staffwindow.h"
#include "ui_staffwindow.h"

StaffWindow::StaffWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffWindow)
{
    ui->setupUi(this);
    this->data.dbconn = dbconn;
    this->data.table = ui->twStaff;
    this->data.tableName = QString("staff");
    this->data.numColumns = 7;
    this->data.numArgs= 7;
    this->data.numSearchArgs = 6;
    this->data.numAddArgs = 6;

    QString cols[] = {QString("ID"), QString("Фамилия"), QString("Имя"), QString("Отчество"),
                      QString("Email"), QString("Должность"), QString("Телефон")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 120, 120, 180, 210, 230, 150};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("staff_id"), QString("last_name"), QString("first_name"),
                      QString("patronymic"), QString("email"), QString("post"), QString("phone")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString searchArgs[] = {QString("last_name"), QString("first_name"), QString("patronymic"),
                            QString("email"), QString("post"), QString("phone")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("last_name"), QString("first_name"), QString("patronymic"),
                         QString("email"), QString("post"), QString("phone")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    twActions::markUp(this->getData());
    twActions::renew(this->getData());
    contractsWindow = new ContractsWindow(dbconn);
    connect(contractsWindow, &ContractsWindow::prevWindow, this, &StaffWindow::show);
}

StaffWindow::~StaffWindow()
{
    delete ui;
}


void StaffWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow();
}

TableData StaffWindow::getData()
{

    QString searchVals[] = {QString(ui->leLastnameSearch->text()), QString(ui->leNameSearch->text()),
                           QString(ui->lePatronymicSearch->text()), QString(ui->leEmailSearch->text()),
                           QString(ui->lePostSearch->text()), QString(ui->lePhoneSearch->text())};

    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    QString addVals[] = {QString("'" + ui->leLastname->text() + "'"), QString("'" + ui->leName->text() + "'"),
                         QString("'" + ui->lePatronymic->text() + "'"), QString("'" + ui->leEmail->text() + "'"),
                         QString("'" + ui->lePost->text() + "'"), QString("'" + ui->lePhone->text() + "'")};

    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}

void StaffWindow::on_btnBack_2_clicked()
{
    twActions::load(contractsWindow->data,
                    twActions::request(contractsWindow->data.dbconn,
                                       "select * from pacts where staff_id = " +
                                       QString(data.table->item(data.table->currentRow(),0)->text())));
    contractsWindow->show();
    this->close();
}

void StaffWindow::on_btnAdd_clicked()
{
    twActions::add(this->getData());
    twActions::renew(this->getData());
}

void StaffWindow::on_btnDelete_clicked()
{
    twActions::del(this->getData());
    twActions::renew(this->getData());
}

void StaffWindow::on_btnChange_clicked()
{
    twActions::edit(this->getData());
    twActions::renew(this->getData());
}

void StaffWindow::on_leLastnameSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_leNameSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_lePatronymicSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_leEmailSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_lePhoneSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_lePostSearch_textChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void StaffWindow::on_twStaff_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    ui->leLastname->setText(data.table->item(data.table->currentRow(),1)->text());
    ui->leName->setText(data.table->item(data.table->currentRow(),2)->text());
    ui->lePatronymic->setText(data.table->item(data.table->currentRow(),3)->text());
    ui->leEmail->setText(data.table->item(data.table->currentRow(),4)->text());
    ui->lePost->setText(data.table->item(data.table->currentRow(),5)->text());
    ui->lePhone->setText(data.table->item(data.table->currentRow(),6)->text());
}
