<h1>Architectuur:</h1>
Er wordt gebruik gemaakt van de ESP32 Devkit V1 board als microcontroller voor de aansturing. De ESP zal in een 3D-geprinte box geplaatst worden en aan een speciale adapter bevestigd worden om kabels makkelijker te kunnen bevestigen: 
<br></br>
<img src="./Afbeeldingen/ESP-adapter.webp"></img>
<br></br>
<h1>Sensoren</h1>
De volgende 6 sensoren worden gebruikt voor het monitoren van de planten:

<h2>Temperatuur- en vochtsensor omgeving</h2>
<img src="./Afbeeldingen/Temp-vochtsensor-omgeving.webp"></img>
<br></br>
<ul>
    <li><b>Beschrijving:</b> Deze sensor (Temperatuur/Vochtigheid Sensor Module Breakout - HTU21D (OT3567)) meet zowel de omgevingstemperatuur als vocht in de omgeving van de serre. Hiervoor zal een klein boxje geprint worden om deze veilig op te bergen. </li>
    <li><b>Elektrische eigenschappen:</b> gevoed op 3.3V, rechtstreeks via ESP. Stoom ligt tussen 300 en 500 µA in actieve toestand (tussen 0.02 en 0.14 µA in sleeping mode).</li>
    <li><b>Overig:</b> Er zijn ook een SCL/SDA pin die rechtstreeks op pin D21 en D22 op de ESP aangesloten kunnen worden. Echter is er ook nog een andere sensor (lichtsensor) die ook SCL/SDA. Dit zou geen probleem moeten vormen omdat beide sensoren een ander I2C-adres hebben. Deze sensor werkt op het 0x40 adres. </li>
</ul>

<h2>Lichtintensiteitsensor</h2>

<ul>
<li><b>Beschrijving:</b> Deze sensor werkt op I2C, werkt op het 0x5C adres (indien ADDR hoog is) of het 0X23 adres (indien ADDR laag is) (bron: datasheet p. 10).</li>
<li><b>Elektrische eigenschappen:</b></li>
<li><b>Overig:</b></li>
</ul>