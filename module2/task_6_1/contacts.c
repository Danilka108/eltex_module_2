#include "contacts.h"

contacts_t contacts_init() {
  contacts_t self;
  self.fake_node.next = NULL;
  self.fake_node.prev = NULL;

  return self;
}

bool contacts_add(contacts_t *self, person_t person) {
  contacts_node_t *new_node = malloc(sizeof(contacts_node_t));
  new_node->person = person;

  contacts_node_t *node = &self->fake_node;
  for (; node->next != NULL; node = node->next) {
    int comparision_result =
        person_compare(&node->next->person, &new_node->person);

    if (comparision_result == 0) {
      return false;
    }

    if (comparision_result < 0) {
      continue;
    }

    break;
  }

  if (node->next) {
    new_node->next = node->next;
    node->next->prev = new_node;
  }

  node->next = new_node;
  new_node->prev = node;

  return true;
}

bool contacts_remove(contacts_t *self, name_t *name) {
  contacts_node_t *node = &self->fake_node;
  for (; node->next != NULL; node = node->next) {
    if (person_compare_by_name(&node->next->person, name) == 0) {
      contacts_node_t *node_to_remove = node->next;

      node->next = node_to_remove->next;
      if (node_to_remove->next) {
        node_to_remove->next->prev = node;
      }

      free(node_to_remove);
      return true;
    }
  }

  return false;
}

person_t *contacts_find(contacts_t *self, name_t *name) {
  for (contacts_node_t *i = &self->fake_node; i->next != NULL; i = i->next) {
    contacts_node_t *node = i->next;

    if (person_compare_by_name(&node->person, name) == 0) {
      return &node->person;
    }
  }

  return NULL;
}

void contacts_print(contacts_t *contacts) {
  printf("contacts = [\n");

  for (contacts_node_t *i = &contacts->fake_node; i->next != NULL;
       i = i->next) {
    person_print(&i->next->person, 1);
  }

  printf("]\n");
}

void contacts_destroy(contacts_t *self) {
  contacts_node_t *node = &self->fake_node;

  while (node) {
    contacts_node_t *next = node->next;
    free(node);
    node = next;
  }

  self->fake_node.next = NULL;
}
