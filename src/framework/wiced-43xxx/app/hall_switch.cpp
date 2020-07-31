/**
 * @file        hall_switch.cpp
 * @brief       Hall Switch WICED Application Example
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 */
 
#include "../../../config/hall-conf.hpp"

#if (HALL_SWITCH_FRAMEWORK == HALL_SWITCH_FRMWK_WICED)

#include <stdlib.h>
#include "wiced.h"
#include "hall-switch-wiced.hpp"

extern "C" void application_start();

HallSwitch::Status_t stat  = HallSwitch::Status_t::UNINITED;
HallSwitch::Result_t field = HallSwitch::Result_t::B_FIELD_UNDEF;

HallSwitch::Status_t curStat  = stat;
HallSwitch::Result_t curField = field;
HallSwitch::Error_t  err = HallSwitch::OK;


#define EXAMPLE_POLLING_ENABLED    0       /**< Polling mode example */
#define EXAMPLE_INTERRUPT_ENABLED  1       /**< Interrupt mode example */

#if (EXAMPLE_POLLING_ENABLED == EXAMPLE_INTERRUPT_ENABLED)
#error "Select either polling or interrupt example."
#endif


#if (EXAMPLE_POLLING_ENABLED == 1)

HallSwitchWiced      hs(TLE4964_3M_S2Go_CYW943907AEVAL1F);

/**
 * Polling output in super loop
 */
void loop()
{
    curStat  = hs.getStatus();
    err      = hs.updateBField();
    curField = hs.getBField();

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

HallSwitchWiced hs(TLE4964_3M_S2Go_CYW943907AEVAL1F, IntCBack);

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

#endif /** HALL_SWITCH_FRAMEWORK **/

