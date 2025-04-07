#include "dbpad.h"

dbpad::dbpad()
{

}

dbpad::~dbpad()
{

}
bool dbpad::connect()
{
    if(!dbconn.isOpen())
    {
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        dbconn.setDatabaseName("electronic_goods_store");
        dbconn.setHostName("localhost");
        dbconn.setUserName("student");
        dbconn.setPassword("1");
        return dbconn.open();
    }
    return true;
}
void dbpad::disconnect()
{
    if(dbconn.isOpen())
    {
        dbconn.close();
    }
}
