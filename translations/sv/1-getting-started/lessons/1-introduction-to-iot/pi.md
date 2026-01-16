<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T21:59:07+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "sv"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) är en enkortsdator. Du kan lägga till sensorer och aktuatorer med hjälp av en mängd olika enheter och ekosystem, och för dessa lektioner använder vi ett hårdvaruekosystem som heter [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Du kommer att programmera din Pi och använda Grove-sensorerna med Python.

![En Raspberry Pi 4](../../../../../translated_images/sv/raspberry-pi-4.fd4590d308c3d456.jpg)

## Installation

Om du använder en Raspberry Pi som din IoT-hårdvara har du två alternativ - du kan arbeta igenom alla dessa lektioner och programmera direkt på Pi, eller du kan ansluta till en "headless" Pi och programmera från din dator.

Innan du börjar behöver du också ansluta Grove Base Hat till din Pi.

### Uppgift - installation

Installera Grove Base Hat på din Pi och konfigurera Pi.

1. Anslut Grove Base Hat till din Pi. Uttaget på hatten passar över alla GPIO-stift på Pi och glider hela vägen ner för att sitta stadigt på basen. Den täcker Pi och sitter ovanpå den.

    ![Montering av Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Bestäm hur du vill programmera din Pi och gå till relevant avsnitt nedan:

    * [Arbeta direkt på din Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Fjärråtkomst för att programmera Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Arbeta direkt på din Pi

Om du vill arbeta direkt på din Pi kan du använda desktopversionen av Raspberry Pi OS och installera alla verktyg du behöver.

#### Uppgift - arbeta direkt på din Pi

Konfigurera din Pi för utveckling.

1. Följ instruktionerna i [Raspberry Pi installationsguide](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) för att ställa in din Pi, ansluta den till ett tangentbord/mus/skärm, ansluta den till ditt WiFi- eller Ethernet-nätverk och uppdatera mjukvaran.

För att programmera Pi med Grove-sensorer och aktuatorer behöver du installera en editor för att skriva enhetskoden samt olika bibliotek och verktyg som interagerar med Grove-hårdvaran.

1. När din Pi har startat om, öppna Terminal genom att klicka på **Terminal**-ikonen i toppmenyn eller välj *Meny -> Tillbehör -> Terminal*

1. Kör följande kommando för att säkerställa att operativsystemet och den installerade mjukvaran är uppdaterade:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Kör följande kommandon för att installera alla nödvändiga bibliotek för Grove-hårdvaran:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Detta börjar med att installera Git, tillsammans med Pip för att installera Python-paket.

    En av de kraftfulla funktionerna i Python är möjligheten att installera [Pip-paket](https://pypi.org) - dessa är kodpaket skrivna av andra och publicerade på internet. Du kan installera ett Pip-paket på din dator med ett kommando och sedan använda det paketet i din kod.

    Seeed Grove Python-paketen behöver installeras från källkod. Dessa kommandon klonar repot som innehåller källkoden för detta paket och installerar det lokalt.

    > 💁 Som standard, när du installerar ett paket, är det tillgängligt överallt på din dator, vilket kan leda till problem med paketversioner - till exempel att en applikation beror på en version av ett paket som slutar fungera när du installerar en ny version för en annan applikation. För att undvika detta problem kan du använda en [Python-virtuell miljö](https://docs.python.org/3/library/venv.html), i princip en kopia av Python i en dedikerad mapp, och när du installerar Pip-paket installeras de bara i den mappen. Du kommer inte att använda virtuella miljöer när du använder din Pi. Grove-installationsskriptet installerar Grove Python-paketen globalt, så för att använda en virtuell miljö skulle du behöva ställa in en virtuell miljö och sedan manuellt installera om Grove-paketen i den miljön. Det är enklare att bara använda globala paket, särskilt eftersom många Pi-utvecklare kommer att omformatera ett rent SD-kort för varje projekt.

    Slutligen aktiveras I<sup>2</sup>C-gränssnittet.

1. Starta om Pi antingen via menyn eller genom att köra följande kommando i Terminal:

    ```sh
    sudo reboot
    ```

1. När Pi har startat om, öppna Terminal igen och kör följande kommando för att installera [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - detta är editorn du kommer att använda för att skriva din enhetskod i Python.

    ```sh
    sudo apt install code
    ```

    När detta är installerat kommer VS Code att vara tillgängligt från toppmenyn.

    > 💁 Du är fri att använda vilken Python-IDE eller editor som helst för dessa lektioner om du har ett föredraget verktyg, men lektionerna kommer att ge instruktioner baserade på att använda VS Code.

1. Installera Pylance. Detta är en extension för VS Code som ger stöd för Python-språket. Se [Pylance extension-dokumentationen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) för instruktioner om hur du installerar denna extension i VS Code.

### Fjärråtkomst för att programmera Pi

Istället för att programmera direkt på Pi kan den köras "headless", det vill säga utan att vara ansluten till tangentbord/mus/skärm, och du kan konfigurera och programmera den från din dator med Visual Studio Code.

#### Installera Pi OS

För att programmera fjärrstyrt behöver Pi OS installeras på ett SD-kort.

##### Uppgift - installera Pi OS

Installera det headless Pi OS.

1. Ladda ner **Raspberry Pi Imager** från [Raspberry Pi OS mjukvarusida](https://www.raspberrypi.org/software/) och installera det.

1. Sätt in ett SD-kort i din dator, använd en adapter om det behövs.

1. Starta Raspberry Pi Imager.

1. I Raspberry Pi Imager, välj **CHOOSE OS**-knappen och välj *Raspberry Pi OS (Other)*, följt av *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager med Raspberry Pi OS Lite valt](../../../../../translated_images/sv/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite är en version av Raspberry Pi OS som inte har desktop-UI eller UI-baserade verktyg. Dessa behövs inte för en headless Pi och gör installationen mindre och uppstarten snabbare.

1. Välj **CHOOSE STORAGE**-knappen och välj ditt SD-kort.

1. Starta **Advanced Options** genom att trycka på `Ctrl+Shift+X`. Dessa alternativ tillåter viss förkonfiguration av Raspberry Pi OS innan det skrivs till SD-kortet.

    1. Markera **Enable SSH**-rutan och ställ in ett lösenord för användaren `pi`. Detta är lösenordet du kommer att använda för att logga in på Pi senare.

    1. Om du planerar att ansluta till Pi via WiFi, markera **Configure WiFi**-rutan och ange ditt WiFi SSID och lösenord, samt välj ditt WiFi-land. Du behöver inte göra detta om du kommer att använda en Ethernet-kabel. Se till att nätverket du ansluter till är samma som din dator är ansluten till.

    1. Markera **Set locale settings**-rutan och ställ in ditt land och tidszon.

    1. Välj **SAVE**-knappen.

1. Välj **WRITE**-knappen för att skriva OS till SD-kortet. Om du använder macOS kommer du att bli ombedd att ange ditt lösenord eftersom det underliggande verktyget som skriver diskbilder behöver privilegierad åtkomst.

Operativsystemet kommer att skrivas till SD-kortet, och när det är klart kommer kortet att matas ut av operativsystemet och du kommer att bli meddelad. Ta ut SD-kortet från din dator, sätt in det i Pi, starta Pi och vänta cirka 2 minuter för att den ska starta ordentligt.

#### Anslut till Pi

Nästa steg är att fjärransluta till Pi. Du kan göra detta med `ssh`, som är tillgängligt på macOS, Linux och nyare versioner av Windows.

##### Uppgift - anslut till Pi

Fjärranslut till Pi.

1. Starta en Terminal eller Kommandotolk och ange följande kommando för att ansluta till Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Om du använder Windows med en äldre version som inte har `ssh` installerat kan du använda OpenSSH. Du hittar installationsinstruktionerna i [OpenSSH installationsdokumentation](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Detta bör ansluta till din Pi och fråga efter lösenordet.

    Att kunna hitta datorer på ditt nätverk med `<hostname>.local` är en ganska ny funktion i Linux och Windows. Om du använder Linux eller Windows och får några fel om att värdnamnet inte hittas, måste du installera ytterligare mjukvara för att aktivera ZeroConf-nätverk (även kallat Bonjour av Apple):

    1. Om du använder Linux, installera Avahi med följande kommando:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Om du använder Windows är det enklaste sättet att aktivera ZeroConf att installera [Bonjour Print Services för Windows](http://support.apple.com/kb/DL999). Du kan också installera [iTunes för Windows](https://www.apple.com/itunes/download/) för att få en nyare version av verktyget (som inte är tillgängligt separat).

    > 💁 Om du inte kan ansluta med `raspberrypi.local` kan du använda IP-adressen för din Pi. Se [Raspberry Pi IP-adressdokumentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) för instruktioner om olika sätt att få IP-adressen.

1. Ange lösenordet du ställde in i Raspberry Pi Imager Advanced Options.

#### Konfigurera mjukvara på Pi

När du är ansluten till Pi behöver du säkerställa att operativsystemet är uppdaterat och installera olika bibliotek och verktyg som interagerar med Grove-hårdvaran.

##### Uppgift - konfigurera mjukvara på Pi

Konfigurera den installerade Pi-mjukvaran och installera Grove-biblioteken.

1. Från din `ssh`-session, kör följande kommando för att uppdatera och sedan starta om Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi kommer att uppdateras och startas om. `ssh`-sessionen kommer att avslutas när Pi startas om, så vänta cirka 30 sekunder och anslut igen.

1. Från den återanslutna `ssh`-sessionen, kör följande kommandon för att installera alla nödvändiga bibliotek för Grove-hårdvaran:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Detta börjar med att installera Git, tillsammans med Pip för att installera Python-paket.

    En av de kraftfulla funktionerna i Python är möjligheten att installera [Pip-paket](https://pypi.org) - dessa är kodpaket skrivna av andra och publicerade på internet. Du kan installera ett Pip-paket på din dator med ett kommando och sedan använda det paketet i din kod.

    Seeed Grove Python-paketen behöver installeras från källkod. Dessa kommandon klonar repot som innehåller källkoden för detta paket och installerar det lokalt.

    > 💁 Som standard, när du installerar ett paket, är det tillgängligt överallt på din dator, vilket kan leda till problem med paketversioner - till exempel att en applikation beror på en version av ett paket som slutar fungera när du installerar en ny version för en annan applikation. För att undvika detta problem kan du använda en [Python-virtuell miljö](https://docs.python.org/3/library/venv.html), i princip en kopia av Python i en dedikerad mapp, och när du installerar Pip-paket installeras de bara i den mappen. Du kommer inte att använda virtuella miljöer när du använder din Pi. Grove-installationsskriptet installerar Grove Python-paketen globalt, så för att använda en virtuell miljö skulle du behöva ställa in en virtuell miljö och sedan manuellt installera om Grove-paketen i den miljön. Det är enklare att bara använda globala paket, särskilt eftersom många Pi-utvecklare kommer att omformatera ett rent SD-kort för varje projekt.

    Slutligen aktiveras I<sup>2</sup>C-gränssnittet.

1. Starta om Pi genom att köra följande kommando:

    ```sh
    sudo reboot
    ```

    `ssh`-sessionen kommer att avslutas när Pi startas om. Det finns ingen anledning att ansluta igen.

#### Konfigurera VS Code för fjärråtkomst

När Pi är konfigurerad kan du ansluta till den med Visual Studio Code (VS Code) från din dator - detta är en gratis utvecklartexteditor som du kommer att använda för att skriva din enhetskod i Python.

##### Uppgift - konfigurera VS Code för fjärråtkomst

Installera den nödvändiga mjukvaran och anslut fjärrstyrt till din Pi.

1. Installera VS Code på din dator genom att följa [VS Code-dokumentationen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Följ instruktionerna i [VS Code Remote Development using SSH-dokumentationen](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) för att installera de komponenter som behövs.

1. Följ samma instruktioner för att ansluta VS Code till Pi.

1. När du är ansluten, följ instruktionerna för [hantering av extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) för att installera [Pylance extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) fjärrstyrt på Pi.

## Hello world
Det är traditionellt när man börjar med ett nytt programmeringsspråk eller en ny teknik att skapa en 'Hello World'-applikation – en liten applikation som skriver ut något i stil med texten `"Hello World"` för att visa att alla verktyg är korrekt konfigurerade.

Hello World-appen för Pi kommer att säkerställa att du har Python och Visual Studio Code installerade korrekt.

Denna app kommer att finnas i en mapp som heter `nightlight`, och den kommer att återanvändas med olika kod i senare delar av denna uppgift för att bygga nattlampa-applikationen.

### Uppgift - hello world

Skapa Hello World-appen.

1. Starta VS Code, antingen direkt på Pi eller på din dator och anslut till Pi med hjälp av Remote SSH-tillägget.

1. Starta VS Code-terminalen genom att välja *Terminal -> New Terminal*, eller genom att trycka på `` CTRL+` ``. Den öppnas i hemmakatalogen för användaren `pi`.

1. Kör följande kommandon för att skapa en katalog för din kod och skapa en Python-fil som heter `app.py` i den katalogen:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Öppna denna mapp i VS Code genom att välja *File -> Open...* och välja mappen *nightlight*, klicka sedan på **OK**.

    ![Dialogrutan för att öppna filer i VS Code som visar mappen nightlight](../../../../../translated_images/sv/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Öppna filen `app.py` från VS Code Explorer och lägg till följande kod:

    ```python
    print('Hello World!')
    ```

    Funktionen `print` skriver ut det som skickas till den i konsolen.

1. Från VS Code-terminalen, kör följande kommando för att köra din Python-app:

    ```sh
    python app.py
    ```

    > 💁 Du kan behöva explicit ange `python3` för att köra denna kod om du har Python 2 installerat utöver Python 3 (den senaste versionen). Om du har Python 2 installerat kommer kommandot `python` att använda Python 2 istället för Python 3. Som standard har de senaste versionerna av Raspberry Pi OS endast Python 3 installerat.

    Följande utdata kommer att visas i terminalen:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Du kan hitta denna kod i mappen [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Ditt 'Hello World'-program blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.