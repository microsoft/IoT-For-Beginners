<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T14:30:40+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "hr"
}
-->
# Brojanje zaliha s vašeg IoT uređaja - Wio Terminal

Kombinacija predikcija i njihovih okvira može se koristiti za brojanje zaliha na slici.

## Brojanje zaliha

![4 limenke paste od rajčice s okvirima oko svake limenke](../../../../../translated_images/hr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

Na slici prikazanoj iznad, okviri se malo preklapaju. Ako bi to preklapanje bilo znatno veće, okviri bi mogli označavati isti objekt. Da biste ispravno izbrojali objekte, trebate ignorirati okvire s velikim preklapanjem.

### Zadatak - brojanje zaliha ignorirajući preklapanje

1. Otvorite svoj projekt `stock-counter` ako već nije otvoren.

1. Iznad funkcije `processPredictions`, dodajte sljedeći kod:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ovo definira postotak preklapanja koji je dopušten prije nego što se okviri smatraju istim objektom. 0.20 definira 20% preklapanja.

1. Ispod toga, a iznad funkcije `processPredictions`, dodajte sljedeći kod za izračun preklapanja između dva pravokutnika:

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

    Ovaj kod definira strukturu `Point` za pohranu točaka na slici i strukturu `Rect` za definiranje pravokutnika pomoću gornje lijeve i donje desne koordinate. Zatim definira funkciju `area` koja izračunava površinu pravokutnika iz gornje lijeve i donje desne koordinate.

    Nadalje, definira funkciju `overlappingArea` koja izračunava preklapajuću površinu dvaju pravokutnika. Ako se ne preklapaju, vraća 0.

1. Ispod funkcije `overlappingArea`, deklarirajte funkciju za pretvaranje okvira u `Rect`:

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

    Ovo uzima predikciju iz detektora objekata, izvlači okvir i koristi vrijednosti iz okvira za definiranje pravokutnika. Desna strana se izračunava kao lijeva plus širina. Donja strana se izračunava kao gornja plus visina.

1. Predikcije treba usporediti međusobno, a ako dvije predikcije imaju preklapanje veće od praga, jednu od njih treba izbrisati. Prag preklapanja je postotak, pa ga treba pomnožiti s veličinom najmanjeg okvira kako bi se provjerilo prelazi li preklapanje zadani postotak okvira, a ne zadani postotak cijele slike. Počnite brisanjem sadržaja funkcije `processPredictions`.

1. Dodajte sljedeće u praznu funkciju `processPredictions`:

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

    Ovaj kod deklarira vektor za pohranu predikcija koje se ne preklapaju. Zatim prolazi kroz sve predikcije, stvarajući `Rect` iz okvira.

    Zatim ovaj kod prolazi kroz preostale predikcije, počevši od one nakon trenutne predikcije. Ovo sprječava da se predikcije uspoređuju više puta - nakon što su 1 i 2 uspoređene, nema potrebe uspoređivati 2 s 1, već samo s 3, 4, itd.

    Za svaki par predikcija izračunava se preklapajuća površina. Ovo se zatim uspoređuje s površinom najmanjeg okvira - ako preklapanje prelazi prag postotka najmanjeg okvira, predikcija se označava kao neuspješna. Ako nakon usporedbe svih preklapanja predikcija prođe provjere, dodaje se u kolekciju `passed_predictions`.

    > 💁 Ovo je vrlo jednostavan način uklanjanja preklapanja, jednostavno uklanjajući prvu u paru koji se preklapa. Za produkcijski kod, ovdje biste trebali dodati više logike, poput razmatranja preklapanja između više objekata ili ako je jedan okvir unutar drugog.

1. Nakon toga, dodajte sljedeći kod za slanje detalja o prošlim predikcijama na serijski monitor:

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

    Ovaj kod prolazi kroz prošle predikcije i ispisuje njihove detalje na serijski monitor.

1. Ispod toga, dodajte kod za ispis broja izbrojanih stavki na serijski monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Ovo bi se zatim moglo poslati IoT usluzi kako bi se upozorilo ako su razine zaliha niske.

1. Prenesite i pokrenite svoj kod. Usmjerite kameru prema objektima na polici i pritisnite gumb C. Pokušajte prilagoditi vrijednost `overlap_threshold` kako biste vidjeli kako se predikcije ignoriraju.

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

> 💁 Ovaj kod možete pronaći u mapi [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Vaš program za brojanje zaliha bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.