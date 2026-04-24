# Suport pentru mai multe limbi

![O prezentare grafică a acestei lecții](../../../../../translated_images/ro/lesson-24.4246968ed058510a.webp)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

Acest videoclip oferă o prezentare generală a serviciilor de vorbire Azure, acoperind conversia vorbirii în text și textului în vorbire din lecțiile anterioare, precum și traducerea vorbirii, un subiect abordat în această lecție:

[![Recunoașterea vorbirii cu câteva linii de cod Python de la Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Click pe imaginea de mai sus pentru a viziona videoclipul

## Test înainte de lecție

[Test înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introducere

În ultimele 3 lecții ai învățat despre conversia vorbirii în text, înțelegerea limbajului și conversia textului în vorbire, toate alimentate de AI. Un alt domeniu al comunicării umane în care AI poate ajuta este traducerea limbajului - conversia dintr-o limbă în alta, cum ar fi din engleză în franceză.

În această lecție vei învăța cum să folosești AI pentru a traduce text, permițând cronometrului inteligent să interacționeze cu utilizatorii în mai multe limbi.

În această lecție vom acoperi:

* [Traducerea textului](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Servicii de traducere](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Crearea unei resurse de traducere](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Suport pentru mai multe limbi în aplicații cu traduceri](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Traducerea textului folosind un serviciu AI](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Aceasta este ultima lecție din acest proiect, așa că după ce finalizezi lecția și sarcina, nu uita să cureți serviciile cloud. Vei avea nevoie de aceste servicii pentru a finaliza sarcina, așa că asigură-te că o finalizezi mai întâi.
>
> Consultă [ghidul de curățare a proiectului](../../../clean-up.md) dacă este necesar pentru instrucțiuni despre cum să faci acest lucru.

## Traducerea textului

Traducerea textului a fost o problemă în informatică cercetată de peste 70 de ani, și abia acum, datorită progreselor în AI și puterea de calcul, este aproape de a fi rezolvată la un nivel aproape la fel de bun ca traducătorii umani.

> 💁 Originile pot fi urmărite chiar mai departe, până la [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), un criptograf arab din secolul al IX-lea care a dezvoltat tehnici pentru traducerea limbajului.

### Traduceri automate

Traducerea textului a început ca o tehnologie cunoscută sub numele de Traducere Automată (MT), care poate traduce între perechi de limbi diferite. MT funcționează prin substituirea cuvintelor dintr-o limbă cu altele, adăugând tehnici pentru a selecta modalitățile corecte de traducere a frazelor sau părților de propoziții atunci când o traducere simplă cuvânt-cu-cuvânt nu are sens.

> 🎓 Când traducătorii suportă traducerea între o limbă și alta, acestea sunt cunoscute sub numele de *perechi de limbi*. Diferite instrumente suportă diferite perechi de limbi, iar acestea pot să nu fie complete. De exemplu, un traducător poate suporta engleză-spaniolă ca pereche de limbi și spaniolă-italiană ca pereche de limbi, dar nu engleză-italiană.

De exemplu, traducerea "Hello world" din engleză în franceză poate fi realizată prin substituție - "Bonjour" pentru "Hello" și "le monde" pentru "world", ducând la traducerea corectă "Bonjour le monde".

Substituțiile nu funcționează atunci când diferite limbi folosesc modalități diferite de a spune același lucru. De exemplu, propoziția în engleză "My name is Jim" se traduce în franceză ca "Je m'appelle Jim" - literalmente "Eu mă numesc Jim". "Je" este franceză pentru "Eu", "moi" este "mă", dar este concatenat cu verbul deoarece începe cu o vocală, devenind "m'", "appelle" înseamnă "a numi", iar "Jim" nu este tradus deoarece este un nume și nu un cuvânt care poate fi tradus. Ordinea cuvintelor devine, de asemenea, o problemă - o simplă substituție a "Je m'appelle Jim" devine "Eu mă numesc Jim", cu o ordine diferită a cuvintelor față de engleză.

> 💁 Unele cuvinte nu sunt niciodată traduse - numele meu este Jim indiferent de limba folosită pentru a mă prezenta. Când se traduce în limbi care folosesc alfabete diferite sau litere diferite pentru sunete diferite, atunci cuvintele pot fi *transliterate*, adică selectarea literelor sau caracterelor care oferă sunetul potrivit pentru a suna la fel ca cuvântul dat.

Idiomurile sunt, de asemenea, o problemă pentru traducere. Acestea sunt expresii care au un sens înțeles diferit de interpretarea directă a cuvintelor. De exemplu, în engleză idiomul "I've got ants in my pants" nu se referă literal la a avea furnici în haine, ci la a fi neliniștit. Dacă ai traduce acest lucru în germană, ai ajunge să confunzi ascultătorul, deoarece versiunea germană este "Am albine în fund".

> 💁 Diferite regiuni adaugă complexități diferite. Cu idiomul "ants in your pants", în engleza americană "pants" se referă la haine exterioare, în engleza britanică, "pants" înseamnă lenjerie intimă.

✅ Dacă vorbești mai multe limbi, gândește-te la câteva expresii care nu se traduc direct.

Sistemele de traducere automată se bazează pe baze de date mari de reguli care descriu cum să traduci anumite fraze și idiomuri, împreună cu metode statistice pentru a alege traducerile potrivite din opțiunile posibile. Aceste metode statistice folosesc baze de date uriașe de lucrări traduse de oameni în mai multe limbi pentru a alege cea mai probabilă traducere, o tehnică numită *traducere automată statistică*. Unele dintre acestea folosesc reprezentări intermediare ale limbii, permițând unei limbi să fie tradusă în intermediar, apoi din intermediar în altă limbă. În acest fel, adăugarea mai multor limbi implică traduceri către și din intermediar, nu către și din toate celelalte limbi.

### Traduceri neuronale

Traducerile neuronale implică utilizarea puterii AI pentru a traduce, de obicei traducând propoziții întregi folosind un singur model. Aceste modele sunt antrenate pe seturi de date uriașe care au fost traduse de oameni, cum ar fi pagini web, cărți și documentație a Națiunilor Unite.

Modelele de traducere neuronală sunt de obicei mai mici decât modelele de traducere automată datorită faptului că nu necesită baze de date uriașe de fraze și idiomuri. Serviciile AI moderne care oferă traduceri combină adesea mai multe tehnici, amestecând traducerea automată statistică și traducerea neuronală.

Nu există o traducere 1:1 pentru nicio pereche de limbi. Diferite modele de traducere vor produce rezultate ușor diferite în funcție de datele utilizate pentru antrenarea modelului. Traducerile nu sunt întotdeauna simetrice - adică dacă traduci o propoziție dintr-o limbă în alta, apoi înapoi în prima limbă, este posibil să vezi o propoziție ușor diferită ca rezultat.

✅ Încearcă diferiți traducători online, cum ar fi [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) sau aplicația Apple Translate. Compară versiunile traduse ale câtorva propoziții. Încearcă, de asemenea, să traduci într-unul, apoi să traduci înapoi în altul.

## Servicii de traducere

Există o serie de servicii AI care pot fi utilizate din aplicațiile tale pentru a traduce vorbirea și textul.

### Serviciul de vorbire Cognitive Services

![Logo-ul serviciului de vorbire](../../../../../translated_images/ro/azure-speech-logo.a1f08c4befb0159f.webp)

Serviciul de vorbire pe care l-ai utilizat în lecțiile anterioare are capabilități de traducere pentru recunoașterea vorbirii. Când recunoști vorbirea, poți solicita nu doar textul vorbirii în aceeași limbă, ci și în alte limbi.

> 💁 Acest lucru este disponibil doar din SDK-ul de vorbire, API-ul REST nu are traduceri integrate.

### Serviciul Translator Cognitive Services

![Logo-ul serviciului Translator](../../../../../translated_images/ro/azure-translator-logo.c6ed3a4a433edfd2.webp)

Serviciul Translator este un serviciu dedicat traducerii care poate traduce textul dintr-o limbă în una sau mai multe limbi țintă. Pe lângă traducere, acesta suportă o gamă largă de funcții suplimentare, inclusiv mascarea limbajului obscen. De asemenea, îți permite să oferi o traducere specifică pentru un anumit cuvânt sau propoziție, pentru a lucra cu termeni pe care nu dorești să-i traduci sau să ai o traducere bine-cunoscută.

De exemplu, când traduci propoziția "I have a Raspberry Pi", referindu-te la computerul cu o singură placă, într-o altă limbă, cum ar fi franceza, ai dori să păstrezi numele "Raspberry Pi" așa cum este și să nu-l traduci, obținând "J’ai un Raspberry Pi" în loc de "J’ai une pi aux framboises".

## Crearea unei resurse de traducere

Pentru această lecție vei avea nevoie de o resursă Translator. Vei folosi API-ul REST pentru a traduce textul.

### Sarcină - crearea unei resurse de traducere

1. Din terminalul sau promptul de comandă, rulează următoarea comandă pentru a crea o resursă Translator în grupul de resurse `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Înlocuiește `<location>` cu locația utilizată la crearea grupului de resurse.

1. Obține cheia pentru serviciul Translator:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Ia o copie a uneia dintre chei.

## Suport pentru mai multe limbi în aplicații cu traduceri

Într-o lume ideală, întreaga aplicație ar trebui să înțeleagă cât mai multe limbi diferite, de la ascultarea vorbirii, la înțelegerea limbajului, până la răspunsul cu vorbire. Acest lucru implică multă muncă, așa că serviciile de traducere pot accelera timpul de livrare al aplicației tale.

![O arhitectură de cronometru inteligent care traduce japoneza în engleză, procesează în engleză, apoi traduce înapoi în japoneză](../../../../../translated_images/ro/translated-smart-timer.08ac20057fdc5c37.webp)

Imaginează-ți că construiești un cronometru inteligent care folosește engleza de la un capăt la altul, înțelegând vorbirea în engleză și convertind-o în text, rulând înțelegerea limbajului în engleză, construind răspunsuri în engleză și răspunzând cu vorbire în engleză. Dacă ai dori să adaugi suport pentru japoneză, ai putea începe prin traducerea vorbirii japoneze în text englez, apoi păstrând nucleul aplicației la fel, apoi traducând textul răspunsului în japoneză înainte de a răspunde cu vorbire. Acest lucru ți-ar permite să adaugi rapid suport pentru japoneză și poți extinde pentru a oferi suport complet de la un capăt la altul pentru japoneză mai târziu.

> 💁 Dezavantajul de a te baza pe traducerea automată este că diferite limbi și culturi au modalități diferite de a spune aceleași lucruri, astfel încât traducerea poate să nu se potrivească cu expresia pe care o aștepți.

Traducerile automate deschid, de asemenea, posibilități pentru aplicații și dispozitive care pot traduce conținut creat de utilizatori pe măsură ce este creat. Science fiction-ul prezintă frecvent 'traducători universali', dispozitive care pot traduce din limbi extraterestre în (de obicei) engleza americană. Aceste dispozitive sunt mai puțin science fiction, mai mult science fact, dacă ignorăm partea cu extratereștrii. Există deja aplicații și dispozitive care oferă traducerea în timp real a vorbirii și textului scris, folosind combinații de servicii de vorbire și traducere.

Un exemplu este aplicația pentru telefon mobil [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), demonstrată în acest videoclip:

[![Funcția live a Microsoft Translator în acțiune](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Click pe imaginea de mai sus pentru a viziona videoclipul

Imaginează-ți să ai un astfel de dispozitiv disponibil, mai ales când călătorești sau interacționezi cu persoane a căror limbă nu o cunoști. Dispozitivele de traducere automată în aeroporturi sau spitale ar oferi îmbunătățiri mult necesare în accesibilitate.

✅ Fă niște cercetări: Există dispozitive IoT de traducere disponibile comercial? Ce zici de capabilități de traducere integrate în dispozitive inteligente?

> 👽 Deși nu există traducători universali adevărați care să ne permită să vorbim cu extratereștri, [Microsoft Translator suportă Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Traducerea textului folosind un serviciu AI

Poți folosi un serviciu AI pentru a adăuga această capacitate de traducere la cronometrul tău inteligent.

### Sarcină - traducerea textului folosind un serviciu AI

Parcurge ghidul relevant pentru a traduce textul pe dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Computer cu o singură placă - Raspberry Pi](pi-translate-speech.md)
* [Computer cu o singură placă - Dispozitiv virtual](virtual-device-translate-speech.md)

---

## 🚀 Provocare

Cum pot traducerile automate să beneficieze alte aplicații IoT dincolo de dispozitivele inteligente? Gândește-te la diferite moduri în care traducerile pot ajuta, nu doar cu cuvintele vorbite, ci și cu textul.

## Test după lecție

[Test după lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Recapitulare și studiu individual

* Citește mai multe despre traducerea automată pe [pagina de traducere automată de pe Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Citește mai multe despre traducerea neuronală pe [pagina de traducere neuronală de pe Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Consultă lista de limbi suportate pentru serviciile de vorbire Microsoft în [documentația despre suportul pentru limbă și voce pentru serviciul de vorbire pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Sarcină

[Construiește un traducător universal](assignment.md)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.