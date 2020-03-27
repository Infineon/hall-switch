/** 
 * @file        hall-platf-ino.h
 * @brief       Hall Arduino Hardware Platforms
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_PLATF_INO_H_
#define HALL_PLATF_INO_H_

#include "../pal/hall-pal-ino.h"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

/**
 * @addtogroup hsinohw
 * @{
 */

/**
 * @brief Arduino Hardware Platform Pins
 */
typedef struct 
{
    uint8_t output;     /**< Output pin */
    uint8_t power;      /**< Power pin */
}PlatformIno_t;

extern PlatformIno_t TLE4964_3M_S2Go_XMC2Go;        /**< TLE4964 3M Shield 2Go + XMC2Go Stack */
extern PlatformIno_t TLE4964_3M_S2Go_ArduinoUno;    /**< TLE4964 3M Shield 2Go + MyIoT + Arduino Uno Form Factor */
extern PlatformIno_t TLE4922_2GoKit_Pins;           /**< TLE4922 Kit 2Go  */

/** @} */

#endif /** HALL_SWITCH_FRAMEWORK **/
#endif /** HALL_PLATF_INO_H_ **/