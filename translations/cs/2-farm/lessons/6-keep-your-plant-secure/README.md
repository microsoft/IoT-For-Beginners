<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-27T23:05:35+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "cs"
}
-->
# Udržujte svou rostlinu v bezpečí

![Přehled lekce ve formě sketchnote](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.cs.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

## Kvíz před přednáškou

[Kvíz před přednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Úvod

V posledních několika lekcích jste vytvořili IoT zařízení pro monitorování půdy a připojili ho ke cloudu. Ale co kdyby hackeři pracující pro konkurenčního farmáře získali kontrolu nad vašimi IoT zařízeními? Co kdyby posílali falešné údaje o vysoké vlhkosti půdy, takže by vaše rostliny nikdy nebyly zalévány, nebo zapnuli zavlažovací systém, aby běžel neustále, což by vedlo k přemokření rostlin a stálo vás malé jmění za vodu?

V této lekci se naučíte, jak zabezpečit IoT zařízení. Jelikož se jedná o poslední lekci tohoto projektu, naučíte se také, jak vyčistit cloudové zdroje, čímž snížíte potenciální náklady.

V této lekci se zaměříme na:

* [Proč je potřeba zabezpečit IoT zařízení?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptografie](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Zabezpečení IoT zařízení](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generování a použití certifikátu X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Toto je poslední lekce tohoto projektu, takže po dokončení této lekce a úkolu nezapomeňte vyčistit své cloudové služby. Služby budete potřebovat k dokončení úkolu, takže se ujistěte, že ho nejprve dokončíte.
>
> Pokud potřebujete pokyny, podívejte se na [průvodce vyčištěním projektu](../../../clean-up.md).

## Proč je potřeba zabezpečit IoT zařízení?

Zabezpečení IoT zahrnuje zajištění, že pouze očekávaná zařízení mohou připojit se k vaší cloudové IoT službě a posílat jí telemetrii, a že pouze vaše cloudová služba může posílat příkazy vašim zařízením. IoT data mohou být také osobní, včetně lékařských nebo intimních údajů, takže celá vaše aplikace musí zohlednit bezpečnost, aby zabránila úniku těchto dat.

Pokud vaše IoT aplikace není zabezpečená, existuje několik rizik:

* Falešné zařízení by mohlo posílat nesprávná data, což by způsobilo, že vaše aplikace bude reagovat nesprávně. Například by mohlo posílat neustále vysoké hodnoty vlhkosti půdy, což by znamenalo, že váš zavlažovací systém se nikdy nezapne a vaše rostliny uschnou.
* Neoprávnění uživatelé by mohli číst data z IoT zařízení, včetně osobních nebo kritických obchodních údajů.
* Hackeři by mohli posílat příkazy k ovládání zařízení způsobem, který by mohl poškodit zařízení nebo připojený hardware.
* Připojením k IoT zařízení by hackeři mohli získat přístup k dalším sítím a dostat se k soukromým systémům.
* Zlomyslní uživatelé by mohli získat přístup k osobním údajům a použít je k vydírání.

Toto jsou scénáře z reálného světa, které se dějí neustále. Některé příklady byly uvedeny v předchozích lekcích, ale zde jsou další:

* V roce 2018 hackeři použili otevřený WiFi přístupový bod na termostatu akvária, aby získali přístup k síti kasina a ukradli data. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* V roce 2016 Mirai Botnet spustil útok typu denial of service proti Dyn, poskytovateli internetových služeb, což způsobilo výpadky velké části internetu. Tento botnet použil malware k připojení k IoT zařízením, jako jsou DVR a kamery, které používaly výchozí uživatelská jména a hesla, a odtud spustil útok. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys měl databázi uživatelů svých připojených hraček CloudPets veřejně dostupnou na internetu. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava označovala běžce, které jste míjeli, a ukazovala jejich trasy, což umožnilo cizím lidem efektivně zjistit, kde bydlíte. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Udělejte si průzkum: Vyhledejte další příklady hacků IoT a úniků dat IoT, zejména u osobních předmětů, jako jsou internetově připojené zubní kartáčky nebo váhy. Zamyslete se nad dopadem těchto hacků na oběti nebo zákazníky.

> 💁 Zabezpečení je obrovské téma a tato lekce se dotkne pouze některých základů týkajících se připojení vašeho zařízení ke cloudu. Mezi další témata, která nebudou pokryta, patří monitorování změn dat během přenosu, přímé hackování zařízení nebo změny konfigurací zařízení. Hacking IoT je takovou hrozbou, že byly vyvinuty nástroje jako [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Tyto nástroje jsou podobné antivirovým a bezpečnostním nástrojům, které můžete mít na svém počítači, ale jsou navrženy pro malá, nízkoenergetická IoT zařízení.

## Kryptografie

Když se zařízení připojuje k IoT službě, používá ID k identifikaci. Problém je, že toto ID může být zkopírováno – hacker by mohl nastavit škodlivé zařízení, které používá stejné ID jako skutečné zařízení, ale posílá falešná data.

![Platná i škodlivá zařízení mohou používat stejné ID k odesílání telemetrie](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.cs.png)

Řešením je převést data, která jsou odesílána, do zašifrovaného formátu pomocí hodnoty známé pouze zařízení a cloudu. Tento proces se nazývá *šifrování* a hodnota použitá k šifrování dat se nazývá *šifrovací klíč*.

![Pokud je použito šifrování, budou přijímány pouze zašifrované zprávy, ostatní budou odmítnuty](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.cs.png)

Cloudová služba pak může data převést zpět do čitelného formátu pomocí procesu nazývaného *dešifrování*, buď pomocí stejného šifrovacího klíče, nebo *dešifrovacího klíče*. Pokud zašifrovanou zprávu nelze dešifrovat klíčem, zařízení bylo hacknuto a zpráva je odmítnuta.

Technika pro šifrování a dešifrování se nazývá *kryptografie*.

### Raná kryptografie

Nejstarší typy kryptografie byly substituční šifry, které se datují 3 500 let zpět. Substituční šifry zahrnují nahrazení jednoho písmene jiným. Například [Caesarova šifra](https://wikipedia.org/wiki/Caesar_cipher) zahrnuje posunutí abecedy o definované množství, přičemž pouze odesílatel zašifrované zprávy a zamýšlený příjemce vědí, o kolik písmen se posunout.

[Vigenèrova šifra](https://wikipedia.org/wiki/Vigenère_cipher) šla ještě dál tím, že používala slova k šifrování textu, takže každé písmeno v původním textu bylo posunuto o jiné množství, místo aby se vždy posunovalo o stejný počet písmen.

Kryptografie byla používána k široké škále účelů, například k ochraně receptu na glazuru hrnčíře ve starověké Mezopotámii, psaní tajných milostných dopisů v Indii nebo k uchování tajemství staroegyptských magických zaklínadel.

### Moderní kryptografie

Moderní kryptografie je mnohem pokročilejší, což ji činí těžší prolomit než rané metody. Moderní kryptografie používá složité matematické postupy k šifrování dat s příliš mnoha možnými klíči, aby byly útoky hrubou silou možné.

Kryptografie se používá v mnoha různých oblastech pro bezpečnou komunikaci. Pokud čtete tuto stránku na GitHubu, můžete si všimnout, že adresa webu začíná *HTTPS*, což znamená, že komunikace mezi vaším prohlížečem a webovými servery GitHubu je šifrována. Pokud by někdo mohl číst internetový provoz mezi vaším prohlížečem a GitHubem, nemohl by data přečíst, protože jsou šifrována. Váš počítač může dokonce šifrovat všechna data na vašem pevném disku, takže pokud by ho někdo ukradl, nemohl by bez vašeho hesla přečíst žádná data.

> 🎓 HTTPS znamená HyperText Transfer Protocol **Secure**

Bohužel ne všechno je bezpečné. Některá zařízení nemají žádné zabezpečení, jiná jsou zabezpečena pomocí snadno prolomitelných klíčů, nebo dokonce všechna zařízení stejného typu používají stejný klíč. Existují případy velmi osobních IoT zařízení, která mají všechna stejné heslo pro připojení přes WiFi nebo Bluetooth. Pokud se můžete připojit ke svému vlastnímu zařízení, můžete se připojit i k zařízení někoho jiného. Jakmile se připojíte, můžete získat přístup k velmi soukromým datům nebo mít kontrolu nad jejich zařízením.

> 💁 Navzdory složitosti moderní kryptografie a tvrzením, že prolomení šifrování může trvat miliardy let, vzestup kvantového počítání přinesl možnost prolomení všech známých šifrování během velmi krátké doby!

### Symetrické a asymetrické klíče

Šifrování existuje ve dvou typech – symetrické a asymetrické.

**Symetrické** šifrování používá stejný klíč k šifrování i dešifrování dat. Odesílatel i příjemce musí znát stejný klíč. Toto je nejméně bezpečný typ, protože klíč musí být nějakým způsobem sdílen. Aby odesílatel mohl poslat zašifrovanou zprávu příjemci, musí nejprve odeslat příjemci klíč.

![Symetrické šifrování používá stejný klíč k šifrování i dešifrování zprávy](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ff.cs.png)

Pokud je klíč během přenosu ukraden, nebo je odesílatel či příjemce hacknut a klíč je nalezen, šifrování může být prolomeno.

![Symetrické šifrování je bezpečné pouze tehdy, pokud hacker nezíská klíč – pokud ano, může zachytit a dešifrovat zprávu](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb.cs.png)

**Asymetrické** šifrování používá 2 klíče – šifrovací klíč a dešifrovací klíč, označované jako veřejný/soukromý pár klíčů. Veřejný klíč se používá k šifrování zprávy, ale nelze ho použít k jejímu dešifrování, soukromý klíč se používá k dešifrování zprávy, ale nelze ho použít k jejímu šifrování.

![Asymetrické šifrování používá jiný klíč k šifrování a dešifrování. Šifrovací klíč je odeslán všem odesílatelům zpráv, aby mohli zašifrovat zprávu před jejím odesláním příjemci, který vlastní klíče](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c.cs.png)

Příjemce sdílí svůj veřejný klíč a odesílatel ho používá k šifrování zprávy. Jakmile je zpráva odeslána, příjemce ji dešifruje pomocí svého soukromého klíče. Asymetrické šifrování je bezpečnější, protože soukromý klíč je uchováván v tajnosti příjemcem a nikdy není sdílen. Veřejný klíč může mít kdokoli, protože ho lze použít pouze k šifrování zpráv.

Symetrické šifrování je rychlejší než asymetrické, asymetrické je bezpečnější. Některé systémy používají obojí – asymetrické šifrování k zašifrování a sdílení symetrického klíče, poté symetrický klíč k šifrování všech dat. To umožňuje bezpečnější sdílení symetrického klíče mezi odesílatelem a příjemcem a rychlejší šifrování a dešifrování dat.

## Zabezpečení IoT zařízení

IoT zařízení mohou být zabezpečena pomocí symetrického nebo asymetrického šifrování. Symetrické je jednodušší, ale méně bezpečné.

### Symetrické klíče

Když nastavujete své IoT zařízení pro interakci s IoT Hubem, použili jste připojovací řetězec. Příklad připojovacího řetězce je:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Tento připojovací řetězec se skládá ze tří částí oddělených středníky, přičemž každá část je klíč a hodnota:

| Klíč | Hodnota | Popis |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL IoT Hubu |
| DeviceId | `soil-moisture-sensor` | Jedinečné ID zařízení |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Symetrický klíč známý zařízením a IoT Hubem |

Poslední část tohoto připojovacího řetězce, `SharedAccessKey`, je symetrický klíč známý jak zařízením, tak IoT Hubem. Tento klíč nikdy není odeslán ze zařízení do cloudu nebo z cloudu do zařízení. Místo toho se používá k šifrování dat, která jsou odesílána nebo přijímána.

✅ Udělejte experiment. Co si myslíte, že se stane, pokud změníte část `SharedAccessKey` v připojovacím řetězci při připojování vašeho IoT zařízení? Vyzkoušejte to.

Když se zařízení poprvé pokusí připojit, odešle token sdíleného přístupu (SAS) obsahující URL IoT Hubu, časový údaj, kdy token přístupu vyprší (obvykle 1 den od aktuálního času), a podpis. Tento podpis se skládá z URL a času vypršení zašifrovaného pomocí sdíleného přístupového klíče z připojovacího řetězce.

IoT Hub dešifruje tento podpis pomocí sdíleného přístupového klíče a pokud dešifrovaná hodnota odpovídá URL a času vypršení, zařízení je povoleno připojit se. Také ověřuje, že aktuální čas je před časem vypršení, aby zabránil škodlivému zařízení zachytit token SAS skutečného zařízení a použít ho.

Toto je elegantní způsob, jak ověřit, že odesílatel je správné zařízení. Odesláním známých dat ve formě dešifrované i zašifrované může server ověřit zařízení tím, že zajistí, že když dešifruje zašifrovaná data, výsledek odpovídá dešifrované verzi, která byla odeslána. Pokud se shodují, pak odesílatel i příjemce mají stejný symetrický šif
💁 Kvůli době vypršení platnosti musí vaše IoT zařízení znát přesný čas, který se obvykle získává ze serveru [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Pokud čas není přesný, připojení selže.
Po připojení budou všechna data odeslaná do IoT Hubu z zařízení nebo na zařízení z IoT Hubu šifrována pomocí sdíleného přístupového klíče.

✅ Co si myslíte, že se stane, pokud více zařízení sdílí stejný připojovací řetězec?

> 💁 Není dobrá bezpečnostní praxe ukládat tento klíč do kódu. Pokud hacker získá váš zdrojový kód, může získat váš klíč. Je také obtížnější při vydávání kódu, protože byste museli znovu zkompilovat s aktualizovaným klíčem pro každé zařízení. Je lepší načíst tento klíč z hardwarového bezpečnostního modulu – čipu na IoT zařízení, který ukládá šifrované hodnoty, jež může váš kód číst.
>
> Při učení IoT je často jednodušší vložit klíč do kódu, jak jste to udělali v předchozí lekci, ale musíte zajistit, aby tento klíč nebyl zkontrolován do veřejného systému správy zdrojového kódu.

Zařízení mají 2 klíče a 2 odpovídající připojovací řetězce. To umožňuje rotaci klíčů – tedy přepnutí z jednoho klíče na druhý, pokud je první kompromitován, a znovu vygenerování prvního klíče.

### X.509 certifikáty

Když používáte asymetrické šifrování s párem veřejného/soukromého klíče, musíte poskytnout svůj veřejný klíč každému, kdo vám chce poslat data. Problém je, jak si může příjemce vašeho klíče být jistý, že je to skutečně váš veřejný klíč, a ne někdo jiný, kdo se za vás vydává? Místo poskytování klíče můžete místo toho poskytnout svůj veřejný klíč uvnitř certifikátu, který byl ověřen důvěryhodnou třetí stranou, nazývanou X.509 certifikát.

X.509 certifikáty jsou digitální dokumenty, které obsahují veřejnou část páru veřejného/soukromého klíče. Obvykle jsou vydávány jednou z řady důvěryhodných organizací nazývaných [Certifikační autority](https://wikipedia.org/wiki/Certificate_authority) (CA) a digitálně podepsány CA, aby naznačily, že klíč je platný a pochází od vás. Certifikátu důvěřujete a věříte, že veřejný klíč pochází od toho, koho certifikát uvádí, protože důvěřujete CA, podobně jako byste důvěřovali pasu nebo řidičskému průkazu, protože důvěřujete zemi, která ho vydala. Certifikáty stojí peníze, takže můžete také „sami podepsat“, tedy vytvořit certifikát sami, který je podepsán vámi, pro testovací účely.

> 💁 Nikdy byste neměli používat certifikát podepsaný sami pro produkční vydání.

Tyto certifikáty obsahují řadu polí, včetně toho, od koho je veřejný klíč, podrobností o CA, která ho vydala, jak dlouho je platný, a samotného veřejného klíče. Před použitím certifikátu je dobrá praxe ověřit jej kontrolou, zda byl podepsán původní CA.

✅ Kompletní seznam polí v certifikátu si můžete přečíst v [Microsoft Understanding X.509 Public Key Certificates tutorial](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Při používání X.509 certifikátů budou mít jak odesílatel, tak příjemce své vlastní veřejné a soukromé klíče, stejně jako oba budou mít X.509 certifikáty obsahující veřejný klíč. Poté si nějakým způsobem vymění X.509 certifikáty, přičemž k šifrování dat, která odesílají, používají veřejné klíče druhé strany, a k dešifrování dat, která přijímají, používají svůj vlastní soukromý klíč.

![Místo sdílení veřejného klíče můžete sdílet certifikát. Uživatel certifikátu může ověřit, že pochází od vás, kontrolou u certifikační autority, která ho podepsala.](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76e.cs.png)

Jednou z velkých výhod používání X.509 certifikátů je, že je lze sdílet mezi zařízeními. Můžete vytvořit jeden certifikát, nahrát ho do IoT Hubu a použít ho pro všechna vaše zařízení. Každé zařízení pak potřebuje pouze znát soukromý klíč, aby dešifrovalo zprávy, které přijímá z IoT Hubu.

Certifikát používaný vaším zařízením k šifrování zpráv, které odesílá do IoT Hubu, je publikován společností Microsoft. Je to stejný certifikát, který používá mnoho služeb Azure, a někdy je zabudován do SDK.

> 💁 Pamatujte, že veřejný klíč je právě to – veřejný. Veřejný klíč Azure lze použít pouze k šifrování dat odesílaných do Azure, nikoli k jejich dešifrování, takže ho lze sdílet všude, včetně zdrojového kódu. Například ho můžete vidět v [Azure IoT C SDK source code](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ S X.509 certifikáty je spojeno mnoho odborných termínů. Definice některých pojmů, na které můžete narazit, si můžete přečíst v [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Generování a použití X.509 certifikátu

Kroky k vytvoření X.509 certifikátu jsou:

1. Vytvořte pár veřejného/soukromého klíče. Jedním z nejrozšířenějších algoritmů pro generování páru veřejného/soukromého klíče je [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Odešlete veřejný klíč s přidruženými daty k podepsání, buď CA, nebo vlastním podpisem.

Azure CLI má příkazy k vytvoření nové identity zařízení v IoT Hubu a automaticky generuje pár veřejného/soukromého klíče a vytvoří certifikát podepsaný vlastníkem.

> 💁 Pokud chcete vidět kroky podrobněji, místo použití Azure CLI, najdete je v [Using OpenSSL to create self-signed certificates tutorial in the Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Úkol – vytvořte identitu zařízení pomocí X.509 certifikátu

1. Spusťte následující příkaz k registraci nové identity zařízení, automaticky generující klíče a certifikáty:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro svůj IoT Hub.

    Tím se vytvoří zařízení s ID `soil-moisture-sensor-x509`, aby se odlišilo od identity zařízení, kterou jste vytvořili v předchozí lekci. Tento příkaz také vytvoří 2 soubory v aktuálním adresáři:

    * `soil-moisture-sensor-x509-key.pem` – tento soubor obsahuje soukromý klíč zařízení.
    * `soil-moisture-sensor-x509-cert.pem` – toto je soubor X.509 certifikátu zařízení.

    Tyto soubory uchovávejte v bezpečí! Soubor se soukromým klíčem by neměl být zkontrolován do veřejného systému správy zdrojového kódu.

### Úkol – použijte X.509 certifikát ve svém kódu zařízení

Projděte si relevantní průvodce připojením vašeho IoT zařízení ke cloudu pomocí X.509 certifikátu:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Jednodeskový počítač - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Výzva

Existuje několik způsobů, jak vytvořit, spravovat a mazat služby Azure, jako jsou Resource Groups a IoT Huby. Jedním ze způsobů je [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – webové rozhraní, které vám poskytuje GUI pro správu vašich služeb Azure.

Přejděte na [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) a prozkoumejte portál. Zkuste vytvořit IoT Hub pomocí portálu a poté ho smazat.

**Tip** – při vytváření služeb prostřednictvím portálu nemusíte předem vytvářet Resource Group, jedna může být vytvořena při vytváření služby. Ujistěte se, že ji smažete, když skončíte!

Na portálu Azure najdete spoustu dokumentace, tutoriálů a průvodců v [Azure portal documentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Přehled & Samostudium

* Přečtěte si o historii kryptografie na [History of cryptography page on Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Přečtěte si o X.509 certifikátech na [X.509 page on Wikipedia](https://wikipedia.org/wiki/X.509).

## Zadání

[Vytvořte nové IoT zařízení](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.