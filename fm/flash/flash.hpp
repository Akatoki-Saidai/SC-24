#include <array>
#include <iostream>
#include <string>

#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"

class Flash {
  static constexpr uint32_t _target_begin =
      0x1F0000; // W25Q16JVの最終ブロック(Block31)のセクタ0の先頭アドレス
                // = 0x1F0000
  static constexpr uint32_t _target_end = 0x1FFFFF;
  static constexpr uint32_t _block_size = 0xFFFF; // 1ブロックのサイズ
  static constexpr uint8_t _block_num = 1;        // 使用するブロックの数
  uint32_t _target_offset = _target_begin;
  std::array<uint8_t, FLASH_PAGE_SIZE> _write_data;

public:
  //! @brief フラッシュメモリのセットアップ
  Flash();

  //! @brief フラッシュメモリに書き込み
  void write(std::string write_mesage);

  //! @brief フラッシュメモリのデータを出力
  void print();

  //! @brief フラッシュメモリのデータを削除
  void clear();

  ~Flash();
};