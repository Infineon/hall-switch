/** 
 * @file        hall-switch-platf-ard.cpp
 * @brief       Hall Switch Arduino GPIO Hardware Interface
 * 
 *  Wraps the Arduino GPIO Reference Language calls
 * 
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#include <Arduino.h>
#include "hall-switch-platf-ard.h"

/**
 * @addtogroup hallgpioino
 * @{
 */

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
GPIOIno::Error_t GPIOIno::init()
{   
    pinMode(this->pin, this->mode);
    return OK;
}

/**
 * @brief   Enables the Arduino GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
GPIOIno::Error_t GPIOIno::enableInt(HallSwitch *ptr)
{
    attachInterrupt(digitalPinToInterrupt(this->pin), HallSwitch::Interrupt::isrRegister(ptr), CHANGE);
    return OK;
}

/**
 * @brief   Disables the Arduino GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
inline GPIOIno::Error_t GPIOIno::disableInt()
{
    detachInterrupt(digitalPinToInterrupt(this->pin));
    return OK;
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
inline GPIOIno::Error_t GPIOIno::write(VLevel_t level)
{
    digitalWrite(this->pin, GPIO_HIGH);
    return OK;
}

/**
 * @brief       Enables the Arduino GPIO output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline GPIOIno::Error_t GPIOIno::enable()
{
    if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    return OK;
}

/**
 * @brief       Disables the Arduino GPIO output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline GPIOIno::Error_t GPIOIno::disable()
{
   if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    return OK;
}

/** @} */
 
#ifdef XMC1100_XMC2GO                                       /**< xmc2go + Shield2Go  */ 
ArdHwPlatfPins_t TLE4964_3M_S2Go_Pins = {9, UNUSED_PIN};    /**< Pin connected to Q1 */                                                      
#elif ((XMC1100_Boot_Kit) \
      || (XMC4700_Relax_Kit) \
      || (ARDUINO_AVR_UNO))                                 /**< xmc arduino and arduino uno boards */  
ArdHwPlatfPins_t TLE4964_3M_S2Go_Pins = {3, UNUSED_PIN};    /**< Pin connected to Q1 */
#else
    # error "Board not yet defined. Please define the specific Arduino boards Pins"
#endif
