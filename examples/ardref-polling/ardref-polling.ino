/**
 * @file        ardref-polling.ino
 * @brief       GPIO Polling Example for TLE4964-3M Shield2Go + XMC2Go
 *          
 *              Usage of the Arduino Reference Library Functions.
 *              - How does it work? 
 *              In the presence of a magnetic field dots (".") will be 
 *              printed through the serial and the LED1 will be turned ON.
 * @copyright   Copyright (c) 2019 Infineon Technologies AG         
 */

#include <Arduino.h> 

#ifdef XMC1100_XMC2GO
#define LED1 14             /**< LED1 Pin Allocation for XMC2Go  */
#endif

#define Q_OUTPUT_PIN    9   /**< Hall Switch Output Pin  */

int     value = HIGH;       /**< Output Value */

void setup()
{
    delay(1000);
    
    Serial.begin(115200);
    Serial.println("Serial Initialized");
    
    pinMode(LED1, OUTPUT);
    Serial.println("LED1 Initialized");
    
    pinMode(Q_OUTPUT_PIN, INPUT_PULLUP);
    Serial.println("Output Pin Initialized");
    Serial.println();
    
}

void loop()
{
	value = digitalRead(Q_OUTPUT_PIN);   

	if(value == LOW)
    {
		Serial.print(".");
        digitalWrite(LED1, HIGH);
	}
    else if(value == HIGH)
    {
        digitalWrite(LED1, LOW);
	}
}