#include "flash.hpp"

Flash::Flash() try {
  try {
  } catch (const std::exception &e) {
    printf("\n********************\n\n<<!! INIT ERRPR !!>> in %s line "
           "%d\n%s\n\n********************\n",
           __FILE__, __LINE__, e.what());
  }
} catch (const std::exception &e) {
  printf("An initialization error occurred");
}

void Flash::clear() {
  // 割り込み無効にする
  uint32_t ints = save_and_disable_interrupts();
  // Flash消去。
  //  消去単位はflash.hで定義されている FLASH_SECTOR_SIZE(4096Byte) の倍数とする
  flash_range_erase(_target_begin, _block_size * _block_num);
  // 割り込みフラグを戻す
  restore_interrupts(ints);

  _target_offset = _target_begin;
  _write_data.fill(0);
}

void Flash::write(std::string write_mesage) {
  static std::size_t _write_index = 0;

  std::basic_string<uint8_t> write_binary(std::begin(write_mesage),
                                          std::end(write_mesage));

  // const uint8_t *ptr = write_binary;
  std::size_t write_size = write_mesage.size();
  for (std::size_t i = 0; i < write_size; ++i) {
    if (_write_index < _write_data.size()) {
      _write_data.at(_write_index) = *(write_binary.data() + i);
    } else {
      // 割り込み無効にする
      uint32_t ints = save_and_disable_interrupts();
      // Flash書き込み。
      //  書込単位はflash.hで定義されている FLASH_PAGE_SIZE(256Byte)
      //  の倍数とする
      flash_range_program(_target_offset, _write_data.data(),
                          _write_data.size());
      // 割り込みフラグを戻す
      restore_interrupts(ints);
      _target_offset += _write_data.size();
      if (_target_offset > _target_end) {
        _target_offset = _target_begin;
      }

      _write_data.fill(0U);
      _write_data.at(0) = *(write_binary.data() + i);
      _write_index = 0;
    }
    ++_write_index;
  }
}

Flash::~Flash() {
  this->write(std::string("\nlog end ") + __DATE__ + __TIME__);
  flash_range_program(_target_offset, _write_data.data(), _write_data.size());
}

void Flash::print() {
  std::cout << "\n#################### Log Data ####################"
            << std::endl;
  for (uint32_t i = _target_begin; i < _target_end; ++i) {
    std::cout << *(const uint8_t *)(XIP_BASE + i);
  }
  std::cout << std::endl;
  std::cout << "##################################################\n"
            << std::endl;
}
