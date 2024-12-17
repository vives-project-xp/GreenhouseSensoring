# Technische documentatie

In dit document werd alle technische documentatie van de testopstelling samengebracht, zodat eventueel verder gebouwd kan worden hierop.

TODO: uitleggen hoe tijdelijke esp vervangen met (nieuwe) definitieve (kabels weg en plaatsen en welke pinnen veranderen)

TODO: omgevingstemp aanbrengen

## Inhoudsopgave

- [Technische documentatie](#Technische-documentatie)
  - [Inhoudsopgave](#inhoudsopgave)
  - [Inleiding](#inleiding)
    - [Stap 1](#stap-1)
    - [Stap 2](#stap-2)
    - [Stap 3](#stap-3)
    - [Stap 4](#stap-4)
    - [Stap 5](#stap-5)
    - [Stap 6](#stap-6)
  - [Conclusie](#conclusie)

## Inleiding
In deze handleiding wordt besproken hoe je nieuwe sensoren kan toevoegen aan dit project.

### Stap 1
Denk na over wat je wilt meten en welke sensor je hiervoor kan gebruiken. Deze sensor kan alleen op 5V of 3.3V werken.

### Stap 2
Maak met de datasheets een aansluitschema zodat je zeker weet dat het mogelijk is.

### Stap 3
Maak een code voor op de esp met de datasheets van de sensoren/esp. Zorg hierbij dat de waardes correct worden doorgestuurd naar home assistant.
Je kan altijd kijken naar de vorige sensoren hoe dit gebeurd is.

### Stap 4
Als de sensor geleverd is moet je deze eerst testen in een test opstelling. Om te kijken of alles werkt.

### Stap 5
Nu kan je de sensor Solderen in de echte opstelling. Doe dit in een veilige omgeving. Als de sensor geplaatst is en werkt dan bent u klaar. Nu kan je kijken in de home assistent wat de waardes zijn.

### Stap 6
Regelmatig de sensoren controleren op vuiligheid en stof zodat ze optimaal werken.

## Conclusie
Nu kunnen er nieuwe sensoren geplaatst worden in de serre. Als er nog vraagtekens zijn kan je altijd de vorige sensoren bekijken en hun documenten.
