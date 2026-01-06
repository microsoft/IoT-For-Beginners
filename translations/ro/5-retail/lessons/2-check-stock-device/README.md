<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-28T10:47:43+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "ro"
}
-->
# Verificarea stocului de pe un dispozitiv IoT

![O prezentare grafică a lecției](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.ro.jpg)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introducere

În lecția anterioară ai învățat despre diferitele utilizări ale detectării obiectelor în retail. De asemenea, ai învățat cum să antrenezi un detector de obiecte pentru a identifica stocul. În această lecție vei învăța cum să folosești detectorul de obiecte de pe dispozitivul tău IoT pentru a număra stocul.

În această lecție vom acoperi:

* [Numărarea stocului](../../../../../5-retail/lessons/2-check-stock-device)
* [Apelarea detectorului de obiecte de pe dispozitivul IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Casete delimitatoare](../../../../../5-retail/lessons/2-check-stock-device)
* [Reantrenarea modelului](../../../../../5-retail/lessons/2-check-stock-device)
* [Numărarea stocului](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Aceasta este ultima lecție din acest proiect, așa că după ce finalizezi lecția și sarcina, nu uita să cureți serviciile cloud. Vei avea nevoie de aceste servicii pentru a finaliza sarcina, așa că asigură-te că o finalizezi mai întâi.
>
> Consultă [ghidul de curățare a proiectului](../../../clean-up.md) dacă este necesar pentru instrucțiuni despre cum să faci acest lucru.

## Numărarea stocului

Detectoarele de obiecte pot fi utilizate pentru verificarea stocului, fie pentru numărarea acestuia, fie pentru a se asigura că stocul este acolo unde ar trebui să fie. Dispozitivele IoT cu camere pot fi amplasate în tot magazinul pentru a monitoriza stocul, începând cu zonele de interes unde este important să se reumple rafturile, cum ar fi zonele în care sunt stocate articole de valoare mare în cantități mici.

De exemplu, dacă o cameră este îndreptată spre un set de rafturi care pot ține 8 conserve de pastă de tomate, iar un detector de obiecte detectează doar 7 conserve, atunci una lipsește și trebuie reumplută.

![7 conserve de pastă de tomate pe un raft, 4 pe rândul de sus, 3 pe rândul de jos](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.ro.png)

În imaginea de mai sus, un detector de obiecte a detectat 7 conserve de pastă de tomate pe un raft care poate ține 8 conserve. Dispozitivul IoT nu doar că poate trimite o notificare despre necesitatea reumplerii, dar poate chiar să ofere o indicație despre locația articolului lipsă, informație importantă dacă folosești roboți pentru a reumple rafturile.

> 💁 În funcție de magazin și de popularitatea articolului, probabil că reumplerea nu ar avea loc dacă lipsește doar o conservă. Ar trebui să construiești un algoritm care determină când să reumpli rafturile pe baza produselor, clienților și altor criterii.

✅ În ce alte scenarii ai putea combina detectarea obiectelor și roboții?

Uneori, stocul greșit poate ajunge pe rafturi. Acest lucru poate fi o eroare umană la reumplere sau clienți care se răzgândesc în privința unei achiziții și pun un articol în primul loc disponibil. Când este vorba de un articol neperisabil, cum ar fi conservele, acest lucru este doar o neplăcere. Dacă este vorba de un articol perisabil, cum ar fi produsele congelate sau refrigerate, acest lucru poate însemna că produsul nu mai poate fi vândut, deoarece ar putea fi imposibil de determinat cât timp a fost în afara congelatorului.

Detectarea obiectelor poate fi utilizată pentru a detecta articole neașteptate, alertând din nou un om sau un robot să returneze articolul imediat ce este detectat.

![O conservă de porumb pentru bebeluși pe raftul de pastă de tomate](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.ro.png)

În imaginea de mai sus, o conservă de porumb pentru bebeluși a fost pusă pe raftul de pastă de tomate. Detectorul de obiecte a detectat acest lucru, permițând dispozitivului IoT să notifice un om sau un robot să returneze conserva la locația corectă.

## Apelarea detectorului de obiecte de pe dispozitivul IoT

Detectorul de obiecte pe care l-ai antrenat în lecția anterioară poate fi apelat de pe dispozitivul tău IoT.

### Sarcină - publicarea unei iterații a detectorului de obiecte

Iterațiile sunt publicate din portalul Custom Vision.

1. Accesează portalul Custom Vision la [CustomVision.ai](https://customvision.ai) și autentifică-te dacă nu l-ai deschis deja. Apoi deschide proiectul `stock-detector`.

1. Selectează fila **Performance** din opțiunile de sus.

1. Selectează cea mai recentă iterație din lista *Iterations* din lateral.

1. Apasă butonul **Publish** pentru iterație.

    ![Butonul de publicare](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.ro.png)

1. În dialogul *Publish Model*, setează *Prediction resource* la resursa `stock-detector-prediction` pe care ai creat-o în lecția anterioară. Lasă numele ca `Iteration2` și apasă butonul **Publish**.

1. După publicare, apasă butonul **Prediction URL**. Acesta va afișa detalii despre API-ul de predicție, iar tu vei avea nevoie de acestea pentru a apela modelul de pe dispozitivul tău IoT. Secțiunea de jos este etichetată *If you have an image file*, și acestea sunt detaliile de care ai nevoie. Ia o copie a URL-ului afișat, care va arăta ceva de genul:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Unde `<location>` va fi locația pe care ai utilizat-o când ai creat resursa Custom Vision, iar `<id>` va fi un ID lung format din litere și cifre.

    De asemenea, ia o copie a valorii *Prediction-Key*. Aceasta este o cheie securizată pe care trebuie să o transmiți când apelezi modelul. Doar aplicațiile care transmit această cheie au permisiunea de a utiliza modelul, orice alte aplicații sunt respinse.

    ![Dialogul API de predicție care arată URL-ul și cheia](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.ro.png)

✅ Când o nouă iterație este publicată, aceasta va avea un nume diferit. Cum crezi că ai putea schimba iterația pe care o folosește un dispozitiv IoT?

### Sarcină - apelarea detectorului de obiecte de pe dispozitivul IoT

Urmează ghidul relevant de mai jos pentru a utiliza detectorul de obiecte de pe dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Computer cu placă unică - Raspberry Pi/dispozitiv virtual](single-board-computer-object-detector.md)

## Casete delimitatoare

Când utilizezi detectorul de obiecte, nu primești doar obiectele detectate cu etichetele și probabilitățile lor, ci primești și casetele delimitatoare ale obiectelor. Acestea definesc unde detectorul de obiecte a detectat obiectul cu probabilitatea dată.

> 💁 O casetă delimitatoare este o casetă care definește zona ce conține obiectul detectat, o casetă care definește limita pentru obiect.

Rezultatele unei predicții în fila **Predictions** din Custom Vision au casetele delimitatoare desenate pe imaginea care a fost trimisă pentru predicție.

![4 conserve de pastă de tomate pe un raft cu predicții pentru cele 4 detectări de 35.8%, 33.5%, 25.7% și 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.ro.png)

În imaginea de mai sus, au fost detectate 4 conserve de pastă de tomate. În rezultate, un pătrat roșu este suprapus pentru fiecare obiect detectat în imagine, indicând caseta delimitatoare pentru imagine.

✅ Deschide predicțiile în Custom Vision și verifică casetele delimitatoare.

Casetele delimitatoare sunt definite cu 4 valori - top, left, height și width. Aceste valori sunt pe o scară de la 0 la 1, reprezentând pozițiile ca procent din dimensiunea imaginii. Originea (poziția 0,0) este colțul din stânga sus al imaginii, astfel încât valoarea top este distanța de sus, iar partea de jos a casetei delimitatoare este top plus height.

![O casetă delimitatoare în jurul unei conserve de pastă de tomate](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.ro.png)

Imaginea de mai sus are 600 de pixeli lățime și 800 de pixeli înălțime. Caseta delimitatoare începe la 320 de pixeli în jos, oferind o coordonată top de 0.4 (800 x 0.4 = 320). De la stânga, caseta delimitatoare începe la 240 de pixeli în lateral, oferind o coordonată left de 0.4 (600 x 0.4 = 240). Înălțimea casetei delimitatoare este de 240 de pixeli, oferind o valoare height de 0.3 (800 x 0.3 = 240). Lățimea casetei delimitatoare este de 120 de pixeli, oferind o valoare width de 0.2 (600 x 0.2 = 120).

| Coordonată | Valoare |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Utilizarea valorilor procentuale de la 0 la 1 înseamnă că, indiferent de dimensiunea la care este scalată imaginea, caseta delimitatoare începe la 0.4 din lungime și înălțime și are 0.3 din înălțime și 0.2 din lățime.

Poți utiliza casetele delimitatoare combinate cu probabilitățile pentru a evalua cât de precisă este o detectare. De exemplu, un detector de obiecte poate detecta mai multe obiecte care se suprapun, de exemplu detectând o conservă în interiorul alteia. Codul tău ar putea analiza casetele delimitatoare, înțelege că acest lucru este imposibil și ignora orice obiecte care au o suprapunere semnificativă cu alte obiecte.

![Două casete delimitatoare suprapunându-se pe o conservă de pastă de tomate](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.ro.png)

În exemplul de mai sus, o casetă delimitatoare indică o conservă de pastă de tomate prezisă la 78.3%. O a doua casetă delimitatoare este puțin mai mică și se află în interiorul primei casete delimitatoare, cu o probabilitate de 64.3%. Codul tău poate verifica casetele delimitatoare, vedea că se suprapun complet și ignora probabilitatea mai mică, deoarece nu există nicio posibilitate ca una să fie în interiorul celeilalte.

✅ Poți să te gândești la o situație în care este valid să detectezi un obiect în interiorul altuia?

## Reantrenarea modelului

La fel ca în cazul clasificatorului de imagini, poți reantrena modelul folosind date capturate de dispozitivul tău IoT. Utilizarea acestor date din lumea reală va asigura că modelul funcționează bine atunci când este utilizat de pe dispozitivul tău IoT.

Spre deosebire de clasificatorul de imagini, nu poți doar să etichetezi o imagine. În schimb, trebuie să revizuiești fiecare casetă delimitatoare detectată de model. Dacă caseta este în jurul unui lucru greșit, trebuie să fie ștearsă, iar dacă este în locația greșită, trebuie ajustată.

### Sarcină - reantrenarea modelului

1. Asigură-te că ai capturat o gamă de imagini folosind dispozitivul tău IoT.

1. Din fila **Predictions**, selectează o imagine. Vei vedea casete roșii care indică casetele delimitatoare ale obiectelor detectate.

1. Lucrează prin fiecare casetă delimitatoare. Selectează-o mai întâi și vei vedea un pop-up care arată eticheta. Folosește mânerele de pe colțurile casetei delimitatoare pentru a ajusta dimensiunea, dacă este necesar. Dacă eticheta este greșită, elimin-o cu butonul **X** și adaugă eticheta corectă. Dacă caseta delimitatoare nu conține un obiect, șterge-o cu butonul coș de gunoi.

1. Închide editorul când ai terminat, iar imaginea va trece de la fila **Predictions** la fila **Training Images**. Repetă procesul pentru toate predicțiile.

1. Folosește butonul **Train** pentru a reantrena modelul. După ce s-a antrenat, publică iterația și actualizează dispozitivul IoT pentru a utiliza URL-ul noii iterații.

1. Re-deployează codul și testează dispozitivul IoT.

## Numărarea stocului

Folosind o combinație între numărul de obiecte detectate și casetele delimitatoare, poți număra stocul de pe un raft.

### Sarcină - numărarea stocului

Urmează ghidul relevant de mai jos pentru a număra stocul folosind rezultatele detectorului de obiecte de pe dispozitivul tău IoT:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Computer cu placă unică - Raspberry Pi/dispozitiv virtual](single-board-computer-count-stock.md)

---

## 🚀 Provocare

Poți detecta stocul incorect? Antrenează modelul pe mai multe obiecte, apoi actualizează aplicația pentru a te alerta dacă este detectat stocul greșit.

Poate chiar du-te mai departe și detectează stocul alăturat pe același raft și vezi dacă ceva a fost pus în locul greșit, definind limite pentru casetele delimitatoare.

## Chestionar după lecție

[Chestionar după lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Recapitulare și studiu individual

* Află mai multe despre cum să arhitectezi un sistem complet de detectare a stocului din ghidul [Out of stock detection at the edge pattern guide on Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Descoperă alte modalități de a construi soluții complete pentru retail combinând o gamă de servicii IoT și cloud urmărind acest [Behind the scenes of a retail solution - Hands On! video on YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Sarcină

[Folosește detectorul de obiecte la margine](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.