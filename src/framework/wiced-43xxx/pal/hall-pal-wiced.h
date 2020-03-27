/** 
 * @file        hall-pal-wiced.h
 * @brief       Hall Switch WICED PAL  
 * @date        January 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "../../../config/hall-conf.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

/**
 * @addtogroup hswicedpal
 * @{
 */

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

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/