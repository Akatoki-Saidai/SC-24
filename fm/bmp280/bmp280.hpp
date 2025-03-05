#ifndef SC24_FM_BMP280_HPP_
#define SC24_FM_BMP280_HPP_

#include <cmath>
#include <iostream>
#include <string>
#include <tuple>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include "../flash/flash.hpp"

class BMP280 {
public:
  // 既にI2Cのセットアップが済んでいることを前提として，BMP280をセットアップ
  BMP280(Flash &flash, i2c_inst_t *i2c_port = i2c0,
         uint8_t i2c_addr = DefaultI2cAddr);

  struct Measurement_t {
    double pressure;
    double temperature;
    double humidity;
    double altitude;
  };

  // 気温と気圧を受信
  Measurement_t read();

private:
  Flash &_flash; // 出力用のフラッシュメモリ

  i2c_inst_t *const _i2c_port; // I2Cポート  i2c0かi2c1か
  const uint8_t _i2c_addr;     // I2Cアドレス
                           // (センサの電話番号みたいなもの．通信が誰宛かを示す)
  static constexpr uint8_t DefaultI2cAddr = 0x76;
  static constexpr uint8_t ChipIdRegister = 0xd0;
  // static constexpr uint8_t ReadBit = 0x80;  //
  // これはSPI通信で使用します．I2C通信では使用しません

  // I2CでBMP280にデータを書き込み
  void _write_register(uint8_t reg, uint8_t data) const;

  // I2CでBMP280からデータを読み込み
  void _read_registers(uint8_t reg, uint8_t *buf, uint16_t len) const;

  // BMP280から気温と気圧と湿度の生データを読み込み
  void _read_raw(int32_t *pressure, int32_t *temperature,
                 int32_t *humidity) const;

  // 補正用データを使用して，生データから気温を計算
  int32_t _compensate_temp(int32_t adc_T);

  // 補正用データを使用して，生データから気圧を計算
  uint32_t _compensate_pressure(int32_t adc_P) const;

  // 補正用データを使用して，生データから湿度を計算
  uint32_t _compensate_humidity(int32_t adc_H) const;

  // 補正用データを読み込んで保存
  void _read_compensation_parameters();

  // 気圧から高度を計算
  double _get_altitude(double pressure_hPa);

  // 高度0m地点の気圧を保存
  void _set_qnh();
  double _qnh = 1013.15; // 高度0m地点の気圧 (hPa)

  // 補正用データ
  // 気温用
  uint16_t _dig_T1;
  int16_t _dig_T2, _dig_T3;
  int32_t _t_fine;
  // 気圧用
  uint16_t _dig_P1;
  int16_t _dig_P2, _dig_P3, _dig_P4, _dig_P5, _dig_P6, _dig_P7, _dig_P8,
      _dig_P9;
  // 湿度用
  uint8_t dig_H1, dig_H3;
  int8_t dig_H6;
  int16_t dig_H2, dig_H4, dig_H5;
};

#endif // SC24_FM_BMP280_HPP_