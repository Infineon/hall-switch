/** 
 * @file        hall-switch-ino.hpp
 * @brief       Hall Switch Arduino API
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_INO_HPP_
#define HALL_SWITCH_INO_HPP_

#include "config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

#include "corelib/hall-switch.hpp"
#include "framework/arduino/wrapper/hall-platf-ino.hpp"

/**
 * @addtogroup hsinoapi
 * @{
 */

class HallSwitchIno
{
    public:
 

                    HallSwitchIno   (uint8_t                outputPin, 
                                     HallSwitch::CBack_t    cBack      = NULL,
                                     uint8_t                powerPin   = UNUSED_PIN);
                    HallSwitchIno   (PlatformIno_t          hwPlatf,
                                     HallSwitch::CBack_t    cBack      = NULL);
                   ~HallSwitchIno   ();
        int         begin           ();
        int         end             ();
        int         getBField       ();


    private:
        HallSwitch sw;
};

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SWITCH_INO_HPP_ **/