/** 
 * @file        hall-speed-ino.h
 * @brief       Hall Speed Arduino Class
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#ifndef HALL_SPEED_INO_H_
#define HALL_SPEED_INO_H_

#include <Arduino.h>
#include "common/hall-speed.h"
#include "pal/arduino/hall-switch-ard.h"

/**
 * @class HallSpeedIno
 */

class HallSpeedIno: public HallSpeed
{
    public:

        enum HwPlatf_t
        {
            TLE4964_3M_S2Go,      /**< TLE4964-3M Shield 2Go */
            TLE4922_Speed_2GoKit,
        };

        HallSpeedIno(uint8_t     outputPin, 
                     uint8_t     polesNum = 1,
                     SpeedUnit_t units    = HERTZ,
                     CBack_t     cBack    = NULL,
                     uint8_t     powerPin = UNUSED_PIN);
        HallSpeedIno(HwPlatf_t   hwPlatf,
                     uint8_t     polesNum = 1,
                     SpeedUnit_t units    = HERTZ,
                     CBack_t     cBack    = NULL);
};

#endif /** HALL_SPEED_INO_H_ **/