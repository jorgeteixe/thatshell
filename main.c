#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

/** comment template **/

/**
 * Function: func_name
 * ------------------
 * func def
 *
 * param: param def
 *
 * returns: return def
 */


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


/**
 * Function: router
 * ------------------
 * Receiving the tokens of the user input, finds the function
 * related to the command that the user wants to run, goes and passes
 * the arguments.
 *
 * **tokens: user input tokenized
 *
 * returns: void
 */
int router(char **tokens, int ntokens) {
    /** Array of commands and the assigned number */
    const int N_COMMANDS = 11;
    char *myCommands[N_COMMANDS];

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
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            printf("Unrecognised command... Try again.\n");
    }
    printf("\n");
    return 1;
}

int main() {
    /** Reserves 100 bytes for user input */
    char *inStr = malloc(100);
    int status = 1;

    while (status) {
        /** Prints shell prompt */
        prompt();

        /** Gets user input and writes on inStr */
        input(inStr);

        /** !TODO save inStr in history before TrocearCadena is called */

        /** Tokenizes user input */
        char *tokens[50];
        int ntokens = TrocearCadena(inStr, tokens);

        status = router(tokens, ntokens);

    }

    /** Final operations */
    free(inStr);
    return 1;
}
