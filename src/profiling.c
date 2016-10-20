#include "profiling.h"
#include <stdlib.h>

long long timestamp_in_milliseconds() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    unsigned long time_in_micros = 1000000 * te.tv_sec + te.tv_usec; // caculate microseconds
    return time_in_micros;
}
