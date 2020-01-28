/** 
 * @file        hall-switch-wiced.cpp
 * @brief       Hall Switch GPIO WICED Hardware Interface
 * 
 *  Wraps the WICED GPIO library
 * 
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 */

#ifdef HALL_SWITCH_WICED_PLATFORM_ENABLED

#include "hall-switch-wiced.h"

/**
 * @addtogroup hallgpiowiced
 * @{
 */

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
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INIT_ERROR if initialization error
 */
inline GPIOWiced::Error_t GPIOWiced::init()
{   
    Error_t err = OK;
    if(WICED_SUCCESS != wiced_gpio_init(pin, config))
        err = INIT_ERROR;

    return err;
}

/**
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INIT_ERROR if initialization error
 */
inline GPIOWiced::Error_t GPIOWiced::deinit()
{
    Error_t err = OK;
    if(WICED_SUCCESS != wiced_gpio_deinit(pin))
        err = INIT_ERROR;

    return err;
}

/**
 * @brief   Enables the WICED GPIO interrupt
 * @return  GPIO error code
 * @retval      OK if success
 * @retval      INIT_ERROR if initialization error
 */
inline GPIOWiced::Error_t GPIOWiced::enableInt(HallSwitch *ptr)
{
    Error_t err = OK;

    if(WICED_SUCCESS != wiced_gpio_input_irq_enable(pin,IRQ_TRIGGER_BOTH_EDGES, (wiced_gpio_irq_handler_t)(HallSwitch::Interrupt::isrRegister(ptr)),NULL))
        err = INIT_ERROR;

    return err;
}

/**
 * @brief   Disables the WICED GPIO interrupt
 * @return  GPIO error code
 * @retval  OK always
 */
inline GPIOWiced::Error_t GPIOWiced::disableInt()
{
    Error_t err = OK;

    if(WICED_SUCCESS != wiced_gpio_input_irq_disable(pin))
        err = INIT_ERROR;

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
 * @retval      WRITE_ERROR if write error
 */
inline GPIOWiced::Error_t GPIOWiced::write(VLevel_t level)
{
    Error_t err = OK;

    if(GPIO_LOW == level)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = WRITE_ERROR;
    }
    else if(GPIO_HIGH == level)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = WRITE_ERROR;
    }

    return err;
}

/**
 * @brief       Enables the Arduino GPIO output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline GPIOWiced::Error_t GPIOWiced::enable()
{
    Error_t err = OK;

    if(this->logic == POSITIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = WRITE_ERROR;
    }
    else if(this->logic == NEGATIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = WRITE_ERROR;
    }
    return err;
}

/**
 * @brief       Disables the Arduino GPIO output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      WRITE_ERROR if write error
 */
inline GPIOWiced::Error_t GPIOWiced::disable()
{
    Error_t err = OK;

    if(this->logic == POSITIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_low(pin))
            err = WRITE_ERROR;
    }
    else if(this->logic == NEGATIVE)
    {
        if(WICED_SUCCESS != wiced_gpio_output_high(pin))
            err = WRITE_ERROR;
    }
    return err;
}

/** @} */
 
/**
 * @brief           Hall switch WICED instance constructor with WICED pins
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
HallSwitchWiced::HallSwitchWiced(wiced_gpio_t   outputPin,
                                 CBack_t        cBack,
                                 wiced_gpio_t   powerPin)
:HallSwitch(new GPIOWiced(outputPin, INPUT_PULL_UP, GPIO::VLogic_t::POSITIVE),
            cBack,
            (powerPin == (wiced_gpio_t)UNUSED_PIN) ? NULL : new GPIOWiced(outputPin, OUTPUT_PUSH_PULL, GPIO::VLogic_t::POSITIVE)){ }

/**
 * @brief           Hall switch WICED instance constructor with predefined WICED hardware platform
 *                  Mandatory arguments:
 *                      - Hardware platform
 *                  Optional  arguments:
 *                      - interrupt callback. By default NULL. Required to enable interrupt mode.
 *
 * @param[in]       hwPlatf     Predefined WICED hardware platform.
 * @param[in]       cBack       Callback for interrupt mode. When passed, it enables interrupt mode.
 * @return          void
 */
HallSwitchWiced::HallSwitchWiced(WICEDHwPlatf_t &hwPlatf,
                                 CBack_t        cBack)
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

/**
 *  TLE4964 3M Shield 2Go + MyIOT Adapter + CYW943907AEVAL1F Eval Kit
 */
HallSwitchWiced::WICEDHwPlatf_t TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F =
{
    .output = WICED_GPIO_9,
    .power  = UNUSED_PIN
};

#endif