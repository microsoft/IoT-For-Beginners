# Automatisk plantevanning

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-7.30b5f577d3cb8e03.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [IoT for Beginners Prosjekt 2 - Digital Agriculture-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![IoT-drevet automatisk plantevanning](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Introduksjon

I forrige leksjon lærte du hvordan du overvåker jordfuktighet. I denne leksjonen vil du lære hvordan du bygger de grunnleggende komponentene i et automatisk vanningssystem som reagerer på jordfuktighet. Du vil også lære om timing – hvordan sensorer kan bruke tid på å reagere på endringer, og hvordan aktuatorer kan bruke tid på å endre egenskapene som måles av sensorer.

I denne leksjonen dekker vi:

* [Kontrollere høystrømsenheter fra en lavstrøms IoT-enhet](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Kontrollere et relé](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Kontrollere planten din via MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Sensor- og aktuator-timing](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Legge til timing i plantekontrollserveren din](../../../../../2-farm/lessons/3-automated-plant-watering)

## Kontrollere høystrømsenheter fra en lavstrøms IoT-enhet

IoT-enheter bruker lav spenning. Selv om dette er nok for sensorer og lavstrømsaktuatorer som LED-lys, er det for lavt til å kontrollere større maskinvare, som en vannpumpe brukt til vanning. Selv små pumper som kan brukes til potteplanter trekker for mye strøm for et IoT-utviklingskort og kan skade kortet.

> 🎓 Strøm, målt i ampere (A), er mengden elektrisitet som beveger seg gjennom en krets. Spenning gir "dyttet", mens strøm er hvor mye som blir dyttet. Du kan lese mer om strøm på [Wikipedia-siden om elektrisk strøm](https://wikipedia.org/wiki/Electric_current).

Løsningen på dette er å ha en pumpe koblet til en ekstern strømkilde og bruke en aktuator til å slå på pumpen, på samme måte som du ville slått på et lys. Det krever en liten mengde energi (i form av energi i kroppen din) for fingeren din å trykke på en bryter, og dette kobler lyset til strømnettet som kjører på 110v/240v.

![En lysbryter slår på strømmen til et lys](../../../../../translated_images/no/light-switch.760317ad6ab8bd6d.webp)

> 🎓 [Strømnett](https://wikipedia.org/wiki/Mains_electricity) refererer til elektrisiteten som leveres til hjem og bedrifter gjennom nasjonal infrastruktur i mange deler av verden.

✅ IoT-enheter kan vanligvis levere 3,3V eller 5V, med mindre enn 1 ampere (1A) strøm. Sammenlign dette med strømnettet som oftest er på 230V (120V i Nord-Amerika og 100V i Japan), og kan levere strøm til enheter som trekker 30A.

Det finnes en rekke aktuatorer som kan gjøre dette, inkludert mekaniske enheter som kan festes til eksisterende brytere og etterligne en finger som slår dem på. Den mest populære er et relé.

### Reléer

Et relé er en elektromekanisk bryter som konverterer et elektrisk signal til en mekanisk bevegelse som slår på en bryter. Kjernen i et relé er en elektromagnet.

> 🎓 [Elektromagneter](https://wikipedia.org/wiki/Electromagnet) er magneter som skapes ved å sende elektrisitet gjennom en spole av ledning. Når elektrisiteten er slått på, blir spolen magnetisert. Når elektrisiteten er slått av, mister spolen magnetismen.

![Når på, skaper elektromagneten et magnetfelt som slår på bryteren for utgangskretsen](../../../../../translated_images/no/relay-on.4db16a0fd6b66926.webp)

I et relé driver en kontrollkrets elektromagneten. Når elektromagneten er på, trekker den en spak som beveger en bryter, lukker et par kontakter og fullfører en utgangskrets.

![Når av, skaper ikke elektromagneten et magnetfelt, og bryteren for utgangskretsen er slått av](../../../../../translated_images/no/relay-off.c34a178a2960fecd.webp)

Når kontrollkretsen er av, slår elektromagneten seg av, slipper spaken og åpner kontaktene, og slår av utgangskretsen. Reléer er digitale aktuatorer – et høyt signal til reléet slår det på, et lavt signal slår det av.

Utgangskretsen kan brukes til å drive ekstra maskinvare, som et vanningssystem. IoT-enheten kan slå reléet på, fullføre utgangskretsen som driver vanningssystemet, og plantene får vann. IoT-enheten kan deretter slå reléet av, kutte strømmen til vanningssystemet og slå av vannet.

![Et relé som slår på, slår på en pumpe som sender vann til en plante](../../../../../images/strawberry-pump.gif)

I videoen ovenfor blir et relé slått på. En LED på reléet lyser opp for å indikere at det er på (noen relékort har LED-lys for å indikere om reléet er på eller av), og strøm sendes til pumpen, som slår seg på og pumper vann til en plante.

> 💁 Reléer kan også brukes til å bytte mellom to utgangskretser i stedet for å slå én av og på. Når spaken beveger seg, flytter den en bryter fra å fullføre én utgangskrets til å fullføre en annen utgangskrets, vanligvis med en felles strømtilkobling eller felles jordtilkobling.

✅ Gjør litt research: Det finnes flere typer reléer, med forskjeller som om kontrollkretsen slår reléet på eller av når strøm tilføres, eller flere utgangskretser. Finn ut mer om disse forskjellige typene.

Når spaken beveger seg, kan du vanligvis høre den lage kontakt med elektromagneten med et tydelig klikk.

> 💁 Et relé kan kobles slik at det å lage forbindelsen faktisk bryter strømmen til reléet, slår reléet av, som deretter sender strøm til reléet og slår det på igjen, og så videre. Dette betyr at reléet vil klikke utrolig raskt og lage en summende lyd. Dette er hvordan noen av de første summerne brukt i elektriske dørklokker fungerte.

### Reléstrøm

Elektromagneten trenger ikke mye strøm for å aktivere og trekke spaken, den kan kontrolleres med 3,3V eller 5V utgang fra et IoT-utviklingskort. Utgangskretsen kan bære mye mer strøm, avhengig av reléet, inkludert strømnettspenning eller enda høyere strømnivåer for industriell bruk. På denne måten kan et IoT-utviklingskort kontrollere et vanningssystem, fra en liten pumpe for en enkelt plante, til et massivt industrielt system for en hel kommersiell gård.

![Et Grove-relé med kontrollkrets, utgangskrets og relé merket](../../../../../translated_images/no/grove-relay-labelled.293e068f5c3c2a19.webp)

Bildet ovenfor viser et Grove-relé. Kontrollkretsen kobles til en IoT-enhet og slår reléet av eller på med 3,3V eller 5V. Utgangskretsen har to terminaler, hvorav en kan være strøm eller jord. Utgangskretsen kan håndtere opptil 250V ved 10A, nok for en rekke enheter som drives av strømnettet. Du kan få reléer som kan håndtere enda høyere strømnivåer.

![En pumpe koblet via et relé](../../../../../translated_images/no/pump-wired-to-relay.66c5cfc0d8918990.webp)

I bildet ovenfor leveres strøm til en pumpe via et relé. Det er en rød ledning som kobler +5V-terminalen på en USB-strømkilde til én terminal på utgangskretsen til reléet, og en annen rød ledning som kobler den andre terminalen på utgangskretsen til pumpen. En svart ledning kobler pumpen til jord på USB-strømkilden. Når reléet slår seg på, fullfører det kretsen, sender 5V til pumpen og slår pumpen på.

## Kontrollere et relé

Du kan kontrollere et relé fra IoT-utviklingskortet ditt.

### Oppgave - kontrollere et relé

Følg den relevante veiledningen for å kontrollere et relé med IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi-relay.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device-relay.md)

## Kontrollere planten din via MQTT

Så langt har reléet ditt blitt kontrollert direkte av IoT-enheten basert på én enkelt jordfuktighetsmåling. I et kommersielt vanningssystem vil kontrolllogikken være sentralisert, slik at den kan ta beslutninger om vanning basert på data fra flere sensorer, og tillate at eventuelle konfigurasjoner endres på ett sted. For å simulere dette kan du kontrollere reléet via MQTT.

### Oppgave - kontrollere reléet via MQTT

1. Legg til de relevante MQTT-bibliotekene/pip-pakkene og kode til `soil-moisture-sensor`-prosjektet ditt for å koble til MQTT. Navngi klient-ID-en som `soilmoisturesensor_client` med ID-en din som prefiks.

    > ⚠️ Du kan referere til [instruksjonene for å koble til MQTT i prosjekt 1, leksjon 4 hvis nødvendig](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Legg til den relevante enhetskoden for å sende telemetri med jordfuktighetsinnstillingene. For telemetrimeldingen, navngi egenskapen `soil_moisture`.

    > ⚠️ Du kan referere til [instruksjonene for å sende telemetri til MQTT i prosjekt 1, leksjon 4 hvis nødvendig](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Lag lokal serverkode for å abonnere på telemetri og sende en kommando for å kontrollere reléet i en mappe kalt `soil-moisture-sensor-server`. Navngi egenskapen i kommandomeldingen `relay_on`, og sett klient-ID-en som `soilmoisturesensor_server` med ID-en din som prefiks. Hold samme struktur som serverkoden du skrev for prosjekt 1, leksjon 4, da du vil legge til denne koden senere i denne leksjonen.

    > ⚠️ Du kan referere til [instruksjonene for å sende telemetri til MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) og [sende kommandoer via MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) i prosjekt 1, leksjon 4 hvis nødvendig.

1. Legg til den relevante enhetskoden for å kontrollere reléet fra mottatte kommandoer, ved å bruke `relay_on`-egenskapen fra meldingen. Send true for `relay_on` hvis `soil_moisture` er større enn 450, ellers send false, samme som logikken du la til for IoT-enheten tidligere.

    > ⚠️ Du kan referere til [instruksjonene for å håndtere kommandoer fra MQTT i prosjekt 1, leksjon 4 hvis nødvendig](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Du finner denne koden i [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt)-mappen.

Sørg for at koden kjører på enheten din og lokal server, og test den ved å endre jordfuktighetsnivåer, enten ved å endre verdiene sendt av den virtuelle sensoren, eller ved å endre fuktighetsnivået i jorden ved å tilsette vann eller fjerne sensoren fra jorden.

## Sensor- og aktuator-timing

Tilbake i leksjon 3 bygde du en nattlampe – en LED som slår seg på så snart et lavt lysnivå ble oppdaget av en lyssensor. Lyssensoren oppdaget en endring i lysnivåer umiddelbart, og enheten kunne reagere raskt, kun begrenset av lengden på forsinkelsen i `loop`-funksjonen eller `while True:`-løkken. Som IoT-utvikler kan du ikke alltid stole på en så rask tilbakemeldingssløyfe.

### Timing for jordfuktighet

Hvis du gjorde forrige leksjon om jordfuktighet med en fysisk sensor, ville du ha lagt merke til at det tok noen sekunder før jordfuktighetsmålingen sank etter at du vannet planten din. Dette er ikke fordi sensoren er treg, men fordi det tar tid for vannet å trekke gjennom jorden.
💁 Hvis du vannet for nær sensoren, kan du ha sett at målingen falt raskt og deretter steg igjen – dette skyldes at vannet nær sensoren sprer seg gjennom resten av jorden, noe som reduserer jordfuktigheten ved sensoren.
![En måling av jordfuktighet på 658 endrer seg ikke under vanning, den faller først til 320 etter vanning når vannet har trukket gjennom jorden](../../../../../translated_images/no/soil-moisture-travel.a0e31af222cf1438.webp)

I diagrammet ovenfor viser en måling av jordfuktighet 658. Planten blir vannet, men denne målingen endrer seg ikke umiddelbart, siden vannet ennå ikke har nådd sensoren. Vanningen kan til og med være ferdig før vannet når sensoren og verdien faller for å reflektere det nye fuktighetsnivået.

Hvis du skulle skrive kode for å kontrollere et vanningssystem via et relé basert på jordfuktighetsnivåer, må du ta denne forsinkelsen i betraktning og bygge smartere timing inn i IoT-enheten din.

✅ Ta et øyeblikk til å tenke på hvordan du kan gjøre dette.

### Kontrollere sensor- og aktuator-timing

Tenk deg at du har fått i oppgave å bygge et vanningssystem for en gård. Basert på jordtypen har det ideelle jordfuktighetsnivået for plantene blitt funnet å tilsvare en analog spenning på 400-450.

Du kunne programmert enheten på samme måte som nattlampen – så lenge sensoren leser over 450, slå på et relé for å aktivere en pumpe. Problemet er at det tar tid for vannet å komme fra pumpen, gjennom jorden og til sensoren. Sensoren vil stoppe vannet når den registrerer et nivå på 450, men vannnivået vil fortsette å synke ettersom det pumpede vannet fortsetter å trekke gjennom jorden. Resultatet er bortkastet vann og risiko for rotskader.

✅ Husk – for mye vann kan være like skadelig for planter som for lite, og det sløser med en verdifull ressurs.

Den bedre løsningen er å forstå at det er en forsinkelse mellom at aktuatoren slår seg på og egenskapen som sensoren leser endrer seg. Dette betyr at ikke bare bør sensoren vente en stund før den måler verdien igjen, men aktuatoren må også slå seg av en stund før neste sensormåling tas.

Hvor lenge bør reléet være på hver gang? Det er bedre å være forsiktig og bare slå reléet på i kort tid, deretter vente til vannet har trukket gjennom, og så sjekke fuktighetsnivåene på nytt. Tross alt kan du alltid slå det på igjen for å tilføre mer vann, men du kan ikke fjerne vann fra jorden.

> 💁 Denne typen timingkontroll er veldig spesifikk for IoT-enheten du bygger, egenskapen du måler og sensorene og aktuatorene som brukes.

![En jordbærplante koblet til vann via en pumpe, med pumpen koblet til et relé. Reléet og en jordfuktighetssensor i planten er begge koblet til en Raspberry Pi](../../../../../translated_images/no/strawberry-with-pump.b410fc72ac6aabad.webp)

For eksempel har jeg en jordbærplante med en jordfuktighetssensor og en pumpe kontrollert av et relé. Jeg har observert at når jeg tilfører vann, tar det omtrent 20 sekunder før målingen av jordfuktighet stabiliserer seg. Dette betyr at jeg må slå av reléet og vente 20 sekunder før jeg sjekker fuktighetsnivåene. Jeg foretrekker å ha for lite vann enn for mye – jeg kan alltid slå på pumpen igjen, men jeg kan ikke fjerne vann fra planten.

![Steg 1, ta måling. Steg 2, tilføre vann. Steg 3, vent til vannet har trukket gjennom jorden. Steg 4, ta ny måling](../../../../../translated_images/no/soil-moisture-delay.865f3fae206db01d.webp)

Dette betyr at den beste prosessen vil være en vanningssyklus som ser slik ut:

* Slå på pumpen i 5 sekunder
* Vent 20 sekunder
* Sjekk jordfuktigheten
* Hvis nivået fortsatt er over det jeg trenger, gjenta trinnene ovenfor

5 sekunder kan være for lenge for pumpen, spesielt hvis fuktighetsnivåene bare er litt over det nødvendige nivået. Den beste måten å vite hvilken timing som skal brukes, er å prøve det, og deretter justere når du har sensordata, med en konstant tilbakemeldingssløyfe. Dette kan til og med føre til mer granulær timing, som å slå på pumpen i 1 sekund for hver 100 over det nødvendige jordfuktighetsnivået, i stedet for faste 5 sekunder.

✅ Gjør litt research: Finnes det andre timinghensyn? Kan planten vannes når som helst når jordfuktigheten er for lav, eller er det spesifikke tider på dagen som er gode og dårlige for vanning av planter?

> 💁 Værprognoser kan også tas i betraktning når man kontrollerer automatiske vanningssystemer for utendørs dyrking. Hvis det er ventet regn, kan vanningen settes på pause til etter regnet er ferdig. På det tidspunktet kan jorden være fuktig nok til at den ikke trenger vanning, noe som er mye mer effektivt enn å sløse vann ved å vanne rett før regnet.

## Legg til timing i serveren for plantekontroll

Serverkoden kan modifiseres for å legge til kontroll rundt timingen av vanningssyklusen og venting på at jordfuktighetsnivåene skal endre seg. Serverlogikken for å kontrollere relétiming er:

1. Telemetrimelding mottatt
1. Sjekk jordfuktighetsnivået
1. Hvis det er ok, gjør ingenting. Hvis målingen er for høy (som betyr at jordfuktigheten er for lav), så:
    1. Send en kommando for å slå på reléet
    1. Vent i 5 sekunder
    1. Send en kommando for å slå av reléet
    1. Vent i 20 sekunder for at jordfuktighetsnivåene skal stabilisere seg

Vanningssyklusen, prosessen fra mottak av telemetrimelding til å være klar til å prosessere jordfuktighetsnivåer igjen, tar omtrent 25 sekunder. Vi sender jordfuktighetsnivåer hvert 10. sekund, så det er en overlapping der en melding mottas mens serveren venter på at jordfuktighetsnivåene skal stabilisere seg, noe som kan starte en ny vanningssyklus.

Det finnes to alternativer for å håndtere dette:

* Endre IoT-enhetskoden til å bare sende telemetri hvert minutt, slik at vanningssyklusen fullføres før neste melding sendes
* Avslutte abonnementet på telemetri under vanningssyklusen

Det første alternativet er ikke alltid en god løsning for store gårder. Bonden kan ønske å fange jordfuktighetsnivåene mens jorden vannes for senere analyse, for eksempel for å være klar over vannstrømmen i forskjellige områder på gården for å veilede mer målrettet vanning. Det andre alternativet er bedre – koden ignorerer bare telemetri når den ikke kan bruke den, men telemetrien er fortsatt tilgjengelig for andre tjenester som kan abonnere på den.

> 💁 IoT-data sendes ikke fra bare én enhet til bare én tjeneste, i stedet kan mange enheter sende data til en broker, og mange tjenester kan lytte til dataene fra broker. For eksempel kan én tjeneste lytte til jordfuktighetsdata og lagre det i en database for analyse senere. En annen tjeneste kan også lytte til den samme telemetrien for å kontrollere et vanningssystem.

### Oppgave - legg til timing i serveren for plantekontroll

Oppdater serverkoden din for å kjøre reléet i 5 sekunder, deretter vente i 20 sekunder.

1. Åpne `soil-moisture-sensor-server`-mappen i VS Code hvis den ikke allerede er åpen. Sørg for at det virtuelle miljøet er aktivert.

1. Åpne `app.py`-filen

1. Legg til følgende kode i `app.py`-filen under de eksisterende importene:

    ```python
    import threading
    ```

    Denne uttalelsen importerer `threading` fra Python-bibliotekene. Threading lar Python utføre annen kode mens den venter.

1. Legg til følgende kode før `handle_telemetry`-funksjonen som håndterer telemetrimeldinger mottatt av serverkoden:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Dette definerer hvor lenge reléet skal være på (`water_time`), og hvor lenge det skal vente etterpå for å sjekke jordfuktigheten (`wait_time`).

1. Under denne koden, legg til følgende:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Denne koden definerer en funksjon kalt `send_relay_command` som sender en kommando over MQTT for å kontrollere reléet. Telemetrien opprettes som et ordbokobjekt, og konverteres deretter til en JSON-streng. Verdien som sendes inn i `state` bestemmer om reléet skal være på eller av.

1. Etter `send_relay_code`-funksjonen, legg til følgende kode:

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

    Dette definerer en funksjon for å kontrollere reléet basert på nødvendig timing. Den starter med å avslutte abonnementet på telemetri slik at jordfuktighetsmeldinger ikke behandles mens vanningen pågår. Deretter sender den en kommando for å slå på reléet. Den venter deretter i `water_time` før den sender en kommando for å slå av reléet. Til slutt venter den i `wait_time` sekunder for at jordfuktighetsnivåene skal stabilisere seg. Den abonnerer deretter på telemetri igjen.

1. Endre `handle_telemetry`-funksjonen til følgende:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Denne koden sjekker jordfuktighetsnivået. Hvis det er større enn 450, trenger jorden vanning, så den kaller `control_relay`-funksjonen. Denne funksjonen kjøres på en separat tråd, som kjører i bakgrunnen.

1. Sørg for at IoT-enheten din kjører, og kjør deretter denne koden. Endre jordfuktighetsnivåene og observer hva som skjer med reléet – det skal slå seg på i 5 sekunder og deretter forbli av i minst 20 sekunder, og bare slå seg på hvis jordfuktighetsnivåene ikke er tilstrekkelige.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    En god måte å teste dette i et simulert vanningssystem er å bruke tørr jord, og deretter helle vann manuelt mens reléet er på, og stoppe når reléet slår seg av.

> 💁 Du finner denne koden i [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing)-mappen.

> 💁 Hvis du vil bruke en pumpe for å bygge et ekte vanningssystem, kan du bruke en [6V vannpumpe](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) med en [USB-terminal strømforsyning](https://www.adafruit.com/product/3628). Sørg for at strømmen til eller fra pumpen er koblet via reléet.

---

## 🚀 Utfordring

Kan du tenke på andre IoT- eller elektriske enheter som har et lignende problem der det tar tid før resultatene fra aktuatoren når sensoren? Du har sannsynligvis et par i huset eller på skolen.

* Hvilke egenskaper måler de?
* Hvor lang tid tar det før egenskapen endrer seg etter at aktuatoren er brukt?
* Er det greit at egenskapen endrer seg forbi det nødvendige nivået?
* Hvordan kan den returneres til det nødvendige nivået hvis det trengs?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Gjennomgang og selvstudie

* Les mer om reléer, inkludert deres historiske bruk i telefonsentraler, på [relé Wikipedia-siden](https://wikipedia.org/wiki/Relay).

## Oppgave

[Bygg en mer effektiv vanningssyklus](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.