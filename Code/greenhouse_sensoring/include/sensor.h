#include <Arduino.h>
#ifndef HA_SENSOR_H
#define HA_SENSOR_H


class HaSensor {

private:
    String name;
    String type;
    String unit;
    float value;


public:
    HaSensor();
    HaSensor(String name, String type, String unit);
    void setValue(float value);
    float getValue();
    String getType();
    String getUnit();
    String getName();
    String toJson();
};


#endif