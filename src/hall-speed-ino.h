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
#include "framework/arduino/hall-pal-ino.h"

/**
 * @class HallSpeedIno
 */

class HallSpeedIno: public HallSpeed
{
    public:

        // enum HwPlatf_t
        // {
        //     TLE4964_3M_S2Go,      /**< TLE4964-3M Shield 2Go */
        //     TLE4922_Speed_2GoKit,
        // };

        /**
         * @brief Hall Speed Arduino hardware platform
         */
        struct Platform_t
        {
            uint8_t output;     /**< Output pin */
            uint8_t power;      /**< Power pin */
        };

        HallSpeedIno(uint8_t     outputPin, 
                     uint8_t     polesNum = 1,
                     SpeedUnit_t units    = HERTZ,
                     CBackSpd_t  cBack    = NULL,
                     uint8_t     powerPin = UNUSED_PIN);
        HallSpeedIno(Platform_t  hwPlatf,
                     uint8_t     polesNum = 1,
                     SpeedUnit_t units    = HERTZ,
                     CBackSpd_t  cBack    = NULL);
};

#endif /** HALL_SPEED_INO_H_ **/