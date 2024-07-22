#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>

#ifndef TASK_3_1_PARSER_H
#define TASK_3_1_PARSER_H

bool parse_operation(mode_t *mode, const char *const src, size_t len);

#endif
