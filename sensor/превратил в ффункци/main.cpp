#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"
#include "PhotoSensorArray.h"

// Настройки пинов
#define EXPANDER_ADDRESS 0x20  // Адрес расширителя PCF8574
#define ANALOG_PIN A1         // Аналоговый пин для считывания данных



void setup() {
    Serial.begin(9600);  // Инициализация серийного порта
    Wire.begin();  // Инициализация шины I2C
    expander.begin();  // Инициализация расширителя пинов
}

void loop() {
    float direction = getDirection();
    if (direction >= 0) {
        Serial.print("Direction: ");
        Serial.println(direction);
    } else {
        Serial.println("No clear IR source detected");
    }

    delay(500);
}
