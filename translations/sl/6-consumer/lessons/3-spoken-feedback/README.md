# Nastavite časovnik in podajte zvočne povratne informacije

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-23.f38483e1d4df4828.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Uvod

Pametni asistenti niso naprave za enosmerno komunikacijo. Govorite z njimi, oni pa odgovarjajo:

"Alexa, nastavi časovnik za 3 minute"

"V redu, vaš časovnik je nastavljen na 3 minute"

V zadnjih dveh lekcijah ste se naučili, kako pretvoriti govor v besedilo in nato iz besedila izluščiti zahtevo za nastavitev časovnika. V tej lekciji se boste naučili, kako nastaviti časovnik na IoT napravi, uporabniku odgovoriti z zvočnimi besedami, ki potrjujejo časovnik, ter ga opozoriti, ko se časovnik izteče.

V tej lekciji bomo obravnavali:

* [Pretvorba besedila v govor](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Nastavitev časovnika](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Pretvorba besedila v govor](../../../../../6-consumer/lessons/3-spoken-feedback)

## Pretvorba besedila v govor

Pretvorba besedila v govor, kot že ime pove, je proces pretvorbe besedila v zvok, ki vsebuje besedilo kot izgovorjene besede. Osnovno načelo je razčleniti besede v besedilu na njihove sestavne zvoke (imenovane foneme) in sestaviti zvok za te zvoke, bodisi z uporabo vnaprej posnetega zvoka bodisi z zvokom, ki ga generirajo modeli umetne inteligence.

![Tri faze tipičnih sistemov za pretvorbo besedila v govor](../../../../../translated_images/sl/tts-overview.193843cf3f5ee09f.webp)

Sistemi za pretvorbo besedila v govor običajno vključujejo 3 faze:

* Analiza besedila
* Jezikovna analiza
* Generiranje zvočnega valovanja

### Analiza besedila

Analiza besedila vključuje obdelavo podanega besedila in njegovo pretvorbo v besede, ki jih je mogoče uporabiti za generiranje govora. Na primer, če pretvorite "Hello world", analiza besedila ni potrebna, saj lahko ti dve besedi neposredno pretvorite v govor. Če pa imate "1234", je to morda treba pretvoriti bodisi v besede "One thousand, two hundred thirty four" ali "One, two, three, four", odvisno od konteksta. Za "I have 1234 apples" bi bilo to "One thousand, two hundred thirty four", medtem ko bi za "The child counted 1234" bilo "One, two, three, four".

Besede, ki jih ustvarite, se razlikujejo ne le glede na jezik, temveč tudi glede na lokalno različico jezika. Na primer, v ameriški angleščini je 120 "One hundred twenty", v britanski angleščini pa "One hundred and twenty", z uporabo "and" po stotici.

✅ Nekateri drugi primeri, ki zahtevajo analizo besedila, vključujejo "in" kot okrajšavo za inch in "st" kot okrajšavo za saint ali street. Ali lahko pomislite na druge primere v vašem jeziku, kjer so besede dvoumne brez konteksta?

Ko so besede definirane, se pošljejo v jezikovno analizo.

### Jezikovna analiza

Jezikovna analiza razčleni besede na foneme. Fonemi temeljijo ne le na uporabljenih črkah, temveč tudi na drugih črkah v besedi. Na primer, v angleščini je zvok 'a' v 'car' in 'care' različen. Angleški jezik ima 44 različnih fonemov za 26 črk v abecedi, nekateri pa so skupni različnim črkam, kot je isti fonem, ki se uporablja na začetku 'circle' in 'serpent'.

✅ Raziskujte: Kakšni so fonemi v vašem jeziku?

Ko so besede pretvorjene v foneme, ti fonemi potrebujejo dodatne podatke za podporo intonaciji, prilagajanju tona ali trajanja glede na kontekst. En primer je v angleščini, kjer se zvišanje tona lahko uporabi za pretvorbo stavka v vprašanje; zvišan ton pri zadnji besedi nakazuje vprašanje.

Na primer - stavek "You have an apple" je trditev, da imate jabolko. Če se ton na koncu dvigne, poveča pri besedi apple, postane vprašanje "You have an apple?", ki sprašuje, ali imate jabolko. Jezikovna analiza mora uporabiti vprašaj na koncu, da se odloči za zvišanje tona.

Ko so fonemi generirani, se pošljejo za generiranje zvočnega valovanja, da se ustvari zvočni izhod.

### Generiranje zvočnega valovanja

Prvi elektronski sistemi za pretvorbo besedila v govor so uporabljali posamezne zvočne posnetke za vsak fonem, kar je vodilo do zelo monotonih, robotsko zvenečih glasov. Jezikovna analiza bi ustvarila foneme, ti bi se naložili iz baze podatkov zvokov in sestavili skupaj, da bi ustvarili zvok.

✅ Raziskujte: Poiščite zvočne posnetke iz zgodnjih sistemov za sintezo govora. Primerjajte jih z modernimi sistemi za sintezo govora, kot jih uporabljajo pametni asistenti.

Sodobnejše generiranje zvočnega valovanja uporablja modele strojnega učenja, zgrajene z globokim učenjem (zelo velike nevronske mreže, ki delujejo podobno kot nevroni v možganih), da ustvarijo bolj naravno zveneče glasove, ki so lahko nerazločljivi od človeških.

> 💁 Nekateri od teh modelov strojnega učenja se lahko ponovno usposobijo z uporabo prenosa učenja, da zvenijo kot resnični ljudje. To pomeni, da uporaba glasu kot varnostnega sistema, kar banke vse bolj poskušajo, ni več dobra ideja, saj lahko kdorkoli z nekaj minutami posnetka vašega glasu posnema vas.

Ti veliki modeli strojnega učenja se usposabljajo za združitev vseh treh korakov v celovite sintetizatorje govora.

## Nastavitev časovnika

Za nastavitev časovnika mora vaša IoT naprava poklicati REST končno točko, ki ste jo ustvarili z uporabo strežniške kode, nato pa uporabiti pridobljeno število sekund za nastavitev časovnika.

### Naloga - pokličite strežniško funkcijo za pridobitev časa časovnika

Sledite ustreznemu vodniku za klic REST končne točke iz vaše IoT naprave in nastavite časovnik za zahtevani čas:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Enočipni računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-set-timer.md)

## Pretvorba besedila v govor

Ista storitev za govor, ki ste jo uporabili za pretvorbo govora v besedilo, se lahko uporabi za pretvorbo besedila nazaj v govor, ki se predvaja prek zvočnika na vaši IoT napravi. Besedilo za pretvorbo se pošlje storitvi za govor skupaj z vrsto zahtevanega zvoka (kot je vzorčna frekvenca), nato pa se vrnejo binarni podatki, ki vsebujejo zvok.

Ko pošljete to zahtevo, jo pošljete z uporabo *Speech Synthesis Markup Language* (SSML), XML-jezikovne oznake za aplikacije za sintezo govora. Ta ne določa le besedila za pretvorbo, temveč tudi jezik besedila, glas za uporabo, in lahko celo določi hitrost, glasnost ter ton za nekatere ali vse besede v besedilu.

Na primer, ta SSML definira zahtevo za pretvorbo besedila "Your 3 minute 5 second time has been set" v govor z uporabo britanskega angleškega glasu, imenovanega `en-GB-MiaNeural`.

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Večina sistemov za pretvorbo besedila v govor ima več glasov za različne jezike, z ustreznimi naglasi, kot je britanski angleški glas z angleškim naglasom in novozelandski angleški glas z novozelandskim naglasom.

### Naloga - pretvorite besedilo v govor

Sledite ustreznemu vodniku za pretvorbo besedila v govor z uporabo vaše IoT naprave:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Enočipni računalnik - Raspberry Pi](pi-text-to-speech.md)
* [Enočipni računalnik - Virtualna naprava](virtual-device-text-to-speech.md)

---

## 🚀 Izziv

SSML omogoča spreminjanje načina izgovorjave besed, kot je dodajanje poudarka določenim besedam, dodajanje premorov ali spreminjanje tona. Preizkusite nekatere od teh možnosti, pošljite različne SSML iz vaše IoT naprave in primerjajte rezultate. Več o SSML, vključno s tem, kako spremeniti način izgovorjave besed, lahko preberete v [specifikaciji Speech Synthesis Markup Language (SSML) Version 1.1 od World Wide Web konzorcija](https://www.w3.org/TR/speech-synthesis11/).

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Pregled in samostojno učenje

* Preberite več o sintezi govora na [strani o sintezi govora na Wikipediji](https://wikipedia.org/wiki/Speech_synthesis)
* Preberite več o načinih, kako kriminalci uporabljajo sintezo govora za krajo, v [zgodbi o lažnih glasovih 'pomagajo kibernetskim kriminalcem ukrasti denar' na BBC novicah](https://www.bbc.com/news/technology-48908736)
* Spoznajte več o tveganjih za glasovne igralce zaradi sintetiziranih različic njihovih glasov v [članku na Vice: 'Tožba TikToka poudarja, kako AI škodi glasovnim igralcem'](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Naloga

[Prekličite časovnik](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.