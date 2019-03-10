#include <stdio.h>
#include "logger.h"

int main(int argc, char *argv[]) {
    infof("info message", argv[0]);
    warnf("warning message", argv[0]);
    panicf("panic message", argv[0]);
    errorf("error message", argv[0]);
    return 0;

    // // default logging
    // infof("INFO Message %d", 1);
    // warnf("WARN Message %d", 2);
    // errorf("ERROR Message %d", 2);

    // // stdout logging
    // // initLogger("stdout");
    // infof("INFO Message %d", 1);
    // warnf("WARN Message %d", 2);
    // errorf("ERROR Message %d", 2);

    // // syslog logging
    // // initLogger("syslog");
    // infof("INFO Message %d", 1);
    // warnf("WARN Message %d", 2);
    // errorf("ERROR Message %d", 2);

    // return 0;
}
