#include "bno055.hpp"

// Initialise Accelerometer Function
BNO055::BNO055(i2c_inst_t *i2c_port, uint8_t i2c_addr, Flash flash)
    : _i2c_port(i2c_port), _i2c_addr(i2c_addr) {
  // 接続が正常か確かめる
  const uint8_t reg = 0x00;
  uint8_t chipID[1];
  i2c_write_blocking(_i2c_port, _i2c_addr, &reg, 1, true);
  i2c_read_blocking(_i2c_port, _i2c_addr, chipID, 1, false);

  printf("bno055 chip id: 0x%X (0xAD is correct)\n", chipID[0]);

  // Use internal oscillator
  uint8_t data[2];
  data[0] = 0x3F;
  data[1] = 0x40;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);

  // Reset all interrupt status bits
  data[0] = 0x3F;
  data[1] = 0x01;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);

  // Configure Power Mode
  data[0] = 0x3E;
  data[1] = 0x00;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);
  sleep_ms(50);

  // Defaul Axis Configuration
  data[0] = 0x41;
  data[1] = 0x24;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);

  // Default Axis Signs
  data[0] = 0x42;
  data[1] = 0x00;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);

  // Set units to m/s^2
  data[0] = 0x3B;
  data[1] = 0b0001000;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);
  sleep_ms(30);

  // //モードをAMG(Accel Mag Gyro)に設定
  // data[0] = 0x3D;
  // data[1] = 0b0111;
  // i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);
  // sleep_ms(100);

  // モードをNDOFに設定
  // メモ:NDOFは加速度を分けれるFusion modeに対応している
  // また、Fusion Dataは地球の補正が入ったAbsolute orientationになっている
  // 解釈違いがあるかもなので詳しくはData Sheet p21~
  data[0] = 0x3D;
  data[1] = 0b1100;
  i2c_write_blocking(_i2c_port, _i2c_addr, data, 2, true);
  sleep_ms(100);

  // メモ:SC-17のコードでもdata[1] = 0x0C = (int)12となっている??
}

BNO055::~BNO055() {}

BNO055::Measurement_t BNO055::read(void) const {
  // read acceleration data
  uint8_t line_accel[6];
  i2c_write_blocking(_i2c_port, _i2c_addr, &LineAccelVal, 1, true);
  i2c_read_blocking(_i2c_port, _i2c_addr, line_accel, 6, false);

  int16_t line_accelX = ((line_accel[1] << 8) | line_accel[0]);
  int16_t line_accelY = ((line_accel[3] << 8) | line_accel[2]);
  int16_t line_accelZ = ((line_accel[5] << 8) | line_accel[4]);

  double d_line_accelX = line_accelX / 100.00;
  double d_line_accelY = line_accelY / 100.00;
  double d_line_accelZ = line_accelZ / 100.00;

  std::vector<double> line_accel_vector{d_line_accelX, d_line_accelY,
                                        d_line_accelZ};

  // read gravity data
  uint8_t grv[6];
  i2c_write_blocking(_i2c_port, _i2c_addr, &GrvVal, 1, true);
  i2c_read_blocking(_i2c_port, _i2c_addr, grv, 6, false);

  int16_t grvX = ((grv[1] << 8) | grv[0]);
  int16_t grvY = ((grv[3] << 8) | grv[2]);
  int16_t grvZ = ((grv[5] << 8) | grv[4]);

  double d_grvX = grvX / 100.00;
  double d_grvY = grvY / 100.00;
  double d_grvZ = grvZ / 100.00;

  std::vector<double> grv_vector{d_grvX, d_grvY, d_grvZ};

  // Read mag
  uint8_t mag[6];
  i2c_write_blocking(_i2c_port, _i2c_addr, &MagVal, 1, true);
  i2c_read_blocking(_i2c_port, _i2c_addr, mag, 6, false);
  int16_t magX = ((mag[1] << 8) | mag[0]);
  int16_t magY = ((mag[3] << 8) | mag[2]);
  int16_t magZ = ((mag[5] << 8) | mag[4]);

  double d_magX = magX / 16.00;
  double d_magY = magY / 16.00;
  double d_magZ = magZ / 16.00;

  std::vector<double> mag_vector{d_magX, d_magY, d_magZ};

  // // Read gyro data
  // i2c_write_blocking(_i2c_port, _i2c_addr, &GyroVal, 1, true);
  // i2c_read_blocking(_i2c_port, _i2c_addr, gyro, 6, false);
  // int16_t gyroX = ((gyro[1] << 8) | gyro[0]);
  // int16_t gyroY = ((gyro[3] << 8) | gyro[2]);
  // int16_t gyroZ = ((gyro[5] << 8) | gyro[4]);

  // double d_gyroX = gyroX / 900.00;
  // double d_gyroY = gyroY / 900.00;
  // double d_gyroZ = gyroZ / 900.00;

  // std::vector<double> gyro_vector{d_gyroX, d_gyroY, d_gyroZ};

  printf("bno055 accel: %f, %f, %f\n", line_accel_vector[0],
         line_accel_vector[1], line_accel_vector[2]);
  printf("bno055 grv: %f, %f, %f\n", grv_vector[0], grv_vector[1],
         grv_vector[2]);
  printf("bno055 mag: %f, %f, %f\n", mag_vector[0], mag_vector[1],
         mag_vector[2]);
  return {line_accel_vector, grv_vector, mag_vector};
}
