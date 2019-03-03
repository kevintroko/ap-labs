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