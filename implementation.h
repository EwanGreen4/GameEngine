#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <GameEngine>
#include <filesystem>
#include <iostream>
#include <fstream>

class GameApplication : public Application {

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;

  void exit() override;
  bool mainLoop() override;
};

#endif // IMPLEMENTATION_H
