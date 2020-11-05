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
GPIORpi::GPIORpi(   uint8_t     pin,
                    uint8_t     mode,
                    VLogic_t    logic)
: pin(pin), mode(mode), logic(logic)
{

}

/**
 * @brief   GPIO Rpi constructor
 */
GPIORpi::GPIORpi() 
: pin(4), mode(INPUT), logic(POSITIVE) 
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
 * @retval  OK if success
 * @retval  INTF_ERROR if initialization error
 */
HallSwitch::Error_t GPIORpi::init()
{
    HallSwitch::Error_t err = HallSwitch::OK;
    if (wiringPiSetup() < 0)
        err = HallSwitch::INTF_ERROR;

    pinMode(this->pin, this->mode);

    return err;
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
 * @retval  OK if success
 * @retval  INTF_ERROR if error
 */
HallSwitch::Error_t GPIORpi::enableInt(HallSwitch *ptr)
{
    HallSwitch::Error_t err = HallSwitch::OK;
    if (0 > wiringPiISR(this->pin, INT_EDGE_BOTH, (void (*)())HallSwitch::Interrupt::isrRegister(ptr)))
        err = HallSwitch::INTF_ERROR;
    
    return err;
}

/**
 * @brief   Disables the Raspberry Pi GPIO interrupt
 * @note    Not supported by low level framework.
 * @return  GPIO error code
 * @retval  INTF Error always
 */
inline HallSwitch::Error_t GPIORpi::disableInt()
{
    return HallSwitch::INTF_ERROR;
}

/**
 * @brief   Gets the latest Raspberry Pi interrupt event 
 * @return  GPIO interrupt event
 * @retval  INT_FALLING_EDGE if falling edge event
 * @retval  INT_RISING_EDGE if rising edge event
 */
inline GPIORpi::IntEvent_t GPIORpi::intEvent()
{
    IntEvent_t edge = INT_FALLING_EDGE;
    
    int val = digitalRead(this->pin);
    if(val == LOW)
    {
        edge = INT_FALLING_EDGE;
    }
    else if(val == HIGH) 
    {
        edge = INT_RISING_EDGE;
    }

    return edge;
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
 * @retval      OK always
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
 * @retval      OK always
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
 * @retval      OK always
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

#endif /** HALL_SWITCH_FRAMEWORK **/
