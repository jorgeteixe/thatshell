/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listmem.h"


struct struct_command{
    void * address ;
    int size;
    char * date_and_time;
    char * type;
    char * param;
};


struct memory_struct {
    command * list[4096];
    int n_elem;
};



mem_historic create_memlist(){
    mem_historic historic = (mem_historic) malloc(sizeof(struct memory_struct));
    historic->n_elem = 0;
    for(int i = 0;i<4096;i++){
        historic->list[i]=NULL;
    }
    return historic;
    
    return historic;
}

void remove_memlist(mem_historic historic){
    for(int i=0 ; i<historic->n_elem ; i++){
        free(historic->list[i]);
    }
    free(historic->list);
};

void insert_in_memlist(mem_historic historic,void* memoryAddress,int size,char* type,char* params){  

    if (historic->n_elem<4096){
        historic->list[historic->n_elem]=(command*)malloc(sizeof(command));
        historic->list[historic->n_elem]->address = memoryAddress;
        historic->list[historic->n_elem]->size = size;
        historic->list[historic->n_elem]->date_and_time = dateAndTime();
        historic->list[historic->n_elem]->type = type;
        historic->list[historic->n_elem]->param =params;
        historic->n_elem++;
    }
}

char * dateAndTime(){
    time_t t;
    struct tm * tm;
    char * dateAndTime;
    dateAndTime = (char*)malloc(sizeof(char)*40);
    t = time(NULL);
    tm = localtime(&t);
    strftime(dateAndTime,24,"%d/%m/%Y : %H:%M:%S",tm);
    free(dateAndTime);
    return dateAndTime;
};


void remove_from_memlist(mem_historic historic , int position){
    int last = historic->n_elem-1;
    if(historic->n_elem==0){
        printf("the list is empty, you cant remove");
    }else{
        if(position==last){
            free(historic->list[position]);
            historic->n_elem--;
        }else{
            free(historic->list[position]);
            for(int i=position ; i<=last ; ++i){
                historic->list[i] = historic->list[i+1];
            }
            historic->n_elem--;
        }
    }
    
};

command * read_from_memlist(mem_historic historic, int position){
    return historic->list[position];
};

int n_elements_in_memlist(mem_historic historic){
    return historic->n_elem;
}
