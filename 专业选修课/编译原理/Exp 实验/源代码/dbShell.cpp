//
// Created by 93773 on 2019/5/14.
//

#include <dbShell.h>
#include <bprinter/table_printer.h>

#include "dbShell.h"
#include "dbCore.h"
#include <cstring>

void dbShell::CreateDatabase(char * DatabaseName) {
    if (core.createDatabase(DatabaseName)){
        std::cout << "Create Database '" << DatabaseName << "' Success" << endl;
    }else {
        std::cout << "Create Database '" << DatabaseName << "' Error" << endl;
    }
}

void dbShell::ShowDatabases() {
    auto result = core.getDatabases();
    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Database", 20);

    tp.PrintHeader();
    for(auto db : result){
        tp << db ;
    }
    tp.PrintFooter();
    cout << result.size() << " rows in set" << endl;
}

void dbShell::CreateTable(char *tableName, table_field_node *tfn) {
    _strupr_s(tableName, strlen(tableName)+1);
    if(core.createTable(tableName, tfn)){
        std::cout << "Create Table '" << tableName << "' Success" << endl;
    }else{
        std::cout << "Create Table '" << tableName << "' Failed" << endl;
    }
}

void dbShell::UseDatabase(char *DatabaseName) {
    if(core.useDatabase(DatabaseName)){
        cout << "Database Changed " << endl;
    }
}

void dbShell::ShowTables() {
    auto tables =  core.getTables();
    bprinter::TablePrinter tp(&std::cout);
    string head = "Tables_in_";
    head += core.InUseDBName;
    tp.AddColumn(head, 20);

    tp.PrintHeader();
    for(auto t : tables){
        tp << t.tableName ;
    }
    tp.PrintFooter();
    cout << tables.size() << " rows in set" << endl;
}

void dbShell::DropDatabases(char *DatabaseName) {
    if(core.deleteDatabase(DatabaseName)){
        cout << "Delete Database '" << DatabaseName << "' Success" << endl;
    }
}

void dbShell::sqlInsert(insert_node *insertNode) {
    _strupr_s(insertNode->table->tableName, strlen(insertNode->table->tableName)+1);
    cout << insertNode->table->tableName << endl;
    if(core.insert(insertNode)){
        cout << "Query OK, " << 1 << "row affected" << endl;
    }
}

void dbShell::select(select_node * selectNode) {
    auto table = selectNode->table;
    while (table){
        _strupr_s(table->tableName, strlen(table->tableName)+1);
        table = table->next;
    }

    auto rs = core.select_mult(selectNode);
    vector<int> max_len(rs.first.size(), 5);
    for (auto s : rs.second) {
        for (int i =0; i< s.size(); i++) {
            if (s[i].type == values_node::INT)
                max_len[i] = 5;
            else
                if (max_len[i] < strlen(s[i].chval)){
                    max_len[i] = static_cast<int>(strlen(s[i].chval));
                }
        }
    }
    bprinter::TablePrinter tp(&std::cout);
    for  (int i =0 ; i <rs.first.size(); i++){
        tp.AddColumn(rs.first[i].field_name, max_len[i]);
    }
    tp.PrintHeader();
    for(auto s: rs.second){
        for (auto ss : s) {
            if (ss.type == values_node::INT)
                tp<< ss.intval;
            else
                tp<< ss.chval;
        }
    }
    tp.PrintFooter();
    cout << rs.second.size() << " rows in set" << endl;
}

void dbShell::sqldelete(select_node *selectNode) {
    auto table = selectNode->table;
    while (table){
        _strupr_s(table->tableName, strlen(table->tableName)+1);
        table = table->next;
    }
    int num = core.sqldelete(selectNode);
    cout << "Query OK, " << num << "rows affected" << endl;
}

void dbShell::sqlupdate(update_node *updateNode) {
    auto table = updateNode->table;
    while (table){
        _strupr_s(table->tableName, strlen(table->tableName)+1);
        table = table->next;
    }
    int num = core.sqlupdate(updateNode);
    cout << "Query OK, " << num << "rows affected" << endl;
}

void dbShell::dropTable(char *tableName) {
    _strupr_s(tableName, strlen(tableName)+1);

    if(core.deleteTable(tableName)){
        cout << "Drop Table Success" << endl;
    }else{
        cout << "Drop Table Failed" << endl;
    }
}

dbShell::dbShell() {
    cout << "Welcome to the CPDatabase monitor.  Commands end with ;\n"
            "Made by SincereXIA 16030199025@XDU. Compilation principle homework\n"
            "Database shell init successfully!" << endl;
}

dbShell::~dbShell() {
    cout << "bye" << endl;
}
