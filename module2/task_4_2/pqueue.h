#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef TASK_4_2_PQUEUE_H
#define TASK_4_2_PQUEUE_H

typedef struct node_t {
  void *data;

  struct node_t *next;
  uint8_t priority;
} node_t;

typedef struct {
  node_t fake_node;
} pqueue_t;

pqueue_t pqueue_init();

bool pqueue_insert(pqueue_t *self, uint8_t priority, void *data);

void *pqueue_extract_min(pqueue_t *self, uint8_t *priority);

void *pqueue_extract_by_priority(pqueue_t *self, uint8_t priority);

void *pqueue_extract_by_priority_gt_eq(pqueue_t *self, uint8_t priority,
                                       uint8_t *result_priority);

void pqueue_free(pqueue_t *self, void free_data(void *));

#endif
