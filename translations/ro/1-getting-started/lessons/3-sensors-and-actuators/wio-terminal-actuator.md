# Construiește o lampă de veghe - Wio Terminal

În această parte a lecției, vei adăuga un LED la Wio Terminal și îl vei folosi pentru a crea o lampă de veghe.

## Hardware

Lampa de veghe are acum nevoie de un actuator.

Actuatorul este un **LED**, o [diodă emițătoare de lumină](https://wikipedia.org/wiki/Light-emitting_diode) care emite lumină atunci când curentul trece prin ea. Acesta este un actuator digital care are 2 stări: pornit și oprit. Trimiterea unei valori de 1 aprinde LED-ul, iar 0 îl stinge. Acesta este un actuator extern Grove și trebuie conectat la Wio Terminal.

Logica lămpii de veghe în pseudo-cod este:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conectează LED-ul

LED-ul Grove vine ca un modul cu o selecție de LED-uri, permițându-ți să alegi culoarea.

#### Sarcină - conectează LED-ul

Conectează LED-ul.

![Un LED Grove](../../../../../translated_images/ro/grove-led.6c853be93f473cf2.webp)

1. Alege LED-ul preferat și inserează picioarele acestuia în cele două găuri de pe modulul LED.

    LED-urile sunt diode emițătoare de lumină, iar diodele sunt dispozitive electronice care pot transporta curent doar într-o singură direcție. Acest lucru înseamnă că LED-ul trebuie conectat corect, altfel nu va funcționa.

    Unul dintre picioarele LED-ului este pinul pozitiv, iar celălalt este pinul negativ. LED-ul nu este perfect rotund și este ușor mai plat pe o parte. Partea ușor mai plată este pinul negativ. Când conectezi LED-ul la modul, asigură-te că pinul de pe partea rotunjită este conectat la soclul marcat **+** pe exteriorul modulului, iar partea mai plată este conectată la soclul mai aproape de mijlocul modulului.

1. Modulul LED are un buton rotativ care îți permite să controlezi luminozitatea. Rotește-l complet în sens invers acelor de ceasornic pentru început, folosind o șurubelniță mică cu cap Phillips.

1. Introdu un capăt al unui cablu Grove în soclul de pe modulul LED. Acesta va intra doar într-un singur mod.

1. Cu Wio Terminal deconectat de la computer sau altă sursă de alimentare, conectează celălalt capăt al cablului Grove la soclul Grove din partea dreaptă a Wio Terminal, așa cum privești ecranul. Acesta este soclul cel mai îndepărtat de butonul de alimentare.

    > 💁 Soclul Grove din partea dreaptă poate fi utilizat cu senzori și actuatori analogici sau digitali. Soclul din partea stângă este pentru senzori și actuatori digitali doar. C

C va fi acoperit într-o lecție ulterioară.

![LED-ul Grove conectat la soclul din partea dreaptă](../../../../../translated_images/ro/wio-led.265a1897e72d7f21.webp)

## Programează lampa de veghe

Lampa de veghe poate fi acum programată folosind senzorul de lumină integrat și LED-ul Grove.

### Sarcină - programează lampa de veghe

Programează lampa de veghe.

1. Deschide proiectul lămpii de veghe în VS Code pe care l-ai creat în partea anterioară a acestui exercițiu.

1. Adaugă următoarea linie la sfârșitul funcției `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Această linie configurează pinul utilizat pentru a comunica cu LED-ul prin portul Grove.

    Pinul `D0` este pinul digital pentru soclul Grove din partea dreaptă. Acest pin este setat la `OUTPUT`, ceea ce înseamnă că se conectează la un actuator și datele vor fi scrise pe pin.

1. Adaugă următorul cod imediat înainte de `delay` în funcția loop:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Acest cod verifică valoarea `light`. Dacă aceasta este mai mică de 300, trimite o valoare `HIGH` către pinul digital `D0`. Această valoare `HIGH` este 1, aprinzând LED-ul. Dacă lumina este mai mare sau egală cu 300, se trimite o valoare `LOW` de 0 către pin, stingând LED-ul.

    > 💁 Când trimiți valori digitale către actuatori, o valoare LOW este 0v, iar o valoare HIGH este tensiunea maximă pentru dispozitiv. Pentru Wio Terminal, tensiunea HIGH este 3.3V.

1. Reconectează Wio Terminal la computerul tău și încarcă noul cod așa cum ai făcut înainte.

1. Conectează Serial Monitor. Valorile luminii vor fi afișate în terminal.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Acoperă și descoperă senzorul de lumină. Observă cum LED-ul se va aprinde dacă nivelul de lumină este 300 sau mai puțin și se va stinge când nivelul de lumină este mai mare de 300.

![LED-ul conectat la WIO se aprinde și se stinge pe măsură ce nivelul de lumină se schimbă](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Poți găsi acest cod în folderul [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Programul tău pentru lampa de veghe a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.