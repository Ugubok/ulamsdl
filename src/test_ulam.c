#include "eratosthene.h"
#include "ulam.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

static const int WIN_W = 640;
static const int WIN_H = 480;
static const SDL_Color COLOR_BG = {0x0C, 0x0E, 0x15, 255};
static const SDL_Color COLOR_FG = {0x78, 0xA4, 0xFF, 255};

typedef struct {
  bool done;
  SDL_Renderer *renderer;
} DrawingThreadOptions;

Uint32 color_to_rgba(SDL_Color color) {
  return color.a << 24 | color.b << 16 | color.g << 8 | color.r;
}

static int drawer(DrawingThreadOptions *options) {
  SDL_Renderer *renderer = options->renderer;
  SDL_Texture *texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, WIN_W, WIN_H);

  PrimeGen prime_gen = init_prime_gen(WIN_W * WIN_H);
  Uint32 pixels[WIN_W * WIN_H];

  int i = 0;

  for (int i = 0; i < WIN_W * WIN_H; i++) {
    pixels[i] = color_to_rgba(COLOR_BG);
  }

  while (!options->done) {
    prime_t n = get_next_prime(&prime_gen);

    if (!n) {
      break;
    }

    SDL_Point coord = translate_x_y(WIN_W, WIN_H, n);

    if (coord.x < 0 || coord.y < 0 || coord.x + 1 > WIN_W ||
        coord.y + 1 > WIN_H) {
      continue;
    }

    pixels[coord.y * WIN_W + coord.x] = color_to_rgba(COLOR_FG);

    if (++i % 1024 == 0) {
      SDL_UpdateTexture(texture, NULL, pixels, WIN_W * sizeof(Uint32));
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
  }

  if (!options->done) {
    SDL_UpdateTexture(texture, NULL, pixels, WIN_W * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  return 0;
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

#ifdef DEBUG
  SDL_Log("Debug enabled");
#endif

  SDL_Window *window = SDL_CreateWindow(
      "Ulam Spiral", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W,
      WIN_H, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);

  if (window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    SDL_Log("CreateRenderer: %s", SDL_GetError());
    return 1;
  }

  DrawingThreadOptions drawing_thread_options = {
      .done = false,
      .renderer = renderer,
  };

  SDL_Thread *drawing_thread = SDL_CreateThread(
      (SDL_ThreadFunction)drawer, "drawing thread", &drawing_thread_options);

  while (true) {
    SDL_Event e;

    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        break;
      }
    }
  }

  drawing_thread_options.done = true;
  SDL_WaitThread(drawing_thread, NULL);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  atexit(SDL_Quit);

  return 0;
}
