/*
 * Copyright 2019, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, associated documentation and materials ("Software"),
 * is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

#include <stdlib.h>
#include "wiced.h"
#include "hall-switch-wiced.hpp"

extern "C" void application_start();

HallSwitch::Status_t stat  = HallSwitch::Status_t::UNINITED;
HallSwitch::Result_t field = HallSwitch::Result_t::B_FIELD_UNDEF;

HallSwitch::Status_t curStat  = stat;
HallSwitch::Result_t curField = field;


#define EXAMPLE_POLLING_ENABLED    0       /**< Polling mode example */
#define EXAMPLE_INTERRUPT_ENABLED  1       /**< Interrupt mode example */

#if ((EXAMPLE_POLLING_ENABLED ^ EXAMPLE_INTERRUPT_ENBLED) == 1)
#error "Select either polling or interrupt example."
#endif


#if (EXAMPLE_POLLING_ENABLED == 1)

HallSwitchWiced      hs(TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F);

/**
 * Polling output in super loop
 */
void loop()
{
    curStat  = hs.getStatus();
    curField = hs.updateBField();

    if (curStat != stat || curField != field)
    {
      stat  = curStat;
      field = curField;

      if(field == HallSwitch::Result_t::B_FIELD_ON)
      {
          WPRINT_APP_INFO(( "[hall-switch] : bField -> ON\n" ));
      }
      else if(field == HallSwitch::Result_t::B_FIELD_OFF)
      {
          WPRINT_APP_INFO(( "[hall-switch] : bField -> OFF\n" ));
      }
      WPRINT_APP_INFO(( "[hall-switch] : status -> %u \n", stat ));
    }
}
#elif (EXAMPLE_INTERRUPT_ENABLED == 1)

/**
 * Output interrupt callback
 */
void IntCBack(HallSwitch::Result_t result)
{
    if(result == HallSwitch::Result_t::B_FIELD_ON)
    {
        WPRINT_APP_INFO(( "[hall-switch] : bField -> ON\n" ));
    }
    else if(result == HallSwitch::Result_t::B_FIELD_OFF)
    {
        WPRINT_APP_INFO(( "[hall-switch] : bField -> OFF\n" ));
    }
}

HallSwitchWiced hs(TLE4964_3M_S2Go_MyIoT_CYW943907AEVAL1F, IntCBack);

void loop()
{
    //Nothing happens in the super loop
}

#endif

void setup()
{
    HallSwitch::Error_t err;

    err = hs.init();
    WPRINT_APP_INFO(("[hall-switch] : begin -> %u\n", err));
    err = hs.enable();
    WPRINT_APP_INFO(("[hall-switch] : end   -> %u\n", err));

    WPRINT_APP_INFO(( "[hall-switch] : status -> %u \n", hs.getStatus()));
}

/******************************************************
 *               Function Definitions
 ******************************************************/

void application_start( )
{
    wiced_result_t      result;

    /* Initialize the device */
    result = wiced_init();
    if (result != WICED_SUCCESS)
    {
        return;
    }

    setup();

    while(1)
    {
        loop();
    }
}

