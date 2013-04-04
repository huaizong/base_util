
#include "zhw_mysql_db.h"

static int zhw_mysql_query(struct zhw_mysql_conn_desc_t *conn, const char *sql, int len);
int zhw_multi_save_sql_result(
        struct zhw_myql_conn_desc_t *conn,
        const char *sql,
        void *para,
        zhw_mysql_save_row_pt save_func)
{
    if(conn == NULL || sql == NULL || save_func == NULL) {
        return -1;
    }
    //TODO
    
    return 0;
}

int zhw_mysql_query(struct zhw_mysql_conn_desc_t *conn, const char *sql, int len);
{
    if(conn == NULL || sql == NULL || len == 0) {
        return -1;
    }
    //TODO
    return 0;

}
