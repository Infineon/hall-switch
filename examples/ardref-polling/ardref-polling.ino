/**
 * @file        ardref-polling.ino
 * @brief       GPIO Polling Example for TLE4964-3M Shield2Go
 *          
 *              Usage of the Arduino Reference Library Functions.
 *              - How does it work? 
 *              In the presence of a magnetic field B Field ON will be 
 *              printed through the serial and the LED1 will be turned ON.
 * @copyright   Copyright (c) 2019 Infineon Technologies AG         
 */

#include <Arduino.h> 

#define Q_OUTPUT_PIN    9   /**< Hall Switch Output Pin  */
int     value = HIGH;       /**< Output Value */

void setup()
{
    delay(1000);
    
    Serial.begin(115200);
    Serial.println("Serial Initialized");
    
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("LED1 Initialized");
    
    pinMode(Q_OUTPUT_PIN, INPUT_PULLUP);
    Serial.println("Output Pin Initialized");
    Serial.println();
}

int curValue = value;

void loop()
{
	curValue = digitalRead(Q_OUTPUT_PIN);   
    if(curValue  != value)
    {
        value = curValue;
        if(value == LOW)
        {
            Serial.println("B Field ON");
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else if(value == HIGH)
        {
            Serial.println("B Field OFF");
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}