/** 
 * @file        hall-switch-int.cpp
 * @brief       Hall Switch Interrupt Handler
 * @date        July 2019
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hall-switch-int.h"

HallSwitch*  HallSwitch::Interrupt::objPtrVector[GPIO_INT_PINS] = {NULL};
uint8_t      HallSwitch::Interrupt::idxNext    = 0;

/**
 * @brief   Interrupt 0 Handler
 */
void HallSwitch::Interrupt::int0Handler() 
{
    objPtrVector[0]->callback();
}

/**
 * @brief   Interrupt 1 Handler
 */
void HallSwitch::Interrupt::int1Handler()
{
    objPtrVector[1]->callback();
}

/**
 * @brief   Interrupt 2 Handler
 */
void HallSwitch::Interrupt::int2Handler()
{
    objPtrVector[2]->callback();
}

/**
 * @brief   Interrupt 3 Handler
 */
void HallSwitch::Interrupt::int3Handler()
{
    objPtrVector[3]->callback();
}


void *HallSwitch::Interrupt::fnPtrVector[GPIO_INT_PINS] = {(void *)int0Handler,
                                                           (void *)int1Handler,
                                                           (void *)int2Handler,
                                                           (void *)int3Handler};

/**
 * @brief       Register a hardware interrupt on the argument hall switch object
 * @param[in]   *objPtr Hall switch object pointer
 * @return      Pointer to allocated the interrupt function handler 
 */
void *HallSwitch::Interrupt::isrRegister(HallSwitch *objPtr) 
{
    objPtrVector[HallSwitch::Interrupt::idxNext] = objPtr;
    return fnPtrVector[HallSwitch::Interrupt::idxNext++];
}

