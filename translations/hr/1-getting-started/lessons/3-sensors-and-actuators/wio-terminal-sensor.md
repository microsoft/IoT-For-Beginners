<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T14:18:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "hr"
}
-->
# Dodavanje senzora - Wio Terminal

U ovom dijelu lekcije koristit ćete senzor svjetla na svom Wio Terminalu.

## Hardver

Senzor za ovu lekciju je **senzor svjetla** koji koristi [fotodiodu](https://wikipedia.org/wiki/Photodiode) za pretvaranje svjetla u električni signal. Ovo je analogni senzor koji šalje cijeli broj od 0 do 1.023, što označava relativnu količinu svjetla koja se ne odnosi na standardnu mjeru poput [luxa](https://wikipedia.org/wiki/Lux).

Senzor svjetla ugrađen je u Wio Terminal i vidljiv je kroz prozirni plastični prozor na stražnjoj strani.

![Senzor svjetla na stražnjoj strani Wio Terminala](../../../../../translated_images/hr/wio-light-sensor.b1f529f3c95f5165.webp)

## Programiranje senzora svjetla

Uređaj sada može biti programiran za korištenje ugrađenog senzora svjetla.

### Zadatak

Programirajte uređaj.

1. Otvorite projekt noćnog svjetla u VS Codeu koji ste kreirali u prethodnom dijelu ovog zadatka.

1. Dodajte sljedeći redak na dno funkcije `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ovaj redak konfigurira pinove koji se koriste za komunikaciju s hardverom senzora.

    Pin `WIO_LIGHT` je broj GPIO pina povezanog s ugrađenim senzorom svjetla. Ovaj pin je postavljen na `INPUT`, što znači da je povezan sa senzorom i podaci će se čitati s tog pina.

1. Obrišite sadržaj funkcije `loop`.

1. Dodajte sljedeći kod u sada praznu funkciju `loop`.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ovaj kod čita analognu vrijednost s pina `WIO_LIGHT`. Ova vrijednost je u rasponu od 0 do 1.023 i dolazi s ugrađenog senzora svjetla. Vrijednost se zatim šalje na serijski port kako biste je mogli pročitati u Serial Monitoru dok ovaj kod radi. `Serial.print` ispisuje tekst bez novog retka na kraju, tako da će svaki redak započeti s `Light value:` i završiti stvarnom vrijednošću svjetla.

1. Dodajte kratku pauzu od jedne sekunde (1.000 ms) na kraj funkcije `loop`, jer razine svjetla nije potrebno provjeravati kontinuirano. Pauza smanjuje potrošnju energije uređaja.

    ```cpp
    delay(1000);
    ```

1. Ponovno povežite Wio Terminal s računalom i učitajte novi kod kao što ste to učinili ranije.

1. Povežite se s Serial Monitorom. Vrijednosti svjetla će se ispisivati na terminalu. Pokrijte i otkrijte senzor svjetla na stražnjoj strani Wio Terminala i vrijednosti će se mijenjati.

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

> 💁 Ovaj kod možete pronaći u mapi [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Dodavanje senzora vašem programu za noćno svjetlo bilo je uspješno!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.