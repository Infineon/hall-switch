/** 
 * @file        hall-conf.hpp
 * @brief       Hall Switch Library Configuration
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *              
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_CONF_HPP_
#define HALL_CONF_HPP_

#include "hall-conf-opts.hpp"

#ifndef HALL_SPEED_ENABLED
#define HALL_SPEED_ENABLED          1            
#endif

#ifndef HALL_SWITCH_FRAMEWORK 
#define HALL_SWITCH_FRAMEWORK       HALL_SWITCH_FRMWK_ARDUINO
#endif

#include "hall-conf-dfl.hpp"

#endif /** HALL_CONF_HPP_ **/