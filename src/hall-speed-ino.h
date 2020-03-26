/** 
 * @file        hall-speed-ino.h
 * @brief       Hall Speed Arduino Class
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#ifndef HALL_SPEED_INO_H_
#define HALL_SPEED_INO_H_

#include "config/hall-conf.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)
#if (HALL_SPEED_ENABLED == 1)

#include "corelib/hall-speed.h"
#include "framework/arduino/wrapper/hall-platf-ino.h"

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

#endif /** HALL_SPEED_ENABLED */
#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SPEED_INO_H_ **/