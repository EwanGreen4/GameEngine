#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

class Application {
public:
  Application();
  virtual ~Application();
  virtual bool beginMainLoop();
  virtual void argumentHandler(int, char *[]);
  virtual void log(bool isFatal, std::string contents);

  enum logFatality { LOG_FATAL = 0, LOG_NONFATAL = 1 };
  bool exitIsQueued = false;

protected:
  virtual bool tryInitializeRenderer();
  virtual bool tryInitializeAudio();
  virtual bool tryInitializeIO();

  virtual bool mainLoop();
  virtual void exit();
};

#endif // APPLICATION_H
