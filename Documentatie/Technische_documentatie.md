# Technische documentatie

In dit document werd alle benodigde technische documentatie van de testopstelling samengebracht om eventueel te kunnen bouwen hierop. Specifieke schema's of datasheets zijn te vinden onder de mapjes [Hardware](../Hardware/) en [Datasheets](../Datasheets/). Mogelijke uitbreidingen of verbeteringen voor het product zijn in [dit bestand](./Mogelijke_uitbreiding.md) te vinden. Ook is er een [handleiding](./Handleiding_gebruiker.md) voor het gebruik van het product als eindgebruiker. Het wordt aangeraden om al deze documenten eerst door te nemen alvorens dit document te gebruiken.

TODO: uitleggen hoe tijdelijke esp vervangen met (nieuwe) definitieve (kabels weg en plaatsen en welke pinnen veranderen)

TODO: omgevingstemp aanbrengen

## Inhoudsopgave

- [Technische documentatie](#Technische-documentatie)
  - [Extra sensoren toevoegen aan project](#Extra-sensoren-toevoegen-aan-project)
  - [Vervangen tijdelijke ESP32](#Vervangen-tijdelijke-ESP32)
  - [Toevoegen omgevingstemperatuursensor](#Toevoegen-omgevingstemperatuursensor)
  - [Overige info ESP32](#Overige-info-ESP32)

## Extra sensoren toevoegen aan project
In dit onderdeel wordt besproken hoe je nieuwe sensoren kan toevoegen aan dit project.

### Stap 1
Denk na over wat je wilt meten en welke sensor je hiervoor kan gebruiken. Deze sensor kan alleen op 5V of 3.3V werken. Indien een sensor op een hogere spanning werkt, zal dit niet compatibel zijn met ons systeem en zal een aparte manier van voeden gebruikt moeten worden voor die component. Ook is het gebruik van een step-down-converter aangeraden om de ESP32 niet te beschadigen.

### Stap 2
Maak met de datasheets een architectuurschema zodat je zeker weet hoe deze sensor aan te sluiten is op de ESP. Later kun je o.a. bij fouten hierop terugkomen, een duidelijk schema is dus van groot belang! Kijk hierbij ook van welk communicatieprotocol de sensor gebruik maakt en welke pinconfiguraties hier voor nodig zijn.

### Stap 3
Schrijf de code voor de ESP zodat deze de sensorwaardes kan weergeven (serieel om te testen en/of via home assistant) In veel gevallen is voorbeeldcode online te vinden als je het specifieke typenummer van de sensor opzoekt. Deze voorbeeldcode kan vaak een goed vertrekpunt zijn. Je kan ook altijd kijken naar de code van de reeds geïmplementeerde sensoren, hieronder de belangrijkste code van de lichtsensor ter illustratie (zie commentaar ernaast):
```
#include <BH1750.h> // voor deze sensor wordt gebruik gemaakt van deze library. Dit is te dowloaden adhv de platformIO extensie in VS code (ga naar boards en selecteer daar eerst het type bord, daarna kan onder libraries een library gezocht en toegekend aan een project worden)

HaSensor lichtWaarde; // initialisatie van naam sensorwaarde voor home assistant

BH1750 lightMeter;

void setup()
{
  lightMeter.begin(); // initialiseren van lightmeter in setup

  if (!lightMeter.begin()) { //optionele error-handling
    Serial.println("BH1750 initialisatie mislukt! Controleer de verbinding.");
  }

  //connectie met home assistant opzetten:
  connection =  HaConnection(WIFI_SSID, WIFI_PASSWORD, "IP-ADRES", 8123);
  connection.setup();
  if (!connection.connected)
    return;

  lichtWaarde = HaSensor("Light", SensorType::LIGHT,0,10000);

}

void loop() { 
  //adhv library data verkrijgen en schrijven:
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println("");

  //en versturen naar home assistant:
  lichtWaarde.setValue(lux);
  std::vector<HaSensor> sensors = {lichtWaarde}; // hier kunnen andere sensoren in worden toegevoegd
  connection.sendData("Sensoring", sensors);
  delay(5000);

```

### Stap 4
Als de sensor geleverd is test je deze best eerst even uit in een testopstelling om te kijken of alles werkt. Dit kan bvb. op een breadboard zijn en enkel serieel versturen van data. Dan kan via een applicatie als putty gekeken worden of er waardes gestuurd worden.

### Stap 5
Nu kan je de sensor solderen in de echte opstelling. Doe dit in een veilige omgeving. Als de sensor geplaatst is en werkt dan ben je in principe klaar. Nu kan via home assistant gekeken worden of de waardes correct verstuurd worden (opgelet: op home assistant moeten ook nog enkele dingen opgezet worden, kijk daarvoor in de documentatie van team GH-Networking and monitoring).

## Vervangen tijdelijke ESP32

Om de tijdelijke Devkit V1 te vervangen met de voorziene ESP32 USB-C WROOM, moeten de volgende simpele stappen voldaan worden:

### Stap 1
Eerst en vooral moet de code upgeload worden naar de nieuwe ESP.

### Stap 2
Verwijder de tijdelijke ESP en alle kabels die deze verbinden met het adapterbord. Deze zijn niet meer nodig, waardoor het doosje een stuk overzichterlijker zal worden.

### Stap 3
Hierna moeten de pinaansluitingen voor voor enkele sensoren fysiek veranderd worden. Voor de sensoren die gebruik maken van I2C moet SCL aan pin D22 en SDA aan pin D21 hangen. Aangezien I2C met adressen werkt kunnen beide sensoren aan deze datapinnen hangen. Dit moet dus op het adapterbordje veranderd worden.

### Stap 4
Wanneer de ESP32 nu op de juiste manier op het adapterbordje bevestigd zal worden (kijk hiervoor naar pinnamen op adapter en ESP en kijk of ze overeenkomen), zal alles werken met de nieuwe ESP!

## Toevoegen omgevingstemperatuursensor
Omdat wij door een defect de omgevingstemperatuursensor niet konden gebruiken, zit deze niet inbegrepen in het project op dit moment. Op volgende manier moet deze toegevoegd worden:

### Stap 1
Sluit de sensor aan, raadpleeg hiervoor het [elektrisch schema](../Hardware/Elektrisch_schema_sensoring.pdf) (kijk naar omgevingstemp./vocht rechtsboven in het schema). 

### Stap 2
Verander nu de code zodat de waardes uitgelezen kunnen worden. Hiervoor moet de code die ongeveer staat op lijn 104-105, 166-174 en 188-189 uit comment gezet worden. Upload nu de code naar de ESP en de data zou serieel verstuurd moeten worden. Om deze ook te zien in het dashboard van home assistant moet opnieuw nog het een en ander toegevoegd worden op de home assistant.

## Overige info ESP32
Indien je code wil uploaden naar de tijdelijke (Devkit v1) ESP, moet tijdens het uploaden de boot knop ingedrukt worden, anders verschijnt een error. Let ook bij het uploaden dat andere seriële programma's die de COM-poort gebruiken, zoals Putty, niet meer openstaan.