#include "wait_phase.hpp"

void wait_phase(Phase &phase, BMP280 &bmp280, const BNO055 &bno055) {
  auto bno_data = bno055.read(); //{accel,grv,mag}の順番で入っている想定
  double accel_abs =
      abs(bno_data.accel[0]) + abs(bno_data.accel[1]) + abs(bno_data.accel[2]);
  if (accel_abs > 10 /*[m/s^2]*/) {
    // ここにフェーズを変えるコードを書く
  }
}