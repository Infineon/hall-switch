/** 
 * @file        hall-switch-ino.h
 * @brief       Hall Switch Arduino Class
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_INO_H_
#define HALL_SWITCH_INO_H_

#include <Arduino.h>
#include "common/hall-switch.h"
#include "framework/arduino/hall-pal-ino.h"
#include "platform/xmc/hall-xmc-platf.h"

/**
 * @class HallSwitchIno
 */

class HallSwitchIno: public HallSwitch
{
    public:
        /**
         * @addtogroup hallswitchinohal
         * @{
         */

        HallSwitchIno(uint8_t       outputPin, 
                      CBack_t       cBack      = NULL,
                      uint8_t       powerPin   = UNUSED_PIN);
        HallSwitchIno(PlatformIno_t hwPlatf,
                      CBack_t       cBack      = NULL);
        /** @} */
};

#endif /** HALL_SWITCH_INO_H_ **/