#include "goal_phase.hpp"

void goal_phase(Phase &phase, BMP280 &bmp280, BNO055 &bno055, GPS &gps, const Servo &servo_r,const Servo &servo_l) {
  auto bmp_data = bmp280.read();
  // auto bno_data = bno055.read();
  servo_r.left_turn();
  servo_l.right_turn();//回転させる指示を何回も出したときどうなる?多分大丈夫だけど
  double altitude = bmp_data.altitude;
  // double accel_abs = abs(bno_data.accel[0]) + abs(bno_data.accel[1]) + abs(bno_data.accel[2]);
  if (altitude < 5.0 /*&& accel_abs < 2.0 [m/s^2]加速度の条件も追加したい */) {
    servo_r.stop_turn();
    servo_l.stop_turn();
  }
}