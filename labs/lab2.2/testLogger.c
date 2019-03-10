#include <stdio.h>

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main(int argc, char *argv[]) {
    infof("info message", argv[0]);
    warnf("warning message", argv[0]);
    panicf("panic message", argv[0]);
    errorf("error message", argv[0]);
    return 0;
}

/*
#include <stdio.h>
#include "logger.h"

int main(){

    // default logging
    infof("INFO Message %d", 1);
    warnf("WARN Message %d", 2);
    errorf("ERROR Message %d", 2);

    // stdout logging
    initLogger("stdout");
    infof("INFO Message %d", 1);
    warnf("WARN Message %d", 2);
    errorf("ERROR Message %d", 2);

    // syslog logging
    initLogger("syslog");
    infof("INFO Message %d", 1);
    warnf("WARN Message %d", 2);
    errorf("ERROR Message %d", 2);

    return 0;
}
*/