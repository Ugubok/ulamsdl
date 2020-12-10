#ifndef _ERATOSTHENE_H
#define _ERATOSTHENE_H

typedef unsigned long long prime_t;

typedef struct {
  const prime_t max_prime;
  prime_t current;
  char *buf;
} PrimeGen;

PrimeGen init_prime_gen(prime_t max_prime);
void free_prime_gen(PrimeGen);
prime_t get_next_prime(PrimeGen *);

#endif
