/** 
 * @file        hall-switch-rpi.cpp
 * @brief       Hall Switch Raspberry Pi API
 * @date        August 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-switch-rpi.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

 /**
 * @brief           Hall switch Raspberry Pi instance constructor with Raspberry Pi pins
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

//HallSwitchRpi::HallSwitchRpi() {}
/*
HallSwitchRpi::HallSwitchRpi(uint8_t   outputPin,
                                 CBack_t        cBack,
                                 uint8_t   powerPin)
:HallSwitch(new GPIORpi(outputPin, INPUT_PULL_UP, GPIO::VLogic_t::POSITIVE),
            cBack,
            (powerPin == UNUSED_PIN) ? NULL : new GPIORpi(outputPin, OUTPUT_PUSH_PULL, GPIO::VLogic_t::POSITIVE)){ }

/**
 * @brief           Hall switch Raspberry Pi instance constructor with predefined Raspberry Pi hardware platform
 * 
 *  Mandatory arguments:
 *   - hardware platform
 *                  
 *  Optional  arguments:
 *   - interrupt callback. By default NULL. Required to enable interrupt mode.
 *
 * @param[in]       hwPlatf     Predefined Raspberry Pi hardware platform.
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.
 * @return          void
 */


HallSwitchRpi::HallSwitchRpi(){}

HallSwitchRpi::HallSwitchRpi(PlatformRpi_t hwPlatf,
                                 CBack_t         cBack)
{

    this->output    = new GPIORpi(hwPlatf.output, 0, GPIO::VLogic_t::POSITIVE);
    this->cBack     = cBack;
    if(this->cBack == NULL)
        this->measMode  = POLLING;
    else
        this->measMode = INTERRUPT;

    if(hwPlatf.power == UNUSED_PIN)
    {
        this->power     = NULL;
        this->powerMode = MAIN;
    }
    else
    {
        this->power  =   new GPIORpi(hwPlatf.power, 0, GPIO::VLogic_t::POSITIVE);
        this->powerMode = SWITCH;
    }
}

#endif /** HALL_SWITCH_FRAMEWORK **/
