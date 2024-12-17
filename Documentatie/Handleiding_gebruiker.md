# Handleiding voor de gebruiker van de data

## Aansluiten op netwerk
Het gebruiken van het product is vrij simpel. Wanneer deze in het stopcontact gestopt is, zou de ESP na enkele seconden automatisch verbinding moeten maken. Als deze verbinding kan maken met het Devbit netwerk, zullen de waarden doorgestuurd worden naar home assistant. Indien geen verbinding gemaakt kan worden, zal uiteraard niets verstuurd kunnen worden (ook eventuele seriële data zal niet verstuurd worden). Wanneer de verbinding tot stand gekomen is, kan het voor enkele sensoren enkele seconden tot een minuutje duren voor ze hun waardes doorsturen. De esp heeft een IP-adres dat vaststaat voor die esp, zodat home assistant weet welk specifiek toestel dit is.

## Sensoren en hun waardes
Wie surft naar de home assistant of het dashboard raadpleegd, zal onderstaande tabel zien staan met alle waarden: 

![home-assistant](<Schermafbeelding 2024-12-17 111951.png>)

We zien dat de esp verbonden is met het netwerk en alle sensoren waardes doorsturen. Hieronder overlopen we elke sensor en daarbij ook gemiddelde waardes en wat de waardes willen zeggen voor de plant of omgeving. (Om de meer technische documentatie van sensor te raadplegen, klik [hier](./Algemene%20info%20componenten/README.md).)

### Bodem temperatuur:
De bodemtemperatuur is de sensor met de witte kabel, deze moet voldoende diep in de grond gestopt worden, tot aan de zwarte band ongeveer. Waardes voor de bodemtemperatuur hangen uiteraard af van weersomstandigheden, en meestal kan hier niet veel aan veranderd worden door iemand. Wel geeft het een goede indicatie of de omgeving geschikt is voor de plant. Hoewel dit afhangt van plant tot plant, ligt de gemiddelde waarde voor een goede groei tussen de 8 en 30 graden C.

### Lichtmeter:
Deze sensor meet de lichtintensiteit, uitgedrukt in lux, voor de gehele serre en niet voor 1 plantje specifiek. Uiteraard geldt hoe meer zonlicht, en dus een hogere waarde, hoe beter voor de groei van de plant. Aan de hand van deze gemeten waardes zorgt project Light & Heat voor een verbetering van de lichtintensiteit voor de serre.

### NPK-sensor
De NPK-sensor geeft de voedingstoffen in de bodem weer. Dit zijn Stikstof (N), Fosfor (P) en Kalium (K).
    
    Stikstof is het groeihormoon voor planten en is de allerbelangrijkste stof. Het zorgt voor een goede werking van de fotosynthese, zonder deze stof zal een plant geel worden en zijn bladeren verliezen. Een ideale waarde ligt rond de 20 à 60 mg/kg.

    Fosfor zorgt voornamelijk voor de ontwikkeling van de wortels van een plant, ze worden sterker door fosfor. Een ideale waarde ligt rond de 20 à 50 mg/kg.

    Kalium houdt ten slotte de waterhuishouding in stand. Celwanden van de plant worden erdoor verstevigd, wat zorgt voor een plant met een betere weerstand. Een ideale waarde ligt rond de 100 à 300 mg/kg.

Echter moeten wij bij deze sensor een kleine kanttekening opmaken, deze werkt namelijk niet optimaal. Om goede metingen te hebben, moet de aarde zeer vochtig zijn (bijna modder). In praktijk is dit bijna nooit het geval, waardoor deze zeer vaak de waardes 0 zal doorgeven.

### Bodemvochtsensor
De bodemvochtsensor geeft a.d.h.v. een analoge waarde (die omgezet werd naar een percentage) het vochtigheidspercentage in de bodem weer. Let op dat deze niet te diep in de bodem zit, de witte streep op de sensor is het absolute maximum. Als deze totaal niet vochtig is en gewoon ergens ligt zal een waarde van rond de 4 à 7 procent gegeven worden, dit omdat in de omgeving natuurlijk ook vocht zit. Bij twijfel of de grond te droog is (of net te vochtig), kan deze waarde geraadpleegd worden.

### CO2-sensor
CO2 is een belangrijk onderdeel voor fotosynthese van een plant. Het is belangrijke om een goede balans tussen zuurstof en CO2 te hebben, er moet dus verlucht worden indien nodig. Een ideale CO2 waarde voor de buitenlucht ligt rond de 400 ppm.

### Omgevingsvocht- en temperatuursensor
Momenteel is deze sensor bij ons niet ter beschikking, echter is deze zeer goedkoop en ook zeer simpel aan te brengen, zie [dit document](./Technische_documentatie.md). Deze meet voor de serre in z'n geheel, en niet per plantje. Beide waardes worden door deze sensor gemeten.