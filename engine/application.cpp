#include "application.h"

Application::Application() {}

Application::~Application() {}

bool Application::tryInitializeRenderer() {
  // TODO: implement default renderer
  return EXIT_SUCCESS;
}

bool Application::tryInitializeAudio() {
  // TODO: implement default audio
  return EXIT_SUCCESS;
}

bool Application::tryInitializeIO() {
  // TODO: implement default IO
  return EXIT_SUCCESS;
}

bool Application::mainLoop() {
  // TODO: add default mainloop with event scheduling
  log(LOG_FATAL, "Main loop has not been reimplemented!");
  return EXIT_FAILURE;
}

bool Application::beginMainLoop() {
  if (tryInitializeRenderer() && tryInitializeAudio() && tryInitializeIO())
    return EXIT_FAILURE;
  else {
    if (!mainLoop())
      return EXIT_SUCCESS;
    else
      return EXIT_FAILURE;
  }
}

void Application::argumentHandler(int, char *[]) {}
void Application::exit() {}

void Application::log(bool isFatal, std::string contents) {
  FILE *type;
  if (isFatal)
    type = stderr;
  else
    type = stdout;

  fputs(contents.c_str(), type);
}
