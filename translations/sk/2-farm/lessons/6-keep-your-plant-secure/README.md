<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-28T11:13:01+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "sk"
}
-->
# Udržujte svoju rastlinu v bezpečí

![Prehľad tejto lekcie v sketchnote](../../../../../translated_images/sk/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Úvod

V posledných lekciách ste vytvorili IoT zariadenie na monitorovanie pôdy a pripojili ho ku cloudu. Ale čo ak by hackeri pracujúci pre konkurenčného farmára získali kontrolu nad vašimi IoT zariadeniami? Čo ak by posielali vysoké hodnoty vlhkosti pôdy, aby vaše rastliny nikdy neboli zalievané, alebo zapli zavlažovací systém, ktorý by bežal neustále, čím by vaše rastliny zahynuli kvôli nadmernému zalievaniu a spôsobili by vám vysoké náklady na vodu?

V tejto lekcii sa naučíte, ako zabezpečiť IoT zariadenia. Keďže ide o poslednú lekciu tohto projektu, naučíte sa tiež, ako vyčistiť cloudové zdroje, čím znížite potenciálne náklady.

V tejto lekcii sa budeme venovať:

* [Prečo je potrebné zabezpečiť IoT zariadenia?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptografia](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Zabezpečenie IoT zariadení](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generovanie a použitie X.509 certifikátu](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Toto je posledná lekcia v tomto projekte, takže po dokončení tejto lekcie a úlohy nezabudnite vyčistiť svoje cloudové služby. Služby budete potrebovať na dokončenie úlohy, takže sa uistite, že ju najskôr dokončíte.
>
> Ak potrebujete pokyny, pozrite si [príručku na vyčistenie projektu](../../../clean-up.md).

## Prečo je potrebné zabezpečiť IoT zariadenia?

Zabezpečenie IoT zahŕňa zabezpečenie, že iba očakávané zariadenia sa môžu pripojiť k vašej cloudovej IoT službe a posielať jej telemetriu, a že iba vaša cloudová služba môže posielať príkazy vašim zariadeniam. IoT dáta môžu byť tiež osobné, vrátane medicínskych alebo intímnych údajov, takže celá vaša aplikácia musí brať do úvahy bezpečnosť, aby sa zabránilo úniku týchto údajov.

Ak vaša IoT aplikácia nie je zabezpečená, existuje množstvo rizík:

* Falošné zariadenie by mohlo posielať nesprávne údaje, čo by spôsobilo nesprávnu reakciu vašej aplikácie. Napríklad by mohlo posielať neustále vysoké hodnoty vlhkosti pôdy, čo by znamenalo, že váš zavlažovací systém sa nikdy nezapne a vaše rastliny zahynú kvôli nedostatku vody.
* Neoprávnení používatelia by mohli čítať údaje z IoT zariadení vrátane osobných alebo kritických obchodných údajov.
* Hackeri by mohli posielať príkazy na ovládanie zariadenia spôsobom, ktorý by mohol poškodiť zariadenie alebo pripojený hardvér.
* Pripojením k IoT zariadeniu by hackeri mohli získať prístup k ďalším sieťam a získať prístup k súkromným systémom.
* Zlomyseľní používatelia by mohli získať osobné údaje a použiť ich na vydieranie.

Toto sú scenáre z reálneho sveta, ktoré sa dejú neustále. Niektoré príklady boli uvedené v predchádzajúcich lekciách, ale tu sú ďalšie:

* V roku 2018 hackeri použili otvorený WiFi prístupový bod na termostate akvária, aby získali prístup k sieti kasína a ukradli údaje. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* V roku 2016 Mirai Botnet spustil útok odmietnutia služby proti Dyn, poskytovateľovi internetových služieb, čím znefunkčnil veľké časti internetu. Tento botnet použil malvér na pripojenie k IoT zariadeniam, ako sú DVR a kamery, ktoré používali predvolené používateľské mená a heslá, a odtiaľ spustil útok. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys mali databázu používateľov ich pripojených hračiek CloudPets verejne dostupnú na internete. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava označovala bežcov, ktorých ste prebehli, a ukazovala ich trasy, čo umožnilo cudzím ľuďom efektívne vidieť, kde bývate. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Urobte si výskum: Vyhľadajte ďalšie príklady hackov IoT a narušení údajov IoT, najmä pri osobných predmetoch, ako sú internetom pripojené zubné kefky alebo váhy. Premýšľajte o dopade týchto hackov na obete alebo zákazníkov.

> 💁 Bezpečnosť je obrovská téma a táto lekcia sa dotkne iba niektorých základov okolo pripojenia vášho zariadenia ku cloudu. Medzi témy, ktoré nebudú pokryté, patrí monitorovanie zmien údajov počas prenosu, hackovanie zariadení priamo alebo zmeny konfigurácií zariadení. Hackovanie IoT je takou hrozbou, že boli vyvinuté nástroje ako [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Tieto nástroje sú podobné antivírusovým a bezpečnostným nástrojom, ktoré môžete mať na svojom počítači, len sú navrhnuté pre malé, nízko výkonné IoT zariadenia.

## Kryptografia

Keď sa zariadenie pripojí k IoT službe, používa ID na identifikáciu. Problém je, že toto ID môže byť skopírované - hacker by mohol nastaviť škodlivé zariadenie, ktoré používa rovnaké ID ako skutočné zariadenie, ale posiela falošné údaje.

![Platné aj škodlivé zariadenia môžu používať rovnaké ID na posielanie telemetrie](../../../../../translated_images/sk/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

Riešením je konvertovať posielané údaje do zašifrovanej podoby pomocou hodnoty, ktorá je známa iba zariadeniu a cloudu. Tento proces sa nazýva *šifrovanie* a hodnota použitá na šifrovanie údajov sa nazýva *šifrovací kľúč*.

![Ak sa použije šifrovanie, budú akceptované iba zašifrované správy, ostatné budú odmietnuté](../../../../../translated_images/sk/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

Cloudová služba potom môže údaje konvertovať späť do čitateľnej podoby pomocou procesu nazývaného *dešifrovanie*, buď pomocou rovnakého šifrovacieho kľúča, alebo *dešifrovacieho kľúča*. Ak zašifrovanú správu nie je možné dešifrovať pomocou kľúča, zariadenie bolo hacknuté a správa je odmietnutá.

Technika na šifrovanie a dešifrovanie sa nazýva *kryptografia*.

### Raná kryptografia

Najstaršie typy kryptografie boli substitučné šifry, ktoré siahajú až 3 500 rokov dozadu. Substitučné šifry zahŕňajú nahradenie jedného písmena iným. Napríklad [Caesarova šifra](https://wikipedia.org/wiki/Caesar_cipher) zahŕňa posunutie abecedy o definované množstvo, pričom iba odosielateľ zašifrovanej správy a zamýšľaný príjemca vedia, o koľko písmen sa má posunúť.

[Vigenèrova šifra](https://wikipedia.org/wiki/Vigenère_cipher) to posunula ďalej použitím slov na šifrovanie textu, takže každé písmeno v pôvodnom texte bolo posunuté o iné množstvo, namiesto toho, aby sa vždy posúvalo o rovnaký počet písmen.

Kryptografia sa používala na širokú škálu účelov, ako je ochrana receptu na glazúru hrnčiarov v starovekej Mezopotámii, písanie tajných milostných poznámok v Indii alebo uchovávanie staroegyptských magických zaklínadiel v tajnosti.

### Moderná kryptografia

Moderná kryptografia je oveľa pokročilejšia, čo ju robí ťažšie prelomiteľnou ako skoré metódy. Moderná kryptografia používa komplikovanú matematiku na šifrovanie údajov s príliš veľkým počtom možných kľúčov, aby boli útoky hrubou silou možné.

Kryptografia sa používa na množstvo rôznych spôsobov zabezpečenej komunikácie. Ak čítate túto stránku na GitHube, môžete si všimnúť, že adresa webovej stránky začína *HTTPS*, čo znamená, že komunikácia medzi vaším prehliadačom a webovými servermi GitHubu je zašifrovaná. Ak by niekto dokázal čítať internetovú prevádzku medzi vaším prehliadačom a GitHubom, nemohol by čítať údaje, pretože sú zašifrované. Váš počítač môže dokonca zašifrovať všetky údaje na vašom pevnom disku, takže ak by ho niekto ukradol, nemohol by čítať žiadne vaše údaje bez vášho hesla.

> 🎓 HTTPS znamená HyperText Transfer Protocol **Secure**

Bohužiaľ, nie všetko je zabezpečené. Niektoré zariadenia nemajú žiadne zabezpečenie, iné sú zabezpečené pomocou ľahko prelomiteľných kľúčov, alebo dokonca všetky zariadenia rovnakého typu používajú rovnaký kľúč. Existujú prípady veľmi osobných IoT zariadení, ktoré majú všetky rovnaké heslo na pripojenie cez WiFi alebo Bluetooth. Ak sa môžete pripojiť k svojmu vlastnému zariadeniu, môžete sa pripojiť aj k zariadeniu niekoho iného. Po pripojení by ste mohli získať prístup k veľmi súkromným údajom alebo mať kontrolu nad ich zariadením.

> 💁 Napriek zložitosti modernej kryptografie a tvrdeniam, že prelomenie šifrovania môže trvať miliardy rokov, vzostup kvantového počítania priniesol možnosť prelomenia všetkých známych šifrovaní v veľmi krátkom čase!

### Symetrické a asymetrické kľúče

Šifrovanie existuje v dvoch typoch - symetrické a asymetrické.

**Symetrické** šifrovanie používa rovnaký kľúč na šifrovanie a dešifrovanie údajov. Odosielateľ aj príjemca musia poznať rovnaký kľúč. Toto je najmenej bezpečný typ, pretože kľúč musí byť nejako zdieľaný. Aby odosielateľ mohol poslať zašifrovanú správu príjemcovi, odosielateľ musí najskôr poslať príjemcovi kľúč.

![Symetrické šifrovanie používa rovnaký kľúč na šifrovanie a dešifrovanie správy](../../../../../translated_images/sk/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Ak je kľúč ukradnutý počas prenosu, alebo je odosielateľ alebo príjemca hacknutý a kľúč je nájdený, šifrovanie môže byť prelomené.

![Symetrické šifrovanie je bezpečné iba v prípade, že hacker nezíska kľúč - ak áno, môže zachytiť a dešifrovať správu](../../../../../translated_images/sk/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asymetrické** šifrovanie používa 2 kľúče - šifrovací kľúč a dešifrovací kľúč, označované ako verejný/súkromný pár kľúčov. Verejný kľúč sa používa na šifrovanie správy, ale nemôže byť použitý na jej dešifrovanie, súkromný kľúč sa používa na dešifrovanie správy, ale nemôže byť použitý na jej šifrovanie.

![Asymetrické šifrovanie používa iný kľúč na šifrovanie a dešifrovanie. Šifrovací kľúč je poslaný odosielateľom správ, aby mohli zašifrovať správu pred jej odoslaním príjemcovi, ktorý vlastní kľúče](../../../../../translated_images/sk/send-message-asymmetric.7abe327c62615b8c.webp)

Príjemca zdieľa svoj verejný kľúč a odosielateľ ho používa na šifrovanie správy. Po odoslaní správy ju príjemca dešifruje pomocou svojho súkromného kľúča. Asymetrické šifrovanie je bezpečnejšie, pretože súkromný kľúč je uchovávaný v tajnosti príjemcom a nikdy nie je zdieľaný. Verejný kľúč môže mať ktokoľvek, pretože môže byť použitý iba na šifrovanie správ.

Symetrické šifrovanie je rýchlejšie ako asymetrické šifrovanie, asymetrické je bezpečnejšie. Niektoré systémy používajú oboje - asymetrické šifrovanie na šifrovanie a zdieľanie symetrického kľúča, potom symetrický kľúč na šifrovanie všetkých údajov. Tým sa zabezpečí bezpečnejšie zdieľanie symetrického kľúča medzi odosielateľom a príjemcom a rýchlejšie šifrovanie a dešifrovanie údajov.

## Zabezpečenie IoT zariadení

IoT zariadenia môžu byť zabezpečené pomocou symetrického alebo asymetrického šifrovania. Symetrické je jednoduchšie, ale menej bezpečné.

### Symetrické kľúče

Keď ste nastavili svoje IoT zariadenie na interakciu s IoT Hubom, použili ste reťazec pripojenia. Príklad reťazca pripojenia je:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Tento reťazec pripojenia pozostáva z troch častí oddelených bodkočiarkami, pričom každá časť je kľúč a hodnota:

| Kľúč | Hodnota | Popis |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL IoT Hubu |
| DeviceId | `soil-moisture-sensor` | Jedinečné ID zariadenia |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Symetrický kľúč známy zariadeniu a IoT Hubu |

Posledná časť tohto reťazca pripojenia, `SharedAccessKey`, je symetrický kľúč známy zariadeniu aj IoT Hubu. Tento kľúč sa nikdy neposiela zo zariadenia do cloudu ani z cloudu do zariadenia. Namiesto toho sa používa na šifrovanie údajov, ktoré sú posielané alebo prijímané.

✅ Urobte experiment. Čo si myslíte, že sa stane, ak zmeníte časť `SharedAccessKey` v reťazci pripojenia pri pripojení vášho IoT zariadenia? Vyskúšajte to.

Keď sa zariadenie prvýkrát pokúsi pripojiť, pošle token zdieľaného prístupu (SAS) pozostávajúci z URL IoT Hubu, časového razítka, kedy prístupový podpis vyprší (zvyčajne 1 deň od aktuálneho času), a podpisu. Tento podpis pozostáva z
💁 Kvôli času vypršania platnosti musí vaše IoT zariadenie poznať presný čas, ktorý sa zvyčajne získava zo servera [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Ak čas nie je presný, pripojenie zlyhá.
Po pripojení budú všetky údaje odoslané do IoT Hubu zo zariadenia alebo na zariadenie z IoT Hubu šifrované pomocou zdieľaného prístupového kľúča.

✅ Čo si myslíte, že sa stane, ak viaceré zariadenia budú zdieľať rovnaký reťazec pripojenia?

> 💁 Nie je dobrým bezpečnostným postupom ukladať tento kľúč v kóde. Ak by hacker získal váš zdrojový kód, mohol by získať aj váš kľúč. Navyše, pri vydávaní kódu by ste museli pre každý nový kľúč zariadenia kód znova skompilovať. Lepšie je načítať tento kľúč z hardvérového bezpečnostného modulu – čipu na IoT zariadení, ktorý uchováva šifrované hodnoty, ktoré váš kód dokáže prečítať.
>
> Pri učení sa o IoT je často jednoduchšie vložiť kľúč priamo do kódu, ako ste to urobili v predchádzajúcej lekcii, ale musíte zabezpečiť, aby tento kľúč nebol verejne dostupný v systémoch na správu zdrojového kódu.

Zariadenia majú 2 kľúče a 2 zodpovedajúce reťazce pripojenia. To umožňuje rotáciu kľúčov – teda prechod z jedného kľúča na druhý, ak by bol prvý kompromitovaný, a následnú regeneráciu prvého kľúča.

### X.509 certifikáty

Keď používate asymetrické šifrovanie s párom verejného/súkromného kľúča, musíte poskytnúť svoj verejný kľúč každému, kto vám chce poslať údaje. Problém je, ako môže príjemca vášho kľúča vedieť, že ide skutočne o váš verejný kľúč, a nie o niekoho, kto sa za vás vydáva? Namiesto poskytovania kľúča môžete poskytnúť svoj verejný kľúč v certifikáte, ktorý overila dôveryhodná tretia strana, nazývaná X.509 certifikát.

X.509 certifikáty sú digitálne dokumenty, ktoré obsahujú verejnú časť páru verejného/súkromného kľúča. Zvyčajne ich vydávajú dôveryhodné organizácie nazývané [Certifikačné autority](https://wikipedia.org/wiki/Certificate_authority) (CAs) a digitálne ich podpisujú, aby potvrdili, že kľúč je platný a pochádza od vás. Certifikátu dôverujete a veríte, že verejný kľúč pochádza od osoby, ktorú certifikát uvádza, pretože dôverujete certifikačnej autorite, podobne ako dôverujete pasu alebo vodičskému preukazu, pretože dôverujete krajine, ktorá ich vydala. Certifikáty stoja peniaze, takže si môžete vytvoriť aj „svojpomocne podpísaný“ certifikát, teda certifikát, ktorý si sami vytvoríte a podpíšete, na testovacie účely.

> 💁 Nikdy by ste nemali používať svojpomocne podpísaný certifikát na produkčné vydanie.

Tieto certifikáty obsahujú množstvo polí, vrátane informácií o tom, od koho pochádza verejný kľúč, podrobností o CA, ktorá ho vydala, ako dlho je platný, a samotného verejného kľúča. Pred použitím certifikátu je dobrým zvykom overiť ho kontrolou, či bol podpísaný pôvodnou CA.

✅ Kompletný zoznam polí v certifikáte si môžete prečítať v [Microsoft tutoriáli o pochopení X.509 verejných kľúčových certifikátov](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Pri používaní X.509 certifikátov budú mať odosielateľ aj príjemca svoje vlastné verejné a súkromné kľúče, ako aj X.509 certifikáty obsahujúce verejný kľúč. Následne si vymenia X.509 certifikáty a používajú verejné kľúče na šifrovanie údajov, ktoré posielajú, a svoje súkromné kľúče na dešifrovanie údajov, ktoré prijímajú.

![Namiesto zdieľania verejného kľúča môžete zdieľať certifikát. Používateľ certifikátu môže overiť, že pochádza od vás, kontrolou u certifikačnej autority, ktorá ho podpísala.](../../../../../translated_images/sk/send-message-certificate.9cc576ac1e46b76e.webp)

Jednou z veľkých výhod používania X.509 certifikátov je, že ich možno zdieľať medzi zariadeniami. Môžete vytvoriť jeden certifikát, nahrať ho do IoT Hubu a používať ho pre všetky vaše zariadenia. Každé zariadenie potom potrebuje poznať iba súkromný kľúč na dešifrovanie správ, ktoré prijíma z IoT Hubu.

Certifikát, ktorý vaše zariadenie používa na šifrovanie správ odosielaných do IoT Hubu, je publikovaný spoločnosťou Microsoft. Ide o rovnaký certifikát, ktorý používa mnoho služieb Azure, a niekedy je zabudovaný do SDK.

> 💁 Pamätajte, že verejný kľúč je práve to – verejný. Verejný kľúč Azure možno použiť iba na šifrovanie údajov odosielaných do Azure, nie na ich dešifrovanie, takže ho možno zdieľať kdekoľvek, vrátane zdrojového kódu. Napríklad ho môžete vidieť v [zdrojovom kóde Azure IoT C SDK](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Existuje veľa žargónu spojeného s X.509 certifikátmi. Definície niektorých pojmov, na ktoré môžete naraziť, si môžete prečítať v [Sprievodcovi žargónom X.509 certifikátov pre laikov](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Generovanie a používanie X.509 certifikátu

Kroky na generovanie X.509 certifikátu sú:

1. Vytvorte pár verejného/súkromného kľúča. Jedným z najpoužívanejších algoritmov na generovanie páru verejného/súkromného kľúča je [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

2. Predložte verejný kľúč s pridruženými údajmi na podpis, buď CA, alebo svojpomocne podpísaný.

Azure CLI obsahuje príkazy na vytvorenie novej identity zariadenia v IoT Hub a automatické generovanie páru verejného/súkromného kľúča a vytvorenie svojpomocne podpísaného certifikátu.

> 💁 Ak chcete vidieť kroky podrobne, namiesto použitia Azure CLI, môžete si ich pozrieť v [návode na používanie OpenSSL na vytvorenie svojpomocne podpísaných certifikátov v dokumentácii Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Úloha – vytvorte identitu zariadenia pomocou X.509 certifikátu

1. Spustite nasledujúci príkaz na registráciu novej identity zariadenia, automaticky generujúc kľúče a certifikáty:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

    Tento príkaz vytvorí zariadenie s ID `soil-moisture-sensor-x509`, aby sa odlíšilo od identity zariadenia, ktorú ste vytvorili v predchádzajúcej lekcii. Tento príkaz tiež vytvorí 2 súbory v aktuálnom adresári:

    * `soil-moisture-sensor-x509-key.pem` – tento súbor obsahuje súkromný kľúč zariadenia.
    * `soil-moisture-sensor-x509-cert.pem` – toto je súbor X.509 certifikátu zariadenia.

    Tieto súbory uchovávajte v bezpečí! Súbor so súkromným kľúčom by nemal byť verejne dostupný v systémoch na správu zdrojového kódu.

### Úloha – použite X.509 certifikát vo vašom zariadení

Prejdite si príslušného sprievodcu na pripojenie vášho IoT zariadenia ku cloudu pomocou X.509 certifikátu:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Jednodoskový počítač - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Výzva

Existuje viacero spôsobov, ako vytvárať, spravovať a mazať služby Azure, ako sú Resource Groups a IoT Huby. Jedným zo spôsobov je [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – webové rozhranie, ktoré vám poskytuje GUI na správu vašich Azure služieb.

Navštívte [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) a preskúmajte portál. Skúste vytvoriť IoT Hub pomocou portálu a potom ho odstrániť.

**Tip** – pri vytváraní služieb cez portál nemusíte vytvárať Resource Group vopred, môžete ju vytvoriť počas vytvárania služby. Uistite sa, že ju po dokončení odstránite!

Na portáli Azure nájdete množstvo dokumentácie, tutoriálov a sprievodcov v [dokumentácii Azure portálu](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Prehľad a samoštúdium

* Prečítajte si o histórii kryptografie na [stránke História kryptografie na Wikipédii](https://wikipedia.org/wiki/History_of_cryptography).
* Prečítajte si o X.509 certifikátoch na [stránke X.509 na Wikipédii](https://wikipedia.org/wiki/X.509).

## Zadanie

[Postavte nové IoT zariadenie](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.