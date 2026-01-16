<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-28T14:13:26+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "hr"
}
-->
# Izradite noćno svjetlo - Raspberry Pi

U ovom dijelu lekcije dodati ćete LED na svoj Raspberry Pi i koristiti ga za stvaranje noćnog svjetla.

## Hardver

Noćnom svjetlu sada je potreban aktuator.

Aktuator je **LED**, [svjetleća dioda](https://wikipedia.org/wiki/Light-emitting_diode) koja emitira svjetlost kada kroz nju teče struja. Ovo je digitalni aktuator koji ima dva stanja, uključeno i isključeno. Slanjem vrijednosti 1 LED se uključuje, a vrijednosti 0 ga isključuje. LED je vanjski Grove aktuator i mora biti povezan na Grove Base hat na Raspberry Pi-u.

Logika noćnog svjetla u pseudo-kodu je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Povežite LED

Grove LED dolazi kao modul s izborom LED-ova, omogućujući vam da odaberete boju.

#### Zadatak - povežite LED

Povežite LED.

![Grove LED](../../../../../translated_images/hr/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Odaberite svoj omiljeni LED i umetnite nogice u dvije rupe na LED modulu.

    LED-ovi su svjetleće diode, a diode su elektronički uređaji koji mogu provoditi struju samo u jednom smjeru. To znači da LED mora biti povezan na ispravan način, inače neće raditi.

    Jedna od nogica LED-a je pozitivni pin, a druga je negativni pin. LED nije savršeno okrugao i malo je spljošten na jednoj strani. Malo spljoštena strana je negativni pin. Kada povezujete LED s modulom, pazite da je pin uz zaobljenu stranu povezan s utičnicom označenom **+** na vanjskoj strani modula, a spljoštena strana povezana s utičnicom bliže sredini modula.

1. LED modul ima okretni gumb koji vam omogućuje kontrolu svjetline. Za početak ga potpuno pojačajte okretanjem u smjeru suprotnom od kazaljke na satu koliko god ide pomoću malog odvijača s križnom glavom.

1. Umetnite jedan kraj Grove kabela u utičnicu na LED modulu. Kabel će ući samo u jednom smjeru.

1. Dok je Raspberry Pi isključen, povežite drugi kraj Grove kabela s digitalnom utičnicom označenom **D5** na Grove Base hatu pričvršćenom na Pi. Ova utičnica je druga s lijeva, u redu utičnica pored GPIO pinova.

![Grove LED povezan s utičnicom D5](../../../../../translated_images/hr/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Programirajte noćno svjetlo

Noćno svjetlo sada se može programirati pomoću Grove senzora svjetla i Grove LED-a.

### Zadatak - programirajte noćno svjetlo

Programirajte noćno svjetlo.

1. Uključite Pi i pričekajte da se pokrene.

1. Otvorite projekt noćnog svjetla u VS Code koji ste kreirali u prethodnom dijelu zadatka, bilo da ga pokrećete izravno na Pi-u ili se povezujete pomoću Remote SSH ekstenzije.

1. Dodajte sljedeći kod u datoteku `app.py` kako biste uvezli potrebnu biblioteku. Ovo treba dodati na vrh, ispod ostalih `import` linija.

    ```python
    from grove.grove_led import GroveLed
    ```

    Izjava `from grove.grove_led import GroveLed` uvozi `GroveLed` iz Grove Python biblioteka. Ova biblioteka sadrži kod za interakciju s Grove LED-om.

1. Dodajte sljedeći kod nakon deklaracije `light_sensor` kako biste kreirali instancu klase koja upravlja LED-om:

    ```python
    led = GroveLed(5)
    ```

    Linija `led = GroveLed(5)` kreira instancu klase `GroveLed` povezujući se s pinom **D5** - digitalnim Grove pinom na koji je LED povezan.

    > 💁 Sve utičnice imaju jedinstvene brojeve pinova. Pinovi 0, 2, 4 i 6 su analogni pinovi, a pinovi 5, 16, 18, 22, 24 i 26 su digitalni pinovi.

1. Dodajte provjeru unutar `while` petlje, prije `time.sleep`, kako biste provjerili razinu svjetla i uključili ili isključili LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ovaj kod provjerava vrijednost `light`. Ako je manja od 300, poziva metodu `on` klase `GroveLed` koja šalje digitalnu vrijednost 1 LED-u, uključujući ga. Ako je vrijednost svjetla veća ili jednaka 300, poziva metodu `off`, šaljući digitalnu vrijednost 0 LED-u, isključujući ga.

    > 💁 Ovaj kod treba biti uvučen na istu razinu kao linija `print('Light level:', light)` kako bi bio unutar while petlje!

    > 💁 Kada šaljete digitalne vrijednosti aktuatorima, vrijednost 0 je 0V, a vrijednost 1 je maksimalni napon za uređaj. Za Raspberry Pi s Grove senzorima i aktuatorima, napon vrijednosti 1 je 3.3V.

1. Iz terminala u VS Code-u pokrenite sljedeće kako biste pokrenuli svoju Python aplikaciju:

    ```sh
    python3 app.py
    ```

    Vrijednosti svjetla će se ispisivati na konzolu.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Pokrijte i otkrijte senzor svjetla. Primijetite kako će se LED upaliti ako je razina svjetla 300 ili manje, i ugasiti kada je razina svjetla veća od 300.

    > 💁 Ako se LED ne upali, provjerite je li povezan na ispravan način i je li okretni gumb postavljen na maksimalnu svjetlinu.

![LED povezan s Pi-jem koji se pali i gasi kako se razina svjetla mijenja](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Ovaj kod možete pronaći u mapi [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Vaš program za noćno svjetlo je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakva pogrešna tumačenja ili nesporazume koji mogu proizaći iz korištenja ovog prijevoda.