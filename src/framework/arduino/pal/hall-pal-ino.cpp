/** 
 * @file        hall-pal-ino.cpp
 * @brief       Hall Switch Arduino PAL  
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-pal-ino.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

#include <Arduino.h>
#include "../../../corelib/hall-switch-int.h"

/**
 * @brief GPIO Ino default constructor
 */
GPIOIno::GPIOIno()
: pin(0), mode(INPUT_PULLUP), logic(POSITIVE)
{

}

/**
 * @brief   GPIO Ino constructor
 */
GPIOIno::GPIOIno(uint8_t      pin, 
                 uint8_t      mode, 
                 VLogic_t     logic) 
: pin(pin), mode(mode), logic(logic) 
{

}

/**
 * @brief   Initializes the Arduino GPIO
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIOIno::init()
{   
    pinMode(this->pin, this->mode);
    return HallSwitch::OK;
}

/**
 * @brief   Deinitializes the Arduino GPIO
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIOIno::deinit()
{
    return HallSwitch::OK;
}

/**
 * @brief   Enables the Arduino GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIOIno::enableInt(HallSwitch *ptr)
{
    attachInterrupt(digitalPinToInterrupt(this->pin), HallSwitch::Interrupt::isrRegister(ptr), CHANGE);
    return HallSwitch::OK;
}

/**
 * @brief   Disables the Arduino GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
inline HallSwitch::Error_t GPIOIno::disableInt()
{
    detachInterrupt(digitalPinToInterrupt(this->pin));
    return HallSwitch::OK;
}

/**
 * @brief   Gets the latest Arduino interrupt event 
 * @return  GPIO interrupt event
 * @retval  INT_FALLING_EDGE if falling edge event
 * @retval  INT_RISING_EDGE if rising edge event
 */
inline GPIOIno::IntEvent_t GPIOIno::intEvent()
{
    int val = digitalRead(this->pin);
    if(val == LOW)
    {
        return INT_FALLING_EDGE;
    }
    else if(val == HIGH) 
    {
        return INT_RISING_EDGE;
    }
}

/**
 * @brief       Reads the Arduino GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIOIno::VLevel_t GPIOIno::read()
{
    return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief       Writes the Arduino GPIO output voltage level
 * @param[in]   level  Voltage level
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIOIno::write(VLevel_t level)
{
    digitalWrite(this->pin, level);
    return HallSwitch::OK;
}

/**
 * @brief       Enables the Arduino GPIO output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIOIno::enable()
{
    if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    return HallSwitch::OK;
}

/**
 * @brief       Disables the Arduino GPIO output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIOIno::disable()
{
   if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    return HallSwitch::OK;
}

#if (HALL_SPEED_ENABLED == 1)

TimerIno::TimerIno() : curTime(0)
{

}

TimerIno::~TimerIno()
{
    curTime = 0;
}

/**
 * @brief   Initialiazes the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline  HallSwitch::Error_t TimerIno::init()
{
    curTime = 0;
    return HallSwitch::OK;
}

/**
 * @brief   Deinitialiazes the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline  HallSwitch::Error_t TimerIno::deinit()
{
    curTime = 0;
    return HallSwitch::OK;
}

/**
 * @brief   Starts the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline HallSwitch::Error_t TimerIno::start()
{
    curTime = millis();
    return HallSwitch::OK;
}

/**
 * @brief       Elapsed time since the timer was started 
 * @param[out]  elapsed Time in milliseconds 
 * @return      Timer error code
 * @retval      OK if success (always)
 */
inline HallSwitch::Error_t TimerIno::elapsed(uint32_t &elapsed)
{
    elapsed = (millis() - curTime);
    return HallSwitch::OK;
}

/**
 * @brief   Stops the timer
 * @return  Timer error code
 * @retval  OK if success
 * @retval  OK if success (always)
 */
inline HallSwitch::Error_t TimerIno::stop()
{
    //Nothing
     return HallSwitch::OK;
}

/**
 * @brief       Introduces a delay during the specified time    
 * @param[in]   timeout    Delay time in milliseconds   
 * @return      Timer error code
 * @retval      OK if success
 * @retval      OK if success (always)
 */
inline HallSwitch::Error_t TimerIno::delay(uint32_t timeout)
{
    delay(timeout);
    return HallSwitch::OK;
}
 
 #endif /** HALL_SPEED_ENABLED */
 #endif /** HALL_SWITCH_FRAMEWORK **/
