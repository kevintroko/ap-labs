#include <syslog.h>
#include <stdio.h>
#include <stdarg.h>

void openlog(const char *ident, int log_options, int facility);
void syslog(int priority, const char *format, ...);

int infof(const char *format, ...);
// int warnf(const char *format, ...);
// int errorf(const char *format, ...);
// int panicf(const char *format, ...);

 int infof(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char* arg = va_arg(list, char*);
    openlog(arg, (LOG_CONS|LOG_PERROR|LOG_PID), LOG_USER);
    syslog(LOG_INFO, "%s", format);
    closelog();
    return 0;
}

 int warnf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char* arg = va_arg(list, char*);
    openlog(arg, (LOG_CONS|LOG_PERROR|LOG_PID), LOG_USER);
    syslog(LOG_WARNING, "%s", format);
    closelog();
    return 0;
}

 int errof(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char* arg = va_arg(list, char*);
    openlog(arg, (LOG_CONS|LOG_PERROR|LOG_PID), LOG_USER);
    syslog(LOG_ERR, "%s", format);
    closelog();
    return 0;
}

 int panicf(const char *format, ...) {
    va_list list;
    va_start(list, format);
    char* arg = va_arg(list, char*);
    openlog(arg, (LOG_CONS|LOG_PERROR|LOG_PID), LOG_USER);
    syslog(LOG_EMERG, "%s", format);
    closelog();
    return 0;
}

int main(int argc, char *argv[]) {
    infof("info message", argv[0]);
    return 0;
}