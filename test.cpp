/*
 * @Author: your name
 * @Date: 2020-07-21 16:01:03
 * @LastEditTime: 2020-07-24 11:19:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit±∏
 * @FilePath: /test/test.c
 */ 


#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string>
#include "leveldb/db.h"

using namespace std;


int show_tbl(void *p, int nColumn, char **colValue, char **colName) {
    for (int i = 0; i < nColumn; i++)
    {
        cout << i << " " << (colName[i] ? colName[i] : "NULL") << " " << (colValue[i] ? colValue[i] : "NULL") << endl;
    }
    return 0;
}

int update_cb(void *p, int nColumn, char **colValue ,char **colName) {
    cout << "xxxx" << endl;
    for (int i = 0; i < nColumn; i++)
    {
    }
    return 0;
}

int test_sqlite(void) {
    struct sqlite3 *db = NULL;
    char *errmsg = NULL;
    int ret = 0;
    sqlite3_open("sqlite.db", &db);
    /* ret = sqlite3_exec(db, "drop table MyTable_1", NULL, NULL, &errmsg);
    if (ret) {
        cout << errmsg << endl;
        free(errmsg);
        errmsg = NULL;
    }
    ret = sqlite3_exec(db, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32) )", NULL, NULL, &errmsg);
    if (ret) {
        cout << errmsg << endl;
        free(errmsg);
        errmsg = NULL;
    }
    ret = sqlite3_exec(db, "insert into MyTable_1(`name`) values ('name')", NULL, NULL, &errmsg);
    if (ret) {
        cout << "insert: " << errmsg << endl;
        free(errmsg);
        errmsg = NULL;
    } */
    ret = sqlite3_exec(db, "PRAGMA journal_mode=delete", NULL, NULL, &errmsg);
    if (ret)
    {
        cout << "pragma: " << errmsg << endl;
        free(errmsg);
        errmsg = NULL;
    }
    ret = sqlite3_exec(db, "select * from MyTable_1", show_tbl, NULL, &errmsg);
    if (ret)
    {
        cout << "insert: " << errmsg << endl;
        free(errmsg);
        errmsg = NULL;
    }
    for (int val = 0; val < 10000000; val ++) {
        const char *sql = "update MyTable_1 set name='%d'";
        char sql_str[128];
        snprintf(sql_str, sizeof(sql_str), sql, val);
        sqlite3_exec(db, sql_str, NULL, NULL, &errmsg);
    }
    sqlite3_close(db);
    return 0;
}


int test_leveldb(void) {
    leveldb::DB *db;
    leveldb::Options options;
    //leveldb::DestroyDB("leveldb", options);
    leveldb::RepairDB("leveldb", options);
    leveldb::DB::Open(options, "leveldb", &db);
    leveldb::WriteOptions wops;
    leveldb::ReadOptions rops;
    string val;
    wops.sync = true;
    cout << "starting..." << endl;
    db->Get(rops, "name", &val);
    cout << val << endl;
    for (int val = 0; val < 10000000; val++)
    {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", val);
        db->Put(wops, "name", buf);
    }
    return 0;
}

int main(void) {
    while (true) {
        int pid = fork();
        if (pid < 0) {
            exit(0);
        } else if (pid == 0) {
            // 子进程
            test_sqlite();
            return 0;
        } else {
            // 父进程
            sleep(1);
            kill(pid, 9);
            waitpid(pid, NULL, 0);
        }
    }
    return 0;
}
