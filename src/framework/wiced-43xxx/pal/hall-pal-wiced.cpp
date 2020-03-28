/** 
 * @file        hall-pal-wiced.cpp
 * @brief       Hall Switch WICED PAL 
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 */

#include "hall-pal-wiced.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

#include "hall-switch-int.h"

/**
 * @brief GPIO WICED default constructor
 */
GPIOWiced::GPIOWiced(wiced_gpio_t          pin,
                     wiced_gpio_config_t   config,
                     VLogic_t              logic)
: pin(pin), config(config), logic(logic)
{

}

/**
 * @brief GPIO WICED default constructor
 */
GPIOWiced::GPIOWiced()
:pin(WICED_GPIO_1), config(INPUT_HIGH_IMPEDANCE), logic(POSITIVE)
{

}

/**
 * @brief GPIO WICED destructor
 */
GPIOWiced::~GPIOWiced()
{
    disable();
    deinit();
}

/**
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if initialization error
 */
inline HallSwitch::Error_t GPIOWiced::init()
{   
    HallSwitch::Error_t err = HallSwitch::OK;
    if(WICED_SUCCESS != wiced_gpio_init(pin, config))
        err = HallSwitch::INTF_ERROR;

    return err;
}

/**
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if deinitialization error
 */
inline HallSwitch::Error_t GPIOWiced::deinit()
{
    HallSwitch::Error_t err = HallSwitch::OK;
    if(WICED_SUCCESS != wiced_gpio_deinit(pin))
        err = HallSwitch::INTF_ERROR;

    return err;
}

/**
 * @brief   Enables the WICED GPIO interrupt
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if error
 */
inline HallSwitch::Error_t GPIOWiced::enableInt(HallSwitch *ptr)
{
    HallSwitch::Error_t err = HallSwitch::OK;

    if(WICED_SUCCESS != wiced_gpio_input_irq_enable(pin,IRQ_TRIGGER_BOTH_EDGES, (wiced_gpio_irq_handler_t)(HallSwitch::Interrupt::isrRegister(ptr)),NULL))
        err = HallSwitch::INTF_ERROR;

    return err;
}

/**
 * @brief   Disables the WICED GPIO interrupt
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if error
 */
inline HallSwitch::Error_t GPIOWiced::disableInt()
{
    HallSwitch::Error_t err = HallSwitch::OK;

    if(WICED_SUCCESS != wiced_gpio_input_irq_disable(pin))
        err = HallSwitch::INTF_ERROR;

    return err;
}

/**
 * @brief   Gets the latest WICED interrupt event
 * @return  GPIO interrupt event
 * @retval  INT_FALLING_EDGE if falling edge event
 * @retval  INT_RISING_EDGE if rising edge event
 */
inline GPIOWiced::IntEvent_t GPIOWiced::intEvent()
{
    IntEvent_t event = INT_FALLING_EDGE;
    wiced_bool_t val = wiced_gpio_input_get(this->pin);

    if(WICED_FALSE == val )
    {
        event = INT_FALLING_EDGE;
    }
    else if(WICED_TRUE == val)
    {
        event = INT_RISING_EDGE;
    }

    return event;
}

/**
 * @brief       Reads the WICED GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIOWiced::VLevel_t GPIOWiced::read()
{
    return (VLevel_t) wiced_gpio_input_get(pin);
}

/**
 * @brief       Writes the WICED GPIO output voltage level
 * @param[in]   level  Voltage level
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline HallSwitch::Error_t GPIOWiced::write(VLevel_t level)
{
    HallSwitch::Error_t err = HallSwitch::OK;

    if(GPIO_LOW == level)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = HallSwitch::INTF_ERROR;
    }
    else if(GPIO_HIGH == level)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = HallSwitch::INTF_ERROR;
    }

    return err;
}

/**
 * @brief       Enables the WICED output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline HallSwitch::Error_t GPIOWiced::enable()
{
    HallSwitch::Error_t err = HallSwitch::OK;

    if(this->logic == POSITIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = HallSwitch::INTF_ERROR;
    }
    else if(this->logic == NEGATIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = HallSwitch::INTF_ERROR;
    }
    return err;
}

/**
 * @brief       Disables the WICED output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline HallSwitch::Error_t GPIOWiced::disable()
{
    HallSwitch::Error_t err = HallSwitch::OK;

    if(this->logic == POSITIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = HallSwitch::INTF_ERROR;
    }
    else if(this->logic == NEGATIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = HallSwitch::INTF_ERROR;
    }
    return err;
}

#endif /** HALL_SWITCH_FRAMEWORK **/
