#include "wait_phase.hpp"

void wait_phase(BMP280 &bmp280, BNO055 &bno055) {
  std::vector<std::vector<double>> bno_data =
      bno055.read(); //{accel,grv,mag}の順番で入っている想定
  double accel_abs =
      abs(bno_data[0][0]) + abs(bno_data[0][1]) + abs(bno_data[0][2]);
  if (accel_abs > 10 /*[m/s^2]*/) {
    // ここにフェーズを変えるコードを書く
  }
}