#ifndef SENSOR_H
#define SENSOR_H

#include "includes.h"

class Sensor {
  public:
    virtual ~Sensor() {};
    virtual String getSensorData() = 0;
    virtual String getJsonData() = 0;
};

#endif