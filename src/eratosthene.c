#include <assert.h>
#include <stdlib.h>

#include "eratosthene.h"

void _mark_prime(PrimeGen prime_gen, prime_t n) {
  for (prime_t i = n * 2; i < prime_gen.max_prime; i += n) {
    prime_gen.buf[i] = 1;
  }
}

PrimeGen init_prime_gen(prime_t max_prime) {
  assert(max_prime > 2);

  PrimeGen prime_gen = {
      .max_prime = max_prime,
      .current = 1,
      .buf = (char *)calloc(max_prime, sizeof(char)),
  };

  if (prime_gen.buf == NULL) {
    return prime_gen;
  }

  _mark_prime(prime_gen, 2);

  return prime_gen;
}

void free_prime_gen(PrimeGen prime_gen) { free(prime_gen.buf); }

prime_t get_next_prime(PrimeGen *prime_gen) {
  while (prime_gen->current < prime_gen->max_prime &&
         prime_gen->buf[++prime_gen->current])
    ;

  if (prime_gen->current == prime_gen->max_prime) {
    return 0;
  }

  _mark_prime(*prime_gen, prime_gen->current);
  return prime_gen->current;
}
