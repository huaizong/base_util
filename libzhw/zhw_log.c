#include <stdio.h>
#include <stdarg.h>
#include "zhw_log.h"


void zhw_log_init(const char *ident)
{
    fprintf(stdout, "ident: %s\n", ident);

}

void zhw_write_log(int priority, const char *message, ...)
{
    #define MAX_MSG_SIZE 1024
    char msg[MAX_MSG_SIZE + 1] = {0};
    va_list ap;
    va_start(ap, message);
    vsnprintf(msg, MAX_MSG_SIZE, message, ap);
    msg[MAX_MSG_SIZE] = '\0';
    fprintf(stdout, "%s\n", msg);
//    syslog(priority, "%s", msg);
}
