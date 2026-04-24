# Nastavte časovač a poskytnite hovorenú spätnú väzbu

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/sk/lesson-23.f38483e1d4df4828.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Úvod

Inteligentní asistenti nie sú zariadenia na jednosmernú komunikáciu. Hovoríte s nimi a oni odpovedajú:

„Alexa, nastav časovač na 3 minúty.“

„Ok, váš časovač je nastavený na 3 minúty.“

V posledných dvoch lekciách ste sa naučili, ako previesť reč na text a potom z tohto textu extrahovať požiadavku na nastavenie časovača. V tejto lekcii sa naučíte, ako nastaviť časovač na IoT zariadení, odpovedať používateľovi hovorenými slovami, ktoré potvrdzujú jeho časovač, a upozorniť ho, keď časovač skončí.

V tejto lekcii sa budeme venovať:

* [Textu na reč](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Nastaveniu časovača](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Konverzii textu na reč](../../../../../6-consumer/lessons/3-spoken-feedback)

## Text na reč

Text na reč, ako názov napovedá, je proces konverzie textu na zvuk, ktorý obsahuje text ako hovorené slová. Základný princíp spočíva v rozložení slov v texte na ich základné zvuky (známe ako fonémy) a v spojení zvukov buď pomocou prednahraného zvuku, alebo zvuku generovaného modelmi umelej inteligencie.

![Tri fázy typických systémov textu na reč](../../../../../translated_images/sk/tts-overview.193843cf3f5ee09f.webp)

Systémy textu na reč majú zvyčajne 3 fázy:

* Analýza textu
* Lingvistická analýza
* Generovanie zvukovej vlny

### Analýza textu

Analýza textu zahŕňa spracovanie poskytnutého textu a jeho konverziu na slová, ktoré môžu byť použité na generovanie reči. Napríklad, ak konvertujete „Hello world“, nie je potrebná žiadna analýza textu, tieto dve slová môžu byť priamo prevedené na reč. Ak však máte „1234“, môže byť potrebné to previesť buď na slová „Tisícdvestotridsaťštyri“ alebo „Jeden, dva, tri, štyri“ v závislosti od kontextu. Pre „Mám 1234 jabĺk“ by to bolo „Tisícdvestotridsaťštyri“, ale pre „Dieťa počítalo 1234“ by to bolo „Jeden, dva, tri, štyri“.

Slová, ktoré sa vytvoria, sa líšia nielen podľa jazyka, ale aj podľa lokality daného jazyka. Napríklad v americkej angličtine je 120 „One hundred twenty“, zatiaľ čo v britskej angličtine je to „One hundred and twenty“, s použitím „and“ po stovkách.

✅ Niektoré ďalšie príklady, ktoré vyžadujú analýzu textu, zahŕňajú „in“ ako skratku pre palec a „st“ ako skratku pre svätého alebo ulicu. Dokážete nájsť ďalšie príklady vo vašom jazyku, kde sú slová bez kontextu nejednoznačné?

Keď sú slová definované, posielajú sa na lingvistickú analýzu.

### Lingvistická analýza

Lingvistická analýza rozkladá slová na fonémy. Fonémy sú založené nielen na použitých písmenách, ale aj na ostatných písmenách v slove. Napríklad v angličtine je zvuk „a“ v „car“ a „care“ odlišný. Anglický jazyk má 44 rôznych fonémov pre 26 písmen abecedy, niektoré zdieľané rôznymi písmenami, ako napríklad rovnaký foném použitý na začiatku „circle“ a „serpent“.

✅ Urobte si výskum: Aké sú fonémy vo vašom jazyku?

Keď sú slová prevedené na fonémy, tieto fonémy potrebujú ďalšie údaje na podporu intonácie, úpravy tónu alebo trvania v závislosti od kontextu. Jedným príkladom je, že v angličtine môže zvýšenie tónu premeniť vetu na otázku, pričom zvýšený tón na poslednom slove naznačuje otázku.

Napríklad - veta „You have an apple“ je vyhlásenie, že máte jablko. Ak sa tón na konci zvýši, zvýšením pre slovo „apple“, stane sa z toho otázka „You have an apple?“, pýtajúc sa, či máte jablko. Lingvistická analýza musí použiť otáznik na konci, aby rozhodla o zvýšení tónu.

Keď sú fonémy vygenerované, môžu byť poslané na generovanie zvukovej vlny na produkciu zvukového výstupu.

### Generovanie zvukovej vlny

Prvé elektronické systémy textu na reč používali jednotlivé zvukové nahrávky pre každý foném, čo viedlo k veľmi monotónnym, robotickým hlasom. Lingvistická analýza by produkovala fonémy, tie by sa načítali z databázy zvukov a spojili, aby vytvorili zvuk.

✅ Urobte si výskum: Nájdite niektoré zvukové nahrávky z raných systémov syntézy reči. Porovnajte ich s modernou syntézou reči, ako je tá, ktorá sa používa v inteligentných asistentoch.

Modernejšie generovanie zvukovej vlny používa ML modely postavené na hlbokom učení (veľmi veľké neurónové siete, ktoré fungujú podobne ako neuróny v mozgu) na produkciu prirodzenejšie znejúcich hlasov, ktoré môžu byť nerozoznateľné od ľudských.

> 💁 Niektoré z týchto ML modelov môžu byť preškolené pomocou transferového učenia, aby zneli ako skutoční ľudia. To znamená, že používanie hlasu ako bezpečnostného systému, čo banky čoraz viac skúšajú, už nie je dobrý nápad, pretože ktokoľvek s nahrávkou niekoľkých minút vášho hlasu vás môže napodobniť.

Tieto veľké ML modely sa trénujú na kombináciu všetkých troch krokov do end-to-end syntetizátorov reči.

## Nastavenie časovača

Na nastavenie časovača musí vaše IoT zariadenie zavolať REST endpoint, ktorý ste vytvorili pomocou serverless kódu, a potom použiť výsledný počet sekúnd na nastavenie časovača.

### Úloha - zavolajte serverless funkciu na získanie času časovača

Postupujte podľa príslušného návodu na zavolanie REST endpointu z vášho IoT zariadenia a nastavte časovač na požadovaný čas:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Jednodoskový počítač - Raspberry Pi/virtuálne IoT zariadenie](single-board-computer-set-timer.md)

## Konverzia textu na reč

Rovnaká služba reči, ktorú ste použili na konverziu reči na text, môže byť použitá na konverziu textu späť na reč, a táto reč môže byť prehraná cez reproduktor na vašom IoT zariadení. Text na konverziu sa posiela do služby reči spolu s typom požadovaného zvuku (napríklad vzorkovacia frekvencia) a binárne údaje obsahujúce zvuk sa vrátia.

Keď odošlete túto požiadavku, použijete *Speech Synthesis Markup Language* (SSML), jazyk na báze XML pre aplikácie syntézy reči. Tento jazyk definuje nielen text na konverziu, ale aj jazyk textu, hlas, ktorý sa má použiť, a môže byť dokonca použitý na definovanie rýchlosti, hlasitosti a tónu pre niektoré alebo všetky slová v texte.

Napríklad tento SSML definuje požiadavku na konverziu textu „Váš časovač na 3 minúty a 5 sekúnd bol nastavený“ na reč pomocou britského anglického hlasu s názvom `en-GB-MiaNeural`:

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Väčšina systémov textu na reč má viacero hlasov pre rôzne jazyky, s príslušnými akcentmi, ako je britský anglický hlas s anglickým prízvukom a novozélandský anglický hlas s novozélandským prízvukom.

### Úloha - konvertujte text na reč

Prejdite si príslušný návod na konverziu textu na reč pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Jednodoskový počítač - Raspberry Pi](pi-text-to-speech.md)
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device-text-to-speech.md)

---

## 🚀 Výzva

SSML má spôsoby, ako zmeniť, ako sa slová vyslovujú, napríklad pridaním dôrazu na určité slová, pridaním pauz alebo zmenou tónu. Vyskúšajte niektoré z nich, odošlite rôzne SSML z vášho IoT zariadenia a porovnajte výstup. Viac o SSML, vrátane toho, ako zmeniť spôsob, akým sa slová vyslovujú, si môžete prečítať v [špecifikácii Speech Synthesis Markup Language (SSML) Version 1.1 od World Wide Web Consortium](https://www.w3.org/TR/speech-synthesis11/).

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Prehľad a samoštúdium

* Prečítajte si viac o syntéze reči na [stránke o syntéze reči na Wikipédii](https://wikipedia.org/wiki/Speech_synthesis)
* Prečítajte si viac o spôsoboch, akými zločinci používajú syntézu reči na krádeže, v [článku o falošných hlasoch na BBC](https://www.bbc.com/news/technology-48908736)
* Zistite viac o rizikách pre dabingových hercov zo syntetizovaných verzií ich hlasov v [článku na Vice o tom, ako AI ovplyvňuje dabingových hercov](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Zadanie

[Zrušte časovač](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.