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
#include "platform/xmc/hall-xmc-platf.h"

/**
 * @class HallSpeedIno
 */

class HallSpeedIno
{
    public:
                HallSpeedIno    (uint8_t                    outputPin, 
                                 uint8_t                     polesNum = 1,
                                 HallSpeed::SpeedUnit_t      units    = HallSpeed::HERTZ,
                                 HallSpeed::CBackSpd_t       cBack    = NULL,
                                 uint8_t                     powerPin = UNUSED_PIN);
                HallSpeedIno    (PlatformIno_t              hwPlatf,
                                 uint8_t                     polesNum = 1,
                                 HallSpeed::SpeedUnit_t      units    = HallSpeed::HERTZ,
                                 HallSpeed::CBackSpd_t       cBack    = NULL);
               ~HallSpeedIno    ();
        int     begin           ();
        int     end             ();
        double  getSpeed        ();
    
    private:
        HallSpeed sp;
};

#endif /** HALL_SPEED_INO_H_ **/