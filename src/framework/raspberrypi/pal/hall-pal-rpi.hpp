/** 
 * @file        hall-pal-rpi.hpp
 * @brief       Hall Switch Raspberry Pi PAL 
 * @date        August 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_RPI_HPP_
#define HALL_SWITCH_RPI_HPP_

#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

#include "../../../pal/hall-pal-gpio.hpp"
#include <wiringPi.h>

/**
 * @addtogroup hsrpipal
 * @{
 */

class GPIORpi : virtual public HallSwitch::GPIO 
{
    private:
        #define     UNUSED_PIN    0xFF  /**< Unused pin */
        uint8_t     pin;                /**< Pin number*/
        uint8_t     mode;               /**< Pin mode*/
        VLogic_t    logic;              /**< Pin logic */

    public:
                                GPIORpi       ();
                                GPIORpi       (uint8_t pin, 
                                               uint8_t mode, 
                                               VLogic_t logic);
                               ~GPIORpi       ();
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

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_SWITCH_RPI_H_ **/
