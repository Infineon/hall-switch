/** 
 * @file        hall-pal-rpi.cpp
 * @brief       Hall Switch Raspberry Pi PAL  
 * @date        August 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-pal-rpi.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_RPI)

#include "../../../corelib/hall-switch-int.hpp"

/**
 * @brief GPIO Rpi default constructor
 */
GPIORpi::GPIORpi()
: pin(0), mode(INPUT), logic(POSITIVE)
{

}

/**
 * @brief   GPIO Rpi constructor
 */
GPIORpi::GPIORpi(uint8_t      pin, 
                 uint8_t      mode, 
                 VLogic_t     logic) 
: pin(pin), mode(mode), logic(logic) 
{

}

/**
 * @brief   GPIO Rpi destructor
 */
GPIORpi::~GPIORpi()
{

}


/**
 * @brief   Initializes the Raspberry Pi GPIO
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIORpi::init()
{   
    if (wiringPiSetup() == -1) return HallSwitch::CONF_ERROR;

    pinMode(this->pin, this->mode);

    return HallSwitch::OK;
}

/**
 * @brief   Deinitializes the Raspberry Pi GPIO
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIORpi::deinit()
{
    return HallSwitch::OK;
}

/**
 * @brief   Enables the Raspberry Pi GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
HallSwitch::Error_t GPIORpi::enableInt(HallSwitch *ptr)
{
    //attachInterrupt(digitalPinToInterrupt(this->pin), (void (*)())HallSwitch::Interrupt::isrRegister(ptr), CHANGE);
    return HallSwitch::OK;
}

/**
 * @brief   Disables the Raspberry Pi GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
inline HallSwitch::Error_t GPIORpi::disableInt()
{
    //detachInterrupt(digitalPinToInterrupt(this->pin));
    return HallSwitch::OK;
}

/**
 * @brief   Gets the latest Raspberry Pi interrupt event 
 * @return  GPIO interrupt event
 * @retval  INT_FALLING_EDGE if falling edge event
 * @retval  INT_RISING_EDGE if rising edge event
 */
inline GPIORpi::IntEvent_t GPIORpi::intEvent()
{
    /*IntEvent_t edge = INT_FALLING_EDGE;
    
    int val = digitalRead(this->pin);
    if(val == LOW)
    {
        edge = INT_FALLING_EDGE;
    }
    else if(val == HIGH) 
    {
        edge = INT_RISING_EDGE;
    }

    return edge;*/
    return (IntEvent_t) 0;
}

/**
 * @brief       Reads the Raspberry Pi GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIORpi::VLevel_t GPIORpi::read()
{
    return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief       Writes the Raspberry Pi GPIO output voltage level
 * @param[in]   level  Voltage level
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIORpi::write(VLevel_t level)
{
    digitalWrite(this->pin, level);
    return HallSwitch::OK;
}

/**
 * @brief       Enables the Raspberry Pi GPIO output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIORpi::enable()
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
 * @brief       Disables the Raspberry Pi GPIO output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline HallSwitch::Error_t GPIORpi::disable()
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

TimerRpi::TimerRpi() : curTime(0)
{

}

TimerRpi::~TimerRpi()
{
    curTime = 0;
}

/**
 * @brief   Initialiazes the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline  HallSwitch::Error_t TimerRpi::init()
{
    curTime = 0;
    return HallSwitch::OK;
}

/**
 * @brief   Deinitialiazes the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline  HallSwitch::Error_t TimerRpi::deinit()
{
    curTime = 0;
    return HallSwitch::OK;
}

/**
 * @brief   Starts the timer
 * @return  Timer error code
 * @retval  OK if success (always)
 */
inline HallSwitch::Error_t TimerRpi::start()
{
    //curTime = millis();
    return HallSwitch::OK;
}

/**
 * @brief       Elapsed time since the timer was started 
 * @param[out]  elapsed Time in milliseconds 
 * @return      Timer error code
 * @retval      OK if success (always)
 */
inline HallSwitch::Error_t TimerRpi::elapsed(uint32_t &elapsed)
{
    //elapsed = (millis() - curTime);
    return HallSwitch::OK;
}

/**
 * @brief   Stops the timer
 * @return  Timer error code
 * @retval  OK if success
 * @retval  OK if success (always)
 */
inline HallSwitch::Error_t TimerRpi::stop()
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
inline HallSwitch::Error_t TimerRpi::delay(uint32_t timeout)
{
    //delay(timeout);
    return HallSwitch::OK;
}
 
 #endif /** HALL_SPEED_ENABLED */
 #endif /** HALL_SWITCH_FRAMEWORK **/
