#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <database.h>


#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif

using namespace std;


void Database::createTable(char *tableName) {
    Table* table = new Table;
    table->name = tableName;
    table->columns = this->columnsNow;
    this->tables.insert(pair<string, Table>(table->name, *table));
    this->columnsNow.erase(columnsNow.begin(), columnsNow.end());
    cout << "create table " << table->name << " success!" << endl;
    cout << "now tables :" << tables.size() << endl;
}

void Database::addColumn(char *columnName, int columnType,  int size) {
    column* column1 = new column;
    column1->columnName = columnName;
    column1->columnType = columnType;
    column1->columnSize = size;
    this->columnsNow.push_back(*column1);
}

void Database::showTables() {
    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Tables", 20);

    tp.PrintHeader();
    for(auto db : this->tables){
        tp << db.first ;
    }
    tp.PrintFooter();
}

/**
 * 删除数据表
 * @param tableName
 */
void Database::droptable(char *tableName) {
    auto iter = this->tables.find(string(tableName));
    if (iter == tables.end()){
        cout  << "ERROR 1049 (42000): Unknown table '" << tableName << "'" << endl;
        return;
    }
    //delete(&(iter->second));
    tables.erase(iter);
    cout << "Table Dropped" << endl;
}

/**
 * 建立数据库
 * @param databaseName
 */
void DBDriver::createDatabase(char *databaseName) {
    Database* database = new Database;
    database->name = databaseName;
    this->databases.insert(pair<string, Database>(database->name, *database));
    cout << "create database " << databaseName << " success." << endl;
}

/**
 * 选定数据库
 * @param databaseName
 */
void DBDriver::useDB(char *databaseName) {
    auto iter = databases.find(string(databaseName));
    if (iter == databases.end()){
        cout  << "ERROR 1049 (42000): Unknown database '" << databaseName << "'" << endl;
        return;
    }
    this->databaseInUse = &(iter->second);
    cout << "Database changed" << endl;
}

/**
 * 获取选定的数据库
 * @return
 */
Database * DBDriver::getDB() {
    return this->databaseInUse;
}

/**
 * 显示当前所有数据库
 */
void DBDriver::showDatabases() {

    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Database", 20);

    tp.PrintHeader();
    for(auto db : this->databases){
        tp << db.first ;
    }
    tp.PrintFooter();
}

/**
 * 删除数据库
 * @param databaseName
 */
void DBDriver::dropDatabase(char *databaseName) {
    auto iter = databases.find(string(databaseName));
    if (iter == databases.end()){
        cout  << "ERROR 1049 (42000): Unknown database '" << databaseName << "'" << endl;
        return;
    }
    //delete(&(iter->second));
    databases.erase(iter);
    cout << "Database Dropped" << endl;
}


