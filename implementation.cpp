#include "implementation.h"

void GameApplication::exit() {
  SDL_free(window);
  SDL_free(renderer);
}
bool GameApplication::mainLoop() {

  bool finishedNaturally = true;
  int windowWidth = 320, windowHeight = 240;

  int imgFlags = IMG_INIT_PNG;
  uint32_t sdlFlags = SDL_WINDOW_SHOWN;
  SDL_Init(sdlFlags);
  IMG_Init(imgFlags);
  std::string path = std::filesystem::current_path().string();
  window =
      SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  Resource rc;
  int bmageSize = static_cast<int>(rc.getSize("bmage.png"));
  const char *bmageData = rc.getFile("bmage.png");
      SDL_RWops bmageFp(*SDL_RWFromConstMem(bmageData, bmageSize));

  int imageSize = static_cast<int>(rc.getSize("image.png"));
  const char *imageData = rc.getFile("image.png");

  log(LOG_NONFATAL, rc.getFile("test/test.txt"));
  log(LOG_NONFATAL, std::to_string(rc.getSize("test/test.txt")) + " bytes\n");

  SDL_RWops imageFp(*SDL_RWFromConstMem(imageData, imageSize));

  SDL_Surface *z = IMG_LoadPNG_RW(&bmageFp);
  SDL_Surface *s = IMG_LoadPNG_RW(&imageFp);

  texture = SDL_CreateTextureFromSurface(renderer, s);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
  SDL_Event evt;

  bool isGreen = false;
  log(LOG_NONFATAL, "start\n");
  while (!exitIsQueued) {
    while (SDL_PollEvent(&evt)) {
      switch (evt.type) {
      case SDL_QUIT:
        exitIsQueued = true;
        break;
      case SDL_WINDOWEVENT_HIDDEN:
        SDL_MinimizeWindow(window);
        break;
      case SDL_WINDOWEVENT_SHOWN:
        SDL_UpdateWindowSurface(window);
        break;
      case SDL_KEYDOWN:
        if (evt.key.keysym.sym == SDL_GetKeyFromScancode(SDL_SCANCODE_Z)) {
          if (isGreen) {
            texture = SDL_CreateTextureFromSurface(renderer, s);
          } else {
            texture = SDL_CreateTextureFromSurface(renderer, z);
          }
          isGreen = !isGreen;
          SDL_RenderCopy(renderer, texture, nullptr, nullptr);
          SDL_RenderPresent(renderer);
        }
        break;
      }
    }
    SDL_UpdateWindowSurface(window);
  }
  exit();
  if (finishedNaturally)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
