/** 
 * @file        hall-speed.cpp
 * @brief       Hall Switch Speed Sensor
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#include "hall-speed.h"
#include "../pal/hall-pal-gpio.h"
#include "../pal/hall-pal-timer.h"

double const HallSpeed::speedCoeff[] =
{
    1000.0,  /**< Hertz - cps (1000 ms)*/
    6283.2,  /**< Rad/s (2pi x 1000 ms) */
    60000.0  /**< RPM  (60 x 1000 ms)*/
};

HallSpeed::HallSpeed()
{
    timer     = NULL;
    polesPair = 0;
    sUnits    = 0;
    speed     = 0.0;
}

/**
 * @brief       Hall Switch Constructor
 * 
 *   Mandatory arguments: 
 *      - sensor output GPIO pointer
 * 
 *   Optional  arguments: 
 *      - interrupt callback. By default NULL. Required to enable interrupt mode.
 *      - sensor power GPIO pointer (only for switch powered mode platform). By default it is NULL.
 * 
 * @param[in]   *output Sensor output GPIO interface pointer
 * @param[in]   cBack   Callback for interrupt mode. When passed, it enables interrupt mode
 * @param[in]   *power  Sensor switch poewr controller GPIO interface pointer. Default NULL will set power mode to MAIN
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

HallSwitch::Error_t HallSpeed::begin()
{
    Error_t err = OK;
    
    err = HallSwitch::begin();
    if(err != OK) return err;

    if(timer == NULL)
        return INTF_ERROR;

    err = timer->init();
    if(err != OK) return err;
    
    status = INITED;

    return err;
}

HallSwitch::Error_t HallSpeed::end()
{
    Error_t err = OK;

    err = HallSwitch::end();
    if(err != OK) return err;

    err = timer->deinit();
    if(err != OK) return err;

    status    = UNINITED;
    bfieldVal = B_FIELD_UNDEF;
    speed     = 0.0;

    return err;
}

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

double HallSpeed::getSpeed()
{
    return speed;
}

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

void HallSpeed::calculateSpeed()
{
    uint32_t elapsed = 0.0;
    timer->elapsed(elapsed);
    speed = HallSpeed::speedCoeff[sUnits]/((double)polesPair * (double)elapsed);
}

