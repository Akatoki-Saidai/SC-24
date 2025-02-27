#ifndef BNO055_H
#define BNO055_H

#include <tuple>
#include <vector>
#include <iostream>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class BNO055{
public:
    BNO055();//コンストラクタ
    ~BNO055();//デストラクタ
    std::vector<std::vector<double>> read();
    //磁気、加速度、重力加速度を読み取る(ジャイロは必要だったら追加して)

private:
    const int addr = 0x28;  // I2Cアドレス
    i2c_inst_t* const i2c_port = i2c0;

    ////全加速度
    // uint8_t accel[6]; // Store data from the 6 acceleration registers
    // int16_t accelX, accelY, accelZ; // Combined 3 axis data
    // double d_accelX, d_accelY, d_accelZ; // double type of acceleration data
    // uint8_t accel_val = 0x08; // ACC_DATA_XLSB 0x08

    //磁気
    std::vector<double> mag_vector;   // magnetometer registers
    int16_t magX, magY, magZ;
    double d_magX, d_magY, d_magZ;
    const uint8_t mag_val = 0x0E; //MAG_DATA_XLSB 0x0E

    // //ジャイロセンサ
    // uint8_t gyro[6];
    // int16_t gyroX, gyroY, gyroZ;
    // double d_gyroX, d_gyroY, d_gyroZ;
    // uint8_t gyro_val = 0x14; //GYR_DATA_X_LSB 0x14

    //重力加速度
    std::vector<double> grv_vector;
    int16_t grvX, grvY, grvZ;
    double d_grvX, d_grvY, d_grvZ;
    const uint8_t grv_val = 0x2E; //GRV_DATA_X_LSB 0x2E

    //加速度
    std::vector<double> accel_vector;
    int16_t accelX, accelY, accelZ;
    double d_accelX, d_accelY, d_accelZ;
    const uint8_t accel_val = 0x28; //LIA_DATA_X_LSB 0x28
};

#endif