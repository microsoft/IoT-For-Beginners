<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T10:40:00+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "ro"
}
-->
# Adăugarea unui senzor - Wio Terminal

În această parte a lecției, vei folosi senzorul de lumină de pe Wio Terminal.

## Hardware

Senzorul pentru această lecție este un **senzor de lumină** care folosește un [fotodiod](https://wikipedia.org/wiki/Photodiode) pentru a converti lumina într-un semnal electric. Acesta este un senzor analogic care trimite o valoare întreagă de la 0 la 1.023, indicând o cantitate relativă de lumină care nu corespunde niciunei unități standard de măsură, cum ar fi [lux](https://wikipedia.org/wiki/Lux).

Senzorul de lumină este integrat în Wio Terminal și este vizibil prin fereastra de plastic transparentă de pe spate.

![Senzorul de lumină de pe spatele Wio Terminal](../../../../../translated_images/ro/wio-light-sensor.b1f529f3c95f5165.png)

## Programează senzorul de lumină

Dispozitivul poate fi acum programat pentru a folosi senzorul de lumină integrat.

### Sarcină

Programează dispozitivul.

1. Deschide proiectul de nightlight în VS Code pe care l-ai creat în partea anterioară a acestui exercițiu.

1. Adaugă următoarea linie la sfârșitul funcției `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Această linie configurează pinii folosiți pentru a comunica cu hardware-ul senzorului.

    Pinul `WIO_LIGHT` este numărul pinului GPIO conectat la senzorul de lumină integrat. Acest pin este setat la `INPUT`, ceea ce înseamnă că este conectat la un senzor și datele vor fi citite de pe pin.

1. Șterge conținutul funcției `loop`.

1. Adaugă următorul cod în funcția `loop`, care acum este goală.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Acest cod citește o valoare analogică de la pinul `WIO_LIGHT`. Aceasta citește o valoare între 0 și 1.023 de la senzorul de lumină integrat. Valoarea este apoi trimisă către portul serial, astfel încât să o poți citi în Serial Monitor atunci când acest cod rulează. `Serial.print` scrie textul fără o linie nouă la sfârșit, astfel încât fiecare linie va începe cu `Light value:` și se va termina cu valoarea reală a luminii.

1. Adaugă o mică întârziere de o secundă (1.000ms) la sfârșitul funcției `loop`, deoarece nivelurile de lumină nu trebuie verificate continuu. O întârziere reduce consumul de energie al dispozitivului.

    ```cpp
    delay(1000);
    ```

1. Reconectează Wio Terminal la computerul tău și încarcă noul cod, așa cum ai făcut înainte.

1. Conectează Serial Monitor. Valorile luminii vor fi afișate în terminal. Acoperă și descoperă senzorul de lumină de pe spatele Wio Terminal, iar valorile se vor schimba.

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

> 💁 Poți găsi acest cod în folderul [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Adăugarea unui senzor la programul tău de nightlight a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.