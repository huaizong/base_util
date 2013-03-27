#pragma once
#include <pthread.h>
#include <syslog.h>

#define ZHW_LOG_INFO(fmt, arg...)      zhw_write_log(LOG_INFO|LOG_LOCAL6, "%s[%d][%x]: "#fmt, __func__, __LINE__, pthread_self(), ##arg)
#define ZHW_LOG_ERR(fmt, arg...)       zhw_write_log(LOG_ERR|LOG_LOCAL6, "%s[%d][%x]: "#fmt, __func__, __LINE__, pthread_self(), ##arg)
#define ZHW_LOG_DEBUG(fmt, arg...)     zhw_write_log(LOG_DEBUG|LOG_LOCAL6, "%s[%d][%x]: "#fmt, __func__, __LINE__, pthread_self(), ##arg)
void zhw_log_init(const char *ident);
void zhw_write_log(int priority, const char *message, ...);
