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
#include "phase.hpp"
#include "s35/s35.hpp"
#include "sd_card/sd_card.hpp"


void goal_phase(Phase &phase, BMP280 &bmp280, GPS &gps);

#endif // SC24_FM_GOAL_PHASE_HPP_