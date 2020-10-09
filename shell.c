#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "arrayimpl.h"

/** COMMAND CONSTANTS */

#define EXIT 0
#define QUIT 1
#define END 2
#define AUTHORS 3
#define GETPID 4
#define GETPPID 5
#define PWD 6
#define CHDIR 7
#define DATE 8
#define TIME 9
#define HISTORIC 10

/**
 * Function: prompt
 * ------------------
 * prints the prompt in stdout
 *
 * returns: void
 */
void prompt() {
    char shellName[] = "thatshell";
    printf("%s$:", shellName);
}

/**
 * Function: input
 * ------------------
 * func def
 *
 * *inStr: pointer to 100 bytes where to write the input from stdin
 *
 * returns: void
 */
void input(char *inStr) {
    fgets(inStr, 100, stdin);
}

/**
 * Function: TrocearCadena (got from exercise statement)
 * ------------------
 * The following function splits the string pointed by
 * cadena (suposedly not null) into a NULL terminated array
 * of pointers (trozos).
 *
 * *cadena: ref to user input (value gets modified and useless)
 * **trozos: ref to null terminated array
 *
 * returns: number of tokens
 */
int TrocearCadena(char *cadena, char **trozos) {
    int i = 1;
    if ((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;
    while ((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

/**
 * Function: getpid_cmd
 * ------------------
 * Calls system getpid and prints the result
 *
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int getpid_cmd(int nargs) {
    if (nargs != 0) {
        printf("%s\n", "getpid does not accept any argument.");
        return -1;
    }
    printf("%d\n", getpid());
    return 0;
}


/**
 * Function: getppid_cmd
 * ------------------
 * Calls system getppid and prints the result
 *
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int getppid_cmd(int nargs) {
    if (nargs != 0) {
        printf("%s\n", "getppid does not accept any argument.");
        return -1;
    }
    printf("%d\n", getppid());
    return 0;
}


/**
 * Function: pwd_cmd
 * ------------------
 * Prints the current working directory
 *
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int pwd_cmd(int nargs) {
    if (nargs != 0) {
        printf("%s\n", "pwd does not accept any argument.");
        return -1;
    }
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return 0;
}


/**
 * Function: date_cmd
 * ------------------
 * Prints the current date in DD/MM/YYYY format
 *
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int date_cmd(int nargs) {
    if (nargs != 0) {
        printf("%s\n", "date does not accept any argument.");
        return -1;
    }
    time_t t;
    char buffer[12];
    struct tm *tc;

    t = time(NULL);
    tc = localtime(&t);

    strftime(buffer, 12, "%d/%m/%Y", tc);
    printf("%s\n", buffer);
    return 0;
}


/**
 * Function: time_cmd
 * ------------------
 * Prints the current t in hh:mm:ss format
 *
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int time_cmd(int nargs) {
    if (nargs != 0) {
        printf("%s\n", "time does not accept any argument.");
        return -1;
    }
    time_t t;
    char buffer[10];
    struct tm *tc;

    t = time(NULL);
    tc = localtime(&t);

    strftime(buffer, 10, "%T", tc);
    printf("%s\n", buffer);
    return 0;
}

/**
 * Function: chdir_cmd
 * ------------------
 * Changes the current working directory.
 *
 * **args: array of arguments received from user
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int chdir_cmd(char **args, int nargs) {
    switch (nargs) {
        case 0:
            pwd_cmd(nargs);
            return 0;
        case 1:
            if (chdir(args[0]) == -1) {
                printf("Could not change to %s: %s\n", args[0], strerror(errno));
                return -1;
            }
            return 0;
        default:
            break;
    }
    printf("%s\n", "Arguments are wrong, check it out.");
    return -1;
}


/**
 * Function: authors_cmd
 * ------------------
 * Gives the logic to the authors command.
 *
 * **args: array of arguments received from user
 * nargs: number of arguments received
 *
 * returns: returns 0 when correct, -1 when error
 */
int authors_cmd(char **args, int nargs) {
    char *authors[2][2] = {
            {"Jorge Teixeira Crespo", "jorge.teixeira@udc.es"},
            {"Miguel Juncal Paz",     "miguel.juncalp@udc.es"}
    };
    switch (nargs) {
        case 0:
            printf("Authors: \n%s (%s)\n%s (%s)\n", authors[0][0], authors[0][1], authors[1][0], authors[1][1]);
            return 0;
        case 1:
            if (strcmp(args[0], "-n") == 0) {
                printf("Authors names:\n %s\n %s\n", authors[0][0], authors[1][0]);
                return 0;
            }
            if (strcmp(args[0], "-l") == 0) {
                printf("Authors logins:\n %s\n %s\n", authors[0][1], authors[1][1]);
                return 0;
            }
        default:
            break;
    }
    printf("%s\n", "Arguments are wrong, check it out.");
    return -1;
}


/**
 * Function: historic_cmd
 * ------------------
 * Works with the command history.
 *
 * **args: array of arguments received from user
 * nargs: number of arguments received
 * h: the address where the history is saved
 *
 * returns: returns 0 when correct, -1 when error
 */
int historic_cmd(char **args, int nargs, historic h) {

    int n_elem = n_elements_in_historic(h);

    if (n_elem == 0) {
        printf("%s", "There is no history yet, cannot do anything.\n");
        return 0;
    }

    switch (nargs) {
        case 0:
            for (int i = 0; i < n_elem; ++i) {
                printf("%d) %s\n", i, read_from_historic(h, i));
            }
            break;
        case 1:
            if (strcmp(args[0], "-c") == 0) {
                for (int i = 0; i < n_elem; ++i) {
                    remove_from_historic(h, 0);
                }
                printf("%s\n", "Cleared history.");
                return 0;
            }
            if (args[0][0] == '-' && args[0][1] == 'r') {
                if (strlen(args[0]) == 3 && args[0][2] == '0') {
                    // TODO RUN 0
                } else {
                    int n = atoi(args[0] + 2);
                    if (n == 0) {
                        printf("%s\n", "Arguments are wrong, check it out.");
                    } else {
                        // TODO RUN N
                    }
                }
                return 0;
            }
            if (args[0][0] == '-') {
                if (strlen(args[0]) == 2 && args[0][1] == '0') {
                    printf("0) %s\n", read_from_historic(h, 0));
                } else {
                    int n = atoi(args[0] + 1);
                    if (n == 0) {
                        printf("%s\n", "Arguments are wrong, check it out.");
                    } else {
                        for (int i = 0; i < n + 1; ++i) {
                            if (i < n_elem) printf("%d) %s\n", i, read_from_historic(h, i));
                        }
                    }
                }
                return 0;
            }
            break;
        default:
            printf("%s\n", "Arguments are wrong, check it out.");
            break;
    }

    return 0;
}


/**
 * Function: router
 * ------------------
 * Receiving the tokens of the user input, finds the function
 * related to the command that the user wants to run, goes and passes
 * the arguments.
 *
 * **myCommands: array with avaliable commands
 * N_COMMANDS: number of elements in myCommands
 * **tokens: user input tokenized
 * ntokens: number of elements in tokens
 * historic: address to history
 *
 * returns: int 1 when continue, 0 when exit
 */
int router(char **myCommands, int N_COMMANDS, char **tokens, int ntokens, historic h) {

    int cmdCounter;
    for (cmdCounter = 0; cmdCounter < N_COMMANDS; ++cmdCounter) {
        if (strcmp(tokens[0], myCommands[cmdCounter]) == 0) {
            break;
        }
    }

    /** Actual router to functions */
    switch (cmdCounter) {
        case EXIT:
        case QUIT:
        case END:
            return 0;
        case AUTHORS:
            authors_cmd(tokens + 1, ntokens - 1);
            break;
        case GETPID:
            getpid_cmd(ntokens - 1);
            break;
        case GETPPID:
            getppid_cmd(ntokens - 1);
            break;
        case PWD:
            pwd_cmd(ntokens - 1);
            break;
        case CHDIR:
            chdir_cmd(tokens + 1, ntokens - 1);
            break;
        case DATE:
            date_cmd(ntokens - 1);
            break;
        case TIME:
            time_cmd(ntokens - 1);
            break;
        case HISTORIC:
            historic_cmd(tokens + 1, ntokens - 1, h);
            break;
        default:
            printf("Unrecognised command... Try again.\n");
    }
    printf("\n");
    return 1;
}

/**
 * Function: load_cmds
 * ------------------
 * Loads the pointers of the commands words in heap
 *
 * N_COMMANDS: number of commands that will be stored
 *
 * returns: the pointer to the commands array
 */
char **load_cmds(int N_COMMANDS) {
    /** Array of commands and the assigned number */

    char **myCommands = malloc(sizeof(char *) * N_COMMANDS);

    myCommands[EXIT] = "exit";
    myCommands[QUIT] = "quit";
    myCommands[END] = "end";
    myCommands[AUTHORS] = "authors";
    myCommands[GETPID] = "getpid";
    myCommands[GETPPID] = "getppid";
    myCommands[PWD] = "pwd";
    myCommands[CHDIR] = "chdir";
    myCommands[DATE] = "date";
    myCommands[TIME] = "time";
    myCommands[HISTORIC] = "historic";

    return myCommands;
}

int main() {
    /** Reserves 100 bytes for user input */
    char *inStr = malloc(100);
    int status = 1;

    char *inCopy;

    int n_cms = 11;
    char **cms = load_cmds(n_cms);

    historic h = create_historic();

    while (status) {
        /** Prints shell prompt */
        prompt();

        /** Gets user input and writes on inStr */
        input(inStr);

        /** Saves a copy of the entry */
        inCopy = strdup(inStr);

        /** Tokenizes user input */
        char *tokens[50];
        int ntokens = TrocearCadena(inStr, tokens);
        status = router(cms, n_cms, tokens, ntokens, h);

        /** If the command is different to HISTORIC, save it in historic and frees copy */
        if (strcmp(tokens[0], cms[HISTORIC]) != 0) {
            insert_in_historic(h, inCopy);
        }
        free(inCopy);

    }

    /** Final operations */
    remove_historic(h);
    free(cms);
    free(inStr);
    return 1;
}
