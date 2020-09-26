#include <stdio.h>
#include <stdlib.h>

/* comment template */

/*
 * Function: func_name
 * ------------------
 * func def
 *
 * param: param def
 *
 * returns: return def
 */


/*
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

/*
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

int main() {
    /* Reserve 100 bytes for user input */
    char *inStr = malloc(100);

    while (1) {
        /* Prints shell prompt */
        prompt();

        /* Get user input and writes on inStr */
        input(inStr);




        /* Variable value test output */
        printf("%s", inStr);

        /* Final operations */
        free(inStr);
        exit(1);
    }
}
