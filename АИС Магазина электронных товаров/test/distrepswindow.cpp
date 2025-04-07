#include "distrepswindow.h"
#include "ui_distrepswindow.h"

DistRepsWindow::DistRepsWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DistRepsWindow)
{
    ui->setupUi(this);
    this->data.dbconn = dbconn;
    this->data.table = ui->twDistReps;
    this->data.tableName = QString("representatives");
    this->data.numColumns = 8;
    this->data.numArgs= 8;
    this->data.numSearchArgs = 7;
    this->data.numAddArgs = 7;

    QString cols[] = {QString("ID"), QString("Фамилия"), QString("Имя"), QString("Отчество"), QString("Email"), QString("Должность"),
                     QString("Телефон"), QString("Дистрибьютор")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 120, 120, 120, 240, 200, 150, 240};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("dist_repr_id"), QString("last_name"), QString("first_name"),
                      QString("patronymic"), QString("email"), QString("post"), QString("phone"), QString("distr_name")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString searchArgs[] = {QString("last_name"), QString("first_name"),
                            QString("patronymic"), QString("email"), QString("post"), QString("phone"), QString("distr_name")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("last_name"), QString("first_name"),
                         QString("patronymic"), QString("email"), QString("post"), QString("phone"), QString("distributor_id")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    twActions::markUp(this->getData());
    twActions::renew(this->getData());

    RequestStruct response = twActions::request(this->data.dbconn, QString("select distributor_id, distr_name from distributors"));
    int i=0;

    ui->cmbDistributorSearch->addItem("");
    ui->cmbDistributor->addItem("");

    while(response.query.next())
    {
            QString item = QString(response.query.value("distributor_id").toString() + "~" + response.query.value("distr_name").toString());
            ui->cmbDistributorSearch->addItem(item);
            ui->cmbDistributor->addItem(item);
    }

    contractsWindow = new ContractsWindow(dbconn);
    connect(contractsWindow, &ContractsWindow::prevWindow, this, &DistRepsWindow::show);
}

DistRepsWindow::~DistRepsWindow()
{
    delete ui;
}

void DistRepsWindow::on_btnBack_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}

void DistRepsWindow::on_btnAdd_clicked()
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

void DistRepsWindow::on_btnDelete_clicked()
{
    this->data.tableName = QString("distribution_representatives");
    twActions::del(this->getData());
    this->data.tableName = QString("representatives");
    twActions::renew(this->getData());
}

void DistRepsWindow::on_btnChange_clicked()
{
    this->data.tableName = QString("distribution_representatives");

    twActions::edit(this->getData());
    this->data.tableName = QString("representatives");
    twActions::renew(this->getData());
}

TableData DistRepsWindow::getData()
{

    QString distr = "";
    if(ui->cmbDistributorSearch->currentText() != "")
    {
            QStringList distributor = QString(ui->cmbDistributorSearch->currentText()).split("~");
            distr = distributor[1];
    }
    QString searchVals[] = {QString(ui->leLastnameSearch->text()), QString(ui->leNameSearch->text()),
                           QString(ui->lePatronymicSearch->text()), QString(ui->leEmailSearch->text()),
                           QString(ui->lePostSearch->text()), QString(ui->lePhoneSearch->text()),
                           distr};

    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    distr = "";
    if(ui->cmbDistributor->currentText() != "")
    {
        QStringList distributor = QString(ui->cmbDistributor->currentText()).split("~");
        distr = distributor[0];
    }

    QString addVals[] = {QString("'" + ui->leLastname->text() + "'"), QString("'" + ui->leName->text() + "'"),
                         QString("'" + ui->lePatronymic->text() + "'"), QString("'" + ui->leEmail->text() + "'"),
                         QString("'" + ui->lePost->text() + "'"), QString("'" + ui->lePhone->text() + "'"),
                         distr};

    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}

void DistRepsWindow::on_leLastnameSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_cmbDistributorSearch_currentTextChanged(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_twDistReps_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    ui->leLastname->setText(data.table->item(data.table->currentRow(),1)->text());
    ui->leName->setText(data.table->item(data.table->currentRow(),2)->text());
    ui->lePatronymic->setText(data.table->item(data.table->currentRow(),3)->text());
    ui->leEmail->setText(data.table->item(data.table->currentRow(),4)->text());
    ui->lePost->setText(data.table->item(data.table->currentRow(),5)->text());
    ui->lePhone->setText(data.table->item(data.table->currentRow(),6)->text());

    RequestStruct response = twActions::request(this->data.dbconn,
            QString("select distributor_id from distributors where distr_name = '" +
                    this->data.table->item(this->data.table->currentRow(),7)->text()) + "'");
    response.query.next();

    int index = ui->cmbDistributor->findText(response.query.value("distributor_id").toString()
                                    + "~" + this->data.table->item(this->data.table->currentRow(),7)->text());
    ui->cmbDistributor->setCurrentIndex(index);
}

void DistRepsWindow::on_leEmailSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_lePhoneSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_leNameSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_lePatronymicSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_lePostSearch_textEdited(const QString &arg1)
{
    twActions::search(this->getData());
}

void DistRepsWindow::on_btnBack_2_clicked()
{
    twActions::load(contractsWindow->data,
                    twActions::request(contractsWindow->data.dbconn,
                                       "select * from pacts where dist_repr_id = " +
                                       QString(data.table->item(data.table->currentRow(),0)->text())));
    contractsWindow->show();
    this->close();
}
