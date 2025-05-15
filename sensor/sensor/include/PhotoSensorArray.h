#ifndef PHOTOSENSORARRAY_H
#define PHOTOSENSORARRAY_H

#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"

class PhotoSensorArray {
public:
    static const uint8_t NUM_SENSORS = 8;          // Количество датчиков
    static constexpr float ANGLE_STEP = 45.0;      // Шаг угла для каждого датчика (45 градусов)

    
    // Конструктор класса
    PhotoSensorArray(PCF8574& expander, uint8_t analogPin);
 
    // Метод для получения двух датчиков с одинаковым максимальным значением фототока
    void getMaxSensors(int &sensor1, int &sensor2,float &Vals1,float &Vals2);
    
    // Метод для вычисления направления относительно первого датчика
    float getDirection(); 

private:
    PCF8574& _expander;           // Ссылка на расширитель пинов PCF8574
    uint8_t _analogPin;           // Пин для аналогового считывания
    float _values[NUM_SENSORS];   // Массив значений для датчиков

    // Метод для выбора канала мультиплексора
    void selectChannel(uint8_t channel);
    

    // Метод для считывания данных с датчиков
    void readSensors();
};

#endif // PHOTOSENSORARRAY_H
