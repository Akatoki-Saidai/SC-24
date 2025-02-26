#include "bno055.hpp"


// Initialise Accelerometer Function
BNO055::BNO055(void){
    // 接続が正常か確かめる
    sleep_ms(1000);
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    i2c_write_blocking(i2c_port, addr, &reg, 1, true);
    i2c_read_blocking(i2c_port, addr, chipID, 1, false);

    if(chipID[0] != 0xA0){
        while(1){
            printf("Chip ID Not Correct - Check Connection!");
            sleep_ms(5000);
        }
    }

    // Use internal oscillator
    uint8_t data[2];
    data[0] = 0x3F;
    data[1] = 0x40;
    i2c_write_blocking(i2c_port, addr, data, 2, true);

    // Reset all interrupt status bits
    data[0] = 0x3F;
    data[1] = 0x01;
    i2c_write_blocking(i2c_port, addr, data, 2, true);

    // Configure Power Mode
    data[0] = 0x3E;
    data[1] = 0x00;
    i2c_write_blocking(i2c_port, addr, data, 2, true);
    sleep_ms(50);

    // Defaul Axis Configuration
    data[0] = 0x41;
    data[1] = 0x24;
    i2c_write_blocking(i2c_port, addr, data, 2, true);

    // Default Axis Signs
    data[0] = 0x42;
    data[1] = 0x00;
    i2c_write_blocking(i2c_port, addr, data, 2, true);

    // Set units to m/s^2
    data[0] = 0x3B;
    data[1] = 0b0001000;
    i2c_write_blocking(i2c_port, addr, data, 2, true);
    sleep_ms(30);

    // //モードをAMG(Accel Mag Gyro)に設定
    // data[0] = 0x3D;
    // data[1] = 0b0111;
    // i2c_write_blocking(i2c_port, addr, data, 2, true);
    // sleep_ms(100);

    //モードをNDOFに設定
    //メモ:NDOFは加速度を分けれるFusion modeに対応している
    //また、Fusion Dataは地球の補正が入ったAbsolute orientationになっている
    //解釈違いがあるかもなので詳しくはData Sheet p21~
    data[0] = 0x3D;
    data[1] = 0b1100;
    i2c_write_blocking(i2c_port, addr, data, 2, true);
    sleep_ms(100);

    //メモ:SC-17のコードでもdata[1] = 0x0C = (int)12となっている??
}

BNO055::~BNO055() {
}

std::vector<std::vector<double>> BNO055::read(void) {
    //read acceleration data
    uint8_t accel[6];
    i2c_write_blocking(i2c_port, addr, &accel_val, 1, true);
    i2c_read_blocking(i2c_port, addr, accel, 6, false);

    accelX = ((accel[1]<<8) | accel[0]);
    accelY = ((accel[3]<<8) | accel[2]);
    accelZ = ((accel[5]<<8) | accel[4]);

    d_accelX = accelX / 100.00;
    d_accelY = accelY / 100.00;
    d_accelZ = accelZ / 100.00;

    accel_vector = {d_accelX,d_accelY,d_accelZ};

    //read gravity data
    uint8_t grv[6];
    i2c_write_blocking(i2c_port, addr, &grv_val, 1, true);
    i2c_read_blocking(i2c_port, addr, grv, 6, false);

    grvX = ((grv[1]<<8) | grv[0]);
    grvY = ((grv[3]<<8) | grv[2]);
    grvZ = ((grv[5]<<8) | grv[4]);

    d_grvX = grvX / 100.00;
    d_grvY = grvY / 100.00;
    d_grvZ = grvZ / 100.00;

    grv_vector = {d_grvX,d_grvY,d_grvZ};

    // Read magnetometer data
    uint8_t mag[6];
    i2c_write_blocking(i2c_port, addr, &mag_val, 1, true);
    i2c_read_blocking(i2c_port, addr, mag, 6, false);
    magX = ((mag[1] << 8) | mag[0]);
    magY = ((mag[3] << 8) | mag[2]);
    magZ = ((mag[5] << 8) | mag[4]);

    d_magX = magX / 16.00;
    d_magY = magY / 16.00;
    d_magZ = magZ / 16.00;

    mag_vector = {d_magX,d_magY,d_magZ};

    // // Read gyro data
    // i2c_write_blocking(i2c_port, addr, &gyro_val, 1, true);
    // i2c_read_blocking(i2c_port, addr, gyro, 6, false);
    // gyroX = ((gyro[1] << 8) | gyro[0]);
    // gyroY = ((gyro[3] << 8) | gyro[2]);
    // gyroZ = ((gyro[5] << 8) | gyro[4]);

    // d_gyroX = gyroX / 900.00;
    // d_gyroY = gyroY / 900.00;
    // d_gyroZ = gyroZ / 900.00;

    return {accel_vector,grv_vector,mag_vector};
}
