# Anslut din enhet till Internet

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-4.7344e074ea68fa54.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion ingick i [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen presenterades i två videor - en timmes lektion och en timmes frågestund där delar av lektionen fördjupades och frågor besvarades.

[![Lektion 4: Anslut din enhet till Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lektion 4: Anslut din enhet till Internet - Frågestund](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Klicka på bilderna ovan för att se videorna

## Förkunskapsquiz

[Förkunskapsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introduktion

**I** i IoT står för **Internet** - molnanslutning och tjänster som möjliggör många av funktionerna hos IoT-enheter, från att samla in mätningar från sensorer som är anslutna till enheten, till att skicka meddelanden för att styra aktuatorer. IoT-enheter ansluter vanligtvis till en enda moln-IoT-tjänst med hjälp av ett standardkommunikationsprotokoll, och den tjänsten är ansluten till resten av din IoT-applikation, från AI-tjänster för att fatta smarta beslut baserat på dina data, till webbappar för kontroll eller rapportering.

> 🎓 Data som samlas in från sensorer och skickas till molnet kallas telemetri.

IoT-enheter kan ta emot meddelanden från molnet. Ofta innehåller dessa meddelanden kommandon - instruktioner för att utföra en åtgärd antingen internt (som att starta om eller uppdatera firmware) eller med hjälp av en aktuator (som att tända en lampa).

Denna lektion introducerar några av de kommunikationsprotokoll som IoT-enheter kan använda för att ansluta till molnet, och vilka typer av data de kan skicka eller ta emot. Du kommer också att få praktisk erfarenhet av båda, genom att lägga till internetkontroll till din nattlampa och flytta LED-styrlogiken till "server"-kod som körs lokalt.

I denna lektion kommer vi att gå igenom:

* [Kommunikationsprotokoll](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetri](../../../../../1-getting-started/lessons/4-connect-internet)
* [Kommandon](../../../../../1-getting-started/lessons/4-connect-internet)

## Kommunikationsprotokoll

Det finns flera populära kommunikationsprotokoll som används av IoT-enheter för att kommunicera med Internet. De mest populära är baserade på publicera/prenumerera-meddelanden via någon form av broker. IoT-enheter ansluter till brokern och publicerar telemetri och prenumererar på kommandon. Molntjänster ansluter också till brokern och prenumererar på alla telemetrimeddelanden och publicerar kommandon antingen till specifika enheter eller till grupper av enheter.

![IoT-enheter ansluter till en broker och publicerar telemetri och prenumererar på kommandon. Molntjänster ansluter till brokern och prenumererar på all telemetri och skickar kommandon till specifika enheter.](../../../../../translated_images/sv/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT är det mest populära kommunikationsprotokollet för IoT-enheter och behandlas i denna lektion. Andra protokoll inkluderar AMQP och HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) är ett lättviktigt, öppet standardmeddelandeprotokoll som kan skicka meddelanden mellan enheter. Det designades 1999 för att övervaka oljeledningar, innan det släpptes som en öppen standard 15 år senare av IBM.

MQTT har en enda broker och flera klienter. Alla klienter ansluter till brokern, och brokern dirigerar meddelanden till relevanta klienter. Meddelanden dirigeras med hjälp av namngivna ämnen, snarare än att skickas direkt till en individuell klient. En klient kan publicera till ett ämne, och alla klienter som prenumererar på det ämnet kommer att ta emot meddelandet.

![IoT-enhet som publicerar telemetri på ämnet /telemetry, och molntjänsten som prenumererar på det ämnet](../../../../../translated_images/sv/mqtt.cbf7f21d9adc3e17.webp)

✅ Gör lite research. Om du har många IoT-enheter, hur kan du säkerställa att din MQTT-broker kan hantera alla meddelanden?

### Anslut din IoT-enhet till MQTT

Den första delen av att lägga till internetkontroll till din nattlampa är att ansluta den till en MQTT-broker.

#### Uppgift

Anslut din enhet till en MQTT-broker.

I denna del av lektionen kommer du att ansluta din IoT-nattlampa till internet för att möjliggöra fjärrstyrning. Senare i lektionen kommer din IoT-enhet att skicka ett telemetrimeddelande via MQTT till en offentlig MQTT-broker med ljusnivån, där det kommer att plockas upp av serverkod som du kommer att skriva. Denna kod kommer att kontrollera ljusnivån och skicka ett kommandomeddelande tillbaka till enheten som instruerar den att tända eller släcka LED-lampan.

Ett verkligt användningsfall för en sådan uppsättning kan vara att samla in data från flera ljussensorer innan man beslutar att tända lampor, på en plats med många lampor, som en stadion. Detta kan förhindra att lamporna tänds om endast en sensor täcks av moln eller en fågel, men de andra sensorerna registrerar tillräckligt med ljus.

✅ Vilka andra situationer skulle kräva att data från flera sensorer utvärderas innan kommandon skickas?

Istället för att hantera komplexiteten med att ställa in en MQTT-broker som en del av denna uppgift, kan du använda en offentlig testserver som kör [Eclipse Mosquitto](https://www.mosquitto.org), en öppen MQTT-broker. Denna testbroker är offentligt tillgänglig på [test.mosquitto.org](https://test.mosquitto.org) och kräver inget konto för att ställas in, vilket gör den till ett utmärkt verktyg för att testa MQTT-klienter och servrar.

> 💁 Denna testbroker är offentlig och inte säker. Vem som helst kan lyssna på vad du publicerar, så den bör inte användas med data som behöver hållas privat.

![Ett flödesschema för uppgiften som visar ljusnivåer som läses och kontrolleras, och LED-lampan som styrs](../../../../../translated_images/sv/assignment-1-internet-flow.3256feab5f052fd2.webp)

Följ relevant steg nedan för att ansluta din enhet till MQTT-brokern:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Enkortsdator - Raspberry Pi/Virtual IoT-enhet](single-board-computer-mqtt.md)

### En djupare titt på MQTT

Ämnen kan ha en hierarki, och klienter kan prenumerera på olika nivåer av hierarkin med hjälp av jokertecken. Till exempel kan du skicka temperaturtelemetrimeddelanden till ämnet `/telemetry/temperature` och fuktighetsmeddelanden till ämnet `/telemetry/humidity`, och sedan i din molnapplikation prenumerera på ämnet `/telemetry/*` för att ta emot både temperatur- och fuktighetstelemetrimeddelanden.

Meddelanden kan skickas med en kvalitet på tjänst (QoS), vilket avgör garantin för att meddelandet tas emot.

* Högst en gång - meddelandet skickas endast en gång och klienten och brokern vidtar inga ytterligare åtgärder för att bekräfta leverans (skicka och glöm).
* Minst en gång - meddelandet skickas om flera gånger av avsändaren tills bekräftelse tas emot (bekräftad leverans).
* Exakt en gång - avsändaren och mottagaren genomför en tvåstegshandshake för att säkerställa att endast en kopia av meddelandet tas emot (säker leverans).

✅ Vilka situationer kan kräva ett säkert leveransmeddelande över ett skicka-och-glöm-meddelande?

Trots namnet Message Queueing (MQTT) stöder det faktiskt inte meddelandeköer. Detta innebär att om en klient kopplas bort och sedan ansluter igen, kommer den inte att ta emot meddelanden som skickades under frånkopplingen, förutom de meddelanden som den redan hade börjat bearbeta med hjälp av QoS-processen. Meddelanden kan ha en flagga för att behållas. Om denna flagga är inställd kommer MQTT-brokern att lagra det senaste meddelandet som skickades på ett ämne med denna flagga och skicka detta till alla klienter som senare prenumererar på ämnet. På så sätt får klienterna alltid det senaste meddelandet.

MQTT stöder också en keep-alive-funktion som kontrollerar om anslutningen fortfarande är aktiv under långa pauser mellan meddelanden.

> 🦟 [Mosquitto från Eclipse Foundation](https://mosquitto.org) har en gratis MQTT-broker som du kan köra själv för att experimentera med MQTT, samt en offentlig MQTT-broker som du kan använda för att testa din kod, värd på [test.mosquitto.org](https://test.mosquitto.org).

MQTT-anslutningar kan vara offentliga och öppna, eller krypterade och säkrade med användarnamn och lösenord, eller certifikat.

> 💁 MQTT kommunicerar över TCP/IP, samma underliggande nätverksprotokoll som HTTP, men på en annan port. Du kan också använda MQTT över websockets för att kommunicera med webbappar som körs i en webbläsare, eller i situationer där brandväggar eller andra nätverksregler blockerar standard-MQTT-anslutningar.

## Telemetri

Ordet telemetri kommer från grekiska rötter och betyder att mäta på distans. Telemetri är handlingen att samla in data från sensorer och skicka den till molnet.

> 💁 En av de tidigaste telemetrianordningarna uppfanns i Frankrike 1874 och skickade realtidsväder och snödjup från Mont Blanc till Paris. Den använde fysiska kablar eftersom trådlösa teknologier inte var tillgängliga vid den tiden.

Låt oss återgå till exemplet med den smarta termostaten från Lektion 1.

![En internetansluten termostat som använder flera rumssensorer](../../../../../translated_images/sv/telemetry.21e5d8b97649d2eb.webp)

Termostaten har temperatursensorer för att samla in telemetri. Den skulle troligen ha en inbyggd temperatursensor och kanske ansluta till flera externa temperatursensorer via ett trådlöst protokoll som [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Ett exempel på telemetridata som den skulle skicka kan vara:

| Namn | Värde | Beskrivning |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Temperaturen som mäts av termostatens inbyggda temperatursensor |
| `livingroom_temperature` | 19°C | Temperaturen som mäts av en fjärrsensor som har namngivits `livingroom` för att identifiera rummet den är i |
| `bedroom_temperature` | 21°C | Temperaturen som mäts av en fjärrsensor som har namngivits `bedroom` för att identifiera rummet den är i |

Molntjänsten kan sedan använda denna telemetridata för att fatta beslut om vilka kommandon som ska skickas för att styra uppvärmningen.

### Skicka telemetri från din IoT-enhet

Nästa steg i att lägga till internetkontroll till din nattlampa är att skicka ljusnivåtelemetri till MQTT-brokern på ett telemetriämne.

#### Uppgift - skicka telemetri från din IoT-enhet

Skicka ljusnivåtelemetri till MQTT-brokern.

Data skickas kodad som JSON - kort för JavaScript Object Notation, en standard för att koda data i text med nyckel/värde-par.

✅ Om du inte har stött på JSON tidigare kan du lära dig mer om det på [JSON.org-dokumentationen](https://www.json.org/).

Följ relevant steg nedan för att skicka telemetri från din enhet till MQTT-brokern:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Enkortsdator - Raspberry Pi/Virtual IoT-enhet](single-board-computer-telemetry.md)

### Ta emot telemetri från MQTT-brokern

Det är ingen idé att skicka telemetri om det inte finns något på andra sidan som lyssnar på det. Ljusnivåtelemetrin behöver något som lyssnar på den för att bearbeta data. Denna "server"-kod är den typ av kod du kommer att distribuera till en molntjänst som en del av en större IoT-applikation, men här kommer du att köra denna kod lokalt på din dator (eller på din Pi om du kodar direkt där). Serverkoden består av en Python-app som lyssnar på telemetrimeddelanden via MQTT med ljusnivåer. Senare i lektionen kommer du att få den att svara med ett kommandomeddelande med instruktioner för att tända eller släcka LED-lampan.

✅ Gör lite research: Vad händer med MQTT-meddelanden om det inte finns någon lyssnare?

#### Installera Python och VS Code

Om du inte har Python och VS Code installerat lokalt, måste du installera båda för att kunna koda servern. Om du använder en virtuell IoT-enhet eller arbetar på din Raspberry Pi kan du hoppa över detta steg eftersom du redan bör ha detta installerat och konfigurerat.

##### Uppgift - installera Python och VS Code

Installera Python och VS Code.

1. Installera Python. Se [Python-nedladdningssidan](https://www.python.org/downloads/) för instruktioner om hur du installerar den senaste versionen av Python.

1. Installera Visual Studio Code (VS Code). Detta är den editor du kommer att använda för att skriva din virtuella enhetskod i Python. Se [VS Code-dokumentationen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) för instruktioner om hur du installerar VS Code.
> 💁 Du är fri att använda vilken Python-IDE eller editor du föredrar för dessa lektioner, men instruktionerna i lektionerna kommer att baseras på användning av VS Code.
1. Installera VS Code Pylance-tillägget. Detta är ett tillägg för VS Code som ger stöd för Python-språket. Se [Pylance-tilläggets dokumentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) för instruktioner om hur du installerar detta tillägg i VS Code.

#### Konfigurera en virtuell Python-miljö

En av de kraftfulla funktionerna i Python är möjligheten att installera [pip-paket](https://pypi.org) - dessa är kodpaket skrivna av andra och publicerade på internet. Du kan installera ett pip-paket på din dator med ett enda kommando och sedan använda det paketet i din kod. Du kommer att använda pip för att installera ett paket för att kommunicera via MQTT.

Som standard, när du installerar ett paket, är det tillgängligt överallt på din dator, vilket kan leda till problem med paketversioner - till exempel om en applikation är beroende av en version av ett paket som slutar fungera när du installerar en ny version för en annan applikation. För att undvika detta problem kan du använda en [virtuell Python-miljö](https://docs.python.org/3/library/venv.html), som i princip är en kopia av Python i en dedikerad mapp. När du installerar pip-paket installeras de endast i den mappen.

##### Uppgift - konfigurera en virtuell Python-miljö

Konfigurera en virtuell Python-miljö och installera MQTT-pip-paketen.

1. Från din terminal eller kommandorad, kör följande på en plats du väljer för att skapa och navigera till en ny katalog:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Kör nu följande för att skapa en virtuell miljö i `.venv`-mappen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Du måste uttryckligen anropa `python3` för att skapa den virtuella miljön, ifall du har Python 2 installerat utöver Python 3 (den senaste versionen). Om du har Python 2 installerat kommer anropet av `python` att använda Python 2 istället för Python 3.

1. Aktivera den virtuella miljön:

    * På Windows:
        * Om du använder Kommandotolken eller Kommandotolken via Windows Terminal, kör:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Om du använder PowerShell, kör:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * På macOS eller Linux, kör:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Dessa kommandon bör köras från samma plats där du körde kommandot för att skapa den virtuella miljön. Du behöver aldrig navigera in i `.venv`-mappen, du bör alltid köra aktiveringskommandot och alla kommandon för att installera paket eller köra kod från mappen du var i när du skapade den virtuella miljön.

1. När den virtuella miljön har aktiverats kommer standardkommandot `python` att köra den version av Python som användes för att skapa den virtuella miljön. Kör följande för att få versionen:

    ```sh
    python --version
    ```

    Utdata kommer att likna följande:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Din Python-version kan vara annorlunda - så länge den är version 3.6 eller högre är det bra. Om inte, ta bort den här mappen, installera en nyare version av Python och försök igen.

1. Kör följande kommandon för att installera pip-paketet för [Paho-MQTT](https://pypi.org/project/paho-mqtt/), ett populärt MQTT-bibliotek.

    ```sh
    pip install paho-mqtt
    ```

    Detta pip-paket kommer endast att installeras i den virtuella miljön och kommer inte att vara tillgängligt utanför den.

#### Skriv serverkoden

Serverkoden kan nu skrivas i Python.

##### Uppgift - skriv serverkoden

Skriv serverkoden.

1. Från din terminal eller kommandorad, kör följande inuti den virtuella miljön för att skapa en Python-fil som heter `app.py`:

    * På Windows, kör:

        ```cmd
        type nul > app.py
        ```

    * På macOS eller Linux, kör:

        ```cmd
        touch app.py
        ```

1. Öppna den aktuella mappen i VS Code:

    ```sh
    code .
    ```

1. När VS Code startar kommer det att aktivera den virtuella Python-miljön. Detta kommer att rapporteras i den nedre statusfältet:

    ![VS Code visar den valda virtuella miljön](../../../../../translated_images/sv/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Om VS Code-terminalen redan körs när VS Code startar kommer den inte att ha den virtuella miljön aktiverad i sig. Det enklaste är att stänga terminalen med knappen **Kill the active terminal instance**:

    ![VS Code-knappen för att stänga aktiv terminalinstans](../../../../../translated_images/sv/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Starta en ny VS Code-terminal genom att välja *Terminal -> New Terminal*, eller trycka på `` CTRL+` ``. Den nya terminalen kommer att ladda den virtuella miljön, med anropet för att aktivera detta som visas i terminalen. Namnet på den virtuella miljön (`.venv`) kommer också att finnas i prompten:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Öppna filen `app.py` från VS Code Explorer och lägg till följande kod:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Ersätt `<ID>` på rad 6 med det unika ID du använde när du skapade din enhetskod.

    ⚠️ Detta **måste** vara samma ID som du använde på din enhet, annars kommer serverkoden inte att prenumerera eller publicera på rätt ämne.

    Denna kod skapar en MQTT-klient med ett unikt namn och ansluter till *test.mosquitto.org*-mäklaren. Den startar sedan en bearbetningsslinga som körs i en bakgrundstråd och lyssnar efter meddelanden på alla prenumererade ämnen.

    Klienten prenumererar sedan på meddelanden på telemetriämnet och definierar en funktion som anropas när ett meddelande tas emot. När ett telemetrimeddelande tas emot anropas funktionen `handle_telemetry`, som skriver ut det mottagna meddelandet till konsolen.

    Slutligen håller en oändlig slinga applikationen igång. MQTT-klienten lyssnar på meddelanden i en bakgrundstråd och körs så länge huvudapplikationen körs.

1. Från VS Code-terminalen, kör följande för att köra din Python-app:

    ```sh
    python app.py
    ```

    Appen börjar lyssna på meddelanden från IoT-enheten.

1. Se till att din enhet körs och skickar telemetrimeddelanden. Justera ljusnivåerna som detekteras av din fysiska eller virtuella enhet. Mottagna meddelanden kommer att skrivas ut i terminalen.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Filen `app.py` i den virtuella miljön för nattljuset måste köras för att filen `app.py` i den virtuella miljön för nattljus-servern ska kunna ta emot de meddelanden som skickas.

> 💁 Du kan hitta denna kod i mappen [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Hur ofta ska telemetri skickas?

En viktig fråga med telemetri är hur ofta data ska mätas och skickas? Svaret är - det beror på. Om du mäter ofta kan du reagera snabbare på förändringar i mätningarna, men du använder mer ström, mer bandbredd, genererar mer data och behöver fler molnresurser för att bearbeta. Du behöver mäta tillräckligt ofta, men inte för ofta.

För en termostat är det förmodligen mer än tillräckligt att mäta var några minuter eftersom temperaturer inte ändras så ofta. Om du bara mäter en gång om dagen kan du dock riskera att värma ditt hus för nattens temperaturer mitt på en solig dag, medan om du mäter varje sekund kommer du att ha tusentals onödigt duplicerade temperaturmätningar som kan påverka användarens internethastighet och bandbredd (ett problem för personer med begränsade bandbreddsplaner), använda mer ström vilket kan vara ett problem för batteridrivna enheter som fjärrsensorer, och öka kostnaden för molnresurser som bearbetar och lagrar dem.

Om du övervakar data från en maskin i en fabrik som, om den går sönder, kan orsaka katastrofala skador och miljontals dollar i förlorade intäkter, kan det vara nödvändigt att mäta flera gånger per sekund. Det är bättre att slösa bandbredd än att missa telemetri som indikerar att en maskin behöver stoppas och repareras innan den går sönder.

> 💁 I en sådan situation kan du överväga att ha en edge-enhet för att bearbeta telemetrin först och minska beroendet av internet.

### Förlust av anslutning

Internetanslutningar kan vara opålitliga, med vanliga avbrott. Vad ska en IoT-enhet göra under dessa omständigheter - ska den förlora data, eller ska den lagra den tills anslutningen återställs? Återigen, svaret är att det beror på.

För en termostat kan data förmodligen förloras så snart en ny temperaturmätning har tagits. Värmesystemet bryr sig inte om att det för 20 minuter sedan var 20,5°C om temperaturen nu är 19°C, det är temperaturen nu som avgör om värmen ska vara på eller av.

För maskiner kanske du vill behålla data, särskilt om den används för att leta efter trender. Det finns maskininlärningsmodeller som kan upptäcka avvikelser i dataströmmar genom att titta på data från en definierad tidsperiod (till exempel den senaste timmen) och identifiera avvikande data. Detta används ofta för prediktivt underhåll, för att leta efter indikationer på att något kan gå sönder snart så att du kan reparera eller byta ut det innan det händer. Du kanske vill att varje bit telemetri för en maskin skickas så att den kan bearbetas för avvikelsedetektering, så när IoT-enheten kan återansluta kommer den att skicka all telemetri som genererades under internetavbrottet.

IoT-enhetsdesigners bör också överväga om IoT-enheten kan användas under ett internetavbrott eller förlust av signal på grund av plats. En smart termostat bör kunna fatta vissa begränsade beslut för att styra värmen om den inte kan skicka telemetri till molnet på grund av ett avbrott.

[![Denna Ferrari blev oanvändbar eftersom någon försökte uppgradera den under jord där det inte finns någon mobiltäckning](../../../../../translated_images/sv/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

För att MQTT ska hantera en förlust av anslutning måste enhetens och serverns kod vara ansvariga för att säkerställa meddelandeleverans om det behövs, till exempel genom att kräva att alla skickade meddelanden besvaras med ytterligare meddelanden på ett svarstema, och om inte, köas de manuellt för att spelas upp senare.

## Kommandon

Kommandon är meddelanden som skickas från molnet till en enhet och instruerar den att göra något. Oftast innebär detta att ge någon form av output via en aktor, men det kan vara en instruktion för själva enheten, som att starta om eller samla in extra telemetri och returnera den som ett svar på kommandot.

![En internetansluten termostat som tar emot ett kommando för att slå på värmen](../../../../../translated_images/sv/commands.d6c06bbbb3a02cce.webp)

En termostat kan ta emot ett kommando från molnet för att slå på värmen. Baserat på telemetridata från alla sensorer har molntjänsten beslutat att värmen ska vara på, så den skickar det relevanta kommandot.

### Skicka kommandon till MQTT-mäklaren

Nästa steg för vårt internetstyrda nattljus är att serverkoden skickar ett kommando tillbaka till IoT-enheten för att styra ljuset baserat på de ljusnivåer den känner av.

1. Öppna serverkoden i VS Code.

1. Lägg till följande rad efter deklarationen av `client_telemetry_topic` för att definiera vilket ämne kommandon ska skickas till:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Lägg till följande kod i slutet av funktionen `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Detta skickar ett JSON-meddelande till kommandotemat med värdet `led_on` satt till true eller false beroende på om ljuset är mindre än 300 eller inte. Om ljuset är mindre än 300 skickas true för att instruera enheten att slå på LED-lampan.

1. Kör koden som tidigare.

1. Justera ljusnivåerna som detekteras av din fysiska eller virtuella enhet. Mottagna meddelanden och skickade kommandon kommer att skrivas ut i terminalen:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetrin och kommandona skickas på ett enda tema vardera. Detta innebär att telemetri från flera enheter kommer att visas på samma telemetritema, och kommandon till flera enheter kommer att visas på samma kommandotema. Om du ville skicka ett kommando till en specifik enhet kan du använda flera teman, namngivna med ett unikt enhets-ID, som `/commands/device1`, `/commands/device2`. På så sätt kan en enhet lyssna på meddelanden som bara är avsedda för just den enheten.

> 💁 Du kan hitta denna kod i mappen [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Hantera kommandon på IoT-enheten

Nu när kommandon skickas från servern kan du lägga till kod på IoT-enheten för att hantera dem och styra LED-lampan.

Följ relevant steg nedan för att lyssna på kommandon från MQTT-mäklaren:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Enkortsdator - Raspberry Pi/Virtual IoT-enhet](single-board-computer-commands.md)

När denna kod är skriven och körs, experimentera med att ändra ljusnivåer. Titta på utdata från servern och enheten, och observera LED-lampan när du ändrar ljusnivåerna.

### Förlust av anslutning

Vad ska en molntjänst göra om den behöver skicka ett kommando till en IoT-enhet som är offline? Återigen, svaret är att det beror på.

Om det senaste kommandot åsidosätter ett tidigare kan de tidigare förmodligen ignoreras. Om en molntjänst skickar ett kommando för att slå på värmen och sedan skickar ett kommando för att stänga av den, kan kommandot för att slå på ignoreras och inte skickas igen.

Om kommandona behöver bearbetas i ordning, som att flytta en robotarm uppåt och sedan stänga en gripare, måste de skickas i ordning när anslutningen återställs.

✅ Hur kan enhetens eller serverns kod säkerställa att kommandon alltid skickas och hanteras i rätt ordning över MQTT om det behövs?

---

## 🚀 Utmaning

Utmaningen i de senaste tre lektionerna var att lista så många IoT-enheter som du kan hitta i ditt hem, skola eller arbetsplats och avgöra om de är byggda kring mikrokontroller eller enkortsdatorer, eller till och med en blandning av båda, och fundera på vilka sensorer och aktorer de använder.
För dessa enheter, fundera på vilka meddelanden de kan skicka eller ta emot. Vilken telemetri skickar de? Vilka meddelanden eller kommandon kan de ta emot? Tror du att de är säkra?

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Granskning & Självstudier

Läs mer om MQTT på [MQTT Wikipedia-sidan](https://wikipedia.org/wiki/MQTT).

Prova att köra en MQTT-broker själv med [Mosquitto](https://www.mosquitto.org) och anslut till den från din IoT-enhet och serverkod.

> 💁 Tips - som standard tillåter Mosquitto inte anonyma anslutningar (det vill säga anslutningar utan användarnamn och lösenord), och tillåter inte anslutningar från andra datorer än den det körs på.  
> Du kan lösa detta med en [`mosquitto.conf` konfigurationsfil](https://www.mosquitto.org/man/mosquitto-conf-5.html) med följande:  
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Uppgift

[Jämför och kontrastera MQTT med andra kommunikationsprotokoll](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.