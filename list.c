/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdio.h>
#include <memory.h>
#include <sys/stat.h>
#include <time.h>
#include "list.h"


void file_date(time_t mtim) {
    char buffer[13];
    struct tm *tc;

    tc = localtime(&mtim);

    strftime(buffer, 13, "%b %d %R", tc);
    printf("%s ", buffer);
}

void list_file(char *filename, int rec_flag, int hid_flag, int long_flag, int dir_flag) {
    struct stat st;
    lstat(filename, &st);

    

    file_date(st.st_mtim.tv_sec);

    printf("%lu ", st.st_ino);

    printf("%s\n", filename);
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
        list_file(".", rec_flag, hid_flag, long_flag, 1);
    } else for (int i = flags; i < ntokens; ++i) {
        list_file(tokens[i], rec_flag, hid_flag, long_flag, dir_flag);
    }


    return 0;
}