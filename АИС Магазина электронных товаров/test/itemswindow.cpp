#include "itemswindow.h"
#include "ui_itemswindow.h"

ItemsWindow::ItemsWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsWindow)
{
    ui->setupUi(this);
    this->data.dbconn = dbconn;
    this->data.table = ui->twItems;
    this->data.tableName = QString("products");
    this->data.numColumns = 6;
    this->data.numArgs= 6;
    this->data.numSearchArgs = 2; //жанр, тип, наименование
    this->data.numAddArgs = 6;
    this->firstGen = true;

    QString cols[] = {QString("ID"), QString("Наименование"), QString("Тип"), QString("Расположение иконки"),
                      QString("Расположение файла"), QString("Стоимость")};
    for(int i=0;i<this->data.numColumns;i++) this->data.columns[i] = cols[i];

    int colSizes[] = {30, 240, 120, 210, 240, 90};
    for(int i=0;i<this->data.numColumns;i++) this->data.columnSizes[i] = colSizes[i];

    QString args[] = {QString("product_id"), QString("pr_name"), QString("pr_type"),
                      QString("image_adress"), QString("pr_link"), QString("pr_cost")};
    for(int i=0;i<this->data.numArgs;i++) this->data.args[i] = args[i];

    QString addArgs[] = {QString("pr_name"), QString("pr_type"),
                         QString("image_adress"), QString("pr_link"), QString("pr_cost"), QString("description")};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addArgs[i] = addArgs[i];

    QString searchArgs[] = {QString("pr_type"), QString("pr_name")};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchArgs[i] = searchArgs[i];

    renew();
    loadCmbs();
}

ItemsWindow::~ItemsWindow()
{
    delete ui;
}

void ItemsWindow::on_btnBack_2_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow(); // И вызываем сигнал на открытие главного окна
}

TableData ItemsWindow::getData()
{
    QString searchVals[] = {ui->cmbTypeSearch->currentText(), ui->leNameSearch->text()};
    for(int i=0;i<this->data.numSearchArgs;i++) this->data.searchVals[i] = searchVals[i];

    QString addVals[] = {QString("'" + ui->leName->text() + "'"), QString("'" + ui->cmbType->currentText() + "'"),
                            QString("'" + ui->leImage->text() + "'"), QString("'" + ui->leLocation->text() + "'"),
                            QString(ui->leCost->text()), QString("'" + ui->teDescription->toPlainText()) + "'"};
    for(int i=0;i<this->data.numAddArgs;i++) this->data.addVals[i] = addVals[i];
    return this->data;
}

void ItemsWindow::renew(){
    twActions::markUp(this->getData());
    twActions::search(this->getData());
    QMessageBox msgBox;
    msgBox.setText("After search");
    int colNum = data.numColumns;
    colNum++;
    twActions::externalColumn(&(this->data), colNum, "Жанр", 210);

    int rowCount = data.table->rowCount();
    if(rowCount != 0){

        for(int i=0;i<rowCount;i++){
            QString pr_id = data.table->item(i,0)->text();
            RequestStruct response = twActions::request(this->data.dbconn, QString("select genre_name from genres inner join product_2_genre "
                                                                                   "on genres.genre_id=product_2_genre.genre_id "
                                                                                   "inner join products "
                                                                                   "on products.product_id=product_2_genre.product_id "
                                                                                   "where products.product_id = " + pr_id));
            QString genre_set = "";
            while(response.query.next())
                    genre_set = genre_set + response.query.value("genre_name").toString() + ",";

            genre_set.chop(1);
            (*data.table).setItem(i,colNum-1,new QTableWidgetItem(genre_set));
        }
        colNum++;
        twActions::externalColumn(&(this->data), colNum, "Изображение", 100);

        for(int i=0;i<rowCount;i++){
            (*data.table).setItem(i,colNum-1,new QTableWidgetItem(""));
            patterns::setPicture(data.table, i, colNum-1, 10, data.table->item(i,3)->text());
        }

        data.table->setColumnHidden(3, true);
    }
}

void ItemsWindow::on_cmbTypeSearch_currentTextChanged(const QString &arg1)
{
    renew();
}

void ItemsWindow::on_leNameSearch_textChanged(const QString &arg1)
{
    renew();
}

void ItemsWindow::loadCmbs(){
    RequestStruct response = twActions::request(this->data.dbconn, QString("select * from types"));

    ui->cmbTypeSearch->addItem("");
    ui->cmbType->addItem("");

    while(response.query.next())
    {
            QString item = response.query.value("type_name").toString();
            ui->cmbTypeSearch->addItem(item);
            ui->cmbType->addItem(item);
    }

    response = twActions::request(this->data.dbconn, QString("select genre_name from genres"));

    ui->cmbGenreSearch->addItem("");
    ui->cmbGenre->addItem("");

    while(response.query.next())
    {
            QString item = response.query.value("genre_name").toString();
            ui->cmbGenreSearch->addItem(item);
            ui->cmbGenre->addItem(item);
    }
}

void ItemsWindow::on_cmbGenreSearch_currentTextChanged(const QString &arg1)
{
    renew();
    if(!this->firstGen){
        bool outerFlag = true;
        int outerNumRows = data.table->rowCount();
        while(outerFlag){
            bool innerFlag = true;
            int innerNumRows = data.table->rowCount();
            int i = 0;
            while(innerFlag && i<innerNumRows){
                QString rowGenre = QString(data.table->item(i,6)->text());
                if(!rowGenre.contains(ui->cmbGenreSearch->currentText())){
                    data.table->removeRow(i);
                    innerFlag = false;
                }
                i++;
            }
            if(i == innerNumRows)
                outerFlag = false;
        }
    }
    this->firstGen = false;
}

void ItemsWindow::on_twItems_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    ui->leGenres->setText(data.table->item(data.table->currentRow(),6)->text());
    ui->leName->setText(data.table->item(data.table->currentRow(),1)->text());
    ui->leImage->setText(data.table->item(data.table->currentRow(),3)->text());
    ui->leLocation->setText(data.table->item(data.table->currentRow(),4)->text());
    ui->leCost->setText(data.table->item(data.table->currentRow(),5)->text());

    RequestStruct response = twActions::request(this->data.dbconn,
            QString("select description from products where product_id = " +
                    this->data.table->item(this->data.table->currentRow(),0)->text()));
    response.query.next();

    ui->teDescription->setText(response.query.value("description").toString());

    int index = ui->cmbType->findText(this->data.table->item(this->data.table->currentRow(),2)->text());
    ui->cmbType->setCurrentIndex(index);
}

void ItemsWindow::on_btnBackSpace_clicked()
{
    QString genres = ui->leGenres->text();
    int size = genres.size();
    int lastComma = genres.lastIndexOf(",");
    genres.chop(size - lastComma);
    ui->leGenres->setText(genres);
}

void ItemsWindow::on_btnAddGenre_clicked()
{
    if(ui->cmbGenre->currentText() != "")
        ui->leGenres->setText(ui->leGenres->text() + "," + ui->cmbGenre->currentText());

    RequestStruct response = twActions::request(this->data.dbconn,
            QString("select description from products where product_id = " +
                    this->data.table->item(this->data.table->currentRow(),0)->text()));
    response.query.next();

    ui->teDescription->setText(response.query.value("description").toString());

    int index = ui->cmbType->findText(this->data.table->item(this->data.table->currentRow(),2)->text());
    ui->cmbType->setCurrentIndex(index);
}

void ItemsWindow::on_btnAdd_clicked()
{
    QString product_name = ui->leName->text();
    twActions::add(this->getData());

    RequestStruct response = twActions::request(this->data.dbconn,
            QString("select product_id from products where pr_name = '" +
                    product_name + "'"));
    response.query.next();

    QString product_id = response.query.value("product_id").toString();
    QStringList genres = ui->leGenres->text().split(",");
    for(int i=0;i<genres.size();i++){
        response = twActions::request(this->data.dbconn,
                                      QString("select genre_id from genres where genre_name = '" +
                                              genres[i] + "'"));
        response.query.next();
        QString genre_id = response.query.value("genre_id").toString();
        twActions::request(this->data.dbconn,
                                              QString("insert into product_2_genre (product_id, genre_id) values(" +
                                                      product_id + ", " + genre_id + ")"));
    }
    renew();
}

void ItemsWindow::on_btnDelete_clicked()
{
    QString product_id = this->data.table->item(this->data.table->currentRow(),0)->text();
    RequestStruct response = twActions::request(this->data.dbconn,
            QString("delete from product_2_genre where product_id = " + product_id));
    response = twActions::request(this->data.dbconn,
            QString("delete from order_2_product where product_id = " + product_id));
    response = twActions::request(this->data.dbconn,
            QString("delete from contracts where product_id = " + product_id));
    twActions::del(this->getData());
    renew();
}

void ItemsWindow::on_btnChange_clicked()
{
    QString product_id = this->data.table->item(this->data.table->currentRow(),0)->text();
    RequestStruct response = twActions::request(this->data.dbconn,
            QString("delete from product_2_genre where product_id = " + product_id));

    QStringList genres = ui->leGenres->text().split(",");
    for(int i=0;i<genres.size();i++){
        response = twActions::request(this->data.dbconn,
                                      QString("select genre_id from genres where genre_name = '" +
                                              genres[i] + "'"));
        response.query.next();

        QString genre_id = response.query.value("genre_id").toString();
        twActions::request(this->data.dbconn,
                                              QString("insert into product_2_genre (product_id, genre_id) values(" +
                                                      product_id + ", " + genre_id + ")"));
    }
    twActions::edit(this->getData());
    renew();
}
