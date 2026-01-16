<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6d6aa1be033625d201a190fc9c5cbfb4",
  "translation_date": "2025-08-28T12:50:31+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/README.md",
  "language_code": "hr"
}
-->
# Prepoznajte govor pomoću IoT uređaja

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-21.e34de51354d6606fb5ee08d8c89d0222eea0a2a7aaf744a8805ae847c4f69dc4.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video daje pregled Azure govorne usluge, teme koja će biti obrađena u ovoj lekciji:

[![Kako započeti korištenje resursa Cognitive Services Speech s Microsoft Azure YouTube kanala](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Kliknite na sliku iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Uvod

'Alexa, postavi timer na 12 minuta'

'Alexa, status timera'

'Alexa, postavi timer na 8 minuta pod nazivom kuhaj brokulu na pari'

Pametni uređaji postaju sve prisutniji. Ne samo kao pametni zvučnici poput HomePods, Echos i Google Homes, već i ugrađeni u naše telefone, satove, pa čak i rasvjetna tijela i termostate.

> 💁 Imam barem 19 uređaja u svom domu koji imaju glasovne asistente, i to su samo oni za koje znam!

Glasovna kontrola povećava pristupačnost omogućujući osobama s ograničenom pokretljivošću interakciju s uređajima. Bilo da se radi o trajnom invaliditetu, poput rođenja bez ruku, privremenim invaliditetima poput slomljenih ruku, ili situacijama kada su vam ruke zauzete kupovinom ili malom djecom, mogućnost upravljanja kućom glasom umjesto rukama otvara svijet pristupačnosti. Viknuti 'Hej Siri, zatvori garažna vrata' dok se bavite presvlačenjem bebe i nestašnim djetetom može biti mala, ali učinkovita životna olakšica.

Jedna od popularnijih upotreba glasovnih asistenata je postavljanje timera, posebno kuhinjskih timera. Mogućnost postavljanja više timera samo glasom velika je pomoć u kuhinji - nema potrebe zaustavljati miješenje tijesta, miješanje juhe ili čišćenje ruku od nadjeva za knedle kako biste koristili fizički timer.

U ovoj lekciji naučit ćete kako integrirati prepoznavanje glasa u IoT uređaje. Naučit ćete o mikrofonima kao senzorima, kako snimiti zvuk s mikrofona povezanog s IoT uređajem i kako koristiti AI za pretvaranje onoga što se čuje u tekst. Tijekom ostatka ovog projekta izgradit ćete pametni kuhinjski timer, sposoban postavljati timere glasom na više jezika.

U ovoj lekciji obradit ćemo:

* [Mikrofoni](../../../../../6-consumer/lessons/1-speech-recognition)
* [Snimanje zvuka s vašeg IoT uređaja](../../../../../6-consumer/lessons/1-speech-recognition)
* [Govor u tekst](../../../../../6-consumer/lessons/1-speech-recognition)
* [Pretvaranje govora u tekst](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofoni

Mikrofoni su analogni senzori koji pretvaraju zvučne valove u električne signale. Vibracije u zraku uzrokuju pomicanje komponenti u mikrofonu za vrlo male iznose, što uzrokuje male promjene u električnim signalima. Te se promjene zatim pojačavaju kako bi se generirao električni izlaz.

### Vrste mikrofona

Mikrofoni dolaze u raznim vrstama:

* Dinamički - Dinamički mikrofoni imaju magnet pričvršćen na pokretnu membranu koja se pomiče u zavojnici žice stvarajući električnu struju. Ovo je suprotno od većine zvučnika, koji koriste električnu struju za pomicanje magneta u zavojnici žice, pomičući membranu kako bi stvorili zvuk. To znači da se zvučnici mogu koristiti kao dinamički mikrofoni, a dinamički mikrofoni kao zvučnici. U uređajima poput interfona, gdje korisnik ili sluša ili govori, ali ne oboje, jedan uređaj može djelovati i kao zvučnik i kao mikrofon.

    Dinamički mikrofoni ne trebaju napajanje za rad, električni signal se stvara isključivo iz mikrofona.

    ![Patti Smith pjeva u Shure SM58 (dinamički kardioidni tip) mikrofon](../../../../../translated_images/hr/dynamic-mic.8babac890a2d80dfb0874b5bf37d4b851fe2aeb9da6fd72945746176978bf3bb.jpg)

* Trakasti - Trakasti mikrofoni slični su dinamičkim mikrofonima, osim što imaju metalnu traku umjesto membrane. Ova traka se pomiče u magnetskom polju stvarajući električnu struju. Kao i dinamički mikrofoni, trakasti mikrofoni ne trebaju napajanje za rad.

    ![Edmund Lowe, američki glumac, stoji uz radijski mikrofon (označen za (NBC) Blue Network), drži skriptu, 1942](../../../../../translated_images/hr/ribbon-mic.eacc8e092c7441ca.webp)

* Kondenzatorski - Kondenzatorski mikrofoni imaju tanku metalnu membranu i fiksnu metalnu stražnju ploču. Elektricitet se primjenjuje na obje ove komponente, a kako membrana vibrira, statički naboj između ploča se mijenja generirajući signal. Kondenzatorski mikrofoni trebaju napajanje za rad - nazvano *Phantom power*.

    ![C451B mali kondenzatorski mikrofon s membranom od AKG Acoustics](../../../../../translated_images/hr/condenser-mic.6f6ed5b76ca19e0ec3fd0c544601542d4479a6cb7565db336de49fbbf69f623e.jpg)

* MEMS - Mikroelektromehanički sustavi mikrofona, ili MEMS, su mikrofoni na čipu. Imaju dijafragmu osjetljivu na pritisak ugraviranu na silicijski čip i rade slično kondenzatorskom mikrofonu. Ovi mikrofoni mogu biti vrlo mali i integrirani u elektroničke sklopove.

    ![MEMS mikrofon na pločici](../../../../../translated_images/hr/mems-microphone.80574019e1f5e4d9ee72fed720ecd25a39fc2969c91355d17ebb24ba4159e4c4.png)

    Na slici iznad, čip označen **LEFT** je MEMS mikrofon, s dijafragmom manjom od jednog milimetra.

✅ Istražite: Koje mikrofone imate oko sebe - bilo u vašem računalu, telefonu, slušalicama ili drugim uređajima. Koje vrste mikrofona su to?

### Digitalni zvuk

Zvuk je analogni signal koji nosi vrlo detaljne informacije. Da bi se taj signal pretvorio u digitalni, zvuk se mora uzorkovati tisuće puta u sekundi.

> 🎓 Uzorkovanje je pretvaranje audio signala u digitalnu vrijednost koja predstavlja signal u tom trenutku.

![Grafikon koji prikazuje signal s diskretnim točkama u fiksnim intervalima](../../../../../translated_images/hr/sampling.6f4fadb3f2d9dfe7.webp)

Digitalni zvuk se uzorkuje pomoću Pulse Code Modulation (PCM). PCM uključuje očitavanje napona signala i odabir najbliže diskretne vrijednosti tom naponu koristeći definiranu veličinu.

> 💁 PCM možete zamisliti kao verziju senzora za modulaciju širine impulsa (PWM). (PWM je obrađen u [lekciji 3 projekta za početnike](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM uključuje pretvaranje analognog signala u digitalni, dok PWM uključuje pretvaranje digitalnog signala u analogni.

Na primjer, većina streaming glazbenih servisa nudi 16-bitni ili 24-bitni zvuk. To znači da pretvaraju napon u vrijednost koja stane u 16-bitni ili 24-bitni cijeli broj. 16-bitni zvuk stane u raspon od -32,768 do 32,767, dok je 24-bitni u rasponu −8,388,608 do 8,388,607. Što je više bitova, to je uzorak bliži onome što naše uši zapravo čuju.

> 💁 Možda ste čuli za 8-bitni zvuk, često nazivan LoFi. Ovo je zvuk uzorkovan koristeći samo 8 bitova, dakle -128 do 127. Prvi računalni zvuk bio je ograničen na 8 bitova zbog hardverskih ograničenja, pa se često pojavljuje u retro igrama.

Ovi uzorci se uzimaju tisuće puta u sekundi, koristeći dobro definirane stope uzorkovanja mjerene u KHz (tisuće očitanja u sekundi). Streaming glazbeni servisi koriste 48KHz za većinu zvuka, ali neki 'lossless' zvuk koristi do 96KHz ili čak 192KHz. Što je veća stopa uzorkovanja, to je zvuk bliži originalu, do određene granice. Postoji rasprava mogu li ljudi primijetiti razliku iznad 48KHz.

✅ Istražite: Ako koristite streaming glazbeni servis, koju stopu uzorkovanja i veličinu koristi? Ako koristite CD-ove, koja je stopa uzorkovanja i veličina CD zvuka?

Postoji niz različitih formata za audio podatke. Vjerojatno ste čuli za mp3 datoteke - audio podatke koji su komprimirani kako bi bili manji bez gubitka kvalitete. Nekompresirani zvuk često se pohranjuje kao WAV datoteka - to je datoteka s 44 bajta zaglavlja informacija, nakon čega slijede sirovi audio podaci. Zaglavlje sadrži informacije poput stope uzorkovanja (na primjer 16000 za 16KHz) i veličine uzorka (16 za 16-bitni), te broja kanala. Nakon zaglavlja, WAV datoteka sadrži sirove audio podatke.

> 🎓 Kanali se odnose na broj različitih audio tokova koji čine zvuk. Na primjer, za stereo zvuk s lijevim i desnim kanalom, postojala bi 2 kanala. Za 7.1 surround zvuk za kućni kino sustav, to bi bilo 8.

### Veličina audio podataka

Audio podaci su relativno veliki. Na primjer, snimanje nekompresiranog 16-bitnog zvuka na 16KHz (dovoljno dobra stopa za korištenje s modelom za govor u tekst) zahtijeva 32KB podataka za svaku sekundu zvuka:

* 16-bitni znači 2 bajta po uzorku (1 bajt je 8 bitova).
* 16KHz je 16,000 uzoraka u sekundi.
* 16,000 x 2 bajta = 32,000 bajtova u sekundi.

Ovo zvuči kao mala količina podataka, ali ako koristite mikrokontroler s ograničenom memorijom, to može biti puno. Na primjer, Wio Terminal ima 192KB memorije, a ta memorija mora pohraniti programski kod i varijable. Čak i ako je vaš programski kod vrlo mali, ne biste mogli snimiti više od 5 sekundi zvuka.

Mikrokontroleri mogu pristupiti dodatnoj pohrani, poput SD kartica ili flash memorije. Kada gradite IoT uređaj koji snima zvuk, morat ćete osigurati ne samo da imate dodatnu pohranu, već i da vaš kod zapisuje snimljeni zvuk s mikrofona izravno na tu pohranu, te da prilikom slanja u oblak, strujate podatke iz pohrane u web zahtjev. Na taj način možete izbjeći nedostatak memorije pokušavajući držati cijeli blok audio podataka u memoriji odjednom.

## Snimanje zvuka s vašeg IoT uređaja

Vaš IoT uređaj može biti povezan s mikrofonom za snimanje zvuka, spremnog za pretvaranje u tekst. Također može biti povezan sa zvučnicima za reprodukciju zvuka. U kasnijim lekcijama ovo će se koristiti za davanje audio povratnih informacija, ali korisno je postaviti zvučnike sada kako biste testirali mikrofon.

### Zadatak - konfigurirajte mikrofon i zvučnike

Prođite kroz odgovarajući vodič za konfiguraciju mikrofona i zvučnika za vaš IoT uređaj:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Jednoboardno računalo - Raspberry Pi](pi-microphone.md)
* [Jednoboardno računalo - Virtualni uređaj](virtual-device-microphone.md)

### Zadatak - snimanje zvuka

Prođite kroz odgovarajući vodič za snimanje zvuka na vašem IoT uređaju:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Jednoboardno računalo - Raspberry Pi](pi-audio.md)
* [Jednoboardno računalo - Virtualni uređaj](virtual-device-audio.md)

## Govor u tekst

Govor u tekst, ili prepoznavanje govora, uključuje korištenje AI-a za pretvaranje riječi u audio signalu u tekst.

### Modeli za prepoznavanje govora

Za pretvaranje govora u tekst, uzorci iz audio signala grupiraju se i šalju u model strojnog učenja temeljen na Recurrent Neural Network (RNN). Ovo je vrsta modela strojnog učenja koji može koristiti prethodne podatke za donošenje odluka o dolaznim podacima. Na primjer, RNN bi mogao prepoznati jedan blok audio uzoraka kao zvuk 'Hel', a kada primi drugi blok koji prepoznaje kao zvuk 'lo', može kombinirati ovo s prethodnim zvukom, pronaći da je 'Hello' valjana riječ i odabrati je kao rezultat.

ML modeli uvijek prihvaćaju podatke iste veličine svaki put. Klasifikator slika koji ste izgradili u ranijoj lekciji mijenja veličinu slika na fiksnu veličinu i obrađuje ih. Isto vrijedi i za modele govora, oni moraju obrađivati audio blokove fiksne veličine. Modeli govora moraju biti sposobni kombinirati rezultate više predikcija kako bi dobili odgovor, omogućujući im razlikovanje između 'Hi' i 'Highway', ili 'flock' i 'floccinaucinihilipilification'.

Modeli govora također su dovoljno napredni da razumiju kontekst i mogu ispraviti riječi koje prepoznaju kako se obrađuje više zvukova. Na primjer, ako kažete "Išao sam u trgovine da kupim dvije banane i jednu jabuku također", koristili biste tri riječi koje zvuče isto, ali se pišu različito - to, two i too. Modeli govora mogu razumjeti kontekst i koristiti odgovarajuće pravopis riječi.
💁 Neke govorne usluge omogućuju prilagodbu kako bi bolje funkcionirale u bučnim okruženjima poput tvornica ili s industrijski specifičnim riječima, poput kemijskih naziva. Ove prilagodbe se treniraju pružanjem uzoraka zvuka i transkripcije te funkcioniraju koristeći prijenosno učenje, na isti način kao što ste ranije trenirali klasifikator slika koristeći samo nekoliko slika.
### Privatnost

Kada koristite prepoznavanje govora na IoT uređaju za potrošače, privatnost je iznimno važna. Ovi uređaji kontinuirano slušaju zvuk, pa kao potrošač ne želite da se sve što kažete šalje u oblak i pretvara u tekst. Ne samo da će to koristiti puno internetske propusnosti, već ima i velike implikacije na privatnost, posebno kada neki proizvođači pametnih uređaja nasumično odabiru audio zapise za [ljudsku validaciju u odnosu na generirani tekst kako bi poboljšali svoj model](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Želite da vaš pametni uređaj šalje zvuk u oblak za obradu samo kada ga koristite, a ne kada čuje zvuk u vašem domu, zvuk koji može uključivati privatne sastanke ili intimne interakcije. Većina pametnih uređaja radi pomoću *budne riječi*, ključne fraze poput "Alexa", "Hej Siri" ili "OK Google", koja uzrokuje da se uređaj 'probudi' i sluša što govorite sve dok ne otkrije pauzu u vašem govoru, što ukazuje da ste završili razgovor s uređajem.

> 🎓 Detekcija budne riječi također se naziva *prepoznavanje ključne riječi* ili *otkrivanje ključne riječi*.

Te budne riječi otkrivaju se na samom uređaju, a ne u oblaku. Pametni uređaji imaju male AI modele koji rade na uređaju i slušaju budnu riječ, a kada je otkriju, počinju slati zvuk u oblak za prepoznavanje. Ti modeli su vrlo specijalizirani i slušaju samo budnu riječ.

> 💁 Neke tehnološke kompanije dodaju više privatnosti svojim uređajima i dio pretvorbe govora u tekst obavljaju na samom uređaju. Apple je najavio da će kao dio svojih ažuriranja za iOS i macOS u 2021. godini podržavati pretvorbu govora u tekst na uređaju i moći obraditi mnoge zahtjeve bez potrebe za korištenjem oblaka. To je moguće zahvaljujući snažnim procesorima u njihovim uređajima koji mogu pokretati ML modele.

✅ Koje su, po vašem mišljenju, implikacije na privatnost i etiku kada se audio zapis šalje u oblak? Treba li taj audio zapis biti pohranjen, i ako da, na koji način? Smatrate li da je korištenje snimki za provedbu zakona dobra zamjena za gubitak privatnosti?

Detekcija budne riječi obično koristi tehniku poznatu kao TinyML, koja omogućuje pretvorbu ML modela kako bi se mogli pokretati na mikrokontrolerima. Ti modeli su maleni i troše vrlo malo energije za rad.

Kako biste izbjegli složenost treniranja i korištenja modela za budnu riječ, pametni mjerač vremena koji gradite u ovoj lekciji koristit će gumb za uključivanje prepoznavanja govora.

> 💁 Ako želite pokušati stvoriti model za detekciju budne riječi koji se može pokretati na Wio Terminalu ili Raspberry Pi-ju, pogledajte ovaj [tutorial za odgovaranje na vaš glas od Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Ako želite koristiti svoje računalo za to, možete isprobati [brzi početak s prilagođenom ključnom riječi na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Pretvorba govora u tekst

![Logotip govorne usluge](../../../../../translated_images/hr/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Kao i kod klasifikacije slika u ranijem projektu, postoje unaprijed izgrađene AI usluge koje mogu uzeti govor kao audio datoteku i pretvoriti ga u tekst. Jedna od takvih usluga je Govorna usluga, dio Cognitive Services, unaprijed izgrađenih AI usluga koje možete koristiti u svojim aplikacijama.

### Zadatak - konfigurirajte AI resurs za govor

1. Kreirajte grupu resursa za ovaj projekt pod nazivom `smart-timer`.

1. Koristite sljedeću naredbu za kreiranje besplatnog govornog resursa:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja grupe resursa.

1. Trebat će vam API ključ za pristup govornom resursu iz vašeg koda. Pokrenite sljedeću naredbu za dobivanje ključa:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopirajte jedan od ključeva.

### Zadatak - pretvorite govor u tekst

Prođite kroz relevantni vodič za pretvorbu govora u tekst na vašem IoT uređaju:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Jednoplano računalo - Raspberry Pi](pi-speech-to-text.md)
* [Jednoplano računalo - Virtualni uređaj](virtual-device-speech-to-text.md)

---

## 🚀 Izazov

Prepoznavanje govora postoji već dugo vremena i kontinuirano se poboljšava. Istražite trenutne mogućnosti i usporedite kako su se razvijale tijekom vremena, uključujući koliko su točne strojne transkripcije u usporedbi s ljudskim.

Što mislite, što budućnost donosi za prepoznavanje govora?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Pregled i samostalno učenje

* Pročitajte o različitim vrstama mikrofona i kako rade u članku [koja je razlika između dinamičkih i kondenzatorskih mikrofona na Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Pročitajte više o govornoj usluzi Cognitive Services u [dokumentaciji o govornoj usluzi na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Pročitajte o prepoznavanju ključnih riječi u [dokumentaciji o prepoznavanju ključnih riječi na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Zadatak

[](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.