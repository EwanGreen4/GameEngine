#include "application.h"

#include <thread>
#include <vector>

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

// TODO: create a suitable event scheduler
// void Application::schedule(void (*function)()) {
//  eventQueue.push_back(Event{function, nullptr});
//}
// void Application::eventPoll() {
//  while (eventQueue.size() > 0) {
//    struct Event e = eventQueue.at(eventQueue.size());
//    e.function();
//  }
//}
// struct arg {
//  typedef void *type;
//  void *value;
//};

// struct event {
//  void (*function)(...);
//  std::vector<arg> arguments;
//};

// extern std::vector<event> eventQueue;

bool Application::mainLoop() {
  while (!exitIsQueued) {
    log(LOG_FATAL, "Main loop has not been reimplemented!");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return EXIT_SUCCESS;
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
