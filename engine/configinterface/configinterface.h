#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H

#include <filesystem>

#include "configtypes.h"

class ConfigInterface {
 private:
  void initialize(toml::parse_result *toml);
  std::string currentSection;
  toml::parse_result toml;

 public:
  ConfigInterface(std::string pathToFile) {
    toml = toml::parse_file(pathToFile);
    initialize(&toml);
  }
  ConfigInterface(char *buf) {
    toml = toml::parse(std::string_view(buf));
    initialize(&toml);
  }
  bool beginSection(std::string sectionName);
  void endSection();
  std::string readValueFromCurrentSection(std::string key,
                                          std::string fallback);
  std::string readValueFromSection(std::string key, std::string section,
                                   std::string fallback);
  std::string readValue(std::string key, std::string fallback);
  ~ConfigInterface() { delete &toml; }
};
// TODO: implement all toml types not supported by stdlib; time and dates &
// abstractions for hashmaps (tables), vectors (arrays)
// there is no point to having them if they aren't any easier to use than the
// original; make them friendly
#endif  // CONFIGINTERFACE_H
