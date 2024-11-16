# Temperatuur en vochtigheidssensor omgeving:
Voorbeeldproject:  https://lastminuteengineers.com/htu21d-temperature-humidity-sensor-arduino-tutorial/ 

1) In PlatformIO de HTU21D library installeren.
2) Volgende code toevoegen aan main.cpp:
```
#include <Wire.h>
#include "Adafruit_HTU21DF.h"

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  Serial.begin(9600);

  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}

void loop() {
    float temp = htu.readTemperature();
    float rel_hum = htu.readHumidity();
    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
    Serial.print("\t\t");
    Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" \%");
    delay(500);
}
``` 
# Lichtsensor:
Voorbeeldproject: https://randomnerdtutorials.com/arduino-bh1750-ambient-light-sensor/ 

1) BH1750 (by claws) library installeren 
2) Volgende code toevoegen aan main.cpp:
```
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup(){
  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
```

# CO2 sensor:
Voorbeeldproject: https://registry.platformio.org/libraries/wifwaf/MH-Z19/examples/RawCO2/RawCO2.ino 

(of https://wolles-elektronikkiste.de/en/mh-z14-and-mh-z19-co2-sensors)

1) MH-Z19 by Jonathan Dempsey library installeren
2) Volgende code toevoegen aan main.cpp:
```
#include "MHZ19.h"
#include <Arduino.h>
#include <SoftwareSerial.h>                                //  Remove if using HardwareSerial or non-uno compatabile device

#define RX_PIN 10                                          
#define TX_PIN 11                                         
#define BAUDRATE 9600                                      // Native to the sensor (do not change)

MHZ19 myMHZ19;                                             
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // Uno example

unsigned long getDataTimer = 0;

void setup()
{
  Serial.begin(9600);

  mySerial.begin(BAUDRATE);                               // Uno example: Begin Stream with MHZ19 baudrate  
  myMHZ19.begin(mySerial);                                 // *Important, Pass your Stream reference
}

void loop()
{
  if (millis() - getDataTimer >= 2000)
  {

    double adjustedCO2 = myMHZ19.getCO2Raw();

    Serial.println("----------------");
    Serial.print("Raw CO2: ");
    Serial.println(adjustedCO2);

    adjustedCO2 = 6.60435861e+15 * exp(-8.78661228e-04 * adjustedCO2);      
    // Exponential equation for Raw & CO2 relationship

    Serial.print("Adjusted CO2: ");
    Serial.print(adjustedCO2);
    Serial.println(" ppm");

    getDataTimer = millis();

  }
}
```

# Bodemvochtsensor:
Voorbeeldproject: https://www.datocms-assets.com/28969/1662716326-hw-101-hw-moisture-sensor-v1-0.pdf 

# NPK sensor:
Voorbeeldproject: https://community.dfrobot.com/makelog-313566.html?tracking=660bd90501412 