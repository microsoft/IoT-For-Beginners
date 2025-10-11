<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-10-11T11:43:39+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ta"
}
-->
# IoT Edge அடிப்படையிலான படத்தை வகைப்படுத்துதல் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், நீங்கள் IoT Edge சாதனத்தில் இயங்கும் Image Classifier-ஐ பயன்படுத்துவீர்கள்.

## IoT Edge வகைப்படுத்தியை பயன்படுத்தவும்

IoT சாதனம் IoT Edge பட வகைப்படுத்தியை பயன்படுத்த மறு-திசைமாற்றம் செய்யப்படலாம். Image Classifier-க்கான URL `http://<IP address or name>/image` ஆகும், இதில் `<IP address or name>` என்பதை IoT Edge இயங்கும் கணினியின் IP முகவரி அல்லது ஹோஸ்ட் பெயரால் மாற்றவும்.

### பணிகள் - IoT Edge வகைப்படுத்தியை பயன்படுத்தவும்

1. `fruit-quality-detector` ஆப் திட்டத்தை திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. பட வகைப்படுத்தி HTTP மூலம் REST API ஆக இயங்குகிறது, HTTPS அல்ல, எனவே அழைப்பு HTTP அழைப்புகளுடன் மட்டுமே வேலை செய்யும் WiFi கிளையண்டை பயன்படுத்த வேண்டும். இதனால் சான்றிதழ் தேவையில்லை. `config.h` கோப்பில் இருந்து `CERTIFICATE`-ஐ நீக்கவும்.

1. `config.h` கோப்பில் உள்ள கணிப்பு URL-ஐ புதிய URL-க்கு புதுப்பிக்க வேண்டும். `PREDICTION_KEY`-ஐ நீக்கவும், இது தேவையில்லை.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    `<URL>`-ஐ உங்கள் வகைப்படுத்தியின் URL-ஆக மாற்றவும்.

1. `main.cpp`-இல், WiFi Client Secure-க்கு உள்ள include directive-ஐ மாறி, சாதாரண HTTP பதிப்பை இறக்குமதி செய்யவும்:

    ```cpp
    #include <WiFiClient.h>
    ```

1. `WiFiClient`-ஐ HTTP பதிப்பாக அறிவிக்க மாற்றவும்:

    ```cpp
    WiFiClient client;
    ```

1. WiFi கிளையண்டில் சான்றிதழை அமைக்கும் வரியை தேர்ந்தெடுக்கவும். `connectWiFi` செயல்பாட்டில் இருந்து `client.setCACert(CERTIFICATE);` வரியை நீக்கவும்.

1. `classifyImage` செயல்பாட்டில், தலைப்பில் கணிப்பு விசையை அமைக்கும் `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` வரியை நீக்கவும்.

1. உங்கள் குறியீட்டை பதிவேற்றி இயக்கவும். கேமராவை சில பழங்களின் மீது சுட்டி C பொத்தானை அழுத்தவும். நீங்கள் சீரியல் மானிட்டரில் வெளியீட்டை காணலாம்:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 இந்த குறியீட்டை [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) கோப்புறையில் காணலாம்.

😀 உங்கள் பழ தரம் வகைப்படுத்தும் திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.