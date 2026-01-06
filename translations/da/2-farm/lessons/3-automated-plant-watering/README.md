<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-27T22:54:19+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "da"
}
-->
# Automatisk plantevanding

![En sketchnote oversigt over denne lektion](../../../../../translated_images/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.da.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne lektion blev undervist som en del af [IoT for Beginners Project 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![IoT-drevet automatisk plantevanding](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Introduktion

I den sidste lektion lærte du, hvordan man overvåger jordfugtighed. I denne lektion vil du lære at bygge de centrale komponenter i et automatisk vandingssystem, der reagerer på jordfugtighed. Du vil også lære om timing - hvordan sensorer kan tage tid om at reagere på ændringer, og hvordan aktuatorer kan tage tid om at ændre de egenskaber, der måles af sensorer.

I denne lektion vil vi dække:

* [Styr højstrømsenheder fra en lavstrøms IoT-enhed](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Styr en relæ](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Styr din plante via MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Sensor- og aktuator-timing](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Tilføj timing til din plantekontrolserver](../../../../../2-farm/lessons/3-automated-plant-watering)

## Styr højstrømsenheder fra en lavstrøms IoT-enhed

IoT-enheder bruger lav spænding. Selvom dette er nok til sensorer og lavstrømsaktuatorer som LED'er, er det for lavt til at styre større hardware, såsom en vandpumpe, der bruges til vanding. Selv små pumper, du kunne bruge til stueplanter, trækker for meget strøm til en IoT-udviklingskit og ville brænde printkortet af.

> 🎓 Strøm, målt i ampere (A), er mængden af elektricitet, der bevæger sig gennem et kredsløb. Spænding giver skubbet, strøm er hvor meget der skubbes. Du kan læse mere om strøm på [Wikipedia-siden om elektrisk strøm](https://wikipedia.org/wiki/Electric_current).

Løsningen på dette er at have en pumpe tilsluttet en ekstern strømforsyning og bruge en aktuator til at tænde pumpen, ligesom du ville tænde en lampe. Det kræver en lille mængde energi (i form af energi i din krop) for din finger at trykke på en kontakt, og dette forbinder lampen til elnettet, der kører på 110v/240v.

![En lyskontakt tænder strømmen til en lampe](../../../../../translated_images/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.da.png)

> 🎓 [Elnet](https://wikipedia.org/wiki/Mains_electricity) refererer til den elektricitet, der leveres til hjem og virksomheder gennem national infrastruktur i mange dele af verden.

✅ IoT-enheder kan normalt levere 3,3V eller 5V, med mindre end 1 ampere (1A) strøm. Sammenlign dette med elnettet, som oftest er på 230V (120V i Nordamerika og 100V i Japan) og kan levere strøm til enheder, der trækker 30A.

Der findes en række aktuatorer, der kan gøre dette, herunder mekaniske enheder, du kan fastgøre til eksisterende kontakter, der efterligner en finger, der tænder dem. Den mest populære er et relæ.

### Relæer

Et relæ er en elektromekanisk kontakt, der konverterer et elektrisk signal til en mekanisk bevægelse, der tænder en kontakt. Kernen i et relæ er en elektromagnet.

> 🎓 [Elektromagneter](https://wikipedia.org/wiki/Electromagnet) er magneter, der skabes ved at føre elektricitet gennem en spole af ledning. Når elektriciteten tændes, bliver spolen magnetiseret. Når elektriciteten slukkes, mister spolen sin magnetisme.

![Når tændt, skaber elektromagneten et magnetfelt, der tænder kontakten for udgangskredsløbet](../../../../../translated_images/relay-on.4db16a0fd6b66926.da.png)

I et relæ driver et kontrolkredsløb elektromagneten. Når elektromagneten er tændt, trækker den en arm, der bevæger en kontakt, lukker et par kontakter og fuldender et udgangskredsløb.

![Når slukket, skaber elektromagneten ikke et magnetfelt, der slukker kontakten for udgangskredsløbet](../../../../../translated_images/relay-off.c34a178a2960fecd.da.png)

Når kontrolkredsløbet er slukket, slukkes elektromagneten, frigiver armen og åbner kontakterne, hvilket slukker udgangskredsløbet. Relæer er digitale aktuatorer - et højt signal til relæet tænder det, et lavt signal slukker det.

Udgangskredsløbet kan bruges til at drive ekstra hardware, såsom et vandingssystem. IoT-enheden kan tænde relæet, fuldende udgangskredsløbet, der driver vandingssystemet, og planterne bliver vandet. IoT-enheden kan derefter slukke relæet, afbryde strømmen til vandingssystemet og slukke for vandet.

![Et relæ, der tænder en pumpe, der sender vand til en plante](../../../../../images/strawberry-pump.gif)

I videoen ovenfor tændes et relæ. En LED på relæet lyser op for at indikere, at det er tændt (nogle relæboards har LED'er til at indikere, om relæet er tændt eller slukket), og strøm sendes til pumpen, som tænder og pumper vand til en plante.

> 💁 Relæer kan også bruges til at skifte mellem to udgangskredsløb i stedet for at tænde og slukke for et. Når armen bevæger sig, flytter den en kontakt fra at fuldende et udgangskredsløb til at fuldende et andet udgangskredsløb, normalt med en fælles strømforbindelse eller fælles jordforbindelse.

✅ Undersøg: Der findes flere typer relæer med forskelle såsom om kontrolkredsløbet tænder eller slukker relæet, når strøm tilføres, eller flere udgangskredsløb. Find ud af mere om disse forskellige typer.

Når armen bevæger sig, kan du normalt høre den lave kontakt med elektromagneten med en veldefineret kliklyd.

> 💁 Et relæ kan forbindes, så det at lave forbindelsen faktisk afbryder strømmen til relæet, hvilket slukker relæet, som derefter sender strøm til relæet og tænder det igen, og så videre. Dette betyder, at relæet vil klikke utroligt hurtigt og lave en summende lyd. Sådan fungerede nogle af de første summer, der blev brugt i elektriske dørklokker.

### Relæstrøm

Elektromagneten behøver ikke meget strøm for at aktivere og trække armen; den kan styres med 3,3V eller 5V output fra en IoT-udviklingskit. Udgangskredsløbet kan bære meget mere strøm, afhængigt af relæet, inklusive elnetspænding eller endda højere strømniveauer til industriel brug. På denne måde kan en IoT-udviklingskit styre et vandingssystem, fra en lille pumpe til en enkelt plante, op til et massivt industrielt system til en hel kommerciel gård.

![Et Grove-relæ med kontrolkredsløb, udgangskredsløb og relæ mærket](../../../../../translated_images/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.da.png)

Billedet ovenfor viser et Grove-relæ. Kontrolkredsløbet forbinder til en IoT-enhed og tænder eller slukker relæet ved hjælp af 3,3V eller 5V. Udgangskredsløbet har to terminaler, hvoraf en kan være strøm eller jord. Udgangskredsløbet kan håndtere op til 250V ved 10A, nok til en række enheder, der drives af elnettet. Du kan få relæer, der kan håndtere endnu højere strømniveauer.

![En pumpe forbundet via et relæ](../../../../../translated_images/pump-wired-to-relay.66c5cfc0d8918990.da.png)

I billedet ovenfor leveres strøm til en pumpe via et relæ. Der er en rød ledning, der forbinder +5V-terminalen på en USB-strømforsyning til en terminal på relæets udgangskredsløb, og en anden rød ledning, der forbinder den anden terminal på udgangskredsløbet til pumpen. En sort ledning forbinder pumpen til jord på USB-strømforsyningen. Når relæet tændes, fuldender det kredsløbet, sender 5V til pumpen og tænder pumpen.

## Styr et relæ

Du kan styre et relæ fra din IoT-udviklingskit.

### Opgave - styr et relæ

Følg den relevante vejledning for at styre et relæ ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Single-board computer - Raspberry Pi](pi-relay.md)
* [Single-board computer - Virtuel enhed](virtual-device-relay.md)

## Styr din plante via MQTT

Indtil videre er dit relæ styret direkte af IoT-enheden baseret på en enkelt jordfugtighedsmåling. I et kommercielt vandingssystem vil kontrollogikken være centraliseret, så den kan træffe beslutninger om vanding ved hjælp af data fra flere sensorer og tillade, at enhver konfiguration ændres ét sted. For at simulere dette kan du styre relæet via MQTT.

### Opgave - styr relæet via MQTT

1. Tilføj de relevante MQTT-biblioteker/pip-pakker og kode til dit `soil-moisture-sensor`-projekt for at oprette forbindelse til MQTT. Navngiv klient-ID'et som `soilmoisturesensor_client` med dit ID som præfiks.

    > ⚠️ Du kan henvise til [instruktionerne for at oprette forbindelse til MQTT i projekt 1, lektion 4, hvis nødvendigt](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Tilføj den relevante enhedskode for at sende telemetri med jordfugtighedsindstillingerne. For telemetribeskeden skal du navngive egenskaben `soil_moisture`.

    > ⚠️ Du kan henvise til [instruktionerne for at sende telemetri til MQTT i projekt 1, lektion 4, hvis nødvendigt](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Opret noget lokal serverkode for at abonnere på telemetri og sende en kommando for at styre relæet i en mappe kaldet `soil-moisture-sensor-server`. Navngiv egenskaben i kommandobeskeden `relay_on`, og sæt klient-ID'et som `soilmoisturesensor_server` med dit ID som præfiks. Behold samme struktur som serverkoden, du skrev til projekt 1, lektion 4, da du vil tilføje til denne kode senere i lektionen.

    > ⚠️ Du kan henvise til [instruktionerne for at sende telemetri til MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) og [sende kommandoer via MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) i projekt 1, lektion 4, hvis nødvendigt.

1. Tilføj den relevante enhedskode for at styre relæet fra modtagne kommandoer ved hjælp af egenskaben `relay_on` fra beskeden. Send true for `relay_on`, hvis `soil_moisture` er større end 450, ellers send false, samme logik som du tilføjede til IoT-enheden tidligere.

    > ⚠️ Du kan henvise til [instruktionerne for at reagere på kommandoer fra MQTT i projekt 1, lektion 4, hvis nødvendigt](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Du kan finde denne kode i [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt)-mappen.

Sørg for, at koden kører på din enhed og lokale server, og test den ved at ændre jordfugtighedsniveauer, enten ved at ændre de værdier, der sendes af den virtuelle sensor, eller ved at ændre jordens fugtighedsniveauer ved at tilføje vand eller fjerne sensoren fra jorden.

## Sensor- og aktuator-timing

Tilbage i lektion 3 byggede du en natlampe - en LED, der tænder, så snart et lavt lysniveau blev registreret af en lyssensor. Lyssensoren registrerede en ændring i lysniveauer øjeblikkeligt, og enheden kunne reagere hurtigt, kun begrænset af længden af forsinkelsen i `loop`-funktionen eller `while True:`-løkken. Som IoT-udvikler kan du ikke altid stole på en så hurtig feedback-loop.

### Timing for jordfugtighed

Hvis du lavede den sidste lektion om jordfugtighed med en fysisk sensor, ville du have bemærket, at det tog et par sekunder for jordfugtighedsmålingen at falde, efter du vandede din plante. Dette skyldes ikke, at sensoren er langsom, men fordi det tager tid for vand at trænge igennem jorden.
💁 Hvis du vandede for tæt på sensoren, har du måske set aflæsningen falde hurtigt og derefter stige igen - dette skyldes, at vandet nær sensoren spreder sig i resten af jorden, hvilket reducerer jordfugtigheden omkring sensoren.
![En måling af jordfugtighed på 658 ændrer sig ikke under vanding, den falder først til 320 efter vanding, når vandet er trængt igennem jorden](../../../../../translated_images/soil-moisture-travel.a0e31af222cf1438.da.png)

I diagrammet ovenfor viser en måling af jordfugtighed 658. Planten bliver vandet, men denne måling ændrer sig ikke med det samme, da vandet endnu ikke har nået sensoren. Vanding kan endda afsluttes, før vandet når sensoren, og værdien falder for at afspejle det nye fugtighedsniveau.

Hvis du skulle skrive kode til at styre et vandingssystem via et relæ baseret på jordfugtighedsniveauer, ville du være nødt til at tage denne forsinkelse i betragtning og indbygge smartere timing i din IoT-enhed.

✅ Tag et øjeblik til at overveje, hvordan du kunne gøre dette.

### Styring af sensor- og aktuator-timing

Forestil dig, at du har fået til opgave at bygge et vandingssystem til en gård. Baseret på jordtypen er det ideelle jordfugtighedsniveau for de dyrkede planter blevet fastsat til at matche en analog spændingsmåling på 400-450.

Du kunne programmere enheden på samme måde som natlampen - så længe sensoren viser over 450, tænd et relæ for at aktivere en pumpe. Problemet er, at det tager tid for vandet at bevæge sig fra pumpen, gennem jorden og til sensoren. Sensoren vil stoppe vandet, når den registrerer et niveau på 450, men vandniveauet vil fortsætte med at falde, da det pumpede vand fortsætter med at trænge igennem jorden. Det endelige resultat er spildt vand og risiko for rodskader.

✅ Husk - for meget vand kan være lige så skadeligt for planter som for lidt, og det spilder en værdifuld ressource.

Den bedre løsning er at forstå, at der er en forsinkelse mellem aktuatoren, der tændes, og den egenskab, som sensoren måler, ændrer sig. Det betyder, at sensoren ikke kun skal vente et stykke tid, før den måler værdien igen, men aktuatoren skal også slukkes i et stykke tid, før den næste måling foretages.

Hvor længe skal relæet være tændt hver gang? Det er bedre at være forsigtig og kun tænde relæet i kort tid, derefter vente på, at vandet trænger igennem, og så genkontrollere fugtighedsniveauerne. Når alt kommer til alt, kan du altid tænde det igen for at tilføje mere vand, men du kan ikke fjerne vand fra jorden.

> 💁 Denne form for timingkontrol er meget specifik for den IoT-enhed, du bygger, den egenskab, du måler, og de sensorer og aktuatorer, der bruges.

![En jordbærplante forbundet til vand via en pumpe, hvor pumpen er forbundet til et relæ. Relæet og en jordfugtighedssensor i planten er begge forbundet til en Raspberry Pi](../../../../../translated_images/strawberry-with-pump.b410fc72ac6aabad.da.png)

For eksempel har jeg en jordbærplante med en jordfugtighedssensor og en pumpe, der styres af et relæ. Jeg har observeret, at når jeg tilføjer vand, tager det cirka 20 sekunder, før målingen af jordfugtighed stabiliserer sig. Det betyder, at jeg skal slukke relæet og vente 20 sekunder, før jeg kontrollerer fugtighedsniveauerne. Jeg vil hellere have for lidt vand end for meget - jeg kan altid tænde pumpen igen, men jeg kan ikke fjerne vand fra planten.

![Trin 1, tag måling. Trin 2, tilføj vand. Trin 3, vent på, at vandet trænger igennem jorden. Trin 4, tag måling igen](../../../../../translated_images/soil-moisture-delay.865f3fae206db01d.da.png)

Det betyder, at den bedste proces ville være en vandingscyklus, der ser sådan ud:

* Tænd pumpen i 5 sekunder
* Vent 20 sekunder
* Kontroller jordfugtigheden
* Hvis niveauet stadig er over det ønskede, gentag ovenstående trin

5 sekunder kan være for lang tid for pumpen, især hvis fugtighedsniveauerne kun er lidt over det krævede niveau. Den bedste måde at finde ud af, hvilken timing der skal bruges, er at prøve det og derefter justere, når du har sensordata, med en konstant feedback-loop. Dette kan endda føre til mere granulær timing, såsom at tænde pumpen i 1 sekund for hver 100 over det krævede jordfugtighedsniveau i stedet for faste 5 sekunder.

✅ Undersøg: Er der andre timingovervejelser? Kan planten vandes når som helst, hvis jordfugtigheden er for lav, eller er der specifikke tidspunkter på dagen, der er gode og dårlige til at vande planter?

> 💁 Vejrprognoser kan også tages i betragtning, når man styrer automatiske vandingssystemer til udendørs dyrkning. Hvis der forventes regn, kan vandingen sættes på pause, indtil regnen er overstået. På det tidspunkt kan jorden være fugtig nok til, at den ikke behøver vanding, hvilket er meget mere effektivt end at spilde vand ved at vande lige før regnen.

## Tilføj timing til din plantekontrolserver

Serverkoden kan ændres for at tilføje kontrol omkring timingen af vandingscyklussen og vente på, at jordfugtighedsniveauerne ændrer sig. Serverlogikken for styring af relætiming er:

1. Telemetrimeddelelse modtaget
1. Kontroller jordfugtighedsniveauet
1. Hvis det er ok, gør ingenting. Hvis målingen er for høj (hvilket betyder, at jordfugtigheden er for lav), så:
    1. Send en kommando for at tænde relæet
    1. Vent i 5 sekunder
    1. Send en kommando for at slukke relæet
    1. Vent i 20 sekunder, så jordfugtighedsniveauerne kan stabilisere sig

Vandingscyklussen, processen fra modtagelse af telemetrimeddelelse til at være klar til at behandle jordfugtighedsniveauer igen, tager cirka 25 sekunder. Vi sender jordfugtighedsniveauer hvert 10. sekund, så der er et overlap, hvor en meddelelse modtages, mens serveren venter på, at jordfugtighedsniveauerne stabiliserer sig, hvilket kunne starte en ny vandingscyklus.

Der er to muligheder for at omgå dette:

* Ændre IoT-enhedens kode til kun at sende telemetri hvert minut, så vandingscyklussen er afsluttet, før den næste meddelelse sendes
* Afmelde telemetri under vandingscyklussen

Den første mulighed er ikke altid en god løsning for store gårde. Landmanden vil måske gerne registrere jordfugtighedsniveauerne, mens jorden vandes, til senere analyse, for eksempel for at være opmærksom på vandstrømmen i forskellige områder på gården for at guide mere målrettet vanding. Den anden mulighed er bedre - koden ignorerer bare telemetri, når den ikke kan bruge den, men telemetrien er stadig tilgængelig for andre tjenester, der måske abonnerer på den.

> 💁 IoT-data sendes ikke kun fra én enhed til én tjeneste, i stedet kan mange enheder sende data til en broker, og mange tjenester kan lytte til dataene fra brokeren. For eksempel kan én tjeneste lytte til jordfugtighedsdata og gemme dem i en database til analyse på et senere tidspunkt. En anden tjeneste kan også lytte til den samme telemetri for at styre et vandingssystem.

### Opgave - tilføj timing til din plantekontrolserver

Opdater din serverkode til at køre relæet i 5 sekunder og derefter vente 20 sekunder.

1. Åbn mappen `soil-moisture-sensor-server` i VS Code, hvis den ikke allerede er åben. Sørg for, at det virtuelle miljø er aktiveret.

1. Åbn filen `app.py`

1. Tilføj følgende kode til filen `app.py` under de eksisterende imports:

    ```python
    import threading
    ```

    Denne erklæring importerer `threading` fra Python-bibliotekerne. Threading gør det muligt for Python at udføre anden kode, mens den venter.

1. Tilføj følgende kode før funktionen `handle_telemetry`, der håndterer telemetrimeddelelser modtaget af serverkoden:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Dette definerer, hvor længe relæet skal køre (`water_time`), og hvor længe der skal ventes bagefter for at kontrollere jordfugtigheden (`wait_time`).

1. Under denne kode skal du tilføje følgende:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Denne kode definerer en funktion kaldet `send_relay_command`, der sender en kommando over MQTT for at styre relæet. Telemetrien oprettes som en ordbog og konverteres derefter til en JSON-streng. Værdien, der sendes til `state`, bestemmer, om relæet skal være tændt eller slukket.

1. Efter funktionen `send_relay_code` skal du tilføje følgende kode:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Dette definerer en funktion til at styre relæet baseret på den krævede timing. Den starter med at afmelde telemetri, så jordfugtighedsmeddelelser ikke behandles, mens vandingen foregår. Derefter sender den en kommando for at tænde relæet. Den venter derefter i `water_time`, før den sender en kommando for at slukke relæet. Til sidst venter den i `wait_time` sekunder, så jordfugtighedsniveauerne kan stabilisere sig. Den genabonnerer derefter på telemetri.

1. Ændr funktionen `handle_telemetry` til følgende:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Denne kode kontrollerer jordfugtighedsniveauet. Hvis det er større end 450, har jorden brug for vanding, så den kalder funktionen `control_relay`. Denne funktion køres på en separat tråd, der kører i baggrunden.

1. Sørg for, at din IoT-enhed kører, og kør derefter denne kode. Ændr jordfugtighedsniveauerne og observer, hvad der sker med relæet - det skulle tænde i 5 sekunder og derefter forblive slukket i mindst 20 sekunder, kun tænde igen, hvis jordfugtighedsniveauerne ikke er tilstrækkelige.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    En god måde at teste dette i et simuleret vandingssystem er at bruge tør jord og derefter hælde vand i manuelt, mens relæet er tændt, og stoppe med at hælde, når relæet slukker.

> 💁 Du kan finde denne kode i mappen [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Hvis du vil bruge en pumpe til at bygge et rigtigt vandingssystem, kan du bruge en [6V vandpumpe](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) med en [USB-terminal strømforsyning](https://www.adafruit.com/product/3628). Sørg for, at strømmen til eller fra pumpen er forbundet via relæet.

---

## 🚀 Udfordring

Kan du komme i tanke om andre IoT- eller elektriske enheder, der har et lignende problem, hvor det tager tid, før resultaterne af aktuatoren når sensoren? Du har sandsynligvis et par stykker i dit hus eller din skole.

* Hvilke egenskaber måler de?
* Hvor lang tid tager det for egenskaben at ændre sig, efter en aktuator er brugt?
* Er det ok, at egenskaben ændrer sig forbi det ønskede niveau?
* Hvordan kan den bringes tilbage til det ønskede niveau, hvis det er nødvendigt?

## Quiz efter forelæsning

[Quiz efter forelæsning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Gennemgang & Selvstudie

* Læs mere om relæer, inklusive deres historiske brug i telefoncentraler, på [relæ Wikipedia-siden](https://wikipedia.org/wiki/Relay).

## Opgave

[Byg en mere effektiv vandingscyklus](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.