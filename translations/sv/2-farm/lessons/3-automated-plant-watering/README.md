# Automatisk växtbevattning

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-7.30b5f577d3cb8e03.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion ingick i [IoT för nybörjare Projekt 2 - Digital jordbruk-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![IoT-driven automatisk växtbevattning](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Introduktion

I den förra lektionen lärde du dig att övervaka jordfuktighet. I denna lektion kommer du att lära dig att bygga de grundläggande komponenterna i ett automatiskt bevattningssystem som reagerar på jordfuktighet. Du kommer också att lära dig om timing – hur sensorer kan ta tid att reagera på förändringar och hur aktuatorer kan ta tid att ändra de egenskaper som mäts av sensorer.

I denna lektion kommer vi att täcka:

* [Styr högströmsenheter från en lågströms IoT-enhet](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Styr ett relä](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Styr din växt via MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Sensor- och aktuator-timing](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Lägg till timing till din växtkontrollserver](../../../../../2-farm/lessons/3-automated-plant-watering)

## Styr högströmsenheter från en lågströms IoT-enhet

IoT-enheter använder låg spänning. Även om detta räcker för sensorer och lågströmsaktuatorer som lysdioder, är det för lågt för att styra större hårdvara, såsom en vattenpump som används för bevattning. Även små pumpar som du kan använda för krukväxter drar för mycket ström för en IoT-utvecklingssats och skulle bränna ut kortet.

> 🎓 Ström, mätt i Ampere (A), är mängden elektricitet som rör sig genom en krets. Spänning ger trycket, strömmen är hur mycket som trycks. Du kan läsa mer om ström på [Wikipedia-sidan om elektrisk ström](https://wikipedia.org/wiki/Electric_current).

Lösningen på detta är att ha en pump ansluten till en extern strömkälla och använda en aktuator för att slå på pumpen, ungefär som du skulle slå på en lampa. Det krävs en liten mängd energi (i form av energi i din kropp) för att ditt finger ska trycka på en strömbrytare, och detta ansluter lampan till nätström som körs på 110v/240v.

![En strömbrytare slår på strömmen till en lampa](../../../../../translated_images/sv/light-switch.760317ad6ab8bd6d.webp)

> 🎓 [Nätström](https://wikipedia.org/wiki/Mains_electricity) avser elektricitet som levereras till hem och företag via nationell infrastruktur i många delar av världen.

✅ IoT-enheter kan vanligtvis ge 3,3V eller 5V, med mindre än 1 ampere (1A) ström. Jämför detta med nätström som oftast är på 230V (120V i Nordamerika och 100V i Japan) och kan ge ström till enheter som drar 30A.

Det finns ett antal aktuatorer som kan göra detta, inklusive mekaniska enheter som du kan fästa på befintliga strömbrytare som efterliknar ett finger som slår på dem. Den mest populära är ett relä.

### Reläer

Ett relä är en elektromekanisk strömbrytare som omvandlar en elektrisk signal till en mekanisk rörelse som slår på en strömbrytare. Kärnan i ett relä är en elektromagnet.

> 🎓 [Elektromagneter](https://wikipedia.org/wiki/Electromagnet) är magneter som skapas genom att elektricitet passerar genom en spole av tråd. När elektriciteten är påslagen blir spolen magnetiserad. När elektriciteten stängs av förlorar spolen sin magnetism.

![När påslagen skapar elektromagneten ett magnetfält som slår på strömbrytaren för utgångskretsen](../../../../../translated_images/sv/relay-on.4db16a0fd6b66926.webp)

I ett relä driver en styrkrets elektromagneten. När elektromagneten är påslagen drar den en spak som flyttar en strömbrytare, stänger ett par kontakter och slutför en utgångskrets.

![När avstängd skapar elektromagneten inget magnetfält, vilket stänger av strömbrytaren för utgångskretsen](../../../../../translated_images/sv/relay-off.c34a178a2960fecd.webp)

När styrkretsen är avstängd stängs elektromagneten av, släpper spaken och öppnar kontakterna, vilket stänger av utgångskretsen. Reläer är digitala aktuatorer – en hög signal till reläet slår på det, en låg signal stänger av det.

Utgångskretsen kan användas för att driva ytterligare hårdvara, som ett bevattningssystem. IoT-enheten kan slå på reläet, slutföra utgångskretsen som driver bevattningssystemet, och växterna får vatten. IoT-enheten kan sedan stänga av reläet, bryta strömmen till bevattningssystemet och stänga av vattnet.

![Ett relä som slås på, slår på en pump som skickar vatten till en växt](../../../../../images/strawberry-pump.gif)

I videon ovan slås ett relä på. En lysdiod på reläet lyser för att indikera att det är på (vissa reläkort har lysdioder för att indikera om reläet är på eller av), och ström skickas till pumpen, vilket slår på den och pumpar vatten till en växt.

> 💁 Reläer kan också användas för att växla mellan två utgångskretsar istället för att slå på och av en. När spaken rör sig flyttar den en strömbrytare från att slutföra en utgångskrets till att slutföra en annan utgångskrets, vanligtvis med en gemensam strömanslutning eller gemensam jordanslutning.

✅ Gör lite forskning: Det finns flera typer av reläer, med skillnader som om styrkretsen slår på eller av reläet när ström tillförs, eller flera utgångskretsar. Ta reda på mer om dessa olika typer.

När spaken rör sig kan du vanligtvis höra den göra kontakt med elektromagneten med ett tydligt klickljud.

> 💁 Ett relä kan kopplas så att anslutningen faktiskt bryter strömmen till reläet, vilket stänger av reläet, som sedan skickar ström till reläet och slår på det igen, och så vidare. Detta innebär att reläet klickar otroligt snabbt och skapar ett surrande ljud. Så här fungerade några av de första summerna som användes i elektriska dörrklockor.

### Reläström

Elektromagneten behöver inte mycket ström för att aktiveras och dra spaken, den kan styras med 3,3V eller 5V från en IoT-utvecklingssats. Utgångskretsen kan bära mycket mer ström, beroende på reläet, inklusive nätspänning eller ännu högre strömnivåer för industriellt bruk. På detta sätt kan en IoT-utvecklingssats styra ett bevattningssystem, från en liten pump för en enskild växt, till ett massivt industriellt system för en hel kommersiell gård.

![Ett Grove-relä med styrkrets, utgångskrets och relä markerade](../../../../../translated_images/sv/grove-relay-labelled.293e068f5c3c2a19.webp)

Bilden ovan visar ett Grove-relä. Styrkretsen ansluts till en IoT-enhet och slår på eller av reläet med 3,3V eller 5V. Utgångskretsen har två terminaler, var och en kan vara ström eller jord. Utgångskretsen kan hantera upp till 250V vid 10A, tillräckligt för en rad nätanslutna enheter. Du kan få reläer som kan hantera ännu högre strömnivåer.

![En pump ansluten via ett relä](../../../../../translated_images/sv/pump-wired-to-relay.66c5cfc0d8918990.webp)

I bilden ovan tillförs ström till en pump via ett relä. Det finns en röd kabel som ansluter +5V-terminalen på en USB-strömkälla till en terminal på utgångskretsen på reläet, och en annan röd kabel som ansluter den andra terminalen på utgångskretsen till pumpen. En svart kabel ansluter pumpen till jord på USB-strömkällan. När reläet slås på slutför det kretsen, skickar 5V till pumpen och slår på pumpen.

## Styr ett relä

Du kan styra ett relä från din IoT-utvecklingssats.

### Uppgift - styr ett relä

Följ den relevanta guiden för att styra ett relä med din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Enkorts-dator - Raspberry Pi](pi-relay.md)
* [Enkorts-dator - Virtuell enhet](virtual-device-relay.md)

## Styr din växt via MQTT

Hittills har ditt relä styrts direkt av IoT-enheten baserat på en enda jordfuktighetsavläsning. I ett kommersiellt bevattningssystem kommer styrlogiken att vara centraliserad, vilket gör det möjligt att fatta beslut om bevattning med data från flera sensorer och tillåta att alla konfigurationer ändras på ett enda ställe. För att simulera detta kan du styra reläet via MQTT.

### Uppgift - styr reläet via MQTT

1. Lägg till de relevanta MQTT-biblioteken/pip-paketen och kod till ditt `soil-moisture-sensor`-projekt för att ansluta till MQTT. Namnge klient-ID:t som `soilmoisturesensor_client` med ditt ID som prefix.

    > ⚠️ Du kan hänvisa till [instruktionerna för att ansluta till MQTT i projekt 1, lektion 4 om det behövs](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Lägg till den relevanta enhetskoden för att skicka telemetri med inställningarna för jordfuktighet. För telemetrimeddelandet, namnge egenskapen `soil_moisture`.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skicka telemetri till MQTT i projekt 1, lektion 4 om det behövs](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Skapa lite lokal serverkod för att prenumerera på telemetri och skicka ett kommando för att styra reläet i en mapp som heter `soil-moisture-sensor-server`. Namnge egenskapen i kommandomeddelandet `relay_on`, och sätt klient-ID:t som `soilmoisturesensor_server` med ditt ID som prefix. Behåll samma struktur som serverkoden du skrev för projekt 1, lektion 4 eftersom du kommer att lägga till denna kod senare i denna lektion.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skicka telemetri till MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) och [skicka kommandon via MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) i projekt 1, lektion 4 om det behövs.

1. Lägg till den relevanta enhetskoden för att styra reläet från mottagna kommandon, med egenskapen `relay_on` från meddelandet. Skicka true för `relay_on` om `soil_moisture` är större än 450, annars skicka false, samma som logiken du lade till för IoT-enheten tidigare.

    > ⚠️ Du kan hänvisa till [instruktionerna för att svara på kommandon från MQTT i projekt 1, lektion 4 om det behövs](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Du kan hitta denna kod i [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt)-mappen.

Se till att koden körs på din enhet och lokala server, och testa den genom att ändra jordfuktighetsnivåer, antingen genom att ändra värdena som skickas av den virtuella sensorn eller genom att ändra fuktighetsnivåerna i jorden genom att tillsätta vatten eller ta bort sensorn från jorden.

## Sensor- och aktuator-timing

Tillbaka i lektion 3 byggde du en nattlampa – en lysdiod som tänds så snart en låg ljusnivå upptäcks av en ljussensor. Ljussensorn upptäckte en förändring i ljusnivåer direkt, och enheten kunde reagera snabbt, endast begränsad av längden på fördröjningen i `loop`-funktionen eller `while True:`-loopen. Som IoT-utvecklare kan du inte alltid förlita dig på en så snabb återkopplingsslinga.

### Timing för jordfuktighet

Om du gjorde den senaste lektionen om jordfuktighet med en fysisk sensor, skulle du ha märkt att det tog några sekunder för jordfuktighetsavläsningen att sjunka efter att du vattnat din växt. Detta beror inte på att sensorn är långsam, utan på att det tar tid för vatten att tränga igenom jorden.
💁 Om du vattnade för nära sensorn kan du ha sett att avläsningen sjönk snabbt och sedan steg igen – detta beror på att vattnet nära sensorn sprider sig genom resten av jorden, vilket minskar jordfuktigheten vid sensorn.
![En jordfuktighetsmätning på 658 ändras inte under bevattning, den sjunker bara till 320 efter bevattning när vattnet har trängt igenom jorden](../../../../../translated_images/sv/soil-moisture-travel.a0e31af222cf1438.webp)

I diagrammet ovan visar en jordfuktighetsmätning 658. Växten vattnas, men denna mätning ändras inte omedelbart eftersom vattnet ännu inte har nått sensorn. Vattningen kan till och med avslutas innan vattnet når sensorn och värdet sjunker för att återspegla den nya fuktighetsnivån.

Om du skulle skriva kod för att styra ett bevattningssystem via ett relä baserat på jordfuktighetsnivåer, skulle du behöva ta hänsyn till denna fördröjning och bygga in smartare timing i din IoT-enhet.

✅ Ta en stund och fundera på hur du skulle kunna göra detta.

### Kontrollera sensor- och aktuatortiming

Föreställ dig att du har fått i uppdrag att bygga ett bevattningssystem för en gård. Baserat på jordtypen har den ideala jordfuktighetsnivån för de odlade växterna visat sig motsvara en analog spänningsavläsning på 400-450.

Du skulle kunna programmera enheten på samma sätt som en nattlampa - så länge sensorn läser över 450, slå på ett relä för att aktivera en pump. Problemet är att det tar tid för vattnet att nå från pumpen, genom jorden till sensorn. Sensorn kommer att stoppa vattnet när den upptäcker en nivå på 450, men fuktighetsnivån kommer att fortsätta sjunka eftersom det pumpade vattnet fortsätter att tränga igenom jorden. Slutresultatet är slöseri med vatten och risk för rotskador.

✅ Kom ihåg - för mycket vatten kan vara lika dåligt för växterna som för lite, och det slösar med en värdefull resurs.

Den bättre lösningen är att förstå att det finns en fördröjning mellan att aktivera aktuatorn och att egenskapen som sensorn läser ändras. Detta innebär att sensorn inte bara bör vänta ett tag innan den mäter värdet igen, utan att aktuatorn också behöver stängas av ett tag innan nästa sensormätning görs.

Hur länge ska reläet vara på varje gång? Det är bättre att vara försiktig och bara slå på reläet en kort stund, sedan vänta på att vattnet ska tränga igenom och därefter kontrollera fuktighetsnivåerna igen. När allt kommer omkring kan du alltid slå på det igen för att lägga till mer vatten, men du kan inte ta bort vatten från jorden.

> 💁 Den här typen av timingkontroll är mycket specifik för den IoT-enhet du bygger, egenskapen du mäter och de sensorer och aktuatorer som används.

![En jordgubbsplanta ansluten till vatten via en pump, med pumpen ansluten till ett relä. Reläet och en jordfuktighetssensor i plantan är båda anslutna till en Raspberry Pi](../../../../../translated_images/sv/strawberry-with-pump.b410fc72ac6aabad.webp)

Till exempel har jag en jordgubbsplanta med en jordfuktighetssensor och en pump som styrs av ett relä. Jag har observerat att när jag tillsätter vatten tar det cirka 20 sekunder för jordfuktighetsavläsningen att stabilisera sig. Detta innebär att jag behöver stänga av reläet och vänta 20 sekunder innan jag kontrollerar fuktighetsnivåerna. Jag föredrar att ha för lite vatten än för mycket - jag kan alltid slå på pumpen igen, men jag kan inte ta bort vatten från plantan.

![Steg 1, ta mätning. Steg 2, tillsätt vatten. Steg 3, vänta på att vattnet ska tränga igenom jorden. Steg 4, ta ny mätning](../../../../../translated_images/sv/soil-moisture-delay.865f3fae206db01d.webp)

Detta innebär att den bästa processen skulle vara en bevattningscykel som ser ut ungefär så här:

* Slå på pumpen i 5 sekunder
* Vänta 20 sekunder
* Kontrollera jordfuktigheten
* Om nivån fortfarande är över vad jag behöver, upprepa ovanstående steg

5 sekunder kan vara för länge för pumpen, särskilt om fuktighetsnivåerna bara är något över den önskade nivån. Det bästa sättet att veta vilken timing som ska användas är att testa, och sedan justera när du har sensordata, med en konstant feedback-loop. Detta kan till och med leda till mer detaljerad timing, såsom att slå på pumpen i 1 sekund för varje 100 över den önskade jordfuktigheten, istället för en fast tid på 5 sekunder.

✅ Gör lite research: Finns det andra timingöverväganden? Kan plantan vattnas när som helst när jordfuktigheten är för låg, eller finns det specifika tider på dagen som är bra och dåliga för att vattna växter?

> 💁 Väderprognoser kan också tas med i beräkningen när man styr automatiska bevattningssystem för utomhusodling. Om regn förväntas kan bevattningen skjutas upp tills efter regnet har slutat. Vid den tidpunkten kan jorden vara tillräckligt fuktig för att inte behöva vattnas, vilket är mycket mer effektivt än att slösa vatten genom att vattna precis innan regnet.

## Lägg till timing i din växtkontrollserver

Serverkoden kan modifieras för att lägga till kontroll kring timingen av bevattningscykeln och väntan på att jordfuktighetsnivåerna ska ändras. Serverlogiken för att styra relätiming är:

1. Telemetrimeddelande mottaget
1. Kontrollera jordfuktighetsnivån
1. Om den är ok, gör ingenting. Om avläsningen är för hög (vilket betyder att jordfuktigheten är för låg) så:
    1. Skicka ett kommando för att slå på reläet
    1. Vänta i 5 sekunder
    1. Skicka ett kommando för att stänga av reläet
    1. Vänta i 20 sekunder för att jordfuktighetsnivåerna ska stabilisera sig

Bevattningscykeln, processen från att telemetrimeddelandet tas emot till att vara redo att bearbeta jordfuktighetsnivåer igen, tar cirka 25 sekunder. Vi skickar jordfuktighetsnivåer var 10:e sekund, så det finns en överlappning där ett meddelande tas emot medan servern väntar på att jordfuktighetsnivåerna ska stabilisera sig, vilket kan starta en ny bevattningscykel.

Det finns två alternativ för att hantera detta:

* Ändra IoT-enhetens kod så att den bara skickar telemetri varje minut, på så sätt kommer bevattningscykeln att vara avslutad innan nästa meddelande skickas
* Avsluta prenumerationen på telemetri under bevattningscykeln

Det första alternativet är inte alltid en bra lösning för stora gårdar. Bonden kanske vill fånga jordfuktighetsnivåerna medan jorden vattnas för senare analys, till exempel för att vara medveten om vattenflödet i olika områden på gården för att vägleda mer riktad bevattning. Det andra alternativet är bättre - koden ignorerar bara telemetri när den inte kan använda den, men telemetrin finns fortfarande där för andra tjänster som kan prenumerera på den.

> 💁 IoT-data skickas inte från bara en enhet till bara en tjänst, istället kan många enheter skicka data till en broker, och många tjänster kan lyssna på data från brokern. Till exempel kan en tjänst lyssna på jordfuktighetsdata och lagra den i en databas för analys vid ett senare tillfälle. En annan tjänst kan också lyssna på samma telemetri för att styra ett bevattningssystem.

### Uppgift - lägg till timing i din växtkontrollserver

Uppdatera din serverkod för att köra reläet i 5 sekunder, och sedan vänta i 20 sekunder.

1. Öppna mappen `soil-moisture-sensor-server` i VS Code om den inte redan är öppen. Se till att den virtuella miljön är aktiverad.

1. Öppna filen `app.py`

1. Lägg till följande kod i filen `app.py` under de befintliga importerna:

    ```python
    import threading
    ```

    Detta uttalande importerar `threading` från Python-biblioteken, vilket gör att Python kan köra annan kod medan den väntar.

1. Lägg till följande kod före funktionen `handle_telemetry` som hanterar telemetrimeddelanden som tas emot av serverkoden:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Detta definierar hur länge reläet ska köras (`water_time`), och hur länge man ska vänta efteråt för att kontrollera jordfuktigheten (`wait_time`).

1. Under denna kod, lägg till följande:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Denna kod definierar en funktion som heter `send_relay_command` som skickar ett kommando över MQTT för att styra reläet. Telemetrin skapas som en ordbok och konverteras sedan till en JSON-sträng. Värdet som skickas in i `state` avgör om reläet ska vara på eller av.

1. Efter funktionen `send_relay_code`, lägg till följande kod:

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

    Detta definierar en funktion för att styra reläet baserat på den nödvändiga timingen. Den börjar med att avsluta prenumerationen på telemetri så att jordfuktighetsmeddelanden inte bearbetas medan bevattningen pågår. Därefter skickar den ett kommando för att slå på reläet. Den väntar sedan i `water_time` innan den skickar ett kommando för att stänga av reläet. Slutligen väntar den i `wait_time` sekunder för att jordfuktighetsnivåerna ska stabilisera sig. Den prenumererar sedan på telemetri igen.

1. Ändra funktionen `handle_telemetry` till följande:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Denna kod kontrollerar jordfuktighetsnivån. Om den är större än 450 behöver jorden vattnas, så den anropar funktionen `control_relay`. Denna funktion körs på en separat tråd, som körs i bakgrunden.

1. Se till att din IoT-enhet körs, och kör sedan denna kod. Ändra jordfuktighetsnivåerna och observera vad som händer med reläet - det ska slå på i 5 sekunder och sedan förbli avstängt i minst 20 sekunder, och bara slå på om jordfuktighetsnivåerna inte är tillräckliga.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Ett bra sätt att testa detta i ett simulerat bevattningssystem är att använda torr jord, och sedan hälla vatten manuellt medan reläet är på, och sluta hälla när reläet stängs av.

> 💁 Du kan hitta denna kod i mappen [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Om du vill använda en pump för att bygga ett riktigt bevattningssystem kan du använda en [6V vattenpump](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) med en [USB-terminal strömförsörjning](https://www.adafruit.com/product/3628). Se till att strömmen till eller från pumpen är ansluten via reläet.

---

## 🚀 Utmaning

Kan du komma på några andra IoT- eller elektriska enheter som har ett liknande problem där det tar tid för resultaten från aktuatorn att nå sensorn? Du har förmodligen ett par i ditt hem eller skola.

* Vilka egenskaper mäter de?
* Hur lång tid tar det för egenskapen att ändras efter att en aktuator används?
* Är det ok att egenskapen ändras förbi det önskade värdet?
* Hur kan det återställas till det önskade värdet om det behövs?

## Efterföreläsningsquiz

[Efterföreläsningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Granskning & Självstudier

* Läs mer om reläer, inklusive deras historiska användning i telefonväxlar, på [relä Wikipedia-sidan](https://wikipedia.org/wiki/Relay).

## Uppgift

[Bygg en mer effektiv bevattningscykel](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.