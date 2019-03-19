#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <ftw.h>
#include <string.h>
#include <stdint.h>
#include "logger.h"
#include <poll.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))
#define _XOPEN_SOURCE 500

int wd;
int fd;

/* Read all available inotify events from the file descriptor 'fd'.
          wd is the table of watch descriptors for the directories in argv.
          argc is the length of wd and argv.
          argv is the list of watched directories.
          Entry 0 of wd and argv is unused. */


static void getTree(char dir[]);
static int addWatchers(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);

static void getTree(char dir[]) {
    int flags = 0;
    if (nftw(dir, addWatchers, 20, flags) == -1) {
        errorf("nftw");
        exit(EXIT_FAILURE);
    }
}

static int addWatchers(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    if ((intmax_t)sb->st_size == 4096) {
        wd = inotify_add_watch(fd, fpath, IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    }
    return 0;
}

int main(int argc, char **argv) {
    int length, i;
    char buffer[BUF_LEN];

    if (argc < 2) {
        errorf("Incorrect usage, do: ./main [directory]\n");
        return -1;
    }

    initLogger("stdout");
    fd = inotify_init();

    if (fd < 0) {
        errorf("inotify_init");
    }

    getTree(argv[1]);

    while (1) {
        i = 0;
        length = read(fd, buffer, BUF_LEN);

        if (length < 0) {
            perror("read");
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer;
            if (event->len) {
                if (event->mask & IN_CREATE) {
                    if (event->mask == 256) {
                        infof("The file %s was created.\n", event->name);
                    }
                    else if (event->mask == 1073742080) {
                        infof("The directory %s was created.\n", event->name);
                        getTree(argv[1]);
                    }
                } else if (event->mask & IN_DELETE) {
                    if (event->mask == 512) {
                        infof("The file %s was deleted.\n", event->name);
                    } else if (event->mask == 1073742336) {
                        infof("The directory %s was deleted.\n", event->name);
                        getTree(argv[1]);
                    }
                }
                else if (event->mask & IN_MODIFY) { //directory change
                    infof("The file %s was modified.\n", event->name);
                }
                else if (event->mask & IN_MOVED_FROM) {
                    if (event->mask == 64) {
                        infof("The file %s was renamed ", event->name);
                    }
                    else if (event->mask == 1073741888) {
                        infof("The directory %s was renamed ", event->name);
                        getTree(argv[1]);
                    }
                }
                
                if (event->mask & IN_MOVED_TO) {
                    infof("to %s.\n", event->name);
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    (void)inotify_rm_watch(fd, wd);
    (void)close(fd);

    return 0;
}

