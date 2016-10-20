#define _POSIX_C_SOURCE 200112L
#include "profiling.h"
#include <time.h>


long long timestamp_in_milliseconds() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    unsigned long time_in_micros = 1000000 * te.tv_sec + te.tv_usec; // caculate microseconds
    return time_in_micros;
}

long long timestamp_in_nanoseconds(){
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    long long ct = t.tv_sec * 10^9 + t.tv_nsec;
    return ct;
}
