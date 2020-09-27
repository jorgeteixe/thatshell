#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

    /** Get only arguments */


    /** Actual router to functions */
    switch (cmdCounter) {
        case 0:
        case 1:
        case 2:
            return 0;
        case 3:
            break;
        case 4:
            printf("%d", getpid());
            break;
        case 5:
            printf("%d", getppid());
            break;
        case 6:
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
