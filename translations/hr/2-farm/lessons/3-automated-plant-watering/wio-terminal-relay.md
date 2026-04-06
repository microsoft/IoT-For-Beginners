# Kontrola releja - Wio Terminal

U ovom dijelu lekcije, dodat ćete relej svom Wio Terminalu uz senzor vlažnosti tla i kontrolirati ga na temelju razine vlažnosti tla.

## Hardver

Wio Terminalu je potreban relej.

Relej koji ćete koristiti je [Grove relej](https://www.seeedstudio.com/Grove-Relay.html), relej koji je obično otvoren (što znači da je izlazni krug otvoren ili odspojen kada nema signala poslanog releju) i može podnijeti izlazne krugove do 250V i 10A.

Ovo je digitalni aktuator, pa se povezuje na digitalne pinove na Wio Terminalu. Kombinirani analogni/digitalni port već je u upotrebi sa senzorom vlažnosti tla, pa se ovaj priključuje na drugi port, koji je kombinirani I2C i digitalni port.

### Povežite relej

Grove relej može se povezati na digitalni port Wio Terminala.

#### Zadatak

Povežite relej.

![Grove relej](../../../../../translated_images/hr/grove-relay.d426958ca210fbd0.webp)

1. Umetnite jedan kraj Grove kabela u utičnicu na releju. Kabel će ući samo na jedan način.

1. Dok je Wio Terminal odspojen od vašeg računala ili drugog izvora napajanja, povežite drugi kraj Grove kabela s lijevom Grove utičnicom na Wio Terminalu gledajući ekran. Ostavite senzor vlažnosti tla povezan s desnom utičnicom.

![Grove relej povezan s lijevom utičnicom, a senzor vlažnosti tla povezan s desnom utičnicom](../../../../../translated_images/hr/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Umetnite senzor vlažnosti tla u tlo, ako već nije umetnut iz prethodne lekcije.

## Programiranje releja

Wio Terminal sada može biti programiran za korištenje povezanog releja.

### Zadatak

Programirajte uređaj.

1. Otvorite projekt `soil-moisture-sensor` iz prethodne lekcije u VS Code-u ako već nije otvoren. Dodavat ćete kod ovom projektu.

2. Ne postoji biblioteka za ovaj aktuator - to je digitalni aktuator koji se kontrolira visokim ili niskim signalom. Da biste ga uključili, šaljete visoki signal na pin (3.3V), a da biste ga isključili, šaljete niski signal (0V). To možete učiniti pomoću ugrađene Arduino funkcije [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/). Započnite dodavanjem sljedećeg na dno funkcije `setup` kako biste postavili kombinirani I2C/digitalni port kao izlazni pin za slanje napona releju:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` je broj porta za kombinirani I2C/digitalni port.

1. Da biste testirali radi li relej, dodajte sljedeće u funkciju `loop`, ispod završnog `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Kod šalje visoki signal na pin na koji je relej povezan kako bi ga uključio, čeka 500ms (pola sekunde), zatim šalje niski signal kako bi isključio relej.

1. Izgradite i učitajte kod na Wio Terminal.

1. Nakon učitavanja, relej će se uključivati i isključivati svakih 10 sekundi, s pola sekunde kašnjenja između uključivanja i isključivanja. Čut ćete kako relej klikne pri uključivanju, a zatim klikne pri isključivanju. LED na Grove ploči će svijetliti kada je relej uključen, a ugasiti se kada je isključen.

    ![Relej se uključuje i isključuje](../../../../../images/relay-turn-on-off.gif)

## Kontrola releja na temelju vlažnosti tla

Sada kada relej radi, može se kontrolirati kao odgovor na očitanja vlažnosti tla.

### Zadatak

Kontrolirajte relej.

1. Izbrišite 3 linije koda koje ste dodali za testiranje releja. Zamijenite ih sljedećim kodom:

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

    Ovaj kod provjerava razinu vlažnosti tla pomoću senzora vlažnosti tla. Ako je iznad 450, uključuje relej, a isključuje ga kada padne ispod 450.

    > 💁 Zapamtite, kapacitivni senzor vlažnosti tla očitava: što je niža razina vlažnosti tla, to je više vlage u tlu i obrnuto.

1. Izgradite i učitajte kod na Wio Terminal.

1. Pratite uređaj putem serijskog monitora. Vidjet ćete kako se relej uključuje ili isključuje ovisno o razini vlažnosti tla. Isprobajte u suhom tlu, a zatim dodajte vodu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Vaš program za kontrolu releja pomoću senzora vlažnosti tla je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.