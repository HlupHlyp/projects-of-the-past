#ifndef TWACTIONS_H
#define TWACTIONS_H

#include<QTableWidget>
#include <QHeaderView>
#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <patterns.h>


const int MAX_SIZE = 10;

struct RequestStruct
{
    bool condition;
    QSqlQuery query;
};

struct TableData
{
    QSqlDatabase *dbconn;

    QTableWidget *table;
    QString tableName;

    int numColumns;
    int numArgs;
    int numSearchArgs;
    int numAddArgs;

    int columnSizes[MAX_SIZE];

    QString columns[MAX_SIZE];
    QString args[MAX_SIZE];
    QString searchArgs[MAX_SIZE];
    QString addArgs[MAX_SIZE];
    QString searchVals[MAX_SIZE];
    QString addVals[MAX_SIZE];

};

class twActions
{
public:
    twActions();
    static void markUp(TableData data);
    static void renew(TableData data);
    static RequestStruct request(QSqlDatabase *dbconn, QString request_text);
    static void add(TableData data);
    static void load(TableData data, RequestStruct response);
    static void del(TableData data);
    static void search(TableData data);
    static void edit(TableData data);
    static void externalColumn(TableData* data, int num, QString name, int size);
};

#endif // TWACTIONS_H
