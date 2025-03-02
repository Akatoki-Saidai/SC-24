#include "sd_card.hpp"

SD::SD() try {
  try {
    pSD = sd_get_by_num(0);

    fr = f_mount(&pSD->fatfs, pSD->pcName, 1);

    if (FR_OK != fr) {
      SD::save = false;
      printf("\n********************\n\n<<!! INIT ERRPR !!>> in %s line "
             "%d\n\n********************\n",
             __FILE__, __LINE__);
      printf("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    }
  } catch (const std::exception &e) {
    printf("\n********************\n\n<<!! INIT ERRPR !!>> in %s line "
           "%d\n%s\n\n********************\n",
           __FILE__, __LINE__, e.what());
  }
} catch (const std::exception &e) {
  printf("An initialization error occurred %s", e.what());
}

SD::~SD() { f_unmount(pSD->pcName); }

void SD::write(const std::string &write_str) {
  if (SD::save == false) {
    // throw std::runtime_error(f_err(__FILE__, __LINE__, "SD card is not
    // working properly"));  // SDカードは正常に動作していません
    return;
  }

  FIL fil;
  fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
  if (FR_OK != fr && FR_EXIST != fr) {
    SD::save = false;
    printf("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    return;
  }
  if (f_printf(&fil, write_str.c_str()) < 0) {
    SD::save = false;
    printf("f_printf failed\n");
    return;
  }
  fr = f_close(&fil);
  if (FR_OK != fr) {
    SD::save = false;
    printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    return;
  }
}