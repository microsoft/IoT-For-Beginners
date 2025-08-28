<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T14:27:57+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "sr"
}
-->
# Позовите ваш детектор објеката са IoT уређаја - Wio Terminal

Када ваш детектор објеката буде објављен, можете га користити са вашег IoT уређаја.

## Копирајте пројекат класификатора слика

Већина вашег детектора залиха је иста као класификатор слика који сте креирали у претходној лекцији.

### Задатак - копирајте пројекат класификатора слика

1. Повежите ваш ArduCam са Wio Terminal-ом, пратећи кораке из [лекције 2 пројекта производње](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Можда ћете желети да фиксирате камеру у једној позицији, на пример, тако што ћете кабл обесити преко кутије или конзерве, или фиксирати камеру на кутију помоћу двостране траке.

1. Направите потпуно нови Wio Terminal пројекат користећи PlatformIO. Назовите овај пројекат `stock-counter`.

1. Реплицирајте кораке из [лекције 2 пројекта производње](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) за снимање слика са камере.

1. Реплицирајте кораке из [лекције 2 пројекта производње](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) за позивање класификатора слика. Већина овог кода ће бити поново употребљена за детекцију објеката.

## Промените код са класификатора на детектор слика

Код који сте користили за класификацију слика је веома сличан коду за детекцију објеката. Главна разлика је URL који се позива, а који сте добили од Custom Vision, и резултати позива.

### Задатак - промените код са класификатора на детектор слика

1. Додајте следећу директиву за укључивање на врх `main.cpp` датотеке:

    ```cpp
    #include <vector>
    ```

1. Преименујте функцију `classifyImage` у `detectStock`, како име функције, тако и позив у функцији `buttonPressed`.

1. Изнад функције `detectStock`, декларишите праг за филтрирање било које детекције са ниском вероватноћом:

    ```cpp
    const float threshold = 0.3f;
    ```

    За разлику од класификатора слика који враћа само један резултат по ознаци, детектор објеката ће вратити више резултата, па је потребно филтрирати оне са ниском вероватноћом.

1. Изнад функције `detectStock`, декларишите функцију за обраду предвиђања:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Ова функција узима листу предвиђања и штампа их на серијски монитор.

1. У функцији `detectStock`, замените садржај `for` петље која пролази кроз предвиђања следећим:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Ова петља пролази кроз предвиђања, упоређујући вероватноћу са прагом. Сва предвиђања која имају вероватноћу већу од прага додају се у `list` и прослеђују функцији `processPredictions`.

1. Отпремите и покрените ваш код. Усмерите камеру ка објектима на полици и притисните C дугме. Видећете излаз на серијском монитору:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Можда ћете морати да прилагодите `threshold` на одговарајућу вредност за ваше слике.

    Моћи ћете да видите слику која је снимљена, као и ове вредности у **Predictions** картици у Custom Vision.

    ![4 конзерве парадајз пасте на полици са предвиђањима за 4 детекције од 35.8%, 33.5%, 25.7% и 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.sr.png)

> 💁 Овај код можете пронаћи у [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) фасцикли.

😀 Ваш програм за бројање залиха је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако настојимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.