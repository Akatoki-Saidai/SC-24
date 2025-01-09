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
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 4
#define UART_RX_PIN 5

static int chars_rxed = 0;

char uart_buffer[256];

// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        // uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?

        // if (uart_is_writable(UART_ID)) {
        //     // Change it slightly first!
        //     ch++;
        //     uart_putc(UART_ID, ch);
        // }
        chars_rxed++;
    }
}

int Serial_receive(char *buffer, size_t length) {
    size_t count = 0;

    while (count < length) {
        // データが受信可能か確認
        if (uart_is_readable(UART_ID)) {
            // 受信したデータをバッファに格納
            buffer[count++] = uart_getc(UART_ID);
        }
    }
    return count; // 受信したバイト数を返す
}


int main() {
  stdio_init_all();

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

  int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
  
  // Set UART flow control CTS/RTS, we don't want these, so turn them off
  uart_set_hw_flow(UART_ID, false, false);
  
  // Set our data format
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
  
  // Turn off FIFO's - we want to do this character by character
  uart_set_fifo_enabled(UART_ID, false);
  
  // Set up a RX interrupt
  // We need to set up the handler first
  // Select correct interrupt for the UART we are using
  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
  
  // And set up and enable the interrupt handlers
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);
  
  // Now enable the UART to send interrupts - RX only
  uart_set_irq_enables(UART_ID, true, false);


  NEMAParser::NEMAParser parser;
  NEMAParser::ErrorCode error;
  while (true) {
    sleep_us(1000000.f); // 100ms
    ofs_all_log << "-----START-----" << std::endl;
    // std::istringstream ss(uart_getc(UART_ID, '\n'y));
    
    int received_bytes = Serial_receive(uart_buffer, sizeof(uart_buffer) - 1);
    std::istringstream ss(uart_buffer);
    
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

