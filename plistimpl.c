/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdlib.h>
#include "plistimpl.h"

struct proccess_info {
    int pid;
    int priority;
    char* caller;
    time_t started_time;
    int end_status;
};

struct proccess_node {
    pnode next;
    pinfo info;
};


plist create_plist() {
    return NULL;
}

void add_node(plist pl, int pid, int priority, char* caller) {
    pnode pn = malloc(sizeof(struct proccess_node));
    pinfo pi = malloc(sizeof(struct proccess_info));

    pn->info = pi;
    pn->next = NULL;
    if (pl == NULL) pl = pn;
}