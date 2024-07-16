#include "person.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef TASK_4_3_LIST_H
#define TASK_4_3_LIST_H

typedef struct node_t {
    person_t person;

    struct node_t *left, *right;
    size_t height;
} node_t;

typedef struct {
    node_t *root;
} contacts_t;

contacts_t contacts_init();

bool contacts_add(contacts_t *self, person_t person);

bool contacts_remove(contacts_t *self, name_t *name);

person_t *contacts_find(contacts_t *self, name_t *name);

void contacts_print(contacts_t *contacts);

void contacts_destroy(contacts_t *self);

#endif
