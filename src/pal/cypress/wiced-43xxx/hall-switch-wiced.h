/** 
 * @file        hall-switch-wiced.h
 * @brief       Hall Switch GPIO WICED Hardware Interface
 * @date        January 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 */

#ifdef HALL_SWITCH_WICED_PLATFORM_ENABLED

#ifndef HALL_SWITCH_WICED_H_
#define HALL_SWITCH_WICED_H_

#include <stdint.h>
#include "hall-switch.h"
#include "wiced_platform.h"


class GPIOWiced : virtual public HallSwitch::GPIO, public HallSwitch::Interrupt
{
    private:
        #define             UNUSED_PIN    (wiced_gpio_t)(WICED_GPIO_51 + 1) /**< Unused pin */
        wiced_gpio_t        pin;                                            /**< GPIO number */
        wiced_gpio_config_t config;                                         /**< GPIO configuration */
        VLogic_t            logic;                                          /**< Pin logic */

    public:
                      GPIOWiced     (wiced_gpio_t pin,
                                     wiced_gpio_config_t   config,
                                     VLogic_t              logic);
                      GPIOWiced     ();
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

 
class HallSwitchWiced : public HallSwitch
{
    public:
        /**
         * @addtogroup hallswitchwicedhal
         * @{
         */

        /**
         * @brief WICED Hardware Platform
         */
        typedef struct
        {
            wiced_gpio_t output;     /**< Output pin */
            wiced_gpio_t power;      /**< Power pin */
        }WICEDHwPlatf_t;


        HallSwitchWiced(wiced_gpio_t    outputPin,
                        CBack_t         cBack      = NULL,
                        wiced_gpio_t    powerPin   = UNUSED_PIN);
        HallSwitchWiced(WICEDHwPlatf_t  &hwPlatf,
                        CBack_t         cBack      = NULL);
        /** @} */
};


/**
 * @addtogroup tle49643ms2go
 * @{
 */
extern HallSwitchWiced::WICEDHwPlatf_t TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F;   /**< TLE4964 3M Shield 2Go + MyIOT Adapter + CYW943907AEVAL1F Eval Kit*/
/** @} */

#endif /** HALL_SWITCH_WICED_H_ **/

#endif