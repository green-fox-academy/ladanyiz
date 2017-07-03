#include <time.h>
#include "timestamp.h"

time_t rawtime;
struct tm *timeinfo;
char time_buffer[30];

char *timestamp()
{
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime (time_buffer, 30, "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_buffer;
}
