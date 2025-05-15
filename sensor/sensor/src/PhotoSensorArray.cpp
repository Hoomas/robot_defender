#include "PhotoSensorArray.h"

// Конструктор класса
PhotoSensorArray::PhotoSensorArray(PCF8574 &expander, uint8_t analogPin)
    : _expander(expander), _analogPin(analogPin)
{
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        _values[i] = 0; // Инициализация значений датчиков
    }
}

// Метод для выбора канала мультиплексора
void PhotoSensorArray::selectChannel(uint8_t channel)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        _expander.write(i + 1, (channel >> i) & 0x01);
    }
}

// Метод для считывания данных с датчиков
void PhotoSensorArray::readSensors()
{
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        selectChannel(i);
        delayMicroseconds(10);               // Задержка для стабилизации сигнала
        _values[i] = analogRead(_analogPin); // Считывание значения с аналогового пина
    }
}

// Метод для получения двух датчиков с максимальным значением
void PhotoSensorArray::getMaxSensors(int &sensor1, int &sensor2,float &Vals1,float &Vals2)
{
    sensor1 = -1;
    sensor2 = -1;
    Vals1=0;
    Vals2=0;
    
         // Находим первый максимум
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (_values[i] > Vals1) {
            Vals1 = _values[i];
            sensor1 = i;
        }
    }

    //  Находим второй максимум (не тот же самый датчик)
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (i != sensor1 && _values[i] > Vals2) {
            Vals2 = _values[i];
            sensor2 = i;
        }
    }

    // Если второй датчик недостаточно яркий или не соседний, игнорируем его
    if (Vals2 < 0.9 * Vals1 || (abs(sensor2-sensor1)!=1 && abs(sensor2-sensor1)!=NUM_SENSORS-1))
     {  
        sensor2 = -1;
        Vals2 = 0;
    }

}
  

// Метод для вычисления направления относительно первого датчика
float PhotoSensorArray::getDirection()
{
    readSensors(); // Чтение данных с датчиков
    int s1, s2;
    float Vs1,Vs2,Angle;
    getMaxSensors(s1, s2,Vs1, Vs2); // Получаем два датчика с максимальным значением

    if (s2 == -1)
    {
        // Если только один датчик с максимальным значением
        Angle=  s1 * ANGLE_STEP;
    }
    else
    {
        if (Vs1 == Vs2) // Если два датчика имеют одинаковое максимальное значение
        {
            if(abs(s2-s1)==1){
           
            Angle=  ((s1 + s2) / 2.0) * ANGLE_STEP;
        }
        if(abs(s2-s1)==NUM_SENSORS-1)
        {
             Angle = (s1 - (1 - NUM_SENSORS-1)) * ANGLE_STEP;
            if (Angle < 0) Angle += 360.0;
        }
    }
        else if (Vs1 > Vs2)
        {
           Angle= (s1*ANGLE_STEP+(Vs1/(Vs1 + Vs2)) * ANGLE_STEP); //Угол = Угол_датчика + (Сигнал_соседа / (Сигнал_датчика + Сигнал_соседа)) * 45°
        }
    }
    return Angle;
}
