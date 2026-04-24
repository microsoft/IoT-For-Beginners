# Introducere în IoT

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-1.2606670fa61ee904.webp)

> Ilustrație realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

Această lecție a fost predată ca parte a seriei [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) de la [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lecția a fost prezentată în două videoclipuri - o lecție de o oră și o sesiune de întrebări și răspunsuri de o oră, în care s-au aprofundat anumite părți ale lecției.

[![Lecția 1: Introducere în IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lecția 1: Introducere în IoT - Sesiune de întrebări și răspunsuri](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Faceți clic pe imaginile de mai sus pentru a viziona videoclipurile

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introducere

Această lecție acoperă câteva subiecte introductive despre Internetul Lucrurilor (IoT) și vă ajută să vă configurați hardware-ul.

În această lecție vom discuta despre:

* [Ce este „Internetul Lucrurilor”?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Dispozitive IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Configurarea dispozitivului](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplicații ale IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Exemple de dispozitive IoT din jurul vostru](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Ce este „Internetul Lucrurilor”?

Termenul „Internetul Lucrurilor” a fost introdus de [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) în 1999, pentru a descrie conectarea Internetului la lumea fizică prin intermediul senzorilor. De atunci, termenul a fost folosit pentru a descrie orice dispozitiv care interacționează cu lumea fizică din jurul său, fie prin colectarea de date de la senzori, fie prin oferirea de interacțiuni reale prin actuatoare (dispozitive care fac ceva, cum ar fi să aprindă un bec sau să activeze un comutator), de obicei conectate la alte dispozitive sau la Internet.

> **Senzorii** colectează informații din mediul înconjurător, cum ar fi măsurarea vitezei, temperaturii sau locației.
>
> **Actuatoarele** transformă semnalele electrice în interacțiuni reale, cum ar fi activarea unui comutator, aprinderea luminilor, emiterea de sunete sau trimiterea de semnale de control către alte echipamente, de exemplu, pentru a porni o priză.

IoT ca domeniu tehnologic înseamnă mai mult decât dispozitive - include servicii bazate pe cloud care pot procesa datele senzorilor sau pot trimite comenzi către actuatoare conectate la dispozitive IoT. De asemenea, include dispozitive care nu au sau nu necesită conectivitate la Internet, adesea numite dispozitive edge. Acestea sunt dispozitive care pot procesa și răspunde singure la datele senzorilor, de obicei folosind modele AI antrenate în cloud.

IoT este un domeniu tehnologic în plină expansiune. Se estimează că, până la sfârșitul anului 2020, 30 de miliarde de dispozitive IoT au fost implementate și conectate la Internet. Privind spre viitor, se estimează că, până în 2025, dispozitivele IoT vor colecta aproape 80 de zettabytes de date, adică 80 de trilioane de gigabytes. Este o cantitate enormă de date!

![Un grafic care arată creșterea dispozitivelor IoT active în timp, de la mai puțin de 5 miliarde în 2015 la peste 30 de miliarde în 2025](../../../../../images/connected-iot-devices.svg)

✅ Faceți puțină cercetare: Cât din datele generate de dispozitivele IoT sunt efectiv utilizate și cât este irosit? De ce sunt ignorate atât de multe date?

Aceste date sunt cheia succesului IoT. Pentru a deveni un dezvoltator IoT de succes, trebuie să înțelegeți ce date trebuie colectate, cum să le colectați, cum să luați decizii pe baza lor și cum să utilizați aceste decizii pentru a interacționa cu lumea fizică, dacă este necesar.

## Dispozitive IoT

Litera **T** din IoT vine de la **Things** (Lucruri) - dispozitive care interacționează cu lumea fizică din jurul lor, fie prin colectarea de date de la senzori, fie prin oferirea de interacțiuni reale prin actuatoare.

Dispozitivele pentru uz comercial sau industrial, cum ar fi brățările de fitness pentru consumatori sau controlerele pentru mașini industriale, sunt de obicei personalizate. Acestea folosesc plăci de circuite personalizate, poate chiar procesoare personalizate, proiectate pentru a îndeplini cerințele unei anumite sarcini, fie că este vorba de a fi suficient de mici pentru a încăpea pe o încheietură, fie suficient de robuste pentru a funcționa într-un mediu industrial cu temperaturi ridicate, stres sau vibrații.

Ca dezvoltator care învață despre IoT sau creează un prototip de dispozitiv, va trebui să începeți cu un kit de dezvoltare. Acestea sunt dispozitive IoT general-purpose (cu scop general) proiectate pentru dezvoltatori, adesea cu caracteristici pe care nu le-ați găsi pe un dispozitiv de producție, cum ar fi pini externi pentru conectarea senzorilor sau actuatoarelor, hardware pentru depanare sau resurse suplimentare care ar adăuga costuri inutile într-o producție de masă.

Aceste kituri de dezvoltare se împart de obicei în două categorii - microcontrolere și computere pe o singură placă. Acestea vor fi introduse aici, iar în lecția următoare vom intra în mai multe detalii.

> 💁 Telefonul vostru poate fi considerat, de asemenea, un dispozitiv IoT general-purpose, având senzori și actuatoare integrate, cu diferite aplicații care utilizează acești senzori și actuatoare în moduri diferite, împreună cu diverse servicii cloud. Puteți găsi chiar și unele tutoriale IoT care folosesc o aplicație de telefon ca dispozitiv IoT.

### Microcontrolere

Un microcontroler (denumit și MCU, prescurtare de la microcontroller unit) este un mic computer format din:

🧠 Una sau mai multe unități centrale de procesare (CPU-uri) - „creierul” microcontrolerului care rulează programul vostru

💾 Memorie (RAM și memorie pentru programe) - unde sunt stocate programul, datele și variabilele voastre

🔌 Conexiuni de intrare/ieșire programabile (I/O) - pentru a comunica cu periferice externe (dispozitive conectate) cum ar fi senzori și actuatoare

Microcontrolerele sunt dispozitive de calcul cu costuri reduse, cu prețuri medii pentru cele utilizate în hardware personalizat scăzând la aproximativ 0,50 USD, iar unele dispozitive costând chiar și 0,03 USD. Kiturile de dezvoltare pot începe de la 4 USD, cu costuri care cresc pe măsură ce adăugați mai multe funcții. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un kit de dezvoltare pentru microcontrolere de la [Seeed studios](https://www.seeedstudio.com), care include senzori, actuatoare, WiFi și un ecran, costă aproximativ 30 USD.

![Un Wio Terminal](../../../../../translated_images/ro/wio-terminal.b8299ee16587db9a.webp)

> 💁 Când căutați pe Internet microcontrolere, fiți atenți la termenul **MCU**, deoarece acesta va aduce multe rezultate despre Universul Cinematic Marvel, nu despre microcontrolere.

Microcontrolerele sunt proiectate pentru a fi programate să îndeplinească un număr limitat de sarcini foarte specifice, mai degrabă decât să fie computere general-purpose precum PC-urile sau Mac-urile. Cu excepția unor scenarii foarte specifice, nu puteți conecta un monitor, o tastatură și un mouse pentru a le utiliza în scopuri generale.

Kiturile de dezvoltare pentru microcontrolere vin de obicei cu senzori și actuatoare suplimentare integrate. Majoritatea plăcilor vor avea unul sau mai multe LED-uri pe care le puteți programa, împreună cu alte dispozitive, cum ar fi prize standard pentru adăugarea mai multor senzori sau actuatoare folosind ecosistemele diferiților producători sau senzori integrați (de obicei cei mai populari, cum ar fi senzorii de temperatură). Unele microcontrolere au conectivitate wireless integrată, cum ar fi Bluetooth sau WiFi, sau au microcontrolere suplimentare pe placă pentru a adăuga această conectivitate.

> 💁 Microcontrolerele sunt de obicei programate în C/C++.

### Computere pe o singură placă

Un computer pe o singură placă este un dispozitiv de calcul mic care conține toate elementele unui computer complet pe o singură placă mică. Acestea sunt dispozitive cu specificații apropiate de un PC sau Mac desktop sau laptop, rulează un sistem de operare complet, dar sunt mai mici, consumă mai puțină energie și sunt considerabil mai ieftine.

![Un Raspberry Pi 4](../../../../../translated_images/ro/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi este unul dintre cele mai populare computere pe o singură placă.

La fel ca un microcontroler, computerele pe o singură placă au un CPU, memorie și pini de intrare/ieșire, dar au caracteristici suplimentare, cum ar fi un cip grafic pentru a permite conectarea monitoarelor, ieșiri audio și porturi USB pentru conectarea tastaturilor, șoarecilor și altor dispozitive USB standard, cum ar fi camerele web sau stocarea externă. Programele sunt stocate pe carduri SD sau hard disk-uri împreună cu un sistem de operare, în loc de un cip de memorie integrat în placă.

> 🎓 Puteți considera un computer pe o singură placă ca o versiune mai mică, mai ieftină a PC-ului sau Mac-ului pe care citiți acest text, cu adăugarea pinilor GPIO (intrare/ieșire general-purpose) pentru a interacționa cu senzori și actuatoare.

Computerele pe o singură placă sunt computere complet funcționale, așa că pot fi programate în orice limbaj. Dispozitivele IoT sunt de obicei programate în Python.

### Alegerea hardware-ului pentru lecțiile următoare

Toate lecțiile ulterioare includ sarcini care utilizează un dispozitiv IoT pentru a interacționa cu lumea fizică și pentru a comunica cu cloud-ul. Fiecare lecție suportă 3 opțiuni de dispozitive - Arduino (folosind un Seeed Studios Wio Terminal) sau un computer pe o singură placă, fie un dispozitiv fizic (un Raspberry Pi 4), fie un computer virtual pe o singură placă care rulează pe PC-ul sau Mac-ul vostru.

Puteți citi despre hardware-ul necesar pentru a finaliza toate sarcinile în [ghidul hardware](../../../hardware.md).

> 💁 Nu este necesar să achiziționați hardware IoT pentru a finaliza sarcinile, puteți face totul folosind un computer virtual pe o singură placă.

Alegerea hardware-ului depinde de ceea ce aveți disponibil acasă sau la școală și de limbajul de programare pe care îl cunoașteți sau pe care intenționați să îl învățați. Ambele variante hardware vor folosi același ecosistem de senzori, așa că, dacă începeți cu una dintre opțiuni, puteți trece la cealaltă fără a fi nevoie să înlocuiți majoritatea kitului. Computerul virtual pe o singură placă va fi echivalent cu învățarea pe un Raspberry Pi, iar majoritatea codului va fi transferabil pe un Pi dacă veți achiziționa ulterior un dispozitiv și senzori.

### Kit de dezvoltare Arduino

Dacă sunteți interesați să învățați dezvoltarea microcontrolerelor, puteți finaliza sarcinile folosind un dispozitiv Arduino. Veți avea nevoie de o înțelegere de bază a programării în C/C++, deoarece lecțiile vor preda doar codul relevant pentru cadrul Arduino, senzorii și actuatoarele utilizate și bibliotecile care interacționează cu cloud-ul.

Sarcinile vor utiliza [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) cu extensia [PlatformIO pentru dezvoltarea microcontrolerelor](https://platformio.org). De asemenea, puteți utiliza Arduino IDE dacă aveți experiență cu acest instrument, deoarece instrucțiuni suplimentare nu vor fi furnizate.

### Kit de dezvoltare pentru computere pe o singură placă

Dacă sunteți interesați să învățați dezvoltarea IoT folosind computere pe o singură placă, puteți finaliza sarcinile folosind un Raspberry Pi sau un dispozitiv virtual care rulează pe PC-ul sau Mac-ul vostru.

Veți avea nevoie de o înțelegere de bază a programării în Python, deoarece lecțiile vor preda doar codul relevant pentru senzorii și actuatoarele utilizate și bibliotecile care interacționează cu cloud-ul.

> 💁 Dacă doriți să învățați să programați în Python, consultați următoarele două serii video:
>
> * [Python pentru începători](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mai mult Python pentru începători](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Sarcinile vor utiliza [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Dacă utilizați un Raspberry Pi, puteți fie să rulați Pi-ul folosind versiunea completă desktop a Raspberry Pi OS și să faceți toată programarea direct pe Pi folosind [versiunea Raspberry Pi OS a VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), fie să rulați Pi-ul ca dispozitiv fără ecran și să programați de pe PC-ul sau Mac-ul vostru folosind VS Code cu extensia [Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), care vă permite să vă conectați la Pi și să editați, depanați și rulați codul ca și cum ați programa direct pe el.

Dacă utilizați opțiunea dispozitivului virtual, veți programa direct pe computerul vostru. În loc să accesați senzori și actuatoare, veți utiliza un instrument pentru a simula acest hardware, oferind valori ale senzorilor pe care le puteți defini și afișând rezultatele actuatoarelor pe ecran.

## Configurarea dispozitivului

Înainte de a începe programarea dispozitivului IoT, va trebui să faceți o mică configurare. Urmați instrucțiunile relevante de mai jos, în funcție de dispozitivul pe care îl veți utiliza.
💁 Dacă încă nu ai un dispozitiv, consultă [ghidul hardware](../../../hardware.md) pentru a te ajuta să decizi ce dispozitiv vei folosi și ce hardware suplimentar trebuie să achiziționezi. Nu este necesar să achiziționezi hardware, deoarece toate proiectele pot fi rulate pe hardware virtual.
Aceste instrucțiuni includ linkuri către site-uri web ale terților, create de producătorii hardware-ului sau instrumentelor pe care le veți utiliza. Acest lucru este pentru a vă asigura că folosiți întotdeauna cele mai actualizate instrucțiuni pentru diversele instrumente și hardware.

Parcurgeți ghidul relevant pentru a configura dispozitivul și pentru a finaliza un proiect „Hello World”. Acesta va fi primul pas în crearea unei lămpi de noapte IoT pe parcursul celor 4 lecții din această parte introductivă.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Computer cu placă unică - Raspberry Pi](pi.md)
* [Computer cu placă unică - Dispozitiv virtual](virtual-device.md)

✅ Veți folosi VS Code atât pentru Arduino, cât și pentru computerele cu placă unică. Dacă nu l-ați utilizat până acum, citiți mai multe despre acesta pe [site-ul VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Aplicații ale IoT

IoT acoperă o gamă largă de utilizări, împărțite în câteva categorii principale:

* IoT pentru consumatori
* IoT comercial
* IoT industrial
* IoT pentru infrastructură

✅ Faceți puțin cercetare: Pentru fiecare dintre domeniile descrise mai jos, găsiți un exemplu concret care nu este menționat în text.

### IoT pentru consumatori

IoT pentru consumatori se referă la dispozitivele IoT pe care consumatorii le cumpără și le folosesc acasă. Unele dintre aceste dispozitive sunt extrem de utile, cum ar fi difuzoarele inteligente, sistemele inteligente de încălzire și aspiratoarele robotizate. Altele sunt discutabile în ceea ce privește utilitatea lor, cum ar fi robinetele controlate prin voce, care pot deveni problematice atunci când nu le puteți opri deoarece controlul vocal nu vă aude din cauza zgomotului apei curgătoare.

Dispozitivele IoT pentru consumatori le oferă oamenilor posibilitatea de a face mai multe în mediul lor, în special celor 1 miliard de persoane care au o dizabilitate. Aspiratoarele robotizate pot oferi podele curate persoanelor cu probleme de mobilitate care nu pot aspira singure, cuptoarele controlate prin voce permit persoanelor cu deficiențe de vedere sau control motor să își încălzească cuptoarele doar prin voce, iar monitoarele de sănătate permit pacienților să își monitorizeze afecțiunile cronice cu actualizări mai frecvente și mai detaliate. Aceste dispozitive devin atât de omniprezente încât chiar și copiii mici le folosesc în viața lor de zi cu zi, de exemplu, elevii care fac școală virtuală în timpul pandemiei COVID folosind dispozitive inteligente pentru a seta cronometre pentru temele lor sau alarme pentru a le aminti de întâlnirile de clasă.

✅ Ce dispozitive IoT pentru consumatori aveți asupra voastră sau acasă?

### IoT comercial

IoT comercial acoperă utilizarea IoT la locul de muncă. Într-un birou, pot exista senzori de ocupare și detectoare de mișcare pentru a gestiona iluminatul și încălzirea, astfel încât luminile și căldura să fie oprite atunci când nu sunt necesare, reducând costurile și emisiile de carbon. Într-o fabrică, dispozitivele IoT pot monitoriza pericolele de siguranță, cum ar fi muncitorii care nu poartă căști de protecție sau zgomotul care a atins niveluri periculoase. În retail, dispozitivele IoT pot măsura temperatura depozitelor frigorifice, alertând proprietarul magazinului dacă un frigider sau congelator este în afara intervalului de temperatură necesar, sau pot monitoriza produsele de pe rafturi pentru a direcționa angajații să reumple produsele vândute. Industria transporturilor se bazează din ce în ce mai mult pe IoT pentru a monitoriza locațiile vehiculelor, a urmări kilometrajul pe drum pentru taxarea utilizatorilor de drumuri, a verifica orele de lucru și pauzele șoferilor sau a notifica personalul când un vehicul se apropie de un depozit pentru a se pregăti de încărcare sau descărcare.

✅ Ce dispozitive IoT comerciale aveți în școală sau la locul de muncă?

### IoT industrial (IIoT)

IoT industrial, sau IIoT, reprezintă utilizarea dispozitivelor IoT pentru a controla și gestiona mașinile la scară largă. Acesta acoperă o gamă largă de utilizări, de la fabrici la agricultură digitală.

Fabricile folosesc dispozitive IoT în multe moduri diferite. Mașinile pot fi monitorizate cu mai mulți senzori pentru a urmări lucruri precum temperatura, vibrațiile și viteza de rotație. Aceste date pot fi monitorizate pentru a permite oprirea mașinii dacă depășește anumite toleranțe - de exemplu, dacă se supraîncălzește, aceasta este oprită. Aceste date pot fi, de asemenea, colectate și analizate în timp pentru a face întreținere predictivă, unde modelele AI analizează datele care preced o defecțiune și le folosesc pentru a prezice alte defecțiuni înainte ca acestea să se întâmple.

Agricultura digitală este importantă pentru a hrăni populația în creștere, în special pentru cele 2 miliarde de persoane din 500 de milioane de gospodării care depind de [agricultura de subzistență](https://wikipedia.org/wiki/Subsistence_agriculture). Agricultura digitală poate varia de la senzori de câțiva dolari la configurații comerciale masive. Un fermier poate începe prin monitorizarea temperaturilor și utilizarea [zilelor de grad de creștere](https://wikipedia.org/wiki/Growing_degree-day) pentru a prezice când o cultură va fi gata de recoltare. Aceștia pot conecta monitorizarea umidității solului la sisteme automate de irigare pentru a oferi plantelor lor atât de multă apă cât este necesar, dar nu mai mult, pentru a se asigura că culturile nu se usucă fără a irosi apă. Fermierii merg chiar mai departe, folosind drone, date satelitare și AI pentru a monitoriza creșterea culturilor, bolile și calitatea solului pe suprafețe mari de teren agricol.

✅ Ce alte dispozitive IoT ar putea ajuta fermierii?

### IoT pentru infrastructură

IoT pentru infrastructură monitorizează și controlează infrastructura locală și globală pe care oamenii o folosesc zilnic.

[Orașele inteligente](https://wikipedia.org/wiki/Smart_city) sunt zone urbane care folosesc dispozitive IoT pentru a colecta date despre oraș și pentru a le utiliza pentru a îmbunătăți modul în care orașul funcționează. Aceste orașe sunt de obicei gestionate prin colaborări între guvernele locale, mediul academic și afacerile locale, monitorizând și gestionând lucruri variate, de la transport la parcare și poluare. De exemplu, în Copenhaga, Danemarca, poluarea aerului este importantă pentru locuitorii locali, astfel încât aceasta este măsurată, iar datele sunt utilizate pentru a oferi informații despre cele mai curate trasee pentru ciclism și jogging.

[Rețelele electrice inteligente](https://wikipedia.org/wiki/Smart_grid) permit o mai bună analiză a cererii de energie prin colectarea datelor de utilizare la nivelul fiecărei locuințe. Aceste date pot ghida deciziile la nivel de țară, inclusiv unde să se construiască noi centrale electrice, și la nivel personal, oferind utilizatorilor informații despre câtă energie consumă, când o consumă și chiar sugestii despre cum să reducă costurile, cum ar fi încărcarea mașinilor electrice pe timp de noapte.

✅ Dacă ați putea adăuga dispozitive IoT pentru a măsura ceva în zona în care locuiți, ce ar fi?

## Exemple de dispozitive IoT pe care le puteți avea în jurul vostru

Ați fi uimiți de câte dispozitive IoT aveți în jurul vostru. Scriu acest text de acasă și am următoarele dispozitive conectate la Internet, cu funcții inteligente, cum ar fi controlul prin aplicație, controlul vocal sau capacitatea de a trimite date către mine prin telefon:

* Mai multe difuzoare inteligente
* Frigider, mașină de spălat vase, cuptor și cuptor cu microunde
* Monitor de electricitate pentru panouri solare
* Prize inteligente
* Sonerie video și camere de securitate
* Termostat inteligent cu mai mulți senzori inteligenți pentru camere
* Deschizător de uși de garaj
* Sisteme de divertisment acasă și televizoare controlate prin voce
* Luminile
* Trackere de fitness și sănătate

Toate aceste tipuri de dispozitive au senzori și/sau actuatori și comunică cu Internetul. Pot verifica de pe telefon dacă ușa garajului meu este deschisă și pot cere difuzorului inteligent să o închidă pentru mine. Pot chiar să setez un cronometru, astfel încât dacă este încă deschisă noaptea, să se închidă automat. Când sună soneria, pot vedea de pe telefon cine este acolo, oriunde mă aflu în lume, și pot vorbi cu ei printr-un difuzor și microfon încorporat în sonerie. Pot monitoriza glicemia, ritmul cardiac și modelele de somn, căutând tipare în date pentru a-mi îmbunătăți sănătatea. Pot controla luminile prin cloud și pot sta în întuneric când conexiunea mea la Internet se întrerupe.

---

## 🚀 Provocare

Enumerați cât mai multe dispozitive IoT pe care le aveți acasă, la școală sau la locul de muncă - s-ar putea să fie mai multe decât credeți!

## Test după lecție

[Test după lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Recapitulare și studiu individual

Citiți despre beneficiile și eșecurile proiectelor IoT pentru consumatori. Verificați site-urile de știri pentru articole despre momentele în care acestea au eșuat, cum ar fi probleme de confidențialitate, probleme hardware sau probleme cauzate de lipsa conectivității.

Câteva exemple:

* Consultați contul de Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(avertisment: limbaj explicit)* pentru exemple bune de eșecuri ale IoT pentru consumatori.
* [c|net - My Apple Watch saved my life: 5 people share their stories](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT technician pleads guilty to spying on customer camera feeds for years](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(avertisment: voyeurism neconsensual)*

## Temă

[Investigați un proiect IoT](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.