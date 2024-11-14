//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_HTU21DF.h"
#include <BH1750.h>
#include "MHZ19.h"
//#include "sensor.h"
//#include "connection.h"
//#include "Wifi_config.h"
#include "SoftwareSerial.h"

//Initialisatie namen van sensorwaarden voor home assistant
// HaSensor bodemTempWaarde;
// HaSensor omgevingTempWaarde;
// HaSensor omgevingVochtWaarde;
// HaSensor lichtWaarde;
// HaSensor CO2Waarde;
// HaSensor bodemVochtWaarde;
// HaSensor NPKWaarde;
// HaConnection connection;

// Datapin bodemtemperatuursensor
#define GPIO_BODEMTEMP 14
OneWire oneWire(GPIO_BODEMTEMP);
DallasTemperature bodemTemp(&oneWire);
float Celsius = 0;

//omgevingtemperatuursensor
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

//lichtsensor
BH1750 lightMeter;

//CO2sensor
#define RX_PIN 16                                       
#define TX_PIN 17
MHZ19 myMHZ19;  
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup()
{
  bodemTemp.begin();
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  mySerial.begin(9600);
  myMHZ19.begin(mySerial);
  
  myMHZ19.autoCalibration(); 

  if (!htu.begin()) {
    Serial.println("HTU21DF initialisatie mislukt! Controleer de verbinding.");
}

if (!lightMeter.begin()) {
    Serial.println("BH1750 initialisatie mislukt! Controleer de verbinding.");
}


  // connection =  HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
  // connection.setup();
  // if (!connection.connected)
  //   return;

  // bodemTempWaarde = HaSensor("Soil temp meting", "soil_temperature", "°C");
  // omgevingTempWaarde = HaSensor("Ambient temp meting", "ambient_temperature", "°C");
  // omgevingVochtWaarde = HaSensor("Humidity meting","humidity", "%");
  // lichtWaarde = HaSensor("Light meting", "light", "lx");
  //waardes voor andere sensoren hier
}

void loop()
{ 
  int CO2 = myMHZ19.getCO2();

  // HaSensor sensors[] = { bodemTempWaarde, omgevingTempWaarde, omgevingVochtWaarde, lichtWaarde }; //andere sensoren hier toevoegen voor home assistant connectie
  // int sensorCount = sizeof(sensors) / sizeof(sensors[0]);

  // // Genereer en verzend het volledige JSON-bericht
  // String fullJson = connection.generateAllSensorsJson(sensors, sensorCount);
  //connection.sendData(fullJson);
  //Serial.println(fullJson);

  // Send the command to get temperatures
  bodemTemp.requestTemperatures();  
  Celsius = bodemTemp.getTempCByIndex(0);
  Serial.print("Bodemtemperatuur: ");
  Serial.print(Celsius);
  Serial.print(" C    ");
  Serial.println("");

  //omgevingstemp & omgevingsvocht
  float temp = htu.readTemperature();
  float rel_hum = htu.readHumidity();

  Serial.print("Omgevingstemperatuur: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.println("");

  Serial.print("Omgevingsvochtigheid: ");
  Serial.print(rel_hum);
  Serial.println(" %");
  Serial.println("");

  //lichtsensor
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println("");
  Serial.println("");
  Serial.println("");

  //CO2sensor
  Serial.print("CO2 Concentration: ");
  Serial.print(CO2);
  Serial.println(" ppm");

  //waardes andere sensoren verzenden hier

  delay(5000);
}