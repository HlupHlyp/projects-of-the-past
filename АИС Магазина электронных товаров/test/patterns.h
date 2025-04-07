#ifndef PATTERNS_H
#define PATTERNS_H

#include<QString>
#include<QTableWidgetItem>
#include <QMessageBox>
#include <QSqlError>
#include <QPixmap>
#include <QFile>

class patterns
{
public:
    patterns();
    static QString searchString(QString table, QString searchVals[], QString searchArgs[], int numArgs);
    static QString deleteString(QString table, QString id_column, QString id);
    static QString addString(QString table, QString addArgs[], QString addVals[], int numArgs);
    static QString editString(QString table, QString editArgs[], QString editVals[],
                       int numArgs, QString id_column, QString id);
    static void setPicture(QTableWidget* table, int row, int column, int margin, QString imgLink);
};

#endif // PATTERNS_H
