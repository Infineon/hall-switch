:q/** 
 * @file        hall-switch-wiced.cpp
 * @brief       Hall Switch WICED API
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-switch-wiced.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

 /**
 * @brief           Hall switch WICED instance constructor with WICED pins
 * 
 *  Mandatory arguments:
 *   - sensor output pin
 * 
 *  Optional  arguments:
 *   - interrupt callback. By default NULL. Required to enable interrupt mode.
 *   - sensor power pin (only for switch powered mode platform). By default it is UNUSED.
 *
 * @param[in]       outputPin   Hall switch output pin
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.
 * @param[in]       powerPin    Hall switch power pin. When passed, enabled the sensor switch controlled mode.
 * @return          void
 */
HallSwitchWiced::HallSwitchWiced(wiced_gpio_t   outputPin,
                                 CBack_t        cBack,
                                 wiced_gpio_t   powerPin)
:HallSwitch(new GPIOWiced(outputPin, INPUT_PULL_UP, GPIO::VLogic_t::POSITIVE),
            cBack,
            (powerPin == (wiced_gpio_t)UNUSED_PIN) ? NULL : new GPIOWiced(outputPin, OUTPUT_PUSH_PULL, GPIO::VLogic_t::POSITIVE)){ }

/**
 * @brief           Hall switch WICED instance constructor with predefined WICED hardware platform
 * 
 *  Mandatory arguments:
 *   - hardware platform
 *                  
 *  Optional  arguments:
 *   - interrupt callback. By default NULL. Required to enable interrupt mode.
 *
 * @param[in]       hwPlatf     Predefined WICED hardware platform.
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.
 * @return          void
 */
HallSwitchWiced::HallSwitchWiced(PlatformWICED_t hwPlatf,
                                 CBack_t         cBack)
{

    this->output    = new GPIOWiced(hwPlatf.output, INPUT_PULL_UP, GPIO::VLogic_t::POSITIVE);
    this->cBack     = cBack;
    if(this->cBack == NULL)
        this->measMode  = POLLING;
    else
        this->measMode = INTERRUPT;

    if(hwPlatf.power == (wiced_gpio_t)UNUSED_PIN)
    {
        this->power     = NULL;
        this->powerMode = MAIN;
    }
    else
    {
        this->power  =   new GPIOWiced(hwPlatf.power, OUTPUT_PUSH_PULL, GPIO::VLogic_t::POSITIVE);
        this->powerMode = SWITCH;
    }
}

#endif /** HALL_SWITCH_FRAMEWORK **/