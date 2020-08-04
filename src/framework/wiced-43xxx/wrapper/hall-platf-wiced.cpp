/** 
 * @file        hall-platf-wiced.cpp
 * @brief       Hall WICED Hardware Platforms 
 * @date        January 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-platf-wiced.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

/**
 *  TLE4964 3M Shield 2Go + CYW943907AEVAL1F Eval Kit
 */
PlatformWICED_t TLE4964_3M_S2Go_CYW943907AEVAL1F =
{
    .output = WICED_GPIO_9,
    .power  = UNUSED_PIN
};

#endif /** HALL_SWITCH_FRAMEWORK **/
