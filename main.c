#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "arrayimpl.h"

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
    struct tm* tc;

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
    struct tm* tc;

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
    char *authors[] = {"Jorge Teixeira Crespo", "jorge.teixeira@udc.es"};
    switch (nargs) {
        case 0:
            printf("Author: \n%s (%s)\n", authors[0], authors[1]);
            return 0;
        case 1:
            if (strcmp(args[0], "-n") == 0) {
                printf("Author name: %s\n", authors[0]);
                return 0;
            }
            if (strcmp(args[0], "-l") == 0) {
                printf("Author login: %s\n", authors[1]);
                return 0;
            }
        default:
            break;
    }
    printf("%s\n", "Arguments are wrong, check it out.");
    return -1;
}

void historic_cmd(char **args, int nargs) {

}


/**
 * Function: router
 * ------------------
 * Receiving the tokens of the user input, finds the function
 * related to the command that the user wants to run, goes and passes
 * the arguments.
 *
 * **tokens: user input tokenized
 * ntokens: number of elements in tokens
 *
 * returns: void
 */
int router(char **myCommands, int N_COMMANDS, char **tokens, int ntokens) {


    int cmdCounter;
    for (cmdCounter = 0; cmdCounter < N_COMMANDS; ++cmdCounter) {
        if (strcmp(tokens[0], myCommands[cmdCounter]) == 0) {
            break;
        }
    }

    /** Actual router to functions */
    switch (cmdCounter) {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
            authors_cmd(tokens + 1, ntokens - 1);
            break;
        case 4:
            getpid_cmd(ntokens - 1);
            break;
        case 5:
            getppid_cmd(ntokens - 1);
            break;
        case 6:
            pwd_cmd(ntokens - 1);
            break;
        case 7:
            chdir_cmd(tokens + 1, ntokens - 1);
            break;
        case 8:
            date_cmd(ntokens - 1);
            break;
        case 9:
            time_cmd(ntokens - 1);
            break;
        case 10:
            historic_cmd(tokens + 1, ntokens - 1);
            break;
        default:
            printf("Unrecognised command... Try again.\n");
    }
    printf("\n");
    return 1;
}

char** loadCmds(int N_COMMANDS) {
    /** Array of commands and the assigned number */

    char **myCommands = malloc(sizeof(char*)*N_COMMANDS);

    myCommands[0] = "exit";
    myCommands[1] = "quit";
    myCommands[2] = "end";
    myCommands[3] = "authors";
    myCommands[4] = "getpid";
    myCommands[5] = "getppid";
    myCommands[6] = "pwd";
    myCommands[7] = "chdir";
    myCommands[8] = "date";
    myCommands[9] = "time";
    myCommands[10] = "historic";

    return myCommands;
}

int main() {
    /** Reserves 100 bytes for user input */
    char *inStr = malloc(100);
    int status = 1;

    int n_cms = 11;
    char **cms = loadCmds(n_cms);

    historic h = create_historic();

    while (status) {
        /** Prints shell prompt */
        prompt();

        /** Gets user input and writes on inStr */
        input(inStr);

        /** Save the command in historic */
        insert_in_historic(h, inStr);

        /** Tokenizes user input */
        char *tokens[50];
        int ntokens = TrocearCadena(inStr, tokens);

        status = router(cms, n_cms, tokens, ntokens);

    }

    /** Final operations */
    remove_historic(h);
    free(cms);
    free(inStr);
    return 1;
}
