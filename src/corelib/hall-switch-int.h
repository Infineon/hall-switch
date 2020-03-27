/** 
 * @file        hall-switch-int.h
 * @brief       Hall Switch Interrupt Handler
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HALL_SWITCH_INT_H_
#define HALL_SWITCH_INT_H_

#include "hall-switch.h"

class HallSwitch::Interrupt
{
    private:
        #define             GPIO_INT_PINS       4           /**< Maximum hardware interrupt signals */
        static uint8_t      idxNext;                        /**< Interrupt array allocation index*/
        static HallSwitch   *objPtrVector[GPIO_INT_PINS];   /**< Hall switch object pointers vector */
        static void         *fnPtrVector[GPIO_INT_PINS];    /**< Hall switch interrupt function handlers vector */
        static void         int0Handler ();
        static void         int1Handler ();
        static void         int2Handler ();
        static void         int3Handler ();
    public:
        static void         *isrRegister(HallSwitch *objPtr);
};

#endif /** HALL_SWITCH_INT_H_ **/