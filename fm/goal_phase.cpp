#include "goal_phase.hpp"

void goal_phase(Phase &phase, Flash &flash, BMP280 &bmp280, BNO055 &bno055,
                GPS &gps, const Servo &servo_r, const Servo &servo_l) {
  auto bmp_data = bmp280.read();
  auto bno_data = bno055.read();
  servo_r.left_turn();
  servo_l.right_turn();
  double altitude = bmp_data.altitude;
  if (altitude < 5.0 && abs_sum(bno_data.accel) < 1.0) {
    servo_r.stop_turn();
    servo_l.stop_turn();
    gpio_put(13, false);
  }
}