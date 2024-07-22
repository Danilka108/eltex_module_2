#include <dlfcn.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

typedef double (*operation_func)(int args_num, ...);

typedef struct {
  char description[64];
  char libpath[64];
  char funcname[64];
  void *handle;
  operation_func func;
} operation_t;

size_t OPERATIONS_NUMBER = 4;
operation_t OPERATIONS[4] = {
    {"sum", "./libsum.so", "sum", NULL, NULL},
    {"subtraction", "./libsub.so", "sub", NULL, NULL},
    {"division", "./libdiv.so", "div", NULL, NULL},
    {"multiplication", "./libmul.so", "mul", NULL, NULL},
};

int main() {
  while (true) {
    printf("choose operation:\n");

    for (size_t i = 0; i < OPERATIONS_NUMBER; i++) {
      printf("\t%lu - %s\n", i + 1, OPERATIONS[i].description);
    }

    int op_num;
    printf("> ");
    scanf("%d", &op_num);

    double args[6];
    size_t args_num;

    printf("arguments number: ");
    scanf("%lu", &args_num);

    printf("arguments:\n");
    for (size_t i = 0; i < args_num; i++) {
      scanf("%lf", &args[i]);
    }

    operation_t *op = &OPERATIONS[op_num - 1];

    if (!op->handle)
      op->handle = dlopen(op->libpath, RTLD_LAZY);
    printf("%p\n", op->handle);
    if (!op->func)
      op->func = dlsym(op->handle, op->funcname);

    switch (args_num) {
    case 1:
      printf("result = %lf\n", op->func(1, args[0]));
      break;
    case 2:
      printf("result = %lf\n", op->func(2, args[0], args[1]));
      break;
    case 3:
      printf("result = %lf\n", op->func(3, args[0], args[1], args[2]));
      break;
    case 4:
      printf("result = %lf\n", op->func(4, args[0], args[1], args[2], args[3]));
      break;
    case 5:
      printf("result = %lf\n",
             op->func(5, args[0], args[1], args[2], args[3], args[4]));
      break;
    case 6:
      printf("result = %lf\n",
             op->func(6, args[0], args[1], args[2], args[3], args[4], args[5]));
      break;
    }
  }

  for (size_t i = 0; i < OPERATIONS_NUMBER; i++) {
    if (OPERATIONS[i].handle)
      dlclose(OPERATIONS[i].handle);
  }

  return 0;
}
