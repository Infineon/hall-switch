/** 
 * @file        hall-pal-wiced.hpp
 * @brief       Hall Switch WICED PAL  
 * @date        January 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */


#ifndef HALL_PAL_WICED_HPP_
#define HALL_PAL_WICED_HPP_

#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

#include "hall-pal-gpio.hpp"
#include "wiced_platform.h"

/**
 * @addtogroup hswicedpal
 * @{
 */

class GPIOWiced : virtual public HallSwitch::GPIO
{
    private:
        #define             UNUSED_PIN    (wiced_gpio_t)(WICED_GPIO_51 + 1) /**< Unused pin */
        wiced_gpio_t        pin;                                            /**< GPIO number */
        wiced_gpio_config_t config;                                         /**< GPIO configuration */
        VLogic_t            logic;                                          /**< Pin logic */

    public:
                                GPIOWiced     (wiced_gpio_t pin,
                                     wiced_gpio_config_t   config,
                                     VLogic_t              logic);
                                GPIOWiced     ();
                               ~GPIOWiced     ();
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
#endif /** HALL_PAL_WICED_HPP_ **/