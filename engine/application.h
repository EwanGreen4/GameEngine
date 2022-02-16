#ifndef APPLICATION_H
#define APPLICATION_H

#include <chrono>
#include <string>
#include <vector>

class Application {
public:
  Application();
  virtual ~Application();
  virtual bool beginMainLoop();
  virtual void argumentHandler(int, char *[]);
  virtual void log(bool isFatal, std::string contents);

  enum logFatality { LOG_FATAL = 0, LOG_NONFATAL = 1 };
  bool exitIsQueued = false;

  //  struct Arguments {
  //    void *data;
  //  };
  //  struct Event {
  //    void (*function)();
  //    std::vector<Arguments> *args;
  //  };

protected:
  //  std::vector<Event> eventQueue;
  virtual bool tryInitializeRenderer();
  virtual bool tryInitializeAudio();
  virtual bool tryInitializeIO();

  //  virtual void schedule(void (*function)());
  //  virtual void eventPoll();
  virtual bool mainLoop();
  virtual void exit();
};

#endif // APPLICATION_H
