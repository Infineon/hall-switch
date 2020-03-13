/** 
 * @file        hall-pal-timer.h
 * @brief       Hall Switch Timer Platform Abstraction Layer
 * @date        March 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */

#ifndef HALL_PAL_TIMER_H_
#define HALL_PAL_TIMER_H_

#include "../common/hall-speed.h"

class HallSpeed::Timer
{
    public: 

        /**
         * @brief   Initialiazes the timer
         * @return  Timer error code
         * @retval  OK if success
         * @retval  INIT_ERROR if hardware interface error
         */
        virtual  HallSwitch::Error_t         init    () = 0;

        /**
         * @brief   Deinitialiazes the timer
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

#endif /** HALL_PAL_TIMER_H_ **/