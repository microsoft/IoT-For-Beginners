<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "hu"
}
-->
# Képek osztályozása IoT Edge alapú képosztályozóval - Wio Terminal

Ebben a leckében az IoT Edge eszközön futó képosztályozót fogod használni.

## Az IoT Edge osztályozó használata

Az IoT eszközt át lehet irányítani, hogy az IoT Edge képosztályozót használja. A képosztályozó URL-je: `http://<IP cím vagy név>/image`, ahol `<IP cím vagy név>` helyére az IoT Edge-t futtató számítógép IP címe vagy hosztneve kerül.

### Feladat - az IoT Edge osztályozó használata

1. Nyisd meg a `fruit-quality-detector` alkalmazás projektet, ha még nincs megnyitva.

1. A képosztályozó REST API-ként fut HTTP-n keresztül, nem HTTPS-en, ezért a híváshoz olyan WiFi kliensre van szükség, amely csak HTTP hívásokkal működik. Ez azt jelenti, hogy tanúsítványra nincs szükség. Töröld a `CERTIFICATE`-t a `config.h` fájlból.

1. A `config.h` fájlban frissíteni kell az előrejelzési URL-t az új URL-re. A `PREDICTION_KEY`-t is törölheted, mivel erre nincs szükség.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Cseréld ki `<URL>`-t az osztályozód URL-jére.

1. A `main.cpp` fájlban módosítsd a WiFi Client Secure importálási direktíváját, hogy a standard HTTP verziót importálja:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Módosítsd a `WiFiClient` deklarációját, hogy az HTTP verziót használja:

    ```cpp
    WiFiClient client;
    ```

1. Keresd meg azt a sort, amely beállítja a tanúsítványt a WiFi kliensen. Töröld a `client.setCACert(CERTIFICATE);` sort a `connectWiFi` függvényből.

1. A `classifyImage` függvényben töröld a `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` sort, amely beállítja az előrejelzési kulcsot a fejlécben.

1. Töltsd fel és futtasd a kódot. Irányítsd a kamerát néhány gyümölcsre, és nyomd meg a C gombot. Az eredményt a soros monitoron fogod látni:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ezt a kódot megtalálod a [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) mappában.

😀 A gyümölcsminőség osztályozó programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.