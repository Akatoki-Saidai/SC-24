#ifndef SC24_FM_GOAL_PHASE_HPP_
#define SC24_FM_GOAL_PHASE_HPP_

#include <array>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>

#include "pico/stdlib.h"

#include "GPS/gps.hpp"
#include "bmp280/bmp280.hpp"
#include "bno055/bno055.hpp"
#include "fm.hpp"
#include "sd_card/sd_card.hpp"
#include "servo/servo.hpp"

void goal_phase(Phase &phase, Flash &flash, BMP280 &bmp280, GPS &gps,
                const Servo &servo_r, const Servo &servo_l);

#endif // SC24_FM_GOAL_PHASE_HPP_