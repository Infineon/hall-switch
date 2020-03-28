/** 
 * @file        hall-platf-wiced.hpp
 * @brief       Hall WICED Hardware Platforms 
 * @date        January 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_PLATF_WICED_HPP_
#define HALL_PLATF_WICED_HPP_

#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

#include "hall-pal-wiced.hpp"

/**
 * @addtogroup hswicedhw
 * @{
 */

/**
 * @brief WICED Hardware Platform
 */
typedef struct
{
    wiced_gpio_t output;     /**< Output pin */
    wiced_gpio_t power;      /**< Power pin */
}PlatformWICED_t;

extern PlatformWICED_t TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F;   /**< TLE4964 3M Shield 2Go + MyIOT Adapter + CYW943907AEVAL1F Eval Kit*/

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_PLATF_WICED_HPP_ **/