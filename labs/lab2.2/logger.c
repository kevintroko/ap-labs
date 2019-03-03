#include <syslog.h>
#include <stdio.h>

void openlog(const char *ident, int log_options, int facility);
void syslog(int priority, const char *format, ...);

void warning_message() {
    openlog("foo", (LOG_CONS|LOG_PERROR|LOG_PID), LOG_USER);
    syslog(LOG_WARNING, "%s", "warning message");
    closelog();
}

int main(int argc, char *argv[]) {
    warning_message();
    return 0;
}