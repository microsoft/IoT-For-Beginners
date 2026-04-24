# Interagere med den fysiske verden med sensorer og aktuatorer

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-3.cc3b7b4cd646de59.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Leksjonen ble delt opp i to videoer - en én times leksjon og en én times kontortid der vi gikk dypere inn i deler av leksjonen og besvarte spørsmål.

[![Leksjon 3: Interagere med den fysiske verden med sensorer og aktuatorer](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Leksjon 3: Interagere med den fysiske verden med sensorer og aktuatorer - Kontortid](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klikk på bildene ovenfor for å se videoene

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Introduksjon

Denne leksjonen introduserer to viktige konsepter for IoT-enheten din - sensorer og aktuatorer. Du vil også få praktisk erfaring med begge, ved å legge til en lyssensor i IoT-prosjektet ditt, og deretter legge til en LED som styres av lysnivåer, og effektivt bygge en nattlampe.

I denne leksjonen dekker vi:

* [Hva er sensorer?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Bruke en sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sensor-typer](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Hva er aktuatorer?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Bruke en aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Aktuator-typer](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Hva er sensorer?

Sensorer er maskinvareenheter som registrerer den fysiske verden - det vil si at de måler én eller flere egenskaper rundt seg og sender informasjonen til en IoT-enhet. Sensorer dekker et enormt spekter av enheter, ettersom det er så mange ting som kan måles, fra naturlige egenskaper som lufttemperatur til fysiske interaksjoner som bevegelse.

Noen vanlige sensorer inkluderer:

* Temperatur-sensorer - disse registrerer lufttemperaturen eller temperaturen på det de er nedsenket i. For hobbyister og utviklere er disse ofte kombinert med lufttrykk og fuktighet i én enkelt sensor.
* Knapper - disse registrerer når de blir trykket.
* Lyssensorer - disse registrerer lysnivåer og kan være for spesifikke farger, UV-lys, IR-lys eller generelt synlig lys.
* Kameraer - disse registrerer en visuell representasjon av verden ved å ta et fotografi eller strømme video.
* Akselerometre - disse registrerer bevegelse i flere retninger.
* Mikrofoner - disse registrerer lyd, enten generelle lydnivåer eller retningsbestemt lyd.

✅ Gjør litt research. Hvilke sensorer har telefonen din?

Alle sensorer har én ting til felles - de konverterer det de registrerer til et elektrisk signal som kan tolkes av en IoT-enhet. Hvordan dette elektriske signalet tolkes avhenger av sensoren, samt kommunikasjonsprotokollen som brukes for å kommunisere med IoT-enheten.

## Bruke en sensor

Følg den relevante veiledningen nedenfor for å legge til en sensor i IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Enkeltkort-datamaskin - Raspberry Pi](pi-sensor.md)
* [Enkeltkort-datamaskin - Virtuell enhet](virtual-device-sensor.md)

## Sensor-typer

Sensorer er enten analoge eller digitale.

### Analoge sensorer

Noen av de mest grunnleggende sensorene er analoge sensorer. Disse sensorene mottar en spenning fra IoT-enheten, sensorens komponenter justerer denne spenningen, og spenningen som returneres fra sensoren måles for å gi sensorverdien.

> 🎓 Spenning er et mål på hvor mye kraft det er til å flytte elektrisitet fra ett sted til et annet, for eksempel fra den positive terminalen på et batteri til den negative terminalen. For eksempel er et standard AA-batteri 1,5V (V er symbolet for volt) og kan skyve elektrisitet med en kraft på 1,5V fra sin positive terminal til sin negative terminal. Ulike elektriske komponenter krever forskjellige spenninger for å fungere, for eksempel kan en LED lyse med mellom 2-3V, men en 100W glødelampe vil trenge 240V. Du kan lese mer om spenning på [Wikipedia-siden om spenning](https://wikipedia.org/wiki/Voltage).

Et eksempel på dette er en potensiometer. Dette er en dreieknapp som du kan rotere mellom to posisjoner, og sensoren måler rotasjonen.

![Et potensiometer satt til et midtpunkt som mottar 5 volt og returnerer 3,8 volt](../../../../../translated_images/no/potentiometer.35a348b9ce22f6ec.webp)

IoT-enheten sender et elektrisk signal til potensiometeret med en spenning, for eksempel 5 volt (5V). Når potensiometeret justeres, endrer det spenningen som kommer ut på den andre siden. Tenk deg at du har et potensiometer merket som en dreieknapp som går fra 0 til [11](https://wikipedia.org/wiki/Up_to_eleven), som en volumknapp på en forsterker. Når potensiometeret er i full av-posisjon (0), vil 0V (0 volt) komme ut. Når det er i full på-posisjon (11), vil 5V (5 volt) komme ut.

> 🎓 Dette er en forenkling, og du kan lese mer om potensiometre og variable motstander på [Wikipedia-siden om potensiometre](https://wikipedia.org/wiki/Potentiometer).

Spenningen som kommer ut av sensoren leses deretter av IoT-enheten, og enheten kan reagere på den. Avhengig av sensoren kan denne spenningen være en vilkårlig verdi eller kan kartlegges til en standard enhet. For eksempel endrer en analog temperatursensor basert på en [termistor](https://wikipedia.org/wiki/Thermistor) sin motstand avhengig av temperaturen. Utgangsspenningen kan deretter konverteres til en temperatur i Kelvin, og tilsvarende til °C eller °F, ved beregninger i kode.

✅ Hva tror du skjer hvis sensoren returnerer en høyere spenning enn det som ble sendt (for eksempel fra en ekstern strømkilde)? ⛔️ IKKE test dette.

#### Analog til digital konvertering

IoT-enheter er digitale - de kan ikke arbeide med analoge verdier, de fungerer kun med 0 og 1. Dette betyr at analoge sensorverdier må konverteres til et digitalt signal før de kan behandles. Mange IoT-enheter har analog-til-digital-konvertere (ADC-er) for å konvertere analoge innganger til digitale representasjoner av verdiene. Sensorer kan også fungere med ADC-er via en tilkoblingsplate. For eksempel, i Seeed Grove-økosystemet med en Raspberry Pi, kobles analoge sensorer til spesifikke porter på en 'hat' som sitter på Pi koblet til Pi's GPIO-pinner, og denne hatten har en ADC for å konvertere spenningen til et digitalt signal som kan sendes fra Pi's GPIO-pinner.

Tenk deg at du har en analog lyssensor koblet til en IoT-enhet som bruker 3,3V og returnerer en verdi på 1V. Denne 1V betyr ingenting i den digitale verden, så den må konverteres. Spenningen vil bli konvertert til en analog verdi ved hjelp av en skala avhengig av enheten og sensoren. Et eksempel er Seeed Grove-lyssensoren som gir verdier fra 0 til 1,023. For denne sensoren som kjører på 3,3V, vil en 1V-utgang være en verdi på 300. En IoT-enhet kan ikke håndtere 300 som en analog verdi, så verdien vil bli konvertert til `0000000100101100`, den binære representasjonen av 300 av Grove-hatten. Dette vil deretter bli behandlet av IoT-enheten.

✅ Hvis du ikke kjenner til binær, gjør litt research for å lære hvordan tall representeres med 0 og 1. [BBC Bitesize introduksjon til binær](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) er et flott sted å starte.

Fra et kodeperspektiv håndteres alt dette vanligvis av biblioteker som følger med sensorene, så du trenger ikke bekymre deg for denne konverteringen selv. For Grove-lyssensoren vil du bruke Python-biblioteket og kalle `light`-egenskapen, eller bruke Arduino-biblioteket og kalle `analogRead` for å få en verdi på 300.

### Digitale sensorer

Digitale sensorer, som analoge sensorer, registrerer verden rundt seg ved hjelp av endringer i elektrisk spenning. Forskjellen er at de gir et digitalt signal, enten ved kun å måle to tilstander eller ved å bruke en innebygd ADC. Digitale sensorer blir stadig mer vanlige for å unngå behovet for å bruke en ADC enten i en tilkoblingsplate eller på selve IoT-enheten.

Den enkleste digitale sensoren er en knapp eller bryter. Dette er en sensor med to tilstander, på eller av.

![En knapp mottar 5 volt. Når den ikke er trykket, returnerer den 0 volt, når den er trykket, returnerer den 5 volt](../../../../../translated_images/no/button.eadb560b77ac45e5.webp)

Pinner på IoT-enheter, som GPIO-pinner, kan måle dette signalet direkte som en 0 eller 1. Hvis spenningen som sendes er den samme som spenningen som returneres, leses verdien som 1, ellers leses verdien som 0. Det er ikke behov for å konvertere signalet, det kan bare være 1 eller 0.

> 💁 Spenninger er aldri helt nøyaktige, spesielt siden komponentene i en sensor vil ha noe motstand, så det er vanligvis en toleranse. For eksempel fungerer GPIO-pinnene på en Raspberry Pi på 3,3V, og leser et retur-signal over 1,8V som en 1, under 1,8V som 0.

* 3,3V går inn i knappen. Knappen er av, så 0V kommer ut, og gir en verdi på 0
* 3,3V går inn i knappen. Knappen er på, så 3,3V kommer ut, og gir en verdi på 1

Mer avanserte digitale sensorer leser analoge verdier, og konverterer dem deretter ved hjelp av innebygde ADC-er til digitale signaler. For eksempel vil en digital temperatursensor fortsatt bruke et termoelement på samme måte som en analog sensor, og vil fortsatt måle endringen i spenning forårsaket av motstanden i termoelementet ved den nåværende temperaturen. I stedet for å returnere en analog verdi og stole på enheten eller tilkoblingsplaten for å konvertere til et digitalt signal, vil en innebygd ADC konvertere verdien og sende den som en serie med 0 og 1 til IoT-enheten. Disse 0 og 1 sendes på samme måte som det digitale signalet for en knapp, der 1 er full spenning og 0 er 0V.

![En digital temperatursensor konverterer en analog avlesning til binære data med 0 som 0 volt og 1 som 5 volt før den sendes til en IoT-enhet](../../../../../translated_images/no/temperature-as-digital.85004491b977bae1.webp)

Å sende digitale data gjør det mulig for sensorer å bli mer komplekse og sende mer detaljerte data, til og med krypterte data for sikre sensorer. Et eksempel er et kamera. Dette er en sensor som fanger et bilde og sender det som digitale data som inneholder det bildet, vanligvis i et komprimert format som JPEG, for å bli lest av IoT-enheten. Det kan til og med strømme video ved å fange bilder og sende enten hele bildet ramme for ramme eller en komprimert videostrøm.

## Hva er aktuatorer?

Aktuatorer er det motsatte av sensorer - de konverterer et elektrisk signal fra IoT-enheten din til en interaksjon med den fysiske verden, som å sende ut lys eller lyd, eller bevege en motor.

Noen vanlige aktuatorer inkluderer:

* LED - disse sender ut lys når de er slått på
* Høyttaler - disse sender ut lyd basert på signalet som sendes til dem, fra en enkel buzzer til en lydhøyttaler som kan spille musikk
* Stepmotor - disse konverterer et signal til en definert mengde rotasjon, for eksempel å dreie en knapp 90°
* Relé - disse er brytere som kan slås på eller av med et elektrisk signal. De lar en liten spenning fra en IoT-enhet slå på større spenninger.
* Skjermer - disse er mer komplekse aktuatorer og viser informasjon på en multi-segment skjerm. Skjermer varierer fra enkle LED-skjermer til høyoppløselige videomonitorer.

✅ Gjør litt research. Hvilke aktuatorer har telefonen din?

## Bruke en aktuator

Følg den relevante veiledningen nedenfor for å legge til en aktuator i IoT-enheten din, kontrollert av sensoren, for å bygge en IoT-nattlampe. Den vil samle lysnivåer fra lyssensoren og bruke en aktuator i form av en LED til å sende ut lys når det registrerte lysnivået er for lavt.

![Et flytskjema for oppgaven som viser lysnivåer som leses og kontrolleres, og LED-en som styres](../../../../../translated_images/no/assignment-1-flow.7552a51acb1a5ec8.webp)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Enkeltkort-datamaskin - Raspberry Pi](pi-actuator.md)
* [Enkeltkort-datamaskin - Virtuell enhet](virtual-device-actuator.md)

## Aktuator-typer

Som sensorer, er aktuatorer enten analoge eller digitale.

### Analoge aktuatorer

Analoge aktuatorer tar et analogt signal og konverterer det til en form for interaksjon, der interaksjonen endres basert på spenningen som tilføres.

Et eksempel er en dimbar lampe, som de du kanskje har hjemme. Mengden spenning som tilføres lampen avgjør hvor sterkt den lyser.
![En lyspære dimmet ved lav spenning og lysere ved høyere spenning](../../../../../translated_images/no/dimmable-light.9ceffeb195dec1a8.webp)

Akkurat som med sensorer, fungerer den faktiske IoT-enheten med digitale signaler, ikke analoge. Dette betyr at for å sende et analogt signal, trenger IoT-enheten en digital-til-analog-omformer (DAC), enten direkte på IoT-enheten eller på et tilkoblingskort. Dette vil konvertere 0-ene og 1-ene fra IoT-enheten til en analog spenning som aktuatoren kan bruke.

✅ Hva tror du skjer hvis IoT-enheten sender en høyere spenning enn aktuatoren kan håndtere?  
⛔️ IKKE test dette ut.

#### Pulsbreddemodulasjon

En annen metode for å konvertere digitale signaler fra en IoT-enhet til et analogt signal er pulsbreddemodulasjon (PWM). Dette innebærer å sende mange korte digitale pulser som oppfører seg som et analogt signal.

For eksempel kan du bruke PWM til å kontrollere hastigheten på en motor.

Tenk deg at du styrer en motor med en 5V strømforsyning. Du sender en kort puls til motoren, som bytter spenningen til høy (5V) i to hundredels sekund (0,02s). I løpet av den tiden kan motoren rotere en tidel av en omdreining, eller 36°. Signalet pauser deretter i to hundredels sekund (0,02s), og sender et lavt signal (0V). Hver syklus av på og deretter av varer 0,04s. Syklusen gjentas deretter.

![Pulsbreddemodulasjon som roterer en motor ved 150 RPM](../../../../../translated_images/no/pwm-motor-150rpm.83347ac04ca38482.webp)

Dette betyr at du i løpet av ett sekund har 25 pulser på 5V som varer 0,02s og roterer motoren, hver etterfulgt av en pause på 0,02s med 0V som ikke roterer motoren. Hver puls roterer motoren en tidel av en omdreining, noe som betyr at motoren fullfører 2,5 omdreininger per sekund. Du har brukt et digitalt signal til å rotere motoren med 2,5 omdreininger per sekund, eller 150 [omdreininger per minutt](https://wikipedia.org/wiki/Revolutions_per_minute) (en ikke-standard måleenhet for rotasjonshastighet).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Når et PWM-signal er på halvparten av tiden og av halvparten av tiden, kalles det en [50% arbeidscyklus](https://wikipedia.org/wiki/Duty_cycle). Arbeidssykluser måles som prosentandelen av tiden signalet er i på-tilstand sammenlignet med av-tilstand.

![Pulsbreddemodulasjon som roterer en motor ved 75 RPM](../../../../../translated_images/no/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Du kan endre motorhastigheten ved å endre størrelsen på pulsene. For eksempel, med den samme motoren kan du beholde den samme syklustiden på 0,04s, men halvere på-pulsen til 0,01s og øke av-pulsen til 0,03s. Du har det samme antallet pulser per sekund (25), men hver på-puls er halvparten så lang. En halv lengde-puls roterer motoren bare en tjuendedel av en omdreining, og ved 25 pulser per sekund vil motoren fullføre 1,25 omdreininger per sekund eller 75 RPM. Ved å endre pulsens varighet i et digitalt signal har du halvert hastigheten på en analog motor.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Hvordan ville du holdt motorrotasjonen jevn, spesielt ved lave hastigheter? Ville du brukt et lite antall lange pulser med lange pauser eller mange veldig korte pulser med veldig korte pauser?

> 💁 Noen sensorer bruker også PWM for å konvertere analoge signaler til digitale signaler.

> 🎓 Du kan lese mer om pulsbreddemodulasjon på [Wikipedia-siden om pulsbreddemodulasjon](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitale aktuatorer

Digitale aktuatorer, som digitale sensorer, har enten to tilstander som styres av høy eller lav spenning, eller har en innebygd DAC som kan konvertere et digitalt signal til et analogt.

En enkel digital aktuator er en LED. Når en enhet sender et digitalt signal på 1, sendes en høy spenning som tenner LED-en. Når et digitalt signal på 0 sendes, faller spenningen til 0V, og LED-en slukkes.

![En LED er av ved 0 volt og på ved 5V](../../../../../translated_images/no/led.ec6d94f66676a174.webp)

✅ Hvilke andre enkle 2-tilstandsaktuatorer kan du komme på? Et eksempel er en solenoid, som er en elektromagnet som kan aktiveres for å gjøre ting som å flytte en dørlås for å låse/åpne en dør.

Mer avanserte digitale aktuatorer, som skjermer, krever at de digitale dataene sendes i bestemte formater. De kommer vanligvis med biblioteker som gjør det enklere å sende de riktige dataene for å kontrollere dem.

---

## 🚀 Utfordring

Utfordringen i de to siste leksjonene var å liste opp så mange IoT-enheter du kan finne i hjemmet, skolen eller på arbeidsplassen din, og avgjøre om de er bygget rundt mikrokontrollere eller enkortdatamaskiner, eller en blanding av begge.

For hver enhet du listet opp, hvilke sensorer og aktuatorer er de koblet til? Hva er formålet med hver sensor og aktuator som er koblet til disse enhetene?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Gjennomgang og selvstudium

* Les om elektrisitet og kretser på [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Les om de forskjellige typene temperatursensorer i [Seeed Studios guide til temperatursensorer](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/).  
* Les om LED-er på [Wikipedia-siden om LED](https://wikipedia.org/wiki/Light-emitting_diode).  

## Oppgave

[Undersøk sensorer og aktuatorer](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.