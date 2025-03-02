#ifndef SC24_FM_GPS_HPP_
#define SC24_FM_GPS_HPP_

#include <cmath>
#include <deque>
#include <iostream>
#include <string>

#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

class GPS {
private:
  uart_inst_t *_uart_hw;

  static constexpr uint DataBits = 8;
  static constexpr uint StopBits = 1;
  const uart_parity_t UartParity = UART_PARITY_NONE;
  int uart_irq;
  // int actual_baudrate;
  const uint _read_len = 800;

public:
  GPS(uart_inst_t *uart_hw);

  struct Measurement_t {
    double lat = -1024.0;
    double lon = -1024.0;
    float altitude = -1024.0F;
    float HDOP = -1024.0F;
    float geoid_separation = -1024.0F;
    float velocity = -1024.0F;
    int second = -1024;
    int minute = -1024;
    int hour = -1024;
    int day = -1024;
    int month = -1024;
    int year = -1024;
    double target_angle = -1024.0;
    double target_distance = -1024.0;
  } _measurement;

  Measurement_t read();

private:
  std::deque<char> _recv_copy;

  void output_time(std::string &);
  void output_lat(std::string &, std::string &);
  void output_lon(std::string &, std::string &);
  void output_altitude(std::string &);
  void output_HDOP(std::string &);
  void output_geoid_separation(std::string &);
  void output_velocity(std::string &);
  void output_date(std::string &);

  void UTCtoJST_date();
  const int time_diff = +9;

public:
  void set_target(double, double);

private:
  double _target_lat;
  double _target_lon;
  const double EarthR =
      6369275.1; // 地球の半径(地球楕円体の緯度40度の中心からの距離)
  void output_target();
};

#endif // SC24_FM_GPS_HPP_