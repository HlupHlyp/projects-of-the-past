#include "patterns.h"

patterns::patterns()
{

}

QString patterns::searchString(QString table, QString searchArgs[], QString searchVals[], int numArgs)
{
    QString str = QString("select * from " + table);
    bool f = false;
    for(int i=0; i<numArgs; i++){
        if(searchVals[i] != "" && f == false){
            str = str + QString(" where cast(" + searchArgs[i] + " as text) like '%"
                                + searchVals[i] + "%'");
            f = true;
        }
        else if(searchVals[i] != "")
            str = str + QString(" and cast(" + searchArgs[i] + " as text) like '%"
                                + searchVals[i] + "%'");
    }
    return str;
}

QString patterns::deleteString(QString table, QString id_column, QString id)
{
    return QString("delete from " + table + " where " + id_column + " = " + id);
}

QString patterns::addString(QString table, QString addArgs[], QString addVals[], int numArgs)
{
    QString str = QString("insert into " + table + " (");
    for(int i=0;i<numArgs; i++){
        if(i != numArgs - 1)
            str = QString(str + addArgs[i] + ", ");
        else
            str = QString(str + addArgs[i] + ") values(");
    }

    for(int i=0;i<numArgs; i++){
        if(i != numArgs - 1)
            str = QString(str + addVals[i] + ", ");
        else
            str = QString(str + addVals[i] + ")");
    }
    return str;
}

QString patterns::editString(QString table, QString editArgs[], QString editVals[],
                             int numArgs, QString id_column, QString id)
{
    QString str = QString("update " + table + " set " );

    for(int i=0;i<numArgs; i++){
        if(i != numArgs - 1)
            str = QString(str + editArgs[i] + " = " + editVals[i] + ", ");
        else
            str = QString(str + editArgs[i] + " = " + editVals[i] + " where ");
    }

    return QString(str + id_column + " = " + id);
}

void patterns::setPicture(QTableWidget* table, int row, int column, int margin, QString imgLink){
    QMessageBox msgBox;

    QFile imgFile(imgLink);
    if(!imgFile.exists()){
        msgBox.setInformativeText("Файл не найден");
        msgBox.exec();
    }

    if(!imgFile.open(QIODevice::ReadOnly)){
        msgBox.setInformativeText(imgFile.errorString());
        msgBox.exec();
    }

    QByteArray Image = imgFile.readAll();
    if(Image.isEmpty()){
        msgBox.setInformativeText("Байтовый массив не загружен");
        msgBox.exec();
    }

    QImage bitm;
    bitm.loadFromData(Image);//Convert to QImage
    QPixmap bmp;
    bmp = QPixmap::fromImage(bitm);//Convert to QPixmaps
    if(bmp.isNull()){
        msgBox.setInformativeText("Изображение не загружено");
        msgBox.exec();
    }

    (*table).item(row, column)->setData(Qt::DecorationRole, bmp);
    (*table).setRowHeight(row, bmp.height() + margin);
}

