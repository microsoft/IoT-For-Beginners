# Prepoznajte govor z IoT napravo

![Pregled lekcije v obliki sketchnote](../../../../../translated_images/sl/lesson-21.e34de51354d6606f.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta video ponuja pregled storitve Azure Speech, ki bo obravnavana v tej lekciji:

[![Kako začeti uporabljati vir Cognitive Services Speech iz YouTube kanala Microsoft Azure](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Kliknite zgornjo sliko za ogled videa

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Uvod

'Alexa, nastavi 12-minutni časovnik'

'Alexa, status časovnika'

'Alexa, nastavi 8-minutni časovnik z imenom kuhanje brokolija na pari'

Pametne naprave postajajo vse bolj razširjene. Ne le kot pametni zvočniki, kot so HomePods, Echos in Google Homes, ampak tudi vgrajene v naše telefone, ure, svetila in termostate.

> 💁 V mojem domu je vsaj 19 naprav z glasovnimi asistenti, in to so samo tiste, za katere vem!

Glasovno upravljanje povečuje dostopnost, saj omogoča ljudem z omejenim gibanjem interakcijo z napravami. Ne glede na to, ali gre za trajno invalidnost, kot je rojstvo brez rok, začasno invalidnost, kot so zlomljene roke, ali pa preprosto polne roke nakupov ali majhnih otrok, možnost upravljanja našega doma z glasom namesto z rokami odpira svet dostopnosti. Klicanje 'Hej Siri, zapri garažna vrata' med previjanjem dojenčka in ukvarjanjem z razposajenim malčkom je lahko majhna, a učinkovita izboljšava življenja.

Ena izmed bolj priljubljenih uporab glasovnih asistentov je nastavitev časovnikov, še posebej kuhinjskih časovnikov. Možnost nastavitve več časovnikov samo z glasom je velika pomoč v kuhinji – ni treba prenehati z gnetenjem testa, mešanjem juhe ali čiščenjem rok od nadeva za cmoke, da bi uporabili fizični časovnik.

V tej lekciji se boste naučili, kako vgraditi prepoznavanje glasu v IoT naprave. Spoznali boste mikrofone kot senzorje, kako zajeti zvok z mikrofonom, priključenim na IoT napravo, in kako uporabiti AI za pretvorbo slišanega v besedilo. V preostanku projekta boste izdelali pametni kuhinjski časovnik, ki bo omogočal nastavitev časovnikov z glasom v več jezikih.

V tej lekciji bomo obravnavali:

* [Mikrofoni](../../../../../6-consumer/lessons/1-speech-recognition)
* [Zajem zvoka z IoT naprave](../../../../../6-consumer/lessons/1-speech-recognition)
* [Govor v besedilo](../../../../../6-consumer/lessons/1-speech-recognition)
* [Pretvorba govora v besedilo](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofoni

Mikrofoni so analogni senzorji, ki pretvarjajo zvočne valove v električne signale. Vibracije v zraku povzročijo premikanje komponent v mikrofonu, kar povzroči majhne spremembe v električnih signalih. Te spremembe se nato ojačajo, da ustvarijo električni izhod.

### Vrste mikrofonov

Mikrofoni so na voljo v različnih vrstah:

* Dinamični - Dinamični mikrofoni imajo magnet, pritrjen na gibljivo membrano, ki se premika v tuljavi žice in ustvarja električni tok. To je nasprotje večine zvočnikov, ki uporabljajo električni tok za premikanje magneta v tuljavi žice, premikanje membrane za ustvarjanje zvoka. To pomeni, da se zvočniki lahko uporabljajo kot dinamični mikrofoni, dinamični mikrofoni pa kot zvočniki. V napravah, kot so domofoni, kjer uporabnik posluša ali govori, vendar ne oboje hkrati, lahko ena naprava deluje kot zvočnik in mikrofon.

    Dinamični mikrofoni ne potrebujejo napajanja za delovanje, električni signal se ustvari povsem iz mikrofona.

    ![Patti Smith poje v mikrofon Shure SM58 (dinamični kardioidni tip)](../../../../../translated_images/sl/dynamic-mic.8babac890a2d80df.webp)

* Trakasti - Trakasti mikrofoni so podobni dinamičnim mikrofonom, razen da imajo kovinski trak namesto membrane. Ta trak se premika v magnetnem polju in ustvarja električni tok. Tako kot dinamični mikrofoni trakasti mikrofoni ne potrebujejo napajanja za delovanje.

    ![Edmund Lowe, ameriški igralec, stoji ob radijskem mikrofonu (označen za (NBC) Blue Network), drži scenarij, 1942](../../../../../translated_images/sl/ribbon-mic.eacc8e092c7441ca.webp)

* Kondenzatorski - Kondenzatorski mikrofoni imajo tanko kovinsko membrano in fiksno kovinsko ploščo. Elektrika se uporablja na obeh, in ko membrana vibrira, se statični naboj med ploščama spreminja, kar ustvarja signal. Kondenzatorski mikrofoni potrebujejo napajanje za delovanje – imenovano *Phantom power*.

    ![C451B kondenzatorski mikrofon z majhno membrano znamke AKG Acoustics](../../../../../translated_images/sl/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS - Mikrofoni mikroelektromehanskih sistemov, ali MEMS, so mikrofoni na čipu. Imajo tlačno občutljivo membrano, vgravirano na silicijev čip, in delujejo podobno kot kondenzatorski mikrofon. Ti mikrofoni so lahko zelo majhni in integrirani v vezje.

    ![MEMS mikrofon na vezju](../../../../../translated_images/sl/mems-microphone.80574019e1f5e4d9.webp)

    Na zgornji sliki je čip z oznako **LEFT** MEMS mikrofon, z majhno membrano, široko manj kot milimeter.

✅ Raziskujte: Katere mikrofone imate okoli sebe – bodisi v računalniku, telefonu, slušalkah ali drugih napravah? Kakšne vrste mikrofonov so?

### Digitalni zvok

Zvok je analogni signal, ki nosi zelo podrobne informacije. Da bi ta signal pretvorili v digitalnega, ga je treba vzorčiti več tisočkrat na sekundo.

> 🎓 Vzorčenje je pretvorba zvočnega signala v digitalno vrednost, ki predstavlja signal v določenem trenutku.

![Graf, ki prikazuje signal z diskretnimi točkami v fiksnih intervalih](../../../../../translated_images/sl/sampling.6f4fadb3f2d9dfe7.webp)

Digitalni zvok se vzorči z uporabo modulacije pulznega kodeksa, ali PCM. PCM vključuje branje napetosti signala in izbiro najbližje diskretne vrednosti tej napetosti z uporabo določene velikosti.

> 💁 PCM lahko razumete kot senzorsko različico modulacije širine impulza, ali PWM (PWM je bil obravnavan v [lekciji 3 začetnega projekta](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM vključuje pretvorbo analognega signala v digitalnega, PWM pa pretvorbo digitalnega signala v analognega.

Na primer, večina storitev za pretakanje glasbe ponuja 16-bitni ali 24-bitni zvok. To pomeni, da napetost pretvorijo v vrednost, ki ustreza 16-bitnemu ali 24-bitnemu celoštevilskemu tipu. 16-bitni zvok ustreza vrednosti v razponu od -32.768 do 32.767, 24-bitni pa v razponu od −8.388.608 do 8.388.607. Več bitov pomeni, da je vzorec bližje temu, kar dejansko slišijo naša ušesa.

> 💁 Morda ste že slišali za 8-bitni zvok, pogosto imenovan LoFi. To je zvok, vzorčen z uporabo le 8 bitov, torej -128 do 127. Prvi računalniški zvok je bil omejen na 8 bitov zaradi strojnih omejitev, zato ga pogosto najdemo v retro igrah.

Ti vzorci se vzamejo več tisočkrat na sekundo, z uporabo dobro definiranih vzorčnih frekvenc, merjenih v KHz (tisoč odčitkov na sekundo). Storitve za pretakanje glasbe uporabljajo 48KHz za večino zvoka, nekatere 'brezizgubne' storitve pa uporabljajo do 96KHz ali celo 192KHz. Višja kot je vzorčna frekvenca, bližje je zvok originalu, do določene točke. Obstaja razprava, ali ljudje lahko zaznajo razliko nad 48KHz.

✅ Raziskujte: Če uporabljate storitev za pretakanje glasbe, kakšno vzorčno frekvenco in velikost uporablja? Če uporabljate CD-je, kakšna je vzorčna frekvenca in velikost zvoka na CD-jih?

Obstaja več različnih formatov za zvočne podatke. Verjetno ste že slišali za mp3 datoteke – zvočne podatke, ki so stisnjeni, da so manjši, ne da bi izgubili kakovost. Nestisnjen zvok je pogosto shranjen kot WAV datoteka – to je datoteka s 44 bajti glave, ki ji sledijo surovi zvočni podatki. Glava vsebuje informacije, kot so vzorčna frekvenca (na primer 16000 za 16KHz) in velikost vzorca (16 za 16-bitni), ter število kanalov. Po glavi WAV datoteka vsebuje surove zvočne podatke.

> 🎓 Kanali se nanašajo na to, koliko različnih zvočnih tokov sestavlja zvok. Na primer, za stereo zvok z levim in desnim kanalom bi bili 2 kanala. Za 7.1 prostorski zvok za domači kino bi bilo to 8 kanalov.

### Velikost zvočnih podatkov

Zvočni podatki so razmeroma veliki. Na primer, zajem nestisnjenega 16-bitnega zvoka pri 16KHz (dovolj dobra frekvenca za uporabo z modelom za pretvorbo govora v besedilo) zahteva 32KB podatkov za vsako sekundo zvoka:

* 16-bitni pomeni 2 bajta na vzorec (1 bajt je 8 bitov).
* 16KHz je 16.000 vzorcev na sekundo.
* 16.000 x 2 bajta = 32.000 bajtov na sekundo.

To se morda sliši kot majhna količina podatkov, vendar je lahko veliko, če uporabljate mikrokrmilnik z omejenim pomnilnikom. Na primer, Wio Terminal ima 192KB pomnilnika, ki mora shranjevati programsko kodo in spremenljivke. Tudi če bi bila vaša programska koda zelo majhna, ne bi mogli zajeti več kot 5 sekund zvoka.

Mikrokrmilniki lahko dostopajo do dodatnega pomnilnika, kot so SD kartice ali flash pomnilnik. Pri gradnji IoT naprave, ki zajema zvok, boste morali zagotoviti, da imate ne le dodaten pomnilnik, ampak da vaša koda zapisuje zajeti zvok neposredno v ta pomnilnik, in ko ga pošiljate v oblak, pretakate iz pomnilnika v spletno zahtevo. Tako se lahko izognete pomanjkanju pomnilnika, ker bi poskušali hkrati držati celoten blok zvočnih podatkov v pomnilniku.

## Zajem zvoka z IoT naprave

Vaša IoT naprava je lahko povezana z mikrofonom za zajem zvoka, pripravljenega za pretvorbo v besedilo. Prav tako je lahko povezana z zvočniki za predvajanje zvoka. V kasnejših lekcijah bo to uporabljeno za zvočne povratne informacije, vendar je koristno, da zvočnike nastavite že zdaj za testiranje mikrofona.

### Naloga - konfigurirajte mikrofon in zvočnike

Sledite ustreznemu vodniku za konfiguracijo mikrofona in zvočnikov za vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Enočipni računalnik - Raspberry Pi](pi-microphone.md)
* [Enočipni računalnik - Virtualna naprava](virtual-device-microphone.md)

### Naloga - zajem zvoka

Sledite ustreznemu vodniku za zajem zvoka na vaši IoT napravi:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Enočipni računalnik - Raspberry Pi](pi-audio.md)
* [Enočipni računalnik - Virtualna naprava](virtual-device-audio.md)

## Govor v besedilo

Govor v besedilo, ali prepoznavanje govora, vključuje uporabo AI za pretvorbo besed v zvočnem signalu v besedilo.

### Modeli za prepoznavanje govora

Za pretvorbo govora v besedilo se vzorci iz zvočnega signala združijo in vnesejo v model strojnega učenja, ki temelji na rekurentni nevronski mreži (RNN). To je vrsta modela strojnega učenja, ki lahko uporablja prejšnje podatke za sprejemanje odločitev o prihajajočih podatkih. Na primer, RNN lahko zazna en blok zvočnih vzorcev kot zvok 'Hel', in ko prejme drugega, za katerega meni, da je zvok 'lo', lahko to združi s prejšnjim zvokom, ugotovi, da je 'Hello' veljavna beseda, in jo izbere kot rezultat.

Modeli strojnega učenja vedno sprejemajo podatke enake velikosti vsakič. Razvrščevalnik slik, ki ste ga zgradili v prejšnji lekciji, spreminja velikost slik na fiksno velikost in jih obdeluje. Enako velja za modele govora, ki morajo obdelovati zvočne bloke fiksne velikosti. Modeli govora morajo biti sposobni združiti rezultate več napovedi, da dobijo odgovor, kar jim omogoča razlikovanje med 'Hi' in 'Highway' ali 'flock' in 'floccinaucinihilipilification'.

Modeli govora so tudi dovolj napredni, da razumejo kontekst in lahko popravijo besede, ki jih zaznajo, ko se obdeluje več zvokov. Na primer, če rečete "Šel sem v trgovino po dve banani in jabolko tudi", bi uporabili tri besede, ki zvenijo enako, vendar so zapisane različno – to, dve in tudi. Modeli govora lahko razumejo kontekst in uporabijo ustrezno črkovanje besede.
💁 Nekatere govorne storitve omogočajo prilagoditve, da bolje delujejo v hrupnih okoljih, kot so tovarne, ali z industrijsko specifičnimi izrazi, kot so imena kemikalij. Te prilagoditve se usposobijo z zagotavljanjem vzorčnih zvočnih posnetkov in prepisov ter delujejo s prenosnim učenjem, podobno kot ste v prejšnji lekciji usposobili klasifikator slik z le nekaj slikami.
### Zasebnost

Pri uporabi pretvorbe govora v besedilo na potrošniški IoT napravi je zasebnost izjemno pomembna. Te naprave neprestano poslušajo zvok, zato kot potrošnik ne želite, da se vse, kar rečete, pošilja v oblak in pretvori v besedilo. To ne le porabi veliko internetne pasovne širine, ampak ima tudi velike posledice za zasebnost, še posebej, ker nekateri proizvajalci pametnih naprav naključno izberejo zvok za [človeško preverjanje glede na generirano besedilo, da izboljšajo svoj model](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Pametne naprave želite pošiljati zvok v oblak za obdelavo le takrat, ko jih uporabljate, ne pa takrat, ko zaznajo zvok v vašem domu, zvok, ki lahko vključuje zasebne sestanke ali intimne interakcije. Večina pametnih naprav deluje s *budilno besedo*, ključno frazo, kot je "Alexa", "Hej Siri" ali "OK Google", ki napravo 'zbudi' in jo pripravi na poslušanje, dokler ne zazna premora v vašem govoru, kar pomeni, da ste končali z govorjenjem napravi.

> 🎓 Zaznavanje budilne besede se imenuje tudi *prepoznavanje ključnih besed* ali *iskanje ključnih besed*.

Te budilne besede se zaznajo na napravi, ne v oblaku. Pametne naprave imajo majhne AI modele, ki tečejo na napravi in poslušajo budilno besedo, ter ob zaznavi začnejo pretakati zvok v oblak za prepoznavo. Ti modeli so zelo specializirani in poslušajo le budilno besedo.

> 💁 Nekatera tehnološka podjetja dodajajo več zasebnosti svojim napravam in del pretvorbe govora v besedilo izvajajo na napravi. Apple je napovedal, da bodo kot del svojih posodobitev za iOS in macOS leta 2021 podpirali pretvorbo govora v besedilo na napravi ter lahko obdelali številne zahteve brez uporabe oblaka. To je omogočeno zaradi zmogljivih procesorjev v njihovih napravah, ki lahko poganjajo ML modele.

✅ Kakšne so po vašem mnenju posledice za zasebnost in etiko pri shranjevanju zvoka, poslanega v oblak? Ali bi moral biti ta zvok shranjen, in če da, kako? Ali menite, da je uporaba posnetkov za organe pregona dobra izmenjava za izgubo zasebnosti?

Zaznavanje budilne besede običajno uporablja tehniko, imenovano TinyML, ki omogoča pretvorbo ML modelov za delovanje na mikrokrmilnikih. Ti modeli so majhni in porabijo zelo malo energije za delovanje.

Da bi se izognili zapletenosti pri treniranju in uporabi modela za budilno besedo, bo pametni časovnik, ki ga gradite v tej lekciji, uporabljal gumb za vklop prepoznavanja govora.

> 💁 Če želite poskusiti ustvariti model za zaznavanje budilne besede, ki teče na Wio Terminalu ali Raspberry Pi, si oglejte ta [tutorial za odzivanje na vaš glas od Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Če želite to narediti na svojem računalniku, lahko poskusite [hitri začetek za prilagojene ključne besede na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Pretvorba govora v besedilo

![Logotip storitev govora](../../../../../translated_images/sl/azure-speech-logo.a1f08c4befb0159f.webp)

Tako kot pri klasifikaciji slik v prejšnjem projektu obstajajo vnaprej pripravljene AI storitve, ki lahko vzamejo govor kot zvočno datoteko in ga pretvorijo v besedilo. Ena takšnih storitev je Speech Service, del Cognitive Services, vnaprej pripravljenih AI storitev, ki jih lahko uporabite v svojih aplikacijah.

### Naloga - konfigurirajte AI vir za govor

1. Ustvarite skupino virov za ta projekt z imenom `smart-timer`.

1. Uporabite naslednji ukaz za ustvarjanje brezplačnega vira za govor:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju skupine virov.

1. Za dostop do vira za govor iz vaše kode boste potrebovali API ključ. Za pridobitev ključa zaženite naslednji ukaz:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopirajte enega od ključev.

### Naloga - pretvorite govor v besedilo

Sledite ustreznemu vodiču za pretvorbo govora v besedilo na vaši IoT napravi:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Eno-ploščni računalnik - Raspberry Pi](pi-speech-to-text.md)
* [Eno-ploščni računalnik - Virtualna naprava](virtual-device-speech-to-text.md)

---

## 🚀 Izziv

Prepoznavanje govora obstaja že dolgo časa in se nenehno izboljšuje. Raziskujte trenutne zmogljivosti in primerjajte, kako so se te razvijale skozi čas, vključno s tem, kako natančne so strojne transkripcije v primerjavi s človeškimi.

Kaj menite, kaj prinaša prihodnost za prepoznavanje govora?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Pregled in samostojno učenje

* Preberite o različnih vrstah mikrofonov in kako delujejo v [članku o razliki med dinamičnimi in kondenzatorskimi mikrofoni na Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Preberite več o storitvi govora Cognitive Services v [dokumentaciji o storitvi govora na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Preberite o prepoznavanju ključnih besed v [dokumentaciji o prepoznavanju ključnih besed na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Naloga

[](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.