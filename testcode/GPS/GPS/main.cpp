#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Error.h"
#include "NEMAParser.h"
// #include "SerialConnection.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"


#define UART_ID uart1
#define BAUD_RATE 39200  // ビットレートこれだっけ？

#define UART_TX_PIN 4
#define UART_RX_PIN 5

static int chars_rxed = 0;


Binary uart_read() const
{
    std::deque<uint8_t> other_data(0);
    std::swap(uart1_queue, other_data);
    return Binary(other_data);  // 割り込み処理で一時保存しておいたデータを返す
}

void uart1_handler()
{
    while (uart_is_readable(UART_ID))
    {
        uart1_queue.push_back(uart_getc(UART_ID));  // 1文字読み込んで末尾に値を追加
    }
    
}

int main() {
  std::ofstream ofs_all_log("all_log.txt");
  std::ofstream ofs_some_log("some_log.csv");

  ofs_some_log
      << "utc" << ","
      << "latitude" << ","
      << "latitude_direction" << ","
      << "longitude" << ","
      << "longitude_direction" << ","
      << "altitude" << ","
      << "ground_speed_kmh" << ","
      << "track" << ","
      << "quality" << ","
      << "status" << ","
      << "number_of_satellites" << ","
      << std::endl;

  // uart
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);
  uart_set_irq_enables(UART_ID, true, false);

  NEMAParser::NEMAParser parser;
  NEMAParser::ErrorCode error;
  while (true) {
    usleep(1000000.f); // 100ms
    ofs_all_log << "-----START-----" << std::endl;
    // std::istringstream ss(uart_getc(UART_ID, '\n'y));
    
    while (uart_is_readable(UART_ID)) {
        std::istringstream ss(uart_read());
    }

    std::string buffer;
    while (std::getline(ss, buffer, '\n') ) {
     error = parser.parse(buffer);
    }
    if (error != NEMAParser::ErrorCode::kNoError) {
      ofs_all_log << "Error Code = " << (int)error << std::endl;
    }
    parser.getGPGGA().output(ofs_all_log);
    parser.getGPGLL().output(ofs_all_log);
    parser.getGPGSA().output(ofs_all_log);
    parser.getGPGSV().output(ofs_all_log);
    parser.getGPRMC().output(ofs_all_log);
    parser.getGPVTG().output(ofs_all_log);
    parser.getGPZDA().output(ofs_all_log);
    ofs_all_log << "-----END-----" << std::endl;

    ofs_some_log
        << std::setprecision(10)
        << parser.getGPGGA().time.utc << ","
        << parser.getGPGGA().latitude.decimal_degrees << ","
        << parser.getGPGGA().latitude_direction << ","
        << parser.getGPGGA().longitude.decimal_degrees << ","
        << parser.getGPGGA().longitude_direction << ","
        << parser.getGPGGA().altitude << ","
        << parser.getGPVTG().ground_speed_kmh << ","
        << parser.getGPVTG().track << ","
        << parser.getGPGGA().quality << ","
        << parser.getGPGSA().status << ","
        << parser.getGPGGA().number_of_satellites
        << std::endl;
  }
  return 0;
}

