/*
このプログラムはGPSセンサ GT_902PMGGを読み取るためのものです．

データの受信に割り込み処理を利用することで，センサの値を直ちに返すことができます．
ただし，割り込み処理によってほかのプログラムに影響を与える可能性を否定できません．

このプログラムを作るにあたって，以下のプログラムを参考にしました．
    https://www.mztn.org/rpi/rpi53.html
    https://github.com/raspberrypi/pico-examples/blob/master/uart/uart_advanced/uart_advanced.c
    https://github.com/ms1963/bme280_spi/find/main
    https://orsj.org/wp-content/corsj/or60-12/or60_12_701.pdf
    https://www.logical-arts.jp/archives/18
*/

#include "gps.hpp"

// 読み取ったGPSの値をdequeに保存
namespace gps {
std::deque<char> recv0;
void read_raw0();
std::deque<char> recv1;
void read_raw1();
} // namespace gps

GPS::GPS(uart_inst_t *uart_hw) : _uart_hw(uart_hw) {
  // uart_init(_uart_hw, baud_rate);

  // gpio_set_function(tx_pin, GPIO_FUNC_UART);
  // gpio_set_function(rx_pin, GPIO_FUNC_UART);

  // フロー制御(受信準備が終わるまで送信しないで待つ機能)を無効にする
  uart_set_hw_flow(_uart_hw, false, false);

  // UART通信の設定をする
  uart_set_format(_uart_hw, DataBits, StopBits, UartParity);

  ((_uart_hw == uart1) ? gps::recv1 : gps::recv0).resize(_read_len);

  _target_lat = 0;
  _target_lon = 0;

  // ここから割り込み処理の設定

  // FIFO(受信したデータを一時的に保管する機能)をオフにし，1文字ずつ受信する
  // uart_set_fifo_enabled(UART_ID, false);

  uart_irq = (_uart_hw == uart0) ? UART0_IRQ : UART1_IRQ;

  // 割り込み処理で実行する関数をセット
  irq_set_exclusive_handler(uart_irq, (_uart_hw == uart1) ? gps::read_raw1
                                                          : gps::read_raw0);
  // 割り込み処理を有効にする
  irq_set_enabled(uart_irq, true);

  // UARTの周波数を設定し，正確な周波数を得る
  // int __unused actual_baudrate = uart_set_baudrate(_uart_hw, baud_rate);

  // UARTの割り込み処理を受信のみ有効にする
  uart_set_irq_enables(_uart_hw, true, false);
}

// uart0のときにGPSの値をdequeに追加-->古い値を削除
inline void gps::read_raw0() {
  while (uart_is_readable(uart0)) {
    gps::recv0.push_back(uart_getc(uart0));
    gps::recv0.pop_front();
  }
}
// uart1のときにGPSの値をdequeに追加-->古い値を削除
inline void gps::read_raw1() {
  while (uart_is_readable(uart1)) {
    gps::recv1.push_back(uart_getc(uart1));
    gps::recv1.pop_front();
  }
}

// dequeに保存したGPSの値から数値を取り出す
GPS::Measurement_t GPS::read() {
  std::deque<char> &recv = (_uart_hw == uart1) ? gps::recv1 : gps::recv0;
  if (recv.size() != _read_len)
    recv.resize(_read_len);
  _recv_copy = recv;

  //------------------------------
  // この部分を削除することで，データを受信できなかった時にエラーの値-1024ではなく前回受信した値が出力されます．
  _measurement.lat = _measurement.lon = _measurement.target_angle =
      _measurement.target_distance = -1024.0;
  _measurement.altitude = _measurement.HDOP = _measurement.geoid_separation =
      _measurement.velocity = _measurement.second = -1024.0F;
  _measurement.minute = _measurement.hour = _measurement.day =
      _measurement.month = _measurement.year = -1024;
  //------------------------------

  int i = 0;
  int check_sum = 0;
  while (i < int(_read_len)) {
    check_sum = 0;
    std::deque<std::string> split_data(1);
    while (i < int(_read_len) && _recv_copy.at(i++) != '$')
      ; // 最初の$まで移動
    for (; i < int(_read_len) && _recv_copy.at(i) != '*';
         i++) { //*になるまで次の文字を見ていく
      check_sum ^= _recv_copy.at(i);
      if (_recv_copy.at(i) == ',') {
        split_data.push_back("");
        continue;
      }
      split_data.back() += _recv_copy.at(i);
    }

    if (i >= int(_read_len))
      break;

    std::string check_sum_str = "";

    i++;
    while (i < int(_read_len) && _recv_copy.at(i) != '\r' &&
           _recv_copy.at(i) != '\n') {
      check_sum_str += _recv_copy.at(i++);
    }

    // チェックサムで正常な値を取得できたか確認
    if (check_sum_str.size() == 0 ||
        check_sum != std::stoi(check_sum_str, nullptr, 16)) {
      printf("\nfaild check_sum\n");
      continue;
    }

    // 数値を出力するための変数に入れていく
    std::string nmea = split_data.at(0).substr(2);
    if (nmea == "GGA") {
      if (split_data.at(7) != "00") {
        output_time(split_data.at(1));
        output_lat(split_data.at(2), split_data.at(3));
        output_lon(split_data.at(4), split_data.at(5));
        output_HDOP(split_data.at(8));
        output_altitude(split_data.at(9));
        output_geoid_separation(split_data.at(11));
      }
    } else if (nmea == "GLL") {
      if (split_data.at(6) != "V" && split_data.at(7) != "N") {
        output_lat(split_data.at(1), split_data.at(2));
        output_lon(split_data.at(3), split_data.at(4));
        output_time(split_data.at(5));
      }
    } else if (nmea == "RMC") {
      if (split_data.at(2) != "V" && split_data.at(12) != "N") {
        output_time(split_data.at(1));
        output_lat(split_data.at(3), split_data.at(4));
        output_lon(split_data.at(5), split_data.at(6));
        output_velocity(split_data.at(7));
        output_date(split_data.at(9));
      }
    } else if (nmea == "VTG") {
      if (split_data.at(9) != "N") {
        output_velocity(split_data.at(5));
      }
    }
  }

  UTCtoJST_date();
  output_target();

  return _measurement;
}

// 目標物の座標を設定
void GPS::set_target(double target_lat, double target_lon) {
  _target_lat = target_lat;
  _target_lon = target_lon;
}

// 時刻を出力するための変数に入れる
inline void GPS::output_time(std::string &value_str) {
  if (value_str.size() == 9) {
    _measurement.hour =
        ((value_str.at(0) - '0') * 10 + (value_str.at(1) - '0') + time_diff) %
        24;
    _measurement.minute = (value_str.at(2) - '0') * 10 + value_str.at(3) - '0';
    _measurement.second =
        (value_str.at(4) - '0') * 10 +
        (value_str.at(5) -
         '0'); // 小数形式で与えられるが，.00しか出力されないようなので小数部分は無視する
    printf("gps_time: %02d:%02d:%02d\n", _measurement.hour, _measurement.minute,
           _measurement.second);
  }
}

// 緯度を出力するための変数に入れる
inline void GPS::output_lat(std::string &value1_str, std::string &value2_str) {
  if (value1_str.size() == 10 && value2_str != "") {
    _measurement.lat =
        ((value1_str.at(0) - '0') * 10 + (value1_str.at(1) - '0') +
         ((value1_str.at(2) - '0') * 10 + (value1_str.at(3) - '0') +
          (value1_str.at(5) - '0') * 0.1 + (value1_str.at(6) - '0') * 0.01 +
          (value1_str.at(7) - '0') * 0.001 + (value1_str.at(8) - '0') * 0.0001 +
          (value1_str.at(9) - '0') * 0.00001) /
             60.0) *
        ((value2_str == "N") ? 1 : -1);
    printf("gps_lat: %f\n", _measurement.lat);
  }
}

// 経度を出力するための変数に入れる
inline void GPS::output_lon(std::string &value1_str, std::string &value2_str) {
  if (value1_str.size() == 11 && value2_str != "") {
    _measurement.lon =
        ((value1_str.at(0) - '0') * 100 + (value1_str.at(1) - '0') * 10 +
         (value1_str.at(2) - '0') +
         ((value1_str.at(3) - '0') * 10 + (value1_str.at(4) - '0') +
          (value1_str.at(6) - '0') * 0.1 + (value1_str.at(7) - '0') * 0.01 +
          (value1_str.at(8) - '0') * 0.001 + (value1_str.at(9) - '0') * 0.0001 +
          (value1_str.at(10) - '0') * 0.00001) /
             60.0) *
        ((value2_str == "E") ? 1 : -1);
    printf("gps_lon: %f\n", _measurement.lon);
  }
}

// 高度を出力するための変数に入れる
inline void GPS::output_altitude(std::string &value_str) {
  if (value_str != "") {
    _measurement.altitude = std::stof(value_str);
    printf("gps_alt: %f\n", _measurement.altitude);
  }
}

// HDOPを出力するための変数に入れる
inline void GPS::output_HDOP(std::string &value_str) {
  if (value_str != "") {
    _measurement.HDOP = std::stof(value_str);
    printf("gps_HDOP: %f\n", _measurement.HDOP);
  }
}

// ジオイド高を出力するための変数に入れる
inline void GPS::output_geoid_separation(std::string &value_str) {
  if (value_str != "") {
    _measurement.geoid_separation = std::stof(value_str);
    printf("gps_geoid: %f\n", _measurement.geoid_separation);
  }
}

// 対地速度を出力するための変数に入れる
inline void GPS::output_velocity(std::string &value_str) {
  if (value_str != "") {
    _measurement.velocity = std::stof(value_str) * 1852.0F / 3600.0F;
    printf("gps_velocity: %f\n", _measurement.velocity);
  }
}

// 日付を出力するための変数に入れる
inline void GPS::output_date(std::string &value_str) {
  if (value_str.size() == 6) {
    _measurement.day = (value_str.at(0) - '0') * 10 + (value_str.at(1) - '0');
    _measurement.month = (value_str.at(2) - '0') * 10 + (value_str.at(3) - '0');
    _measurement.year =
        2000 + (value_str.at(4) - '0') * 10 + (value_str.at(5) - '0');
    printf("gps_date: %02d-%02d-%02d\n", _measurement.day, _measurement.month,
           _measurement.year);
  }
}

// 目標物との角度と距離を出力するための変数に入れる
void GPS::output_target() {
  if (_measurement.lat == -1024.0 || _measurement.lon == -1024.0)
    return;

  double t_lat_rad = _target_lat * M_PI / 180;
  double m_lat_rad = _measurement.lat * M_PI / 180;
  double t_lon_rad = _target_lon * M_PI / 180;
  double m_lon_rad = _measurement.lon * M_PI / 180;

  double cos_n = sin(t_lat_rad) * sin(m_lat_rad) +
                 cos(t_lat_rad) * cos(m_lat_rad) * cos(t_lon_rad - m_lon_rad);

  _measurement.target_distance = EarthR * acos(cos_n);

  // 同じ二点では角度は定義されない
  if (_measurement.lon == _target_lon && _measurement.lat == _target_lat)
    return;

  _measurement.target_angle =
      atan((cos(m_lat_rad) * cos(t_lat_rad) * sin(t_lon_rad - m_lon_rad)) /
           (sin(t_lat_rad) - sin(m_lat_rad) * (cos_n))) *
      180 / M_PI;
  // 東経から西経などへの計算も正確にするため，場合分けをしている．
  if (_target_lon - _measurement.lon > 180)
    _measurement.target_angle += (_measurement.target_angle < 0 ? 360 : 180);
  else if (_target_lon - _measurement.lon > 0)
    _measurement.target_angle += (_measurement.target_angle < 0 ? 180 : 0);
  else if (_target_lon - _measurement.lon > -180)
    _measurement.target_angle += (_measurement.target_angle < 0 ? 360 : 180);
  else
    _measurement.target_angle += (_measurement.target_angle < 0 ? 180 : 0);
}

// 時差を考慮して日付を変更
void GPS::UTCtoJST_date() {
  if (_measurement.hour != -1024 && _measurement.day != -1024) {
    if (_measurement.hour < time_diff) {
      if (_measurement.day >= 28) {
        if (_measurement.month == -1024) {
          _measurement.day = -1024;
          return;
        }
        if (_measurement.day <= 29) {
          if (_measurement.month == 2) {
            _measurement.month = 3;
            _measurement.day = 1;
          } else {
            _measurement.day++;
          }
        } else if (_measurement.day == 30) {
          if (_measurement.month == 4 || _measurement.month == 6 ||
              _measurement.month == 9 || _measurement.month == 11) {
            _measurement.month++;
            _measurement.day = 1;
          } else {
            _measurement.day++;
          }
        } else {
          if (_measurement.month == 12) {
            if (_measurement.year != -1024)
              _measurement.year++;
            _measurement.month = _measurement.day = 1;
          } else {
            _measurement.month++;
            _measurement.day = 1;
          }
        }
      } else {
        _measurement.day++;
      }
    }
  } else {
    _measurement.day = -1024;
  }
}