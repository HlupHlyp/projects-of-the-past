#include "twactions.h"

twActions::twActions()
{

}

void twActions::markUp(TableData data){
    (*data.table).setColumnCount(data.numColumns);
    (*data.table).setAutoScroll(true);
    (*data.table).setSelectionMode(QAbstractItemView::SingleSelection);
    (*data.table).setSelectionBehavior(QAbstractItemView::SelectRows);
    for(int i=0;i<data.numColumns;i++){
        (*data.table).setHorizontalHeaderItem(i,new QTableWidgetItem(data.columns[i]));
        (*data.table).horizontalHeader()->resizeSection(i, data.columnSizes[i]);
    }
    (*data.table).horizontalHeader()->setStretchLastSection(true);
    (*data.table).setSortingEnabled(true);
    (*data.table).sortByColumn(0);
    (*data.table).setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void twActions::add(TableData data){
    request(data.dbconn, patterns::addString(data.tableName, data.addArgs, data.addVals, data.numAddArgs));
    renew(data);
}

void twActions::search(TableData data){
    load(data, request(data.dbconn, patterns::searchString(data.tableName, data.searchArgs, data.searchVals, data.numSearchArgs)));
}

void twActions::del(TableData data){
    request(data.dbconn, patterns::deleteString(data.tableName, data.args[0],
            (*data.table).item((*data.table).currentRow(),0)->text()));
    renew(data);
}

void twActions::edit(TableData data){
    request(data.dbconn, patterns::editString(data.tableName, data.addArgs, data.addVals, data.numAddArgs, data.args[0],
            (*data.table).item((*data.table).currentRow(),0)->text()));

}

void twActions::load(TableData data, RequestStruct response){

    //(*data.table).clearContents();
    if( response.query.isActive()) (*data.table).setRowCount(response.query.size());
    else
    (*data.table).setRowCount(0);
    int i=0;
    while(response.query.next())
    {
        for(int j=0;j<data.numColumns;j++){
            (*data.table).setItem(i,j,new QTableWidgetItem(response.query.value(data.args[j]).toString()));
        }
        i++;
    }

}

void twActions::renew(TableData data){
    load(data, request(data.dbconn, QString("select * from " + data.tableName)));
}

RequestStruct twActions::request(QSqlDatabase *dbconn, QString request_text)
{
    RequestStruct res{false, QSqlQuery ((*dbconn))};
    if( !(*dbconn).isOpen() )
    {
        QMessageBox msgBox;
        msgBox.setText((*dbconn).lastError().text());
        msgBox.setInformativeText("Database connection error");
        msgBox.exec();
        return res;
    }

     if( !res.query.exec(request_text) )
     {
         QMessageBox msgBox;
         msgBox.setText(res.query.lastError().text());
         msgBox.setInformativeText("Query error");
         msgBox.exec();
         return res;
     }

     res.condition = true;
     return res;
}

void twActions::externalColumn(TableData* data, int num, QString name, int size){
    (*data).table->setColumnCount(num);
    (*data).table->setHorizontalHeaderItem(num-1,new QTableWidgetItem(name));
    (*data).table->horizontalHeader()->resizeSection(num-1, size);
}
