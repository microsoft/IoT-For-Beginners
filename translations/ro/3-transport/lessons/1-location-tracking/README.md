# Urmărirea locației

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-11.9fddbac4b664c6d5.webp)

> Schiță realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introducere

Procesul principal de a aduce alimentele de la fermier la consumator implică încărcarea cutiilor cu produse pe camioane, nave, avioane sau alte vehicule comerciale de transport și livrarea alimentelor undeva - fie direct la un client, fie la un centru sau depozit central pentru procesare. Întregul proces de la fermă la consumator face parte dintr-un proces numit *lanț de aprovizionare*. Videoclipul de mai jos, realizat de Școala de Afaceri W. P. Carey a Universității de Stat din Arizona, explică mai detaliat conceptul de lanț de aprovizionare și modul în care este gestionat.

[![Ce este managementul lanțului de aprovizionare? Un videoclip de la Școala de Afaceri W. P. Carey a Universității de Stat din Arizona](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Faceți clic pe imaginea de mai sus pentru a viziona un videoclip

Adăugarea dispozitivelor IoT poate îmbunătăți semnificativ lanțul de aprovizionare, permițându-vă să gestionați locația articolelor, să planificați mai bine transportul și manipularea mărfurilor și să răspundeți mai rapid la probleme.

Când gestionați o flotă de vehicule, cum ar fi camioane, este util să știți unde se află fiecare vehicul la un moment dat. Vehiculele pot fi echipate cu senzori GPS care trimit locația lor către sistemele IoT, permițând proprietarilor să le localizeze, să vadă traseul parcurs și să știe când vor ajunge la destinație. Majoritatea vehiculelor operează în afara acoperirii WiFi, așa că folosesc rețele celulare pentru a trimite acest tip de date. Uneori, senzorul GPS este integrat în dispozitive IoT mai complexe, cum ar fi jurnalele electronice. Aceste dispozitive urmăresc cât timp a fost un camion în tranzit pentru a se asigura că șoferii respectă legile locale privind orele de lucru.

În această lecție veți învăța cum să urmăriți locația unui vehicul folosind un senzor GPS (Global Positioning System).

În această lecție vom acoperi:

* [Vehicule conectate](../../../../../3-transport/lessons/1-location-tracking)
* [Coordonate geospațiale](../../../../../3-transport/lessons/1-location-tracking)
* [Sisteme de poziționare globală (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Citirea datelor de la senzorul GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Date GPS NMEA](../../../../../3-transport/lessons/1-location-tracking)
* [Decodarea datelor de la senzorul GPS](../../../../../3-transport/lessons/1-location-tracking)

## Vehicule conectate

IoT transformă modul în care sunt transportate mărfurile prin crearea de flote de *vehicule conectate*. Aceste vehicule sunt conectate la sisteme IT centrale care raportează informații despre locația lor și alte date de la senzori. A avea o flotă de vehicule conectate oferă o gamă largă de beneficii:

* Urmărirea locației - puteți localiza un vehicul în orice moment, permițându-vă să:

  * Primiți alerte când un vehicul este pe cale să ajungă la destinație pentru a pregăti echipa de descărcare
  * Localizați vehiculele furate
  * Combinați datele despre locație și traseu cu problemele de trafic pentru a redirecționa vehiculele în timpul călătoriei
  * Respectați reglementările fiscale. Unele țări taxează vehiculele pentru kilometrajul parcurs pe drumurile publice (cum ar fi [RUC din Noua Zeelandă](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), astfel încât să știți când un vehicul este pe drumuri publice versus drumuri private face mai ușoară calcularea taxelor datorate.
  * Știți unde să trimiteți echipele de întreținere în cazul unei defecțiuni

* Telemetria șoferului - asigurarea că șoferii respectă limitele de viteză, iau curbele la viteze adecvate, frânează devreme și eficient și conduc în siguranță. Vehiculele conectate pot avea, de asemenea, camere pentru a înregistra incidente. Acest lucru poate fi legat de asigurare, oferind tarife reduse pentru șoferii buni.

* Respectarea orelor de lucru ale șoferilor - asigurarea că șoferii conduc doar în orele legale permise, pe baza momentelor în care pornesc și opresc motorul.

Aceste beneficii pot fi combinate - de exemplu, combinarea respectării orelor de lucru ale șoferilor cu urmărirea locației pentru a redirecționa șoferii dacă nu pot ajunge la destinație în orele permise de condus. Acestea pot fi, de asemenea, combinate cu alte date specifice vehiculului, cum ar fi datele despre temperatură din camioanele cu temperatură controlată, permițând redirecționarea vehiculelor dacă traseul actual ar însemna că mărfurile nu pot fi păstrate la temperatura necesară.

> 🎓 Logistica este procesul de transport al mărfurilor dintr-un loc în altul, cum ar fi de la o fermă la un supermarket prin unul sau mai multe depozite. Un fermier împachetează cutii cu roșii care sunt încărcate pe un camion, livrate la un depozit central și apoi puse pe un al doilea camion care poate conține un amestec de diferite tipuri de produse care sunt apoi livrate la un supermarket.

Componenta de bază a urmăririi vehiculelor este GPS - senzori care pot localiza poziția lor oriunde pe Pământ. În această lecție veți învăța cum să utilizați un senzor GPS, începând cu învățarea modului de a defini o locație pe Pământ.

## Coordonate geospațiale

Coordonatele geospațiale sunt utilizate pentru a defini puncte pe suprafața Pământului, similar cu modul în care coordonatele pot fi utilizate pentru a desena un pixel pe un ecran de computer sau pentru a poziționa cusături într-o broderie. Pentru un singur punct, aveți o pereche de coordonate. De exemplu, campusul Microsoft din Redmond, Washington, SUA este situat la 47.6423109, -122.1390293.

### Latitudine și longitudine

Pământul este o sferă - un cerc tridimensional. Din acest motiv, punctele sunt definite prin împărțirea acestuia în 360 de grade, la fel ca geometria cercurilor. Latitudinea măsoară numărul de grade de la nord la sud, iar longitudinea măsoară numărul de grade de la est la vest.

> 💁 Nimeni nu știe cu adevărat motivul original pentru care cercurile sunt împărțite în 360 de grade. [Pagina despre grad (unghi) pe Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) acoperă câteva dintre motivele posibile.

![Linii de latitudine de la 90° la Polul Nord, 45° la jumătatea distanței dintre Polul Nord și ecuator, 0° la ecuator, -45° la jumătatea distanței dintre ecuator și Polul Sud, și -90° la Polul Sud](../../../../../translated_images/ro/latitude-lines.11d8d91dfb2014a5.webp)

Latitudinea este măsurată folosind linii care înconjoară Pământul și sunt paralele cu ecuatorul, împărțind emisferele nordică și sudică în câte 90° fiecare. Ecuatorul este la 0°, Polul Nord este la 90°, cunoscut și ca 90° Nord, iar Polul Sud este la -90°, sau 90° Sud.

Longitudinea este măsurată ca numărul de grade măsurate spre est și vest. Originea longitudinii la 0° se numește *Meridianul Primar* și a fost definită în 1884 ca o linie de la Polul Nord la Polul Sud care trece prin [Observatorul Regal Britanic din Greenwich, Anglia](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Linii de longitudine care merg de la -180° la vest de Meridianul Primar, la 0° pe Meridianul Primar, la 180° est de Meridianul Primar](../../../../../translated_images/ro/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Un meridian este o linie imaginară dreaptă care merge de la Polul Nord la Polul Sud, formând un semicerc.

Pentru a măsura longitudinea unui punct, măsurați numărul de grade în jurul ecuatorului de la Meridianul Primar la un meridian care trece prin acel punct. Longitudinea variază de la -180°, sau 180° Vest, prin 0° la Meridianul Primar, până la 180°, sau 180° Est. 180° și -180° se referă la același punct, antimeridianul sau meridianul 180. Acesta este un meridian pe partea opusă a Pământului față de Meridianul Primar.

> 💁 Antimeridianul nu trebuie confundat cu Linia Internațională a Datei, care este aproximativ în aceeași poziție, dar nu este o linie dreaptă și variază pentru a se potrivi cu granițele geopolitice.

✅ Faceți câteva cercetări: Încercați să găsiți latitudinea și longitudinea locației dvs. actuale.

### Grade, minute și secunde vs grade zecimale

În mod tradițional, măsurătorile gradelor de latitudine și longitudine erau realizate folosind numerotarea sexagesimală, sau baza-60, un sistem de numerotare folosit de babilonienii antici care au realizat primele măsurători și înregistrări ale timpului și distanței. Probabil folosiți sexagesimalul în fiecare zi fără să vă dați seama - împărțind orele în 60 de minute și minutele în 60 de secunde.

Longitudinea și latitudinea sunt măsurate în grade, minute și secunde, unde un minut reprezintă 1/60 dintr-un grad, iar o secundă reprezintă 1/60 dintr-un minut.

De exemplu, la ecuator:

* 1° de latitudine este **111,3 kilometri**
* 1 minut de latitudine este 111,3/60 = **1,855 kilometri**
* 1 secundă de latitudine este 1,855/60 = **0,031 kilometri**

Simbolul pentru un minut este o apostrofă, iar pentru o secundă sunt două apostrofe. De exemplu, 2 grade, 17 minute și 43 de secunde ar fi scris ca 2°17'43". Părțile de secundă sunt date ca zecimale, de exemplu o jumătate de secundă este 0°0'0.5".

Calculatoarele nu funcționează în baza-60, așa că aceste coordonate sunt date ca grade zecimale atunci când se utilizează date GPS în majoritatea sistemelor informatice. De exemplu, 2°17'43" este 2.295277. Simbolul gradului este de obicei omis.

Coordonatele pentru un punct sunt întotdeauna date ca `latitudine, longitudine`, astfel încât exemplul anterior al campusului Microsoft la 47.6423109,-122.117198 are:

* O latitudine de 47.6423109 (47.6423109 grade nord de ecuator)
* O longitudine de -122.1390293 (122.1390293 grade vest de Meridianul Primar).

![Campusul Microsoft la 47.6423109,-122.117198](../../../../../translated_images/ro/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Sisteme de poziționare globală (GPS)

Sistemele GPS utilizează mai mulți sateliți care orbitează Pământul pentru a localiza poziția dvs. Probabil ați folosit sisteme GPS fără să știți - pentru a vă găsi locația pe o aplicație de hărți de pe telefon, cum ar fi Apple Maps sau Google Maps, pentru a vedea unde se află mașina dvs. într-o aplicație de ride-hailing, cum ar fi Uber sau Lyft, sau când utilizați navigația prin satelit (sat-nav) în mașină.

> 🎓 Sateliții din "navigația prin satelit" sunt sateliți GPS!

Sistemele GPS funcționează având un număr de sateliți care trimit un semnal cu poziția curentă a fiecărui satelit și un marcaj temporal precis. Aceste semnale sunt transmise prin unde radio și sunt detectate de o antenă din senzorul GPS. Un senzor GPS detectează aceste semnale și, folosind timpul curent, măsoară cât a durat ca semnalul să ajungă de la satelit la senzor. Deoarece viteza undelor radio este constantă, senzorul GPS poate utiliza marcajul temporal trimis pentru a calcula cât de departe este senzorul de satelit. Combinând datele de la cel puțin 3 sateliți cu pozițiile trimise, senzorul GPS poate determina locația sa pe Pământ.

> 💁 Senzorii GPS au nevoie de antene pentru a detecta undele radio. Antenele integrate în camioane și mașini cu GPS la bord sunt poziționate pentru a obține un semnal bun, de obicei pe parbriz sau pe acoperiș. Dacă utilizați un sistem GPS separat, cum ar fi un smartphone sau un dispozitiv IoT, trebuie să vă asigurați că antena integrată în sistemul GPS sau telefon are o vedere clară a cerului, cum ar fi montarea pe parbriz.

![Prin cunoașterea distanței de la senzor la mai mulți sateliți, locația poate fi calculată](../../../../../translated_images/ro/gps-satellites.04acf1148fe25fbf.webp)

Sateliții GPS orbitează Pământul, nefiind într-un punct fix deasupra senzorului, astfel încât datele despre locație includ altitudinea deasupra nivelului mării, precum și latitudinea și longitudinea.

GPS-ul avea anterior limitări de precizie impuse de armata SUA, limitând precizia la aproximativ 5 metri. Această limitare a fost eliminată în 2000, permițând o precizie de 30 de centimetri. Obținerea acestei precizii nu este întotdeauna posibilă din cauza interferențelor cu semnalele.

✅ Dacă aveți un smartphone, deschideți aplicația de hărți și vedeți cât de precisă este locația dvs. Este posibil să dureze puțin timp pentru ca telefonul dvs. să detecteze mai mulți sateliți pentru a obține o locație mai precisă.
💁 Sateliții conțin ceasuri atomice extrem de precise, dar acestea se abat cu 38 de microsecunde (0,0000038 secunde) pe zi comparativ cu ceasurile atomice de pe Pământ, din cauza încetinirii timpului pe măsură ce viteza crește, așa cum a fost prezis de teoriile relativității speciale și generale ale lui Einstein - sateliții se deplasează mai repede decât rotația Pământului. Această abatere a fost folosită pentru a demonstra predicțiile relativității speciale și generale și trebuie ajustată în proiectarea sistemelor GPS. Practic, timpul curge mai încet pe un satelit GPS.
Sistemele GPS au fost dezvoltate și implementate de mai multe țări și uniuni politice, inclusiv SUA, Rusia, Japonia, India, UE și China. Senzorii GPS moderni se pot conecta la majoritatea acestor sisteme pentru a obține localizări mai rapide și mai precise.

> 🎓 Grupurile de sateliți din fiecare implementare sunt denumite constelații.

## Citirea datelor de la senzorul GPS

Majoritatea senzorilor GPS trimit date GPS prin UART.

> ⚠️ UART a fost acoperit în [proiectul 2, lecția 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Revino la acea lecție dacă este necesar.

Poți utiliza un senzor GPS pe dispozitivul tău IoT pentru a obține date GPS.

### Sarcină - conectează un senzor GPS și citește datele GPS

Parcurge ghidul relevant pentru a citi datele GPS folosind dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Computer cu placă unică - Raspberry Pi](pi-gps-sensor.md)
* [Computer cu placă unică - Dispozitiv virtual](virtual-device-gps-sensor.md)

## Date GPS NMEA

Când ai rulat codul, probabil ai observat ceea ce pare a fi un text fără sens în output. Acestea sunt de fapt date GPS standard, iar fiecare detaliu are o semnificație.

Senzorii GPS transmit date folosind mesaje NMEA, conform standardului NMEA 0183. NMEA este un acronim pentru [National Marine Electronics Association](https://www.nmea.org), o organizație comercială din SUA care stabilește standarde pentru comunicarea între echipamentele electronice marine.

> 💁 Acest standard este proprietar și costă cel puțin 2.000 USD, dar suficiente informații despre el sunt disponibile în domeniul public, astfel încât majoritatea standardului a fost inversat și poate fi utilizat în cod open-source și alte aplicații non-comerciale.

Aceste mesaje sunt bazate pe text. Fiecare mesaj constă într-o *propoziție* care începe cu caracterul `$`, urmat de 2 caractere care indică sursa mesajului (de exemplu, GP pentru sistemul GPS al SUA, GN pentru GLONASS, sistemul GPS al Rusiei) și 3 caractere care indică tipul mesajului. Restul mesajului este format din câmpuri separate prin virgule, terminându-se cu un caracter de linie nouă.

Unele dintre tipurile de mesaje care pot fi primite sunt:

| Tip | Descriere |
| ---- | ----------- |
| GGA | Date de fixare GPS, inclusiv latitudinea, longitudinea și altitudinea senzorului GPS, împreună cu numărul de sateliți vizibili pentru a calcula această fixare. |
| ZDA | Data și ora curentă, inclusiv fusul orar local |
| GSV | Detalii despre sateliții vizibili - definiți ca sateliții de la care senzorul GPS poate detecta semnale |

> 💁 Datele GPS includ marcaje temporale, astfel încât dispozitivul tău IoT poate obține ora, dacă este necesar, de la un senzor GPS, în loc să se bazeze pe un server NTP sau pe un ceas intern în timp real.

Mesajul GGA include locația curentă folosind formatul `(dd)dmm.mmmm`, împreună cu un singur caracter pentru a indica direcția. `d` în format reprezintă gradele, `m` reprezintă minutele, iar secundele sunt exprimate ca zecimale ale minutelor. De exemplu, 2°17'43" ar fi 217.716666667 - 2 grade, 17.716666667 minute.

Caracterul de direcție poate fi `N` sau `S` pentru latitudine, indicând nord sau sud, și `E` sau `W` pentru longitudine, indicând est sau vest. De exemplu, o latitudine de 2°17'43" ar avea caracterul de direcție `N`, iar -2°17'43" ar avea caracterul de direcție `S`.

De exemplu - propoziția NMEA `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Partea de latitudine este `4738.538654,N`, care se convertește în 47.6423109 în grade zecimale. `4738.538654` este 47.6423109, iar direcția este `N` (nord), deci este o latitudine pozitivă.

* Partea de longitudine este `12208.341758,W`, care se convertește în -122.1390293 în grade zecimale. `12208.341758` este 122.1390293°, iar direcția este `W` (vest), deci este o longitudine negativă.

## Decodarea datelor de la senzorul GPS

Mai degrabă decât să folosești datele brute NMEA, este mai bine să le decodifici într-un format mai util. Există multiple biblioteci open-source pe care le poți utiliza pentru a extrage date utile din mesajele brute NMEA.

### Sarcină - decodifică datele de la senzorul GPS

Parcurge ghidul relevant pentru a decodifica datele de la senzorul GPS folosind dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Computer cu placă unică - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-gps-decode.md)

---

## 🚀 Provocare

Scrie propriul tău decodor NMEA! În loc să te bazezi pe biblioteci terțe pentru a decodifica propozițiile NMEA, poți scrie propriul decodor pentru a extrage latitudinea și longitudinea din propozițiile NMEA?

## Test după lecție

[Test după lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Recapitulare și studiu individual

* Citește mai multe despre coordonatele geospațiale pe [pagina sistemului de coordonate geografice de pe Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Documentează-te despre meridianele de referință pe alte corpuri cerești în afară de Pământ pe [pagina Meridianului de referință de pe Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Cercetează diferitele sisteme GPS ale diferitelor guverne și uniuni politice din lume, cum ar fi UE, Japonia, Rusia, India și SUA.

## Temă

[Investigarea altor date GPS](assignment.md)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.