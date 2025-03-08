#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Error.h"
#include "NEMAParser.h"
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

// static int chars_rxed = 0;

char uart_buffer_temp[512];

// RX interrupt handler
/*  割り込み無効化
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
*/

int Serial_receive(char *buffer, size_t length) {
    size_t count = 0;
    
    // タイムアウト
    absolute_time_t start_time = get_absolute_time();
    const int TIMEOUT_US = 10*1000000;  // マイクロ秒

    // テスト用
    std::cout << length << std::endl;
    std::cout << "uart_is_readable: " << uart_is_readable(UART_ID) << std::endl;


    while (count < length) {
        // データが受信可能か確認
        if (uart_is_readable(UART_ID)) {
            // 受信したデータをバッファに格納
            buffer[count++] = uart_getc(UART_ID);
           
            // std::cout << count << std::endl;  // テスト用
        }
        
        // タイムアウト
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(start_time, now) > TIMEOUT_US) {
            std::cout << "Timeout reached" << std::endl;
            break;
        }

        // sleep_ms(10);
    }
    buffer[count] = '\0';

    return count; // 受信したバイト数を返す
}

std::vector<std::string> ExtractSentences(std::string &buffer) {
    std::vector<std::string> sentences;
    while (true) {
        // '$' がある位置を検索
        size_t start = buffer.find('$');
        if (start == std::string::npos) {
            // '$' が見つからない場合破棄
            buffer.clear();
            break;
        }

        // '$' より前は削除
        if (start > 0) {
            buffer.erase(0, start);
            start = 0;
        }
        // '$' から先頭の '\r' を検索
        size_t end = buffer.find('\r', start);
        if (end == std::string::npos) {
            
            break;  // まだ完全な文が得られていない
        }

        // '$'から'\r'までを抽出（'\r' を含める）
        std::string sentence = buffer.substr(start, end - start + 1);
        sentences.push_back(sentence);

        // 抽出した部分以外を削除
        buffer.erase(0, end + 1);
    }
    return sentences;
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

// 割り込み無効化
//   int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
//   irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
//   irq_set_enabled(UART_IRQ, true);
//   uart_set_irq_enables(UART_ID, true, false);


  NEMAParser::NEMAParser parser;
  NEMAParser::ErrorCode error;
  std::string uart_buffer;

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 0);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);
  sleep_ms(250);

  while (true) {
    std::cout << "hello, gps" << std::endl;

    sleep_us(1000000.f); // 100ms
    ofs_all_log << "-----START-----" << std::endl;
    std::cout << "-----START-----" << std::endl;
    // std::istringstream ss(uart_getc(UART_ID, '\n'y));
    
    int received_bytes = Serial_receive(uart_buffer_temp, sizeof(uart_buffer_temp) - 1);
    if (received_bytes > 0) {
        // 読み込んだ生データをrx_bufferに追加
        uart_buffer.append(uart_buffer_temp);
    }

    std::cout << "receive bytes: " << received_bytes << std::endl;
    std::cout << "buffer: " << uart_buffer_temp << std::endl;
 

    std::vector<std::string> sentences = ExtractSentences(uart_buffer);
    for (const auto &sentence : sentences) {

        std::cout << "Extracted sentence: " << sentence << std::endl;

        // パーサーに渡して解析する
        error = parser.parse(sentence);
        if (error != NEMAParser::ErrorCode::kNoError) {
            ofs_all_log << "Error Code = " << static_cast<int>(error) << std::endl;
            std::cout << "Error Code = " << static_cast<int>(error) << std::endl;
        }
    }
    

    parser.getGPGGA().output(ofs_all_log);
    parser.getGPGLL().output(ofs_all_log);
    parser.getGPGSA().output(ofs_all_log);
    parser.getGPGSV().output(ofs_all_log);
    parser.getGPRMC().output(ofs_all_log);
    parser.getGPVTG().output(ofs_all_log);
    parser.getGPZDA().output(ofs_all_log);
    ofs_all_log << "-----END-----" << std::endl;
    std::cout << "-----END-----" << std::endl;

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
    
    std::cout
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

