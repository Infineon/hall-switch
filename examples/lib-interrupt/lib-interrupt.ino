#include <Arduino.h>
#include <stdint.h>
#include <hall-switch-ino.hpp>

/**
 * Plug & Play hw platform --> XMC2Go with TLE4964-3M 2GoShield
 */

/**
 * @brief       Prints the sensor data in JSON format 
 * @param[in]   field B field value
 */
void JSONPrint(int field)
{
  Serial.print("{ \"field_val\" : ");
  Serial.print(field);
  Serial.println(" }");
}

void IntCBack(HallSwitch::Result_t result)
{
	if(result == HallSwitch::Result_t::B_FIELD_ON)
    {
        digitalWrite(LED_BUILTIN, HIGH);
	}
    else if(result == HallSwitch::Result_t::B_FIELD_OFF)
    {
        digitalWrite(LED_BUILTIN, LOW);
	}

    JSONPrint(result);
}

HallSwitchIno hs(TLE4964_3M_S2Go_XMC2Go, IntCBack);  /**< Hall Switch object */

void setup()
{      
    int err = 0;

    delay(1000);

    Serial.begin(115200);
    Serial.println("Serial initialized");

    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("LED1 initialized");

    err = hs.begin();
    if(0 > err ){ Serial.print("Hall Switch error");}

    Serial.println("Hall Switch started");
}

void loop()
{

}