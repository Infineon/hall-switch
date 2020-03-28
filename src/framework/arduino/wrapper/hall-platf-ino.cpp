/** 
 * @file        hall-platf-ino.cpp
 * @brief       Hall Arduino Hardware Platforms
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-platf-ino.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_ARDUINO)

/**
 * @addtogroup hsinohw
 */

PlatformIno_t TLE4964_3M_S2Go_XMC2Go     =  {9, UNUSED_PIN};    /**< TLE4964 3M Shield 2Go + XMC2Go Stack */
PlatformIno_t TLE4964_3M_S2Go_ArduinoUno =  {3, UNUSED_PIN};    /**< TLE4964 3M Shield 2Go + MyIoT + Arduino Uno Form Factor */
PlatformIno_t TLE4922_2GoKit             =  {1, UNUSED_PIN};    /**< TLE4922 Kit 2Go  */

#endif /** HALL_SWITCH_FRAMEWORK **/
/** @} */