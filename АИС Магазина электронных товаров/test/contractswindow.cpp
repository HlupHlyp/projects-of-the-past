#include "contractswindow.h"
#include "ui_contractswindow.h"

ContractsWindow::ContractsWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContractsWindow)
{
    ui->setupUi(this);
    this->data.dbconn = dbconn;
    this->data.table = ui->twContracts;
    this->data.tableName = QString("pacts");
    this->data.numColumns = 7;
    this->data.numArgs= 7;
    this->data.numSearchArgs = 4;
    this->data.numAddArgs = 4;

    QString cols[] = {QString("ID"), QString("ID С"), QString("Сотрудник"), QString("ID ПД"), QString("Представитель дистрибьютора"),
                      QString("Продукт"), QString("Дистрибьютор")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 0, 120, 0, 240, 250, 240};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("contract_id"), QString("staff_id"), QString("staff_last_name"),
                      QString("dist_repr_id"), QString("dist_repr_last_name"), QString("pr_name"), QString("distr_name")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString searchArgs[] = {QString("distr_name"), QString("staff_last_name"),
                            QString("dist_repr_last_name"), QString("pr_name")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("staff_id"), QString("dist_repr_id"),
                         QString("product_id"), QString("terms")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    twActions::markUp(this->getData());
    twActions::renew(this->getData());

    RequestStruct response = twActions::request(this->data.dbconn, QString("select distributor_id, distr_name from distributors"));
    int i=0;
    ui->cmbDistributorSearch->addItem("");

    while(response.query.next())
    {
            QString item = QString(response.query.value("distributor_id").toString() + "~" + response.query.value("distr_name").toString());
            ui->cmbDistributorSearch->addItem(item);
    }

    response = twActions::request(this->data.dbconn, QString("select staff_id, last_name from staff"));
    i=0;
    ui->cmbStaffSearch->addItem("");
    ui->cmbStaff->addItem("");

    while(response.query.next())
    {
            QString item = QString(response.query.value("staff_id").toString() + "~" + response.query.value("last_name").toString());
            ui->cmbStaffSearch->addItem(item);
            ui->cmbStaff->addItem(item);
    }

    response = twActions::request(this->data.dbconn, QString("select dist_repr_id, last_name from distribution_representatives"));
    i=0;
    ui->cmbDistReprSearch->addItem("");
    ui->cmbDistRepr->addItem("");

    while(response.query.next())
    {
            QString item = QString(response.query.value("dist_repr_id").toString() + "~" + response.query.value("last_name").toString());
            ui->cmbDistReprSearch->addItem(item);
            ui->cmbDistRepr->addItem(item);
    }

    response = twActions::request(this->data.dbconn, QString("select pr_name from products"));
    i=0;
    ui->cmbProductSearch->addItem("");
    ui->cmbProduct->addItem("");

    while(response.query.next())
    {
            QString item = QString(response.query.value("pr_name").toString());
            ui->cmbProductSearch->addItem(item);
            ui->cmbProduct->addItem(item);
    }

    data.table->setColumnHidden(1, true);
    data.table->setColumnHidden(3, true);
}

ContractsWindow::~ContractsWindow()
{
    delete ui;
}

void ContractsWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}

void ContractsWindow::on_btnAdd_clicked()
{
    this->data.tableName = QString("distribution_representatives");
    this->getData();
    bool f = false;
    for(int i=0;i<this->data.numAddArgs;i++)if(this->data.addArgs[i] == "") f = true;
    if(!f){
        twActions::add(this->data);
        this->data.tableName = QString("representatives");
        twActions::renew(this->getData());
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Одно из значений не задано");
        msgBox.setInformativeText("Ошибка");
        msgBox.exec();
        this->data.tableName = QString("representatives");
    }
}

void ContractsWindow::on_btnDelete_clicked()
{
    this->data.tableName = QString("distribution_representatives");
    twActions::del(this->getData());
    this->data.tableName = QString("representatives");
    twActions::renew(this->getData());
}

void ContractsWindow::on_btnChange_clicked()
{
    this->data.tableName = QString("distribution_representatives");

    twActions::edit(this->getData());
    this->data.tableName = QString("representatives");
    twActions::renew(this->getData());
}

TableData ContractsWindow::getData()
{

    QString distr = "";
    QString staff = "";
    QString distrepr = "";
    QString product = "";
    QString terms = "";

    if(ui->cmbStaffSearch->currentText() != "")
    {
            QStringList list = QString(ui->cmbStaffSearch->currentText()).split("~");
            staff = list[1];
    }
    if(ui->cmbDistReprSearch->currentText() != "")
    {
            QStringList list = QString(ui->cmbDistReprSearch->currentText()).split("~");
            distrepr = list[1];
    }
    if(ui->cmbDistributorSearch->currentText() != "")
    {
            QStringList list = QString(ui->cmbDistributorSearch->currentText()).split("~");
            distr = list[1];
    }
    product = QString(ui->cmbProductSearch->currentText());

    QString searchVals[] = {distr, staff, distrepr, product};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    if(ui->cmbStaff->currentText() != "")
    {
            QStringList list = QString(ui->cmbStaff->currentText()).split("~");
            staff = list[0];
    }
    if(ui->cmbDistReprSearch->currentText() != "")
    {
            QStringList list = QString(ui->cmbDistRepr->currentText()).split("~");
            distrepr = list[0];
    }

    terms = QString(ui->teTerms->toPlainText());

    RequestStruct response = twActions::request(this->data.dbconn,
                             QString("select product_id from products where pr_name = '" + product + "'"));

    while(response.query.next())
    {
            product = response.query.value("pr_id").toString();
    }

    QString addVals[] = {staff, distrepr, product, terms};

    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}


void ContractsWindow::on_cmbDistributorSearch_currentTextChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void ContractsWindow::on_cmbStaffSearch_currentTextChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void ContractsWindow::on_cmbDistReprSearch_currentTextChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void ContractsWindow::on_cmbProductSearch_currentTextChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void ContractsWindow::on_twContracts_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{




    QString worker = data.table->item(data.table->currentRow(),1)->text() + "~" + data.table->item(data.table->currentRow(),2)->text();
    int index = ui->cmbStaff->findText(worker);
    ui->cmbStaff->setCurrentIndex(index);

    QString representative = data.table->item(data.table->currentRow(),3)->text() + "~" + data.table->item(data.table->currentRow(),4)->text();
    index = ui->cmbDistRepr->findText(representative);
    ui->cmbDistRepr->setCurrentIndex(index);

    QString product = QString(data.table->item(data.table->currentRow(),5)->text());
    index = ui->cmbProduct->findText(product);
    ui->cmbProduct->setCurrentIndex(index);

    RequestStruct response = twActions::request(this->data.dbconn,
            QString("select terms from pacts where contract_id = " +
                    this->data.table->item(this->data.table->currentRow(),0)->text()) + "");
    response.query.next();

    ui->teTerms->setText(response.query.value("terms").toString());
}
