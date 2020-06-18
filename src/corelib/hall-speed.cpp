/** 
 * @file        hall-speed.cpp
 * @brief       Hall Switch Speed Sensor
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hall-speed.hpp"

#if (HALL_SPEED_ENABLED == 1)

#include "../pal/hall-pal-gpio.hpp"
#include "../pal/hall-pal-timer.hpp"

double const HallSpeed::speedCoeff[] =
{
    1000.0,  /**< Hertz - cps (1000 ms)*/
    6283.2,  /**< Rad/s (2pi x 1000 ms) */
    60000.0  /**< RPM  (60 x 1000 ms)*/
};

/**
 * @brief   Hall Speed Default Constructor
 *          - Hardware interfaces pointers set to NULL
 *          - All speed parameters set to zero  
 * @pre     None  
 */
HallSpeed::HallSpeed()
{
    timer     = NULL;
    polesPair = 0;
    sUnits    = HERTZ;
    speed     = 0.0;
}

/**
 * @brief       Hall Speed Constructor
 * 
 *   Mandatory arguments: 
 *      - Sensor utput GPIO PAL interface pointer
 *      - Timer PAL interface pointer
 * 
 *   Optional  arguments: 
 *      - Magnetic poles pair number. By default 1 pair.
 *      - Speed units. By default Hertzs.
 *      - Interrupt callback. By default NULL. Required to enable interrupt mode.
 *      - Sensor power GPIO pointer (only for switch powered mode platform). By default it is NULL.
 * 
 * @param[in]   *output  Sensor output GPIO interface pointer
 * @param[in]   polesMum Number of magnetic poles pair of the rotating B field
 * @param[in]   units    Speed units (RPM, Hertz, cps ...)
 * @param[in]   cBack    Callback for interrupt mode. When passed, it enables interrupt mode
 * @param[in]   *power   Sensor switch power controlled GPIO interface pointer. Default NULL will set power mode to MAIN
 * 
 * @pre None
 */
HallSpeed::HallSpeed(GPIO       *output,
                    Timer       *timer,
                    uint8_t     polesNum,
                    SpeedUnit_t units,
                    CBackSpd_t  cBack,
                    GPIO        *power                               
) : HallSwitch(output, (HallSwitch::CBack_t)cBack, power)
{
    this->timer = timer;
    this->polesPair = polesNum;
    this->sUnits = units;
    this->speed  = 0.0;
}

/**
 * @brief   Hall Speed Destructor
 *          Disables the sensor:
 *              - Stops and disables the timer interface.
 *              - Stops and disable the GPIO interface.
 *              - If "interrupt measuring mode" is enabled, the interrupt is disabled
 *              - If "switch power mode" is configured, the sensor power is disabled          
 * @pre    None
 */
HallSpeed::~HallSpeed()
{
    if(status == POWER_ON)
        disable();
    if(status == POWER_OFF)
        deinit();
}

/**
 * @brief   Initializes the hardware interfaces
 * @pre     None
 * @return  HallSwitch error code
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error
 */
HallSwitch::Error_t HallSpeed::init()
{
    Error_t err = OK;
    
    err = HallSwitch::init();
    if(err != OK) return err;

    if(timer == NULL)
        return INTF_ERROR;

    err = timer->init();
    if(err != OK) return err;
    
    status = INITED;

    return err;
}

/**
 * @brief   Deinitializes the hardware interfaces
 * @pre     Instance has called init()
 * @return  HallSwitch error code
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error
 */
HallSwitch::Error_t HallSpeed::deinit()
{
    Error_t err = OK;

    err = HallSwitch::deinit();
    if(err != OK) return err;

    err = timer->deinit();
    if(err != OK) return err;

    status    = UNINITED;
    bfieldVal = B_FIELD_UNDEF;
    speed     = 0.0;

    return err;
}

/**
 * @brief   Enables the sensor
 *          - If "switch power mode " is configured, the sensor is powered up
 *          - If "interrupt measuring mode" is configured, the interrupt is enabled
 * 
 * @pre     Instance has called init()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallSwitch::Error_t HallSpeed::enable()
{
   Error_t err = OK;

    err = HallSwitch::enable();
    if(err != OK) return err;
    
    err = timer->start();
    if(err != OK) return err;

    status = POWER_ON;

    return err;
}

/**
 * @brief   Disables the sensor
 *              - If the "interrupt measuring mode" is configured, the interrupt is disabled 
 *              - If the "switch power mode" is configured, the sensor is powered off
 
 * @pre     Instance has called enable()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallSwitch::Error_t HallSpeed::disable()
{
   Error_t err = OK;

    err = timer->stop();
    if(err != OK) return err;

    err = HallSwitch::disable();
    if(err != OK) return err;
    
    status = POWER_OFF; 

    return err;
}

/**
 * @brief   Updates object speed value 
 * 
 *  The "speed" object member is updated with the read value.
 * 
 * @pre     Instance has called enable()
 * @return  HallSwitch error code 
 * @retval  OK if success
 * @retval  INTF_ERROR if hardware interface error     
 */
HallSwitch::Error_t HallSpeed::updateSpeed()
{
    static bool waitingRisingEdge = true;

    if(waitingRisingEdge && (output->read() == GPIO::VLevel_t::GPIO_HIGH))
    {
        bfieldVal = B_FIELD_OFF;
        calculateSpeed();
        timer->stop();
        timer->start();
        waitingRisingEdge = false;
    }
    else if(!waitingRisingEdge && (output->read() == GPIO::VLevel_t::GPIO_LOW))
    {
        bfieldVal = B_FIELD_ON;
        waitingRisingEdge = true;
    }
}

/**
 * @brief   Gets speed value
 * 
 *  This functions returns the last read value updated in the object member speed variable,
 *  either from a explicit updateSpeed() call or due to an interrupt event.
 * 
 * @pre     If polling mode is used, updateSpeed() has to be called preivously in order to get the actual value.
 * @return  Speed value
 */
double HallSpeed::getSpeed()
{
    return speed;
}

/**
 * @brief   Interrupt mode callback function
 *  
 *  The class updates on its own speed member to the when the interrupt occurs
 *  Passed as interrupt callback handler.
 * 
 * @return  void
 */
void HallSpeed::callback()
{
    GPIO::IntEvent_t event = output->intEvent();

    if(event == GPIO::IntEvent_t::INT_RISING_EDGE)
    {
        bfieldVal = B_FIELD_OFF;
        calculateSpeed();
        timer->stop();
        timer->start();
    }
    else if(event == GPIO::IntEvent_t::INT_FALLING_EDGE)
    {
       bfieldVal = B_FIELD_ON;
    }

    CBackSpd_t callb = (CBackSpd_t)cBack;
    callb(speed);
}

/**
 * @brief   Calculates the speed in the configured units
 *  
 *  Called by updateSpeed() or in the callback() interrupt to update the object speed member variable.
 *  
 * @return  void
 */
void HallSpeed::calculateSpeed()
{
    uint32_t elapsed = 0.0;
    timer->elapsed(elapsed);
    speed = HallSpeed::speedCoeff[sUnits]/((double)polesPair * (double)elapsed);
}

#endif /** HALL_SPEED_ENABLED */
