#include <Arduino.h>
#include <stdint.h>
#include <hall-speed-ino.h>


#ifdef XMC1100_XMC2GO
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#else
#define LED1 LED_BUILTIN
#endif

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

  pinMode(LED1, OUTPUT);
  Serial.println("LED1 Initialized");

  err = hs.begin();
  if(0 > err ){ Serial.print("Hall Speed error");}

  Serial.println("Hall Speed started");
}

void loop()
{

}