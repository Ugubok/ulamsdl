#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "eratosthene.h"

int main(int argc, char** argv) {
    prime_t max_prime = 1024 * 1024 * 128;

    if (argc > 1) {
        max_prime = atoll(argv[1]);
    }

    printf("Max prime is set to %llu", max_prime);

    PrimeGen prime_gen = init_prime_gen(max_prime);

    prime_t prime;

    while ((prime = get_next_prime(&prime_gen))) {
        printf("%llu\n", prime);
    }

    free_prime_gen(prime_gen);
}
