/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdio.h>
#include "proccess.h"

#define GETPRIORITY 20
#define SETPRIORITY 21
#define GETUID 22
#define SETUID 23
#define FORK 24
#define EXECUTE 25
#define FOREGROUND 26
#define BACKGROUND 27
#define RUNAS 28
#define EXECUTEAS 29
#define LISTPROCS 30
#define PROC 31
#define DELETEPROCS 32

void getpriority_cmd(char *pid, int flag_pid);

void setpriority_cmd(char **tokens, int ntokens);

void getuid_cmd();

void setuid_cmd(char **tokens, int ntokens);

void fork_cmd();

void execute_cmd(char **tokens, int ntokens);

void foreground_cmd(char **tokens, int ntokens);

void background_cmd(char **tokens, int ntokens);

void runas_cmd(char **tokens, int ntokens);

void executeas_cmd(char **tokens, int ntokens);

void listprocs_cmd();

void proc_cmd(char **tokens, int ntokens);

void deleteprocs_cmd(char *token);

int proccess_router(char **tokens, int ntokens, int cmd_index, pnode plist) {
    switch (cmd_index) {
        case GETPRIORITY:
            if (ntokens > 1)
                printf("Error, check the arguments.");
            else
                getpriority_cmd(tokens[0], ntokens);
            break;
        case SETPRIORITY:
            if (ntokens > 2)
                printf("Error, check the arguments.");
            else
                setpriority_cmd(tokens, ntokens);
            break;
        case GETUID:
            if (ntokens)
                printf("Error, check the arguments.");
            else
                getuid_cmd();
            break;
        case SETUID:
            if (ntokens == 0 || ntokens > 2)
                printf("Error, check the arguments.");
            else
                setuid_cmd(tokens, ntokens);
            break;
        case FORK:
            if (ntokens)
                printf("Error, check the arguments.");
            else
                fork_cmd();
            break;
        case EXECUTE:
            if (ntokens == 0)
                printf("Error, check the arguments.");
            else
                execute_cmd(tokens, ntokens);
            break;
        case FOREGROUND:
            if (ntokens == 0)
                printf("Error, check the arguments.");
            else
                foreground_cmd(tokens, ntokens);
            break;
        case BACKGROUND:
            if (ntokens == 0)
                printf("Error, check the arguments.");
            else
                background_cmd(tokens, ntokens);
            break;
        case RUNAS:
            if (ntokens < 3)
                printf("Error, check the arguments.");
            else
                runas_cmd(tokens, ntokens);
            break;
        case EXECUTEAS:
            if (ntokens < 3)
                printf("Error, check the arguments.");
            else
                executeas_cmd(tokens, ntokens);
            break;
        case LISTPROCS:
            if (ntokens)
                printf("Error, check the arguments.");
            else
                listprocs_cmd();
            break;
        case PROC:
            if (ntokens == 0 || ntokens > 2)
                printf("Error, check the arguments.");
            else
                proc_cmd(tokens, ntokens);
            break;
        case DELETEPROCS:
            if (ntokens != 1)
                printf("Error, check the arguments.");
            else
                deleteprocs_cmd(tokens[0]);
            break;
    }
    return 0;
}

void deleteprocs_cmd(char *token) {
    printf("deleteprocs");
}

void proc_cmd(char **tokens, int ntokens) {
    printf("proc");
}

void listprocs_cmd() {
    printf("listprocs");
}

void executeas_cmd(char **tokens, int ntokens) {
    printf("execute-as");
}

void runas_cmd(char **tokens, int ntokens) {
    printf("run-as");
}

void background_cmd(char **tokens, int ntokens) {
    printf("background");
}

void foreground_cmd(char **tokens, int ntokens) {
    printf("foreground");
}

void execute_cmd(char **tokens, int ntokens) {
    printf("execute");
}

void fork_cmd() {
    printf("fork");
}

void setuid_cmd(char **tokens, int ntokens) {
    printf("setuid");
}

void getuid_cmd() {
    printf("getuid");
}

void setpriority_cmd(char **tokens, int ntokens) {
    printf("set priority");
}

void getpriority_cmd(char *pid, int flag_pid) {
    printf("get priority");
}
