#ifndef S35_H
#define S35_H

#include "pico/stdlib.h"

class S35{
public:
    S35(int pin = 18, int freq = 50);//コンストラクタ
    ~S35();//デストラクタ

    void start();
    void stop();
    void left_turn();
    void right_turn();
    void stop_turn();


private:
    int pin;
    int freq;
};

#endif