#pragma once
#include <stdlib.h>

ssize_t zhw_read(int fd, void *ptr, size_t n);

ssize_t zhw_write(int fd, const void *ptr, size_t n);
