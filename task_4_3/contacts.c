#include "contacts.h"

contacts_t contacts_init() {
  contacts_t contacts;
  contacts.root = NULL;

  return contacts;
}

node_t *node_new(person_t *person) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->left = new_node->right = NULL;
  new_node->height = 1;

  new_node->person = *person;

  return new_node;
}

size_t max(size_t a, size_t b) { return a > b ? a : b; }

size_t height(node_t *node) { return node ? node->height : 0; }

size_t balance_factor(node_t *node) {
  return height(node->right) - height(node->left);
}

void fix_height(node_t *node) {
  size_t height_left = height(node->left);
  size_t height_right = height(node->right);

  node->height = (height_left > height_right ? height_left : height_right) + 1;
}

node_t *rotate_right(node_t *node) {
  node_t *pivot = node->left;
  node->left = pivot->right;
  pivot->right = node;

  fix_height(node);
  fix_height(pivot);

  return pivot;
}

node_t *rotate_left(node_t *node) {
  node_t *pivot = node->right;
  node->right = pivot->left;
  pivot->left = node;

  fix_height(node);
  fix_height(pivot);

  return pivot;
}

node_t *balance(node_t *node) {
  fix_height(node);

  if (balance_factor(node) == 2) {
    if (balance_factor(node->right) < 0) {
      node->right = rotate_right(node->right);
    }

    return rotate_left(node);
  }

  if (balance_factor(node) == -2) {
    if (balance_factor(node->left) > 0) {
      node->left = rotate_left(node->left);
    }

    return rotate_right(node);
  }

  return node;
}

node_t *contacts_insert(node_t *node, person_t *person, bool *inserted) {
  if (!node)
    return node_new(person);

  int cmp = person_compare(person, &node->person);

  if (cmp == 0) {
    return node;
  }

  if (cmp < 0) {
    node->left = contacts_insert(node->left, person, inserted);
  }

  if (cmp > 0) {
    node->right = contacts_insert(node->right, person, inserted);
  }

  *inserted = true;
  return balance(node);
}

bool contacts_add(contacts_t *self, person_t person) {
  bool is_inserted = false;
  self->root = contacts_insert(self->root, &person, &is_inserted);

  return is_inserted;
}

node_t *find_min(node_t *node) {
  return node->left ? find_min(node->left) : node;
}

node_t *remove_min(node_t *node) {
  if (!node->left)
    return node->right;
  node->left = remove_min(node->left);

  return balance(node);
}

node_t *contacts_delete(node_t *node, name_t *name, bool *deleted) {
  if (!node) {
    return NULL;
  }

  int cmp = -1 * person_compare_by_name(&node->person, name);

  if (cmp < 0) {
    node->left = contacts_delete(node->left, name, deleted);
  } else if (cmp > 0) {
    node->right = contacts_delete(node->right, name, deleted);
  } else {
    node_t *l = node->left;
    node_t *r = node->right;

    free(node);

    if (!r)
      return l;
    node_t *min = find_min(r);
    min->right = remove_min(r);
    min->left = l;

    *deleted = true;
    return balance(min);
  }

  return balance(node);
}

bool contacts_remove(contacts_t *self, name_t *name) {
  bool is_deleted = false;

  self->root = contacts_delete(self->root, name, &is_deleted);
  return is_deleted;
}

node_t *find(node_t *node, name_t *name) {
  if (!node)
    return NULL;

  int cmp = -1 * person_compare_by_name(&node->person, name);

  if (cmp < 0) {
    return find(node->left, name);
  } else if (cmp > 0) {
    return find(node->right, name);
  } else {
    return node;
  }
}

person_t *contacts_find(contacts_t *self, name_t *name) {
  node_t *node = find(self->root, name);
  if (node) {
    return &node->person;
  } else {
    return NULL;
  }
}

void print(node_t *node) {
  if (!node)
    return;

  print(node->left);
  person_print(&node->person, 1);
  print(node->right);
}

void contacts_print(contacts_t *contacts) {
  printf("contacts = [\n");
  print(contacts->root);
  printf("]\n");
}

void destroy(node_t *node) {
  destroy(node->left);
  destroy(node->right);
  free(node);
}

void contacts_destroy(contacts_t *contacts) { destroy(contacts->root); }
