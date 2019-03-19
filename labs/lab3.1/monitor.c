// References
// http://man7.org/linux/man-pages/man3/ftw.3.html

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/inotify.h>
#include "logger.h"

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int inotifyFd;
static int get_files(const char *fpath, const struct stat *sb, int flag, struct FTW *ftwbuf);
static void displayInotifyEvent(struct inotify_event *i);

static int get_files(const char *fpath, const struct stat *sb, int flag, struct FTW *ftwbuf) {
    int wd = inotify_add_watch(inotifyFd, fpath, IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    if (wd == -1) {
        errorf("can't add inotify_add_watch");
        exit(EXIT_FAILURE);
    }
    return 0;
}

static void displayInotifyEvent(struct inotify_event *i) {
    if (i->mask & IN_CREATE)
        infof("CREATE ");
    if (i->mask & IN_DELETE)
        infof("DELETE ");
    if (i->mask & IN_MOVED_FROM)
        infof("MOVED_FROM ");
    if (i->mask & IN_MOVED_TO)
        infof("MOVED_TO ");
    printf("\n");

    if (i->len > 0)
        printf("        name = %s\n", i->name);
}

/* main(int argc, char *argv[]) {
    int flags, opt;
    flags = 0;
    while ((opt = getopt(argc, argv, "dmp")) !=
    FTW_SLN) ? "SLN" :
    switch (opt) {
    case 'd': flags |= FTW_DEPTH;
    case 'm': flags |= FTW_MOUNT;
    case 'x': flags |= FTW_PHYS; default: usageError(argv[0], NULL); }
    }
*/

int main(int argc, char *argv[]) {
    inotifyFd = inotify_init();
    char buf[BUF_LEN] __attribute__((aligned(8)));
    ssize_t nRead;
    char *x;
    struct inotify_event *event;

    if (inotifyFd == -1) {
        errorf("can't create inotifyFd");
        exit(EXIT_FAILURE);
    }

    int flags = FTW_PHYS;
    if (nftw((argc < 2) ? "." : argv[1], get_files, 20, flags) == -1) {
        panicf("can't transverse nftw");
        exit(EXIT_FAILURE);
    }

    for (;;) { 
        nRead = read(inotifyFd, buf, BUF_LEN);
        if (nRead == 0) {
            panicf("read() from inotify fd returned 0!");
            exit(EXIT_FAILURE);
        }
        if (nRead == -1) {
            errorf("read");
            exit(EXIT_FAILURE);
        }
        for (x = buf; x < buf + nRead;) {
            event = (struct inotify_event *)x;
            displayInotifyEvent(event);
            x += sizeof(struct inotify_event) + event->len;
        }
        inotifyFd = inotify_init();
        if (nftw((argc < 2) ? "." : argv[1], get_files, 20, flags) == -1) {
            panicf("can't transverse nftw");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
<<<<<<< HEAD
}
=======
}
>>>>>>> fa930b83fcb47e51402e1a49c2ffdc7b2c900a72
