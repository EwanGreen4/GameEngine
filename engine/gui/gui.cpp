#include "gui.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>

gui::gui(int w, int h, int x, int y) {
  // TODO: create layout system & very basic style system based on images;
  // reimplementable
  SDL_Window *window = SDL_CreateWindow("urine", x, y, w, h, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RWops *rw = SDL_RWFromFile("/home/ewan/Pictures/sami.png", "rb");
  SDL_Surface *surface = IMG_LoadPNG_RW(rw);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
  SDL_UpdateWindowSurface(window);

  bool exitQueued = false;
  while (!exitQueued) {
  }
}
