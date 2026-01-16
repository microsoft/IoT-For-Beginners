<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T20:24:00+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "lt"
}
-->
# Matuokite dirvožemio drėgmę - Wio Terminal

Šioje pamokos dalyje pridėsite talpinį dirvožemio drėgmės jutiklį prie savo Wio Terminal ir nuskaitysite jo vertes.

## Aparatūra

Wio Terminal reikalingas talpinis dirvožemio drėgmės jutiklis.

Jutiklis, kurį naudosite, yra [Talpinis dirvožemio drėgmės jutiklis](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), kuris matuoja dirvožemio drėgmę aptikdamas dirvožemio talpą – savybę, kuri keičiasi keičiantis dirvožemio drėgmei. Didėjant dirvožemio drėgmei, įtampa mažėja.

Tai yra analoginis jutiklis, todėl jis jungiamas prie analoginių Wio Terminal pinų, naudojant integruotą ADC, kuris sukuria vertę nuo 0 iki 1,023.

### Prijunkite dirvožemio drėgmės jutiklį

Grove dirvožemio drėgmės jutiklis gali būti prijungtas prie Wio Terminal konfigūruojamo analoginio/skaitmeninio prievado.

#### Užduotis - prijunkite dirvožemio drėgmės jutiklį

Prijunkite dirvožemio drėgmės jutiklį.

![Grove dirvožemio drėgmės jutiklis](../../../../../translated_images/lt/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Įstatykite vieną Grove kabelio galą į dirvožemio drėgmės jutiklio lizdą. Jis įsistatys tik viena kryptimi.

1. Kai Wio Terminal atjungtas nuo kompiuterio ar kito maitinimo šaltinio, prijunkite kitą Grove kabelio galą prie dešiniojo Grove lizdo Wio Terminal, žiūrint į ekraną. Tai yra lizdas, esantis toliausiai nuo maitinimo mygtuko.

![Grove dirvožemio drėgmės jutiklis prijungtas prie dešiniojo lizdo](../../../../../translated_images/lt/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Įstatykite dirvožemio drėgmės jutiklį į dirvožemį. Jutiklis turi „aukščiausios padėties liniją“ – baltą liniją per jutiklį. Įstatykite jutiklį iki šios linijos, bet ne per ją.

![Grove dirvožemio drėgmės jutiklis dirvožemyje](../../../../../translated_images/lt/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Dabar galite prijungti Wio Terminal prie savo kompiuterio.

## Programuokite dirvožemio drėgmės jutiklį

Dabar Wio Terminal galima programuoti naudoti prijungtą dirvožemio drėgmės jutiklį.

### Užduotis - programuokite dirvožemio drėgmės jutiklį

Programuokite įrenginį.

1. Sukurkite visiškai naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `soil-moisture-sensor`. Pridėkite kodą į `setup` funkciją, kad sukonfigūruotumėte nuoseklųjį prievadą.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti PlatformIO projektą 1 projekte, 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Šiam jutikliui nėra bibliotekos, vietoj to galite nuskaityti analoginio pin'o vertę naudodami įmontuotą Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) funkciją. Pradėkite konfigūruodami analoginį pin'ą kaip įvestį, kad iš jo būtų galima nuskaityti vertes, pridėdami šį kodą į `setup` funkciją.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Tai nustato `A0` pin'ą, kombinuotą analoginį/skaitmeninį pin'ą, kaip įvesties pin'ą, iš kurio galima nuskaityti įtampą.

1. Pridėkite šį kodą į `loop` funkciją, kad nuskaitytumėte įtampą iš šio pin'o:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Po šio kodo pridėkite šį kodą, kad išvestumėte vertę į nuoseklųjį prievadą:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Galiausiai pridėkite 10 sekundžių vėlavimą pabaigoje:

    ```cpp
    delay(10000);
    ```

1. Sukurkite ir įkelkite kodą į Wio Terminal.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti PlatformIO projektą 1 projekte, 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Įkėlus kodą, galite stebėti dirvožemio drėgmę naudodami nuoseklųjį monitorių. Įpilkite vandens į dirvožemį arba ištraukite jutiklį iš dirvožemio ir stebėkite, kaip keičiasi vertė.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Pateiktame pavyzdiniame išvestyje matote, kaip įtampa mažėja, kai į dirvožemį pilamas vanduo.

> 💁 Šį kodą galite rasti [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) aplanke.

😀 Jūsų dirvožemio drėgmės jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.