<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-28T12:23:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "sl"
}
-->
# Razvrščanje slike z uporabo IoT Edge klasifikatorja slik - Wio Terminal

V tem delu lekcije boste uporabili klasifikator slik, ki deluje na napravi IoT Edge.

## Uporaba IoT Edge klasifikatorja

IoT napravo je mogoče preusmeriti, da uporablja IoT Edge klasifikator slik. URL za klasifikator slik je `http://<IP naslov ali ime>/image`, kjer `<IP naslov ali ime>` zamenjate z IP naslovom ali imenom računalnika, na katerem deluje IoT Edge.

### Naloga - uporaba IoT Edge klasifikatorja

1. Odprite projekt aplikacije `fruit-quality-detector`, če še ni odprt.

1. Klasifikator slik deluje kot REST API prek HTTP, ne HTTPS, zato mora klic uporabljati WiFi odjemalca, ki podpira samo HTTP klice. To pomeni, da certifikat ni potreben. Izbrišite `CERTIFICATE` iz datoteke `config.h`.

1. URL za napovedovanje v datoteki `config.h` je treba posodobiti na nov URL. Prav tako lahko izbrišete `PREDICTION_KEY`, saj ni potreben.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Zamenjajte `<URL>` z URL-jem vašega klasifikatorja.

1. V datoteki `main.cpp` spremenite direktivo za vključitev WiFi Client Secure, da uvozite standardno različico HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Spremenite deklaracijo `WiFiClient`, da bo uporabljala HTTP različico:

    ```cpp
    WiFiClient client;
    ```

1. Poiščite vrstico, ki nastavi certifikat na WiFi odjemalcu. Odstranite vrstico `client.setCACert(CERTIFICATE);` iz funkcije `connectWiFi`.

1. V funkciji `classifyImage` odstranite vrstico `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, ki nastavi ključ za napovedovanje v glavi.

1. Naložite in zaženite svojo kodo. Usmerite kamero proti sadju in pritisnite gumb C. Izhod boste videli v serijskem monitorju:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 To kodo lahko najdete v mapi [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Vaš program za klasifikacijo kakovosti sadja je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.