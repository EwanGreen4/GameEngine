#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdio.h>

#include <cstring>
#include <string>
#include <vector>

#include "lib/microtar/microtar.h"

class Resource {
 public:
  Resource();
  ~Resource();

  void *tarData;
  const char *getFile(const std::string name);
  unsigned int getSize(const std::string name);
  unsigned long countFiles();

  // TODO: add public type wrapper method for getFileList()
  // TODO: add lots more error checking
  // TODO: add method to check file existence

 private:
  struct file {
    std::string name;
    unsigned int size;
  };

  mtar_t tarball;
  mtar_header_t header;
  std::vector<file> fileList;
};

#endif  // RESOURCE_H
