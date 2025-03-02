#include "goal_phase.hpp"

void goal_phase(Phase &phase, BMP280 &bmp280, GPS &gps, const Servo &servo_r,
                const Servo &servo_l) {
  auto bmp_data = bmp280.read();
  servo_r.left_turn();
  servo_l.right_turn();
  double altitude = bmp_data.altitude;
  if (altitude < 5.0) {
    servo_r.stop_turn();
    servo_l.stop_turn();
  }
}