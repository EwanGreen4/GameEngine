#include "resource.h"

#define INCBIN_PREFIX r_
#include "lib/incbin/incbin.h"
INCBIN(grc, "/home/ewan/GameEngine/data.grc");

std::vector<Resource::fileContents> Resource::getFileList() {

    char *tmp = reinterpret_cast<char *>(tarData);
    tmp[r_grcSize + 1] = '\0';

    mtar_mem_stream_t e;
    e.data = tmp;
    e.size = r_grcSize;
    e.pos = 0;

//    mtar_open_mem(&tarball, &e);
    mtar_open(&tarball, "../data.grc", "r"); // this works
    std::vector<Resource::fileContents> list;
    mtar_header_t h;
    while ((mtar_read_header(&tarball, &h)) != MTAR_ENULLRECORD) {
        list.push_back(Resource::fileContents{h.name, h.size});
        mtar_next(&tarball);
    }
    return list;
}

Resource::Resource() {
    tarData = calloc(1, r_grcSize);
    memcpy(tarData, r_grcData, r_grcSize);
    fileList = getFileList();
}

unsigned long Resource::countFiles() { return fileList.size(); }

Resource::~Resource() {
    mtar_close(&tarball);
    fileList.clear();
}

const char *Resource::getFile(const std::string name) {
    unsigned long e = fileList.size() - 1;
    for (unsigned long i = e; i >= 0; i--) {
        if (fileList.at(i).name == name) {

            mtar_header_t h;
            mtar_read_header(&tarball, &h);
            mtar_find(&tarball, name.c_str(), &h);
            char *contents = (char*)calloc(1, h.size + 1);

            mtar_read_data(&tarball, contents, h.size);
            return contents;
        }
    }
    return nullptr;
}

unsigned int Resource::getSize(const std::string name) {
    unsigned long e = fileList.size() - 1;
    for (unsigned long i = e; i >= 0; i--) {
        if (fileList.at(i).name == name) {
            return fileList.at(i).size;
        }
    }
    return UINT_MAX;
}

// TODO: make sure this code works
