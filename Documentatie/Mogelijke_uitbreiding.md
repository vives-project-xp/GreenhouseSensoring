# Mogelijke Uitbreidingen
Onze opdracht is het uitwerken van een testopstelling van de sensormogelijkheden voor een serre. Omdat wij uiteraard gaandeweg in ons project aspecten tegenkwamen die beter zouden kunnen of als extraatje toegevoegd kunnen worden, maakten we hieronder een overzicht op van uitbreidingen die mogelijk toegepast kunnen worden bij een definitievere uitwerking van deze testopstelling. 

## Inhoudsopgave
- [Mogelijke Uitbreidingen](#mogelijke-uitbreidingen)
  - [Inhoudsopgave](#inhoudsopgave)
  - [Meer ESP's](#meer-esps)
  - [Nieuwe Sensoren](#nieuwe-sensoren)
  - [Verbeterde Aansluitingen](#verbeterde-aansluitingen)
  - [Geautomatiseerde Rapportage](#geautomatiseerde-rapportage)
  - [Veiligheidsverbeteringen](#veiligheidsverbeteringen)

## Meer ESP's
Omdat wij de functionaliteit willen aantonen van dit concept, en bijkomend ook met een beperkt budget werken, maakten wij gebruik van 1 ESP-microcontroller. We raden bij een uitbreiding van dit project aan om per plantje een aparte esp te gebruiken, zodat je geen problemen opduiken. Er zijn bijvoorbeeld een beperkt aantal UART poorten op de ESP, waarvan 1 al gebruikt wordt om serieel via USB eventueel data te versturen naar een PC bij het testen. Het gebruik van meerdere ESP's zorgt ook voor een overzichtelijkere opstelling en meer variatie in de plaats van de opstelling. Ook wordt door ons aangeraden om een aparte ESP te voorzien voor sensoren die de volledige omgeving meten (omgevingstemperatuur, vocht, CO2, lichtintensiteit).

## Nieuwe Sensoren
- Sapflow sensor
  - Meet de snelheid van het sap op de plant
- pH-sensor
  - Meet de zuurgraad van de bodem
- Chlorofylsensor
  - Meet het chlorofylgehalte in de bladeren.
- UV-sensor
  - Meet hoeveel UV-straling er is (niet hetzelfde al onze sensor die de lichtintensiteit meet uitgedrukt in lux)

## Verbeterde Aansluitingen en ontwerp
Het kan handig zijn om de draadjes met krimpkousen aan te sluiten, nu hebben we dit met plakband gedaan omdat er geen krimpkous of dergelijk materiaal ter beschikking. Ook zou het goed zijn om voor de lichtintensiteitsensor een doosje te printen in doorzichtige print, wat voor ons niet mogelijk was. Wij gebruikten hiervoor een bestaand doorzichtig doosje, maar dit is uiteraard niet specifiek afgestemd op dit product. Daarbij moet dit ook in een speciaal printmateriaal geprint worden dat tegen zonlicht kan.
Tot slot zou het kunnen helpen om het 3D doosje groter maken in breedte en in hoogte en vakjes te maken om de wago's netjes in te plaatsen. Wij maakten ook geen gebruik van een specifiek ontworpen PCB, grotendeels omwille van de kost. Het adapterbordje voor de ESP zorgt voor een behoorlijke nette oplossing. Indien hiervan meerdere producten gemaakt zouden worden, is een PCB uiteraard een optie.

## Veiligheidsverbeteringen
Mede doordat we gebruik maken van een CO2 sensor die voortdurend wat luchttoevoer moet hebben en we de componenten ook wat wilden verluchten, kozen we ervoor om aan de zijkant van ons doosje gleufjes te plaatsen. Echter is het product hierdoor in principe niet 100 procent waterdicht. Een mogelijke oplossing hiervoor kan het plaatsen van een speciale plastic over het doosje (met open onderkant) dat opengeritst kan worden als men het doosje wil openen.