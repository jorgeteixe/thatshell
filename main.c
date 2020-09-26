#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Function: TrocearCadena
 * ------------------
 * The following function splits thestring pointed by
 * cadena (suposedly not null) into a NULL terminated array
 * of pointers (trozos).
 *
 * *cadena: ref to user input (value gets modified and useless)
 * *trozos[]: ref to null terminated array
 *
 * returns: number of tokens
 */
int TrocearCadena(char *cadena, char *trozos[]) {
    int i = 1;
    if ((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;
    while ((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}

int main() {
    /** Reserves 100 bytes for user input */
    char *inStr = malloc(100);

    while (1) {
        /** Prints shell prompt */
        prompt();

        /** Gets user input and writes on inStr */
        input(inStr);

        /** !TODO save inStr in history before TrocearCadena is called */
        /** Tokenizes user input */
        char *tokens[50];
        int ntokens = TrocearCadena(inStr, tokens);




        /** DEBUG Prints all tokens separated */
        for (int i = 0; i < ntokens; ++i) {
            printf("%s\n", tokens[i]);
        }

        /** Final operations */
        free(inStr);
        exit(1);
    }
}
