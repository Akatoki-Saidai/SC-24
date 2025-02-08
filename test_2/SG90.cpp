#include "SG90.hpp"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <iostream>
#include <cmath>

SG90::SG90(int pin, int min_angle, int max_angle, int ini_angle, int freq)
    : pin(pin), max_angle(max_angle), min_angle(min_angle), angle(ini_angle), ini_angle(ini_angle), freq(freq) {}

SG90::~SG90() {
    stop();
}

void SG90::start() {
    gpio_init(pin);               // ピンの初期化
    gpio_set_dir(pin, GPIO_OUT);  // 出力ピンとして設定

    // PWMの設定
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 24999);    //
    pwm_set_clkdiv(slice_num, 100);   // クロック分周 (50Hz)
    pwm_set_enabled(slice_num, true); // PWMを有効化
}

void SG90::stop() {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, false); // PWMを無効化
    gpio_set_dir(pin, GPIO_IN);        // ピンを入力に設定
}

void SG90::setAngle(int target_angle) {
    if (target_angle < min_angle || target_angle > max_angle) {
        std::cerr << "Angle must be between " << min_angle << " and " << max_angle << " degrees." << std::endl;
        return;
    }

    // パルス幅を計算（-90度で0.5ms、0度で1ms、90度で1.5ms）
    double pulse_width = (target_angle/90) * 500 + 1500;  // 1000~2000us

    uint slice_num = pwm_gpio_to_slice_num(pin);

    // デューティサイクルの計算（1000~2000us -> 0~65535範囲に変換）←ここからやる
    uint duty_cycle = pulse_width/20000;

    // PWMデューティサイクルの設定
    pwm_set_gpio_level(pin, duty_cycle);  // 正規化されたデューティサイクル

    angle = target_angle;
}


void SG90::setIniAngle() {
    setAngle(ini_angle);
}
