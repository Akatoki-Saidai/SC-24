/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bmp280.hpp"

/* Example code to talk to a bmp280 temperature/pressure sensor.

   NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefor SPI) cannot be used at 5v.

   GPIO 8 (pin 11)-> SDA on bmp280 board
   GPIO 9 (pin 12)-> SCL on bmp280 board
   3.3v (pin 3;6) -> VCC on bmp280 board
   GND (pin 38)  -> GND on bmp280 board

*/

// 既にI2Cのセットアップが済んでいることを前提として，BMP280をセットアップ
BMP280::BMP280(i2c_inst_t *i2c_port, uint8_t i2c_addr)
    : _i2c_port(i2c_port), _i2c_addr(i2c_addr) {
  printf("bmp280 start init\n");
  // stdio_init_all();
  // i2c_init(_i2c_port, 100 * 1000);
  // gpio_set_function(8, GPIO_FUNC_I2C);  // SDAのピン番号を設定
  // gpio_set_function(9, GPIO_FUNC_I2C);  // SCLのピン番号を設定
  // gpio_pull_up(8);
  // gpio_pull_up(9);
  sleep_ms(100);
  _write_register(0xE0, 0xB6);
  sleep_ms(100);
  uint8_t id;
  _read_registers(ChipIdRegister, &id, 1); // チップIDを読み取り
  printf("bmp280 chip id: 0x%X (0x58 is correct)\n", id);

  _write_register(
      0xF4, 0x27); // オーバーサンプリングと電源モードを設定
                   // (0x27なら気温と気圧を1回ずつ測定，電源モードはNormal)
  // _write_register(0xF4, 0b00101000);  //
  // オーバーサンプリングと電源モードを設定
  // (0x27なら気温と気圧を1回ずつ測定，電源モードはNormal)
  _write_register(0xF5, 0x20); // 測定間隔とノイズ除去フィルターを設定
                               // (0x20なら62.5ms間隔で，ノイズ除去なし)
  // _write_register(0xF5, 0b00100100);  // 測定間隔とノイズ除去フィルターを設定
  // (0x20なら62.5ms間隔で，ノイズ除去なし)
  sleep_ms(100);
  _read_compensation_parameters(); // 補正用データを読み取り

  // 何回か空測定
  printf("bmp280 start initial measurement\n");
  for (int i = 0; i < 20; ++i) {
    read();
    sleep_ms(100);
  }
  printf("bmp280 finish initial measurement\n");

  printf("bmp280 finish init\n");
}

// 気温と気圧を受信
std::tuple<double, double> BMP280::read() {
  int32_t pressure, temperature, humidity;
  _read_raw(&pressure, &temperature, &humidity);
  pressure = _compensate_pressure(pressure);
  temperature = _compensate_temp(temperature);
  humidity = _compensate_humidity(humidity);

  printf("bmp280 press: %f, temp: %f, humidith: %f\n", pressure / 100.0,
         temperature / 100.0, humidity / 1024.0);
  return std::make_tuple<double, double>(pressure / 100.0, temperature / 100.0);
}

// I2CでBMP280にデータを書き込み
void BMP280::_write_register(uint8_t reg, uint8_t data) {
  uint8_t buf[2];
  buf[0] = reg;
  // buf[0] &= 0x7f;  //
  // <==これはSPI通信のときのみ使用します．I2C通信では使用しません！
  buf[1] = data; // 続いて1バイトのデータを送信
  i2c_write_blocking(_i2c_port, _i2c_addr, buf, 2, false);
}

// I2CでBMP280からデータを読み込み
void BMP280::_read_registers(uint8_t reg, uint8_t *buf, uint16_t len) {
  // For this particular device, we send the device the register we want to read
  // first, then subsequently read from the device. The register is auto
  // incrementing so we don't need to keep sending the register we want, just
  // the first. reg = reg | ReadBit;  //
  // <==これはSPI通信のときのみ使用します．I2C通信では使用しません！
  i2c_write_blocking(_i2c_port, _i2c_addr, &reg, 1, true);
  i2c_read_blocking(_i2c_port, _i2c_addr, buf, len, false);
}

// BMP280から気温と気圧の生データを読み込み
void BMP280::_read_raw(int32_t *pressure, int32_t *temperature,
                       int32_t *humidity) {
  uint8_t buffer[8];
  _read_registers(0xF7, buffer, 6); // 6バイトの気温と気圧の生データを読み込み

  printf("bmp280 raw: %d, %d, %d, %d, %d, %d\n", buffer[0], buffer[1],
         buffer[2], buffer[3], buffer[4], buffer[5]);

  // 生データを引数の指すポインタに保存
  *pressure = ((uint32_t)buffer[0] << 12) | ((uint32_t)buffer[1] << 4) |
              (buffer[2] >> 4);
  *temperature = ((uint32_t)buffer[3] << 12) | ((uint32_t)buffer[4] << 4) |
                 (buffer[5] >> 4);
  *humidity = (uint32_t)buffer[6] << 8 | buffer[7];
}

// 補正用データを使用して，生データから気温を計算
int32_t BMP280::_compensate_temp(int32_t adc_T) {
  int32_t var1, var2, t;
  var1 =
      ((((adc_T >> 3) - ((int32_t)_dig_T1 << 1))) * ((int32_t)_dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((int32_t)_dig_T1)) *
            ((adc_T >> 4) - ((int32_t)_dig_T1))) >>
           12) *
          ((int32_t)_dig_T3)) >>
         14;

  _t_fine = var1 + var2;
  t = (_t_fine * 5 + 128) >> 8;
  return t;
}

// 補正用データを使用して，生データから気圧を計算
uint32_t BMP280::_compensate_pressure(int32_t adc_P) {
  int32_t var1, var2;
  uint32_t p;
  var1 = (((int32_t)_t_fine) >> 1) - (int32_t)64000;
  var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)_dig_P6);
  var2 = var2 + ((var1 * ((int32_t)_dig_P5)) << 1);
  var2 = (var2 >> 2) + (((int32_t)_dig_P4) << 16);
  var1 = (((_dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
          ((((int32_t)_dig_P2) * var1) >> 1)) >>
         18;
  var1 = ((((32768 + var1)) * ((int32_t)_dig_P1)) >> 15);
  if (var1 == 0)
    return 0;

  p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2 >> 12))) * 3125;
  if (p < 0x80000000) {
    p = (p << 1) / ((uint32_t)var1);
  } else {
    p = (p / (uint32_t)var1) * 2;
  }

  var1 = (((int32_t)_dig_P9) * ((int32_t)(((p >> 3) * (p >> 3)) >> 13))) >> 12;
  var2 = (((int32_t)(p >> 2)) * ((int32_t)_dig_P8)) >> 13;
  p = (uint32_t)((int32_t)p + ((var1 + var2 + _dig_P7) >> 4));

  return p;
}

// 補正用データを使用して，生データから湿度を計算
uint32_t BMP280::_compensate_humidity(int32_t adc_H) {
  int32_t v_x1_u32r;
  v_x1_u32r = (_t_fine - ((int32_t)76800));
  v_x1_u32r =
      (((((adc_H << 14) - (((int32_t)dig_H4) << 20) -
          (((int32_t)dig_H5) * v_x1_u32r)) +
         ((int32_t)16384)) >>
        15) *
       (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) *
            (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >>
           10) +
          ((int32_t)2097152)) *
             ((int32_t)dig_H2) +
         8192) >>
        14));
  v_x1_u32r =
      (v_x1_u32r -
       (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >>
        4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

  return (uint32_t)(v_x1_u32r >> 12);
}

// 補正用データを読み込んで保存
void BMP280::_read_compensation_parameters() {
  uint8_t buffer[26];

  _read_registers(0x88, buffer, 26);

  _dig_T1 = buffer[0] | (buffer[1] << 8);
  _dig_T2 = buffer[2] | (buffer[3] << 8);
  _dig_T3 = buffer[4] | (buffer[5] << 8);

  _dig_P1 = buffer[6] | (buffer[7] << 8);
  _dig_P2 = buffer[8] | (buffer[9] << 8);
  _dig_P3 = buffer[10] | (buffer[11] << 8);
  _dig_P4 = buffer[12] | (buffer[13] << 8);
  _dig_P5 = buffer[14] | (buffer[15] << 8);
  _dig_P6 = buffer[16] | (buffer[17] << 8);
  _dig_P7 = buffer[18] | (buffer[19] << 8);
  _dig_P8 = buffer[20] | (buffer[21] << 8);
  _dig_P9 = buffer[22] | (buffer[23] << 8);

  printf("bmp280 params %d %d %d\n", _dig_T1, _dig_T2, _dig_T3);
  printf("bmp280 params %d, %d, %d, %d, %d, %d, %d, %d, %d\n", _dig_P1, _dig_P2,
         _dig_P3, _dig_P4, _dig_P5, _dig_P6, _dig_P7, _dig_P8, _dig_P9);

  dig_H1 = buffer[25];

  _read_registers(0xE1, buffer, 8);

  dig_H2 = buffer[0] | (buffer[1] << 8);
  dig_H3 = (int8_t)buffer[2];
  dig_H4 = buffer[3] << 4 | (buffer[4] & 0xf);
  dig_H5 = (buffer[5] >> 4) | (buffer[6] << 4);
  dig_H6 = (int8_t)buffer[7];
}