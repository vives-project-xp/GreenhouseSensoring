#include "sensor.h"

HaSensor::HaSensor(): name("undefined"), type("undefined"), unit("undefined"), value(0){};
HaSensor::HaSensor(String name, String type, String unit) : name(name), type(type), unit(unit), value(0) {
    // Serial.println("Sensor initialized");
    // Serial.println("-----------------------");
    // Serial.print("Type: ");
    // Serial.print(type);
    // Serial.print("\nUnit: ");
    // Serial.print(unit);
    // Serial.print("\n");
    // Serial.println("-----------------------");
}

String HaSensor::toJson() {
    String json = "{";
    json += "\"name\":\"" + this->name + "\",";
    json += "\"type\":\"" + this->type + "\",";
    json += "\"value\":" + String(this->value) + ",";
    json += "\"unit\":\"" + this->unit + "\"";
    json += "}";
    return json;
}

void HaSensor::setValue(float value) {
    this->value = value;
}

float HaSensor::getValue() {
    return this->value;
}

String HaSensor::getType() {
    return this->type;
}

String HaSensor::getUnit() {
    return this->unit;
}

String HaSensor::getName() {
    return this->name;
}