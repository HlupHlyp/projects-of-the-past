#ifndef DBPAD_H
#define DBPAD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class dbpad
{
public:
    dbpad();
    ~dbpad();
    bool connect();
    void disconnect();
private:
    QSqlDatabase dbconn;
};

#endif // DBPAD_H
