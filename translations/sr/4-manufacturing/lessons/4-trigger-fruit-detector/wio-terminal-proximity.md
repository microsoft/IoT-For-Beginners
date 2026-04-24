# Детектовање близине - Wio Terminal

У овом делу лекције, додаћете сензор близине на ваш Wio Terminal и читати растојање са њега.

## Хардвер

Wio Terminal захтева сензор близине.

Сензор који ћете користити је [Grove Time of Flight сензор растојања](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Овај сензор користи ласерски модул за мерење растојања. Сензор има опсег од 10мм до 2000мм (1цм - 2м) и прилично прецизно ће пријављивати вредности у том опсегу, док ће растојања изнад 1000мм бити пријављена као 8109мм.

Ласерски мерач растојања налази се на задњој страни сензора, супротно од Grove прикључка.

Ово је IC сензор.

### Повежите Time of Flight сензор

Grove Time of Flight сензор може се повезати са Wio Terminal-ом.

#### Задатак - повежите Time of Flight сензор

Повежите Time of Flight сензор.

![Grove Time of Flight сензор](../../../../../translated_images/sr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Уметните један крај Grove кабла у прикључак на Time of Flight сензору. Кабл ће ући само у једном смеру.

1. Док је Wio Terminal искључен са вашег рачунара или другог извора напајања, повежите други крај Grove кабла са левим Grove прикључком на Wio Terminal-у, гледајући екран. Ово је прикључак најближи дугмету за напајање. Ово је комбиновани дигитални и IC прикључак.

![Grove Time of Flight сензор повезан са левим прикључком](../../../../../translated_images/sr/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Сада можете повезати Wio Terminal са вашим рачунаром.

## Програмирање Time of Flight сензора

Wio Terminal сада може бити програмиран да користи повезани Time of Flight сензор.

### Задатак - програмирајте Time of Flight сензор

1. Направите потпуно нови Wio Terminal пројекат користећи PlatformIO. Назовите овај пројекат `distance-sensor`. Додајте код у функцију `setup` за конфигурисање серијског порта.

1. Додајте зависност библиотеке за Seeed Grove Time of Flight сензор растојања у `platformio.ini` датотеку пројекта:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. У `main.cpp`, додајте следеће испод постојећих директива за укључивање како бисте декларисали инстанцу класе `Seeed_vl53l0x` за интеракцију са Time of Flight сензором:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Додајте следеће на крај функције `setup` за иницијализацију сензора:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. У функцији `loop`, прочитајте вредност са сензора:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Овај код иницијализује структуру података за читање података, а затим је прослеђује у метод `PerformSingleRangingMeasurement` где ће бити попуњена мерењем растојања.

1. Испод овога, испишите мерење растојања, а затим направите паузу од 1 секунде:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Компилирајте, отпремите и покрените овај код. Моћи ћете да видите мерења растојања помоћу серијског монитора. Поставите објекте близу сензора и видећете мерење растојања:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Мерач растојања налази се на задњој страни сензора, па се уверите да користите исправну страну приликом мерења растојања.

    ![Мерач растојања на задњој страни Time of Flight сензора усмерен ка банани](../../../../../translated_images/sr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Овај код можете пронаћи у [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) фасцикли.

😀 Ваш програм за сензор близине је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да превод буде тачан, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.