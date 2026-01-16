<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-28T11:29:22+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "ro"
}
-->
# Preziceți creșterea plantelor cu IoT

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.jpg)

> Prezentare grafică de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introducere

Plantele au nevoie de anumite lucruri pentru a crește - apă, dioxid de carbon, nutrienți, lumină și căldură. În această lecție, vei învăța cum să calculezi ratele de creștere și maturitate ale plantelor prin măsurarea temperaturii aerului.

În această lecție vom acoperi:

* [Agricultura digitală](../../../../../2-farm/lessons/1-predict-plant-growth)
* [De ce este importantă temperatura în agricultură?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Măsurarea temperaturii ambientale](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Zilele gradelor de creștere (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Calcularea GDD folosind datele de la senzorul de temperatură](../../../../../2-farm/lessons/1-predict-plant-growth)

## Agricultura digitală

Agricultura digitală transformă modul în care cultivăm, utilizând instrumente pentru a colecta, stoca și analiza datele din agricultură. Ne aflăm într-o perioadă descrisă de Forumul Economic Mondial drept 'A Patra Revoluție Industrială', iar ascensiunea agriculturii digitale a fost denumită 'A Patra Revoluție Agricolă' sau 'Agricultura 4.0'.

> 🎓 Termenul Agricultură Digitală include și întregul 'lanț valoric agricol', adică întregul parcurs de la fermă la masă. Acesta include urmărirea calității produselor pe măsură ce sunt transportate și procesate, sistemele de depozitare și comerț electronic, chiar și aplicațiile pentru închirierea tractoarelor!

Aceste schimbări permit fermierilor să crească randamentele, să utilizeze mai puține îngrășăminte și pesticide și să folosească apa mai eficient. Deși utilizate în principal în țările mai bogate, senzorii și alte dispozitive devin treptat mai accesibile și în țările în curs de dezvoltare.

Unele tehnici permise de agricultura digitală sunt:

* Măsurarea temperaturii - măsurarea temperaturii permite fermierilor să prezică creșterea și maturitatea plantelor.
* Irigare automată - măsurarea umidității solului și pornirea sistemelor de irigare atunci când solul este prea uscat, în loc de udare programată. Udarea programată poate duce la sub-udarea culturilor în perioadele calde și uscate sau la supra-udare în timpul ploilor. Prin udarea doar atunci când solul are nevoie, fermierii pot optimiza utilizarea apei.
* Controlul dăunătorilor - fermierii pot utiliza camere pe roboți automatizați sau drone pentru a verifica prezența dăunătorilor, apoi pot aplica pesticide doar acolo unde este necesar, reducând cantitatea de pesticide utilizate și scurgerile de pesticide în sursele locale de apă.

✅ Fă niște cercetări. Ce alte tehnici sunt utilizate pentru a îmbunătăți randamentele agricole?

> 🎓 Termenul 'Agricultură de Precizie' este folosit pentru a defini observarea, măsurarea și răspunsul la culturi pe baza fiecărui câmp sau chiar a unor părți ale unui câmp. Acest lucru include măsurarea nivelurilor de apă, nutrienți și dăunători și răspunsul precis, cum ar fi udarea doar a unei părți mici a unui câmp.

## De ce este importantă temperatura în agricultură?

Când învățăm despre plante, majoritatea elevilor sunt învățați despre necesitatea apei, luminii, dioxidului de carbon și nutrienților. Plantele au nevoie și de căldură pentru a crește - acesta este motivul pentru care plantele înfloresc primăvara, pe măsură ce temperatura crește, de ce ghioceii sau narcisele pot răsări devreme datorită unei perioade scurte de căldură și de ce serele și solariile sunt atât de eficiente în creșterea plantelor.

> 🎓 Serele și solariile fac o treabă similară, dar cu o diferență importantă. Serele sunt încălzite artificial și permit fermierilor să controleze temperaturile mai precis, în timp ce solariile se bazează pe soare pentru căldură, iar controlul se face de obicei prin ferestre sau alte deschideri pentru a lăsa căldura să iasă.

Plantele au o temperatură minimă de bază, o temperatură optimă și o temperatură maximă, toate bazate pe temperaturile medii zilnice.

* Temperatura de bază - aceasta este temperatura medie zilnică minimă necesară pentru ca o plantă să crească.
* Temperatura optimă - aceasta este temperatura medie zilnică ideală pentru a obține cea mai mare creștere.
* Temperatura maximă - aceasta este temperatura maximă pe care o plantă o poate suporta. Peste această valoare, planta își va opri creșterea pentru a conserva apa și a supraviețui.

> 💁 Acestea sunt temperaturi medii, calculate pe baza temperaturilor de zi și de noapte. Plantele au nevoie, de asemenea, de temperaturi diferite ziua și noaptea pentru a fotosintetiza mai eficient și a economisi energie pe timpul nopții.

Fiecare specie de plantă are valori diferite pentru temperatura de bază, optimă și maximă. Acesta este motivul pentru care unele plante prosperă în țările calde, iar altele în țările reci.

✅ Fă niște cercetări. Pentru orice plante pe care le ai în grădină, școală sau parc local, vezi dacă poți găsi temperatura de bază.

![Un grafic care arată rata de creștere crescând pe măsură ce temperatura crește, apoi scăzând pe măsură ce temperatura devine prea mare](../../../../../translated_images/ro/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Graficul de mai sus arată un exemplu de grafic al ratei de creștere în funcție de temperatură. Până la temperatura de bază, nu există creștere. Rata de creștere crește până la temperatura optimă, apoi scade după atingerea acestui vârf. La temperatura maximă, creșterea se oprește.

Forma acestui grafic variază de la o specie de plantă la alta. Unele au scăderi mai abrupte peste temperatura optimă, altele au creșteri mai lente de la temperatura de bază la cea optimă.

> 💁 Pentru ca un fermier să obțină cea mai bună creștere, va trebui să cunoască cele trei valori ale temperaturii și să înțeleagă forma graficelor pentru plantele pe care le cultivă.

Dacă un fermier are control asupra temperaturii, de exemplu într-o seră comercială, atunci poate optimiza pentru plantele sale. O seră comercială care cultivă roșii, de exemplu, va avea temperatura setată la aproximativ 25°C în timpul zilei și 20°C noaptea pentru a obține cea mai rapidă creștere.

> 🍅 Combinând aceste temperaturi cu lumini artificiale, îngrășăminte și niveluri controlate de dioxid de carbon, cultivatorii comerciali pot cultiva și recolta pe tot parcursul anului.

## Măsurarea temperaturii ambientale

Senzorii de temperatură pot fi utilizați cu dispozitive IoT pentru a măsura temperatura ambientală.

### Sarcină - măsoară temperatura

Parcurge ghidul relevant pentru a monitoriza temperaturile folosind dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Computer cu o singură placă - Raspberry Pi](pi-temp.md)
* [Computer cu o singură placă - Dispozitiv virtual](virtual-device-temp.md)

## Zilele gradelor de creștere

Zilele gradelor de creștere (cunoscute și sub numele de unități de grade de creștere) sunt o modalitate de a măsura creșterea plantelor pe baza temperaturii. Presupunând că o plantă are suficientă apă, nutrienți și dioxid de carbon, temperatura determină rata de creștere.

Zilele gradelor de creștere, sau GDD, sunt calculate pe zi ca temperatura medie în Celsius pentru o zi peste temperatura de bază a plantei. Fiecare plantă are nevoie de un anumit număr de GDD pentru a crește, a înflori sau a produce și a maturiza o recoltă. Cu cât sunt mai multe GDD pe zi, cu atât planta va crește mai repede.

> 🇺🇸 Pentru americani, zilele gradelor de creștere pot fi calculate și folosind Fahrenheit. 5 GDD (în Celsius) sunt echivalente cu 9 GDD (în Fahrenheit).

Formula completă pentru GDD este puțin complicată, dar există o ecuație simplificată care este adesea utilizată ca o bună aproximare:

![GDD = T max + T min împărțit la 2, totul minus T bază](../../../../../translated_images/ro/gdd-calculation.79b3660f9c5757aa92dc2dd2cdde75344e2d2c1565c4b3151640f7887edc0275.png)

* **GDD** - acesta este numărul de zile ale gradelor de creștere
* **T max** - aceasta este temperatura maximă zilnică în grade Celsius
* **T min** - aceasta este temperatura minimă zilnică în grade Celsius
* **T bază** - aceasta este temperatura de bază a plantei în grade Celsius

> 💁 Există variații care iau în considerare T max peste 30°C sau T min sub T bază, dar le vom ignora pentru moment.

### Exemplu - Porumb 🌽

În funcție de varietate, porumbul are nevoie de între 800 și 2.700 GDD pentru a se maturiza, cu o temperatură de bază de 10°C.

În prima zi peste temperatura de bază, s-au măsurat următoarele temperaturi:

| Măsurătoare | Temp °C |
| :---------- | :-----: |
| Maximă      | 16      |
| Minimă      | 12      |

Introducând aceste numere în calculul nostru:

* T max = 16
* T min = 12
* T bază = 10

Aceasta dă un calcul de:

![GDD = 16 + 12 împărțit la 2, totul minus 10, rezultând un răspuns de 4](../../../../../translated_images/ro/gdd-calculation-corn.64a58b7a7afcd0dfd46ff733996d939f17f4f3feac9f0d1c632be3523e51ebd9.png)

Porumbul a primit 4 GDD în acea zi. Presupunând o varietate de porumb care necesită 800 GDD pentru a se maturiza, va avea nevoie de încă 796 GDD pentru a ajunge la maturitate.

✅ Fă niște cercetări. Pentru orice plante pe care le ai în grădină, școală sau parc local, vezi dacă poți găsi numărul de GDD necesar pentru a ajunge la maturitate sau pentru a produce recolte.

## Calcularea GDD folosind datele de la senzorul de temperatură

Plantele nu cresc pe date fixe - de exemplu, nu poți planta o sămânță și să știi că planta va da fructe exact 100 de zile mai târziu. În schimb, ca fermier, poți avea o idee aproximativă despre cât timp durează ca o plantă să crească, apoi vei verifica zilnic pentru a vedea când culturile sunt gata.

Acest lucru are un impact mare asupra muncii pe o fermă mare și riscă ca fermierul să rateze culturile care sunt gata neașteptat de devreme. Prin măsurarea temperaturilor, fermierul poate calcula GDD pe care o plantă le-a primit, permițându-i să verifice doar aproape de maturitatea așteptată.

Prin colectarea datelor despre temperatură folosind un dispozitiv IoT, un fermier poate fi notificat automat când plantele sunt aproape de maturitate. O arhitectură tipică pentru acest lucru este ca dispozitivele IoT să măsoare temperatura, apoi să publice aceste date de telemetrie pe Internet folosind ceva precum MQTT. Codul serverului ascultă aceste date și le salvează undeva, cum ar fi într-o bază de date. Acest lucru înseamnă că datele pot fi apoi analizate mai târziu, cum ar fi o sarcină nocturnă pentru a calcula GDD pentru ziua respectivă, a totaliza GDD pentru fiecare cultură până acum și a alerta dacă o plantă este aproape de maturitate.

![Datele de telemetrie sunt trimise către un server și apoi salvate într-o bază de date](../../../../../translated_images/ro/save-telemetry-database.ddc9c6bea0c5ba39.webp)

Codul serverului poate, de asemenea, să completeze datele adăugând informații suplimentare. De exemplu, dispozitivul IoT poate publica un identificator pentru a indica ce dispozitiv este, iar codul serverului poate utiliza acest lucru pentru a găsi locația dispozitivului și ce culturi monitorizează. De asemenea, poate adăuga date de bază, cum ar fi ora curentă, deoarece unele dispozitive IoT nu au hardware-ul necesar pentru a ține evidența unei ore exacte sau necesită cod suplimentar pentru a citi ora curentă de pe Internet.

✅ De ce crezi că diferite câmpuri ar putea avea temperaturi diferite?

### Sarcină - publică informații despre temperatură

Parcurge ghidul relevant pentru a publica date despre temperatură prin MQTT folosind dispozitivul tău IoT, astfel încât acestea să poată fi analizate mai târziu:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Computer cu o singură placă - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-temp-publish.md)

### Sarcină - capturează și stochează informațiile despre temperatură

Odată ce dispozitivul IoT publică telemetrie, codul serverului poate fi scris pentru a se abona la aceste date și a le stoca. În loc să le salveze într-o bază de date, codul serverului le va salva într-un fișier CSV (Comma Separated Values). Fișierele CSV stochează datele ca rânduri de valori sub formă de text, cu fiecare valoare separată printr-o virgulă și fiecare înregistrare pe o linie nouă. Sunt o modalitate convenabilă, ușor de citit de oameni și bine susținută pentru a salva datele ca fișier.

Fișierul CSV va avea două coloane - *date* și *temperature*. Coloana *date* este setată ca data și ora curentă la care mesajul a fost primit de server, iar *temperature* provine din mesajul de telemetrie.

1. Repetă pașii din lecția 4 pentru a crea codul serverului care să se aboneze la telemetrie. Nu este nevoie să adaugi cod pentru a publica comenzi.

    Pașii pentru aceasta sunt:

    * Configurează și activează un mediu virtual Python

    * Instalează pachetul pip paho-mqtt

    * Scrie codul pentru a asculta mesajele MQTT publicate pe subiectul de telemetrie

      > ⚠️ Poți consulta [instrucțiunile din lecția 4 pentru crearea unei aplicații Python pentru a primi telemetrie, dacă este necesar](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Denumește folderul pentru acest proiect `temperature-sensor-server`.

1. Asigură-te că `client_name` reflectă acest proiect:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Adaugă următoarele importuri în partea de sus a fișierului, sub importurile existente:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Acest lucru importă o bibliotecă pentru citirea fișierelor, o bibliotecă pentru a interacționa cu fișierele CSV și o bibliotecă pentru a lucra cu datele și orele.

1. Adaugă următorul cod înainte de funcția `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Acest cod declară câteva constante pentru numele fișierului în care să scrie și numele antetelor coloanelor pentru fișierul CSV. Primul rând al unui fișier CSV conține, în mod tradițional, antetele coloanelor separate prin virgule.

    Codul verifică apoi dacă fișierul CSV există deja. Dacă nu există, acesta este creat cu antetele coloanelor pe primul rând.

1. Adaugă următorul cod la sfârșitul funcției `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Acest cod deschide fișierul CSV, apoi adaugă un rând nou la final. Rândul conține data și ora curente, formatate într-un mod ușor de citit, urmate de temperatura primită de la dispozitivul IoT. Datele sunt stocate în [formatul ISO 8601](https://wikipedia.org/wiki/ISO_8601) cu fusul orar, dar fără microsecunde.

1. Rulează acest cod la fel ca înainte, asigurându-te că dispozitivul tău IoT trimite date. Un fișier CSV numit `temperature.csv` va fi creat în același folder. Dacă îl deschizi, vei vedea date/ore și măsurători de temperatură:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Rulează acest cod pentru o perioadă mai lungă pentru a captura date. Ideal ar fi să-l rulezi o zi întreagă pentru a aduna suficiente date pentru calculul GDD.

    
> 💁 Dacă folosești un dispozitiv IoT virtual, selectează caseta de bifare pentru valori aleatorii și setează un interval pentru a evita obținerea aceleiași temperaturi de fiecare dată când este returnată valoarea temperaturii.
    ![Selectează caseta de bifare pentru valori aleatorii și setează un interval](../../../../../translated_images/ro/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Dacă vrei să rulezi acest cod o zi întreagă, trebuie să te asiguri că computerul pe care rulează codul serverului nu va intra în modul de repaus, fie prin schimbarea setărilor de alimentare, fie rulând ceva precum [acest script Python pentru menținerea activității sistemului](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Poți găsi acest cod în folderul [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Sarcină - calculează GDD folosind datele stocate

După ce serverul a capturat datele de temperatură, GDD pentru o plantă poate fi calculat.

Pașii pentru a face acest lucru manual sunt:

1. Găsește temperatura de bază pentru plantă. De exemplu, pentru căpșuni temperatura de bază este de 10°C.

1. Din fișierul `temperature.csv`, găsește cele mai mari și cele mai mici temperaturi ale zilei.

1. Folosește formula de calcul GDD prezentată anterior pentru a calcula GDD.

De exemplu, dacă temperatura maximă a zilei este 25°C, iar cea minimă este 12°C:

![GDD = 25 + 12 împărțit la 2, apoi scade 10 din rezultat, obținând 8.5](../../../../../translated_images/ro/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Prin urmare, căpșunile au primit **8.5** GDD. Căpșunile au nevoie de aproximativ 250 GDD pentru a produce fructe, deci mai este ceva timp până atunci.

---

## 🚀 Provocare

Plantele au nevoie de mai mult decât căldură pentru a crește. De ce alte lucruri mai au nevoie?

Pentru acestea, găsește dacă există senzori care le pot măsura. Ce zici de actuatoare pentru a controla aceste niveluri? Cum ai pune împreună unul sau mai multe dispozitive IoT pentru a optimiza creșterea plantelor?

## Chestionar post-lectură

[Chestionar post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Recapitulare și studiu individual

* Citește mai multe despre agricultura digitală pe [pagina Wikipedia despre Agricultura Digitală](https://wikipedia.org/wiki/Digital_agriculture). De asemenea, citește mai multe despre agricultura de precizie pe [pagina Wikipedia despre Agricultura de Precizie](https://wikipedia.org/wiki/Precision_agriculture).
* Calculul complet al gradelor de creștere este mai complicat decât cel simplificat prezentat aici. Citește mai multe despre ecuația mai complexă și despre cum să gestionezi temperaturile sub pragul de bază pe [pagina Wikipedia despre Gradele de Creștere](https://wikipedia.org/wiki/Growing_degree-day).
* Alimentele ar putea deveni rare în viitor dacă continuăm să folosim aceleași metode de agricultură. Află mai multe despre tehnicile de agricultură hi-tech în acest [video despre Fermele Hi-Tech ale Viitorului pe YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Temă

[Vizualizează datele GDD folosind un Jupyter Notebook](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.