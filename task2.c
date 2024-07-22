#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef double (*operation_func)(int args_num, ...);

typedef struct {
	char description[64];
	operation_func func;

} Operation;

double sum(int args_num, ...) {
	va_list args;
	va_start(args, args_num);

	double result = va_arg(args, double);
	for (; args_num > 1; args_num--) {
		result += va_arg(args, double);
	}

	va_end(args);

	return result;
}

double sub(int args_num, ...) {
	printf("test\n\n");
	va_list args;
	va_start(args, args_num);

	double result = va_arg(args, double);
	for (; args_num > 1; args_num--) {
		result -= va_arg(args, double);
	}

	va_end(args);

	return result;
}

double div(int args_num, ...) {
	va_list args;
	va_start(args, args_num);

	double result = va_arg(args, double);
	for (; args_num > 1; args_num--) {
		result /= va_arg(args, double);
	}

	va_end(args);

	return result;
}

double mul(int args_num, ...) {
	va_list args;
	va_start(args, args_num);

	double result = va_arg(args, double);
	for (; args_num > 1; args_num--) {
		result *= va_arg(args, double);
	}

	va_end(args);
	va_end(args);

	return result;
}

size_t OPERATIONS_NUMBER = 4;
Operation OPERATIONS[4] = {
	{"sum", sum},
	{"subtraction", sub},
	{"division", div},
	{"multiplication", mul},
};

int main() {
	while (true) {
		printf("choose operation:\n");

		for (size_t i = 0; i < OPERATIONS_NUMBER; i++) {
			printf("\t%d - %s\n", i + 1, OPERATIONS[i].description);
		}

		int op;
		printf("> ");
		scanf("%d", &op);

		double args[6];
		int args_num;

		printf("arguments number: ");
		scanf("%d", &args_num);

		printf("arguments:\n");
		for (size_t i = 0; i < args_num; i++) {
			scanf("%lf", &args[i]);
		}

		switch (args_num) {
			case 1:
				printf("result = %lf\n", OPERATIONS[op - 1].func(1, args[0]));
				break;
			case 2:
				printf("result = %lf\n", OPERATIONS[op - 1].func(2, args[0], args[1]));
				break;
			case 3:
				printf("result = %lf\n", OPERATIONS[op - 1].func(3, args[0], args[1], args[2]));
				break;
			case 4:
				printf("result = %lf\n", OPERATIONS[op - 1].func(4, args[0], args[1], args[2], args[3]));
				break;
			case 5:
				printf("result = %lf\n", OPERATIONS[op - 1].func(5, args[0], args[1], args[2], args[3], args[4]));
				break;
			case 6:
				printf("result = %lf\n", OPERATIONS[op - 1].func(6, args[0], args[1], args[2], args[3], args[4], args[5]));
				break;
		}
	}

	return 0;
}
