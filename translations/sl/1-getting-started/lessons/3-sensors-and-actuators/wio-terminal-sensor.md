<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T14:18:21+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "sl"
}
-->
# Dodajanje senzorja - Wio Terminal

V tem delu lekcije boste uporabili svetlobni senzor na vašem Wio Terminalu.

## Strojna oprema

Senzor za to lekcijo je **svetlobni senzor**, ki uporablja [fotodiodo](https://wikipedia.org/wiki/Photodiode) za pretvorbo svetlobe v električni signal. Gre za analogni senzor, ki pošilja celoštevilsko vrednost od 0 do 1.023, kar označuje relativno količino svetlobe, ki ni povezana z nobeno standardno mersko enoto, kot je [lux](https://wikipedia.org/wiki/Lux).

Svetlobni senzor je vgrajen v Wio Terminal in je viden skozi prozorno plastično okno na zadnji strani.

![Svetlobni senzor na zadnji strani Wio Terminala](../../../../../translated_images/sl/wio-light-sensor.b1f529f3c95f5165.png)

## Programiranje svetlobnega senzorja

Napravo je zdaj mogoče programirati za uporabo vgrajenega svetlobnega senzorja.

### Naloga

Programirajte napravo.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu naloge.

1. Dodajte naslednjo vrstico na dno funkcije `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ta vrstica konfigurira pine, ki se uporabljajo za komunikacijo s strojno opremo senzorja.

    Pin `WIO_LIGHT` je številka GPIO pina, povezanega z vgrajenim svetlobnim senzorjem. Ta pin je nastavljen na `INPUT`, kar pomeni, da je povezan s senzorjem in podatki bodo prebrani s pina.

1. Izbrišite vsebino funkcije `loop`.

1. Dodajte naslednjo kodo v zdaj prazno funkcijo `loop`.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ta koda prebere analogno vrednost s pina `WIO_LIGHT`. Prebere vrednost od 0 do 1.023 z vgrajenega svetlobnega senzorja. Ta vrednost se nato pošlje na serijski port, da jo lahko preberete v Serial Monitorju, ko ta koda teče. `Serial.print` zapiše besedilo brez nove vrstice na koncu, tako da se vsaka vrstica začne z `Light value:` in konča z dejansko vrednostjo svetlobe.

1. Na konec funkcije `loop` dodajte majhno zakasnitev ene sekunde (1.000 ms), saj ni potrebno neprekinjeno preverjati ravni svetlobe. Zakasnitev zmanjša porabo energije naprave.

    ```cpp
    delay(1000);
    ```

1. Ponovno povežite Wio Terminal z računalnikom in naložite novo kodo, kot ste to storili prej.

1. Povežite Serial Monitor. Vrednosti svetlobe bodo prikazane v terminalu. Pokrijte in odkrijte svetlobni senzor na zadnji strani Wio Terminala, in vrednosti se bodo spreminjale.

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

> 💁 To kodo lahko najdete v mapi [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Dodajanje senzorja v vaš program nočne lučke je bilo uspešno!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.