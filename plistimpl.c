/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */

#include <stdlib.h>
#include "plistimpl.h"
#include <sys/time.h>
#include <sys/resource.h>


plist create_plist() {
    plist h = malloc(sizeof(plist));
    h = NULL;
    return h;
}

bool createNode(posPL *pos) {
    *pos = malloc(sizeof(struct proccess_node));
    return (*pos!=NULL);
}


bool insertItem(pinfo info, plist* pl){
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
}


posPL findItemByPID(plist pl, int pid){
    posPL pos;
    pos=pl;
    while(pos != NULL){
        if (pos->info.pid==pid){
            return pos;
        }
        pos=pos->next;
    }
    pos=NULL;
    return pos;
}


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
    free(pos);// se libera el nodo pos};
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
}


posPL last(plist pl){
    posPL q;
    for(q=pl; q->next!=NULL; q=q->next);
    return q;
}


pinfo createInfo(int pid, char* caller){
   struct pinfo info;
   info.pid = pid;
   info.priority= 0;
   info.caller=caller;
   info.started_time=time(0);
   info.end_status=1000;
   return info;
}


char *date(time_t time) {
    char *dateAndTime;
    dateAndTime = (char *) malloc(sizeof(char) * 49);
    struct tm *tm;
    tm = localtime(&time);
    strftime(dateAndTime, 80, "%d/%m/%Y at %H:%M:%S", tm);
    return dateAndTime;
}
void printInfo(struct pinfo info){
    int which=PRIO_PROCESS;
    char* dateAndTime= date(info.started_time);
    printf("Process: PID:%d  priority:%d  caller:%s  Start_Time:%s end_status:%d \n", info.pid,
           getpriority(which,info.pid),info.caller, dateAndTime,info.end_status);
    free(dateAndTime);
}
void showList(plist pl){
    posPL p;
    p = pl;
    if(isEmptyList(pl))
        printf("Proccess list is empty :(\n");
    while(p != NULL){
        printInfo(p->info);
        p = p->next;
    }
}