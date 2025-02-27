#ifndef SC24_FM_BMP280_HPP_
#define SC24_FM_BMP280_HPP_

#include <iostream>
#include <string>
#include <tuple>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class BMP280 {
public:
    // 既にI2Cのセットアップが済んでいることを前提として，BMP280をセットアップ
    BMP280(i2c_inst_t* i2c_port = i2c0, uint8_t i2c_addr = DefaultI2cAddr);
    
    // 気温と気圧を受信
    std::tuple<double, double> read();
private:
    i2c_inst_t* const _i2c_port;  // I2Cポート  i2c0かi2c1か
    const uint8_t _i2c_addr;  // I2Cアドレス (センサの電話番号みたいなもの．通信が誰宛かを示す)
    static constexpr uint8_t DefaultI2cAddr = 0x77;
    static constexpr uint8_t ChipIdRegister = 0xd0;
    static constexpr uint8_t ReadBit = 0x80;
    
    // I2CでBMP280にデータを書き込み
    void _write_register(uint8_t reg, uint8_t data);
    
    // I2CでBMP280からデータを読み込み
    void _read_registers(uint8_t reg, uint8_t *buf, uint16_t len);
    
    // BMP280から気温と気圧の生データを読み込み
    void _read_raw(int32_t *pressure, int32_t *temperature);
    
    // 補正用データを使用して，生データから気温を計算
    int32_t _compensate_temp(int32_t adc_T);

    // 補正用データを使用して，生データから気圧を計算
    uint32_t _compensate_pressure(int32_t adc_P);
    
    // 補正用データを読み込んで保存
    void _read_compensation_parameters();
    
    // 補正用データ
    int32_t _t_fine;
    uint16_t _dig_T1;
    int16_t _dig_T2, _dig_T3;
    uint16_t _dig_P1;
    int16_t _dig_P2, _dig_P3, _dig_P4, _dig_P5, _dig_P6, _dig_P7, _dig_P8, _dig_P9;
};

#endif  // SC24_FM_BMP280_HPP_