#include "s35.hpp"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <iostream>
#include <cmath>

S35::S35(int pin,int freq)
    : pin(pin), freq(freq) {}

S35::~S35() {
    stop();
}

void S35::start() {
    gpio_init(pin);               // ピンの初期化
    gpio_set_dir(pin, GPIO_OUT);  // 出力ピンとして設定

    // PWMの設定
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 24999);    //1周期20ms
    pwm_set_clkdiv(slice_num, 100);   // クロック分周 (50Hz)
    pwm_set_enabled(slice_num, true); // PWMを有効化
    //参考：https://rikei-tawamure.com/entry/2021/02/08/213335
    //pwm_set_wrapは(24999+1)/125000000[s]=20[ms]が一周期となる。詳しくは参考サイトのクロックの分割のところを参照。
}

void S35::stop() {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, false); // PWMを無効化
    gpio_set_dir(pin, GPIO_IN);        // ピンを入力に設定
}


//pwm_set_gpio_levelとpwm_set_chan_levelは迷ったけど、スライスがよくわかんなかったから一旦set使う
//参考：https://raspberry.memo.wiki/d/PWM%C0%A9%B8%E6
//デューティサイクルの時に出てくる65535は16bitの最大値。picoのpwmが16bitのカウンタを使用してるらしい

void S35::left_turn() {
    // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
    int pulse_width = 2000; //[us]

    uint slice_num = pwm_gpio_to_slice_num(pin);

    // デューティサイクルの計算（1000~2000us -> 0~65535範囲に変換）
    uint duty_cycle = (pulse_width/20000)*65535;

    // PWMデューティサイクルの設定
    pwm_set_gpio_level(pin, duty_cycle);  // 正規化されたデューティサイクル

}

void S35::right_turn() {

    // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
    int pulse_width = 1000;//[us]

    uint slice_num = pwm_gpio_to_slice_num(pin);

    // デューティサイクルの計算（1000~2000us -> 0~65535範囲に変換)
    uint duty_cycle = (pulse_width/20000)*65535;

    // PWMデューティサイクルの設定
    pwm_set_gpio_level(pin, duty_cycle);  // 正規化されたデューティサイクル

}

void S35::stop_turn() {

    // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
    int pulse_width = 1500;//[us]

    uint slice_num = pwm_gpio_to_slice_num(pin);

    // デューティサイクルの計算（1000~2000us -> 0~65535範囲に変換）
    uint duty_cycle = (pulse_width/20000)*65535;

    // PWMデューティサイクルの設定
    pwm_set_gpio_level(pin, duty_cycle);  // 正規化されたデューティサイクル

}