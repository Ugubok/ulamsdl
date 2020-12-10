#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_W 640
#define WINDOW_H 320

// AABBGGRR
// WHITE AND BLACK
#define W 0x00FFFFFF
#define B 0x00000000

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO))
    exit(1);

  /* Set up main window. */
  SDL_Window *window = SDL_CreateWindow(
      "Texture Streaming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
  if (window == NULL)
    exit(2);

  /* Set up renderer. */
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    exit(3);

  SDL_Event ev;
  int window_running = 1;

  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                           SDL_TEXTUREACCESS_STATIC, 64, 32);
  Uint32 pixels[64 * 32] = {W};

  for (int i = 0; i < (64 * 32); i += 2)
    pixels[i] = 0xFF00FFFF;

  for (int i = 0; i < 64; i++)
    pixels[i] = W;

  SDL_UpdateTexture(texture, NULL, pixels, 64 * 4);

  while (window_running) {
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT)
        window_running = 0;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
