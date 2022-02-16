#include "configinterface.h"

void ConfigInterface::initialize(toml::parse_result *toml) {}

//--- Section

bool ConfigInterface::beginSection(std::string sectionName) {
  if (currentSection.empty()) {
    currentSection = sectionName;
    return 0;
  } else
    return 1;
}  /// Returns 1 if there is already a section in use.

void ConfigInterface::endSection() { currentSection = ""; }

std::string ConfigInterface::readValueFromCurrentSection(
    std::string key, std::string fallback = "invalid") {
  if (currentSection.empty())
    return fallback;
  else
    return toml[currentSection][key].value_or(fallback);
}

std::string ConfigInterface::readValueFromSection(std::string key,
                                                  std::string section,
                                                  std::string fallback) {
  std::string tmp = currentSection;
  endSection();
  beginSection(section);
  std::string value = readValueFromCurrentSection(key, fallback);
  endSection();
  beginSection(tmp);
  return value;
}

// TODO: make write functions

//--- Non-Section

std::string ConfigInterface::readValue(std::string key, std::string fallback) {
  return toml[key].value_or(fallback);
}

// TODO: make write functions
