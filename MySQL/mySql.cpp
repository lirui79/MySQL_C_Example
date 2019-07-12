#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>

#include   </usr/include/mysql/mysql.h>

int test_select(MYSQL *cSql, const char* address, const char *user, const char *password, const char* dbname, int port) {
   /*链接数据库，参数1：句柄        参数2：主机名（NULL表示本机）； 参数3：数据库使用使用名 参数4：数据库登录密码 
                  参数5：数据库名字  参数6：数据库端口               参数7：链接类型         参数8：通常为0*/
 //   MYSQL *sqlcon = mysql_real_connect(cSql , "localhost","root","1","runoob",0,NULL,0);
    MYSQL *sqlcon = mysql_real_connect(cSql, address, user, password, dbname, port, NULL, 0);
    if(NULL == sqlcon){
        printf("connect error!\n");
        return -1;
    }

 //   char *querySql = "select * from runoob_tbl";
    char *querySql = "select * from user";

    /*执行操作命令*/
    int rCode = mysql_query(cSql, querySql);
    if(rCode < 0){
        printf("query error %d!\n", rCode);
        return -1;
    }
    MYSQL_RES *sqlRes;
    /*存储检索信息*/
    sqlRes = mysql_store_result(cSql);
    MYSQL_ROW row;
        /*char **argv*/
    /*检索一行的内容*/
    while(row = mysql_fetch_row(sqlRes)){
        printf("%s \t",row[0]);
        printf("%s \t",row[1]);
        printf("%s \t",row[2]);
        printf("%s \t",row[3]);
        printf("\n");
    }
    /*释放结构体空间*/
    mysql_free_result(sqlRes);
    return 0;
}

int test_show_all_sqldb(MYSQL *cSql, const char* address, const char *user, const char *password) {
    MYSQL *sqlcon = mysql_real_connect(cSql, address, user, password, NULL, 0, NULL, 0);
    if(NULL == sqlcon){
        printf("test_show_all_sqldb connect error!\n");
        return -1;
    }

    const char* sqlQuery = "show databases";
    int rCode = mysql_real_query(cSql, sqlQuery, strlen(sqlQuery)) ;
    if (rCode < 0) {
        printf("test_show_all_sqldb mysql_real_query return code %d\n", rCode);
        return -2;
    }

    MYSQL_RES *sqlRes;
    /*存储检索信息*/
    sqlRes = mysql_store_result(cSql);
    MYSQL_ROW row;
        /*char **argv*/
    /*检索一行的内容*/
    printf("%s \n", sqlQuery);
    while(row = mysql_fetch_row(sqlRes)) {
        for (int i = 0; i < mysql_num_fields(sqlRes); ++i) 
           printf("%s\t", row[i]);
        printf("\n");
    }
    return 0;
}

int test_show_all_tables(MYSQL *cSql, const char* dbname) {
    char sqlQuery[256] = {0} ;
    unsigned long sz = snprintf(sqlQuery, 255, "use %s", dbname);
    int rCode = mysql_real_query(cSql, sqlQuery, sz + 1) ;
    if (rCode < 0) {
        printf("test_show_all_tables mysql_real_query return code %d\n", rCode);
        return -2;
    }

    sz = snprintf(sqlQuery, 255, "show tables");

    rCode = mysql_real_query(cSql, sqlQuery, sz + 1) ;
    if (rCode < 0) {
        printf("test_show_all_tables mysql_real_query return code %d\n", rCode);
        return -2;
    }

    MYSQL_RES *sqlRes;
    /*存储检索信息*/
    sqlRes = mysql_store_result(cSql);
    MYSQL_ROW row;
        /*char **argv*/
    /*检索一行的内容*/
    printf("%s \n", sqlQuery);
    while(row = mysql_fetch_row(sqlRes)) {
        for (int i = 0; i < mysql_num_fields(sqlRes); ++i) 
           printf("%s\t", row[i]);
        printf("\n");
    }
    return 0;
}

int test_show_table_columns(MYSQL *cSql, const char* tbname) {
    char sqlQuery[256] = {0} ;
    unsigned long sz = snprintf(sqlQuery, 255, "show columns from %s", tbname);
    int rCode = mysql_real_query(cSql, sqlQuery, sz + 1) ;
    if (rCode < 0) {
        printf("test_show_all_tables mysql_real_query return code %d\n", rCode);
        return -2;
    }

    MYSQL_RES *sqlRes;
    /*存储检索信息*/
    sqlRes = mysql_store_result(cSql);
    MYSQL_ROW row;
        /*char **argv*/
    /*检索一行的内容*/
    printf("%s \n", sqlQuery);
    while(row = mysql_fetch_row(sqlRes)) {
        for (int i = 0; i < mysql_num_fields(sqlRes); ++i) 
            printf("%s\t", row[i]);
        printf("\n");
    }

////
    sz = snprintf(sqlQuery, 255, "select * from %s", tbname);
    rCode = mysql_real_query(cSql, sqlQuery, sz + 1) ;
    if (rCode < 0) {
        printf("test_show_all_tables mysql_real_query return code %d\n", rCode);
        return -2;
    }

  //  MYSQL_RES *sqlRes;
    /*存储检索信息*/
    sqlRes = mysql_store_result(cSql);
  //  MYSQL_ROW row;
        /*char **argv*/
    /*检索一行的内容*/
    printf("%s \n", sqlQuery);
    while(row = mysql_fetch_row(sqlRes)) {
        for (int i = 0; i < mysql_num_fields(sqlRes); ++i) 
            printf("%s\t", row[i]);
        printf("\n");
    }

    return 0;
}

int test_table_insertto(MYSQL *cSql, const char* tbname) {
    char sqlQuery[256] = {0} ;
    unsigned long sz = snprintf(sqlQuery, 255, "insert into %s (runoob_title, runoob_author, submission_date) values('c++', 'browser', NOW())", tbname);   
    int rCode = mysql_real_query(cSql, sqlQuery, sz + 1) ;
    if (rCode < 0) {
        printf("test_show_all_tables mysql_real_query return code %d\n", rCode);
        return -1;
    }

    return 0;
}


// ./testMySQL localhost root 1 runoob 0
// ./testMySQL localhost root 1 mysql 0 
int main(int argc, char *argv[]){
    /*设定一个文件句柄*/
    MYSQL mysql;
    /*初始化*/
    mysql_init(&mysql);


    if (argc < 3) {
        printf("please enter address user password \n");
        return -1;
    }
    const char *address = argv[1], *user = argv[2], *password = argv[3];//, *dbname = argv[4];
    //int port = atoi(argv[5]);
   // printf("address:%s user:%s password:%s dbname:%s port:%d \n", address, user, password, dbname, port);
    char dbName[128] = {0}, tbName[128] = {0};
    test_show_all_sqldb(&mysql, address, user, password);
    puts("please choice database option:");
    scanf("%s", dbName);
    test_show_all_tables(&mysql, dbName);
    puts("please choice table option:");
    scanf("%s", tbName);
    test_show_table_columns(&mysql, tbName);

    test_table_insertto(&mysql, tbName);
    //test_select(&mysql, address, user, password, dbname, port);
 
    /*关闭句柄所指数据库*/
    mysql_close(&mysql);
    return 0;
}