/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include "memory.h"
#include "listmem.h"
#include <sys/shm.h>


int mem_alloc_malloc(char **tokens, int ntokens, mem_list ml);
int mem_alloc_mmap(char **tokens, int ntokens, mem_list ml);
int mem_alloc_createshared(char **tokens, int ntokens, mem_list ml);
int mem_alloc_shared(char **tokens, int ntokens, mem_list ml);

int mem_dealloc();
int mem_dealloc_addr(char* address);
int mem_dealloc_malloc(char **tokens, int ntokens);
int mem_dealloc_mmap(char **tokens, int ntokens);
int mem_dealloc_shared(char **tokens, int ntokens);

int mem_deletekey(char* key);

int mem_show(char **tokens, int ntokens);

int mem_dopmap();

int memory_cmd(char **tokens, int ntokens, mem_list ml) {
    if (ntokens == 0) {
        printf("only memory\n");
    } else {
        if (strcmp(tokens[0], "-allocate") == 0) {
            if (ntokens == 1) {
                printf("Error, check the arguments.\n");
            } else {
                if (strcmp(tokens[1], "-malloc") == 0) {
                    mem_alloc_malloc(tokens + 2, ntokens - 2, ml);
                } else if (strcmp(tokens[1], "-mmap") == 0) {
                    mem_alloc_mmap(tokens + 2, ntokens - 2, ml);
                } else if (strcmp(tokens[1], "-createshared") == 0) {
                    mem_alloc_createshared(tokens + 2, ntokens - 2, ml);
                } else if (strcmp(tokens[1], "-shared") == 0) {
                    mem_alloc_shared(tokens + 2, ntokens - 2, ml);
                } else {
                    printf("Error, check the arguments.\n");
                }
            }
        } else if (strcmp(tokens[0], "-dealloc") == 0) {
            if (ntokens == 1) {
                mem_dealloc();
            } else {
                if (strcmp(tokens[1], "-malloc") == 0) {
                    mem_dealloc_malloc(tokens + 2, ntokens - 2);
                } else if (strcmp(tokens[1], "-mmap") == 0) {
                    mem_dealloc_mmap(tokens + 2, ntokens - 2);
                } else if (strcmp(tokens[1], "-shared") == 0) {
                    mem_dealloc_shared(tokens + 2, ntokens - 2);
                } else {
                    mem_dealloc_addr(tokens[1]);
                }
            }
        } else if (strcmp(tokens[0], "-deletekey") == 0) {
            if (ntokens != 2) {
                printf("Error, check the arguments.\n");
            } else mem_deletekey(tokens[1]);
        } else if (strcmp(tokens[0], "-show") == 0) {
            mem_show(tokens + 1, ntokens - 1);
        } else if (strcmp(tokens[0], "-dopmap") == 0) {
            if (ntokens > 1) {
                printf("Error, check the arguments.\n");
            } else mem_dopmap();
        } else {
            printf("Error, check the arguments\n");
        }
    }
    return 1;
}

int memdump_cmd(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Memdump\n\n");
    return 1;
}

int memfill_cmd(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Memfill\n\n");
    return 1;
}

int recurse_cmd(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Recurse\n\n");
    return 1;
}

int readfile_cmd(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Readfile\n\n");
    return 1;
}

int writefile_cmd(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Writefile\n\n");
    return 1;
}

int mem_alloc_malloc(char **tokens, int ntokens, mem_list ml) {
    if (ntokens > 1) {
        printf("Take a look at the arguments, expecting one.\n");
        return -1;
    }
    if (ntokens == 0) {
        print_memlist(ml, "malloc");
        return 1;
    }
    unsigned long size = strtol(tokens[0], NULL, 10);
    if (size == 0) {
        printf("That doesn't seem like a valid size\n");
        return -1;
    }
    void *ptr = malloc(size);
    printf("malloc in %p\n", ptr);
    insert_in_memlist(ml, ptr, size, "malloc", "");
    return 1;
}

void *mmapfich(char* fichero, int protection, mem_list ml) {
    int df, map=MAP_PRIVATE, modo=O_RDONLY;
    struct stat s;
    void *p;
    if (protection&PROT_WRITE) modo = O_RDWR;
    if(stat(fichero, &s)== -1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap(NULL, s.st_size, protection, map, df, 0))==MAP_FAILED) { // TODO FIX THIS
        printf("%s\n",strerror(errno));
        return NULL;
    }
    char *params = malloc(20);
    sprintf(params, "(fd:%d)", df);
    insert_in_memlist(ml, p, s.st_size, "mmap", params);
    free(params);
    return p;
}

int mem_alloc_mmap(char **tokens, int ntokens, mem_list ml) {
    if (ntokens > 2) {
        printf("Take a look at the arguments, expecting one or two.\n");
        return -1;
    }
    if (ntokens == 0) {
        print_memlist(ml, "mmap");
        return 1;
    }
    char *perm;
    void *ptr;
    int prot = 0;
    if ((perm=tokens[1])!=NULL && strlen(perm)<4) {
        if (strchr(perm,'r')!=NULL) prot|=PROT_READ;
        if (strchr(perm,'w')!=NULL) prot|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) prot|=PROT_EXEC;
    }
    if ((ptr=mmapfich(tokens[0], prot, ml))==NULL)
        printf("Cannot map file.\n");
    else
        printf("mapped file in %p\n", ptr);
    return 1;
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam, mem_list ml){
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    if (tam) /*si tam no es 0 la crea en modo exclusivo */
        flags=flags | IPC_CREAT | IPC_EXCL;
            /*if tam = 0 try to access */
    if (clave==IPC_PRIVATE) /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno; /*si se ha creado y no se puede mapear*/
        if (tam) /*se borra */
            shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
    char temp[50];
    sprintf(temp,"key:%d",clave);
    insert_in_memlist(ml,p,tam,"shared",temp);
    return (p);
}


int mem_alloc_createshared(char **tokens, int ntokens, mem_list ml) {
    key_t k;
    size_t tam=0;
    void *p;
    if (tokens[0]==NULL || tokens[1]==NULL)
        {/*Listar Direcciones de Memoria Shared */ return;}
        k=(key_t) atoi(tokens[0]);
    if (tokens[1]!=NULL)
        tam=(size_t) atoll(tokens[1]);
    if ((p=ObtenerMemoriaShmget(k,tam,ml))==NULL)
        perror ("Imposible obtener memoria shmget");
    else
    printf ("Memoria de shmget de clave %d asignada en %p\n",k,p);
}

int mem_alloc_shared(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Alloc shared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_dealloc_malloc(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc malloc\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_dealloc_mmap(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc mmap\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_dealloc_shared(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc shared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_dealloc() {
    // TODO
    printf("List to dealloc\n");
    return 1;
}

int mem_dealloc_addr(char* address) {
    // TODO
    printf("Addres to dealloc: %s\n", address);
    return 1;
}

int mem_deletekey(char* key) {
    // TODO
    printf("Key to delete: %s\n", key);
    return 1;
}

int mem_show(char **tokens, int ntokens) {
    // TODO
    printf("Show memory\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_dopmap() {
    // TODO
    printf("Dopmap\n");
    return 1;
}
