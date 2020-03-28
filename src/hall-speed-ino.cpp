/** 
 * @file        hall-speed-ino.cpp
 * @brief       Hall Speed Arduino Class
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-speed-ino.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)
#if (HALL_SPEED_ENABLED == 1)

#include <Arduino.h>
#include "framework/arduino/pal/hall-pal-ino.h"

/**
 * @brief           Hall Speed Ino Constructor
 *                  Mandatory arguments: 
 *                      - Sensor output pin
 *                  Optional  arguments: 
 *                      - Magnetic poles pair number. By default 1 pair
 *                      - Speed units. By default Hertzs
 *                      - Interrupt callback. By default NULL. Required to enable interrupt mode
 *                      - Sensor power pin (only for switch powered mode platform). By default it is UNUSED
 *                 
 * @param[in]       outputPin   Sensor output pin
 * @param[in]       polesMum    Number of magnetic poles pair of the rotating B field
 * @param[in]       units       Speed units (RPM, Hertz, cps ...)
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode  
 * @param[in]       powerPin    Hall speed power pin. When passed, enabled the sensor switch controlled mode
 * @pre             None       
 */
HallSpeedIno::HallSpeedIno(uint8_t     outputPin,
                           uint8_t     polesNum,
                           HallSpeed::SpeedUnit_t units,
                           HallSpeed::CBackSpd_t  cBack,
                           uint8_t     powerPin)
:sp(new GPIOIno(outputPin, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    new TimerIno(),
    polesNum,
    units,
    cBack,
    (powerPin == UNUSED_PIN) ? NULL : new GPIOIno(outputPin, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}


/**
 * @brief           Hall Speed Ino Constructor with predefined Arduino hardware platform
 *                  Mandatory arguments: 
 *                      - Hardware platform 
 *                  Optional  arguments:
 *                      - Magnetic poles pair number. By default 1 pair
 *                      - Speed units. By default Hertzs 
 *                      - Interrupt callback. By default NULL. Required to enable interrupt mode
 * 
 * @param[in]       hwPlatf     Predefined Arduino hardware platform
 * @param[in]       polesMum    Number of magnetic poles pair of the rotating B field
 * @param[in]       units       Speed units (RPM, Hertz, cps ...)                
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode
 * @pre             None        
 */
HallSpeedIno::HallSpeedIno(PlatformIno_t  hwPlatf,
                           uint8_t        polesNum,
                           HallSpeed::SpeedUnit_t    units,
                           HallSpeed::CBackSpd_t     cBack)
:sp(new GPIOIno(hwPlatf.output, INPUT_PULLUP, HallSwitch::GPIO::VLogic_t::POSITIVE), 
    new TimerIno(),
    polesNum,
    units,
    cBack,
    (hwPlatf.power == UNUSED_PIN) ? NULL : new GPIOIno(hwPlatf.power, OUTPUT, HallSwitch::GPIO::VLogic_t::POSITIVE)){}

/**
 * @brief   Hall Speed Ino Destructor         
 * @pre     None
 */
HallSpeedIno::~HallSpeedIno()
{
    sp.~HallSpeed();
}

/**
 * @brief   Begins the speed sensor
 * @pre     None
 * @retval  0 if OK
 * @retval  -1 if error
 */
int HallSpeedIno::begin()
{
    int err = 0;
    
    if(HallSpeed::OK != sp.init())
        err = -1;
    if(HallSpeed::OK != sp.enable())
        err = -1;
    
    return err;
}

/**
 * @brief   Ends the speed sensor
 * @pre     Instance has called begin()
 * @retval  0 if OK
 * @retval  -1 if error
 */
int HallSpeedIno::end()
{
    int err = 0;
    
    if(HallSpeed::OK != sp.disable())
        err = -1;
    if(HallSwitch::OK != sp.deinit())
        err = -1;
    
    return err;
}

/**
 * @brief   Gets the speed value
 * @pre     Instance has called begin()
 * @return  Speed in the configured units
 * @retval  -1 if error
 */
double HallSpeedIno::getSpeed()
{
    double speed = 0.0;

    if(HallSwitch::OK != sp.updateSpeed())
    {
        speed = -1;
    }
    else
    {
        speed = sp.getSpeed();
    }
    
    return speed;
}

#endif /** HALL_SPEED_ENABLED */
#endif /** HALL_SWITCH_FRAMEWORK **/