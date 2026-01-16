<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-28T12:10:57+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "sl"
}
-->
# Sproži zaznavanje kakovosti sadja s senzorjem

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.jpg)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Uvod

IoT aplikacija ni zgolj ena naprava, ki zajema podatke in jih pošilja v oblak. Pogosto gre za več naprav, ki sodelujejo pri zajemanju podatkov iz fizičnega sveta s pomočjo senzorjev, sprejemanju odločitev na podlagi teh podatkov ter interakciji nazaj s fizičnim svetom prek aktuatorjev ali vizualizacij.

V tej lekciji boste izvedeli več o načrtovanju kompleksnih IoT aplikacij, vključevanju več senzorjev, več oblačnih storitev za analizo in shranjevanje podatkov ter prikazovanju odzivov prek aktuatorja. Naučili se boste, kako zasnovati prototip sistema za nadzor kakovosti sadja, vključno z uporabo senzorjev bližine za sprožitev IoT aplikacije ter kakšna bi bila arhitektura tega prototipa.

V tej lekciji bomo obravnavali:

* [Načrtovanje kompleksnih IoT aplikacij](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Oblikovanje sistema za nadzor kakovosti sadja](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Sprožitev preverjanja kakovosti sadja s senzorjem](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Podatki, uporabljeni za detektor kakovosti sadja](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Uporaba razvojnih naprav za simulacijo več IoT naprav](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Prehod v produkcijo](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 To je zadnja lekcija v tem projektu, zato po zaključku te lekcije in naloge ne pozabite počistiti svojih oblačnih storitev. Te storitve boste potrebovali za dokončanje naloge, zato se prepričajte, da jo najprej dokončate.
>
> Če je potrebno, si oglejte [vodnik za čiščenje projekta](../../../clean-up.md) za navodila, kako to storiti.

## Načrtovanje kompleksnih IoT aplikacij

IoT aplikacije so sestavljene iz številnih komponent, vključno z različnimi napravami in internetnimi storitvami.

IoT aplikacije lahko opišemo kot *stvari* (naprave), ki pošiljajo podatke, ki ustvarjajo *vpoglede*. Ti *vpogledi* ustvarjajo *dejanja* za izboljšanje poslovanja ali procesov. Primer je motor (stvar), ki pošilja podatke o temperaturi. Ti podatki se uporabljajo za oceno, ali motor deluje po pričakovanjih (vpogled). Vpogled se nato uporabi za proaktivno določanje prednostnega vzdrževanja motorja (dejanje).

* Različne stvari zbirajo različne vrste podatkov.
* IoT storitve omogočajo vpoglede v te podatke, včasih jih dopolnjujejo z dodatnimi viri podatkov.
* Ti vpogledi vodijo do dejanj, vključno z nadzorom aktuatorjev v napravah ali vizualizacijo podatkov.

### Referenčna IoT arhitektura

![Referenčna IoT arhitektura](../../../../../translated_images/sl/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.png)

Zgornji diagram prikazuje referenčno IoT arhitekturo.

> 🎓 *Referenčna arhitektura* je primer arhitekture, ki jo lahko uporabite kot referenco pri načrtovanju novih sistemov. V tem primeru, če bi gradili nov IoT sistem, lahko sledite referenčni arhitekturi in po potrebi zamenjate svoje naprave in storitve.

* **Stvari** so naprave, ki zbirajo podatke s senzorjev, morda sodelujejo z robnimi storitvami za interpretacijo teh podatkov, kot so klasifikatorji slik za interpretacijo slikovnih podatkov. Podatki iz naprav se pošiljajo v IoT storitev.
* **Vpogledi** izhajajo iz brezstrežnih aplikacij ali iz analize shranjenih podatkov.
* **Dejanja** so lahko ukazi, poslani napravam, ali vizualizacija podatkov, ki omogoča ljudem sprejemanje odločitev.

![Referenčna IoT arhitektura](../../../../../translated_images/sl/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.png)

Zgornji diagram prikazuje nekatere komponente in storitve, obravnavane v teh lekcijah, ter kako se povezujejo v referenčni IoT arhitekturi.

* **Stvari** - napisali ste kodo za naprave za zajemanje podatkov s senzorjev in analizo slik z uporabo Custom Vision, ki deluje tako v oblaku kot na robni napravi. Ti podatki so bili poslani v IoT Hub.
* **Vpogledi** - uporabili ste Azure Functions za odzivanje na sporočila, poslana v IoT Hub, in shranjevanje podatkov za kasnejšo analizo v Azure Storage.
* **Dejanja** - nadzorovali ste aktuatorje na podlagi odločitev, sprejetih v oblaku, in ukazov, poslanih napravam, ter vizualizirali podatke z uporabo Azure Maps.

✅ Razmislite o drugih IoT napravah, ki ste jih uporabljali, kot so pametni gospodinjski aparati. Katere so stvari, vpogledi in dejanja, povezana s to napravo in njeno programsko opremo?

Ta vzorec je mogoče razširiti na poljubno velikost, dodajati več naprav in več storitev.

### Podatki in varnost

Pri definiranju arhitekture vašega sistema morate nenehno razmišljati o podatkih in varnosti.

* Katere podatke vaša naprava pošilja in prejema?
* Kako naj bodo ti podatki zaščiteni in varovani?
* Kako naj bo nadzorovan dostop do naprave in oblačne storitve?

✅ Razmislite o varnosti podatkov katere koli IoT naprave, ki jo imate. Koliko teh podatkov je osebnih in bi jih bilo treba hraniti zasebno, tako med prenosom kot med shranjevanjem? Katere podatke ne bi smeli shranjevati?

## Oblikovanje sistema za nadzor kakovosti sadja

Zdaj vzemimo to idejo o stvareh, vpogledih in dejanjih ter jo uporabimo za naš detektor kakovosti sadja, da oblikujemo večjo aplikacijo od začetka do konca.

Predstavljajte si, da ste dobili nalogo izdelati detektor kakovosti sadja za uporabo v predelovalnem obratu. Sadje potuje po sistemu tekočega traku, kjer trenutno zaposleni ročno preverjajo sadje in odstranjujejo nezrelo sadje, ko prispe. Da bi zmanjšali stroške, želi lastnik obrata avtomatiziran sistem.

✅ Eden od trendov z vzponom IoT (in tehnologije na splošno) je, da se ročna dela nadomeščajo s stroji. Raziskujte: Koliko delovnih mest naj bi bilo izgubljenih zaradi IoT? Koliko novih delovnih mest bo ustvarjenih pri gradnji IoT naprav?

Potrebujete sistem, kjer se sadje zazna, ko prispe na tekoči trak, nato se fotografira in preveri z AI modelom, ki deluje na robu. Rezultati se nato pošljejo v oblak za shranjevanje, in če je sadje nezrelo, se sproži obvestilo, da se nezrelo sadje odstrani.

|   |   |
| - | - |
| **Stvari** | Detektor za sadje, ki prispe na tekoči trak<br>Kamera za fotografiranje in klasifikacijo sadja<br>Robna naprava, ki izvaja klasifikator<br>Naprava za obveščanje o nezrelem sadju |
| **Vpogledi** | Odločitev za preverjanje zrelosti sadja<br>Shranjevanje rezultatov klasifikacije zrelosti<br>Določitev potrebe po opozorilu o nezrelem sadju |
| **Dejanja** | Pošiljanje ukaza napravi za fotografiranje sadja in preverjanje z klasifikatorjem slik<br>Pošiljanje ukaza napravi za opozorilo, da je sadje nezrelo |

### Prototipiranje vaše aplikacije

![Referenčna IoT arhitektura za preverjanje kakovosti sadja](../../../../../translated_images/sl/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.png)

Zgornji diagram prikazuje referenčno arhitekturo za to prototipno aplikacijo.

* IoT naprava s senzorjem bližine zazna prihod sadja. To pošlje sporočilo v oblak, da je sadje zaznano.
* Brezstrežna aplikacija v oblaku pošlje ukaz drugi napravi, da fotografira in klasificira sliko.
* IoT naprava s kamero posname sliko in jo pošlje klasifikatorju slik, ki deluje na robu. Rezultati se nato pošljejo v oblak.
* Brezstrežna aplikacija v oblaku shrani te informacije za kasnejšo analizo, da se ugotovi, kakšen odstotek sadja je nezrelega. Če je sadje nezrelo, pošlje ukaz drugi IoT napravi, da opozori delavce v tovarni o nezrelem sadju prek LED diode.

> 💁 Celotna IoT aplikacija bi lahko bila izvedena kot ena naprava, z vso logiko za začetek klasifikacije slik in nadzor LED diode vgrajeno. Lahko bi uporabljala IoT Hub zgolj za sledenje številu zaznanih nezrelih sadežev in konfiguracijo naprave. V tej lekciji je razširjena, da pokaže koncepte za velike IoT aplikacije.

Za prototip boste vse to izvedli na eni napravi. Če uporabljate mikrokrmilnik, boste uporabili ločeno robno napravo za izvajanje klasifikatorja slik. Večino stvari, ki jih potrebujete za gradnjo, ste se že naučili.

## Sprožitev preverjanja kakovosti sadja s senzorjem

IoT naprava potrebuje nekakšen sprožilec, ki označuje, kdaj je sadje pripravljeno za klasifikacijo. Eden od sprožilcev za to bi bil merjenje, kdaj je sadje na pravem mestu na tekočem traku, z merjenjem razdalje do senzorja.

![Senzorji bližine pošiljajo laserske žarke na predmete, kot so banane, in merijo čas, ki ga žarek potrebuje, da se odbije nazaj](../../../../../translated_images/sl/proximity-sensor.f5cd752c77fb62fe.webp)

Senzorji bližine se lahko uporabljajo za merjenje razdalje med senzorjem in predmetom. Običajno oddajajo žarek elektromagnetnega sevanja, kot je laserski žarek ali infrardeča svetloba, nato zaznajo sevanje, ki se odbije od predmeta. Čas med oddajo laserskega žarka in signalom, ki se odbije nazaj, se lahko uporabi za izračun razdalje do senzorja.

> 💁 Verjetno ste že uporabljali senzorje bližine, ne da bi se tega zavedali. Večina pametnih telefonov med klicem izklopi zaslon, ko jih držite ob ušesu, da prepreči nenamerno prekinitev klica z ušesno mečico. To deluje s senzorjem bližine, ki zazna predmet blizu zaslona med klicem in onemogoči funkcije na dotik, dokler telefon ni na določeni razdalji.

### Naloga - sprožitev zaznavanja kakovosti sadja z razdaljnim senzorjem

Sledite ustreznemu vodniku za uporabo senzorja bližine za zaznavanje predmeta z vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Enoboardni računalnik - Raspberry Pi](pi-proximity.md)
* [Enoboardni računalnik - Virtualna naprava](virtual-device-proximity.md)

## Podatki, uporabljeni za detektor kakovosti sadja

Prototip detektorja sadja ima več komponent, ki medsebojno komunicirajo.

![Komponente, ki medsebojno komunicirajo](../../../../../translated_images/sl/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.png)

* Senzor bližine meri razdaljo do kosa sadja in jo pošilja v IoT Hub
* Ukaz za nadzor kamere prihaja iz IoT Hub do naprave s kamero
* Rezultati klasifikacije slik se pošiljajo v IoT Hub
* Ukaz za nadzor LED diode za opozorilo o nezrelem sadju se pošilja iz IoT Hub do naprave z LED diodo

Dobro je, da vnaprej definirate strukturo teh sporočil, preden zgradite aplikacijo.

> 💁 Skoraj vsak izkušen razvijalec se je v svoji karieri vsaj enkrat soočil z dolgotrajnim iskanjem napak, ki jih povzročajo razlike med podatki, ki se pošiljajo, in pričakovanji.

Na primer - če pošiljate informacije o temperaturi, kako bi definirali JSON? Lahko bi imeli polje z imenom `temperature`, ali pa bi uporabili običajno okrajšavo `temp`.

```json
{
    "temperature": 20.7
}
```

v primerjavi z:

```json
{
    "temp": 20.7
}
```

Prav tako morate upoštevati enote - ali je temperatura v °C ali °F? Če merite temperaturo z napravo za potrošnike in ti spremenijo prikazne enote, morate zagotoviti, da enote, poslane v oblak, ostanejo dosledne.

✅ Raziskujte: Kako so težave z enotami povzročile strmoglavljenje Mars Climate Orbiterja, vrednega 125 milijonov dolarjev?

Razmislite o podatkih, ki se pošiljajo za detektor kakovosti sadja. Kako bi definirali vsako sporočilo? Kje bi analizirali podatke in sprejemali odločitve o tem, katere podatke poslati?

Na primer - sprožitev klasifikacije slik z uporabo senzorja bližine. IoT naprava meri razdaljo, vendar kje se sprejme odločitev? Ali naprava odloči, da je sadje dovolj blizu, in pošlje sporočilo IoT Hub, da sproži klasifikacijo? Ali pa pošlje meritve razdalje in pusti IoT Hub, da odloči?

Odgovor na takšna vprašanja je - odvisno. Vsak primer uporabe je drugačen, zato kot IoT razvijalec morate razumeti sistem, ki ga gradite, kako se uporablja in podatke, ki jih zaznava.

* Če odločitev sprejme IoT Hub, morate poslati več meritev razdalje.
* Če pošljete preveč sporočil, se povečajo stroški IoT Hub in količina pasovne širine, ki jo potrebujejo vaše IoT naprave (zlasti v tovarni z milijoni naprav). Prav tako lahko upočasni vašo napravo.
* Če odločitev sprejmete na napravi, morate zagotoviti način za konfiguracijo naprave za fino nastavitev stroja.

## Uporaba razvojnih naprav za simulacijo več IoT naprav

Za izdelavo vašega prototipa boste potrebovali vaš IoT razvojni komplet, da deluje kot več naprav, pošilja telemetrijo in se odziva na ukaze.

### Simulacija več IoT naprav na Raspberry Pi ali virtualni IoT strojni opremi

Pri uporabi enoboardnega računalnika, kot je Raspberry Pi, lahko hkrati izvajate več aplikacij. To pomeni, da lahko simulirate več IoT naprav z ustvarjanjem več aplikacij, po eno za vsako 'IoT napravo'. Na primer, vsako napravo lahko implementirate kot ločeno Python datoteko in jih izvajate v različnih terminalskih sejah.
💁 Zavedajte se, da nekatera strojna oprema ne bo delovala, če jo hkrati uporabljajo več aplikacij.
### Simulacija več naprav na mikrokrmilniku

Mikrokrmilnike je težje simulirati z več napravami. Za razliko od enoploščnih računalnikov ne morete hkrati poganjati več aplikacij; vso logiko za ločene IoT naprave morate vključiti v eno samo aplikacijo.

Nekaj predlogov, kako si olajšati ta proces:

* Ustvarite enega ali več razredov za vsako IoT napravo – na primer razrede z imeni `DistanceSensor`, `ClassifierCamera`, `LEDController`. Vsak razred lahko ima svoje metode `setup` in `loop`, ki jih kličejo glavne funkcije `setup` in `loop`.
* Ukaze obdelujte na enem mestu in jih po potrebi usmerite v ustrezen razred naprave.
* V glavni funkciji `loop` boste morali upoštevati časovne zahteve za vsako napravo. Na primer, če imate razred naprave, ki mora obdelovati vsakih 10 sekund, in drugega, ki mora obdelovati vsako sekundo, uporabite v glavni funkciji `loop` zamik 1 sekunde. Vsak klic funkcije `loop` sproži ustrezno kodo za napravo, ki mora obdelovati vsako sekundo, in uporabite števec za štetje zank, da obdelate drugo napravo, ko števec doseže 10 (nato števec ponastavite).

## Prehod v produkcijo

Prototip bo osnova za končni produkcijski sistem. Nekatere razlike, ko preidete v produkcijo, so:

* Ojačane komponente – uporaba strojne opreme, zasnovane za vzdrževanje hrupa, toplote, vibracij in obremenitev v tovarni.
* Uporaba notranje komunikacije – nekateri deli bi komunicirali neposredno, s čimer bi se izognili povezavi v oblak, podatke pa bi pošiljali v oblak le za shranjevanje. Kako se to izvede, je odvisno od postavitve tovarne, bodisi z neposredno komunikacijo bodisi z izvajanjem dela IoT storitve na robu z uporabo prehodne naprave.
* Možnosti konfiguracije – vsaka tovarna in primer uporabe sta različna, zato mora biti strojna oprema nastavljiva. Na primer, senzor bližine bi moral zaznavati različne vrste sadja na različnih razdaljah. Namesto da bi razdaljo za sprožitev klasifikacije trdo kodirali, bi želeli, da je to nastavljivo prek oblaka, na primer z uporabo dvojčka naprave.
* Avtomatizirano odstranjevanje sadja – namesto LED lučke, ki opozarja, da je sadje nezrelo, bi avtomatizirane naprave to sadje odstranile.

✅ Raziskujte: Na kakšne druge načine bi se produkcijske naprave razlikovale od razvojnih kompletov?

---

## 🚀 Izziv

V tej lekciji ste spoznali nekaj konceptov, ki jih morate poznati za arhitekturo IoT sistema. Spomnite se prejšnjih projektov. Kako se ti vključujejo v referenčno arhitekturo, prikazano zgoraj?

Izberite enega od dosedanjih projektov in razmislite o zasnovi bolj zapletene rešitve, ki združuje več zmogljivosti, kot so bile obravnavane v projektih. Narišite arhitekturo in razmislite o vseh napravah in storitvah, ki bi jih potrebovali.

Na primer – naprava za sledenje vozilom, ki združuje GPS s senzorji za spremljanje stvari, kot so temperature v hladilnem tovornjaku, časi vklopa in izklopa motorja ter identiteta voznika. Katere naprave so vključene, katere storitve so potrebne, kateri podatki se prenašajo in kakšni so varnostni in zasebnostni vidiki?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Pregled in samostojno učenje

* Preberite več o arhitekturi IoT v [dokumentaciji referenčne arhitekture Azure IoT na Microsoft Docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Preberite več o dvojčkih naprav v [dokumentaciji o razumevanju in uporabi dvojčkov naprav v IoT Hub na Microsoft Docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Preberite o OPC-UA, komunikacijskem protokolu med stroji, ki se uporablja v industrijski avtomatizaciji, na [strani o OPC-UA na Wikipediji](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Naloga

[Zgradite detektor kakovosti sadja](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da se zavedate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.