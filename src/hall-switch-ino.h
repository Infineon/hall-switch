/** 
 * @file        hall-switch-ino.h
 * @brief       Hall Switch Arduino Class
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_INO_H_
#define HALL_SWITCH_INO_H_

#include <Arduino.h>
#include "corelib/hall-switch.h"
#include "framework/arduino/pal/hall-pal-ino.h"
#include "framework/arduino/wrapper/hall-platf-ino.h"

/**
 * @class HallSwitchIno
 */

class HallSwitchIno
{
    public:
        /**
         * @addtogroup hallswitchinohal
         * @{
         */

                    HallSwitchIno   (uint8_t                outputPin, 
                                     HallSwitch::CBack_t    cBack      = NULL,
                                     uint8_t                powerPin   = UNUSED_PIN);
                    HallSwitchIno   (PlatformIno_t          hwPlatf,
                                     HallSwitch::CBack_t    cBack      = NULL);
                   ~HallSwitchIno   ();
        int         begin           ();
        int         end             ();
        int         getBField       ();
        /** @} */

    private:
        HallSwitch sw;
};

#endif /** HALL_SWITCH_INO_H_ **/