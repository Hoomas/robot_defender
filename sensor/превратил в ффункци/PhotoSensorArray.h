#ifndef PHOTOSENSORARRAY_H
#define PHOTOSENSORARRAY_H

#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"

// === Константы ===
const uint8_t NUM_SENSORS = 8;
const float ANGLE_STEP = 45.0;

// === Глобальные переменные ===
PCF8574 expander(0x20);         // Укажи свой адрес PCF8574
uint8_t analogPin = A0;         // Укажи пин, если отличается
float sensorValues[NUM_SENSORS] = {0}; // Значения с датчиков



void selectChannel(uint8_t channel) {
    for (uint8_t i = 0; i < 4; i++) {
        expander.write(i + 1, (channel >> i) & 0x01);
    }
}
void readSensors() {
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        selectChannel(i);
        delayMicroseconds(50);
        sensorValues[i] = analogRead(analogPin);
    }
}
int getMaxSensor() {
    readSensors();

    int sensor1 = -1;
    int val1 = 0;
    int val2 = 0;

    // Первый максимум
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] > val1) {
            val1 = sensorValues[i];
            sensor1 = i;
        }
    }

    // Второй максимум
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (i != sensor1 && sensorValues[i] > val2) {
            val2 = sensorValues[i];
           
        }
    }

    // Проверка на ложный источник
    if (val2 >= val1 * 0.8) {
        sensor1=-1;
        return -1;  // два сильных источника, не доверяем
    }

    return sensor1;
}
float getDirection() {
    int maxSensor = getMaxSensor();
    if (maxSensor == -1) {
        return -1; // направление не определено
    }
    return maxSensor * ANGLE_STEP;
}
#endif //PHOTOSENSORARRAY_H