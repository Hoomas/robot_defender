#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"
#include "PhotoSensorArray.h"

// Настройки пинов
#define EXPANDER_ADDRESS 0x20  // Адрес расширителя PCF8574
#define ANALOG_PIN A1         // Аналоговый пин для считывания данных

PCF8574 expander(EXPANDER_ADDRESS);  // Создаем объект для расширителя пинов
PhotoSensorArray sensorArray(expander, ANALOG_PIN);  // Создаем объект для работы с датчиками

void setup() {
    Serial.begin(9600);  // Инициализация серийного порта
    Wire.begin();  // Инициализация шины I2C
    expander.begin();  // Инициализация расширителя пинов
}

void loop() {
    // Получаем направление, вычисленное с датчиков
    float direction = sensorArray.getDirection();

    // Выводим результат в монитор порта
    Serial.print("Direction: ");
    Serial.println(direction);

    delay(500);  // Задержка 500 мс
}
