<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T14:30:58+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "sl"
}
-->
# Štetje zalog z vašo IoT napravo - Wio Terminal

Kombinacija napovedi in njihovih obrisnih okvirjev se lahko uporabi za štetje zalog na sliki.

## Štetje zalog

![4 pločevinke paradižnikovega koncentrata z obrisnimi okvirji okoli vsake pločevinke](../../../../../translated_images/sl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Na zgornji sliki imajo obrisni okvirji majhno prekrivanje. Če bi bilo to prekrivanje veliko večje, bi lahko obrisni okvirji nakazovali isti predmet. Da pravilno preštejete predmete, morate ignorirati okvirje z znatnim prekrivanjem.

### Naloga - štetje zalog ob ignoriranju prekrivanja

1. Odprite svoj projekt `stock-counter`, če še ni odprt.

1. Nad funkcijo `processPredictions` dodajte naslednjo kodo:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    To določa odstotek dovoljenega prekrivanja, preden se obrisni okvirji obravnavajo kot isti predmet. 0.20 določa 20% prekrivanje.

1. Pod tem, in nad funkcijo `processPredictions`, dodajte naslednjo kodo za izračun prekrivanja med dvema pravokotnikoma:

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

    Ta koda definira strukturo `Point` za shranjevanje točk na sliki in strukturo `Rect` za definiranje pravokotnika z zgornjo levo in spodnjo desno koordinato. Nato definira funkcijo `area`, ki izračuna površino pravokotnika iz zgornje leve in spodnje desne koordinate.

    Nato definira funkcijo `overlappingArea`, ki izračuna prekrivajočo površino dveh pravokotnikov. Če se ne prekrivata, vrne 0.

1. Pod funkcijo `overlappingArea` deklarirajte funkcijo za pretvorbo obrisnega okvirja v `Rect`:

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

    Ta funkcija vzame napoved iz detektorja predmetov, izvleče obrisni okvir in uporabi vrednosti obrisnega okvirja za definiranje pravokotnika. Desna stran se izračuna iz leve plus širina. Spodnja stran se izračuna kot zgornja plus višina.

1. Napovedi je treba primerjati med seboj, in če imata dve napovedi prekrivanje, ki presega prag, je treba eno od njih izbrisati. Prag prekrivanja je odstotek, zato ga je treba pomnožiti z velikostjo najmanjšega obrisnega okvirja, da preverimo, ali prekrivanje presega določen odstotek obrisnega okvirja, ne pa določen odstotek celotne slike. Začnite z brisanjem vsebine funkcije `processPredictions`.

1. Dodajte naslednje v prazno funkcijo `processPredictions`:

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

    Ta koda deklarira vektor za shranjevanje napovedi, ki se ne prekrivajo. Nato zanka prehaja skozi vse napovedi in ustvari `Rect` iz obrisnega okvirja.

    Nato ta koda zanka skozi preostale napovedi, začenši z napovedjo, ki sledi trenutni. To prepreči, da bi bile napovedi primerjane več kot enkrat - ko sta 1 in 2 primerjani, ni potrebe po primerjavi 2 z 1, le z 3, 4 itd.

    Za vsak par napovedi se izračuna prekrivajoča površina. Nato se to primerja s površino najmanjšega obrisnega okvirja - če prekrivanje presega prag odstotka najmanjšega obrisnega okvirja, se napoved označi kot neuspešna. Če po primerjavi vseh prekrivanj napoved prestane preverjanja, se doda v zbirko `passed_predictions`.

    > 💁 To je zelo preprost način za odstranjevanje prekrivanj, saj se odstrani le prva napoved v paru, ki se prekriva. Za produkcijsko kodo bi želeli dodati več logike, kot je upoštevanje prekrivanj med več predmeti ali če je en obrisni okvir vsebovan v drugem.

1. Po tem dodajte naslednjo kodo za pošiljanje podrobnosti o uspešnih napovedih na serijski monitor:

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

    Ta koda zanka skozi uspešne napovedi in natisne njihove podrobnosti na serijski monitor.

1. Pod tem dodajte kodo za tiskanje števila preštetih predmetov na serijski monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    To bi se nato lahko poslalo IoT storitvi za opozarjanje, če so zaloge nizke.

1. Naložite in zaženite svojo kodo. Usmerite kamero na predmete na polici in pritisnite gumb C. Poskusite prilagoditi vrednost `overlap_threshold`, da vidite, kako se napovedi ignorirajo.

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

> 💁 To kodo lahko najdete v mapi [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Vaš program za štetje zalog je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki izhajajo iz uporabe tega prevoda.