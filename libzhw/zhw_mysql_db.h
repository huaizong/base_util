#pragma once
#include <mysql/mysql.h>
struct zhw_mysql_conn_desc_t;
typedef int (*zhw_mysql_save_row_pt)(const MYSQL_ROW row, void *);
int zhw_multi_save_sql_result(
        struct zhw_myql_conn_desc_t *conn,
        const char *sql,
        void *para,
        zhw_mysql_save_row_pt save_func);
