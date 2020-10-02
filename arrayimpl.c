#include <stdlib.h>
#include <memory.h>
#include "arrayimpl.h"

struct historic_struct {
    char* list[4096];
    int n_elem;
};


historic create_historic() {
    historic h = malloc(sizeof(struct historic_struct));
    h->n_elem = 0;
    return h;
}

void remove_historic(historic h) {
    for (int i = 0; i < h->n_elem; ++i) {
        free(h->list[i]);
    }
    free(h);
}

void insert_in_historic(historic h, char* e) {
    h->list[h->n_elem] = strdup(e);
    h->n_elem++;
}

void remove_from_historic(historic h, int n) {
    if (n >= h->n_elem) return;
    free(h->list[n]);
    for (int i = n; i < h->n_elem; ++i) {
        h->list[i] = h->list[i + 1];
    }
    h->n_elem--;
}

char* read_from_historic(historic h, int n) {
    if (n >= h->n_elem) return NULL;
    return h->list[n];
}

int n_elements_in_historic(historic h) {
    return h->n_elem;
}


