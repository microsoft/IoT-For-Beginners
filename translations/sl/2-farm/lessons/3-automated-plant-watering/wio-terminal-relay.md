# Upravljanje releja - Wio Terminal

V tem delu lekcije boste poleg senzorja za vlažnost tal dodali rele na vaš Wio Terminal in ga upravljali glede na raven vlažnosti tal.

## Strojna oprema

Wio Terminal potrebuje rele.

Rele, ki ga boste uporabili, je [Grove rele](https://www.seeedstudio.com/Grove-Relay.html), običajno odprt rele (kar pomeni, da je izhodni krog odprt ali prekinjen, ko ni signala, poslanega na rele), ki lahko obvladuje izhodne kroge do 250V in 10A.

To je digitalni aktuator, zato se povezuje na digitalne pine na Wio Terminalu. Kombinirani analogni/digitalni priključek je že v uporabi s senzorjem za vlažnost tal, zato se ta priključi na drugi priključek, ki je kombinirani I2C in digitalni priključek.

### Povežite rele

Grove rele lahko povežete na digitalni priključek Wio Terminala.

#### Naloga

Povežite rele.

![Grove rele](../../../../../translated_images/sl/grove-relay.d426958ca210fbd0.webp)

1. Vstavite en konec Grove kabla v vtičnico na releju. Kabel bo šel noter samo v eno smer.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega napajalnika, povežite drugi konec Grove kabla na levo vtičnico Grove na Wio Terminalu, gledano na zaslon. Senzor za vlažnost tal pustite povezan na desni vtičnici.

![Grove rele povezan na levo vtičnico, senzor za vlažnost tal povezan na desno vtičnico](../../../../../translated_images/sl/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Vstavite senzor za vlažnost tal v zemljo, če to ni že narejeno v prejšnji lekciji.

## Programiranje releja

Wio Terminal je zdaj pripravljen za programiranje, da uporablja priključeni rele.

### Naloga

Programirajte napravo.

1. Odprite projekt `soil-moisture-sensor` iz prejšnje lekcije v VS Code, če ni že odprt. Dodali boste k temu projektu.

2. Za ta aktuator ni knjižnice - gre za digitalni aktuator, ki ga upravljate z visokim ali nizkim signalom. Za vklop pošljete visok signal na pin (3.3V), za izklop pa nizki signal (0V). To lahko storite z vgrajeno funkcijo Arduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Začnite tako, da na dno funkcije `setup` dodate naslednje, da nastavite kombinirani I2C/digitalni priključek kot izhodni pin za pošiljanje napetosti na rele:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` je številka priključka za kombinirani I2C/digitalni priključek.

1. Da preverite, ali rele deluje, dodajte naslednje v funkcijo `loop`, pod zadnjim `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Koda pošlje visok signal na pin, na katerega je povezan rele, da ga vklopi, počaka 500ms (pol sekunde), nato pošlje nizki signal, da rele izklopi.

1. Sestavite in naložite kodo na Wio Terminal.

1. Ko je koda naložena, se bo rele vklapljal in izklapljal vsakih 10 sekund, s polsekundnim zamikom med vklopom in izklopom. Slišali boste klik releja ob vklopu in izklopu. LED na Grove plošči bo zasvetila, ko je rele vklopljen, in ugasnila, ko je rele izklopljen.

    ![Rele se vklaplja in izklaplja](../../../../../images/relay-turn-on-off.gif)

## Upravljanje releja glede na vlažnost tal

Zdaj, ko rele deluje, ga lahko upravljate glede na odčitke vlažnosti tal.

### Naloga

Upravljajte rele.

1. Izbrišite 3 vrstice kode, ki ste jih dodali za testiranje releja. Zamenjajte jih z naslednjo kodo:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Ta koda preveri raven vlažnosti tal iz senzorja za vlažnost tal. Če je nad 450, vklopi rele, in ga izklopi, ko pade pod 450.

    > 💁 Ne pozabite, da kapacitivni senzor za vlažnost tal bere tako, da nižja kot je raven vlažnosti tal, več vlage je v tleh, in obratno.

1. Sestavite in naložite kodo na Wio Terminal.

1. Spremljajte napravo prek serijskega monitorja. Videli boste, kako se rele vklopi ali izklopi glede na raven vlažnosti tal. Preizkusite v suhih tleh, nato dodajte vodo.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 To kodo najdete v mapi [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Vaš program za upravljanje releja glede na senzor za vlažnost tal je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.