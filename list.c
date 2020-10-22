/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdio.h>
#include <memory.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <libgen.h>
#include <errno.h>
#include "list.h"


void file_date(time_t mtim) {
    char buffer[13];
    struct tm *tc;

    tc = localtime(&mtim);

    strftime(buffer, 13, "%b %d %R", tc);
    printf("%s ", buffer);
}

void list_file(char *filename, int rec_flag, int hid_flag, int long_flag) {
    struct stat st;
    if (lstat(filename, &st) == -1) {
        printf("Could not list %s: %s\n", filename, strerror(errno));
        return;
    }

    if (filename[0] == '.' && !hid_flag) return;

    if (long_flag) {
        // TODO ADD LONG LISTING DATA
        file_date(st.st_mtim.tv_sec);
        printf("%lu ", st.st_ino);
    }
    printf("%s\n", basename(filename));


    if (S_ISDIR(st.st_mode) && rec_flag) {
        DIR *d;
        d = opendir(filename);
        if (d == NULL) return;
        printf("\n%s/ content:\n", filename);
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
            char *path = malloc(PATH_MAX);
            strcpy(path, filename);
            strcat(path, "/");
            strcat(path, ent->d_name);
            list_file(path, rec_flag, hid_flag, long_flag);
            free(path);
        }
    }

}

int list_cmd(char **tokens, int ntokens) {

    int rec_flag = 0;
    int hid_flag = 0;
    int long_flag = 0;
    int dir_flag = 0;

    int flags = 0;
    for (int i = 0; i < ntokens; ++i) {
        if (tokens[i][0] == '-') {
            if (strcmp(tokens[i], "-rec") == 0) {
                rec_flag = 1;
                flags++;
            }
            if (strcmp(tokens[i], "-hid") == 0) {
                hid_flag = 1;
                flags++;
            }
            if (strcmp(tokens[i], "-dir") == 0) {
                dir_flag = 1;
                flags++;
            }
            if (strcmp(tokens[i], "-long") == 0) {
                long_flag = 1;
                flags++;
            }
        } else break;
    }

    if (ntokens - flags == 0) {
        DIR *d;
        d = opendir(".");
        if (d == NULL) return -1;
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
            list_file(ent->d_name, rec_flag, hid_flag, long_flag);
        }
    } else
        for (int i = flags; i < ntokens; ++i) {
            struct stat st;
            lstat(tokens[i], &st);
            if (S_ISDIR(st.st_mode)) {
                if (dir_flag) {
                    DIR *d;
                    d = opendir(tokens[i]);
                    if (d == NULL) return -1;
                    struct dirent *ent;
                    while ((ent = readdir(d)) != NULL) {
                        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
                        char *path = malloc(PATH_MAX);
                        strcpy(path, tokens[i]);
                        strcat(path, "/");
                        strcat(path, ent->d_name);
                        list_file(path, rec_flag, hid_flag, long_flag);
                        free(path);
                    }
                } else {
                    list_file(tokens[i], rec_flag, hid_flag, long_flag);
                }
            } else {
                list_file(tokens[i], rec_flag, hid_flag, long_flag);
            }
        }


    return 0;
}