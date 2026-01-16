<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-28T11:14:47+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "ro"
}
-->
# Păstrează-ți planta în siguranță

![O prezentare grafică a lecției](../../../../../translated_images/ro/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Ilustrație de [Nitya Narasimhan](https://github.com/nitya). Click pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Introducere

În ultimele lecții, ai creat un dispozitiv IoT pentru monitorizarea solului și l-ai conectat la cloud. Dar ce s-ar întâmpla dacă hackeri care lucrează pentru un fermier rival ar reuși să preia controlul asupra dispozitivelor tale IoT? Ce s-ar întâmpla dacă aceștia ar trimite citiri false de umiditate ridicată a solului, astfel încât plantele tale să nu fie niciodată udate, sau ar porni sistemul de irigare să funcționeze continuu, distrugând plantele prin supra-udare și generând costuri mari la apă?

În această lecție vei învăța cum să securizezi dispozitivele IoT. Fiind ultima lecție din acest proiect, vei învăța și cum să cureți resursele din cloud, reducând astfel costurile potențiale.

În această lecție vom acoperi:

* [De ce este necesar să securizezi dispozitivele IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Criptografie](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Securizarea dispozitivelor IoT](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generarea și utilizarea unui certificat X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Aceasta este ultima lecție din acest proiect, așa că după ce finalizezi lecția și sarcina, nu uita să cureți serviciile din cloud. Vei avea nevoie de aceste servicii pentru a finaliza sarcina, așa că asigură-te că o finalizezi mai întâi.
>
> Consultă [ghidul pentru curățarea proiectului](../../../clean-up.md) dacă ai nevoie de instrucțiuni despre cum să faci acest lucru.

## De ce este necesar să securizezi dispozitivele IoT?

Securitatea IoT presupune asigurarea că doar dispozitivele autorizate pot să se conecteze la serviciul tău IoT din cloud și să trimită telemetrie, iar doar serviciul tău din cloud poate trimite comenzi către dispozitivele tale. Datele IoT pot fi, de asemenea, personale, incluzând informații medicale sau intime, astfel încât întreaga aplicație trebuie să ia în considerare securitatea pentru a preveni scurgerile de date.

Dacă aplicația ta IoT nu este securizată, există mai multe riscuri:

* Un dispozitiv fals ar putea trimite date incorecte, determinând aplicația să răspundă greșit. De exemplu, ar putea trimite constant citiri ridicate de umiditate a solului, ceea ce ar însemna că sistemul tău de irigare nu se pornește niciodată, iar plantele tale mor din lipsă de apă.
* Utilizatori neautorizați ar putea citi date de la dispozitivele IoT, inclusiv date personale sau critice pentru afaceri.
* Hackerii ar putea trimite comenzi pentru a controla un dispozitiv într-un mod care ar putea provoca daune dispozitivului sau hardware-ului conectat.
* Prin conectarea la un dispozitiv IoT, hackerii ar putea accesa rețele suplimentare pentru a obține acces la sisteme private.
* Utilizatori rău intenționați ar putea accesa date personale și le-ar putea folosi pentru șantaj.

Acestea sunt scenarii reale și se întâmplă frecvent. Unele exemple au fost prezentate în lecțiile anterioare, dar iată câteva altele:

* În 2018, hackerii au folosit un punct de acces WiFi deschis de pe un termostat pentru acvariu pentru a accesa rețeaua unui cazinou și a fura date. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* În 2016, botnet-ul Mirai a lansat un atac de tip denial of service împotriva Dyn, un furnizor de servicii de internet, blocând mari porțiuni ale internetului. Acest botnet a folosit malware pentru a se conecta la dispozitive IoT precum DVR-uri și camere care utilizau nume de utilizator și parole implicite, și de acolo a lansat atacul. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys a avut o bază de date cu utilizatorii jucăriilor lor conectate CloudPets disponibilă public pe internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava a etichetat alergătorii pe care i-ai depășit și a arătat traseele lor, permițând străinilor să vadă efectiv unde locuiești. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Fă o cercetare: Caută mai multe exemple de atacuri IoT și breșe de date IoT, în special cu obiecte personale precum periuțe de dinți sau cântare conectate la internet. Gândește-te la impactul pe care aceste atacuri l-ar putea avea asupra victimelor sau clienților.

> 💁 Securitatea este un subiect vast, iar această lecție va aborda doar câteva dintre bazele conectării dispozitivului tău la cloud. Alte subiecte care nu vor fi acoperite includ monitorizarea modificărilor de date în tranzit, hacking-ul dispozitivelor direct sau modificările configurațiilor dispozitivelor. Hacking-ul IoT este o amenințare atât de mare încât au fost dezvoltate instrumente precum [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Aceste instrumente sunt similare cu programele antivirus și de securitate pe care le-ai putea avea pe computerul tău, dar sunt concepute pentru dispozitive IoT mici și cu consum redus de energie.

## Criptografie

Când un dispozitiv se conectează la un serviciu IoT, folosește un ID pentru a se identifica. Problema este că acest ID poate fi clonat - un hacker ar putea configura un dispozitiv malițios care folosește același ID ca un dispozitiv real, dar trimite date false.

![Atât dispozitivele valide, cât și cele malițioase ar putea folosi același ID pentru a trimite telemetrie](../../../../../translated_images/ro/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

Soluția este să transformi datele trimise într-un format criptat, folosind o valoare cunoscută doar de dispozitiv și de cloud. Acest proces se numește *criptare*, iar valoarea utilizată pentru criptarea datelor se numește *cheie de criptare*.

![Dacă se folosește criptarea, doar mesajele criptate vor fi acceptate, celelalte vor fi respinse](../../../../../translated_images/ro/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

Serviciul cloud poate apoi să convertească datele înapoi într-un format lizibil, folosind un proces numit *decriptare*, utilizând fie aceeași cheie de criptare, fie o *cheie de decriptare*. Dacă mesajul criptat nu poate fi decriptat cu cheia, dispozitivul a fost compromis, iar mesajul este respins.

Tehnica utilizată pentru criptare și decriptare se numește *criptografie*.

### Criptografia timpurie

Cele mai vechi tipuri de criptografie au fost cifrurile de substituție, datând de acum 3.500 de ani. Cifrurile de substituție implică înlocuirea unei litere cu alta. De exemplu, [cifrul Caesar](https://wikipedia.org/wiki/Caesar_cipher) implică deplasarea alfabetului cu o cantitate definită, cunoscută doar de expeditorul mesajului criptat și de destinatarul intenționat.

[Cifrul Vigenère](https://wikipedia.org/wiki/Vigenère_cipher) a dus acest concept mai departe, utilizând cuvinte pentru a cripta textul, astfel încât fiecare literă din textul original să fie deplasată cu o cantitate diferită, în loc de a fi deplasată mereu cu același număr de litere.

Criptografia a fost utilizată pentru o gamă largă de scopuri, cum ar fi protejarea unei rețete de glazură a olarilor în Mesopotamia antică, scrierea de bilețele de dragoste secrete în India sau păstrarea secretă a vrăjilor magice egiptene antice.

### Criptografia modernă

Criptografia modernă este mult mai avansată, ceea ce o face mult mai greu de spart decât metodele timpurii. Criptografia modernă utilizează matematici complexe pentru a cripta datele, cu un număr atât de mare de chei posibile încât atacurile brute force devin imposibile.

Criptografia este utilizată în multe moduri pentru comunicații sigure. Dacă citești această pagină pe GitHub, este posibil să observi că adresa web începe cu *HTTPS*, ceea ce înseamnă că comunicarea dintre browserul tău și serverele web ale GitHub este criptată. Dacă cineva ar putea citi traficul de internet dintre browserul tău și GitHub, nu ar putea citi datele, deoarece sunt criptate. Computerul tău ar putea chiar să cripteze toate datele de pe hard disk, astfel încât, dacă cineva îl fură, să nu poată citi datele fără parola ta.

> 🎓 HTTPS înseamnă HyperText Transfer Protocol **Secure**

Din păcate, nu totul este securizat. Unele dispozitive nu au deloc securitate, altele sunt securizate cu chei ușor de spart sau, uneori, toate dispozitivele de același tip folosesc aceeași cheie. Au existat cazuri de dispozitive IoT foarte personale care au toate aceeași parolă pentru a se conecta la ele prin WiFi sau Bluetooth. Dacă te poți conecta la propriul dispozitiv, te poți conecta și la al altcuiva. Odată conectat, ai putea accesa date foarte private sau controla dispozitivul lor.

> 💁 În ciuda complexității criptografiei moderne și a afirmațiilor că spargerea criptării poate dura miliarde de ani, apariția calculatoarelor cuantice a dus la posibilitatea de a sparge toate criptările cunoscute într-un timp foarte scurt!

### Chei simetrice și asimetrice

Criptarea vine în două tipuri - simetrică și asimetrică.

**Criptarea simetrică** folosește aceeași cheie pentru a cripta și decripta datele. Atât expeditorul, cât și destinatarul trebuie să cunoască aceeași cheie. Acesta este cel mai puțin sigur tip, deoarece cheia trebuie să fie partajată cumva. Pentru ca un expeditor să trimită un mesaj criptat unui destinatar, expeditorul ar putea mai întâi să trimită cheia destinatarului.

![Criptarea cu cheie simetrică folosește aceeași cheie pentru a cripta și decripta un mesaj](../../../../../translated_images/ro/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Dacă cheia este furată în tranzit sau dacă expeditorul sau destinatarul sunt hackeriți și cheia este găsită, criptarea poate fi spartă.

![Criptarea cu cheie simetrică este sigură doar dacă un hacker nu obține cheia - dacă o face, poate intercepta și decripta mesajul](../../../../../translated_images/ro/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Criptarea asimetrică** folosește 2 chei - o cheie de criptare și o cheie de decriptare, denumite pereche de chei publice/private. Cheia publică este utilizată pentru a cripta mesajul, dar nu poate fi utilizată pentru a-l decripta, iar cheia privată este utilizată pentru a decripta mesajul, dar nu poate fi utilizată pentru a-l cripta.

![Criptarea asimetrică folosește o cheie diferită pentru a cripta și decripta. Cheia de criptare este trimisă oricărui expeditor de mesaje, astfel încât acesta să poată cripta un mesaj înainte de a-l trimite destinatarului care deține cheile](../../../../../translated_images/ro/send-message-asymmetric.7abe327c62615b8c.webp)

Destinatarul își partajează cheia publică, iar expeditorul o folosește pentru a cripta mesajul. Odată ce mesajul este trimis, destinatarul îl decriptează cu cheia sa privată. Criptarea asimetrică este mai sigură, deoarece cheia privată este păstrată privată de către destinatar și nu este niciodată partajată. Oricine poate avea cheia publică, deoarece aceasta poate fi utilizată doar pentru a cripta mesaje.

Criptarea simetrică este mai rapidă decât cea asimetrică, dar cea asimetrică este mai sigură. Unele sisteme folosesc ambele - utilizând criptarea asimetrică pentru a cripta și partaja cheia simetrică, apoi utilizând cheia simetrică pentru a cripta toate datele. Acest lucru face mai sigură partajarea cheii simetrice între expeditor și destinatar și mai rapidă criptarea și decriptarea datelor.

## Securizarea dispozitivelor IoT

Dispozitivele IoT pot fi securizate folosind criptare simetrică sau asimetrică. Criptarea simetrică este mai ușoară, dar mai puțin sigură.

### Chei simetrice

Când configurezi dispozitivul IoT pentru a interacționa cu IoT Hub, ai utilizat un șir de conexiune. Un exemplu de șir de conexiune este:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Acest șir de conexiune este format din trei părți separate prin punct și virgulă, fiecare parte fiind o cheie și o valoare:

| Cheie | Valoare | Descriere |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL-ul IoT Hub |
| DeviceId | `soil-moisture-sensor` | ID-ul unic al dispozitivului |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | O cheie simetrică cunoscută de dispozitiv și de IoT Hub |

Ultima parte a acestui șir de conexiune, `SharedAccessKey`, este cheia simetrică cunoscută atât de dispozitiv, cât și de IoT Hub. Această cheie nu este niciodată trimisă de la dispozitiv la cloud sau de la cloud la dispozitiv. În schimb, este utilizată pentru a cripta datele trimise sau primite.

✅ Fă un experiment. Ce crezi că se va întâmpla dacă modifici partea `SharedAccessKey` a șirului de conexiune atunci când conectezi dispozitivul IoT? Încearcă și vezi.

Când dispozitivul încearcă să se conecteze pentru prima dată, trimite un token de semnătură de acces partajat (SAS) care constă din URL-ul IoT Hub, un timestamp care indică momentul expirării semnăturii de acces (de obicei 1 zi de la momentul curent) și o semnătură. Această semnătură constă din URL-ul și timpul de expirare criptate cu cheia de acces partajată din șirul de conexiune.

IoT Hub decriptează această semnătură cu cheia de acces partajată, iar dacă valoarea decriptată se potrivește cu URL-ul și expirarea, dispozitivul este permis să se conecteze. De asemenea, verifică dacă timpul curent este înainte de expirare, pentru a împiedica un dispozitiv malițios să captureze token-ul SAS al unui dispozitiv real și să-l folosească.

Aceasta este o metodă elegantă de a verifica dacă expeditorul este dispozitivul corect. Trimițând unele date cunoscute atât într-o formă decriptată, cât și criptată, serverul poate verifica dispozitivul asigurându-se că, atunci când decriptează datele criptate, rezultatul se potrivește cu versiunea decriptată trimisă. Dacă se potrivește, atunci atât expeditorul, cât și destinatarul au aceeași cheie de criptare simetrică.
💁 Datorită timpului de expirare, dispozitivul tău IoT trebuie să cunoască ora exactă, de obicei citită de la un server [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Dacă ora nu este precisă, conexiunea va eșua.
După conectare, toate datele trimise către IoT Hub de la dispozitiv sau către dispozitiv de la IoT Hub vor fi criptate cu cheia de acces partajată.

✅ Ce crezi că se va întâmpla dacă mai multe dispozitive împart același șir de conexiune?

> 💁 Este o practică de securitate proastă să stochezi această cheie în cod. Dacă un hacker obține codul sursă, poate obține cheia ta. De asemenea, devine mai dificil la lansarea codului, deoarece ar trebui să recompili cu o cheie actualizată pentru fiecare dispozitiv. Este mai bine să încarci această cheie dintr-un modul de securitate hardware - un cip pe dispozitivul IoT care stochează valori criptate ce pot fi citite de codul tău.
>
> Când înveți despre IoT, este adesea mai ușor să pui cheia în cod, așa cum ai făcut într-o lecție anterioară, dar trebuie să te asiguri că această cheie nu este verificată în controlul sursei publice.

Dispozitivele au 2 chei și 2 șiruri de conexiune corespunzătoare. Acest lucru îți permite să rotești cheile - adică să treci de la o cheie la alta dacă prima este compromisă și să regenerezi prima cheie.

### Certificate X.509

Când folosești criptarea asimetrică cu o pereche de chei publice/private, trebuie să oferi cheia ta publică oricui dorește să îți trimită date. Problema este: cum poate destinatarul cheii tale să fie sigur că este într-adevăr cheia ta publică, nu a altcuiva care pretinde că ești tu? În loc să oferi o cheie, poți oferi cheia ta publică într-un certificat care a fost verificat de o terță parte de încredere, numit certificat X.509.

Certificatele X.509 sunt documente digitale care conțin partea publică a perechii de chei publice/private. Acestea sunt de obicei emise de una dintre numeroasele organizații de încredere numite [Autorități de certificare](https://wikipedia.org/wiki/Certificate_authority) (CAs) și semnate digital de CA pentru a indica faptul că cheia este validă și provine de la tine. Ai încredere în certificat și în faptul că cheia publică provine de la cine spune certificatul că provine, deoarece ai încredere în CA, similar cu modul în care ai avea încredere într-un pașaport sau permis de conducere, deoarece ai încredere în țara care îl emite. Certificatele costă bani, așa că poți și să „semnezi singur”, adică să creezi un certificat tu însuți care este semnat de tine, pentru scopuri de testare.

> 💁 Nu ar trebui niciodată să folosești un certificat semnat de tine pentru o lansare în producție.

Aceste certificate au o serie de câmpuri, inclusiv cine este sursa cheii publice, detaliile CA care l-a emis, cât timp este valabil și cheia publică în sine. Înainte de a folosi un certificat, este o practică bună să îl verifici, asigurându-te că a fost semnat de CA original.

✅ Poți citi o listă completă a câmpurilor din certificat în [tutorialul Microsoft Understanding X.509 Public Key Certificates](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Când folosești certificate X.509, atât expeditorul, cât și destinatarul vor avea propriile chei publice și private, precum și certificate X.509 care conțin cheia publică. Apoi schimbă cumva certificatele X.509, folosind cheile publice ale celuilalt pentru a cripta datele pe care le trimit și propria cheie privată pentru a decripta datele pe care le primesc.

![În loc să împărtășești o cheie publică, poți împărtăși un certificat. Utilizatorul certificatului poate verifica că provine de la tine verificând cu autoritatea de certificare care l-a semnat.](../../../../../translated_images/ro/send-message-certificate.9cc576ac1e46b76e.webp)

Un mare avantaj al utilizării certificatelor X.509 este că acestea pot fi împărtășite între dispozitive. Poți crea un certificat, să-l încarci în IoT Hub și să-l folosești pentru toate dispozitivele tale. Fiecare dispozitiv trebuie doar să cunoască cheia privată pentru a decripta mesajele pe care le primește de la IoT Hub.

Certificatul utilizat de dispozitivul tău pentru a cripta mesajele pe care le trimite către IoT Hub este publicat de Microsoft. Este același certificat pe care îl folosesc multe servicii Azure și este uneori integrat în SDK-uri.

> 💁 Amintește-ți, o cheie publică este exact asta - publică. Cheia publică Azure poate fi folosită doar pentru a cripta datele trimise către Azure, nu pentru a le decripta, așa că poate fi împărtășită oriunde, inclusiv în codul sursă. De exemplu, o poți vedea în [codul sursă Azure IoT C SDK](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Există o mulțime de termeni tehnici asociați cu certificatele X.509. Poți citi definițiile unor termeni pe care s-ar putea să-i întâlnești în [Ghidul simplificat al jargonului certificatelor X.509](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Generarea și utilizarea unui certificat X.509

Pașii pentru generarea unui certificat X.509 sunt:

1. Creează o pereche de chei publice/private. Unul dintre cele mai utilizate algoritme pentru generarea unei perechi de chei publice/private se numește [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Trimite cheia publică cu datele asociate pentru semnare, fie de către un CA, fie prin semnare proprie.

CLI-ul Azure are comenzi pentru a crea o nouă identitate de dispozitiv în IoT Hub și pentru a genera automat perechea de chei publice/private și a crea un certificat semnat de sine.

> 💁 Dacă vrei să vezi pașii în detaliu, în loc să folosești CLI-ul Azure, îi poți găsi în [tutorialul Microsoft IoT Hub despre utilizarea OpenSSL pentru a crea certificate semnate de sine](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Sarcină - creează o identitate de dispozitiv folosind un certificat X.509

1. Rulează următoarea comandă pentru a înregistra noua identitate de dispozitiv, generând automat cheile și certificatele:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Înlocuiește `<hub_name>` cu numele pe care l-ai folosit pentru IoT Hub.

    Aceasta va crea un dispozitiv cu un ID de `soil-moisture-sensor-x509` pentru a-l distinge de identitatea dispozitivului pe care l-ai creat în lecția anterioară. Această comandă va crea, de asemenea, 2 fișiere în directorul curent:

    * `soil-moisture-sensor-x509-key.pem` - acest fișier conține cheia privată pentru dispozitiv.
    * `soil-moisture-sensor-x509-cert.pem` - acesta este fișierul certificatului X.509 pentru dispozitiv.

    Păstrează aceste fișiere în siguranță! Fișierul cu cheia privată nu ar trebui să fie verificat în controlul sursei publice.

### Sarcină - folosește certificatul X.509 în codul dispozitivului tău

Parcurge ghidul relevant pentru a conecta dispozitivul IoT la cloud folosind certificatul X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Computer cu o singură placă - Raspberry Pi/Dispozitiv IoT virtual](single-board-computer-x509.md)

---

## 🚀 Provocare

Există mai multe moduri de a crea, gestiona și șterge servicii Azure, cum ar fi Grupuri de Resurse și IoT Hubs. Un mod este [Portalul Azure](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - o interfață web care îți oferă un GUI pentru a gestiona serviciile Azure.

Accesează [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) și investighează portalul. Vezi dacă poți crea un IoT Hub folosind portalul, apoi șterge-l.

**Sugestie** - când creezi servicii prin portal, nu trebuie să creezi un Grup de Resurse în prealabil, unul poate fi creat atunci când creezi serviciul. Asigură-te că îl ștergi când ai terminat!

Poți găsi o mulțime de documentație, tutoriale și ghiduri despre Portalul Azure în [documentația portalului Azure](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Test de evaluare post-lectură

[Test de evaluare post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Recapitulare și studiu individual

* Citește despre istoria criptografiei pe [pagina Istoria criptografiei de pe Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Citește despre certificatele X.509 pe [pagina X.509 de pe Wikipedia](https://wikipedia.org/wiki/X.509).

## Temă

[Construiește un nou dispozitiv IoT](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.