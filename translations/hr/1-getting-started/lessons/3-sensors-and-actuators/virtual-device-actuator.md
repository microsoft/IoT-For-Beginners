<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T14:12:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "hr"
}
-->
# Izradite noćno svjetlo - Virtualni IoT hardver

U ovom dijelu lekcije, dodati ćete LED na svoj virtualni IoT uređaj i koristiti ga za stvaranje noćnog svjetla.

## Virtualni hardver

Noćno svjetlo zahtijeva jedan aktuator, kreiran u CounterFit aplikaciji.

Aktuator je **LED**. Na fizičkom IoT uređaju, to bi bila [svjetleća dioda](https://wikipedia.org/wiki/Light-emitting_diode) koja emitira svjetlo kada kroz nju teče struja. Ovo je digitalni aktuator koji ima 2 stanja, uključeno i isključeno. Slanje vrijednosti 1 uključuje LED, a vrijednost 0 ga isključuje.

Logika noćnog svjetla u pseudo-kodu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Dodavanje aktuatora u CounterFit

Za korištenje virtualnog LED-a, potrebno ga je dodati u CounterFit aplikaciju.

#### Zadatak - dodajte aktuator u CounterFit

Dodajte LED u CounterFit aplikaciju.

1. Provjerite je li CounterFit web aplikacija pokrenuta iz prethodnog dijela zadatka. Ako nije, pokrenite je i ponovno dodajte senzor svjetla.

1. Kreirajte LED:

    1. U okviru *Create actuator* u *Actuator* panelu, otvorite padajući izbornik *Actuator type* i odaberite *LED*.

    1. Postavite *Pin* na *5*.

    1. Kliknite na gumb **Add** za kreiranje LED-a na pinu 5.

    ![Postavke LED-a](../../../../../translated_images/hr/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED će biti kreiran i pojavit će se na popisu aktuatora.

    ![Kreirani LED](../../../../../translated_images/hr/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Nakon što je LED kreiran, možete promijeniti boju koristeći *Color* alat za odabir boje. Kliknite na gumb **Set** za promjenu boje nakon što je odabrana.

### Programiranje noćnog svjetla

Noćno svjetlo sada se može programirati koristeći CounterFit senzor svjetla i LED.

#### Zadatak - programirajte noćno svjetlo

Programirajte noćno svjetlo.

1. Otvorite projekt noćnog svjetla u VS Code koji ste kreirali u prethodnom dijelu zadatka. Ako je potrebno, zatvorite i ponovno kreirajte terminal kako biste osigurali da radi unutar virtualnog okruženja.

1. Otvorite datoteku `app.py`.

1. Dodajte sljedeći kod u datoteku `app.py` za uvoz potrebne biblioteke. Ovo treba dodati na vrh, ispod ostalih `import` linija.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Izjava `from counterfit_shims_grove.grove_led import GroveLed` uvozi `GroveLed` iz CounterFit Grove shim Python biblioteka. Ova biblioteka sadrži kod za interakciju s LED-om kreiranim u CounterFit aplikaciji.

1. Dodajte sljedeći kod nakon deklaracije `light_sensor` za kreiranje instance klase koja upravlja LED-om:

    ```python
    led = GroveLed(5)
    ```

    Linija `led = GroveLed(5)` kreira instancu klase `GroveLed` povezujući se na pin **5** - CounterFit Grove pin na koji je LED povezan.

1. Dodajte provjeru unutar `while` petlje, prije `time.sleep`, za provjeru razine svjetla i uključivanje ili isključivanje LED-a:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ovaj kod provjerava vrijednost `light`. Ako je manja od 300, poziva metodu `on` klase `GroveLed` koja šalje digitalnu vrijednost 1 LED-u, uključujući ga. Ako je vrijednost svjetla veća ili jednaka 300, poziva metodu `off`, šaljući digitalnu vrijednost 0 LED-u, isključujući ga.

    > 💁 Ovaj kod treba biti uvučen na istu razinu kao linija `print('Light level:', light)` kako bi bio unutar `while` petlje!

1. Iz terminala u VS Code-u, pokrenite sljedeće za pokretanje vaše Python aplikacije:

    ```sh
    python3 app.py
    ```

    Vrijednosti svjetla će se ispisivati na konzolu.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Promijenite *Value* ili postavke *Random* kako biste varirali razinu svjetla iznad i ispod 300. LED će se uključivati i isključivati.

![LED u CounterFit aplikaciji se uključuje i isključuje kako se razina svjetla mijenja](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Ovaj kod možete pronaći u mapi [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Vaš program za noćno svjetlo je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.