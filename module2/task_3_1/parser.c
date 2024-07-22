#include "parser.h"

bool parse_operation(mode_t *mode, const char *const src, size_t len) {
  size_t caret = 0;
  mode_t roles = 0, perms = 0;
  enum { OP_ADD, OP_SUB, OP_SET } op;

  while (true) {
    if (caret == len)
      return false;

    switch (src[caret]) {
    case 'u':
      roles |= S_IRUSR | S_IWUSR | S_IXUSR;
      ++caret;
      continue;
    case 'g':
      roles |= S_IRGRP | S_IWGRP | S_IXGRP;
      ++caret;
      continue;
    case 'o':
      roles |= S_IROTH | S_IWOTH | S_IXOTH;
      ++caret;
      continue;
    case 'a':
      roles = ~0;
      ++caret;
      continue;
    default:
      break;
    }

    break;
  }

  if (roles == 0) {
    roles = ~0;
  }

  switch (src[caret]) {
  case '+':
    op = OP_ADD;
    break;
  case '-':
    op = OP_SUB;
    break;
  case '=':
    op = OP_SET;
    break;
  default:
    return false;
  }
  ++caret;

  while (true) {
    if (caret == len) {
      break;
    }

    switch (src[caret]) {
    case 'r':
      perms |= S_IRUSR | S_IRGRP | S_IROTH;
      ++caret;
      continue;
    case 'w':
      perms |= S_IWUSR | S_IWGRP | S_IWOTH;
      ++caret;
      continue;
    case 'x':
      perms |= S_IXUSR | S_IXGRP | S_IXOTH;
      ++caret;
      continue;
    default:
      break;
    }

    break;
  }

  if (!perms || caret != len) {
    return false;
  }

  mode_t mask = roles & perms;

  switch (op) {
  case OP_ADD:
    *mode |= mask;
    break;
  case OP_SUB:
    *mode &= ~mask;
    break;
  case OP_SET:
    *mode = mask;
    break;
  }

  return true;
}
