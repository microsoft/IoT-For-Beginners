# Verificarea calității fructelor cu un dispozitiv IoT

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-16.215daf18b00631fb.webp)

> Prezentare grafică realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introducere

În lecția anterioară, ați învățat despre clasificatorii de imagini și cum să îi antrenați pentru a detecta fructele bune și rele. Pentru a utiliza acest clasificator de imagini într-o aplicație IoT, trebuie să puteți captura o imagine folosind o cameră și să trimiteți această imagine în cloud pentru a fi clasificată.

În această lecție, veți învăța despre senzorii de cameră și cum să îi utilizați cu un dispozitiv IoT pentru a captura o imagine. De asemenea, veți învăța cum să apelați clasificatorul de imagini de pe dispozitivul IoT.

În această lecție vom acoperi:

* [Senzori de cameră](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Capturarea unei imagini folosind un dispozitiv IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publicarea clasificatorului de imagini](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Clasificarea imaginilor de pe dispozitivul IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Îmbunătățirea modelului](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Senzori de cameră

Senzorii de cameră, așa cum sugerează numele, sunt camere care pot fi conectate la un dispozitiv IoT. Acestea pot captura imagini statice sau pot înregistra fluxuri video. Unele camere returnează date brute ale imaginii, în timp ce altele comprimă datele într-un fișier imagine, cum ar fi JPEG sau PNG. De obicei, camerele compatibile cu dispozitivele IoT sunt mult mai mici și au o rezoluție mai scăzută decât cele cu care sunteți obișnuiți, dar există și camere de înaltă rezoluție care rivalizează cu telefoanele de top. Puteți găsi o varietate de lentile interschimbabile, configurații cu mai multe camere, camere termice în infraroșu sau camere UV.

![Lumina dintr-o scenă trece printr-o lentilă și este focalizată pe un senzor CMOS](../../../../../translated_images/ro/cmos-sensor.75f9cd74decb1371.webp)

Majoritatea senzorilor de cameră utilizează senzori de imagine în care fiecare pixel este o fotodiodă. O lentilă focalizează imaginea pe senzorul de imagine, iar mii sau milioane de fotodiode detectează lumina care cade pe fiecare dintre ele, înregistrând aceasta ca date de pixel.

> 💁 Lentilele inversează imaginile, iar senzorul camerei le întoarce înapoi în poziția corectă. Același lucru se întâmplă și în ochii voștri - ceea ce vedeți este detectat invers pe partea din spate a ochiului, iar creierul corectează acest lucru.

> 🎓 Senzorul de imagine este cunoscut sub numele de senzor activ de pixeli (APS), iar cel mai popular tip de APS este senzorul complementar metal-oxid-semiconductor, sau CMOS. Este posibil să fi auzit termenul de senzor CMOS folosit pentru senzorii de cameră.

Senzorii de cameră sunt senzori digitali, care trimit datele imaginii sub formă de date digitale, de obicei cu ajutorul unei biblioteci care facilitează comunicarea. Camerele se conectează folosind protocoale precum SPI pentru a permite trimiterea unor cantități mari de date - imaginile sunt considerabil mai mari decât valorile unice de la un senzor, cum ar fi un senzor de temperatură.

✅ Care sunt limitările legate de dimensiunea imaginii pe dispozitivele IoT? Gândiți-vă la constrângerile hardware, în special pe microcontrolere.

## Capturarea unei imagini folosind un dispozitiv IoT

Puteți utiliza dispozitivul IoT pentru a captura o imagine care să fie clasificată.

### Sarcină - capturarea unei imagini folosind un dispozitiv IoT

Parcurgeți ghidul relevant pentru a captura o imagine folosind dispozitivul IoT:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Computer cu placă unică - Raspberry Pi](pi-camera.md)
* [Computer cu placă unică - Dispozitiv virtual](virtual-device-camera.md)

## Publicarea clasificatorului de imagini

Ați antrenat clasificatorul de imagini în lecția anterioară. Înainte de a-l putea utiliza de pe dispozitivul IoT, trebuie să publicați modelul.

### Iterațiile modelului

Când modelul a fost antrenat în lecția anterioară, este posibil să fi observat că fila **Performance** afișează iterații în partea laterală. Când ați antrenat modelul pentru prima dată, ați văzut *Iteration 1* în timpul antrenamentului. Când ați îmbunătățit modelul folosind imaginile de predicție, ați văzut *Iteration 2* în timpul antrenamentului.

De fiecare dată când antrenați modelul, obțineți o nouă iterație. Aceasta este o modalitate de a urmări diferitele versiuni ale modelului antrenate pe seturi de date diferite. Când efectuați un **Quick Test**, există un meniu derulant pe care îl puteți utiliza pentru a selecta iterația, astfel încât să puteți compara rezultatele între mai multe iterații.

Când sunteți mulțumit de o iterație, o puteți publica pentru a fi utilizată de aplicații externe. În acest fel, puteți avea o versiune publicată utilizată de dispozitivele voastre, apoi să lucrați la o versiune nouă pe parcursul mai multor iterații, pe care să o publicați odată ce sunteți mulțumit de aceasta.

### Sarcină - publicarea unei iterații

Iterațiile sunt publicate din portalul Custom Vision.

1. Accesați portalul Custom Vision la [CustomVision.ai](https://customvision.ai) și conectați-vă dacă nu l-ați deschis deja. Apoi deschideți proiectul `fruit-quality-detector`.

1. Selectați fila **Performance** din opțiunile de sus.

1. Selectați cea mai recentă iterație din lista *Iterations* din partea laterală.

1. Selectați butonul **Publish** pentru iterație.

    ![Butonul de publicare](../../../../../translated_images/ro/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. În dialogul *Publish Model*, setați *Prediction resource* la resursa `fruit-quality-detector-prediction` creată în lecția anterioară. Lăsați numele ca `Iteration2` și selectați butonul **Publish**.

1. Odată publicat, selectați butonul **Prediction URL**. Acesta va afișa detalii despre API-ul de predicție, iar acestea vor fi necesare pentru a apela modelul de pe dispozitivul IoT. Secțiunea de jos este etichetată *If you have an image file*, iar acestea sunt detaliile de care aveți nevoie. Luați o copie a URL-ului afișat, care va arăta astfel:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Unde `<location>` va fi locația utilizată la crearea resursei Custom Vision, iar `<id>` va fi un ID lung format din litere și cifre.

    De asemenea, luați o copie a valorii *Prediction-Key*. Aceasta este o cheie de securitate pe care trebuie să o transmiteți când apelați modelul. Doar aplicațiile care transmit această cheie au permisiunea de a utiliza modelul, orice alte aplicații sunt respinse.

    ![Dialogul API de predicție care arată URL-ul și cheia](../../../../../translated_images/ro/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Când o nouă iterație este publicată, aceasta va avea un nume diferit. Cum credeți că ați putea schimba iterația utilizată de un dispozitiv IoT?

## Clasificarea imaginilor de pe dispozitivul IoT

Acum puteți utiliza aceste detalii de conexiune pentru a apela clasificatorul de imagini de pe dispozitivul IoT.

### Sarcină - clasificarea imaginilor de pe dispozitivul IoT

Parcurgeți ghidul relevant pentru a clasifica imagini folosind dispozitivul IoT:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Computer cu placă unică - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-classify-image.md)

## Îmbunătățirea modelului

Este posibil să constatați că rezultatele obținute folosind camera conectată la dispozitivul IoT nu corespund așteptărilor. Predicțiile nu sunt întotdeauna la fel de precise ca atunci când utilizați imagini încărcate de pe computer. Acest lucru se întâmplă deoarece modelul a fost antrenat pe date diferite față de cele utilizate pentru predicții.

Pentru a obține cele mai bune rezultate pentru un clasificator de imagini, doriți să antrenați modelul cu imagini cât mai asemănătoare cu cele utilizate pentru predicții. De exemplu, dacă ați folosit camera telefonului pentru a captura imagini pentru antrenament, calitatea imaginii, claritatea și culorile vor fi diferite față de o cameră conectată la un dispozitiv IoT.

![2 imagini cu banane, una cu rezoluție scăzută și iluminare slabă de la un dispozitiv IoT, cealaltă cu rezoluție înaltă și iluminare bună de la un telefon](../../../../../translated_images/ro/banana-picture-compare.174df164dc326a42.webp)

În imaginea de mai sus, fotografia cu banana din stânga a fost realizată folosind o cameră Raspberry Pi, iar cea din dreapta a fost realizată cu același banana în aceeași locație folosind un iPhone. Există o diferență vizibilă în calitate - fotografia realizată cu iPhone-ul este mai clară, cu culori mai vii și mai mult contrast.

✅ Ce altceva ar putea cauza ca imaginile capturate de dispozitivul IoT să aibă predicții incorecte? Gândiți-vă la mediul în care ar putea fi utilizat un dispozitiv IoT, ce factori pot afecta imaginea capturată?

Pentru a îmbunătăți modelul, puteți să-l reantrenați folosind imaginile capturate de dispozitivul IoT.

### Sarcină - îmbunătățirea modelului

1. Clasificați mai multe imagini cu fructe coapte și necoapte folosind dispozitivul IoT.

1. În portalul Custom Vision, reantrenați modelul folosind imaginile din fila *Predictions*.

    > ⚠️ Puteți consulta [instrucțiunile pentru reantrenarea clasificatorului în lecția 1, dacă este necesar](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Dacă imaginile voastre arată foarte diferit de cele originale utilizate pentru antrenament, puteți șterge toate imaginile originale selectându-le în fila *Training Images* și apăsând butonul **Delete**. Pentru a selecta o imagine, mutați cursorul peste ea și va apărea o bifă, selectați acea bifă pentru a selecta sau deselecta imaginea.

1. Antrenați o nouă iterație a modelului și publicați-o folosind pașii de mai sus.

1. Actualizați URL-ul endpoint-ului în codul vostru și rulați din nou aplicația.

1. Repetați acești pași până când sunteți mulțumit de rezultatele predicțiilor.

---

## 🚀 Provocare

Cât de mult afectează rezoluția imaginii sau iluminarea predicția?

Încercați să modificați rezoluția imaginilor în codul dispozitivului și vedeți dacă face o diferență în calitatea imaginilor. De asemenea, încercați să schimbați iluminarea.

Dacă ați crea un dispozitiv de producție pentru a fi vândut fermelor sau fabricilor, cum ați asigura rezultate consistente tot timpul?

## Chestionar după lecție

[Chestionar după lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Recapitulare și studiu individual

Ați antrenat modelul Custom Vision folosind portalul. Acest lucru se bazează pe existența unor imagini disponibile - iar în lumea reală este posibil să nu puteți obține date de antrenament care să corespundă cu ceea ce camera dispozitivului vostru capturează. Puteți rezolva acest lucru antrenând direct de pe dispozitiv folosind API-ul de antrenament, pentru a antrena un model utilizând imagini capturate de dispozitivul IoT.

* Citiți despre API-ul de antrenament în [ghidul de început rapid pentru utilizarea SDK-ului Custom Vision](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Temă

[Reacționați la rezultatele clasificării](assignment.md)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.