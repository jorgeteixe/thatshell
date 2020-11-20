/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */
#include <stdio.h>
#include <memory.h>
#include "memory.h"

int mem_alloc_malloc(char **tokens, int ntokens);
int mem_alloc_mmap(char **tokens, int ntokens);
int mem_alloc_createshared(char **tokens, int ntokens);
int mem_alloc_shared(char **tokens, int ntokens);

int mem_dealloc();
int mem_dealloc_addr(char* address);
int mem_dealloc_malloc(char **tokens, int ntokens);
int mem_dealloc_mmap(char **tokens, int ntokens);
int mem_dealloc_shared(char **tokens, int ntokens);

int mem_deletekey(char* key);

int mem_show(char **tokens, int ntokens);

int mem_dopmap();

int memory_cmd(char **tokens, int ntokens) {
    if (ntokens == 0) {
        printf("only memory\n");
    } else {
        if (strcmp(tokens[0], "-allocate") == 0) {
            if (ntokens == 1) {
                printf("Error, check the arguments.\n");
            } else {
                if (strcmp(tokens[1], "-malloc") == 0) {
                    mem_alloc_malloc(tokens + 2, ntokens - 2);
                } else if (strcmp(tokens[1], "-mmap") == 0) {
                    mem_alloc_mmap(tokens + 2, ntokens - 2);
                } else if (strcmp(tokens[1], "-createshared") == 0) {
                    mem_alloc_createshared(tokens + 2, ntokens - 2);
                } else if (strcmp(tokens[1], "-shared") == 0) {
                    mem_alloc_shared(tokens + 2, ntokens - 2);
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

int memdump_cmd(char **tokens, int ntokens) {
    // TODO
    printf("Memdump\n\n");
    return 1;
}

int memfill_cmd(char **tokens, int ntokens) {
    // TODO
    printf("Memfill\n\n");
    return 1;
}

int recurse_cmd(char **tokens, int ntokens) {
    // TODO
    printf("Recurse\n\n");
    return 1;
}

int readfile_cmd(char **tokens, int ntokens) {
    // TODO
    printf("Readfile\n\n");
    return 1;
}

int writefile_cmd(char **tokens, int ntokens) {
    // TODO
    printf("Writefile\n\n");
    return 1;
}

int mem_alloc_malloc(char **tokens, int ntokens) {
    // TODO
    printf("Alloc malloc\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_alloc_mmap(char **tokens, int ntokens) {
    // TODO
    printf("Alloc mmap\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_alloc_createshared(char **tokens, int ntokens) {
    // TODO
    printf("Alloc createshared\n");
    if (ntokens == 0) printf("No tokens received");
    for (int i = 0; i < ntokens; ++i) {
        printf("arg %d: %s\n",i,  tokens[i]);
    }
    return 1;
}

int mem_alloc_shared(char **tokens, int ntokens) {
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
