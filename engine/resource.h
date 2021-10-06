#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstring>
#include <string>
#include <vector>

#include "lib/microtar/microtar.h"

class Resource {

public:
  Resource();
  ~Resource();

  void *tarData;
  const char *
  getFile(const std::string name); // corresponds to file name (with prefixes)
  unsigned int getSize(const std::string name);
  unsigned long countFiles();

  //add public type wrapper method for getFileList()
  //add lots more error checking
  // add method to check file existence

private:
  struct fileContents {
    std::string name;
    unsigned int size;
  };

  mtar_t tarball;
  std::vector<fileContents> fileList;
  std::vector<fileContents> getFileList();
};

#endif // RESOURCE_H
