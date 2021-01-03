/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdlib.h>
#include "plistimpl.h"


plist create_plist() {
    return NULL;
}

bool createNode(posPL *pos) {
    *pos = malloc(sizeof(struct proccess_node));
    return (*pos!=NULL);
}


bool insertItem(struct pinfo info, plist* pl){
    posPL q, r;
    if (!createNode(&q))
        return false;
    else {
        q->info = info; 
        q->next = NULL; 
        if (isEmptyList(*pl)) { 
            *pl = q; 
        }else{
            r=*pl;
            r=last(*pl);
            r->next=q;
        }  
        return true; 
    }
};


void deleteAtPosition(posPL pos, plist *pl){
    posPL q;
    if(pos == *pl)
        *pl =(*pl)->next;

    else if(pos->next == NULL){
        for(q=*pl; q->next != pos; q = q->next);
        q->next = NULL; 

    }else{
        q=pos->next;
        pos->info=q->info;
        pos->next=q->next;
        pos=q;
    }

    free(pos);// se libera el nodo p};
}

void deleteList(plist *pl){
    posPL p;
    while(*pl != NULL){
        p = *pl;
        *pl = (*pl)->next;
        free(p);
    }
}

bool isEmptyList(plist pl){
    return pl == NULL;
};


posPL last(plist pl){
    posPL q;
    for(q=pl; q->next!=NULL; q=q->next);
    return q;
};

void showList(plist pl){
    posPL p;
    p = pl;
    while(p != NULL){
        printf("Process: PID:%d  priority:%d  caller:%s  Start_Time: end_status:%d \n", p->info.pid, p->info.priority, p->info.caller, p->info.end_status);
        p = p->next;
    }
};