#ifndef SC24_FM_BNO055_HPP_
#define SC24_FM_BNO055_HPP_

#include <iostream>
#include <tuple>
#include <vector>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

class BNO055 {
  struct Measurement_t {
    std::vector<double> accel;
    std::vector<double> mag;
    std::vector<double> grav;
  };

public:
  BNO055(i2c_inst_t *i2c_port = i2c0,
         uint8_t i2c_addr = DefaultI2cAddr); // コンストラクタ
  ~BNO055();                                 // デストラクタ
  Measurement_t read() const;

private:
  static constexpr uint8_t DefaultI2cAddr = 0x28;
  i2c_inst_t *const _i2c_port; // I2Cポート i2c0かi2c1
  const uint8_t _i2c_addr;     // I2Cアドレス

  // static constexpr uint8_t AccelVal = 0x08; // ACC_DATA_XLSB 0x08
  static constexpr uint8_t MagVal = 0x0E; // MAG_DATA_XLSB 0x0E
  // static constexpr uint8_t GyroVal = 0x14; //GYR_DATA_X_LSB 0x14
  static constexpr uint8_t GrvVal = 0x2E;       // GRV_DATA_X_LSB 0x2E
  static constexpr uint8_t LineAccelVal = 0x28; // LIA_DATA_X_LSB 0x28
};

#endif // SC24_FM_BNO055_HPP_