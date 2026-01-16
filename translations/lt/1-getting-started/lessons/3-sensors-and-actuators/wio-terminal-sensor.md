<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T20:10:57+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "lt"
}
-->
# Pridėkite jutiklį - Wio Terminal

Šioje pamokos dalyje naudosite šviesos jutiklį, esantį jūsų Wio Terminal įrenginyje.

## Aparatinė įranga

Šios pamokos jutiklis yra **šviesos jutiklis**, kuris naudoja [fotodiodą](https://wikipedia.org/wiki/Photodiode), kad šviesą paverstų elektriniu signalu. Tai yra analoginis jutiklis, kuris siunčia sveikojo skaičiaus reikšmę nuo 0 iki 1 023, nurodydamas santykinį šviesos kiekį, kuris nėra susietas su jokiu standartiniu matavimo vienetu, pavyzdžiui, [liuksais](https://wikipedia.org/wiki/Lux).

Šviesos jutiklis yra integruotas į Wio Terminal ir matomas per skaidrų plastikinį langelį įrenginio gale.

![Šviesos jutiklis Wio Terminal gale](../../../../../translated_images/lt/wio-light-sensor.b1f529f3c95f5165.png)

## Užprogramuokite šviesos jutiklį

Dabar įrenginį galima užprogramuoti naudoti integruotą šviesos jutiklį.

### Užduotis

Užprogramuokite įrenginį.

1. Atidarykite naktinės lemputės projektą VS Code programoje, kurį sukūrėte ankstesnėje šios užduoties dalyje.

1. Pridėkite šią eilutę į `setup` funkcijos apačią:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ši eilutė konfigūruoja kaiščius, naudojamus bendrauti su jutiklio aparatine įranga.

    `WIO_LIGHT` kaištis yra GPIO kaiščio numeris, prijungtas prie integruoto šviesos jutiklio. Šis kaištis nustatytas kaip `INPUT`, tai reiškia, kad jis jungiasi prie jutiklio ir duomenys bus skaitomi iš šio kaiščio.

1. Ištrinkite `loop` funkcijos turinį.

1. Pridėkite šį kodą į dabar tuščią `loop` funkciją.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Šis kodas nuskaito analoginę reikšmę iš `WIO_LIGHT` kaiščio. Tai nuskaito reikšmę nuo 0 iki 1 023 iš integruoto šviesos jutiklio. Ši reikšmė tada siunčiama į serijinį prievadą, kad galėtumėte ją matyti Serijiniame monitoriuje, kai šis kodas veikia. `Serial.print` rašo tekstą be naujos eilutės pabaigoje, todėl kiekviena eilutė prasidės su `Light value:` ir baigsis faktine šviesos reikšme.

1. Pridėkite nedidelį vienos sekundės (1 000 ms) uždelsimą `loop` pabaigoje, nes šviesos lygiai neturi būti tikrinami nuolat. Uždelsimas sumažina įrenginio energijos suvartojimą.

    ```cpp
    delay(1000);
    ```

1. Prijunkite Wio Terminal prie savo kompiuterio ir įkelkite naują kodą, kaip darėte anksčiau.

1. Prijunkite Serijinį monitorių. Šviesos reikšmės bus išvedamos į terminalą. Uždenkite ir atidenkite šviesos jutiklį Wio Terminal gale, ir reikšmės keisis.

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

> 💁 Šį kodą galite rasti [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) aplanke.

😀 Jutiklio pridėjimas prie jūsų naktinės lemputės programos buvo sėkmingas!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.