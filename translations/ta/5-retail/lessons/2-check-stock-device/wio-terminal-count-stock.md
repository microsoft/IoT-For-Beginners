<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-10-11T12:48:15+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ta"
}
-->
# உங்கள் IoT சாதனத்திலிருந்து பங்கு எண்ணுக - Wio Terminal

முன்னறிவிப்புகள் மற்றும் அவற்றின் எல்லைகளின் சேர்க்கையைப் பயன்படுத்தி ஒரு படத்தில் பங்குகளை எண்ண முடியும்.

## பங்கு எண்ணுக

![தக்காளி பேஸ்ட் கேன்கள் 4, ஒவ்வொரு கேனுக்கும் எல்லைகள்](../../../../../translated_images/ta/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

மேலே காட்டப்பட்டுள்ள படத்தில், எல்லைகள் சிறிய அளவில் ஒட்டியுள்ளன. இந்த ஒட்டுதல் மிகவும் அதிகமாக இருந்தால், எல்லைகள் ஒரே பொருளைக் குறிக்கக்கூடும். பொருட்களை சரியாக எண்ண, முக்கியமான அளவில் ஒட்டியுள்ள எல்லைகளை புறக்கணிக்க வேண்டும்.

### பணிகள் - ஒட்டுதலை புறக்கணித்து பங்கு எண்ணுக

1. உங்கள் `stock-counter` திட்டத்தை திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. `processPredictions` செயல்பாட்டின் மேல், பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    இது எல்லைகள் ஒரே பொருளாகக் கருதப்படும் முன் அனுமதிக்கப்பட்ட சதவீத ஒட்டுதலை வரையறுக்கிறது. 0.20 என்பது 20% ஒட்டுதலைக் குறிக்கிறது.

1. இதற்குப் பிறகு, மற்றும் `processPredictions` செயல்பாட்டின் மேல், இரண்டு செங்குத்துகளுக்கு இடையிலான ஒட்டுதலை கணக்கிட பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    இந்த குறியீடு ஒரு `Point` struct ஐ வரையறுக்கிறது, இது படத்தில் புள்ளிகளைச் சேமிக்கிறது, மற்றும் ஒரு `Rect` struct ஐ வரையறுக்கிறது, இது மேல் இடது மற்றும் கீழ் வலது ஒருங்கிணைப்புகளைப் பயன்படுத்தி ஒரு செங்குத்தை வரையறுக்கிறது. பின்னர், ஒரு `area` செயல்பாட்டை வரையறுக்கிறது, இது மேல் இடது மற்றும் கீழ் வலது ஒருங்கிணைப்புகளிலிருந்து ஒரு செங்குத்தின் பரப்பளவை கணக்கிடுகிறது.

    அடுத்ததாக, இது 2 செங்குத்துகளின் ஒட்டியுள்ள பரப்பளவை கணக்கிடும் `overlappingArea` செயல்பாட்டை வரையறுக்கிறது. அவை ஒட்டவில்லை என்றால், இது 0 ஐத் திருப்புகிறது.

1. `overlappingArea` செயல்பாட்டின் கீழ், ஒரு எல்லையை `Rect` ஆக மாற்ற ஒரு செயல்பாட்டை அறிவிக்கவும்:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    இது பொருள் கண்டறியக்கூடியது மூலம் ஒரு முன்னறிவிப்பை எடுக்கிறது, எல்லையை எடுத்து அதன் மதிப்புகளைப் பயன்படுத்தி ஒரு செங்குத்தை வரையறுக்கிறது. வலது பக்கம் இடது பக்கம் மற்றும் அகலம் மூலம் கணக்கிடப்படுகிறது. கீழ் பக்கம் மேல் பக்கம் மற்றும் உயரம் மூலம் கணக்கிடப்படுகிறது.

1. முன்னறிவிப்புகளை ஒன்றுக்கொன்று ஒப்பிட வேண்டும், மேலும் 2 முன்னறிவிப்புகள் தரவுகளின் அளவை மீறிய ஒட்டுதலைக் கொண்டிருந்தால், அவற்றில் ஒன்றை நீக்க வேண்டும். ஒட்டுதல் தரவளவு ஒரு சதவீதமாகும், எனவே மிகச் சிறிய எல்லையின் அளவுடன் பெருக்கப்பட வேண்டும், ஒட்டுதல் தரவளவின் சதவீதத்தை முழு படத்தின் சதவீதமாக அல்லாமல் சரிபார்க்க. முதலில் `processPredictions` செயல்பாட்டின் உள்ளடக்கத்தை நீக்கவும்.

1. காலியான `processPredictions` செயல்பாட்டில் பின்வருவன சேர்க்கவும்:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    இந்த குறியீடு ஒட்டாத முன்னறிவிப்புகளைச் சேமிக்க ஒரு வெக்டர் அறிவிக்கிறது. பின்னர், அனைத்து முன்னறிவிப்புகளையும் மடக்கி, எல்லையிலிருந்து ஒரு `Rect` உருவாக்குகிறது.

    அடுத்ததாக, இந்த குறியீடு மீதமுள்ள முன்னறிவிப்புகளை மடக்குகிறது, தற்போதைய முன்னறிவிப்புக்குப் பிறகு ஒன்றில் தொடங்குகிறது. இது முன்னறிவிப்புகள் மீண்டும் மீண்டும் ஒப்பிடப்படுவதைத் தடுக்கிறது - 1 மற்றும் 2 ஒப்பிடப்பட்ட பிறகு, 2 ஐ 1 உடன் ஒப்பிட தேவையில்லை, 3, 4, போன்றவற்றுடன் மட்டுமே.

    ஒவ்வொரு முன்னறிவிப்பு ஜோடிகளுக்கும் ஒட்டியுள்ள பரப்பளவு கணக்கிடப்படுகிறது. இது மிகச் சிறிய எல்லையின் பரப்பளவுடன் ஒப்பிடப்படுகிறது - ஒட்டுதல் தரவளவின் சதவீதத்தை மிகச் சிறிய எல்லையின் சதவீதமாக மீறினால், முன்னறிவிப்பு பாஸ் செய்யப்படவில்லை என்று குறிக்கப்படுகிறது. அனைத்து ஒட்டுதல்களையும் ஒப்பிடும் பிறகு, முன்னறிவிப்பு சோதனைகளை பாஸ் செய்தால், அது `passed_predictions` தொகுப்பில் சேர்க்கப்படுகிறது.

    > 💁 இது ஒட்டுதலை நீக்க மிகவும் எளிமையான வழி, ஒட்டியுள்ள ஜோடியில் முதல் ஒன்றை மட்டும் நீக்குகிறது. உற்பத்தி குறியீட்டிற்காக, நீங்கள் இங்கே மேலும் தரவுகளைச் சேர்க்க விரும்புவீர்கள், பல பொருட்களுக்கிடையிலான ஒட்டுதலைக் கருத்தில் கொள்ளுதல் போன்றவை, அல்லது ஒரு எல்லை மற்றொன்றால் அடங்கியிருந்தால்.

1. இதற்குப் பிறகு, பாஸ் செய்யப்பட்ட முன்னறிவிப்புகளின் விவரங்களை சீரியல் மானிட்டருக்கு அனுப்ப பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    இந்த குறியீடு பாஸ் செய்யப்பட்ட முன்னறிவிப்புகளை மடக்கி, அவற்றின் விவரங்களை சீரியல் மானிட்டரில் அச்சிடுகிறது.

1. இதற்குப் பிறகு, எண்ணப்பட்ட பொருட்களின் எண்ணிக்கையை சீரியல் மானிட்டரில் அச்சிட பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    இது பின்னர் பங்கு நிலைகள் குறைவாக இருந்தால் எச்சரிக்க IoT சேவைக்கு அனுப்பப்படலாம்.

1. உங்கள் குறியீட்டை பதிவேற்றவும் மற்றும் இயக்கவும். ஒரு தட்டில் உள்ள பொருட்களை நோக்கி கேமராவைச் சுட்டவும் மற்றும் C பொத்தானை அழுத்தவும். `overlap_threshold` மதிப்பை சரிசெய்து முன்னறிவிப்புகள் புறக்கணிக்கப்படுவதைப் பாருங்கள்.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 இந்த குறியீட்டை [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) கோப்பகத்தில் காணலாம்.

😀 உங்கள் பங்கு எண்ணும் திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் AI மொழிபெயர்ப்பு சேவை [Co-op Translator](https://github.com/Azure/co-op-translator) பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.