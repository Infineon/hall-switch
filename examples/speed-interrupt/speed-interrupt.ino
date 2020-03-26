#include <Arduino.h>
#include <stdint.h>
#include <hall-speed-ino.h>

/**
 * Plug & Play hw platform --> XMC2Go with TLE4964-3M 2GoShield
 */

/**
 * @brief       Prints the sensor data in JSON format 
 * @param[in]   speed Speed value
 */
void JSONPrint(double speed)
{
  Serial.print("{ \"speed\" : ");
  Serial.print(speed);
  Serial.println(" }");
}

HallSpeedIno hs(TLE4964_3M_S2Go_XMC2Go, 1, HallSpeed::HERTZ, JSONPrint);

void setup()
{      
  int err = 0;

  delay(1000);

  Serial.begin(115200);
  Serial.println("Serial initialized");

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED1 Initialized");

  err = hs.begin();
  if(0 > err ){ Serial.print("Hall Speed error");}

  Serial.println("Hall Speed started");
}

void loop()
{

}