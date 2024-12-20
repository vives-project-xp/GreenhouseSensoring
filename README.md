# GreenhouseSensoring

## Inhoudsopgave

- [GreenhouseSensoring](#greenhousesensoring)
  - [Inhoudsopgave](#inhoudsopgave)
  - [Doel](#doel)
  - [Gebruik](#gebruik)
  - [Team](#team)
  - [Sensoren](#sensoren)
- [Meer informatie nodig?](#meer-informatie-nodig)
  - [Alle sensoren uitgelegd:](#alle-sensoren-uitgelegd)
  - [Handleiding voor gebruikers:](#handleiding-voor-gebruikers)
  - [Technische documentatie:](#technische-documentatie)
  - [Tips voor mogelijke uitbreidingen en verbeteringen](#tips-voor-mogelijke-uitbreidingen-en-verbeteringen)
- [Bill of Materials (BOM)](#bill-of-materials-bom)

## Doel
Dit project heeft als einddoel het maken van testopstelling voor het meten van verschillende eigenschappen in de serre m.b.v. sensoren en deze waarden uit te lezen met Home Assistant. Aan de hand van 6 sensoren, die in totaal 9 verschillende parameters doorsturen, worden metingen opgenomen via een ESP32 microcontroller. Deze ESP32 stuurt dan via het lokale netwerk de gemeten waardes door naar de lokale Home Assistant server, waar ze op een visuele manier mooi voorgesteld kunnen worden. Op die manier kan informatie opgedaan worden om de planten zo goed mogelijk te verzorgen. Want meten is weten! 

Daarnaast werd ook [technische documentatie](./Documentatie/Technische_documentatie.md) en een [lijst van mogelijke uitbreidingen/verbeteringen](./Documentatie/Mogelijke_uitbreiding.md) opgesteld zodat hierop verder gebouwd kan worden. Ook is er een [handleiding](./Documentatie/Handleiding_gebruiker.md) ter beschikking voor mensen die het product willen gebruiken.

## Gebruik
Het gebruiken van het product is vrij simpel. Wanneer deze in het stopcontact gestopt is, zou de ESP na enkele seconden automatisch verbinding moeten maken. Als deze verbinding kan maken met het Devbit netwerk, zullen de waarden doorgestuurd worden naar home assistant. Indien geen verbinding gemaakt kan worden, zal ook niets verstuurd kunnen worden (ook eventuele seriële data zal niet verstuurd worden). Voor enkele sensoren kan het enkele seconden tot een minuutje duren voor ze hun waardes doorsturen.


## Team
De groep bestaat uit:  
- [Didier Vereecke](https://github.com/MrI2C) • Projectleader
- [Xander Vyvey](https://github.com/vyx04) • Scrum-master
- [Ruben Belligh](https://github.com/RubenBelligh)    
- [Kenrie Vandekerckhove](https://github.com/Kenrie19)  

## Sensoren
Dit zijn de sensoren die we gaan gebruiken:
- **Temperatuur/Vochtigheid Sensor**: Meet zowel de temperatuur als de luchtvochtigheid binnen de serre.
- **Lichtintensiteitssensor**: Meet de hoeveelheid licht die de planten ontvangen.
- **Bodemvochtsensor**: Meet het vochtgehalte van de grond.
- **Bodemtemperatuursensor**: Meet de temperatuur van de grond.
- **CO2-sensor**: Meet het CO2-gehalte in de lucht binnen de serre.
- **NPK Sensor**: Meet de concentraties van stikstof (N), fosfor (P), en kalium (K) in de bodem.

# Meer informatie nodig?
## Alle sensoren uitgelegd:
  - [Algemene informatie sensoren](./Documentatie/Algemene%20info%20componenten/README.md)

## Handleiding voor gebruikers:
  - [Handleiding](./Documentatie/handleiding.md)

## Technische documentatie:
- [Technische documentatie](./Documentatie/Technische_documentatie.md)

## Tips voor mogelijke uitbreidingen en verbeteringen:
  - [Uitbreidingen](./Documentatie/Mogelijke_uitbreiding.md)

# Bill of Materials (BOM)


| **Aantal** | **Korte Omschrijving**                       | **Totale Kostprijs (excl. BTW)** |
|------------|----------------------------------------------|----------------------------------|
| 1          | ESP                                          | € 9,50                           |
| 1          | Adapter voor ESP                             | € 3,22                           |
| 1          | Temperatuurs/vochtigheid sensor              | € 3,30                           |
| 1          | Lichtintensiteitssensor                      | € 2,23                           |
| 1          | CO2 Sensor                                   | € 35,95                          |
| 1          | Bodemvochtsensor                             | € 2,48                           |
| 1          | Voedingstofsensor                            | € 45,35                          |
| 3          | Bodemtemperatuur sensor                      | € 14,83                          |
| 1          | TTL to RS485 converter                       | € 1,57                           |
| 3          | Level shifter                                | € 1,61                           |
| 6          | USB-connector met schroefaansluiting         | € 4,95                           |
| 1          | Verlengkabel USB                             | € 5,78                           |
| 1          | Stekkerkop                                   | € 5,36                           |
| 10         | Draden van 0,5mm² (oranje)                   | € 1,60                           |
| 10         | Draden van 0,5mm² (zwart)                    | € 4,00                           |
| 10         | Draden van 0,5mm² (rood)                     | € 1,40                           |
| 10         | Draden van 0,5mm² (wit)                      | € 1,60                           |
| 1          | Adereindhulzen voor 0,5mm²                   | € 2,31                           |
| 6          | Wago's 5P                                    | € 4,93                           |
|            |Totaal                                        | € 151,97                         |
