#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextStream"
QTextStream cout(stdout);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!dbconn.isOpen())
    {
        QSqlDatabase::drivers().join(",");
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        dbconn.setDatabaseName("electronic_goods_store");
        dbconn.setHostName("localhost");
        dbconn.setUserName("student");
        dbconn.setPassword("1");
    }
    if(!dbconn.open())
    {
        QMessageBox::critical(this,"Error","Database isn't connected");
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select user_class from users";
    if( !query.exec(sqlstr) )
    {
        cout<<"Error:"<<query.lastError().text()<<"/n";
        //QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    while(query.next())
        ui->cmbRoles->addItem(query.value("user_class").toString());

    menuWindow = new AdminWindow(&dbconn);
    connect(menuWindow, &AdminWindow::prevWindow, this, &MainWindow::show);
    ordersWindow = new OrdersWindow(&dbconn);
    connect(ordersWindow, &OrdersWindow::prevWindow, this, &MainWindow::show);
    cout<<"Auth Say Hi!"<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnter_4_clicked()
{
    RequestStruct response = twActions::request(&dbconn, QString("select * from users where user_class = '"
                                       +  ui->cmbRoles->currentText() + "'"));
    response.query.next();
    if(response.query.value("class_password") == ui->lePassword->text()){
        if(ui->cmbRoles->currentText() == "Мэнеджер")
                ordersWindow->show();
        else if(ui->cmbRoles->currentText() == "Администратор") menuWindow->show();
        this->close();
    }
    else{
        QMessageBox msg;
        msg.setText("Пароль неверен");
        msg.exec();
    }
    /*if(ui->cmbRoles->currentText() == "Мэнеджер")
        ordersWindow->show();
    else if(ui->cmbRoles->currentText() == "Администратор") menuWindow->show();
    this->close();    // Закрываем основное окно*/
}

void MainWindow::on_btnExit_5_clicked()
{
    this->close();
}

