/** 
 * @file        hall-switch-ard.h
 * @brief       Hall Switch Arduino GPIO Hardware Interface
 * @date        July 2019
 * @copyright   Copyright (c) 2019 Infineon Technologies AG
 */

#ifndef HALL_SWITCH_ARD_H_
#define HALL_SWITCH_ARD_H_

#include <stdint.h>
#include "../../common/hall-switch.h"
#include "../../common/hall-speed.h"


class GPIOIno : virtual public HallSwitch::GPIO, public HallSwitch::Interrupt 
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
        Error_t       init          ();            
        Error_t       deinit        ();
        Error_t       enableInt     (HallSwitch *ptr);    
        Error_t       disableInt    ();
        IntEvent_t    intEvent      ();
        VLevel_t      read          ();
        Error_t       write         (VLevel_t level);
        Error_t       enable        ();
        Error_t       disable       ();
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
}ArdHwPlatfPins_t;

/**
 * @addtogroup tle49643ms2go
 * @{
 */ 
extern ArdHwPlatfPins_t TLE4964_3M_S2Go_Pins;   /**< TLE4964 3M Shield 2Go Pins */
extern ArdHwPlatfPins_t TL4922_2GoKit_Pins;     /**< TLE4922 Kit 2Go Pins */ 
/** @} */

#endif /** HALL_SWITCH_ARD_H_ **/
