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
    void accel_init(void);
    std::vector<std::vector<float>> read();
    //磁気、加速度、重力加速度を読み取る(ジャイロは必要だったら追加して)

private:
    ////全加速度
    // uint8_t accel[6]; // Store data from the 6 acceleration registers
    // int16_t accelX, accelY, accelZ; // Combined 3 axis data
    // float f_accelX, f_accelY, f_accelZ; // Float type of acceleration data
    // uint8_t accel_val = 0x08; // ACC_DATA_XLSB 0x08

    //磁気
    std::vector<float> mag_vector;   // magnetometer registers
    int16_t magX, magY, magZ;
    float f_magX, f_magY, f_magZ;
    uint8_t mag_val = 0x0E; //MAG_DATA_XLSB 0x0E

    // //ジャイロセンサ
    // uint8_t gyro[6];
    // int16_t gyroX, gyroY, gyroZ;
    // float f_gyroX, f_gyroY, f_gyroZ;
    // uint8_t gyro_val = 0x14; //GYR_DATA_X_LSB 0x14

    //重力加速度
    std::vector<float> grv_vector;
    int16_t grvX, grvY, grvZ;
    float f_grvX, f_grvY, f_grvZ;
    uint8_t grv_val = 0x2E; //GRV_DATA_X_LSB 0x2E

    //加速度
    std::vector<float> accel_vector;
    int16_t accelX, accelY, accelZ;
    float f_accelX, f_accelY, f_accelZ;
    uint8_t accel_val = 0x28; //LIA_DATA_X_LSB 0x28

    //アドレス
    int addr = 0x28;
};

#endif