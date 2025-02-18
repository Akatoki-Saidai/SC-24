#ifndef SG90_H
#define SG90_H

#include "pico/stdlib.h"

class SG90{
public:
    SG90(int pin = 18, int freq = 50);//コンストラクタ
    ~SG90();//デストラクタ

    void start();
    void stop();
    // void left_turn();
    // void right_turn();
    // void stop_turn();
    void turn(int deg);
    void init_turn();


private:
    int pin;
    int freq;
};

#endif