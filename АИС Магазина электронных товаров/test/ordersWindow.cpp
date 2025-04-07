#include "ordersWindow.h"
#include "ui_orderswindow.h"
#include "QTextStream"
QTextStream cout1(stdout);

OrdersWindow::OrdersWindow(QSqlDatabase *dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdersWindow)
{
    this->dbconn = dbconn;
    ui->setupUi(this);
    SCDProducts();
    productsRenew();
    this->firstGen = false;
    SCDBuyers();
    buyersRenew();
    SCDOrders();
    ordersRenew();
    SCDOrderComposition();
    orderCompositionRenew();
    buyersWindow = new BuyersWindow(dbconn);
    connect(buyersWindow, &BuyersWindow::prevWindow, this, &OrdersWindow::show);
    LoadCmbs();
}

OrdersWindow::~OrdersWindow()
{
    delete ui;
}

void OrdersWindow::on_btnBack_2_clicked()
{
    this->close();
    // Закрываем окно
    emit prevWindow();
}

void OrdersWindow::SCDProducts() // SCD - Set Constant Data
{
    this->products.dbconn = dbconn;
    this->products.table = ui->twItems;
    this->products.tableName = QString("products");
    this->products.numColumns = 6;
    this->products.numArgs= 6;
    this->products.numSearchArgs = 2;

    QString cols[] = {QString("ID"), QString("Наименование"), QString("Тип"), QString("Расположение иконки"),
                      QString("Расположение файла"), QString("Стоимость")};
    for(int i=0;i<products.numColumns;i++) products.columns[i] = cols[i];

    int colSizes[] = {30, 240, 120, 210, 240, 90};
    for(int i=0;i<products.numColumns;i++) products.columnSizes[i] = colSizes[i];

    QString args[] = {QString("product_id"), QString("pr_name"), QString("pr_type"),
                      QString("image_adress"), QString("pr_link"), QString("pr_cost")};
    for(int i=0;i<products.numArgs;i++) products.args[i] = args[i];

    QString searchArgs[] = {QString("pr_type"), QString("pr_name")};
    for(int i=0;i<products.numSearchArgs;i++) products.searchArgs[i] = searchArgs[i];

}

void OrdersWindow::SCDOrders() // SCD - Set Constant Data
{
    orders.dbconn = dbconn;
    orders.table = ui->twOrders;
    orders.tableName = QString("orders");
    orders.numColumns = 5;
    orders.numArgs= 5;
    orders.numSearchArgs = 2;
    orders.numAddArgs = 4;

    QString cols[] = {QString("ID"), QString("Оплата"), QString("Дата заказа"),
                      QString("Отправка"), QString("ID покупателя")};
    for(int i=0;i<orders.numColumns;i++) orders.columns[i] = cols[i];

    int colSizes[] = {30, 60, 120, 60, 30};
    for(int i=0;i<orders.numColumns;i++) orders.columnSizes[i] = colSizes[i];

    QString args[] = {QString("order_id"), QString("payment"), QString("order_date"),
                      QString("sending"), QString("buyer_id")};
    for(int i=0;i<orders.numArgs;i++) orders.args[i] = args[i];

    QString searchArgs[] = {QString("payment"),
                            QString("sending")};
    for(int i=0;i<orders.numSearchArgs;i++) orders.searchArgs[i] = searchArgs[i];

    QString addArgs[] = {QString("payment"), QString("order_date"),
                         QString("sending"), QString("buyer_id")};
    for(int i=0;i<orders.numAddArgs;i++) orders.addArgs[i] = addArgs[i];
}

void OrdersWindow::SCDBuyers() // SCD - Set Constant Data
{
    this->buyers.dbconn = dbconn;
    this->buyers.table = ui->twBuyers;
    this->buyers.tableName = QString("buyers");
    this->buyers.numColumns = 6;
    this->buyers.numArgs= 6;
    this->buyers.numSearchArgs = 1;

    QString cols[] = {QString("ID"), QString("Фамилия"), QString("Имя"),
                      QString("Отчество"), QString("Email"), QString("Телефон")};
    for(int i=0;i<buyers.numColumns;i++) buyers.columns[i] = cols[i];

    int colSizes[] = {30, 120, 120, 150, 220, 150};
    for(int i=0;i<buyers.numColumns;i++) buyers.columnSizes[i] = colSizes[i];

    QString args[] = {QString("buyer_id"), QString("last_name"), QString("first_name"),
                      QString("patronymic"), QString("email"), QString("phone")};
    for(int i=0;i<buyers.numArgs;i++) buyers.args[i] = args[i];

    QString searchArgs[] = {QString("email")};
    for(int i=0;i<buyers.numSearchArgs;i++) buyers.searchArgs[i] = searchArgs[i];

}

void OrdersWindow::SCDOrderComposition() // SCD - Set Constant Data
{
    this->composition.dbconn = dbconn;
    this->composition.table = ui->twComposition;
    this->composition.tableName = QString("order_2_product");
    this->composition.numColumns = 3;
    this->composition.numArgs= 3;

    QString cols[] = {QString("ID"), QString("Наименование"), QString("Стоимость")};
    for(int i=0;i<composition.numColumns;i++) composition.columns[i] = cols[i];

    int colSizes[] = {30, 240, 120};
    for(int i=0;i<composition.numColumns;i++) composition.columnSizes[i] = colSizes[i];

    QString args[] = {QString("product_id"), QString("pr_name"), QString("pr_cost")};
    for(int i=0;i<composition.numArgs;i++) composition.args[i] = args[i];
}

TableData OrdersWindow::GDProducts() // GD - GET DATA
{
    QString searchVals[] = {ui->cmbPrTypeSearch->currentText(), ui->lePrNameSearch->text()};
    for(int i=0;i<products.numSearchArgs;i++) products.searchVals[i] = searchVals[i];
    return products;
}

TableData OrdersWindow::GDOrders() // GD - GET DATA
{
    QString vals[]={ui->cmbPaySearch->currentText(), ui->cmbSendSearch->currentText()};
    for(int i=0;i<orders.numSearchArgs;i++){
        if(vals[i] == "Да") orders.searchVals[i] = "true";
        else if (vals[i] == "Нет") orders.searchVals[i] = "false";
        else orders.searchVals[i] = "";
    }

    QString pay, send;
    if(ui->cbPayment->isChecked())
        pay = "true";
    else
        pay = "false";
    if(ui->cbSending->isChecked())
        send = "true";
    else
        send = "false";
    if(ui->twBuyers->currentRow() != -1){
        QString addVals[] = {pay, QString("'" + Date2String(ui->deOrderDate->date()) + "'"),
                           send, ui->twBuyers->item(ui->twBuyers->currentRow(), 0)->text()};

        for(int i=0;i<orders.numAddArgs;i++)
            orders.addVals[i] = addVals[i];
    }
    return orders;
}

TableData OrdersWindow::GDBuyers() // GD - GET DATA
{
    QString searchVals[] = {QString(ui->leEmailSearch->text())};

    for(int i=0;i<this->buyers.numSearchArgs;i++) this->buyers.searchVals[i] = searchVals[i];
    return buyers;
}


void OrdersWindow::buyersRenew() // GD - GET DATA
{
    twActions::markUp(buyers);
    twActions::search(GDBuyers());
}

void OrdersWindow::orderCompositionRenew() // GD - GET DATA
{
    twActions::markUp(composition);
    if(ui->twOrders->currentRow() != -1){
        RequestStruct items = twActions::request(orders.dbconn, QString("select products.product_id, pr_name, pr_cost "
                                                                        "from order_2_product inner join products "
                                                                        "on products.product_id = order_2_product.product_id "
                                                                        "where order_id = "
                                                                        + ui->twOrders->item(ui->twOrders->currentRow(),0)->text()));
        twActions::load(composition, items);
    }
}

void OrdersWindow::ordersRenew() // GD - GET DATA
{
    twActions::markUp(orders);
    twActions::search(GDOrders());
    orders.table->setColumnHidden(4, true);
    int rowCount = orders.table->rowCount();
    for(int i=0;i<rowCount;i++){
        if(orders.table->item(i,1)->text() == "true")
            orders.table->setItem(i,1,new QTableWidgetItem("✓"));
        else orders.table->setItem(i,1,new QTableWidgetItem("✗"));
        if(orders.table->item(i,3)->text() == "true")
            orders.table->setItem(i,3,new QTableWidgetItem("✓"));
        else orders.table->setItem(i,3,new QTableWidgetItem("✗"));
    }
    ui->deOrderDate->setDate(QDate::currentDate());
}

void OrdersWindow::productsRenew(){
    twActions::markUp(products);
    twActions::search(GDProducts());
    int colNum = products.numColumns;
    colNum++;
    twActions::externalColumn(&(products), colNum, "Жанр", 210);

    int rowCount = products.table->rowCount();
    if(rowCount != 0){

        for(int i=0;i<rowCount;i++){
            QString pr_id = products.table->item(i,0)->text();
            RequestStruct response = twActions::request(products.dbconn, QString("select genre_name from genres inner join product_2_genre "
                                                                                   "on genres.genre_id=product_2_genre.genre_id "
                                                                                   "inner join products "
                                                                                   "on products.product_id=product_2_genre.product_id "
                                                                                   "where products.product_id = " + pr_id));
            QString genre_set = "";
            while(response.query.next())
                    genre_set = genre_set + response.query.value("genre_name").toString() + ",";

            genre_set.chop(1);
            (*products.table).setItem(i,colNum-1,new QTableWidgetItem(genre_set));
        }
        colNum++;
        twActions::externalColumn(&(products), colNum, "Изображение", 100);

        for(int i=0;i<rowCount;i++){
            (*products.table).setItem(i,colNum-1,new QTableWidgetItem(""));
            patterns::setPicture(products.table, i, colNum-1, 10, products.table->item(i,3)->text());
        }

        products.table->setColumnHidden(3, true);
        products.table->setColumnHidden(4, true);
    }
}

void OrdersWindow::LoadCmbs(){
    RequestStruct response;
    QMessageBox message;
    response = twActions::request(this->products.dbconn, QString("select * from types"));

    ui->cmbPrTypeSearch->addItem("");

    while(response.query.next())
    {
            QString item = response.query.value("type_name").toString();
            ui->cmbPrTypeSearch->addItem(item);
    }

    response = twActions::request(products.dbconn, QString("select genre_name from genres"));

    ui->cmbPrGenreSearch->addItem("");

    while(response.query.next())
    {
            QString item = response.query.value("genre_name").toString();
            ui->cmbPrGenreSearch->addItem(item);
    }
    this->firstGen = false;

    QString tripleChoice[] = {QString(""), QString("Да"), QString("Нет")};
    for(int i=0;i<3;i++){
        ui->cmbSendSearch->addItem(tripleChoice[i]);
        ui->cmbPaySearch->addItem(tripleChoice[i]);
    }
    ui->deRightDateSearch->setDate(QDate::currentDate());
    ui->deOrderDate->setDate(QDate::currentDate());
}

void OrdersWindow::on_cmbPrTypeSearch_currentTextChanged(const QString &arg1)
{
    productsRenew();
}

void OrdersWindow::on_cmbPrGenreSearch_currentTextChanged(const QString &arg1)
{
    productsRenew();
    if(!this->firstGen){
        bool outerFlag = true;
        int outerNumRows = products.table->rowCount();
        while(outerFlag){
            bool innerFlag = true;
            int innerNumRows = products.table->rowCount();
            int i = 0;
            while(innerFlag && i<innerNumRows){
                QString rowGenre = QString(products.table->item(i,6)->text());
                if(!rowGenre.contains(ui->cmbPrGenreSearch->currentText())){
                    products.table->removeRow(i);
                    innerFlag = false;
                }
                i++;
            }
            if(i == innerNumRows)
                outerFlag = false;
        }
    }
}

void OrdersWindow::on_lePrNameSearch_textChanged(const QString &arg1)
{
    productsRenew();
}

void OrdersWindow::on_leEmailSearch_textChanged(const QString &arg1)
{
    buyersRenew();
}

void OrdersWindow::on_cmbPaySearch_currentTextChanged(const QString &arg1)
{
    on_deLeftDateSearch_userDateChanged(ui->deLeftDateSearch->date());
}

void OrdersWindow::on_cmbSendSearch_currentTextChanged(const QString &arg1)
{
    on_deLeftDateSearch_userDateChanged(ui->deLeftDateSearch->date());
}

QDate OrdersWindow::String2Date(QString date){
    QStringList parameters = date.split("-");
    QDate result = QDate(parameters[0].toInt(), parameters[1].toInt(), parameters[2].toInt());
    return result;
}
QString OrdersWindow::Date2String(QDate date){
    return date.toString("yyyy-MM-dd");
}

void OrdersWindow::on_deLeftDateSearch_userDateChanged(const QDate &date)
{
    ordersRenew();
    if(!this->firstGen){
        bool outerFlag = true;
        int outerNumRows = orders.table->rowCount();
        while(outerFlag){
            bool innerFlag = true;
            int innerNumRows = orders.table->rowCount();
            int i = 0;
            while(innerFlag && i<innerNumRows){
                QDate rowDate = String2Date(orders.table->item(i,2)->text());
                if(!(rowDate>=date && rowDate<=ui->deRightDateSearch->date())){
                    orders.table->removeRow(i);
                    innerFlag = false;
                }
                i++;
            }
            if(i == innerNumRows)
                outerFlag = false;
        }
    }
}

void OrdersWindow::on_deRightDateSearch_userDateChanged(const QDate &date)
{
    on_deLeftDateSearch_userDateChanged(ui->deLeftDateSearch->date());
}

void OrdersWindow::on_twOrders_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    orderCompositionRenew();
    QString buyer_id = ui->twOrders->item(ui->twOrders->currentRow(),4)->text();
    for(int i=0;i<ui->twBuyers->rowCount();i++){
        if(ui->twBuyers->item(i,0)->text() == buyer_id){
            ui->twBuyers->setCurrentCell(i,0);
            break;
        }
    }

    ui->deOrderDate->setDate(String2Date(ui->twOrders->item(ui->twOrders->currentRow(),2)->text()));

    if(ui->twOrders->item(ui->twOrders->currentRow(),1)->text() == "✓")
        ui->cbPayment->setChecked(true);
    else
        ui->cbPayment->setChecked(false);

    if(ui->twOrders->item(ui->twOrders->currentRow(),3)->text() == "✓")
        ui->cbSending->setChecked(true);
    else
        ui->cbSending->setChecked(false);
}

void OrdersWindow::on_twItems_itemDoubleClicked(QTableWidgetItem *item)
{
    if(ui->twOrders->currentRow() != -1)
    twActions::request(composition.dbconn, QString("insert into order_2_product(product_id, order_id) values(" +
                                                  ui->twItems->item(ui->twItems->currentRow(), 0)->text() + "," +
                                                   ui->twOrders->item(ui->twOrders->currentRow(), 0)->text() + ")"));
    orderCompositionRenew();
}

void OrdersWindow::on_twComposition_itemDoubleClicked(QTableWidgetItem *item)
{
    if(ui->twOrders->currentRow() != -1)
    twActions::request(composition.dbconn, QString("delete from order_2_product where product_id = " +
                                                  ui->twComposition->item(ui->twComposition->currentRow(), 0)->text() + " and order_id = " +
                                                   ui->twOrders->item(ui->twOrders->currentRow(), 0)->text()));
    orderCompositionRenew();
}

void OrdersWindow::on_twBuyers_itemDoubleClicked(QTableWidgetItem *item)
{
    if(ui->twOrders->currentRow() != -1){
        if(QMessageBox::question(this,"Внесение изменений","Изменить заказчика?",
         QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Ok){
            twActions::request(orders.dbconn, QString("update orders set buyer_id = " +
                                                      ui->twBuyers->item(ui->twBuyers->currentRow(), 0)->text() +
                                                      " where order_id = " +
                                                      ui->twOrders->item(ui->twOrders->currentRow(), 0)->text()));
            ordersRenew();
            QMessageBox msg;
            msg.setText("Изменения внесены");
            msg.exec();
        }
    }
}

void OrdersWindow::on_btnAdd_3_clicked()
{
    if(ui->twBuyers->currentRow() != -1){
        twActions::add(GDOrders());
        ordersRenew();
    }
    else{
        QMessageBox msg;
        msg.setText("Выберите пользователя и повторите попытку");
        msg.exec();
    }
    ui->twOrders->setCurrentCell(ui->twOrders->rowCount()-1,0);
}

void OrdersWindow::on_btnDelete_clicked()
{
    QString order_id = ui->twOrders->item(ui->twOrders->currentRow(),0)->text();
    twActions::request(orders.dbconn, QString("delete from order_2_product where order_id = " + order_id));
    twActions::request(orders.dbconn, QString("delete from orders where order_id = " + order_id));
    ordersRenew();
}

void OrdersWindow::on_btnChange_clicked()
{
    twActions::edit(GDOrders());
    ordersRenew();
}

void OrdersWindow::on_btnAdd_4_clicked()
{
    buyersWindow->show();
    this->close();
}
