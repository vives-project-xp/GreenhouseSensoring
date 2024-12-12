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
#include <HardwareSerial.h>

//Initialisatie namen van sensorwaarden voor home assistant
HaSensor bodemTempWaarde;
HaSensor omgevingTempWaarde;
HaSensor omgevingVochtWaarde;
HaSensor lichtWaarde;
HaSensor CO2Waarde;
HaSensor bodemVochtWaarde;
HaSensor NPKWaardeNitro;
HaSensor NPKWaardePhos;
HaSensor NPKWaardePota;
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
#define RX_CO2 16                                       
#define TX_CO2 17
MHZ19 myMHZ19;  
SoftwareSerial mySerial(RX_CO2, TX_CO2);

//npk sensor
#define RX_PIN 4 // Set RX to GPIO4 (voor esp met usbc pin 4)02
#define TX_PIN 5 // Set TX to GPIO5 (voor esp met usbc pin 5)03

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

//bodemvocht
int v_droog = 2900;
int v_nat = 1000;

void setup()
{
  // Turn off RS485 receiver and transmitter initially
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
  delay(1000);

  bodemTemp.begin();
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  mySerial.begin(9600);
  myMHZ19.begin(mySerial);
  
  mod.begin(9600);
 
  // Set RS485 pins as outputs
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  //npkSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  if (!htu.begin()) {
    Serial.println("HTU21DF initialisatie mislukt! Controleer de verbinding.");
}

if (!lightMeter.begin()) {
    Serial.println("BH1750 initialisatie mislukt! Controleer de verbinding.");
}


//   connection =  HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
//   connection.setup();
//   if (!connection.connected)
//     return;

  bodemTempWaarde = HaSensor("Soil_temp",SensorType::TEMPERATURE);
  omgevingTempWaarde = HaSensor("Ambient_temp", SensorType::TEMPERATURE);
  omgevingVochtWaarde = HaSensor("ambient_Humidity",SensorType::TEMPERATURE);
  bodemVochtWaarde = HaSensor("soil_humidity",SensorType::TEMPERATURE);
  NPKWaardeNitro = HaSensor("npkNitro", SensorType::TEMPERATURE);
  NPKWaardePhos = HaSensor("npkPhos", SensorType::TEMPERATURE);
  NPKWaardePota = HaSensor("npkPota", SensorType::TEMPERATURE);
  CO2Waarde = HaSensor("CO2",SensorType::TEMPERATURE);
  lichtWaarde = HaSensor("Light", SensorType::TEMPERATURE);

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

  int CO2 = myMHZ19.getCO2();

  //voor bodemvocht:
  int soilMoistureValue = analogRead(35);  //put Sensor insert into soil
  float vochtigheid = (float(soilMoistureValue) - v_droog) / (v_nat - v_droog) * 100;

  // Zorg dat waarde binnen 0-100% blijft
  if (vochtigheid < 0) vochtigheid = 0;
  if (vochtigheid > 100) vochtigheid = 100;

  // Toon vochtigheid
  Serial.print("Bodemvochtigheid: ");
  Serial.print(vochtigheid);
  Serial.println("%");
  Serial.println("");

  //npk
  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
 
  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
 
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  Serial.println("");

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

  //CO2sensor
  Serial.print("CO2 Concentration: ");
  Serial.print(CO2);
  Serial.println(" ppm");

  //voor sturen van lux waardes naar esp van light&heat
  HTTPClient http; // Maak een HTTP client-object
  http.begin("http://esp2.local/data"); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  int httpResponseCode = http.POST("value=" + String(lux)); 
  if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
  } else {
      Serial.print("Fout bij HTTP POST: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
  }
  http.end();


  bodemTempWaarde.setValue(Celsius);
  omgevingTempWaarde.setValue(temp);
  omgevingVochtWaarde.setValue(rel_hum);
  lichtWaarde.setValue(lux);
  NPKWaardeNitro.setValue(val1);
  NPKWaardePhos.setValue(val2);
  NPKWaardePota.setValue(val3);
  bodemVochtWaarde.setValue(soilMoistureValue);
  CO2Waarde.setValue(CO2);
  std::vector<HaSensor> sensors = {bodemTempWaarde, omgevingTempWaarde, omgevingVochtWaarde, lichtWaarde, NPKWaardeNitro, NPKWaardePhos, NPKWaardePota, bodemVochtWaarde, CO2Waarde};
  connection.sendData("Sensoring", sensors);
  delay(5000);

}

// voor npk
byte readSensor(const byte* request, byte* response, int responseLength) {
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10); // Tijd om te schakelen naar zenden
    mod.write(request, 8); // Stuur Modbus request
    mod.flush(); // Wacht tot het verzenden klaar is
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    delay(20); // Wacht tot de sensor reageert

    int bytesRead = 0;
    while (mod.available()) {
        response[bytesRead++] = mod.read();
        if (bytesRead >= responseLength) break;
    }

    if (bytesRead < responseLength) {
        Serial.println("Onvolledige respons ontvangen!");
        return 0xFF; // Geef een foutwaarde terug
    }

    // Controleer CRC hier indien nodig (niet geïmplementeerd in dit voorbeeld)
    return response[4]; // Return de waarde (bv. N, P of K)
}

byte nitrogen() {
    byte response[7];
    return readSensor(nitro, response, 7);
}

byte phosphorous() {
    byte response[7];
    return readSensor(phos, response, 7);
}

byte potassium() {
    byte response[7];
    return readSensor(pota, response, 7);
}

