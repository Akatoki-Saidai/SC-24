#ifndef SC24_FM_GPS_HPP_
#define SC24_FM_GPS_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "error.hpp"
#include "nema_parser.hpp"
// #include "SerialConnection.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"


#define UART_ID uart0
#define BAUD_RATE 38400  // ビットレートこれだっけ？
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1



class GPS{
public:
    std::pair<double,double> read() const;
};

#endif  // SC24_FM_GPS_HPP_