#include "parser.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_mode(mode_t mode) {
  for (size_t i = 9; i > 0; --i) {
    printf("%c", 1 & mode >> (i - 1) ? '1' : '0');
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "%s: expected mode and file name\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[argc - 1];
  struct stat stat_buff;

  if (stat(filename, &stat_buff) != 0) {
    fprintf(stderr, "%s: Cannot access '%s': %s\n", argv[0], filename,
            strerror(errno));
    return EXIT_FAILURE;
  }

  mode_t mode = stat_buff.st_mode;
  for (size_t i = 1; i < argc - 1; ++i) {
    if (!parse_operation(&mode, argv[i], strlen(argv[i]))) {
      fprintf(stderr, "%s: Invalid mode value", argv[0]);
      return EXIT_FAILURE;
    }
  }

  printf("initial mode: ");
  print_mode(stat_buff.st_mode);
  printf("\n");

  printf("new mode: ");
  print_mode(mode);
  printf("\n");

  return EXIT_SUCCESS;
}
