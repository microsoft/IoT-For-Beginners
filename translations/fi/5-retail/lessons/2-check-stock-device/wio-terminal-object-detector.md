<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T20:31:47+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "fi"
}
-->
# Kutsu objektintunnistinta IoT-laitteestasi - Wio Terminal

Kun objektintunnistin on julkaistu, sitä voidaan käyttää IoT-laitteestasi.

## Kopioi kuvantunnistusprojekti

Suurin osa varastotunnistimestasi on sama kuin aiemmassa oppitunnissa luomasi kuvantunnistin.

### Tehtävä - kopioi kuvantunnistusprojekti

1. Yhdistä ArduCam Wio Terminaliisi seuraamalla [valmistusprojektin oppitunnin 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera) ohjeita.

    Saatat myös haluta kiinnittää kameran yhteen paikkaan, esimerkiksi ripustamalla kaapelin laatikon tai tölkin päälle tai kiinnittämällä kameran laatikkoon kaksipuolisella teipillä.

1. Luo täysin uusi Wio Terminal -projekti käyttämällä PlatformIO:ta. Nimeä projekti `stock-counter`.

1. Toista vaiheet [valmistusprojektin oppitunnin 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) ohjeiden mukaisesti kuvien ottamiseksi kamerasta.

1. Toista vaiheet [valmistusprojektin oppitunnin 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) ohjeiden mukaisesti kutsuaksesi kuvantunnistinta. Suurin osa tästä koodista käytetään uudelleen objektien tunnistamiseen.

## Muuta koodi tunnistimesta objektintunnistimeksi

Koodi, jota käytit kuvien luokitteluun, on hyvin samanlainen kuin objektien tunnistamiseen käytettävä koodi. Suurin ero on Custom Visionista saatu URL-osoite ja kutsun tulokset.

### Tehtävä - muuta koodi tunnistimesta objektintunnistimeksi

1. Lisää seuraava include-direktiivi `main.cpp`-tiedoston alkuun:

    ```cpp
    #include <vector>
    ```

1. Nimeä `classifyImage`-funktio uudelleen `detectStock`-funktioksi, sekä funktion nimi että kutsu `buttonPressed`-funktiossa.

1. Julista `detectStock`-funktion yläpuolella kynnysarvo, jolla suodatetaan pois kaikki tunnistukset, joiden todennäköisyys on alhainen:

    ```cpp
    const float threshold = 0.3f;
    ```

    Toisin kuin kuvantunnistin, joka palauttaa vain yhden tuloksen per tunniste, objektintunnistin palauttaa useita tuloksia, joten kaikki alhaisen todennäköisyyden tulokset täytyy suodattaa pois.

1. Julista `detectStock`-funktion yläpuolella funktio ennusteiden käsittelemiseksi:

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

    Tämä ottaa ennustelistan ja tulostaa sen sarjamonitoriin.

1. Korvaa `detectStock`-funktion sisällä ennusteita läpikäyvän `for`-silmukan sisältö seuraavalla:

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

    Tämä käy läpi ennusteet ja vertaa todennäköisyyttä kynnysarvoon. Kaikki ennusteet, joiden todennäköisyys ylittää kynnysarvon, lisätään `list`-muuttujaan ja välitetään `processPredictions`-funktiolle.

1. Lataa ja suorita koodisi. Suuntaa kamera hyllyllä oleviin esineisiin ja paina C-painiketta. Näet tulokset sarjamonitorissa:

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

    > 💁 Saatat joutua säätämään `threshold`-arvoa sopivaksi kuvillesi.

    Näet otetun kuvan ja nämä arvot **Predictions**-välilehdessä Custom Visionissa.

    ![4 tomaattipyreetölkkiä hyllyllä ennusteilla, joissa tunnistusten todennäköisyydet ovat 35.8%, 33.5%, 25.7% ja 16.6%](../../../../../translated_images/fi/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Löydät tämän koodin [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) -kansiosta.

😀 Varastolaskurisi ohjelma onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.