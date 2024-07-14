#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

bool parse_ip(const char *str_ip, uint32_t *result) {
	uint8_t octet1, octet2, octet3, octet4;

	if (sscanf(str_ip, "%hhd.%hhd.%hhd.%hhd", &octet1, &octet2, &octet3, &octet4) != 4) {
		return false;
	}

	*result = ((uint32_t)octet1 << 24) | ((uint32_t)octet2 << 16) | ((uint32_t)octet3 << 8) | (uint32_t)octet4;
	return true;

}

char *convert_to_bin(uint32_t number) {
	char *result = malloc(sizeof(char) * 33);
	result[32] = 0;
	for (size_t i = 0; i < 32; i++) result[i] = '0';
	
	size_t i = 0;
	while (number > 0) {
		result[31 - i] = '0' + number % 2;
		i++;
		number /= 2;
	}

	return result;
}

bool is_in_subnet(uint32_t ip, uint32_t gateway, uint32_t mask) {
	return (ip & mask) == (gateway & mask);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("command template: %s gateway mask ips_count\n", argv[0]);
		return 1;
	}

	uint32_t gateway;
	if (!parse_ip(argv[1], &gateway)) {
		printf("invalid gateway ip\n");
		return 1;
	}

	uint32_t mask;
	if (!parse_ip(argv[2], &mask)) {
		printf("invalid mask ip\n");
		return 1;
	}


	char *errmsg;
	char *endptr;
	uint32_t ips_count = strtol(argv[3], &endptr, 10);

	if ((errno == ERANGE && (ips_count == LONG_MAX || ips_count == LONG_MIN)) || (errno != 0 && ips_count == 0)) {
		printf("invalid ips_count\n");
		return 1;
    	}

    	if (endptr == argv[3]) {
		printf("invalid ips_count\n");
		return 1;
    	}

	srand(time(NULL));
	size_t subnet_ips_count = 0;

	for (size_t i = 0; i < ips_count; i++) {
		uint32_t random_ip = ((uint32_t)rand() << 16) | rand();
		if (is_in_subnet(random_ip, gateway, mask)) {
			subnet_ips_count++;

		}
	}

	printf("submet ips: %d, %lf% \n", subnet_ips_count, subnet_ips_count / (double)ips_count * 100);
	printf("not submet ips: %d, %lf% \n", ips_count - subnet_ips_count, (ips_count - subnet_ips_count) / (double)ips_count * 100);

	return 0;
}
