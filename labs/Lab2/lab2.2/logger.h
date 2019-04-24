// Logger
void openlog(const char *ident, int log_options, int facility);
void syslog(int priority, const char *format, ...);
int initLogger(char *logType);
int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);
