#include <stdarg.h>

double sub(int args_num, ...) {
  va_list args;
  va_start(args, args_num);

  double result = va_arg(args, double);
  for (; args_num > 1; args_num--) {
    result -= va_arg(args, double);
  }

  va_end(args);

  return result;
}
