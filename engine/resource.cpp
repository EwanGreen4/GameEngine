#include "resource.h"

#include <fstream>
#include <iostream>

#define INCBIN_PREFIX r_
#include "lib/incbin/incbin.h"
INCBIN(grc, "../data.grc");

Resource::Resource() {
  tarData = malloc(r_grcSize);
  memcpy(tarData, r_grcData, r_grcSize);

  //  std::ofstream fe("./FUCK");

  mtar_mem_stream_t e;
  mtar_init_mem_stream(&e, tarData, r_grcSize);
  //  mtar_open_mem(&tarball, &e);
  mtar_open(&tarball, "../data.grc", "r");

  while ((mtar_read_header(&tarball, &header)) != MTAR_ENULLRECORD) {
    fileList.push_back(Resource::file{header.name, header.size});
    mtar_next(&tarball);
  }
}

unsigned long Resource::countFiles() { return fileList.size(); }

Resource::~Resource() {
  mtar_close(&tarball);
  fileList.clear();
}

const char *Resource::getFile(const std::string name) {
  unsigned long e = fileList.size() - 1;
  for (unsigned long i = 0; i < e; i++) {
    if (fileList.at(i).name == name) {
      mtar_find(&tarball, name.c_str(), &header);
      char *contents = static_cast<char *>(calloc(1, header.size));
      contents[header.size + 1] = '\0';
      mtar_read_data(&tarball, contents, header.size);
      return contents;
    }
  }
  return nullptr;
}

unsigned int Resource::getSize(const std::string name) {
  unsigned long e = fileList.size() - 1;
  for (unsigned long i = 0; i < e; i++) {
    if (fileList.at(i).name == name) {
      return fileList.at(i).size;
    }
  }
  return UINT_MAX;
}

// TODO: support multiple .grc files (like qrc)
//  TODO: make it not load all of the tarball into memory
//  TODO: make it actually work & ignore null terminating chars
//  TODO: potentially implement custom tar parser by virtue of below
//  https://techoverflow.net/2013/03/29/reading-tar-files-in-c/
