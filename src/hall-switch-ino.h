/** 
 * @file        hall-switch-ino.h
 * @brief       Hall Switch Arduino Class
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_INO_H_
#define HALL_SWITCH_INO_H_

#include <Arduino.h>
#include "common/hall-switch.h"
#include "pal/arduino/hall-switch-ard.h"

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
        /**
         * @brief Arduino hardware platforms
         */
        enum HwPlatf_t
        {
            TLE4964_3M_S2Go      /**< TLE4964-3M Shield 2Go */
        };

        HallSwitchIno(uint8_t   outputPin, 
                      CBack_t   cBack      = NULL,
                      uint8_t   powerPin   = UNUSED_PIN);
        HallSwitchIno(HwPlatf_t              hwPlatf,
                      CBack_t   cBack      = NULL);
        /** @} */
};


#endif /** HALL_SWITCH_INO_H_ **/