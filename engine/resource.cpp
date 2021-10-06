#include "resource.h"
INCBIN(grc, "../data.grc");

std::vector<Resource::fileContents> Resource::getFileList() {

  char *rwx = nullptr;
  strcpy(rwx, tarData);

  mtar_mem_stream_t e;
  e.data = rwx;
  e.size = r_grcSize + 1;
  e.pos = 0;

  mtar_open_mem(&tarball, &e);
  std::vector<Resource::fileContents> list;
  mtar_header_t h;
  while ((mtar_read_header(&tarball, &h)) != MTAR_ENULLRECORD) {
    list.push_back(Resource::fileContents{h.name, h.size});
    mtar_next(&tarball);
  }
  return list;
}

Resource::Resource() {
  tarData = reinterpret_cast<const char *>(r_grcData);
  fileList = getFileList();
}

unsigned long Resource::countFiles() { return fileList.size(); }

Resource::~Resource() {
  mtar_close(&tarball);
  fileList.clear();
}

const char *Resource::getFile(const std::string name) {
  unsigned long e = fileList.size();
  for (unsigned long i = e; i > 0; i--) {
    if (fileList.at(i).name == name) {
      mtar_header_t h;
      char *contents = nullptr;
      mtar_find(&tarball, name.c_str(), &h);
      mtar_read_data(&tarball, contents, fileList.at(i).size + 1);
      return contents;
    }
  }
  return nullptr;
}

unsigned int Resource::getSize(const std::string name) {
  unsigned long e = fileList.size();
  for (unsigned long i = e; i > 0; i--) {
    if (fileList.at(i).name == name) {
      return fileList.at(i).size;
    }
  }
  return UINT_MAX;
}

// TODO: make sure this code works
