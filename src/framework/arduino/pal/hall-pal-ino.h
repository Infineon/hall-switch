/** 
 * @file        hall-pal-ino.h
 * @brief       Hall Switch Arduino PAL 
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_ARD_H_
#define HALL_SWITCH_ARD_H_

#include "../../../config/hall-conf.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

#include "../../../pal/hall-pal-gpio.h"
#include "../../../pal/hall-pal-timer.h"

/**
 * @addtogroup hsinopal
 * @{
 */

class GPIOIno : virtual public HallSwitch::GPIO 
{
    private:
        #define   UNUSED_PIN    0xFF    /**< Unused pin */
        uint8_t     pin;                /**< Pin number*/
        uint8_t     mode;               /**< Pin mode*/
        VLogic_t    logic;              /**< Pin logic */

    public:
                                GPIOIno       ();
                                GPIOIno       (uint8_t pin, 
                                               uint8_t mode, 
                                               VLogic_t logic);
        HallSwitch::Error_t     init          ();            
        HallSwitch::Error_t     deinit        ();
        HallSwitch::Error_t     enableInt     (HallSwitch *ptr);    
        HallSwitch::Error_t     disableInt    ();
        IntEvent_t              intEvent      ();
        VLevel_t                read          ();
        HallSwitch::Error_t     write         (VLevel_t level);
        HallSwitch::Error_t     enable        ();
        HallSwitch::Error_t     disable       ();
};

#if (HALL_SPEED_ENABLED == 1)

class TimerIno: virtual public HallSpeed::Timer
{
    public:
                                    TimerIno();
                                   ~TimerIno();
        HallSwitch::Error_t         init    ();
        HallSwitch::Error_t         deinit  ();
        HallSwitch::Error_t         start   ();
        HallSwitch::Error_t         elapsed (uint32_t &elapsed);
        HallSwitch::Error_t         stop    ();
        HallSwitch::Error_t         delay   (uint32_t timeout);

    private:
        uint32_t curTime;   /**< Current time */
};

#endif /** HALL_SPEED_ENABLED */

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SWITCH_ARD_H_ **/
