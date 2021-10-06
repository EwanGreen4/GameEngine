#include "implementation.h"

int main(int argc, char *argv[]) {
  GameApplication app;
  int c = argc;
  char **v = argv;
  app.argumentHandler(c, v);
  if (app.beginMainLoop()) {
    app.log(1, "An error has occured.");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
