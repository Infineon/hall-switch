/** 
 * @file        hall-speed-ino.hpp
 * @brief       Hall Speed Arduino API
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SPEED_INO_HPP_
#define HALL_SPEED_INO_HPP_

#include "config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)
#if (HALL_SPEED_ENABLED == 1)

#include "corelib/hall-speed.hpp"
#include "framework/arduino/wrapper/hall-platf-ino.hpp"

/**
 * @addtogroup hspinoapi
 * @{
 */

class HallSpeedIno
{
    public:

                HallSpeedIno    (uint8_t                     outputPin, 
                                 uint8_t                     polesNum = 1,
                                 HallSpeed::SpeedUnit_t      units    = HallSpeed::HERTZ,
                                 HallSpeed::CBackSpd_t       cBack    = NULL,
                                 uint8_t                     powerPin = UNUSED_PIN);
                HallSpeedIno    (PlatformIno_t               hwPlatf,
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
/** @} */

#endif /** HALL_SPEED_ENABLED */
#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SPEED_INO_HPP_ **/