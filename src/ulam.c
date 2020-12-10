#include "eratosthene.h"
#include <SDL2/SDL.h>

prime_t bottom_left_diagonal_value(int n) {
  const int b = 2;
  return (4 * n * n) + (b * n) + 1;
}

prime_t bottom_right_diagonal_value(int n) {
  const int b = 4;
  return (4 * n * n) + (b * n) + 2;
}

prime_t top_right_diagonal_value(int n) {
  const int b = 4;
  return (4 * n * n) + (b * n) + 1;
}

prime_t top_left_diagonal_value(int n) {
  const int b = 0;
  return (4 * n * n) + (b * n) + 1;
}

SDL_Point translate_x_y(int width, int height, prime_t n) {
  SDL_Point result = {0, 0};
  SDL_Point center = {width / 2, height / 2};

  int ring;
  for (ring = 0; bottom_right_diagonal_value(-ring) <= n; ring++) {
    // ↘
  }

  ring--;

  prime_t lt = top_left_diagonal_value(-ring);
  prime_t lb = bottom_left_diagonal_value(ring);
  prime_t rt = bottom_left_diagonal_value(-ring);
  prime_t rb = bottom_right_diagonal_value(-ring);

#ifdef DEBUG
  printf("%llu        %llu\n     %llu     \n%llu        %llu\n\n", lt, rt, n,
         lb, rb);
#endif

  if (n >= rb && n <= rt) { // ➡
#ifdef DEBUG
    printf("%llu        %llu\n          %llu\n%llu        %llu\n", lt, rt, n,
           lb, rb);
#endif

    result.x = ring;
    result.y = ring - 1;

    for (prime_t v = rb; v != n; v++) {
      result.y--;
    }
  } else if (n >= rt && n <= lt) { // ⬆
#ifdef DEBUG
    printf("%llu   %llu   %llu\n            \n%llu        %llu\n", lt, n, rt,
           lb, rb);
#endif

    result.y = -ring;
    result.x = ring;

    for (prime_t v = rt; v != n; v++) {
      result.x--;
    }
  } else if (n >= lt && n <= lb) { // ⬅
#ifdef DEBUG
    printf("%llu        %llu\n%llu          \n%llu        %llu\n", lt, rt, n,
           lb, rb);
#endif

    result.x = -ring;
    result.y = -ring;

    for (prime_t v = lt; v != n; v++) {
      result.y++;
    }
  } else if (n >= lb) { // ⬇
#ifdef DEBUG
    printf("%llu        %llu\n            \n%llu   %llu   %llu\n", lt, rt, lb,
           n, rb);
#endif
    result.y = ring;
    result.x = -ring;

    for (prime_t v = lb; v != n; v++) {
      result.x++;
    }
  }

  result.x += center.x;
  result.y += center.y;

#ifdef DEBUG
  printf("\n(%d, %d)\n", result.x, result.y);
  printf("==============================\n");
#endif

  return result;
}
