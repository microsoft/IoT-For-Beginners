<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:29:45+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "fi"
}
-->
# Laske varasto IoT-laitteellasi - Wio Terminal

Ennusteiden ja niiden rajauslaatikoiden yhdistelmää voidaan käyttää varaston laskemiseen kuvasta.

## Laske varasto

![4 tomaattipyreepurkkia, joiden ympärillä rajauslaatikot](../../../../../translated_images/fi/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Yllä olevassa kuvassa rajauslaatikot ovat hieman päällekkäin. Jos tämä päällekkäisyys olisi paljon suurempi, rajauslaatikot saattaisivat viitata samaan objektiin. Jotta objektit lasketaan oikein, sinun täytyy jättää huomiotta laatikot, joilla on merkittävä päällekkäisyys.

### Tehtävä - laske varasto jättäen päällekkäisyys huomiotta

1. Avaa `stock-counter`-projektisi, jos se ei ole jo auki.

1. Lisää `processPredictions`-funktion yläpuolelle seuraava koodi:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Tämä määrittää sallitun päällekkäisyyden prosenttiosuuden ennen kuin rajauslaatikot katsotaan samaksi objektiksi. 0.20 tarkoittaa 20 % päällekkäisyyttä.

1. Tämän jälkeen, ja edelleen `processPredictions`-funktion yläpuolelle, lisää seuraava koodi laskeaksesi kahden suorakulmion päällekkäisyyden:

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

    Tämä koodi määrittää `Point`-rakenteen tallentaakseen pisteitä kuvassa ja `Rect`-rakenteen määrittääkseen suorakulmion käyttäen vasenta yläkulmaa ja oikeaa alakulmaa. Se määrittää myös `area`-funktion, joka laskee suorakulmion pinta-alan vasemman yläkulman ja oikean alakulman perusteella.

    Seuraavaksi se määrittää `overlappingArea`-funktion, joka laskee kahden suorakulmion päällekkäisen alueen. Jos ne eivät ole päällekkäisiä, se palauttaa arvon 0.

1. `overlappingArea`-funktion alapuolelle määritä funktio, joka muuntaa rajauslaatikon `Rect`-muotoon:

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

    Tämä ottaa ennusteen objektin tunnistimelta, poimii rajauslaatikon ja käyttää rajauslaatikon arvoja suorakulmion määrittämiseen. Oikea reuna lasketaan vasemmasta reunasta plus leveys. Alareuna lasketaan yläreunasta plus korkeus.

1. Ennusteet täytyy verrata toisiinsa, ja jos kahdella ennusteella on päällekkäisyyttä enemmän kuin kynnysarvo, yksi niistä täytyy poistaa. Päällekkäisyyden kynnysarvo on prosenttiosuus, joten se täytyy kertoa pienimmän rajauslaatikon koolla, jotta voidaan tarkistaa, ylittääkö päällekkäisyys annetun prosenttiosuuden rajauslaatikosta, ei koko kuvasta. Aloita poistamalla `processPredictions`-funktion sisältö.

1. Lisää seuraava tyhjään `processPredictions`-funktioon:

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

    Tämä koodi määrittää vektorin tallentaakseen ennusteet, jotka eivät ole päällekkäisiä. Se käy läpi kaikki ennusteet ja luo `Rect`-muodon rajauslaatikosta.

    Seuraavaksi tämä koodi käy läpi jäljellä olevat ennusteet, alkaen nykyisen ennusteen jälkeisestä. Tämä estää ennusteita vertaamasta useammin kuin kerran - kun 1 ja 2 on verrattu, ei ole tarpeen verrata 2:ta 1:een, vain 3:een, 4:ään jne.

    Jokaiselle ennusteparille lasketaan päällekkäinen alue. Tämä sitten verrataan pienimmän rajauslaatikon alueeseen - jos päällekkäisyys ylittää kynnysarvon prosenttiosuuden pienimmästä rajauslaatikosta, ennuste merkitään hylätyksi. Jos kaikkien päällekkäisyyksien jälkeen ennuste läpäisee tarkistukset, se lisätään `passed_predictions`-kokoelmaan.

    > 💁 Tämä on hyvin yksinkertainen tapa poistaa päällekkäisyydet, vain poistamalla ensimmäinen päällekkäisessä parissa. Tuotantokoodissa haluaisit lisätä enemmän logiikkaa, kuten huomioida päällekkäisyydet useiden objektien välillä tai jos yksi rajauslaatikko sisältyy toiseen.

1. Tämän jälkeen lisää seuraava koodi lähettääksesi hyväksyttyjen ennusteiden tiedot sarjamonitoriin:

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

    Tämä koodi käy läpi hyväksytyt ennusteet ja tulostaa niiden tiedot sarjamonitoriin.

1. Tämän alapuolelle lisää koodi tulostaaksesi laskettujen kohteiden määrän sarjamonitoriin:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Tämä voitaisiin sitten lähettää IoT-palveluun ilmoittamaan, jos varastotasot ovat alhaiset.

1. Lataa ja suorita koodisi. Suuntaa kamera hyllyllä oleviin esineisiin ja paina C-painiketta. Kokeile säätää `overlap_threshold`-arvoa nähdäksesi ennusteiden hylkäämisen.

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

> 💁 Löydät tämän koodin [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) -kansiosta.

😀 Varastonlaskentaohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.