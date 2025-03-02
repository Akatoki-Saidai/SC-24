#ifndef SC24_FM_WAIT_PHASE_HPP_
#define SC24_FM_WAIT_PHASE_HPP_

#include <array>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>

#include "pico/stdlib.h"

#include "GPS/gps.hpp"
#include "bmp280/bmp280.hpp"
#include "bno055/bno055.hpp"
#include "phase.hpp"
#include "sd_card/sd_card.hpp"
#include "servo/servo.hpp"

void wait_phase(Phase &phase, BMP280 &bmp280, const BNO055 &bno055);

#endif // SC24_FM_WAIT_PHASE_HPP_