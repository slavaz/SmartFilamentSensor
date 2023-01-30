#ifndef MOCKLIB_TIME__H
#define MOCKLIB_TIME__H

#include "stdlib.h"

typedef uint64_t absolute_time_t;

absolute_time_t get_absolute_time(void);

int64_t absolute_time_diff_us(absolute_time_t from, absolute_time_t to);

#endif
