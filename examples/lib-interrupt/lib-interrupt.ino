#include <Arduino.h>
#include <stdint.h>
#include <hall-switch-ino.h>


#ifdef XMC1100_XMC2GO
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#else
#define LED1 LED_BUILTIN
#endif

HallSwitch::Status_t stat  = HallSwitch::Status_t::UNINITED;
HallSwitch::Result_t field = HallSwitch::Result_t::B_FIELD_UNDEF;

/**
 * @brief       Prints the sensor data in JSON format 
 * @param[in]   stat  status
 * @param[in]   field B field value
 */
void JSONPrint(HallSwitch::Status_t stat,
               HallSwitch::Result_t field)
{
  Serial.print("{ \"status\" : ");
  Serial.print(stat);
  Serial.print(", \"field_val\" : ");
  Serial.print(field);
  Serial.println(" }");
}

void IntCBack(HallSwitch::Result_t result)
{
	if(result == HallSwitch::Result_t::B_FIELD_ON)
    {
        digitalWrite(LED1, HIGH);
	}
    else if(result == HallSwitch::Result_t::B_FIELD_OFF)
    {
        digitalWrite(LED1, LOW);
	}

    JSONPrint(stat, result);
}

HallSwitchIno hs(TLE4964_3M_S2Go_XMC2Go, IntCBack);

void setup()
{      
    HallSwitch::Error_t errCode = HallSwitch::Error_t::OK;

    delay(1000);

    Serial.begin(115200);
    Serial.println("Serial initialized");

    pinMode(LED1, OUTPUT);
    Serial.println("LED1 Initialized");

    /* Begin switch hardware interfaces */ 
    errCode = hs.begin();
    if(errCode != HallSwitch::Error_t::OK)
    {
        Serial.print("Hall Switch error: ");
        Serial.println(errCode);
    }
    Serial.println("Hall Switch initialized");

    /* Enable the switch */
    errCode = hs.enable();
    if(errCode != HallSwitch::Error_t::OK)
    {
        Serial.print("Hall Switch error: ");
        Serial.println(errCode);
    }
    Serial.println("Hall Switch enabled");
        
    stat = hs.getStatus();
    JSONPrint(stat, field);
}


void loop()
{

}