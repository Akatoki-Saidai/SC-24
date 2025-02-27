#ifndef SC24_FM_BNO055_HPP_
#define SC24_FM_BNO055_HPP_

#include <tuple>
#include <vector>
#include <iostream>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class BNO055{
    static constexpr uint8_t DefaultI2cAddr = 0x28;
public:
    BNO055(i2c_inst_t* i2c_port = i2c0, uint8_t i2c_addr = DefaultI2cAddr);//コンストラクタ
    ~BNO055();//デストラクタ
    std::vector<std::vector<double>> read();
    //磁気、加速度、重力加速度を読み取る(ジャイロは必要だったら追加して)
private:
    const uint8_t _i2c_addr;  // I2Cアドレス
    i2c_inst_t* const _i2c_port;  // I2Cポート i2c0かi2c1
    ////全加速度
    // uint8_t accel[6]; // Store data from the 6 acceleration registers
    // int16_t accelX, accelY, accelZ; // Combined 3 axis data
    // double d_accelX, d_accelY, d_accelZ; // double type of acceleration data
    // static constexpr uint8_t AccelVal = 0x08; // ACC_DATA_XLSB 0x08


    static constexpr uint8_t MagVal = 0x0E; //MAG_DATA_XLSB 0x0E

    // //ジャイロセンサ
    // uint8_t gyro[6];
    // int16_t gyroX, gyroY, gyroZ;
    // double d_gyroX, d_gyroY, d_gyroZ;
    // static constexpr uint8_t GyroVal = 0x14; //GYR_DATA_X_LSB 0x14

    //重力加速度
    std::vector<double> grv_vector;
    int16_t grvX, grvY, grvZ;
    double d_grvX, d_grvY, d_grvZ;
    static constexpr uint8_t GrvVal = 0x2E; //GRV_DATA_X_LSB 0x2E

    //線形加速度
    std::vector<double> line_accel_vector;
    int16_t line_accelX, line_accelY, line_accelZ;
    double d_line_accelX, d_line_accelY, d_line_accelZ;
    static constexpr uint8_t LineAccelVal = 0x28; //LIA_DATA_X_LSB 0x28
};

#endif  // SC24_FM_BNO055_HPP_