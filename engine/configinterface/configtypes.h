#ifndef CONFIGTYPES_H
#define CONFIGTYPES_H

#include <ctime>

#include "lib/toml++/toml.h"

class Time {
 public:
  void setTime(int hour, int minute, int second, int millisecond) {
    h = hour;
    m = minute;
    s = second;
    ms = millisecond;
  }
  void setCurrentTime() {
    tm *localtime(const time_t *time);
    int e = time->tm_sec;

    // TODO: make this convertible to & from ctime and usable in the toml
    //  also add comparisons & distances in time and date and whatever

    // fuck ctime
  }
  int h = 0;
  int m = 0;
  int s = 0;
  int ms = 0;
};

class Date {
 public:
  Date() {}
  int y = 0;
  int m = 0;
  int d = 0;
};

class DateTime {
 public:
  DateTime() {}
  Date date;
  Time time;
};

// TODO: put date and time in their own files
#endif  // CONFIGTYPES_H
