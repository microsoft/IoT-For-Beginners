<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T14:42:35+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "sr"
}
-->
# Мерење влаге у земљишту - Wio Terminal

У овом делу лекције, додаћете капацитивни сензор влаге у земљишту на ваш Wio Terminal и читати вредности са њега.

## Хардвер

Wio Terminal захтева капацитивни сензор влаге у земљишту.

Сензор који ћете користити је [Капацитивни сензор влаге у земљишту](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), који мери влагу у земљишту детектовањем капацитивности земљишта, својства које се мења са променом влаге у земљишту. Како се влага у земљишту повећава, напон опада.

Ово је аналогни сензор, тако да се повезује на аналогне пинове на Wio Terminal-у, користећи уграђени ADC за креирање вредности од 0 до 1.023.

### Повежите сензор влаге у земљишту

Grove сензор влаге у земљишту може се повезати на конфигурабилни аналогни/дигитални порт Wio Terminal-а.

#### Задатак - повежите сензор влаге у земљишту

Повежите сензор влаге у земљишту.

![Grove сензор влаге у земљишту](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.sr.png)

1. Уметните један крај Grove кабла у утичницу на сензору влаге у земљишту. Кабл ће ући само у једном смеру.

1. Са Wio Terminal-ом искљученим из рачунара или другог извора напајања, повежите други крај Grove кабла у десну Grove утичницу на Wio Terminal-у када гледате у екран. Ово је утичница најудаљенија од дугмета за напајање.

![Grove сензор влаге у земљишту повезан на десну утичницу](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb7497662251b29038ee0e57a4c8b9d071feb996c3b0d7f65aaf.sr.png)

1. Уметните сензор влаге у земљиште. Има ознаку "највиша позиција" - белу линију преко сензора. Уметните сензор до те линије, али не преко ње.

![Grove сензор влаге у земљишту у земљишту](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e960f8c51ee64b02ee59b32c8c717e3515a2c945f33e614e403.sr.png)

1. Сада можете повезати Wio Terminal са вашим рачунаром.

## Програмирање сензора влаге у земљишту

Wio Terminal сада може бити програмиран за коришћење повезаног сензора влаге у земљишту.

### Задатак - програмирајте сензор влаге у земљишту

Програмирајте уређај.

1. Направите потпуно нови Wio Terminal пројекат користећи PlatformIO. Назовите овај пројекат `soil-moisture-sensor`. Додајте код у функцију `setup` за конфигурисање серијског порта.

    > ⚠️ Можете се позвати на [упутства за креирање PlatformIO пројекта у пројекту 1, лекција 1 ако је потребно](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Не постоји библиотека за овај сензор, уместо тога можете читати са аналогног пина користећи уграђену Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) функцију. Почните конфигурисањем аналогног пина за улаз тако да се вредности могу читати са њега додавањем следећег у функцију `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Ово подешава пин `A0`, комбиновани аналогни/дигитални пин, као улазни пин са којег се може читати напон.

1. Додајте следеће у функцију `loop` за читање напона са овог пина:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Испод овог кода, додајте следећи код за исписивање вредности на серијски порт:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. На крају, додајте кашњење од 10 секунди на крају:

    ```cpp
    delay(10000);
    ```

1. Компилирајте и отпремите код на Wio Terminal.

    > ⚠️ Можете се позвати на [упутства за креирање PlatformIO пројекта у пројекту 1, лекција 1 ако је потребно](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Када се код отпреми, можете пратити влагу у земљишту користећи серијски монитор. Додајте мало воде у земљиште или извадите сензор из земљишта и посматрајте промену вредности.

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

    У примеру излазних података изнад, можете видети како напон опада када се дода вода.

> 💁 Овај код можете пронаћи у [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) фасцикли.

😀 Ваш програм за сензор влаге у земљишту је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да превод буде тачан, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.