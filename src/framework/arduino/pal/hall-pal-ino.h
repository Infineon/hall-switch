/** 
 * @file        hall-switch-ard.h
 * @brief       Hall Switch Arduino GPIO Hardware Interface
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_ARD_H_
#define HALL_SWITCH_ARD_H_

#include <stdint.h>
#include "../../corelib/hall-switch.h"
#include "../../corelib/hall-speed.h"
#include "../../corelib/hall-switch-int.h"
#include "../../pal/hall-pal-gpio.h"
#include "../../pal/hall-pal-timer.h"


class GPIOIno : virtual public HallSwitch::GPIO //, public HallSwitch::Interrupt 
{
    private:
        #define   UNUSED_PIN    0xFF    /**< Unused pin */
        uint8_t     pin;                /**< Pin number*/
        uint8_t     mode;               /**< Pin mode*/
        VLogic_t    logic;              /**< Pin logic */

    public:
                                GPIOIno       ();
                                GPIOIno       (uint8_t pin, 
                                               uint8_t mode, 
                                               VLogic_t logic);
        HallSwitch::Error_t     init          ();            
        HallSwitch::Error_t     deinit        ();
        HallSwitch::Error_t     enableInt     (HallSwitch *ptr);    
        HallSwitch::Error_t     disableInt    ();
        IntEvent_t              intEvent      ();
        VLevel_t                read          ();
        HallSwitch::Error_t     write         (VLevel_t level);
        HallSwitch::Error_t     enable        ();
        HallSwitch::Error_t     disable       ();
};

class TimerIno: virtual public HallSpeed::Timer
{
    public:
                                    TimerIno();
                                   ~TimerIno();
        HallSwitch::Error_t         init    ();
        HallSwitch::Error_t         deinit  ();
        HallSwitch::Error_t         start   ();
        HallSwitch::Error_t         elapsed (uint32_t &elapsed);
        HallSwitch::Error_t         stop    ();
        HallSwitch::Error_t         delay   (uint32_t timeout);

    private:
        uint32_t curTime;   /**< Current time */
};

/**
 * @brief Arduino Hardware Platform Pins
 */
typedef struct 
{
    uint8_t output;     /**< Output pin */
    uint8_t power;      /**< Power pin */
}PlatformIno_t;

#endif /** HALL_SWITCH_ARD_H_ **/
