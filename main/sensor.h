#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <Arduino.h>
#include <ArduinoJson.h>

class Sensor {
  public:
    virtual ~Sensor() {};
    virtual String getSensorData() = 0;
    virtual String getJsonData() = 0;
};

#endif