#include "pqueue.h"

pqueue_t pqueue_init() {
  pqueue_t p;
  p.fake_node.next = NULL;

  return p;
}

bool pqueue_insert(pqueue_t *self, uint8_t priority, void *data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->next = NULL;
  new_node->data = data;
  new_node->priority = priority;

  node_t *node = &self->fake_node;
  for (; node->next != NULL; node = node->next) {
    if (new_node->priority > node->next->priority) {
      continue;
    }

    break;
  }

  new_node->next = node->next;
  node->next = new_node;

  return true;
}

void *pqueue_extract_min(pqueue_t *self, uint8_t *priority) {
  if (!self->fake_node.next)
    return NULL;

  node_t *node = self->fake_node.next;
  self->fake_node.next = node->next;

  if (priority)
    *priority = node->priority;
  void *data = node->data;

  free(node);
  return data;
}

void *pqueue_extract_by_priority(pqueue_t *self, uint8_t priority) {
  for (node_t *node = &self->fake_node; node->next != NULL; node = node->next) {
    if (node->next->priority == priority) {
      node_t *node_to_extract = node->next;
      node->next = node_to_extract->next;

      void *data = node_to_extract->data;
      free(node_to_extract);

      return data;
    }
  }

  return NULL;
}

void *pqueue_extract_by_priority_gt_eq(pqueue_t *self, uint8_t priority,
                                       uint8_t *result_priority) {
  for (node_t *node = &self->fake_node; node->next != NULL; node = node->next) {
    if (node->next->priority <= priority) {
      node_t *node_to_extract = node->next;
      node->next = node_to_extract->next;

      if (result_priority)
        *result_priority = node_to_extract->priority;
      void *data = node_to_extract->data;
      free(node_to_extract);

      return data;
    }
  }

  return NULL;
}

void pqueue_free(pqueue_t *self, void free_data(void *)) {
  while (self->fake_node.next) {
    node_t *node_to_free = self->fake_node.next;
    self->fake_node.next = node_to_free->next;

    free_data(node_to_free->data);
    free(node_to_free);
  }
}
