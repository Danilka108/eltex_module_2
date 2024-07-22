#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

int main() {
  typedef enum {
    INSERT = 0,
    EXTRACT_MIN,
    EXTRACT_BY_PRIOR,
    EXTRACT_BY_PRIOR_GT_EQ,
  } action_t;

  pqueue_t pqueue = pqueue_init();

  while (true) {
    action_t action = (rand() % (EXTRACT_BY_PRIOR_GT_EQ + 1));

    switch (action) {
    case INSERT: {
      uint8_t *value = malloc(sizeof(uint8_t));
      *value = rand();
      uint8_t prior = rand();
      pqueue_insert(&pqueue, prior, value);

      printf("insert: %hhu, priority %hhu\n", *value, prior);
      break;
    }
    case EXTRACT_MIN: {
      uint8_t prior;
      uint8_t *data = pqueue_extract_min(&pqueue, &prior);

      if (data) {
        printf("extract min: %hhu, priority %hhu\n", *data, prior);
      } else {
        printf("extract min: NULL\n");
      }

      break;
    }
    case EXTRACT_BY_PRIOR: {
      uint8_t prior = rand();
      uint8_t *data = pqueue_extract_by_priority(&pqueue, prior);

      if (data) {
        printf("extract by prior: %hhu, priority %hhu\n", *data, prior);
      } else {
        printf("extract by prior: NULL, priority: %hhu\n", prior);
      }

      break;
    }
    case EXTRACT_BY_PRIOR_GT_EQ: {
      uint8_t prior = rand();
      uint8_t result_prior;
      uint8_t *data =
          pqueue_extract_by_priority_gt_eq(&pqueue, prior, &result_prior);

      if (data) {
        printf("extract by prior gt eq %hhu: %hhu, priority %hhu\n", prior,
               *data, result_prior);
      } else {
        printf("extract by prior gt eq %hhu: NULL\n", prior);
      }
      break;
    }
    }

    sleep(1);
  }

  pqueue_free(&pqueue, free);

  return 0;
}
