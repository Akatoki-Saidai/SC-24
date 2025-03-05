#ifndef SC24_FM_FLASH_HPP_
#define SC24_FM_FLASH_HPP_

#include <array>
#include <cstddef>
#include <iostream>
#include <string>

#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"

//! @brief printfの形式で文字列をフォーマット
//! @param format フォーマット文字列
//! @param args フォーマット文字列に埋め込む値
template <typename... Args>
std::string format_str(const std::string &format, Args... args) noexcept {
  try {
    const std::size_t formatted_chars_num = std::snprintf(
        nullptr, 0, format.c_str(), args...); // フォーマット後の文字数を計算
    char formatted_chars
        [formatted_chars_num +
         1]; // フォーマット済みの文字列を保存するための配列を作成
    std::snprintf(&formatted_chars[0], formatted_chars_num + 1, format.c_str(),
                  args...);              // フォーマットを実行
    return std::string(formatted_chars); // フォーマット済み文字列を出力
  } catch (const std::exception &e) {
    std::cout << "           From  FILE : " << __FILE__
              << "  LINE : " << __LINE__
              << "\n                 MESSAGE : Failed to format string\n"
              << e.what() << std::flush;
  } // ログの保存に失敗しました
  catch (...) {
    std::cout << "<<ERROR>>  FILE : " << __FILE__ << "  LINE : " << __LINE__
              << "\n           MESSAGE : Failed to format string" << std::endl;
  } // ログの保存に失敗しました
  return "format error";
}
// この関数は以下の資料を参考にて作成しました
// https://pyopyopyo.hatenablog.com/entry/2019/02/08/102456

class Flash {
  static constexpr uint32_t _target_begin =
      0x1F0000; // W25Q16JVの最終ブロック(Block31)のセクタ0の先頭アドレス
                // = 0x1F0000
  static constexpr uint32_t _target_end = 0x1FFFFF;
  static constexpr uint32_t _block_size = 0xFFFF; // 1ブロックのサイズ
  static constexpr uint8_t _block_num = 1;        // 使用するブロックの数
  uint32_t _target_offset = _target_begin;
  std::array<uint8_t, FLASH_PAGE_SIZE> _write_data;

  const bool _enable;

public:
  //! @brief フラッシュメモリのセットアップ
  Flash();

  //! @brief 無効なオブジェクトを作成
  Flash(std::nullptr_t null) : _enable(false) {};

  //! @brief フラッシュメモリに書き込み
  void write(const std::string &write_mesage) noexcept;

  //! @brief フラッシュメモリにフォーマット済みのデータを書き込み
  template <typename... Args>
  void write(const std::string &format, Args... args) noexcept {
    write(format_str(format, args...));
  }

  //! @brief フラッシュメモリのデータを出力
  void print();

  //! @brief フラッシュメモリのデータを削除
  void clear();

  ~Flash();
};

#endif // SC24_FM_FLASH_HPP_