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
#include "HardwareSerial.h"

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
// #define RX_PIN 16                                       
// #define TX_PIN 17
// MHZ19 myMHZ19;  
// SoftwareSerial mySerial(RX_PIN, TX_PIN);

//npk sensor
#define RX_PIN 4 // Set RX to GPIO4
#define TX_PIN 5 // Set TX to GPIO5

#define RE 2
#define DE 15

// Modbus RTU requests for reading NPK values
const byte nitro[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};  // Nitrogen (N)
const byte phos[] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};   // Phosphorus (P)
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};

byte values[11];
 
// SoftwareSerial object to communicate with the RS485 module
SoftwareSerial modbus(RX_PIN, TX_PIN);

byte readValue(const byte* request);

void setup()
{
  bodemTemp.begin();
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  // mySerial.begin(9600);
  // myMHZ19.begin(mySerial);
  
  modbus.begin(9600);
 
  // Set RS485 pins as outputs
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
 
  // Turn off RS485 receiver and transmitter initially
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);

  //npkSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

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

  delay(500); //voor npk 
}

void loop() { 
  Serial.print("Nitrogen: ");
  Serial.print(readValue(nitro));
  Serial.println(" mg/kg");
 
  Serial.print("Phosphorous: ");
  Serial.print(readValue(phos));
  Serial.println(" mg/kg");
 
  Serial.print("Potassium: ");
  Serial.print(readValue(pota));
  Serial.println(" mg/kg");

  // De andere sensoren
  bodemTemp.requestTemperatures();  
  Celsius = bodemTemp.getTempCByIndex(0);
  Serial.print("Bodemtemperatuur: ");
  Serial.print(Celsius);
  Serial.print(" C    ");
  Serial.println("");

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

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println("");

  delay(5000);
}

// voor npk: sends a Modbus RTU request and reads the response to get a value
byte readValue(const byte* request) {
  // RS485 module to transmit mode
  digitalWrite(RE, HIGH);
  digitalWrite(DE, HIGH);
 
  modbus.write(request, sizeof(request));
 
  // RS485 module to receive mode
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
 
  delay(1000);

  byte responseLength = modbus.available();
  for (byte i = 0; i < responseLength; i++) {
    values[i] = modbus.read();
  }

}
