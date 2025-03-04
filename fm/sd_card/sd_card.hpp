#ifndef SC19_PICO_SD_HPP_
#define SC19_PICO_SD_HPP_

#include <chrono>
#include <ctime>
#include <stdio.h>
#include <string>
//
#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"
//
#include "hw_config.h"

// class SD;

class SD {
  sd_card_t *pSD;
  FRESULT fr;
  //   std::string filename_str = std::string("log_") + __DATE__[4] +
  //   __DATE__[5] +
  //                              '_' + __TIME__[0] + __TIME__[1] + __TIME__[3]
  //                              +
  //                              __TIME__[4] + ".txt";
  const char *filename = "log.txt";

public:
  SD();

  ~SD();

  void write(const std::string &write_str);

  static inline bool save = true; // 正常に動作しているか
};

#endif // SC19_PICO_SD_HPP_