# Controlează un releu - Wio Terminal

În această parte a lecției, vei adăuga un releu la Wio Terminal, pe lângă senzorul de umiditate a solului, și îl vei controla în funcție de nivelul de umiditate a solului.

## Hardware

Wio Terminal are nevoie de un releu.

Releul pe care îl vei folosi este un [releu Grove](https://www.seeedstudio.com/Grove-Relay.html), un releu normal-deschis (ceea ce înseamnă că circuitul de ieșire este deschis sau deconectat atunci când nu este trimis niciun semnal către releu) care poate gestiona circuite de ieșire de până la 250V și 10A.

Acesta este un actuator digital, deci se conectează la pini digitali pe Wio Terminal. Portul combinat analog/digital este deja utilizat cu senzorul de umiditate a solului, așa că acesta se conectează la celălalt port, care este un port combinat I2C și digital.

### Conectează releul

Releul Grove poate fi conectat la portul digital al Wio Terminal.

#### Sarcină

Conectează releul.

![Un releu Grove](../../../../../translated_images/ro/grove-relay.d426958ca210fbd0.webp)

1. Introdu un capăt al unui cablu Grove în soclul releului. Acesta va intra doar într-un singur sens.

1. Cu Wio Terminal deconectat de la computer sau de la altă sursă de alimentare, conectează celălalt capăt al cablului Grove la soclul din stânga al Wio Terminal, așa cum privești ecranul. Lasă senzorul de umiditate a solului conectat la soclul din dreapta.

![Releul Grove conectat la soclul din stânga, iar senzorul de umiditate a solului conectat la soclul din dreapta](../../../../../translated_images/ro/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Introdu senzorul de umiditate a solului în pământ, dacă nu este deja introdus din lecția anterioară.

## Programează releul

Acum, Wio Terminal poate fi programat pentru a utiliza releul atașat.

### Sarcină

Programează dispozitivul.

1. Deschide proiectul `soil-moisture-sensor` din lecția anterioară în VS Code, dacă nu este deja deschis. Vei adăuga la acest proiect.

2. Nu există o bibliotecă pentru acest actuator - este un actuator digital controlat printr-un semnal de nivel înalt sau scăzut. Pentru a-l porni, trimiți un semnal de nivel înalt către pin (3.3V), iar pentru a-l opri trimiți un semnal de nivel scăzut (0V). Poți face acest lucru folosind funcția [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) încorporată în Arduino. Începe prin a adăuga următorul cod la sfârșitul funcției `setup` pentru a configura portul combinat I2C/digital ca pin de ieșire pentru a trimite o tensiune către releu:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` este numărul portului pentru portul combinat I2C/digital.

1. Pentru a testa dacă releul funcționează, adaugă următorul cod în funcția `loop`, sub ultimul `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Codul trimite un semnal de nivel înalt către pinul la care este conectat releul pentru a-l porni, așteaptă 500ms (jumătate de secundă), apoi trimite un semnal de nivel scăzut pentru a opri releul.

1. Construiește și încarcă codul pe Wio Terminal.

1. După ce codul este încărcat, releul se va porni și opri la fiecare 10 secunde, cu o întârziere de jumătate de secundă între pornire și oprire. Vei auzi releul făcând clic când se pornește și când se oprește. Un LED de pe placa Grove se va aprinde când releul este pornit și se va stinge când releul este oprit.

    ![Releul se pornește și se oprește](../../../../../images/relay-turn-on-off.gif)

## Controlează releul în funcție de umiditatea solului

Acum că releul funcționează, acesta poate fi controlat în funcție de citirile senzorului de umiditate a solului.

### Sarcină

Controlează releul.

1. Șterge cele 3 linii de cod pe care le-ai adăugat pentru a testa releul. Înlocuiește-le cu următorul cod:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Acest cod verifică nivelul de umiditate a solului de la senzorul de umiditate a solului. Dacă este peste 450, pornește releul, iar dacă scade sub 450, îl oprește.

    > 💁 Reține că senzorul capacitiv de umiditate a solului citește: cu cât nivelul de umiditate a solului este mai mic, cu atât solul este mai umed și invers.

1. Construiește și încarcă codul pe Wio Terminal.

1. Monitorizează dispozitivul prin intermediul monitorului serial. Vei vedea releul pornindu-se sau oprindu-se în funcție de nivelul de umiditate a solului. Încearcă în sol uscat, apoi adaugă apă.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Poți găsi acest cod în folderul [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Programul tău pentru controlul unui releu în funcție de senzorul de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.