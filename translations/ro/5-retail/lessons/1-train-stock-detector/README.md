# Antrenează un detector de stocuri

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-19.cf6973cecadf080c.webp)

> Prezentare grafică de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

Acest videoclip oferă o prezentare generală a detectării obiectelor folosind serviciul Azure Custom Vision, un serviciu care va fi acoperit în această lecție.

[![Custom Vision 2 - Detectarea Obiectelor Simplificată | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Click pe imaginea de mai sus pentru a viziona videoclipul

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Introducere

În proiectul anterior, ai folosit AI pentru a antrena un clasificator de imagini - un model care poate determina dacă o imagine conține ceva, cum ar fi fructe coapte sau necoapte. Un alt tip de model AI care poate fi utilizat cu imagini este detectarea obiectelor. Aceste modele nu clasifică o imagine prin etichete, ci sunt antrenate să recunoască obiecte și să le găsească în imagini, detectând nu doar prezența obiectului, ci și locația acestuia în imagine. Acest lucru îți permite să numeri obiectele din imagini.

În această lecție vei învăța despre detectarea obiectelor, inclusiv cum poate fi utilizată în retail. De asemenea, vei învăța cum să antrenezi un detector de obiecte în cloud.

În această lecție vom acoperi:

* [Detectarea obiectelor](../../../../../5-retail/lessons/1-train-stock-detector)
* [Utilizarea detectării obiectelor în retail](../../../../../5-retail/lessons/1-train-stock-detector)
* [Antrenarea unui detector de obiecte](../../../../../5-retail/lessons/1-train-stock-detector)
* [Testarea detectorului de obiecte](../../../../../5-retail/lessons/1-train-stock-detector)
* [Reantrenarea detectorului de obiecte](../../../../../5-retail/lessons/1-train-stock-detector)

## Detectarea obiectelor

Detectarea obiectelor implică identificarea obiectelor din imagini folosind AI. Spre deosebire de clasificatorul de imagini pe care l-ai antrenat în proiectul anterior, detectarea obiectelor nu se referă la prezicerea celei mai bune etichete pentru o imagine în ansamblu, ci la găsirea unuia sau mai multor obiecte într-o imagine.

### Detectarea obiectelor vs clasificarea imaginilor

Clasificarea imaginilor se referă la clasificarea unei imagini în ansamblu - care sunt probabilitățile ca întreaga imagine să corespundă fiecărei etichete. Primești înapoi probabilități pentru fiecare etichetă utilizată pentru a antrena modelul.

![Clasificarea imaginilor pentru nuci caju și pastă de tomate](../../../../../translated_images/ro/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

În exemplul de mai sus, două imagini sunt clasificate folosind un model antrenat să clasifice cutii de nuci caju sau conserve de pastă de tomate. Prima imagine este o cutie de nuci caju și are două rezultate de la clasificatorul de imagini:

| Etichetă        | Probabilitate |
| --------------- | ------------: |
| `nuci caju`     | 98.4%         |
| `pastă de tomate` | 1.6%         |

A doua imagine este o conservă de pastă de tomate, iar rezultatele sunt:

| Etichetă        | Probabilitate |
| --------------- | ------------: |
| `nuci caju`     | 0.7%          |
| `pastă de tomate` | 99.3%         |

Ai putea folosi aceste valori cu un prag procentual pentru a prezice ce se află în imagine. Dar ce se întâmplă dacă o imagine conține mai multe conserve de pastă de tomate sau atât nuci caju, cât și pastă de tomate? Rezultatele probabil nu îți vor oferi ceea ce dorești. Aici intervine detectarea obiectelor.

Detectarea obiectelor implică antrenarea unui model pentru a recunoaște obiecte. În loc să îi oferi imagini care conțin obiectul și să îi spui că fiecare imagine este o etichetă sau alta, evidențiezi secțiunea unei imagini care conține obiectul specific și o etichetezi. Poți eticheta un singur obiect într-o imagine sau mai multe. În acest fel, modelul învață cum arată obiectul în sine, nu doar cum arată imaginile care conțin obiectul.

Când îl folosești pentru a prezice imagini, în loc să primești o listă de etichete și procente, primești o listă de obiecte detectate, cu caseta de delimitare și probabilitatea ca obiectul să corespundă etichetei atribuite.

> 🎓 *Casetele de delimitare* sunt casetele din jurul unui obiect.

![Detectarea obiectelor pentru nuci caju și pastă de tomate](../../../../../translated_images/ro/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Imaginea de mai sus conține atât o cutie de nuci caju, cât și trei conserve de pastă de tomate. Detectorul de obiecte a detectat nucile caju, returnând caseta de delimitare care conține nucile caju cu procentul de probabilitate că această casetă conține obiectul, în acest caz 97.6%. Detectorul de obiecte a detectat, de asemenea, trei conserve de pastă de tomate și oferă trei casete de delimitare separate, câte una pentru fiecare conservă detectată, fiecare având o probabilitate procentuală că această casetă conține o conservă de pastă de tomate.

✅ Gândește-te la câteva scenarii diferite în care ai putea folosi modele AI bazate pe imagini. Care dintre ele ar avea nevoie de clasificare și care de detectare a obiectelor?

### Cum funcționează detectarea obiectelor

Detectarea obiectelor folosește modele complexe de ML. Aceste modele funcționează împărțind imaginea în mai multe celule, apoi verifică dacă centrul casetei de delimitare este centrul unei imagini care corespunde uneia dintre imaginile utilizate pentru a antrena modelul. Poți considera acest proces ca fiind similar cu rularea unui clasificator de imagini pe diferite părți ale imaginii pentru a căuta potriviri.

> 💁 Aceasta este o supra-simplificare drastică. Există multe tehnici pentru detectarea obiectelor, iar tu poți citi mai multe despre ele pe [pagina de detectare a obiectelor de pe Wikipedia](https://wikipedia.org/wiki/Object_detection).

Există o serie de modele diferite care pot face detectarea obiectelor. Un model deosebit de faimos este [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), care este incredibil de rapid și poate detecta 20 de clase diferite de obiecte, cum ar fi oameni, câini, sticle și mașini.

✅ Citește despre modelul YOLO pe [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Modelele de detectare a obiectelor pot fi reantrenate folosind transfer learning pentru a detecta obiecte personalizate.

## Utilizarea detectării obiectelor în retail

Detectarea obiectelor are multiple utilizări în retail. Unele dintre acestea includ:

* **Verificarea și numărarea stocurilor** - recunoașterea momentului în care stocul este scăzut pe rafturi. Dacă stocul este prea scăzut, pot fi trimise notificări personalului sau roboților pentru a reumple rafturile.
* **Detectarea măștilor** - în magazinele cu politici de purtare a măștilor în timpul evenimentelor de sănătate publică, detectarea obiectelor poate recunoaște persoanele cu măști și pe cele fără.
* **Facturare automată** - detectarea articolelor luate de pe rafturi în magazinele automatizate și facturarea corespunzătoare a clienților.
* **Detectarea pericolelor** - recunoașterea obiectelor sparte pe podea sau a lichidelor vărsate, alertând echipele de curățenie.

✅ Fă niște cercetări: Care sunt alte utilizări ale detectării obiectelor în retail?

## Antrenarea unui detector de obiecte

Poți antrena un detector de obiecte folosind Custom Vision, într-un mod similar cu cel în care ai antrenat un clasificator de imagini.

### Sarcină - creează un detector de obiecte

1. Creează un grup de resurse pentru acest proiect numit `stock-detector`.

1. Creează o resursă gratuită de antrenare Custom Vision și o resursă gratuită de predicție Custom Vision în grupul de resurse `stock-detector`. Denumește-le `stock-detector-training` și `stock-detector-prediction`.

    > 💁 Poți avea doar o resursă gratuită de antrenare și una de predicție, așa că asigură-te că ai curățat proiectul din lecțiile anterioare.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea resurselor de antrenare și predicție din proiectul 4, lecția 1, dacă este necesar](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Accesează portalul Custom Vision la [CustomVision.ai](https://customvision.ai) și autentifică-te cu contul Microsoft pe care l-ai folosit pentru contul tău Azure.

1. Urmează secțiunea [Crearea unui proiect nou din ghidul rapid pentru construirea unui detector de obiecte pe documentația Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) pentru a crea un nou proiect Custom Vision. Interfața utilizatorului poate suferi modificări, iar această documentație este întotdeauna cea mai actualizată referință.

    Denumește proiectul tău `stock-detector`.

    Când creezi proiectul, asigură-te că folosești resursa `stock-detector-training` pe care ai creat-o anterior. Utilizează tipul de proiect *Object Detection* și domeniul *Products on Shelves*.

    ![Setările pentru proiectul Custom Vision cu numele setat la fruit-quality-detector, fără descriere, resursa setată la fruit-quality-detector-training, tipul proiectului setat la classification, tipurile de clasificare setate la multi class și domeniile setate la food](../../../../../translated_images/ro/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Domeniul *Products on Shelves* este special conceput pentru detectarea stocurilor pe rafturile magazinelor. Citește mai multe despre diferitele domenii în [documentația Select a domain pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection).

✅ Alocă-ți timp pentru a explora interfața Custom Vision pentru detectorul tău de obiecte.

### Sarcină - antrenează-ți detectorul de obiecte

Pentru a-ți antrena modelul, vei avea nevoie de un set de imagini care conțin obiectele pe care dorești să le detectezi.

1. Adună imagini care conțin obiectul de detectat. Vei avea nevoie de cel puțin 15 imagini care conțin fiecare obiect de detectat, dintr-o varietate de unghiuri și în condiții diferite de iluminare, dar cu cât mai multe, cu atât mai bine. Acest detector de obiecte folosește domeniul *Products on Shelves*, așa că încearcă să aranjezi obiectele ca și cum ar fi pe un raft de magazin. Vei avea nevoie și de câteva imagini pentru a testa modelul. Dacă detectezi mai multe obiecte, vei dori câteva imagini de testare care să conțină toate obiectele.

    > 💁 Imaginile cu mai multe obiecte diferite contează pentru minimul de 15 imagini pentru toate obiectele din imagine.

    Imaginile tale ar trebui să fie în format png sau jpeg, mai mici de 6MB. Dacă le creezi cu un iPhone, de exemplu, acestea pot fi imagini HEIC de înaltă rezoluție, așa că va trebui să fie convertite și, posibil, micșorate. Cu cât mai multe imagini, cu atât mai bine, și ar trebui să ai un număr similar de imagini pentru fiecare obiect.

    Modelul este conceput pentru produse pe rafturi, așa că încearcă să faci fotografiile obiectelor pe rafturi.

    Poți găsi câteva imagini exemplu pe care le poți folosi în folderul [images](../../../../../5-retail/lessons/1-train-stock-detector/images) cu nuci caju și pastă de tomate.

1. Urmează secțiunea [Încărcarea și etichetarea imaginilor din ghidul rapid pentru construirea unui detector de obiecte pe documentația Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) pentru a încărca imaginile de antrenament. Creează etichete relevante în funcție de tipurile de obiecte pe care dorești să le detectezi.

    ![Dialogurile de încărcare care arată încărcarea imaginilor cu banane coapte și necoapte](../../../../../translated_images/ro/image-upload-object-detector.77c7892c3093cb59.webp)

    Când desenezi casetele de delimitare pentru obiecte, păstrează-le bine strânse în jurul obiectului. Poate dura ceva timp să conturezi toate imaginile, dar instrumentul va detecta ceea ce crede că sunt casetele de delimitare, făcând procesul mai rapid.

    ![Etichetarea pastei de tomate](../../../../../translated_images/ro/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Dacă ai mai mult de 15 imagini pentru fiecare obiect, poți antrena după 15 imagini, apoi folosi funcția **Suggested tags**. Aceasta va folosi modelul antrenat pentru a detecta obiectele în imaginile netaguite. Poți apoi confirma obiectele detectate sau respinge și redesena casetele de delimitare. Acest lucru poate economisi *mult* timp.

1. Urmează secțiunea [Antrenarea detectorului din ghidul rapid pentru construirea unui detector de obiecte pe documentația Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) pentru a antrena detectorul de obiecte pe imaginile etichetate.

    Ți se va oferi o alegere a tipului de antrenament. Selectează **Quick Training**.

Detectorul de obiecte va începe să se antreneze. Va dura câteva minute pentru ca antrenamentul să fie complet.

## Testarea detectorului de obiecte

Odată ce detectorul tău de obiecte este antrenat, îl poți testa oferindu-i imagini noi pentru a detecta obiecte.

### Sarcină - testează-ți detectorul de obiecte

1. Folosește butonul **Quick Test** pentru a încărca imagini de testare și a verifica dacă obiectele sunt detectate. Folosește imaginile de testare pe care le-ai creat anterior, nu pe cele utilizate pentru antrenament.

    ![3 conserve de pastă de tomate detectate cu probabilități de 38%, 35.5% și 34.6%](../../../../../translated_images/ro/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Încearcă toate imaginile de testare pe care le ai și observă probabilitățile.

## Reantrenarea detectorului de obiecte

Când testezi detectorul tău de obiecte, este posibil să nu ofere rezultatele pe care le aștepți, la fel ca în cazul clasificatorilor de imagini din proiectul anterior. Poți îmbunătăți detectorul tău de obiecte reantrenându-l cu imagini pe care le interpretează greșit.

De fiecare dată când faci o predicție folosind opțiunea de testare rapidă, imaginea și rezultatele sunt stocate. Poți folosi aceste imagini pentru a-ți reantrena modelul.

1. Folosește fila **Predictions** pentru a localiza imaginile pe care le-ai folosit pentru testare.

1. Confirmă orice detecții corecte, șterge-le pe cele incorecte și adaugă orice obiecte lipsă.

1. Reantrenează și retestează modelul.

---

## 🚀 Provocare

Ce s-ar întâmpla dacă ai folosi detectorul de obiecte cu articole care arată similar, cum ar fi conserve de pastă de tomate și conserve de roșii tocate de la același brand?

Dacă ai articole care arată similar, testează-le adăugând imagini cu acestea în detectorul tău de obiecte.

## Chestionar după lecție
[Quiz după prelegere](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Recapitulare și Studiu Individual

* Când ai antrenat detectorul de obiecte, ai observat valori pentru *Precizie*, *Recall* și *mAP* care evaluează modelul creat. Citește mai multe despre aceste valori folosind [secțiunea Evaluarea detectorului din ghidul rapid pentru construirea unui detector de obiecte pe Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Citește mai multe despre detectarea obiectelor pe [pagina Detectarea obiectelor de pe Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Temă

[Compară domeniile](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.