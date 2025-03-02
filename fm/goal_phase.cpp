#include "goal_phase.hpp"

void goal_phase(Phase &phase, BMP280 &bmp280, GPS &gps) {
  auto bmp_data = bmp280.read(); 
  s35_right.left_turn();
  s35_left.right_turn();
  double altitude = bmp_data.altitude;
  if (altitude <  5.0) {
    s35_right.stop_turn();
    s35_left.stop_turn();
  }
}