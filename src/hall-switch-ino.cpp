/** 
 * @file        hall-switch-ino.cpp
 * @brief       Hall Switch Arduino API 
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-switch-ino.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

#include <Arduino.h>
#include "framework/arduino/pal/hall-pal-ino.hpp"

/**
 * @brief           Hall Switch Ino Constructor 
 * 
 * Mandatory arguments: 
 *  - Output pin
 * Optional  arguments: 
 *  - Interrupt callback. By default NULL. Required to enable interrupt mode
 *  - Power pin. By default not allocated 
 *    
 * @param[in]       outputPin   Sensor output pin
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode
 * @param[in]       powerPin    Sensor switch power controller pin  
 * @pre             None         
 */
HallSwitchIno::HallSwitchIno(uint8_t               outputPin, 
                             HallSwitch::CBack_t   cBack,
                             uint8_t               powerPin)
:sw(new GPIOIno(outputPin, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    cBack,
    (powerPin == UNUSED_PIN) ? NULL : new GPIOIno(powerPin, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}

/**
 * @brief           Hall Switch Ino Constructor with predefined Arduino hardware platform
 *                 
 *  Mandatory arguments: 
 *   - Hardware platform 
 *  Optional  arguments: 
 *   - Interrupt callback. By default NULL. Required to enable interrupt mode
 *                  
 * @param[in]       hwPlatf     Predefined Arduino hardware platform
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode  
 * @pre             None         
 */
HallSwitchIno::HallSwitchIno(PlatformIno_t             hwPlatf,
                             HallSwitch::CBack_t       cBack)
:sw(new GPIOIno(hwPlatf.output, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    cBack,
    (hwPlatf.power == UNUSED_PIN) ? NULL : new GPIOIno(hwPlatf.power, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}

/**
 * @brief   Hall Switch Ino Destructor         
 * @pre    None
 */
HallSwitchIno::~HallSwitchIno()
{
    sw.~HallSwitch();
}

/**
 * @brief   Begins the switch
 * @pre     None
 * @retval  0 if OK
 * @retval  -1 if error
 */
int HallSwitchIno::begin()
{
    int err = 0;
    
    if(HallSwitch::OK != sw.init())
        err = -1;
    if(HallSwitch::OK != sw.enable())
        err = -1;
    
    return err;
}

/**
 * @brief   Ends the switch
 * @pre     Instance has called begin()
 * @retval  0 if OK
 * @retval  -1 if error
 */
int HallSwitchIno::end()
{
    int err = 0;
    
    if(HallSwitch::OK != sw.disable())
        err = -1;
    if(HallSwitch::OK != sw.deinit())
        err = -1;
    
    return err;
}

/**
 * @brief   Gets the switch output value
 * @pre     Instance has called begin()
 * @retval  1 if magnetic field present
 * @retval  0 if magnetic field not present
 * @retval  -1 if error
 */
int HallSwitchIno::getBField()
{
    int bfield = 0;
    
    if(HallSwitch::OK != sw.updateBField())
    {    
        bfield = -1;
    }
    else
    {
        bfield = sw.getBField();
    }

    return bfield;
}

#endif /** HALL_SWITCH_FRAMEWORK **/