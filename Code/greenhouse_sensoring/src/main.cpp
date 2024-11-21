//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_HTU21DF.h"
#include <BH1750.h>
#include "MHZ19.h"
#include "sensor.h"
#include "connection.h"
#include "Wifi_config.h"
#include "SoftwareSerial.h"
#include "HardwareSerial.h"

//Initialisatie namen van sensorwaarden voor home assistant
HaSensor bodemTempWaarde;
HaSensor omgevingTempWaarde;
HaSensor omgevingVochtWaarde;
HaSensor lichtWaarde;
HaSensor CO2Waarde;
HaSensor bodemVochtWaarde;
HaSensor NPKWaarde;
HaConnection connection;

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
const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};  // Nitrogen (N)
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};   // Phosphorus (P)
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
 
// SoftwareSerial object to communicate with the RS485 module
SoftwareSerial mod(RX_PIN, TX_PIN);

//byte readValue(const byte* request);
byte nitrogen();
byte phosphorous();
byte potassium();

void setup()
{
  bodemTemp.begin();
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  // mySerial.begin(9600);
  // myMHZ19.begin(mySerial);
  
  mod.begin(9600);
 
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


  connection =  HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
  connection.setup();
  if (!connection.connected)
    return;

  bodemTempWaarde = HaSensor("Soil temp meting",SensorType::TEMPERATURE);
  omgevingTempWaarde = HaSensor("Ambient temp meting", SensorType::TEMPERATURE);
  omgevingVochtWaarde = HaSensor("Humidity meting",SensorType::TEMPERATURE);
  lichtWaarde = HaSensor("Light meting", SensorType::TEMPERATURE);
  //waardes voor andere sensoren hier

  delay(500); //voor npk 
}

void loop() { 
  byte val1,val2,val3;
  val1 = nitrogen();
  delay(250);
  val2 = phosphorous();
  delay(250);
  val3 = potassium();
  delay(250);

  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
 
  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
 
  Serial.print("Potassium: ");
  Serial.print(val3);
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



  std::vector<HaSensor> sensors = {bodemTempWaarde, omgevingTempWaarde, bodemVochtWaarde, lichtWaarde};
  connection.sendData("Sensoring", sensors);
  delay(5000);

}

// voor npk
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  while(mod.available()) mod.read();
  mod.write(nitro, sizeof(nitro));
  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);
  delay(10);
  if (mod.available() >= 7) {
  for(byte i=0;i<7;i++){
    values[i] = mod.read();
  }
  return values[4];
} 
}

byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    delay(10);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
  }
  return values[4];
}

byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    delay(10);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
    }
  }
  return values[4];
}
