//
// Created by 93773 on 2019/5/14.
//

#ifndef MYSQL_DBSHELL_H
#define MYSQL_DBSHELL_H

#include <dbCore.h>


class dbShell {
public:
    void CreateDatabase(char * DatabaseName);
    void ShowDatabases();
    void ShowTables();
    void dropTable(char * tableName);
    void DropDatabases(char * DatabaseName);
    void UseDatabase(char * DatabaseName);
    void CreateTable(char * tableName, table_field_node * tfn);

    void sqlInsert(insert_node * insertNode);
    void select(select_node * selectNode);

    void sqldelete(select_node * selectNode);
    void sqlupdate(update_node * updateNode);
    dbShell();
    ~dbShell();

private:
    Core core;
};


#endif //MYSQL_DBSHELL_H
