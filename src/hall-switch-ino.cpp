/** 
 * @file        hall-switch-ino.cpp
 * @brief       Hall Switch Arduino Class
 *                  
 *  Arduino wrapper for hall switch hardware abstraction layer
 *      - Hardware Allocation using direct arduino pins
 * 
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#include "hall-switch-ino.h"

/**
 * @brief           Hall switch ino instance constructor with Arduino pins
 *                  Mandatory arguments: 
 *                      - sensor output pin
 *                  Optional  arguments: 
 *                      - interrupt callback. By default NULL. Required to enable interrupt mode.
 *                      - sensor power pin (only for switch powered mode platform). By default it is UNUSED.
 *                 
 * @param[in]       outputPin   Hall switch output pin
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.  
 * @param[in]       powerPin    Hall switch power pin. When passed, enabled the sensor switch controlled mode.
 * @return          void         
 */
HallSwitchIno::HallSwitchIno(uint8_t               outputPin, 
                             HallSwitch::CBack_t   cBack,
                             uint8_t               powerPin)
:sw(new GPIOIno(outputPin, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    cBack,
    (powerPin == UNUSED_PIN) ? NULL : new GPIOIno(outputPin, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}

/**
 * @brief           Hall switch ino instance constructor with predefined Arduino hardware platform
 *                  Mandatory arguments: 
 *                      - Hardware platform 
 *                  Optional  arguments: 
 *                      - interrupt callback. By default NULL. Required to enable interrupt mode.
 *                  
 * @param[in]       hwPlatf     Predefined Arduino hardware platform.
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.  
 * @return          void         
 */
HallSwitchIno::HallSwitchIno(PlatformIno_t             hwPlatf,
                             HallSwitch::CBack_t       cBack)
:sw(new GPIOIno(hwPlatf.output, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    cBack,
    (hwPlatf.power == UNUSED_PIN) ? NULL : new GPIOIno(hwPlatf.power, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}

HallSwitchIno::~HallSwitchIno()
{
    sw.~HallSwitch();
}

int HallSwitchIno::begin()
{
    int err = 0;
    
    if(HallSwitch::OK != sw.init())
        err = -1;
    if(HallSwitch::OK != sw.enable())
        err = -1;
    
    return err;
}

int HallSwitchIno::end()
{
    int err = 0;
    
    if(HallSwitch::OK != sw.disable())
        err = -1;
    if(HallSwitch::OK != sw.deinit())
        err = -1;
    
    return err;
}

int HallSwitchIno::getBField()
{
    sw.updateBField();

    return (int)(sw.getBField());
}