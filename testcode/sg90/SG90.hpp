#ifndef SG90_H
#define SG90_H

#include "pico/stdlib.h"

class SG90 {
public:
    SG90(int pin = 18, int min_angle = -90, int max_angle = 90, int ini_angle = 0, int freq = 50);
    ~SG90();

    void start();
    void stop();
    void setAngle(int target_angle);
    void setIniAngle();

private:
    int pin;
    int max_angle;
    int min_angle;
    int angle;
    int ini_angle;
    int freq;
};

#endif
