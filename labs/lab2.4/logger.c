#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"
#include "logger.h"

void openlog(const char *ident, int log_options, int facility);
void syslog(int priority, const char *format, ...);

char buf[256];

int initLogger(char *logType) {
    printf("Initializing Logger on: %s\n", logType);
    return 0;
}

int infof(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char *arg = va_arg(list, char *);
    openlog(arg, (LOG_CONS | LOG_PERROR | LOG_PID), LOG_USER);
    snprintf(buf, sizeof buf, "%s%s%s", GRN, format, RESET);
    syslog(LOG_INFO, "%s", buf);
    closelog();
    return 0;
}

int warnf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char *arg = va_arg(list, char *);
    openlog(arg, (LOG_CONS | LOG_PERROR | LOG_PID), LOG_USER);
    snprintf(buf, sizeof buf, "%s%s%s", YEL, format, RESET);
    syslog(LOG_WARNING, "%s", buf);
    closelog();
    return 0;
}

int errorf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char *arg = va_arg(list, char *);
    openlog(arg, (LOG_CONS | LOG_PERROR | LOG_PID), LOG_USER);
    snprintf(buf, sizeof buf, "%s%s%s", RED, format, RESET);
    syslog(LOG_ERR, "%s", buf);
    closelog();
    return 0;
}
int panicf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char *arg = va_arg(list, char *);
    openlog(arg, (LOG_CONS | LOG_PERROR | LOG_PID), LOG_USER);
    snprintf(buf, sizeof buf, "%s%s%s", MAG, format, RESET);
    syslog(LOG_EMERG, "%s", buf);
    closelog();
    return 0;
}

