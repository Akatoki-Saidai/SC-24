#ifndef SC24_FM_FALL_PHASE_HPP_
#define SC24_FM_FALL_PHASE_HPP_

#include <math.h>
#include <vector>
#include <cmath>
#include <array>
#include <iostream>

#include "pico/stdlib.h"

#include "bmp280/bmp280.hpp"
#include "bno055/bno055.hpp"
#include "GPS/gps.hpp"
#include "s35/s35.hpp"
#include "sd_card/sd_card.hpp"

void fall_phase(BMP280& bmp280, BNO055& bno055, GPS& gps);

# endif  // SC24_FM_FALL_PHASE_HPP_