<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-28T14:15:29+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "hr"
}
-->
# Napravite noćno svjetlo - Wio Terminal

U ovom dijelu lekcije, dodat ćete LED na svoj Wio Terminal i koristiti ga za izradu noćnog svjetla.

## Hardver

Noćnom svjetlu sada je potreban aktuator.

Aktuator je **LED**, [svjetleća dioda](https://wikipedia.org/wiki/Light-emitting_diode) koja emitira svjetlost kada kroz nju prolazi struja. Ovo je digitalni aktuator koji ima dva stanja: uključeno i isključeno. Slanje vrijednosti 1 uključuje LED, a vrijednost 0 ga isključuje. Ovo je vanjski Grove aktuator i treba ga spojiti na Wio Terminal.

Logika noćnog svjetla u pseudo-kodu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Spojite LED

Grove LED dolazi kao modul s izborom LED-ova, omogućujući vam da odaberete boju.

#### Zadatak - spojite LED

Spojite LED.

![Grove LED](../../../../../translated_images/hr/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Odaberite svoj omiljeni LED i umetnite njegove nožice u dvije rupe na LED modulu.

    LED-ovi su svjetleće diode, a diode su elektronički uređaji koji mogu provoditi struju samo u jednom smjeru. To znači da LED mora biti pravilno spojen, inače neće raditi.

    Jedna od nožica LED-a je pozitivni pin, a druga je negativni pin. LED nije savršeno okrugao i malo je spljošten na jednoj strani. Ta spljoštena strana je negativni pin. Kada spajate LED na modul, provjerite je li pin na zaobljenoj strani spojen na utičnicu označenu **+** na vanjskoj strani modula, a spljoštena strana na utičnicu bliže sredini modula.

1. LED modul ima okretni gumb koji vam omogućuje kontrolu svjetline. Za početak ga okrenite do kraja u smjeru suprotnom od kazaljke na satu pomoću malog križnog odvijača.

1. Umetnite jedan kraj Grove kabela u utičnicu na LED modulu. Kabel će ući samo u jednom smjeru.

1. Dok je Wio Terminal isključen iz računala ili drugog izvora napajanja, spojite drugi kraj Grove kabela na desnu Grove utičnicu na Wio Terminalu gledajući prema ekranu. To je utičnica najudaljenija od gumba za napajanje.

    > 💁 Desna Grove utičnica može se koristiti s analognim ili digitalnim senzorima i aktuatorima. Lijeva utičnica je samo za I2C i digitalne senzore i aktuatore. O tome će biti riječi u kasnijoj lekciji.

![Grove LED spojen na desnu utičnicu](../../../../../translated_images/hr/wio-led.265a1897e72d7f21.webp)

## Programirajte noćno svjetlo

Noćno svjetlo sada se može programirati koristeći ugrađeni senzor svjetla i Grove LED.

### Zadatak - programirajte noćno svjetlo

Programirajte noćno svjetlo.

1. Otvorite projekt noćnog svjetla u VS Code koji ste kreirali u prethodnom dijelu ovog zadatka.

1. Dodajte sljedeći redak na dno funkcije `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ovaj redak konfigurira pin koji se koristi za komunikaciju s LED-om putem Grove porta.

    Pin `D0` je digitalni pin za desnu Grove utičnicu. Ovaj pin je postavljen na `OUTPUT`, što znači da je povezan s aktuatorom i podaci će se slati na pin.

1. Dodajte sljedeći kod neposredno prije `delay` u funkciji `loop`:

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

    Ovaj kod provjerava vrijednost `light`. Ako je manja od 300, šalje vrijednost `HIGH` na digitalni pin `D0`. Ova vrijednost `HIGH` je 1, što uključuje LED. Ako je svjetlost veća ili jednaka 300, šalje se vrijednost `LOW` od 0, što isključuje LED.

    > 💁 Kada šaljete digitalne vrijednosti aktuatorima, vrijednost LOW je 0V, a HIGH je maksimalni napon za uređaj. Za Wio Terminal, HIGH napon je 3.3V.

1. Ponovno spojite Wio Terminal na svoje računalo i prenesite novi kod kao što ste to učinili ranije.

1. Spojite Serial Monitor. Vrijednosti svjetla će se ispisivati na terminal.

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

1. Pokrijte i otkrijte senzor svjetla. Primijetit ćete kako se LED pali ako je razina svjetla 300 ili manja, i gasi kada je razina svjetla veća od 300.

![LED spojen na WIO koji se pali i gasi ovisno o razini svjetla](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Ovaj kod možete pronaći u mapi [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Vaš program za noćno svjetlo je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.