//
// Created by 93773 on 2019/5/14.
//

#include "dbCore.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>


char *_S(const char *string) {
    return _strdup(string);
}

void Core::addPage(fstream &f) {
    f.seekp(0, ios::end);
    for (int i = 0; i < PAGE_SIZE; i++) {
        f.put('\0');
    }
    f.flush();
    f.clear();
}

int Core::createDatabase(const char *databaseName) {

    auto databasesNow = getDatabases();
    for (auto db : databasesNow) {
        if (strcmp(databaseName, db) == 0) {
            cout << "Error: database '" << databaseName << "' already exists" << endl;
            return 0;
        }
    }

    //临时
    if (InUsedb && (InUsedb!=sysdb)){
        InUsedb->close();
        InUsedat->close();
    }
    InUsedb = sysdb;
    InUsedat = sysdat;
    insert_node insetNode;
    auto val1 = new values_node;
    val1->type = values_node::STRING;
    val1->chval = _S(databaseName);
    auto val2 = new values_node;
    val2->type = values_node::STRING;
    char dbfileName[40] = {0};
    char datfileName[40] = {0};
    strcat_s(dbfileName, strlen(databaseName) + 1, databaseName);
    strcat_s(dbfileName, ".db");
    val2->chval = dbfileName;
    auto val3 = new values_node;
    val3->type = values_node::STRING;
    strcat_s(datfileName, strlen(databaseName) + 1, databaseName);
    strcat_s(datfileName, ".dat");
    val3->chval = datfileName;
    val1->next = val2;
    val2->next = val3;
    auto tbn = new table_node;
    tbn->tableName = _S("database");
    insetNode.table = tbn;
    insetNode.values = val1;
    this->insert(&insetNode);

    InUsedb = new fstream(dbfileName, ios::out | ios::binary);
    this->getNewDatPage(*InUsedb);
    this->getNewDatPage(*InUsedb);

    InUsedat = new fstream(datfileName, ios::out | ios::binary);

    useDatabase(databaseName);
    return 1;
}

int Core::useDatabase(const char *databaseName) {
    auto dbs = getDatabases();
    for (auto db : dbs){
        if(strcmp(db, databaseName) ==0){
            InUseDBName = _S(databaseName);
            // TODO: 更新 InUSE文件流
            char dbfileName[40] = {0};
            char datfileName[40] = {0};
            strcat_s(dbfileName, strlen(databaseName) + 1, databaseName);
            strcat_s(dbfileName, ".db");
            InUsedb->close();
            InUsedb->open(dbfileName, ios::out | ios::in | ios::binary);
            strcat_s(datfileName, strlen(databaseName) + 1, databaseName);
            strcat_s(datfileName, ".dat");
            InUsedat->close();
            InUsedat->open(datfileName, ios::out | ios::in | ios::binary);
            this->InUseDBName = _S(databaseName);
            return 1;
        }
    }
    return 0;
}

int Core::createTable(const char *tableName, table_field_node *tfn) {
    auto tablesNow = getTables();
    for (auto t : tablesNow) {
        if (strcmp(t.tableName, tableName) == 0) {
            cout << "Error: table '" << tableName << "' already exists" << endl;
            return 0;
        }
    }

    int PageNow = 0; //表字典
    for (int i = 0; i < 20; i++) {
        int offset = PageNow * PAGE_SIZE + i * 100;
        InUsedb->seekg(offset);
        if (InUsedb->peek() == '\0') {
            InUsedb->seekp(InUsedb->tellg());
            InUsedb->write(tableName, strlen(tableName) * sizeof(char));
            int page = getNewDatPage(*InUsedat);
            offset = offset + 100 - sizeof(int);
            InUsedb->seekp(offset);
            InUsedb->write((char *) &page, sizeof(int));;
            break;
        }
    }
    PageNow = getWriteablePageNum(*InUsedb, 1); // 列字典从 1 页开始存放

    int colNum = 0;
    int coloffset = 0;
    for (int i = 0; i < 20; i++) {
        std::streampos offset = PageNow * PAGE_SIZE + i * 100;
        InUsedb->seekg(offset);
        if (InUsedb->peek() == '\0' && tfn) {
            InUsedb->seekp(offset);
            InUsedb->write(tableName, strlen(tableName) * sizeof(char)); //写入数据库名
            offset += 40;
            InUsedb->seekp(offset);
            InUsedb->write((char *) &colNum, sizeof(int)); //写入列号
            offset += sizeof(int);
            InUsedb->seekp(offset);
            InUsedb->write(tfn->field_name, strlen(tfn->field_name)); // 写入列名
            offset += 40;
            InUsedb->seekp(offset);
            InUsedb->write((char *) &coloffset, sizeof(int)); //写入偏移
            offset += sizeof(int);
            InUsedb->seekp(offset);

            InUsedb->write((char *) &(tfn->len), sizeof(int)); //写入宽度

            coloffset += tfn->len == 0 ? sizeof(int) : tfn->len;
            tfn = tfn->next;
            colNum++;
        }
    }
    return 1;
}

/*
获取当前数据库中某个表所有的列
*/
vector<table_field_node> Core::getColumn(char *tableName) {
    vector<table_field_node> result;
    int PageNow = 1;
    readPage(*InUsedb, PageNow);
    for (int i = 0; i < 20; i++) {
        if (strcmp(tableName, DATPAGE + (i * 100)) == 0) {
            table_field_node node;
            node.field_name = _S(DATPAGE + (i * 100) + 44);
            node.offset = *(int *) (DATPAGE + (i * 100) + 84);
            node.len = *(int *) (DATPAGE + (i * 100) + 88);
            if (node.len == 0) {
                node.len = sizeof(int);
                node.type = table_field_node::INT;
            } else {
                node.type = table_field_node::STRING;
            }

            result.push_back(node);
        }
    }
    return result;
}

int Core::insert(insert_node *insertNode) {
    char *tableName = insertNode->table->tableName;
    auto cols = getColumn(tableName);
    vector<int> offsets;
    auto fieldNow = insertNode->field;

    if (fieldNow == nullptr) { //不指定 field 时， 按顺序插入
        for (auto c : cols) {
            offsets.push_back(c.offset);
        }
    }
    while (fieldNow) { // 指定 field 时， 获取每个值的偏移量
        bool find = false;
        for (auto c : cols) {
            if (strcmp(c.field_name, fieldNow->field_name) == 0) {
                find = true;
                offsets.push_back(c.offset);
                break;
            }
        }
        if (!find) {
            cout << "Error: there is no field '" << fieldNow->field_name << "' in table " << tableName << endl;
            return 0;
        }
        fieldNow = fieldNow->next;
    }

    int page = getTableStartDatPage(tableName); //获取起始页
    //获取每条记录的长度
    int Recordlength = cols.at(cols.size() - 1).offset + cols.at(cols.size() - 1).len;
    page = getWriteablePageNum(*InUsedat, page, Recordlength); //获取可插入页
    readPage(*InUsedat, page);

    int offset = 0;
    while (offset + Recordlength <= PAGE_SIZE - sizeof(int)) {
        if (DATPAGE[offset] == '\0') break;
        offset += Recordlength;
    }

    int i = 0; // 当前插入了第几个数据项
    auto data = insertNode->values;
    while (data) {
        // TODO : 属性检查
        if (data->type == values_node::STRING) {
            // TODO : 插入数据项超长后的异常处理
            strcpy_s(&(DATPAGE[offset + offsets[i]]), strlen(data->chval) + 1, data->chval);
        } else if (data->type == values_node::INT) {
            // TODO : 这里写的不对
            *(int *) (DATPAGE + offset + offsets[i]) = data->intval;
        }
        data = data->next;
        i++;
    }
    writePage(*InUsedat, page);
    return 1;
}

pair<vector<table_field_node>, vector<vector<values_node>>>
Core::select_single(select_node *selectNode) {
    char *tableName = selectNode->table->tableName;
    auto tableCols = getColumn(tableName);

    auto fieldrequest = selectNode->field;
    vector<table_field_node> head;
    vector<table_field_node> head_all;
    vector<vector<values_node>> body;
    while (fieldrequest) { //将请求 field 找到
        bool findField = false;
        if (strcmp(fieldrequest->field_name, "*") == 0) {
            findField = true;
            for (auto c : tableCols) {
                head.push_back(c);
                head_all.push_back(c);
            }
        } else {
            for (auto c : tableCols) {
                if (strcmp(c.field_name, fieldrequest->field_name) == 0) {
                    findField = true;
                    head.push_back(c);
                }
                head_all.push_back(c);
            }
        }
        if (!findField) cout << "Error: Field '" << fieldrequest->field_name << "can not find!" << endl;
        fieldrequest = fieldrequest->next;
    }

    auto datpageNum = getTableStartDatPage(tableName);
//获取每条记录的长度
    int Recordlength = tableCols.at(tableCols.size() - 1).offset + tableCols.at(tableCols.size() - 1).len;
    while (datpageNum != -1) {
        if (!readPage(*InUsedat, datpageNum)) {
            cout << "SELECT: readPage Error!" << endl;
        }
        int i = 0;
// TODO : 是否是最后一行的判定有问题
        while ((i+1) * Recordlength + sizeof(int) <= PAGE_SIZE){
            if (*(DATPAGE + i * Recordlength) != '\0') {
                vector<values_node> row;
                vector<values_node> row_all;
                for (auto h : head_all) { // 获取完整行
                    values_node node;
                    if (h.type == table_field_node::INT) { // int
                        node.intval = *(int *) (DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::INT;
                    } else { // string
                        node.chval = _S(DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::STRING;
                    }
                    row_all.push_back(node);
                }
                if (condVerify(head_all, row_all, selectNode->cons)){ //使用完整行进行筛选
                    for (auto h : head) { //筛选通过后生成目标行
                        values_node node;
                        if (h.type == table_field_node::INT) { // int
                            node.intval = *(int *) (DATPAGE + i * Recordlength + h.offset);
                            node.type = values_node::INT;
                        } else { // string
                            node.chval = _S(DATPAGE + i * Recordlength + h.offset);
                            node.type = values_node::STRING;
                        }
                        row.push_back(node);
                    }
                    body.push_back(row);
                }
            }
            i++;
        }
        datpageNum = getNextPageNum();
    }

    return pair<vector<table_field_node>, vector<vector<values_node>>>
            (head, body);
}


pair<vector<table_field_node>, vector<vector<values_node>>>
Core::select_mult(select_node *selectNode) {
    vector<table_node> tables;
    vector<table_field_node> head;
    auto table = selectNode->table;
    tables.push_back(*(selectNode->table));
    table = table->next;
    while (table) {
        tables.push_back(*table);
        table = table->next;
    }

    auto userField = selectNode->field;
    while (userField) {
        for (auto &t : tables) {
            auto cols = getColumn(t.tableName);
            for (auto c : cols) {
                if (strcmp(c.field_name, userField->field_name) == 0 ||
                    strcmp(userField->field_name, "*") == 0) {
                    auto *tfn = new table_field_node;
                    tfn->field_name = userField->field_name;
                    head.push_back(*tfn);
                    auto f = t.field;
                    if (!f) {
                        t.field = tfn;
                    } else {
                        while (f->next) {
                            f = f->next;
                        }
                        f->next = tfn;
                    }
                    break;
                }
            }
        }
        userField = userField->next;
    }

    vector<vector<vector<values_node> > > temp;
    vector<table_field_node> heads_New;
    for (auto &t : tables) {
        select_node sn;
        sn.table = &t;
        sn.cons = selectNode->cons;
        sn.field = t.field;
        auto res = select_single(&sn);
        temp.push_back(res.second);
        heads_New.insert(heads_New.end(), res.first.begin(), res.first.end());
    }
    vector<vector<values_node> > colsNow = temp[0];
    vector<vector<values_node> > colsNew;


    for (int i = 1; i < temp.size(); i++) {
        for (auto ac : temp[i]) {
            for (auto c : colsNow) {
                c.insert(c.end(), ac.begin(), ac.end());
                colsNew.push_back(c);
            }
        }
        colsNow = colsNew;
        colsNew.clear();
    }
    return pair<vector<table_field_node>, vector<vector<values_node>>>(
            heads_New, colsNow
    );
}


void Core::SysdbInit() {

}

vector<table_node> Core::getTables() {
    vector<table_node> result;
    int PageNow = 0; //表字典
    for (int i = 0; i < 20; i++) {
        int offset = PageNow * PAGE_SIZE + i * 100;
        InUsedb->seekg(offset);
        InUsedb->read((char *) TEMP, 100);
        if (((char *) TEMP)[0] == '\0') return result;
        auto *tn = new table_node;
        tn->tableName = _strdup((char *) TEMP);
        offset = offset + 100 - sizeof(int);
        int beginPage;
        InUsedb->seekg(offset);
        InUsedb->read((char *) &beginPage, sizeof(int));
        tn->beginPage = beginPage;
        result.push_back(*tn);
    }
    return result;
}

vector<char *> Core::getDatabases() {
    auto tempdb = this->InUsedb;
    auto tempdat = this->InUsedat;
    this->InUsedb = this->sysdb;
    this->InUsedat = this->sysdat;
    vector<char *> result;
    select_node snode;
    auto tfnode = new table_field_node;
    auto tnode = new table_node;
    tnode->tableName = _S("database");
    tfnode->field_name = _S("name");
    snode.table = tnode;
    snode.field = tfnode;
    auto selectrs = this->select_mult(&snode);
    for (auto s : selectrs.second) {
        result.push_back(s[0].chval);
    }
    this->InUsedb = tempdb;
    this->InUsedat = tempdat;
    return result;
}


int Core::getNewDatPage(fstream &datfile, int PageNow) {
    int offset = PageNow * PAGE_SIZE;
    datfile.seekg(0, ios::end);
    fpos<mbstate_t> fileSize = datfile.tellg();
    while (offset + PAGE_SIZE <= fileSize) {
        datfile.seekg(offset + PAGE_SIZE - sizeof(int));
        datfile.read((char *) TEMP, sizeof(int));
        if (TEMP[0] == 0) {
            datfile.seekp(offset + PAGE_SIZE - sizeof(int));
            TEMP[0] = -1;
            datfile.write((char *) TEMP, sizeof(int));
            return PageNow;
        } else {
            PageNow++;
        }
        offset = PageNow * PAGE_SIZE;
    }
    addPage(datfile);
    datfile.seekp(offset + PAGE_SIZE - sizeof(int));
    TEMP[0] = -1;
    datfile.write((char *) TEMP, sizeof(int));
    return PageNow;
}

int Core::getNextPageNum() {
    int offset = PAGE_SIZE - sizeof(int);
    return *(int *) (DATPAGE + offset);
}

int Core::readPage(fstream &filestream, int pageNum, char *page) {
    int offset = pageNum * PAGE_SIZE;
    filestream.seekg(0, ios::end);
    fpos<mbstate_t> fileSize = filestream.tellg();
    if (offset + PAGE_SIZE > fileSize) {  // 判断这一页是否存在
        cerr << "Core ERROR: Page Not Found!" << endl;
        return 0;
    }
    filestream.seekg(offset); //偏移
    filestream.read(page, PAGE_SIZE); // 读取到 DATPAGE
    return 1;
}

int Core::writePage(fstream &filestream, int pageNum, char *page) {
    int offset = pageNum * PAGE_SIZE;
    filestream.seekp(0, ios::end);
    fpos<mbstate_t> fileSize = filestream.tellp();
    if (offset + PAGE_SIZE > fileSize) {  // 判断这一页是否存在
        cerr << "Core ERROR: Page Not Found!" << endl;
        return 0;
    }
    filestream.seekp(offset); //偏移
    filestream.write(page, PAGE_SIZE); // 写入到文件
    return 1;
}

int Core::getWriteablePageNum(fstream &filestream, int pageNum) {
    char temp[PAGE_SIZE];
    int pageNow = pageNum;
    while (pageNow != -1) {
        readPage(filestream, pageNum, temp);
        pageNow = *(int *) (temp + PAGE_SIZE - sizeof(int));
        if (pageNow != -1) pageNum = pageNow;
    }
    return pageNum;
}

/*
获取一个可写入页
*/
int Core::getWriteablePageNum(fstream &filestream, int pageNum, int rowlen) {
    char temp[PAGE_SIZE];
    // 获取最后一页
    int lastPage = getWriteablePageNum(filestream, pageNum);
    // 判断是否被写满
    readPage(filestream, lastPage, temp);
    int offset = 0;
    while (offset + rowlen <= PAGE_SIZE - sizeof(int)) {
        if (temp[offset] == '\0') {
            return lastPage;
        }
        offset += rowlen;
    }
    // 写满后，添加一个新页，并修正当前页号
    int newPage = getNewDatPage(filestream, lastPage);
    *(int *) (temp + PAGE_SIZE - sizeof(int)) = newPage;
    writePage(filestream, lastPage, temp);
    return newPage;
}

int Core::getTableStartDatPage(char *tableName) {
    auto tables = getTables();
    for (auto table : tables) {
        if (strcmp(tableName, table.tableName) == 0) {
            return table.beginPage;
        }
    }
    return -1;
}


Core::Core() {
    bool needrebuild = false;
    sysdb = new fstream("sys.db", ios::out | ios::in | ios::binary);
    if (!sysdb) {
        cout << "error!" << endl;
    }
    if (sysdb->peek() == EOF) {
        needrebuild = true;
        sysdb->close();
        sysdb->open("sys.db", ios::out | ios::binary);
        sysdb->close();
        sysdb->open("sys.db", ios::out | ios::in | ios::binary);
        getNewDatPage(*sysdb);
        getNewDatPage(*sysdb);
    }
    sysdat = new fstream("sys.dat", ios::out | ios::in | ios::binary);
    if (!sysdat) {
        cout << "error!" << endl;
    }
    if (sysdat->peek() == EOF) {
        needrebuild = true;
        sysdat->close();
        sysdat->open("sys.dat", ios::out | ios::binary);
        sysdat->close();
        sysdat->open("sys.dat", ios::out | ios::in | ios::binary);
    }

    if (needrebuild) {
        cout << "Core Info: can not find 'sys.db' and 'sys.dat'. Rebuilding the basic database... " ;
        //临时
        InUsedb = sysdb;
        InUsedat = sysdat;
        char d[] = "database";
        char s[] = "security";
        auto dbNameNode = new table_field_node;
        dbNameNode->field_name = _S("name");
        dbNameNode->len = 50;
        auto dbFileNode = new table_field_node;
        dbFileNode->field_name = _S("dbfile");
        dbFileNode->len = 100;
        auto datFileNode = new table_field_node;
        datFileNode->field_name = _S("datfile");
        datFileNode->len = 100;
        dbNameNode->next = dbFileNode;
        dbFileNode->next = datFileNode;
        table_field_node secName;
        secName.field_name = _S("name");
        secName.len = 50;
        auto secdb = new table_field_node;
        secdb->field_name = _S("database");
        secdb->len = 50;
        secName.next = secdb;
        createTable(d, dbNameNode);
        createTable(s, &secName);

        insert_node insetNode;
        values_node val1;
        val1.type = values_node::STRING;
        val1.chval = _S("sys");
        auto val2 = new values_node;
        val2->type = values_node::STRING;
        val2->chval = _S("sys.db");
        auto val3 = new values_node;
        val3->type = values_node::STRING;
        val3->chval = _S("sys.dat");
        val1.next = val2;
        val2->next = val3;
        table_node tbn;
        tbn.tableName = _S("database");
        insetNode.table = &tbn;
        insetNode.values = &val1;
        this->insert(&insetNode);
        createDatabase("default");
        cout << "ok!" <<endl;
    }else {
        InUsedb = new fstream("default.db", ios::out | ios::in | ios::binary);
        InUsedat = new fstream("default.dat", ios::out | ios::in | ios::binary);
    }
}

Core::~Core() {
    sysdb->close();
    sysdat->close();
}

bool Core::condVerify(vector<table_field_node> head, vector<values_node> record, condexp_node *cond) {
    if (!cond) return true;
    if (cond->type == cond->LOGIC) {
        if (cond->op == condexp_node::AND) {
            return condVerify(head, record, cond->left) && condVerify(head, record, cond->right);
        } else if (cond->op == condexp_node::OR) {
            return condVerify(head, record, cond->left) || condVerify(head, record, cond->right);
        }
    } else {
        char *fieldName = cond->left->chval;
        string value;
        if (cond->right->type == condexp_node::STRING) {
            value = string(cond->right->chval);
        } else {
            value = to_string(cond->right->intval);
        }
        int intval = cond->right->intval;
        int i = 0;
        for (i = 0; i < head.size(); i++) {
            if (strcmp(fieldName, head[i].field_name) == 0) {
                if (head[i].type == head[i].INT) {
                    if (cond->op == condexp_node::EQ) {
                        return record[i].intval == intval;
                    } else if (cond->op == condexp_node::G) {
                        return record[i].intval > intval;
                    } else if (cond->op == condexp_node::B) {
                        return record[i].intval < intval;
                    }else if (cond->op == condexp_node::NOT) {
                        return record[i].intval != intval;
                    }
                } else if (head[i].type == head[i].STRING) {
                    string recstringval(record[i].chval);
                    if (cond->op == condexp_node::EQ) {
                        return recstringval == value;
                    } else if (cond->op == condexp_node::G) {
                        return recstringval > value;
                    } else if (cond->op == condexp_node::B) {
                        return recstringval < value;
                    }else if (cond->op == condexp_node::NOT) {
                        return recstringval != value;
                    }
                }
            }
        }
    }
    return true;
}

int Core::sqldelete(select_node *deleteNode) {
    int delNum = 0;
    // 获取要删除的表名
    char *tableName = deleteNode->table->tableName;
//    auto tables = getTables();
//    bool findflag = false;
//    for (auto t:tables){
//        if (strcmp(tableName, t.tableName)==0){
//            findflag = true;
//            break;
//        }
//    }
//    if (!findflag){
//        cout << "There is no table named: " << tableName << endl;
//        return 0;
//    }
    // 获取表的所有列属性
    auto tableCols = getColumn(tableName);
    vector<table_field_node> head = tableCols;

    auto datpageNum = getTableStartDatPage(tableName);
//获取每条记录的长度
    int Recordlength = tableCols.at(tableCols.size() - 1).offset + tableCols.at(tableCols.size() - 1).len;

    while (datpageNum != -1) {
        if (!readPage(*InUsedat, datpageNum)) {
            cout << "SELECT: readPage Error!" << endl;
        }
        int i = 0;
        while ((i+1) * Recordlength + sizeof(int) <= PAGE_SIZE){
            if (*(DATPAGE + i * Recordlength) != '\0') {
                vector<values_node> row;
                for (auto h : head) {
                    values_node node;
                    if (h.type == table_field_node::INT) { // int
                        node.intval = *(int *) (DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::INT;
                    } else { // string
                        node.chval = _S(DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::STRING;
                    }
                    row.push_back(node);
                }
                if (condVerify(head, row, deleteNode->cons)){ //将待删除的记录置0
                    memset(DATPAGE + i*Recordlength, '\0', static_cast<size_t>(Recordlength));
                    delNum++;
                }
            }
            i++;
        }
        writePage(*InUsedat, datpageNum);
        datpageNum = getNextPageNum();
    }
    return delNum;
}

int Core::deleteDatabase(char *databaseName) {

    auto deleteNode = new select_node;
    auto deleteTable = new table_node;
    deleteTable->tableName = _S("database");
    deleteNode->table = deleteTable;
    auto cons = new condexp_node;
    cons->op = cons->EQ;
    cons->left = new condexp_node;
    cons->left->chval = _S("name");
    cons->right = new condexp_node;
    cons->right->chval = databaseName;
    cons->right->type = cons->right->STRING;
    deleteNode->cons = cons;
    InUsedb->close();
    InUsedat->close();
    useDatabase("sys");
    char dbfileName[40] = {0};
    char datfileName[40] = {0};
    strcat_s(dbfileName, strlen(databaseName) + 1, databaseName);
    strcat_s(dbfileName, ".db");
    strcat_s(datfileName, strlen(databaseName) + 1, databaseName);
    strcat_s(datfileName, ".dat");

    if (sqldelete(deleteNode) && remove(dbfileName) && remove(datfileName)){
        return  1;
    }
    return 0;
}

int Core::sqlupdate(update_node * updateNode) {
    int updateNum = 0;
    // 获取要删除的表名
    char *tableName = updateNode->table->tableName;
    // 获取表的所有列属性
    auto tableCols = getColumn(tableName);
    vector<table_field_node> head = tableCols;

    auto datpageNum = getTableStartDatPage(tableName);
//获取每条记录的长度
    int Recordlength = tableCols.at(tableCols.size() - 1).offset + tableCols.at(tableCols.size() - 1).len;

    while (datpageNum != -1) {
        if (!readPage(*InUsedat, datpageNum)) {
            cout << "SELECT: readPage Error!" << endl;
        }
        int i = 0;
        while ((i+1) * Recordlength + sizeof(int) <= PAGE_SIZE){
            if (*(DATPAGE + i * Recordlength) != '\0') {
                vector<values_node> row;
                for (auto h : head) {
                    values_node node;
                    if (h.type == table_field_node::INT) { // int
                        node.intval = *(int *) (DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::INT;
                    } else { // string
                        node.chval = _S(DATPAGE + i * Recordlength + h.offset);
                        node.type = values_node::STRING;
                    }
                    row.push_back(node);
                }
                if (condVerify(head, row, updateNode->cons)){ //
                    auto setNode = updateNode->setval;
                    while (setNode){
                        for (auto h:head) {
                            if (strcmp(h.field_name, setNode->field_name) ==0){
                                if (h.type == table_field_node::INT) { // int
                                    *(int *) (DATPAGE + i * Recordlength + h.offset) = setNode->intval;
                                } else { // string
                                    strcpy_s(DATPAGE + i * Recordlength + h.offset, strlen(setNode->chval)+1, setNode->chval);
                                }
                            }
                        }
                        setNode = setNode->next;
                    }
                    updateNum++;
                }
            }
            i++;
        }
        writePage(*InUsedat, datpageNum);
        datpageNum = getNextPageNum();
    }
    return updateNum;
}

int Core::deleteTable(const char * tableName) {
    auto tablesNow = getTables();
    char temp[100] = {0};
    for (auto t : tablesNow) {
        if (strcmp(t.tableName, tableName) == 0) {
            int PageNow = 0; //表字典
            for (int i = 0; i < 20; i++) {
                int offset = PageNow * PAGE_SIZE + i * 100;
                InUsedb->seekg(offset);
                InUsedb->seekp(InUsedb->tellg());
                InUsedb->read(temp, 100);
                if (strcmp(temp, tableName)==0) {
                    InUsedb->seekp(offset);
                    memset(temp,'\0', 100);
                    InUsedb->write(temp, 100);
                    break;
                }
            }
            PageNow = 1; // 列字典从 1 页开始存放

            for (int i = 0; i < 20; i++) {
                std::streampos offset = PageNow * PAGE_SIZE + i * 100;
                InUsedb->seekg(offset);
                InUsedb->seekp(offset);
                InUsedb->read(temp, 100);
                if (strcmp(temp, tableName)==0) {
                    InUsedb->seekp(offset);
                    memset(temp,'\0', 100);
                    InUsedb->write(temp, 100); //清空该记录向
                }
            }
            return 1;
        }
    }
    return 0;
}

char Core::DATPAGE[PAGE_SIZE];
int Core::TEMP[10];