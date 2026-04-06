# Declanșarea detectării calității fructelor de la un senzor

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-18.92c32ed1d354caa5.webp)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introducere

O aplicație IoT nu este doar un singur dispozitiv care captează date și le trimite în cloud; de cele mai multe ori, implică mai multe dispozitive care lucrează împreună pentru a capta date din lumea fizică folosind senzori, pentru a lua decizii pe baza acestor date și pentru a interacționa cu lumea fizică prin actuatori sau vizualizări.

În această lecție, veți învăța mai multe despre arhitectura aplicațiilor IoT complexe, despre integrarea mai multor senzori și servicii cloud pentru analizarea și stocarea datelor, precum și despre afișarea unui răspuns prin intermediul unui actuator. Veți învăța cum să proiectați un prototip al unui sistem de control al calității fructelor, inclusiv utilizarea senzorilor de proximitate pentru a declanșa aplicația IoT și cum ar arăta arhitectura acestui prototip.

În această lecție vom acoperi:

* [Arhitectura aplicațiilor IoT complexe](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Proiectarea unui sistem de control al calității fructelor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Declanșarea verificării calității fructelor de la un senzor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Datele utilizate pentru un detector de calitate a fructelor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Utilizarea dispozitivelor de dezvoltare pentru a simula mai multe dispozitive IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Trecerea la producție](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Aceasta este ultima lecție din acest proiect, așa că, după ce finalizați lecția și sarcina, nu uitați să curățați serviciile cloud. Veți avea nevoie de aceste servicii pentru a finaliza sarcina, așa că asigurați-vă că o finalizați mai întâi.
>
> Consultați [ghidul pentru curățarea proiectului](../../../clean-up.md) dacă este necesar pentru instrucțiuni despre cum să faceți acest lucru.

## Arhitectura aplicațiilor IoT complexe

Aplicațiile IoT sunt compuse din multe componente. Acestea includ o varietate de dispozitive și servicii de internet.

Aplicațiile IoT pot fi descrise ca *dispozitive* care trimit date ce generează *informații*. Aceste *informații* generează *acțiuni* pentru a îmbunătăți o afacere sau un proces. De exemplu, un motor (dispozitivul) trimite date despre temperatură. Aceste date sunt utilizate pentru a evalua dacă motorul funcționează conform așteptărilor (informația). Informația este folosită pentru a prioritiza proactiv programul de întreținere al motorului (acțiunea).

* Dispozitivele diferite colectează diferite tipuri de date.
* Serviciile IoT oferă informații pe baza acestor date, uneori completându-le cu date din surse suplimentare.
* Aceste informații conduc la acțiuni, inclusiv controlul actuatoarelor din dispozitive sau vizualizarea datelor.

### Arhitectura de referință IoT

![O arhitectură de referință IoT](../../../../../translated_images/ro/iot-reference-architecture.2278b98b55c6d4e8.webp)

Diagrama de mai sus prezintă o arhitectură de referință IoT.

> 🎓 O *arhitectură de referință* este un exemplu de arhitectură pe care o puteți utiliza ca referință atunci când proiectați sisteme noi. În acest caz, dacă ați construi un nou sistem IoT, puteți urma arhitectura de referință, înlocuind dispozitivele și serviciile proprii acolo unde este cazul.

* **Dispozitivele** sunt cele care colectează date de la senzori, poate interacționând cu servicii edge pentru a interpreta aceste date, cum ar fi clasificatoare de imagini pentru a interpreta datele vizuale. Datele de la dispozitive sunt trimise către un serviciu IoT.
* **Informațiile** provin din aplicații serverless sau din analize efectuate pe datele stocate.
* **Acțiunile** pot fi comenzi trimise către dispozitive sau vizualizarea datelor pentru a permite oamenilor să ia decizii.

![O arhitectură de referință IoT pe Azure](../../../../../translated_images/ro/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

Diagrama de mai sus prezintă câteva dintre componentele și serviciile acoperite până acum în aceste lecții și modul în care acestea se leagă într-o arhitectură de referință IoT.

* **Dispozitive** - ați scris cod pentru dispozitive pentru a capta date de la senzori și pentru a analiza imagini folosind Custom Vision, rulând atât în cloud, cât și pe un dispozitiv edge. Aceste date au fost trimise către IoT Hub.
* **Informații** - ați utilizat Azure Functions pentru a răspunde la mesajele trimise către un IoT Hub și ați stocat date pentru analize ulterioare în Azure Storage.
* **Acțiuni** - ați controlat actuatoare pe baza deciziilor luate în cloud și a comenzilor trimise către dispozitive și ați vizualizat datele folosind Azure Maps.

✅ Gândiți-vă la alte dispozitive IoT pe care le-ați utilizat, cum ar fi electrocasnicele inteligente. Care sunt dispozitivele, informațiile și acțiunile implicate în acel dispozitiv și software-ul său?

Acest model poate fi scalat atât de mare sau mic cât aveți nevoie, adăugând mai multe dispozitive și servicii.

### Date și securitate

Pe măsură ce definiți arhitectura sistemului dvs., trebuie să luați în considerare constant datele și securitatea.

* Ce date trimite și primește dispozitivul dvs.?
* Cum ar trebui securizate și protejate aceste date?
* Cum ar trebui controlat accesul la dispozitiv și la serviciul cloud?

✅ Gândiți-vă la securitatea datelor dispozitivelor IoT pe care le dețineți. Cât de multe dintre aceste date sunt personale și ar trebui păstrate private, atât în tranzit, cât și atunci când sunt stocate? Ce date nu ar trebui stocate?

## Proiectarea unui sistem de control al calității fructelor

Să luăm acum această idee de dispozitive, informații și acțiuni și să o aplicăm detectorului de calitate a fructelor pentru a proiecta o aplicație completă.

Imaginați-vă că vi s-a dat sarcina de a construi un detector de calitate a fructelor care să fie utilizat într-o fabrică de procesare. Fructele circulă pe o bandă transportoare, unde în prezent angajații verifică manual fructele și îndepărtează fructele necoapte pe măsură ce ajung. Pentru a reduce costurile, proprietarul fabricii dorește un sistem automatizat.

✅ Unul dintre trendurile asociate cu creșterea IoT (și a tehnologiei în general) este că locurile de muncă manuale sunt înlocuite de mașini. Faceți câteva cercetări: Câte locuri de muncă se estimează că vor fi pierdute din cauza IoT? Câte locuri de muncă noi vor fi create pentru construirea dispozitivelor IoT?

Trebuie să construiți un sistem în care fructele sunt detectate pe măsură ce ajung pe banda transportoare, sunt apoi fotografiate și verificate folosind un model AI care rulează pe un dispozitiv edge. Rezultatele sunt apoi trimise în cloud pentru a fi stocate, iar dacă fructele sunt necoapte, se trimite o notificare pentru ca acestea să fie îndepărtate.

|   |   |
| - | - |
| **Dispozitive** | Detector pentru fructele care ajung pe banda transportoare<br>Camera pentru fotografierea și clasificarea fructelor<br>Dispozitiv edge care rulează clasificatorul<br>Dispozitiv pentru notificarea fructelor necoapte |
| **Informații** | Decizia de a verifica maturitatea fructelor<br>Stocarea rezultatelor clasificării maturității<br>Determinarea necesității de a alerta despre fructele necoapte |
| **Acțiuni** | Trimiterea unei comenzi către un dispozitiv pentru a fotografia fructele și a le verifica cu un clasificator de imagini<br>Trimiterea unei comenzi către un dispozitiv pentru a alerta că fructele sunt necoapte |

### Prototiparea aplicației

![O arhitectură de referință IoT pentru verificarea calității fructelor](../../../../../translated_images/ro/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

Diagrama de mai sus prezintă o arhitectură de referință pentru această aplicație prototip.

* Un dispozitiv IoT cu un senzor de proximitate detectează sosirea fructelor. Acesta trimite un mesaj în cloud pentru a semnala că fructele au fost detectate.
* O aplicație serverless din cloud trimite o comandă către un alt dispozitiv pentru a face o fotografie și a clasifica imaginea.
* Un dispozitiv IoT cu o cameră face o fotografie și o trimite către un clasificator de imagini care rulează pe un dispozitiv edge. Rezultatele sunt apoi trimise în cloud.
* O aplicație serverless din cloud stochează aceste informații pentru a fi analizate ulterior, pentru a vedea ce procent din fructe sunt necoapte. Dacă fructele sunt necoapte, trimite o comandă către un alt dispozitiv IoT pentru a alerta muncitorii din fabrică printr-un LED.

> 💁 Întreaga aplicație IoT ar putea fi implementată ca un singur dispozitiv, cu toată logica pentru a porni clasificarea imaginilor și a controla LED-ul integrată. Ar putea folosi un IoT Hub doar pentru a urmări numărul de fructe necoapte detectate și pentru a configura dispozitivul. În această lecție, este extinsă pentru a demonstra conceptele pentru aplicațiile IoT la scară largă.

Pentru prototip, veți implementa toate acestea pe un singur dispozitiv. Dacă utilizați un microcontroler, atunci veți folosi un dispozitiv edge separat pentru a rula clasificatorul de imagini.

## Declanșarea verificării calității fructelor de la un senzor

Dispozitivul IoT are nevoie de un fel de declanșator pentru a indica momentul în care fructele sunt gata să fie clasificate. Un astfel de declanșator ar putea fi măsurarea momentului în care fructele sunt în poziția corectă pe banda transportoare, prin măsurarea distanței față de un senzor.

![Senzorii de proximitate trimit fascicule laser către obiecte, cum ar fi bananele, și măsoară timpul până când fasciculul este reflectat înapoi](../../../../../translated_images/ro/proximity-sensor.f5cd752c77fb62fe.webp)

Senzorii de proximitate pot fi utilizați pentru a măsura distanța dintre senzor și un obiect. De obicei, aceștia transmit un fascicul de radiație electromagnetică, cum ar fi un fascicul laser sau lumină infraroșie, apoi detectează radiația reflectată de un obiect. Timpul dintre trimiterea fasciculului laser și semnalul reflectat poate fi utilizat pentru a calcula distanța până la senzor.

> 💁 Probabil ați folosit senzori de proximitate fără să știți. Majoritatea smartphone-urilor opresc ecranul atunci când le țineți la ureche pentru a preveni încheierea accidentală a unui apel cu lobul urechii, iar acest lucru funcționează folosind un senzor de proximitate, care detectează un obiect apropiat de ecran în timpul unui apel și dezactivează funcțiile tactile până când telefonul este la o anumită distanță.

### Sarcină - declanșarea detectării calității fructelor folosind un senzor de distanță

Parcurgeți ghidul relevant pentru a utiliza un senzor de proximitate pentru a detecta un obiect folosind dispozitivul dvs. IoT:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtual device](virtual-device-proximity.md)

## Datele utilizate pentru un detector de calitate a fructelor

Prototipul detectorului de fructe are mai multe componente care comunică între ele.

![Componentele care comunică între ele](../../../../../translated_images/ro/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Un senzor de proximitate care măsoară distanța până la un fruct și trimite aceste date către IoT Hub
* Comanda pentru controlul camerei venind de la IoT Hub către dispozitivul cu camera
* Rezultatele clasificării imaginilor trimise către IoT Hub
* Comanda pentru controlul unui LED pentru a alerta când fructele sunt necoapte, trimisă de la IoT Hub către dispozitivul cu LED-ul

Este bine să definiți structura acestor mesaje de la început, înainte de a construi aplicația.

> 💁 Aproape orice dezvoltator experimentat a petrecut la un moment dat ore, zile sau chiar săptămâni urmărind erori cauzate de diferențele dintre datele trimise și cele așteptate.

De exemplu - dacă trimiteți informații despre temperatură, cum ați defini JSON-ul? Ați putea avea un câmp numit `temperature`, sau ați putea folosi abrevierea comună `temp`.

```json
{
    "temperature": 20.7
}
```

comparativ cu:

```json
{
    "temp": 20.7
}
```

De asemenea, trebuie să luați în considerare unitățile - temperatura este în °C sau °F? Dacă măsurați temperatura folosind un dispozitiv pentru consumatori și aceștia schimbă unitățile afișate, trebuie să vă asigurați că unitățile trimise în cloud rămân consistente.

✅ Faceți câteva cercetări: Cum au cauzat problemele legate de unități prăbușirea Mars Climate Orbiter, în valoare de 125 milioane de dolari?

Gândiți-vă la datele trimise pentru detectorul de calitate a fructelor. Cum ați defini fiecare mesaj? Unde ați analiza datele și ați lua decizii despre ce date să trimiteți?

De exemplu - declanșarea clasificării imaginilor folosind senzorul de proximitate. Dispozitivul IoT măsoară distanța, dar unde se ia decizia? Dispozitivul decide că fructele sunt suficient de aproape și trimite un mesaj pentru a spune IoT Hub să declanșeze clasificarea? Sau trimite măsurători de proximitate și lasă IoT Hub să decidă?

Răspunsul la astfel de întrebări este - depinde. Fiecare caz de utilizare este diferit, motiv pentru care, ca dezvoltator IoT, trebuie să înțelegeți sistemul pe care îl construiți, cum este utilizat și datele detectate.

* Dacă decizia este luată de IoT Hub, trebuie să trimiteți mai multe măsurători de distanță.
* Dacă trimiteți prea multe mesaje, creșteți costul IoT Hub-ului și cantitatea de lățime de bandă necesară dispozitivelor IoT (mai ales într-o fabrică cu milioane de dispozitive). De asemenea, poate încetini dispozitivul.
* Dacă luați decizia pe dispozitiv, va trebui să oferiți o modalitate de a configura dispozitivul pentru a ajusta fin mașina.

## Utilizarea dispozitivelor de dezvoltare pentru a simula mai multe dispozitive IoT

Pentru a construi prototipul, va trebui ca kitul dvs. de dezvoltare IoT să acționeze ca mai multe dispozitive, trimițând telemetrie și răspunzând la comenzi.

### Simularea mai multor dispozitive IoT pe un Raspberry Pi sau hardware IoT virtual

Când utilizați un computer cu o singură placă, cum ar fi un Raspberry Pi, puteți rula mai multe aplicații simultan. Aceasta înseamnă că puteți simula mai multe dispozitive IoT creând mai multe aplicații, câte una pentru fiecare 'dispozitiv IoT'. De exemplu, puteți implementa fiecare dispozitiv ca un fișier Python separat și să le rulați în sesiuni diferite de terminal.
> 💁 Fii conștient că unele componente hardware nu vor funcționa atunci când sunt accesate de mai multe aplicații care rulează simultan.
### Simularea mai multor dispozitive pe un microcontroller

Microcontrolerele sunt mai complicate de utilizat pentru a simula mai multe dispozitive. Spre deosebire de computerele cu o singură placă, nu poți rula mai multe aplicații simultan; trebuie să incluzi toată logica pentru toate dispozitivele IoT într-o singură aplicație.

Câteva sugestii pentru a face acest proces mai ușor sunt:

* Creează una sau mai multe clase pentru fiecare dispozitiv IoT - de exemplu, clase numite `DistanceSensor`, `ClassifierCamera`, `LEDController`. Fiecare poate avea propriile metode `setup` și `loop`, apelate de funcțiile principale `setup` și `loop`.
* Gestionează comenzile într-un singur loc și direcționează-le către clasa de dispozitiv relevantă, după cum este necesar.
* În funcția principală `loop`, va trebui să iei în considerare sincronizarea pentru fiecare dispozitiv diferit. De exemplu, dacă ai o clasă de dispozitiv care trebuie să proceseze la fiecare 10 secunde și alta care trebuie să proceseze la fiecare 1 secundă, atunci în funcția principală `loop` folosește o întârziere de 1 secundă. Fiecare apel `loop` declanșează codul relevant pentru dispozitivul care trebuie să proceseze la fiecare secundă și folosește un contor pentru a număra fiecare buclă, procesând celălalt dispozitiv când contorul ajunge la 10 (resetând contorul ulterior).

## Trecerea la producție

Prototipul va constitui baza unui sistem final de producție. Unele dintre diferențele care apar atunci când treci la producție ar fi:

* Componente robuste - utilizarea hardware-ului proiectat să reziste la zgomot, căldură, vibrații și stres într-un mediu industrial.
* Utilizarea comunicațiilor interne - unele dintre componente ar comunica direct, evitând trecerea prin cloud, trimițând date în cloud doar pentru stocare. Modul în care se face acest lucru depinde de configurația fabricii, fie prin comunicații directe, fie prin rularea unei părți a serviciului IoT la margine, utilizând un dispozitiv gateway.
* Opțiuni de configurare - fiecare fabrică și caz de utilizare este diferit, așa că hardware-ul ar trebui să fie configurabil. De exemplu, senzorul de proximitate ar putea avea nevoie să detecteze fructe diferite la distanțe diferite. În loc să codifici distanța pentru declanșarea clasificării, ai dori ca aceasta să fie configurabilă prin cloud, de exemplu utilizând un device twin.
* Îndepărtarea automată a fructelor - în loc de un LED care să alerteze că fructul nu este copt, dispozitive automate ar elimina fructul.

✅ Fă niște cercetări: În ce alte moduri ar diferi dispozitivele de producție de kiturile pentru dezvoltatori?

---

## 🚀 Provocare

În această lecție ai învățat câteva dintre conceptele de bază despre cum să arhitectezi un sistem IoT. Gândește-te la proiectele anterioare. Cum s-ar încadra acestea în arhitectura de referință prezentată mai sus?

Alege unul dintre proiectele de până acum și gândește-te la designul unei soluții mai complexe care să reunească mai multe capabilități dincolo de ceea ce a fost acoperit în proiecte. Desenează arhitectura și gândește-te la toate dispozitivele și serviciile de care ai avea nevoie.

De exemplu - un dispozitiv de urmărire a vehiculelor care combină GPS-ul cu senzori pentru a monitoriza lucruri precum temperaturile dintr-un camion frigorific, timpii de pornire și oprire a motorului și identitatea șoferului. Care sunt dispozitivele implicate, serviciile implicate, datele transmise și considerațiile legate de securitate și confidențialitate?

## Chestionar post-lectură

[Chestionar post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Recapitulare și studiu individual

* Citește mai multe despre arhitectura IoT în [documentația despre arhitectura de referință Azure IoT pe Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Citește mai multe despre device twins în [documentația despre înțelegerea și utilizarea device twins în IoT Hub pe Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Citește despre OPC-UA, un protocol de comunicare între mașini utilizat în automatizarea industrială, pe [pagina OPC-UA de pe Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Temă

[Construiește un detector de calitate a fructelor](assignment.md)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.