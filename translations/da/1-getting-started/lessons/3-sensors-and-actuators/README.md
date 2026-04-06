# Interager med den fysiske verden med sensorer og aktuatorer

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-3.cc3b7b4cd646de59.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne lektion blev undervist som en del af [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen blev præsenteret i 2 videoer - en 1-times lektion og en 1-times spørgetime, hvor dele af lektionen blev uddybet, og spørgsmål blev besvaret.

[![Lektion 3: Interager med den fysiske verden med sensorer og aktuatorer](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lektion 3: Interager med den fysiske verden med sensorer og aktuatorer - Spørgetime](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klik på billederne ovenfor for at se videoerne

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Introduktion

Denne lektion introducerer to vigtige begreber for din IoT-enhed - sensorer og aktuatorer. Du vil også få praktisk erfaring med begge dele, ved at tilføje en lyssensor til dit IoT-projekt og derefter tilføje en LED, der styres af lysniveauer, hvilket i praksis skaber en natlampe.

I denne lektion dækker vi:

* [Hvad er sensorer?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Brug en sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sensortyper](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Hvad er aktuatorer?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Brug en aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Aktuatortyper](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Hvad er sensorer?

Sensorer er hardwareenheder, der registrerer den fysiske verden - det vil sige, de måler en eller flere egenskaber omkring dem og sender informationen til en IoT-enhed. Sensorer dækker et enormt udvalg af enheder, da der er så mange ting, der kan måles, fra naturlige egenskaber som lufttemperatur til fysiske interaktioner som bevægelse.

Nogle almindelige sensorer inkluderer:

* Temperatursensorer - disse registrerer lufttemperaturen eller temperaturen på det, de er nedsænket i. For hobbyister og udviklere er disse ofte kombineret med lufttryk og fugtighed i en enkelt sensor.
* Knapper - disse registrerer, når de bliver trykket.
* Lyssensorer - disse registrerer lysniveauer og kan være specifikke for farver, UV-lys, IR-lys eller generelt synligt lys.
* Kameraer - disse registrerer en visuel repræsentation af verden ved at tage et fotografi eller streame video.
* Accelerometre - disse registrerer bevægelse i flere retninger.
* Mikrofoner - disse registrerer lyd, enten generelle lydniveauer eller retningsbestemt lyd.

✅ Lav lidt research. Hvilke sensorer har din telefon?

Alle sensorer har én ting til fælles - de konverterer det, de registrerer, til et elektrisk signal, som kan tolkes af en IoT-enhed. Hvordan dette elektriske signal tolkes afhænger af sensoren samt kommunikationsprotokollen, der bruges til at kommunikere med IoT-enheden.

## Brug en sensor

Følg den relevante vejledning nedenfor for at tilføje en sensor til din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Single-board computer - Raspberry Pi](pi-sensor.md)
* [Single-board computer - Virtuel enhed](virtual-device-sensor.md)

## Sensortyper

Sensorer er enten analoge eller digitale.

### Analoge sensorer

Nogle af de mest grundlæggende sensorer er analoge sensorer. Disse sensorer modtager en spænding fra IoT-enheden, sensorens komponenter justerer denne spænding, og spændingen, der returneres fra sensoren, måles for at give sensorværdien.

> 🎓 Spænding er et mål for, hvor meget kraft der er til at flytte elektricitet fra et sted til et andet, såsom fra den positive terminal på et batteri til den negative terminal. For eksempel er et standard AA-batteri 1,5V (V er symbolet for volt) og kan skubbe elektricitet med en kraft på 1,5V fra sin positive terminal til sin negative terminal. Forskellige elektriske hardware kræver forskellige spændinger for at fungere, for eksempel kan en LED lyse med mellem 2-3V, men en 100W glødepære ville kræve 240V. Du kan læse mere om spænding på [Wikipedia-siden om spænding](https://wikipedia.org/wiki/Voltage).

Et eksempel på dette er en potentiometer. Dette er en drejeknap, som du kan rotere mellem to positioner, og sensoren måler rotationen.

![En potentiometer indstillet til et midtpunkt, der modtager 5 volt og returnerer 3,8 volt](../../../../../translated_images/da/potentiometer.35a348b9ce22f6ec.webp)

IoT-enheden sender et elektrisk signal til potentiometeret med en spænding, såsom 5 volt (5V). Når potentiometeret justeres, ændrer det spændingen, der kommer ud på den anden side. Forestil dig, at du har en potentiometer mærket som en drejeknap, der går fra 0 til [11](https://wikipedia.org/wiki/Up_to_eleven), såsom en volumenknap på en forstærker. Når potentiometeret er i den fulde slukket position (0), vil 0V (0 volt) komme ud. Når det er i den fulde tændt position (11), vil 5V (5 volt) komme ud.

> 🎓 Dette er en forenkling, og du kan læse mere om potentiometre og variable modstande på [Wikipedia-siden om potentiometre](https://wikipedia.org/wiki/Potentiometer).

Spændingen, der kommer ud af sensoren, læses derefter af IoT-enheden, og enheden kan reagere på den. Afhængigt af sensoren kan denne spænding være en vilkårlig værdi eller kan kortlægges til en standardenhed. For eksempel ændrer en analog temperatursensor baseret på en [termistor](https://wikipedia.org/wiki/Thermistor) sin modstand afhængigt af temperaturen. Den udgående spænding kan derefter konverteres til en temperatur i Kelvin og tilsvarende til °C eller °F ved beregninger i kode.

✅ Hvad tror du sker, hvis sensoren returnerer en højere spænding, end der blev sendt (for eksempel fra en ekstern strømforsyning)? ⛔️ TEST IKKE dette.

#### Analog til digital konvertering

IoT-enheder er digitale - de kan ikke arbejde med analoge værdier, de arbejder kun med 0'er og 1'er. Dette betyder, at analoge sensorværdier skal konverteres til et digitalt signal, før de kan behandles. Mange IoT-enheder har analog-til-digital konvertere (ADCs) til at konvertere analoge input til digitale repræsentationer af deres værdi. Sensorer kan også arbejde med ADC'er via en forbindelsesplade. For eksempel i Seeed Grove-økosystemet med en Raspberry Pi, forbinder analoge sensorer til specifikke porte på en 'hat', der sidder på Pi'en forbundet til Pi'ens GPIO-pins, og denne hat har en ADC til at konvertere spændingen til et digitalt signal, der kan sendes fra Pi'ens GPIO-pins.

Forestil dig, at du har en analog lyssensor forbundet til en IoT-enhed, der bruger 3,3V og returnerer en værdi på 1V. Denne 1V betyder ikke noget i den digitale verden, så den skal konverteres. Spændingen vil blive konverteret til en analog værdi ved hjælp af en skala afhængigt af enheden og sensoren. Et eksempel er Seeed Grove-lyssensoren, som outputter værdier fra 0 til 1.023. For denne sensor, der kører ved 3,3V, ville en 1V output være en værdi på 300. En IoT-enhed kan ikke håndtere 300 som en analog værdi, så værdien ville blive konverteret til `0000000100101100`, den binære repræsentation af 300 af Grove-hatten. Dette ville derefter blive behandlet af IoT-enheden.

✅ Hvis du ikke kender binær, så lav lidt research for at lære, hvordan tal repræsenteres af 0'er og 1'er. [BBC Bitesize introduktion til binær](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) er et godt sted at starte.

Fra et kodningsperspektiv håndteres alt dette normalt af biblioteker, der følger med sensorerne, så du behøver ikke bekymre dig om denne konvertering selv. For Grove-lyssensoren ville du bruge Python-biblioteket og kalde `light`-egenskaben eller bruge Arduino-biblioteket og kalde `analogRead` for at få en værdi på 300.

### Digitale sensorer

Digitale sensorer, ligesom analoge sensorer, registrerer verden omkring dem ved hjælp af ændringer i elektrisk spænding. Forskellen er, at de outputter et digitalt signal, enten ved kun at måle to tilstande eller ved at bruge en indbygget ADC. Digitale sensorer bliver mere og mere almindelige for at undgå behovet for at bruge en ADC enten i en forbindelsesplade eller på selve IoT-enheden.

Den enkleste digitale sensor er en knap eller kontakt. Dette er en sensor med to tilstande, tændt eller slukket.

![En knap modtager 5 volt. Når den ikke er trykket, returnerer den 0 volt, når den er trykket, returnerer den 5 volt](../../../../../translated_images/da/button.eadb560b77ac45e5.webp)

Pins på IoT-enheder, såsom GPIO-pins, kan måle dette signal direkte som en 0 eller 1. Hvis den sendte spænding er den samme som den returnerede spænding, læses værdien som 1, ellers læses værdien som 0. Der er ingen grund til at konvertere signalet, det kan kun være 1 eller 0.

> 💁 Spændinger er aldrig helt præcise, især da komponenterne i en sensor vil have en vis modstand, så der er normalt en tolerance. For eksempel arbejder GPIO-pins på en Raspberry Pi med 3,3V og læser et returneret signal over 1,8V som en 1, under 1,8V som 0.

* 3,3V går ind i knappen. Knappen er slukket, så 0V kommer ud, hvilket giver en værdi på 0
* 3,3V går ind i knappen. Knappen er tændt, så 3,3V kommer ud, hvilket giver en værdi på 1

Mere avancerede digitale sensorer læser analoge værdier og konverterer dem derefter ved hjælp af indbyggede ADC'er til digitale signaler. For eksempel vil en digital temperatursensor stadig bruge et termoelement på samme måde som en analog sensor og stadig måle ændringen i spænding forårsaget af termoelementets modstand ved den aktuelle temperatur. I stedet for at returnere en analog værdi og stole på enheden eller forbindelsespladen til at konvertere til et digitalt signal, vil en indbygget ADC i sensoren konvertere værdien og sende den som en række 0'er og 1'er til IoT-enheden. Disse 0'er og 1'er sendes på samme måde som det digitale signal for en knap, hvor 1 er fuld spænding og 0 er 0V.

![En digital temperatursensor konverterer en analog aflæsning til binære data med 0 som 0 volt og 1 som 5 volt, før den sender det til en IoT-enhed](../../../../../translated_images/da/temperature-as-digital.85004491b977bae1.webp)

At sende digitale data gør det muligt for sensorer at blive mere komplekse og sende mere detaljerede data, endda krypterede data for sikre sensorer. Et eksempel er et kamera. Dette er en sensor, der fanger et billede og sender det som digitale data, der indeholder det billede, normalt i et komprimeret format som JPEG, til at blive læst af IoT-enheden. Det kan endda streame video ved at fange billeder og sende enten det komplette billede frame for frame eller en komprimeret videostream.

## Hvad er aktuatorer?

Aktuatorer er det modsatte af sensorer - de konverterer et elektrisk signal fra din IoT-enhed til en interaktion med den fysiske verden, såsom at udsende lys eller lyd eller bevæge en motor.

Nogle almindelige aktuatorer inkluderer:

* LED - disse udsender lys, når de tændes
* Højttaler - disse udsender lyd baseret på det signal, der sendes til dem, fra en simpel buzzer til en lydhøjttaler, der kan spille musik
* Steppermotor - disse konverterer et signal til en defineret mængde rotation, såsom at dreje en drejeknap 90°
* Relæ - disse er kontakter, der kan tændes eller slukkes af et elektrisk signal. De tillader en lille spænding fra en IoT-enhed at tænde større spændinger.
* Skærme - disse er mere komplekse aktuatorer og viser information på en multi-segment display. Skærme varierer fra simple LED-displays til højopløsnings videomonitorer.

✅ Lav lidt research. Hvilke aktuatorer har din telefon?

## Brug en aktuator

Følg den relevante vejledning nedenfor for at tilføje en aktuator til din IoT-enhed, styret af sensoren, for at bygge en IoT-natlampe. Den vil indsamle lysniveauer fra lyssensoren og bruge en aktuator i form af en LED til at udsende lys, når det registrerede lysniveau er for lavt.

![Et flowdiagram over opgaven, der viser lysniveauer, der bliver læst og kontrolleret, og LED'en bliver styret](../../../../../translated_images/da/assignment-1-flow.7552a51acb1a5ec8.webp)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Single-board computer - Raspberry Pi](pi-actuator.md)
* [Single-board computer - Virtuel enhed](virtual-device-actuator.md)

## Aktuatortyper

Ligesom sensorer er aktuatorer enten analoge eller digitale.

### Analoge aktuatorer

Analoge aktuatorer tager et analogt signal og konverterer det til en form for interaktion, hvor interaktionen ændrer sig baseret på den leverede spænding.

Et eksempel er en dæmpbar lampe, såsom dem du måske har i dit hjem. Mængden af spænding, der leveres til lampen, bestemmer, hvor lys den er.
![En lysdæmper ved lav spænding og lysere ved højere spænding](../../../../../translated_images/da/dimmable-light.9ceffeb195dec1a8.webp)

Ligesom med sensorer fungerer den faktiske IoT-enhed med digitale signaler, ikke analoge. Det betyder, at for at sende et analogt signal skal IoT-enheden have en digital-til-analog-konverter (DAC), enten direkte på IoT-enheden eller på et tilslutningskort. Dette konverterer 0'erne og 1'erne fra IoT-enheden til en analog spænding, som aktuatoren kan bruge.

✅ Hvad tror du der sker, hvis IoT-enheden sender en højere spænding, end aktuatoren kan håndtere?  
⛔️ PRØV IKKE at teste dette.

#### Pulsbreddemodulation

En anden mulighed for at konvertere digitale signaler fra en IoT-enhed til et analogt signal er pulsbreddemodulation. Dette indebærer at sende mange korte digitale impulser, der fungerer som et analogt signal.

For eksempel kan du bruge PWM til at kontrollere hastigheden på en motor.

Forestil dig, at du styrer en motor med en 5V strømforsyning. Du sender en kort impuls til din motor, hvor spændingen skifter til høj (5V) i to hundrededele af et sekund (0,02s). I den tid kan din motor rotere en tiendedel af en rotation, eller 36°. Signalet pauser derefter i to hundrededele af et sekund (0,02s), hvor der sendes et lavt signal (0V). Hver cyklus af tændt og slukket varer 0,04s. Cyklussen gentages derefter.

![Pulsbreddemodulation rotation af en motor ved 150 RPM](../../../../../translated_images/da/pwm-motor-150rpm.83347ac04ca38482.webp)

Dette betyder, at du på ét sekund har 25 5V impulser af 0,02s, der roterer motoren, hver efterfulgt af en pause på 0,02s med 0V, hvor motoren ikke roterer. Hver impuls roterer motoren en tiendedel af en rotation, hvilket betyder, at motoren fuldfører 2,5 rotationer per sekund. Du har brugt et digitalt signal til at rotere motoren med 2,5 rotationer per sekund, eller 150 [omdrejninger per minut](https://wikipedia.org/wiki/Revolutions_per_minute) (en ikke-standard måleenhed for rotationshastighed).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Når et PWM-signal er tændt halvdelen af tiden og slukket halvdelen af tiden, kaldes det en [50% duty cycle](https://wikipedia.org/wiki/Duty_cycle). Duty cycles måles som procentdelen af tiden, signalet er i tændt tilstand sammenlignet med slukket tilstand.

![Pulsbreddemodulation rotation af en motor ved 75 RPM](../../../../../translated_images/da/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Du kan ændre motorens hastighed ved at ændre størrelsen på impulserne. For eksempel kan du med den samme motor beholde den samme cyklustid på 0,04s, men halvere den tændte impuls til 0,01s og øge den slukkede impuls til 0,03s. Du har det samme antal impulser per sekund (25), men hver tændt impuls er halvt så lang. En halv længde impuls drejer kun motoren en tyvendedel af en rotation, og ved 25 impulser per sekund vil den fuldføre 1,25 rotationer per sekund eller 75rpm. Ved at ændre impulsens hastighed på et digitalt signal har du halveret hastigheden på en analog motor.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Hvordan ville du holde motorens rotation jævn, især ved lave hastigheder? Ville du bruge et lille antal lange impulser med lange pauser eller mange meget korte impulser med meget korte pauser?

> 💁 Nogle sensorer bruger også PWM til at konvertere analoge signaler til digitale signaler.

> 🎓 Du kan læse mere om pulsbreddemodulation på [pulsbreddemodulationssiden på Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitale aktuatorer

Digitale aktuatorer, ligesom digitale sensorer, har enten to tilstande, der styres af en høj eller lav spænding, eller har en indbygget DAC, der kan konvertere et digitalt signal til et analogt.

En simpel digital aktuator er en LED. Når en enhed sender et digitalt signal på 1, sendes en høj spænding, der tænder LED'en. Når et digitalt signal på 0 sendes, falder spændingen til 0V, og LED'en slukkes.

![En LED er slukket ved 0 volt og tændt ved 5V](../../../../../translated_images/da/led.ec6d94f66676a174.webp)

✅ Hvilke andre simple 2-tilstands aktuatorer kan du komme i tanke om? Et eksempel er en solenoid, som er en elektromagnet, der kan aktiveres til at gøre ting som at flytte en dørlås, der låser/oplåser en dør.

Mere avancerede digitale aktuatorer, såsom skærme, kræver, at de digitale data sendes i bestemte formater. De kommer normalt med biblioteker, der gør det lettere at sende de korrekte data til at styre dem.

---

## 🚀 Udfordring

Udfordringen i de sidste to lektioner var at liste så mange IoT-enheder som muligt, der findes i dit hjem, skole eller arbejdsplads, og afgøre, om de er bygget omkring mikrocontrollere eller single-board computere, eller endda en blanding af begge.

For hver enhed, du listede, hvilke sensorer og aktuatorer er de forbundet til? Hvad er formålet med hver sensor og aktuator, der er forbundet til disse enheder?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Gennemgang & Selvstudie

* Læs om elektricitet og kredsløb på [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Læs om de forskellige typer temperatursensorer på [Seeed Studios guide til temperatursensorer](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)  
* Læs om LED'er på [Wikipedia-siden om LED](https://wikipedia.org/wiki/Light-emitting_diode)  

## Opgave

[Undersøg sensorer og aktuatorer](assignment.md)  

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.