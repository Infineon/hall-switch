/** 
 * @file        hall-pal-timer.hpp
 * @brief       Hall Switch Timer Platform Abstraction Layer
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_PAL_TIMER_HPP_
#define HALL_PAL_TIMER_HPP_

#include "../config/hall-conf.hpp"
#if (HALL_SPEED_ENABLED == 1)

#include "../corelib/hall-speed.hpp"

/**
 * @addtogroup hspal
 * @{
 */

class HallSpeed::Timer
{
    public: 

        /**
         * @brief   Initializes the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         init    () = 0;

        /**
         * @brief   Deinitializes the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         deinit   () = 0;

        /**
         * @brief   Starts the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         start   () = 0;

        /**
         * @brief       Elapsed time since the timer was started 
         * @param[out]  elapsed Time in milliseconds 
         * @return      Timer error code
         * @retval      OK if success
         * @retval      INIT_ERROR if hardware interface error    
         */
        virtual  HallSwitch::Error_t         elapsed (uint32_t &elapsed) = 0;
        
        /**
         * @brief   Stops the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
         virtual  HallSwitch::Error_t         stop    () = 0;
        
        /**
         * @brief       Introduces a delay during the specified time    
         * @param[in]   timeout    Delay time in milliseconds   
         * @return      Timer error code
         * @retval      OK if success
         * @retval      INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         delay   (uint32_t timeout) = 0;
};

/** @} */

#endif /** HALL_SPEED_ENABLED **/
#endif /** HALL_PAL_TIMER_HPP_ **/