<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T06:37:03+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "fi"
}
-->
# Vianmääritysohje

Tämä opas auttaa sinua ratkaisemaan yleisiä ongelmia, joita voi ilmetä IoT for Beginners -oppimateriaalin parissa työskennellessä. Ongelmat on järjestetty kategorioittain helppoa selailua varten.

## Sisällysluettelo

- [Asennusongelmat](../..)
  - [Pythonin asennus](../..)
  - [VS Code ja laajennukset](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove-kirjastot](../..)
- [Laitteisto-ongelmat](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuaalilaite (CounterFit)](../..)
- [Yhteysongelmat](../..)
  - [WiFi-yhteys](../..)
  - [Pilvipalvelut](../..)
  - [MQTT](../..)
- [Anturi- ja toimilaiteongelmat](../..)
  - [Grove-anturit](../..)
  - [Kamera](../..)
  - [Mikrofoni ja kaiutin](../..)
- [Kehitysympäristöongelmat](../..)
  - [VS Code](../..)
  - [Python-virtuaaliympäristöt](../..)
  - [Riippuvuudet](../..)
- [Suorituskykyongelmat](../..)
- [Yleisimmät virheilmoitukset](../..)
- [Apua saatavilla](../..)

---

## Asennusongelmat

### Pythonin asennus

#### Ongelma: Python-versio on liian vanha
**Virhe:** `Python 3.6 tai uudempaa vaaditaan`

**Ratkaisu:**
1. Lataa uusin Python 3 osoitteesta [python.org](https://www.python.org/downloads/)
2. Asennuksen aikana Windowsissa valitse "Add Python to PATH"
3. Tarkista asennus:
   ```bash
   python3 --version
   ```

#### Ongelma: Useat Python-versiot aiheuttavat konflikteja
**Oireet:** Väärä Python-versio käynnistyy, paketit asentuvat väärään sijaintiin

**Ratkaisu:**
- **Windows:** Käytä `py -3` komentoa `python` sijaan kutsuaksesi Python 3:ta suoraan
- **macOS/Linux:** Käytä `python3` komentoa `python` sijaan
- Luo ja käytä aina virtuaaliympäristöjä projekteissa

#### Ongelma: pip-komentoa ei löydy
**Virhe:** `'pip' ei tunnistettu sisäiseksi tai ulkoiseksi komennoksi`

**Ratkaisu:**
1. Kokeile `pip3` komentoa `pip` sijaan
2. Tai käytä `python -m pip` tai `python3 -m pip`
3. Varmista, että Python on lisätty PATHiin (asenna Python uudelleen ja tarkista valinta)

### VS Code ja laajennukset

#### Ongelma: Pylance-laajennus ei toimi
**Oireet:** Ei Python-intelliSenseä, koodin täydentämistä tai tyyppitarkistusta

**Ratkaisu:**
1. Avaa VS Code -komentopaletti (`Ctrl+Shift+P` tai `Cmd+Shift+P`)
2. Suorita "Python: Select Interpreter"
3. Valitse oikea Python-tulkki (virtuaaliympäristö, jos käytössä)
4. Lataa VS Code uudelleen

#### Ongelma: VS Code ei tunnista virtuaaliympäristöä
**Oireet:** Väärä Python-tulkki valittu

**Ratkaisu:**
1. Varmista, että olet aktivoinut virtuaaliympäristön terminalissa
2. Avaa komentopaletti ja suorita "Python: Select Interpreter"
3. Valitse tulkki `.venv`-kansiosta
4. Tarkista tilapalkista (vasen alakulma), että oikea Python-versio näkyy

### PlatformIO (Wio Terminal)

#### Ongelma: PlatformIO:n asennus epäonnistuu
**Virhe:** Erilaisia virheitä PlatformIO:n asennuksen aikana

**Ratkaisu:**
1. Varmista, että VS Code on päivitetty
2. Asenna ensin C/C++ -laajennus
3. Käynnistä VS Code uudelleen PlatformIO:n asennuksen jälkeen
4. Tarkista internet-yhteys (PlatformIO lataa suuria tiedostoja)

#### Ongelma: PlatformIO ei tunnista laitetta
**Oireet:** Koodia ei saa ladattua Wio Terminaliin

**Ratkaisu:**
1. Kokeile toista USB-kaapelia (jotkut kaapelit ovat vain latauskaapeleita)
2. Tarkista Laitehallinnasta (Windows) tai komennolla `ls /dev/tty*` (macOS/Linux)
3. Asenna tai päivitä USB-ajurit
4. Kokeile eri USB-porttia
5. Liikuta Wio Terminalin virtakytkintä kahdesti nopeasti päästäksesi bootloader-tilaan

#### Ongelma: Kääntämisvirheitä PlatformIO:ssa
**Virhe:** `fatal error: Arduino.h: No such file or directory`

**Ratkaisu:**
1. Poista projektin `.pio` kansio
2. Suorita "PlatformIO: Rebuild" komentopaletista
3. Varmista, että `platformio.ini` sisältää oikean kortin määrityksen:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove-kirjastot

#### Ongelma: Grove-kirjaston tuonti epäonnistuu Raspberry Pillä
**Virhe:** `ModuleNotFoundError: No module named 'grove'`

**Ratkaisu:**
1. Asenna Grove-kirjastot uudelleen:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Jos käytät virtuaaliympäristöä, saatat joutua asentamaan ne globaalisti tai kopioimaan kirjastot
3. Varmista, että I2C on käytössä: `sudo raspi-config nonint do_i2c 0`

#### Ongelma: Grove-anturia ei tunnisteta
**Virhe:** `IOError: [Errno 121] Remote I/O error`

**Ratkaisu:**
1. Tarkista fyysiset liitännät (varmista, että Grove-kaapeli on kunnolla kiinni)
2. Varmista, että anturi on kytketty oikeaan porttiin (analoginen, digitaalinen, I2C, UART)
3. Suorita `i2cdetect -y 1` nähdäksesi, näkyykö laite I2C-väylällä
4. Kokeile eri Grove-kaapelia
5. Varmista, että Grove Base Hat on oikein paikoillaan Raspberry Pin GPIO-nastoissa

---

## Laitteisto-ongelmat

### Raspberry Pi

#### Ongelma: Raspberry Pi ei käynnisty
**Oireet:** Ei näyttöä, ei LED-toimintaa tai sateenkaaren värinen näyttö

**Ratkaisu:**
1. **Tarkista virtalähde:** Käytä virallista 5V 3A USB-C virtalähdettä Pi 4:lle
2. **SD-korttiongelmat:** 
   - Alusta SD-kortti ja asenna Raspberry Pi OS uudelleen
   - Kokeile eri SD-korttia (suositeltuja merkkejä)
   - Varmista, että SD-kortti on kunnolla paikallaan
3. **Tarkista HDMI-yhteys:** Kokeile molempia HDMI-portteja Pi 4:ssä, käytä virtalähteen läheisintä HDMI-porttia

#### Ongelma: SSH-yhteys Raspberry Pi:hin ei toimi
**Oireet:** Yhteys evätty tai aikakatkaisu

**Ratkaisu:**
1. Ota SSH käyttöön:
   - Kun kirjoitat SD-korttia Raspberry Pi Imagerilla, ota SSH käyttöön lisäasetuksista
   - Tai luo tyhjä tiedosto nimeltä `ssh` (ilman tiedostopäätettä) käynnistysosiolle
2. Etsi Pi:n IP-osoite:
   - Tarkista reitittimesi liitetyt laitteet
   - Käytä `ping raspberrypi.local` (jos mDNS toimii)
   - Käytä verkon skannausohjelmia kuten `nmap` tai Angry IP Scanner
3. Tarkista verkko:
   - Varmista, että Pi on samassa verkossa kuin tietokoneesi
   - Kokeile ethernet-yhteyttä WiFi:n sijaan
4. Tarkista käyttäjätunnus/salasana (oletus: käyttäjätunnus `pi`, salasana `raspberry`)

#### Ongelma: Grove Base Hat ei tunnistu
**Oireet:** Anturit eivät toimi, I2C-virheitä

**Ratkaisu:**
1. Varmista, että Base Hat on kunnolla kiinni kaikissa GPIO-nastoissa
2. Tarkista, ettei Pi:n tai Base Hatin nastoissa ole taittuneita nastoja
3. Ota I2C-käyttöliittymä käyttöön:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Varmista, että I2C toimii: `i2cdetect -y 1`

#### Ongelma: Raspberry Pi toimii hitaasti
**Oireet:** Käyttöliittymä tökkii, vaste hidasta

**Ratkaisu:**
1. Tarkista SD-kortin nopeus (käytä Class 10 tai parempaa, tai SSD USB:n kautta)
2. Vapauta levytilaa: `df -h` tarkastaa, poista turhat tiedostot
3. Vähennä GPU-muistin määrää `raspi-config`issa, jos kameraa/näyttöä ei käytetä paljon
4. Sulje tarpeettomat sovellukset
5. Harkitse Pi 4:ään vaihto, jossa on enemmän RAM-muistia, jos käytössä on Pi 3 tai vanhempi

### Wio Terminal

#### Ongelma: Wio Terminalin näyttö pysyy tyhjänä
**Oireet:** Ei kuvaruutulähtöä koodin latauksen jälkeen

**Ratkaisu:**
1. Tarkista, että koodi alustaa näytön (TFT_eSPI-kirjasto)
2. Päivitä Wio Terminalin laiteohjelmisto [Seeed Wikistä](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Lisää näytön alustuskoodi:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Kokeile ladata esimerkkisketsi PlatformIO:sta testataksesi laitetta

#### Ongelma: WiFi ei toimi Wio Terminalissa
**Oireet:** Ei yhteyttä WiFi-verkkoon, verkko-ongelmia

**Ratkaisu:**
1. **Päivitä WiFi-laiteohjelmisto:** Noudata [Wio Terminal WiFi -päivitysohjetta](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Tarkista WiFi-tunnukset:** Varmista, että SSID ja salasana ovat oikein
3. **WiFi-taajuus:** Wio Terminal tukee vain 2.4 GHz WiFiä (ei 5 GHz)
4. **Signaalin voimakkuus:** Siirry lähemmäs reititintä
5. **Reitittimen asetukset:** Jotkin yritys- tai WPA-Enterprise-verkot eivät toimi

#### Ongelma: Wio Terminal ei tunnistu tietokoneessa
**Oireet:** USB-laite ei tunnistu

**Ratkaisu:**
1. **Kokeile eri USB-kaapelia:** Käytä datakaapelia, ei pelkkää latauskaapelia
2. **Siirry bootloader-tilaan:** Liikuta virtakytkintä alas kahdesti nopeasti
   - Sininen LED vilkkuu, laite näkyy Laitehallinnassa nimellä "Arduino"
3. **Asenna ajurit (Windows):**
   - Lataa ja asenna [Seeed USB -ajuri](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Kokeile eri USB-porttia:** Vältä USB-keskittimiä, käytä suoraa yhteyttä
5. **Päivitä järjestelmän USB-ajurit**

#### Ongelma: Anturit eivät toimi Wio Terminalissa
**Oireet:** Grove-antureilta ei tule mittaustietoja

**Ratkaisu:**
1. Tarkista Grove-kaapelin liitännät
2. Varmista, että käytät oikeaa Grove-porttia (vasen tai oikea)
3. Sisällytä sensorin vaatimat kirjastot
4. Tarkista anturin virtavaatimukset
5. Testaa anturi kirjaston esimerkkikoodilla

### Virtuaalilaite (CounterFit)

#### Ongelma: CounterFit-sovellus ei käynnisty
**Virhe:** Erilaisia Python-virheitä CounterFitin käynnistyessä

**Ratkaisu:**
1. Varmista, että virtuaaliympäristö on aktivoitu
2. Asenna tai asenna CounterFit uudelleen:
   ```bash
   pip install CounterFit
   ```
3. Tarkista, ettei portti 5000 ole jo käytössä:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Lopeta prosessi, joka käyttää porttia 5000, tai käytä eri porttia:
   ```bash
   counterfit --port 5001
   ```

#### Ongelma: Yhteyttä CounterFitiin ei saada koodista
**Virhe:** Yhteys evätty tai aikakatkaisu

**Ratkaisu:**
1. Varmista, että CounterFit on käynnissä: Avaa selaimella `http://127.0.0.1:5000`
2. Tarkista, että koodin yhteys-URL vastaa CounterFitin osoitetta
3. Varmista, ettei palomuuri estä yhteyttä
4. Kokeile käynnistää uudelleen sekä CounterFit-sovellus että koodisi

#### Ongelma: Antureita ei näy CounterFitissä
**Oireet:** Luodut anturit eivät näy CounterFitin käyttöliittymässä

**Ratkaisu:**
1. Luo anturit CounterFitin käyttöliittymässä ennen koodin suorittamista
2. Päivitä selaimen sivu
3. Tarkista, että anturityyppi vastaa koodin odotuksia
4. Tyhjennä selaimen välimuisti

---

## Yhteysongelmat

### WiFi-yhteys

#### Ongelma: Laite ei yhdistä WiFi-verkkoon
**Oireet:** Yhteyden aikakatkaisu, todennus epäonnistui

**Ratkaisu:**
1. **Tarkista SSID ja salasana:** Varmista kirjautumistiedot
2. **WiFi-taajuus:** Suurin osa IoT-laitteista tukee vain 2.4 GHz (ei 5 GHz)
3. **Reitittimen asetukset:**
   - Poista käytöstä AP-eristys, jos se on päällä
   - Käytä WPA2-PSK -salausta (vältä WPA3:a, WEP:iä tai avoimia verkkoja)
   - Varmista, että DHCP on päällä
4. **Piilotetut verkot:** Jos SSID on piilotettu, se täytyy määrittää eksplisiittisesti
5. **Signaalin voimakkuus:** Siirrä laite lähemmäs reititintä
6. **Häiriöt:** Muut laitteet, mikroaaltouunit tai seinät voivat aiheuttaa häiriöitä

#### Ongelma: WiFi-yhteys katkeilee usein
**Oireet:** Katkonainen yhteys

**Ratkaisu:**
1. Tarkista reitittimen vakaus ja harkitse uudelleenkäynnistystä
2. Päivitä laitteen laiteohjelmisto
3. Käytä staattista IP-osoitetta DHCP:n sijaan
4. Lyhennä etäisyyttä reitittimeen tai lisää WiFi-toistin
5. Tarkista häiriöt muista laitteista
6. Varmista riittävä virransyöttö (erityisesti Raspberry Pi:lle)

### Pilvipalvelut

#### Ongelma: Yhteyttä Azure IoT Hubiin ei saada
**Virhe:** Todennus epäonnistui, yhteys evätty

**Ratkaisu:**
1. **Tarkista kirjautumistiedot:**
   - Varmista, että yhteysmerkkijono on oikea
   - Ei ylimääräisiä välilyöntejä tai rivinvaihtoja yhteysmerkkijonossa
2. **Tarkista laitteen rekisteröinti:** Laite täytyy olla rekisteröity IoT Hubiin
3. **Palomuuri/proxy:** Salli lähtöliikenne MQTT:lle (portti 8883) tai HTTPS:lle (portti 443)
4. **IoT Hubin sijainti:** Varmista, että IoT Hub on käynnissä eikä eri sijainnissa, joka aiheuttaa viiveitä
5. **Käyttörajoitukset:** Tarkista, ettei ilmaisversion rajoja ole ylitetty
6. **Testaa yhteys:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Ongelma: Azure Functions ei laukea
**Oireet:** Viestit lähetetty, mutta funktio ei suoritettu

**Ratkaisu:**
1. Tarkista, että Function App on käynnissä (ei pysäytetty)
2. Varmista, että yhteysmerkkijono on oikein Function Appin asetuksissa
3. Tarkista lokit Azure-portaalista
4. Varmista, että Event Hub -yhteensopiva päätepiste on määritetty oikein
5. Tarkista viestin muoto vastaa funktion odotuksia
6. Tarkista Function Appin palvelusuunnitelma (kulutus vs. omistettu)

### MQTT
#### Ongelma: MQTT-yhteys epäonnistuu  
**Virhe:** Yhteys evätty, tunnistautuminen epäonnistui

**Ratkaisu:**  
1. **Välittäjän osoite:** Tarkista, että välittäjän URL/IP on oikein  
2. **Portti:** Tarkista porttinumero (1883 salauksettomalle, 8883 TLS:lle)  
3. **Tunnistautuminen:** Tarkista käyttäjätunnus/salasana tarvittaessa  
4. **TLS/SSL:** Varmista, että varmenteet ovat voimassa ja luotettuja  
5. **Palomuuri:** Tarkista, ettei portti ole estetty  
6. **Testaa MQTT-asiakkaalla:** Käytä MQTT Exploreria tai mosquitto_pub/sub:ta testaukseen  

#### Ongelma: MQTT-viestejä ei vastaanoteta  
**Oireet:** Viestit julkaistu, mutta tilaajat eivät saa niitä

**Ratkaisu:**  
1. **Aiheiden nimet:** Varmista, että tilaajan aihe vastaa tarkasti julkaisijan aihetta  
2. **QoS-taso:** Kokeile QoS 1 tai 2 sijaan 0  
3. **Jokapäiväiset:** Tarkista, että aihejokapäiväiset on käytetty oikein (`+` yksitasoinen, `#` monitasoinen)  
4. **Pidätetyt viestit:** Julkaisija voi asettaa retain-lipun viimeisen viestin säilyttämiseksi  
5. **Yhteyden aikataulu:** Varmista, että tilaaja yhdistää ennen viestien julkaisua  

---

## Anturi- ja toimilaiteongelmat

### Grove-anturit

#### Ongelma: Anturi palauttaa virheellisiä arvoja  
**Oireet:** Lukemat ovat 0, -1 tai järjettömiä arvoja

**Ratkaisu:**  
1. **Tarkista liitännät:** Varmista, että anturi on oikein liitetty  
2. **Oikea portti:** Varmista, että anturi on oikeantyyppisessä portissa:  
   - Analogiset anturit → Analogiportit (A0, A2, A4)  
   - Digitaaliset anturit → Digitaaliporit (D5, D16, D18 jne.)  
   - I2C-anturit → I2C-portit  
3. **Kalibrointi:** Jotkin anturit tarvitsevat kalibrointia (maankosteus, valo)  
4. **Virta pois/päällä:** Irrota ja liitä anturi uudelleen  
5. **Anturin tekniset tiedot:** Tarkista anturin speksit ja vaatimukset  

#### Ongelma: Kapasitiivinen maankosteusanturi mittaa aina märkää  
**Oireet:** Anturi mittaa korkean kosteuden myös kuivana

**Ratkaisu:**  
1. **Kalibrointi tarvitaan:** Maankosteusanturit vaativat kalibroinnin:  
   - Lue arvo ilmassa (kuiva nollataso)  
   - Lue arvo vedessä (märkä taso)  
   - Karttaa lukemat näiden välillä  
2. **Tarkista anturin pinnoite:** Kosteusanturit voivat vahingoittua, jos pinnoite vaurioituu  
3. **Sijoitus:** Varmista, että anturi on kokonaan upotettu maahan  

#### Ongelma: Lämpötila/kosteusanturin lukemat virheellisiä  
**Oireet:** DHT11/DHT22 näyttää väärää lämpötilaa tai kosteutta

**Ratkaisu:**  
1. **Anturin sijoitus:** Vältä suoraa auringonvaloa, lämmönlähteitä tai ilmavirtauksia  
2. **Lämmittelyaika:** Anna anturin lämmetä 2 sekuntia virran kytkemisen jälkeen ennen lukemista  
3. **Lukemisväli:** DHT-anturit tarvitsevat vähintään 2 sekunnin välin lukemien välillä  
4. **Tarkista kondensaatio:** Se voi vaikuttaa lukemiin  
5. **Anturin laatu:** DHT11 on vähemmän tarkka kuin DHT22  

### Kamera

#### Ongelma: Kameraa ei havaita Raspberry Pi:ssä  
**Virhe:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Ratkaisu:**  
1. **Ota kamera käyttöön:**  
   ```bash
   sudo raspi-config
   ```
   Mene Interface Options → Camera → Enable  
2. **Tarkista nauhapiuha:** Varmista, että kameran kaapeli on oikein liitetty  
   - Sininen puoli kohtaa USB-portit Pi Zero:ssa  
   - Sininen puoli poispäin USB-porteista Pi 4:ssä  
3. **Päivitä laiteohjelmisto:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testaa kamera:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Ongelma: Kameran kuvat ovat huonolaatuisia  
**Oireet:** Epätarkat, tummat tai haaleat kuvat

**Ratkaisu:**  
1. **Tarkennus:** Poista suojaava kalvo linssistä, säädä tarkennusta jos mahdollista  
2. **Valaistus:** Varmista riittävä valaistus  
3. **Kameran asetukset:** Säädä valotusta, ISO-arvoa, valkotasapainoa koodissa  
4. **Vakavuus:** Pidä kamera paikallaan, käytä jalustaa tarvittaessa  
5. **Resoluutio:** Älä ylitä kameran maksimiresoluutiota  

### Mikrofoni ja kaiutin

#### Ongelma: Ei ääniinputtia/outputtia  
**Oireet:** Mikrofoni ei tallenna, kaiutin ei soita

**Ratkaisu:**  
1. **Tarkista liitännät:** Varmista, että äänilaitteet ovat oikein kytketty  
2. **Testaa laitteisto:**  
   - Kaiutin: `speaker-test -t wav -c 2`  
   - Mikrofoni: `arecord -l` listaa, `arecord test.wav` tallentaa  
3. **Äänenvoimakkuusasetukset:** Tarkista ja säädä äänenvoimakkuutta:  
   ```bash
   alsamixer
   ```
4. **Valitse äänilaite:** Määritä oikea laite koodissa  
5. **Ajuriongelmat:** Päivitä ALSA tai asenna uudelleen ääniajurit  

#### Ongelma: ReSpeaker-hattu ei toimi  
**Oireet:** Äänilaite ei havaittu

**Ratkaisu:**  
1. **Asenna ajurit:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Tarkista asennus:** `arecord -l` pitäisi näyttää ReSpeaker  
3. **Päivitä laiteohjelmisto:** Joissakin Pi OS -versioissa tarvitaan ajuripäivityksiä  
4. **Tarkista kiinnitys:** Varmista, että hattu on kunnolla kiinni GPIO-pinnoissa  

---

## Kehitysympäristöongelmat

### VS Code

#### Ongelma: Pääte ei aktivoi virtuaaliympäristöä automaattisesti  
**Oireet:** Pääte avautuu, mutta venv ei ole päällä

**Ratkaisu:**  
1. **Valitse Python-tulkki:** Komentopaletti → "Python: Select Interpreter" → Valitse venv  
2. **Käynnistä VS Code uudelleen** valinnan jälkeen  
3. **Tarkista asetukset:** Lisää `settings.json`-tiedostoon:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Ongelma: Koodi ei suoritu laitteella  
**Oireet:** Koodi pyörii, mutta laitteella ei tapahdu mitään

**Ratkaisu:**  
1. **Varmista, että koodi on tallennettu** (tarkista piste tiedostovälilehdellä)  
2. **Tarkista, mikä Python ajetaan:** `which python` tai `where python`  
3. **Wio Terminalilla:** Varmista, että koodi on ladattu PlatformIO:n kautta (paina latauspainiketta)  
4. **Raspberry Pi:** SSH:lla Pi:hin ja suorita koodi siellä  
5. **Tarkista tulosteikkuna** virheiden varalta  

#### Ongelma: IntelliSense ei näytä kirjastofunktioita  
**Oireet:** Ei automaattista täydennystä tuoduille moduuleille

**Ratkaisu:**  
1. Varmista kirjaston asennus nykyiseen ympäristöön  
2. Lataa VS Code -ikkuna uudelleen  
3. Tarkista Python-tulkin oikeellisuus  
4. Asenna tyypityspaketit, jos saatavilla: `pip install types-<library-name>`  

### Pythonin virtuaaliympäristöt

#### Ongelma: Virtuaaliympäristön luonti epäonnistuu  
**Virhe:** `The virtual environment was not created successfully`

**Ratkaisu:**  
1. **Asenna venv-moduuli:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Sisältyy Pythonin mukana  
   - Windows: Asenna Python uudelleen kaikkine osineen  
2. **Tarkista Pythonin asennus:** Varmista, että Python on oikein asennettu  
3. **Käytä täyttä polkua:** Kokeile `python3 -m venv .venv` käyttäen eksplisiittistä python3-kutsua  

#### Ongelma: Pakettille asennetaan väärä sijainti  
**Oireet:** Import-virhe paketista asennuksen jälkeen

**Ratkaisu:**  
1. **Varmista, että venv on päällä:** Komentorivillä näkyy `(.venv)`  
2. **Tarkista pipin sijainti:** `which pip` osoittaa `.venv/bin/pip`  
3. **Asenna uudelleen venvissä:** Aktivoi venv ja aja `pip install <package>`  
4. **Älä käytä sudoa pipin kanssa** virtuaaliympäristössä  

#### Ongelma: Virtuaaliympäristö ei ole siirrettävissä  
**Oireet:** Venv ei toimi siirron tai eri tietokoneen jälkeen

**Ratkaisu:**  
1. **Älä siirrä venv:iä:** Poista ja luo uudelleen oikeassa paikassa  
2. **Käytä requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Luo venv uudelleen:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # tai activate.bat Windowsilla
   pip install -r requirements.txt
   ```
  
### Riippuvuudet

#### Ongelma: Paketin asennus epäonnistuu  
**Virhe:** Erilaisia pip-virheitä asennuksen aikana

**Ratkaisu:**  
1. **Päivitä pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Asenna build-työkalut:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Asenna Visual Studio Build Tools  
3. **Tarkista internet-yhteys**  
4. **Kokeile eri pakettivarastoa:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Asenna tietty versio:** `pip install <package>==<version>`  

#### Ongelma: Riippuvuuksien ristiriidat  
**Virhe:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Ratkaisu:**  
1. **Käytä uutta virtuaaliympäristöä** projektia kohden  
2. **Päivitä paketit:** `pip install --upgrade <package>`  
3. **Tarkista vaatimukset:** Käytä `pip check` ristiriitojen löytämiseen  
4. **Asenna yhteensopivat versiot:** Määritä versioalueet requirements.txt:ssä  

---

## Suorituskykyongelmat

### Ongelma: Koodi toimii hitaasti  
**Oireet:** Viiveet, aikakatkaisut, reagoimattomuus

**Ratkaisu:**  
1. **Vähennä sensorin lukemistiheyttä:** Älä lue antureita liian usein  
2. **Optimoi silmukat:** Vältä turhaa odotusta, käytä sleep()-funktiota tai viiveitä  
3. **Muisti:**  
   - Sulje tarpeettomat sovellukset  
   - Vapauta levytilaa  
   - Seuraa tilaa `top` tai `htop` -komennolla Pi:llä  
4. **SD-kortin nopeus:** Käytä nopeampaa SD-korttia tai SSD:tä Raspberry Pi:lle  
5. **Verkkoviiveet:** Käytä asynkronisia toimintoja verkkokutsuissa  

### Ongelma: Muistin loppuminen  
**Virhe:** `MemoryError` tai järjestelmän jäätyminen

**Ratkaisu:**  
1. **Raspberry Pi:**  
   - Sulje tarpeettomat sovellukset  
   - Lisää swap-tilaa  
   - Käytä kevyttä käyttöjärjestelmää (Lite-versio)  
   - Päivitä muisti (Pi 4:ssä 2/4/8 Gt vaihtoehdot)  
2. **Wio Terminal:**  
   - Pienennä puskurikokoja  
   - Käytä pienempiä kuvia  
   - Optimoi merkkijonojen käyttö  
   - Etsi muistivuotoja (vapautumattomia muisteja)  

### Ongelma: Tietojen menetys tai vioittuminen  
**Oireet:** Viestit puuttuvat, tiedostot vioittuneet

**Ratkaisu:**  
1. **SD-korttiongelmat:**  
   - Käytä laadukkaita SD-kortteja (vältä halpoja/väärennöksiä)  
   - Tee säännöllisiä varmuuskopioita  
   - Käynnistä laite puhtaasti (älä katkaise virtaa äkillisesti)  
2. **Puskuriylivuoto:** Kasvata puskureita koodissa  
3. **Verkon luotettavuus:** Toteuta uudelleenyritys- ja virheenkäsittelylogiikka  
4. **Palvelun laatu:** Käytä MQTT QoS 1 tai 2 tärkeitä viestejä varten  

---

## Yleiset virheilmoitukset

### `ModuleNotFoundError: No module named 'X'`  
**Syy:** Pakettia ei ole asennettu tai virtuaaliympäristö ei ole päällä

**Ratkaisu:**  
```bash
pip install X
```
Varmista, että virtuaaliympäristö on ensin aktivoitu.  

### `Permission denied` Linux/macOS -järjestelmissä  
**Syy:** Tarvitaan korotettuja oikeuksia tai tiedostolistaloikeusongelma

**Ratkaisu:**  
- Järjestelmätoiminnoissa käytä `sudo`  
- PIP:iä käytettäessä ÄLÄ käytä sudoa venvissä, aktivoi venv ensin  
- Sarjaporttia varten lisää käyttäjä dialout-ryhmään: `sudo usermod -a -G dialout $USER`, sitten ulos/loggaudu sisään  

### `OSError: [Errno 98] Address already in use`  
**Syy:** Portti on jo käytössä toisessa prosessissa

**Ratkaisu:**  
1. Etsi porttia käyttävä prosessi: `lsof -i :<port>` tai `netstat -ano | findstr :<port>`  
2. Lopeta prosessi tai käytä eri porttia koodissasi  

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Syy:** SSL-varmenteen tarkistus epäonnistui

**Ratkaisu:**  
1. Päivitä varmenteet: `pip install --upgrade certifi`  
2. Tarkista järjestelmän aika on oikein: `date`  
3. Vain kehityskäytössä (ei tuotannossa): Poista tarkistus käytöstä koodissa  

### `IndentationError: unexpected indent`  
**Syy:** Pythonin sisennysongelmat (välilehtien ja välilyöntien sekoitus)

**Ratkaisu:**  
1. Käytä yhtenäistä sisennystä (4 välilyöntiä on Pythonin standardi)  
2. Säädä editori käyttämään välilyöntejä tabulaattorien sijaan  
3. VS Code: Aseta `"editor.insertSpaces": true` ja `"editor.tabSize": 4`  

### `UnicodeDecodeError` tai `UnicodeEncodeError`  
**Syy:** Merkkikoodausongelmat

**Ratkaisu:**  
```python
# Tiedostoja luettaessa
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Tiedostoja kirjoitettaessa
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Avun hakeminen

Jos olet kokeillut näitä vianmääritysvaiheita ja sinulla on edelleen ongelmia:

### 1. Tarkista olemassa olevat resurssit  
- **Dokumentaatio:** Tutustu [README](README.md) -tiedostoon ja oppitunteihin  
- **Laitteisto-oppaat:** Katso [hardware.md](hardware.md) laitekohtaisia tietoja  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) Grove-komponenteille  

### 2. Etsi samankaltaisia ongelmia  
- **GitHub-ongelmat:** Etsi [olemassa olevia ongelmia](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Etsi virheilmoituksia  
- **Laitefoorumit:** Tarkista Raspberry Pi -foorumit tai Arduino-foorumit  

### 3. Luo GitHub-ongelma  
Jos et löydä ratkaisua:  
1. Mene [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Klikkaa "New Issue"  
3. Anna:  
   - Selkeä kuvaus ongelmasta  
   - Askeleet ongelman toistamiseen  
   - Virheilmoitukset (kokoteksti)  
   - Laitteisto-/ohjelmistoversiot  
   - Mitä olet jo kokeillut  
   - Kuvakaappaukset, jos tarpeen  

### 4. Liity yhteisöön  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)  

### 5. Toimita hyvät bugiraportit  
Hyvä bugiraportti sisältää:
- **Ympäristö:** Käyttöjärjestelmä, Python-versio, käytetty laitteisto  
- **Vaiheet ongelman toistamiseksi:** Tarkat vaiheet, jotka aiheuttavat ongelman  
- **Odotettu käyttäytyminen:** Mitä pitäisi tapahtua  
- **Todellinen käyttäytyminen:** Mitä todellisuudessa tapahtuu  
- **Virheilmoitukset:** Koko virheteksti, ei kuvakaappauksia  
- **Koodi:** Minimiesimerkki koodista, joka toistaa ongelman  

---

## Vinkkejä ennaltaehkäisyyn

### Yleiset parhaat käytännöt
1. **Pidä varmuuskopiot:** Säännölliset varmuuskopiot toimivista SD-korteista/koodista  
2. **Dokumentoi muutokset:** Merkitse kommentteihin, mikä toimii  
3. **Versiohallinta:** Käytä git:iä koodimuutosten seuraamiseen  
4. **Testaa inkrementaalisesti:** Testaa pieniä muutoksia ennen yhdistämistä  
5. **Lue virheilmoitukset:** Ne kertovat usein tarkalleen, mikä on vialla  
6. **Päivitä säännöllisesti:** Pidä ohjelmisto/laiteohjelmisto ajan tasalla  
7. **Käytä laadukkaita komponentteja:** Vältä halpoja kaapeleita/virtalähteitä  
8. **Vakaa virransyöttö:** Käytä sopivaa virtalähdettä (erityisesti Pi:n kohdalla)  

### Kehityksen työnkulku  
1. **Aloita yksinkertaisesti:** Käynnistä toimivasta esimerkkikoodista  
2. **Yksi muutos kerrallaan:** Helpompi löytää, mikä rikkoo toiminnan  
3. **Testaa usein:** Havaitse ongelmat ajoissa  
4. **Pidä siisti:** Järjestä tiedostot ja koodi loogisesti  
5. **Kommentoi koodi:** Tuleva sinä kiittää  

---

*Tätä vianmääritysohjetta ylläpitää yhteisö. Jos löydät ratkaisun ongelmaan, jota ei ole täällä listattu, harkitse [osallistumista](CONTRIBUTING.md) auttaaksesi muita!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Vastuuvapauslauseke**:
Tämä asiakirja on käännetty tekoälykäännöspalvelulla [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, otathan huomioon, että automaattikäännöksissä saattaa esiintyä virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäiskielellä tulee pitää lopullisena lähteenä. Tärkeiden tietojen osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa tämän käännöksen käytöstä aiheutuvista väärinymmärryksistä tai virhetulkinoista.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->