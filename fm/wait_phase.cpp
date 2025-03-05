#include "wait_phase.hpp"

void wait_phase(Phase &phase, Flash &flash, BMP280 &bmp280, BNO055 &bno055) {
  // auto bmp_data = bmp280.read();
  // double altitude = bmp_data.altitude();
  auto bno_data = bno055.read(); //{accel,grv,mag}の順番で入っている想定
  double accel_abs =
      abs(bno_data.accel[0]) + abs(bno_data.accel[1]) + abs(bno_data.accel[2]);
  printf("accel_abs: %f\n", accel_abs);
  if (accel_abs > 20 /*&& altitude > 30*/) {
    phase = Phase::Fall;
    std::cout << "phase to fall!!" << std::endl;
    sleep_ms(5000);
  }
}