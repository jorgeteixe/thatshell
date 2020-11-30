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
#include <ctype.h>
#include "memory.h"
#include "listmem.h"

int mem_alloc_malloc(char **tokens, int ntokens, mem_list ml);

int mem_alloc_mmap(char **tokens, int ntokens, mem_list ml);

int mem_alloc_createshared(char **tokens, int ntokens, mem_list ml);

int mem_alloc_shared(char **tokens, int ntokens, mem_list ml);

int mem_dealloc();

int mem_dealloc_addr(char *address);

int mem_dealloc_malloc(char **tokens, int ntokens);

int mem_dealloc_mmap(char **tokens, int ntokens);

int mem_dealloc_shared(char **tokens, int ntokens);

int mem_deletekey(char *key);

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
    long tam = 25;
    if (ntokens == 0) {
        printf("Should receive a valid address.\n");
        return -1;
    }
    if (ntokens > 2) {
        printf("Error, check the arguments.\n");
        return -1;
    }
    if (ntokens == 2) tam = strtol(tokens[1], NULL, 10);
    if (tam <= 0) tam = 25;
    char *ptr = (char *) strtol(tokens[0], NULL, 16);
    int pos = 0;
    for (int i = 0; i < tam * 2; i++) {
        if (i != 0 && i % 25 == 0) {
            printf("\n");
            pos = pos - 25;
        }
        if (i != 0 && i % 50 == 0) pos = pos + 25;
        if (i / (float) 50 - i / 50 < 0.5) {
            if (isprint(ptr[pos])) {
                printf("%3c", ptr[pos]);
            } else printf("%3c", ' ');
        } else {
            printf(" %02hhX", ptr[pos]);
        }
        pos++;
    }
    printf("\n");
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

void *mmapfich(char *fichero, int protection, mem_list ml) {
    int df, map = MAP_PRIVATE, modo = O_RDONLY;
    struct stat s;
    void *p;
    if (protection & PROT_WRITE) modo = O_RDWR;
    if (stat(fichero, &s) == -1 || (df = open(fichero, modo)) == -1)
        return NULL;
    if ((p = mmap(NULL, s.st_size, protection, map, df, 0)) == MAP_FAILED) {
        //printf("%s\n",strerror(errno));
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
    if ((perm = tokens[1]) != NULL && strlen(perm) < 4) {
        if (strchr(perm, 'r') != NULL) prot |= PROT_READ;
        if (strchr(perm, 'w') != NULL) prot |= PROT_WRITE;
        if (strchr(perm, 'x') != NULL) prot |= PROT_EXEC;
    }
    if ((ptr = mmapfich(tokens[0], prot, ml)) == NULL)
        printf("Cannot map file.\n");
    else
        printf("mapped file in %p\n", ptr);
    return 1;
}

int mem_alloc_createshared(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Alloc createshared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_alloc_shared(char **tokens, int ntokens, mem_list ml) {
    // TODO
    printf("Alloc shared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_dealloc_malloc(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc malloc\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_dealloc_mmap(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc mmap\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_dealloc_shared(char **tokens, int ntokens) {
    // TODO
    printf("Dealloc shared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_dealloc() {
    // TODO
    printf("List to dealloc\n");
    return 1;
}

int mem_dealloc_addr(char *address) {
    // TODO
    printf("Addres to dealloc: %s\n", address);
    return 1;
}

int mem_deletekey(char *key) {
    // TODO
    printf("Key to delete: %s\n", key);
    return 1;
}

int mem_show(char **tokens, int ntokens) {
    // TODO
    printf("Show memory\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n", i, tokens[i]);
    }
    return 1;
}

int mem_dopmap() {
    // TODO
    printf("Dopmap\n");
    return 1;
}
