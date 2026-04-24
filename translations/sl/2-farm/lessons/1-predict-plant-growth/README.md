## Napovedovanje rasti rastlin z IoT

![Pregled lekcije v obliki sketchnote](../../../../../translated_images/sl/lesson-5.42b234299279d263.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Uvod

Rastline potrebujejo določene stvari za rast - vodo, ogljikov dioksid, hranila, svetlobo in toploto. V tej lekciji se boste naučili, kako izračunati stopnje rasti in zrelosti rastlin z merjenjem temperature zraka.

V tej lekciji bomo obravnavali:

* [Digitalno kmetijstvo](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Zakaj je temperatura pomembna pri kmetovanju?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Merjenje temperature okolja](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Dnevi rastne stopnje (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Izračun GDD z uporabo podatkov senzorja temperature](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitalno kmetijstvo

Digitalno kmetijstvo spreminja način kmetovanja z uporabo orodij za zbiranje, shranjevanje in analizo podatkov s kmetij. Trenutno smo v obdobju, ki ga Svetovni gospodarski forum opisuje kot 'Četrto industrijsko revolucijo', vzpon digitalnega kmetijstva pa je označen kot 'Četrta kmetijska revolucija' ali 'Kmetijstvo 4.0'.

> 🎓 Izraz Digitalno kmetijstvo vključuje tudi celotno 'vrednostno verigo kmetijstva', torej celotno pot od kmetije do mize. Vključuje sledenje kakovosti pridelkov med prevozom in predelavo hrane, sisteme skladiščenja in e-trgovine, celo aplikacije za najem traktorjev!

Te spremembe omogočajo kmetom povečanje pridelka, manjšo uporabo gnojil in pesticidov ter učinkovitejše zalivanje. Čeprav se senzorji in druge naprave primarno uporabljajo v bogatejših državah, se njihova cena počasi znižuje, kar jih naredi dostopnejše v državah v razvoju.

Nekatere tehnike, ki jih omogoča digitalno kmetijstvo, so:

* Merjenje temperature - merjenje temperature omogoča kmetom napovedovanje rasti in zrelosti rastlin.
* Samodejno zalivanje - merjenje vlažnosti tal in vklop namakalnih sistemov, ko so tla preveč suha, namesto časovno določenega zalivanja. Časovno zalivanje lahko vodi do premalo zalitih pridelkov med vročim, suhim obdobjem ali prekomernega zalivanja med dežjem. Z zalivanjem le takrat, ko tla to potrebujejo, lahko kmetje optimizirajo porabo vode.
* Nadzor škodljivcev - kmetje lahko uporabljajo kamere na avtomatiziranih robotih ali dronih za preverjanje škodljivcev, nato pa nanesejo pesticide le tam, kjer so potrebni, kar zmanjša količino uporabljenih pesticidov in zmanjšuje izpiranje pesticidov v lokalne vodne vire.

✅ Raziskujte. Katere druge tehnike se uporabljajo za izboljšanje kmetijskih pridelkov?

> 🎓 Izraz 'Precizno kmetijstvo' se uporablja za opazovanje, merjenje in odzivanje na pridelke na podlagi posameznih polj ali celo delov polja. To vključuje merjenje ravni vode, hranil in škodljivcev ter natančno odzivanje, kot je zalivanje le majhnega dela polja.

## Zakaj je temperatura pomembna pri kmetovanju?

Ko se učimo o rastlinah, se večina učencev nauči o nujnosti vode, svetlobe, ogljikovega dioksida in hranil. Rastline pa potrebujejo tudi toploto za rast - zato rastline cvetijo spomladi, ko se temperatura dvigne, zakaj lahko zvončki ali narcise vzklijejo zgodaj zaradi kratkega toplega obdobja in zakaj so rastlinjaki tako učinkoviti pri spodbujanju rasti rastlin.

> 🎓 Rastlinjaki in topli prostori opravljajo podobno nalogo, vendar z pomembno razliko. Topli prostori se umetno ogrevajo in omogočajo kmetom natančnejše nadzorovanje temperatur, rastlinjaki pa se zanašajo na sonce za toploto, običajno pa je edini nadzor okna ali druge odprtine za odvajanje toplote.

Rastline imajo osnovno ali minimalno temperaturo, optimalno temperaturo in maksimalno temperaturo, vse na podlagi dnevnih povprečnih temperatur.

* Osnovna temperatura - to je minimalna dnevna povprečna temperatura, potrebna za rast rastline.
* Optimalna temperatura - to je najboljša dnevna povprečna temperatura za največjo rast.
* Maksimalna temperatura - to je maksimalna temperatura, ki jo rastlina lahko prenese. Nad to temperaturo rastlina preneha rasti, da bi ohranila vodo in preživela.

> 💁 To so povprečne temperature, izračunane na podlagi dnevnih in nočnih temperatur. Rastline potrebujejo tudi različne temperature podnevi in ponoči, da lahko učinkoviteje fotosintetizirajo in ponoči varčujejo z energijo.

Vsaka vrsta rastline ima različne vrednosti za osnovno, optimalno in maksimalno temperaturo. Zato nekatere rastline uspevajo v vročih državah, druge pa v hladnejših.

✅ Raziskujte. Za rastline, ki jih imate na vrtu, v šoli ali lokalnem parku, preverite, ali lahko najdete osnovno temperaturo.

![Graf, ki prikazuje stopnjo rasti, ki se povečuje z naraščanjem temperature, nato pa upada, ko temperatura postane previsoka](../../../../../translated_images/sl/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Zgornji graf prikazuje primer grafa stopnje rasti glede na temperaturo. Do osnovne temperature ni rasti. Stopnja rasti se povečuje do optimalne temperature, nato pa upada po doseganju vrha. 

Oblika tega grafa se razlikuje od vrste rastline do vrste rastline. Nekatere imajo ostrejše padce nad optimalno temperaturo, druge pa počasnejše povečanje od osnovne do optimalne temperature.

> 💁 Da bi kmet dosegel najboljšo rast, mora poznati tri temperaturne vrednosti in razumeti obliko grafov za rastline, ki jih goji.

Če ima kmet nadzor nad temperaturo, na primer v komercialnem toplogrednem prostoru, lahko optimizira pogoje za svoje rastline. Komercialni toplogredni prostor, ki goji paradižnike, na primer nastavi temperaturo na približno 25°C podnevi in 20°C ponoči, da doseže najhitrejšo rast.

> 🍅 Kombinacija teh temperatur z umetno svetlobo, gnojili in nadzorovanimi ravnmi ogljikovega dioksida omogoča komercialnim pridelovalcem gojenje in žetev skozi vse leto.

## Merjenje temperature okolja

Senzorji temperature se lahko uporabljajo z IoT napravami za merjenje temperature okolja.

### Naloga - merjenje temperature

Sledite ustreznemu vodniku za spremljanje temperatur z uporabo vaše IoT naprave:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Enokartični računalnik - Raspberry Pi](pi-temp.md)
* [Enokartični računalnik - Virtualna naprava](virtual-device-temp.md)

## Dnevi rastne stopnje

Dnevi rastne stopnje (znani tudi kot enote rastne stopnje) so način merjenja rasti rastlin na podlagi temperature. Če ima rastlina dovolj vode, hranil in ogljikovega dioksida, temperatura določa stopnjo rasti.

Dnevi rastne stopnje ali GDD se izračunajo na dan kot povprečna temperatura v stopinjah Celzija za dan nad osnovno temperaturo rastline. Vsaka rastlina potrebuje določeno število GDD za rast, cvetenje ali proizvodnjo in zrelost pridelka. Več GDD na dan, hitreje bo rastlina rasla.

> 🇺🇸 Za Američane se dnevi rastne stopnje lahko izračunajo tudi v stopinjah Fahrenheita. 5 GDD (v Celziju) je enakovredno 9 GDD (v Fahrenheitu).

Celotna formula za GDD je nekoliko zapletena, vendar obstaja poenostavljena enačba, ki se pogosto uporablja kot dobra približek:

![GDD = T max + T min deljeno z 2, vse minus T base](../../../../../translated_images/sl/gdd-calculation.79b3660f9c5757aa.webp)

* **GDD** - to je število dni rastne stopnje
* **T max** - to je dnevna maksimalna temperatura v stopinjah Celzija
* **T min** - to je dnevna minimalna temperatura v stopinjah Celzija
* **T base** - to je osnovna temperatura rastline v stopinjah Celzija

> 💁 Obstajajo različice, ki obravnavajo T max nad 30°C ali T min pod T base, vendar jih bomo za zdaj ignorirali.

### Primer - Koruza 🌽

Odvisno od sorte koruza (ali koruza) potrebuje med 800 in 2.700 GDD za zrelost, z osnovno temperaturo 10°C.

Prvi dan nad osnovno temperaturo so bile izmerjene naslednje temperature:

| Meritev     | Temp °C |
| :---------- | :-----: |
| Maksimalna  | 16      |
| Minimalna   | 12      |

Če te številke vstavimo v naš izračun:

* T max = 16
* T min = 12
* T base = 10

To daje izračun:

![GDD = 16 + 12 deljeno z 2, vse minus 10, kar daje rezultat 4](../../../../../translated_images/sl/gdd-calculation-corn.64a58b7a7afcd0df.webp)

Koruza je prejela 4 GDD tisti dan. Če predpostavimo sorto koruze, ki potrebuje 800 GDD za zrelost, bo potrebovala še 796 GDD, da doseže zrelost.

✅ Raziskujte. Za rastline, ki jih imate na vrtu, v šoli ali lokalnem parku, preverite, ali lahko najdete število GDD, potrebnih za dosego zrelosti ali proizvodnjo pridelka.

## Izračun GDD z uporabo podatkov senzorja temperature

Rastline ne rastejo na fiksne datume - na primer, ne morete posaditi semena in vedeti, da bo rastlina obrodila sadove točno 100 dni kasneje. Namesto tega lahko kmet približno oceni, koliko časa rastlina potrebuje za rast, nato pa dnevno preverja, kdaj so pridelki pripravljeni.

To ima velik vpliv na delo na velikih kmetijah in tveganje, da kmet zamudi pridelke, ki so nepričakovano zgodaj pripravljeni. Z merjenjem temperatur lahko kmet izračuna GDD, ki jih je rastlina prejela, kar mu omogoča preverjanje le blizu pričakovane zrelosti.

Z zbiranjem podatkov o temperaturi z uporabo IoT naprave lahko kmet samodejno prejme obvestilo, ko so rastline blizu zrelosti. Tipična arhitektura za to je, da IoT naprave merijo temperaturo, nato pa te podatke o telemetriji objavijo prek interneta z uporabo nečesa, kot je MQTT. Strežniška koda nato posluša te podatke in jih shrani nekam, na primer v bazo podatkov. To pomeni, da se podatki lahko analizirajo kasneje, na primer nočno opravilo za izračun GDD za dan, seštevanje GDD za vsak pridelek doslej in opozarjanje, če je rastlina blizu zrelosti.

![Podatki o telemetriji se pošljejo na strežnik in nato shranijo v bazo podatkov](../../../../../translated_images/sl/save-telemetry-database.ddc9c6bea0c5ba39.webp)

Strežniška koda lahko podatke tudi dopolni z dodatnimi informacijami. Na primer, IoT naprava lahko objavi identifikator, ki označuje, katera naprava je, strežniška koda pa lahko to uporabi za iskanje lokacije naprave in katere pridelke spremlja. Prav tako lahko doda osnovne podatke, kot je trenutni čas, saj nekatere IoT naprave nimajo potrebne strojne opreme za natančno spremljanje časa ali zahtevajo dodatno kodo za branje trenutnega časa prek interneta.

✅ Zakaj mislite, da imajo različna polja lahko različne temperature?

### Naloga - objavljanje informacij o temperaturi

Sledite ustreznemu vodniku za objavljanje podatkov o temperaturi prek MQTT z uporabo vaše IoT naprave, da jih lahko kasneje analizirate:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Enokartični računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-temp-publish.md)

### Naloga - zajemanje in shranjevanje informacij o temperaturi

Ko IoT naprava objavlja telemetrijo, lahko napišete strežniško kodo za naročanje na te podatke in njihovo shranjevanje. Namesto shranjevanja v bazo podatkov bo strežniška koda podatke shranila v datoteko CSV (Comma Separated Values). Datoteke CSV shranjujejo podatke kot vrstice vrednosti v obliki besedila, pri čemer so posamezne vrednosti ločene z vejico, vsak zapis pa na novi vrstici. So priročen, človeško berljiv in dobro podprt način za shranjevanje podatkov kot datoteko.

Datoteka CSV bo imela dva stolpca - *datum* in *temperatura*. Stolpec *datum* bo nastavljen na trenutni datum in čas, ko je strežnik prejel sporočilo, *temperatura* pa bo iz telemetrijskega sporočila.

1. Ponovite korake iz lekcije 4 za ustvarjanje strežniške kode za naročanje na telemetrijo. Ni vam treba dodajati kode za objavljanje ukazov.

    Koraki za to so:

    * Konfigurirajte in aktivirajte Python Virtual Environment

    * Namestite paho-mqtt pip paket

    * Napišite kodo za poslušanje MQTT sporočil, objavljenih na telemetrijski temi

      > ⚠️ Če potrebujete, se lahko sklicujete na [navodila v lekciji 4 za ustvarjanje Python aplikacije za prejemanje telemetrije](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Poimenujte mapo za ta projekt `temperature-sensor-server`.

1. Poskrbite, da bo `client_name` odražal ta projekt:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Dodajte naslednje uvoze na vrh datoteke, pod obstoječe uvoze:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    To uvozi knjižnico za branje datotek, knjižnico za interakcijo z datotekami CSV in knjižnico za pomoč pri datumih in časih.

1. Dodajte naslednjo kodo pred funkcijo `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Ta koda deklarira nekaj konstant za ime datoteke, v katero bo pisala, in ime stolpčnih naslovov za datoteko CSV. Prva vrstica datoteke CSV tradicionalno vsebuje stolpčne naslove, ločene z vejicami.

    Koda nato preveri, ali datoteka CSV že obstaja. Če ne obstaja, jo ustvari s stolpčnimi naslovi v prvi vrstici.

1. Dodajte naslednjo kodo na konec funkcije `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Ta koda odpre datoteko CSV in na koncu doda novo vrstico. Vrstica vsebuje trenutni datum in čas, formatiran v človeku berljiv format, ter temperaturo, prejeto od IoT naprave. Podatki so shranjeni v [formatu ISO 8601](https://wikipedia.org/wiki/ISO_8601) z časovnim pasom, vendar brez mikrosekund.

1. Zaženite to kodo na enak način kot prej, pri čemer se prepričajte, da vaša IoT naprava pošilja podatke. Datoteka CSV z imenom `temperature.csv` bo ustvarjena v isti mapi. Če jo odprete, boste videli datume/čase in meritve temperature:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Zaženite to kodo za nekaj časa, da zajamete podatke. Idealno bi bilo, da jo zaženete cel dan, da zberete dovolj podatkov za izračun GDD.

    
> 💁 Če uporabljate virtualno IoT napravo, izberite naključni potrditveni okvir in nastavite razpon, da se izognete vedno enaki temperaturi, ko se vrne vrednost temperature.
    ![Izberite naključni potrditveni okvir in nastavite razpon](../../../../../translated_images/sl/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Če želite to izvajati cel dan, morate poskrbeti, da računalnik, na katerem se izvaja vaša strežniška koda, ne bo prešel v stanje spanja, bodisi s spremembo nastavitev porabe energije ali z uporabo nečesa, kot je [ta Python skripta za ohranjanje sistema aktivnega](https://github.com/jaqsparow/keep-system-active).
    
> 💁 To kodo lahko najdete v mapi [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Naloga - izračunajte GDD z uporabo shranjenih podatkov

Ko strežnik zajame podatke o temperaturi, lahko izračunate GDD za rastlino.

Koraki za ročni izračun so:

1. Poiščite osnovno temperaturo za rastlino. Na primer, za jagode je osnovna temperatura 10°C.

1. Iz datoteke `temperature.csv` poiščite najvišjo in najnižjo temperaturo za dan.

1. Uporabite prej podan izračun GDD za izračun GDD.

Na primer, če je najvišja temperatura dneva 25°C, najnižja pa 12°C:

![GDD = 25 + 12 deljeno z 2, nato odštejte 10 od rezultata, kar daje 8.5](../../../../../translated_images/sl/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Torej so jagode prejele **8.5** GDD. Jagode potrebujejo približno 250 GDD, da obrodijo sadove, tako da bo še nekaj časa trajalo.

---

## 🚀 Izziv

Rastline potrebujejo več kot le toploto za rast. Kaj še potrebujejo?

Za te potrebe poiščite, ali obstajajo senzorji, ki jih lahko merijo. Kaj pa aktuatorji za nadzor teh ravni? Kako bi sestavili eno ali več IoT naprav za optimizacijo rasti rastlin?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Pregled in samostojno učenje

* Preberite več o digitalnem kmetijstvu na [strani Wikipedia o digitalnem kmetijstvu](https://wikipedia.org/wiki/Digital_agriculture). Prav tako preberite več o preciznem kmetijstvu na [strani Wikipedia o preciznem kmetijstvu](https://wikipedia.org/wiki/Precision_agriculture).
* Celoten izračun rastnih stopinj je bolj zapleten kot poenostavljen, ki je podan tukaj. Preberite več o bolj zapleteni enačbi in kako ravnati s temperaturami pod osnovno vrednostjo na [strani Wikipedia o rastnih stopinjah](https://wikipedia.org/wiki/Growing_degree-day).
* Hrana bi lahko postala redka v prihodnosti, če bomo še naprej uporabljali iste metode kmetovanja. Naučite se več o visokotehnoloških kmetijskih tehnikah v tem [videu o visokotehnoloških kmetijah prihodnosti na YouTubu](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Naloga

[Vizualizirajte podatke GDD z uporabo Jupyter Notebooka](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.