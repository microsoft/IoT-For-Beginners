<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T15:23:22+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "hr"
}
-->
# Upravljanje relejem - Raspberry Pi

U ovom dijelu lekcije, dodat ćete relej svom Raspberry Pi-ju uz senzor vlažnosti tla i upravljati njime na temelju razine vlažnosti tla.

## Hardver

Raspberry Pi treba relej.

Relej koji ćete koristiti je [Grove relej](https://www.seeedstudio.com/Grove-Relay.html), relej koji je normalno otvoren (što znači da je izlazni krug otvoren ili prekinut kada nema signala poslanog na relej) i može podnijeti izlazne krugove do 250V i 10A.

Ovo je digitalni aktuator, pa se povezuje na digitalni pin na Grove Base Hat-u.

### Povezivanje releja

Grove relej može se povezati s Raspberry Pi-jem.

#### Zadatak

Povežite relej.

![Grove relej](../../../../../translated_images/hr/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Umetnite jedan kraj Grove kabela u utičnicu na releju. Kabel će ući samo na jedan način.

1. Dok je Raspberry Pi isključen, spojite drugi kraj Grove kabela na digitalnu utičnicu označenu **D5** na Grove Base Hat-u pričvršćenom na Pi. Ova utičnica je druga s lijeva, u redu utičnica pored GPIO pinova. Ostavite senzor vlažnosti tla povezan na utičnicu **A0**.

![Grove relej povezan na utičnicu D5, a senzor vlažnosti tla povezan na utičnicu A0](../../../../../translated_images/hr/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Umetnite senzor vlažnosti tla u tlo, ako već nije iz prethodne lekcije.

## Programiranje releja

Sada se Raspberry Pi može programirati za korištenje povezanog releja.

### Zadatak

Programirajte uređaj.

1. Uključite Pi i pričekajte da se pokrene.

1. Otvorite projekt `soil-moisture-sensor` iz prethodne lekcije u VS Code-u ako već nije otvoren. Dodavat ćete kod ovom projektu.

1. Dodajte sljedeći kod u datoteku `app.py` ispod postojećih uvoza:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Ova naredba uvozi `GroveRelay` iz Grove Python knjižnica za interakciju s Grove relejem.

1. Dodajte sljedeći kod ispod deklaracije klase `ADC` kako biste stvorili instancu `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ovo stvara relej koristeći pin **D5**, digitalni pin na koji ste spojili relej.

1. Kako biste testirali radi li relej, dodajte sljedeće u petlju `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod uključuje relej, čeka 0,5 sekundi, a zatim ga isključuje.

1. Pokrenite Python aplikaciju. Relej će se uključivati i isključivati svakih 10 sekundi, s pola sekunde kašnjenja između uključivanja i isključivanja. Čut ćete kako relej klikne pri uključivanju, a zatim pri isključivanju. LED na Grove ploči će svijetliti kada je relej uključen, a ugasiti se kada je isključen.

    ![Relej se uključuje i isključuje](../../../../../images/relay-turn-on-off.gif)

## Upravljanje relejem na temelju vlažnosti tla

Sada kada relej radi, može se kontrolirati u skladu s očitanjima vlažnosti tla.

### Zadatak

Upravljajte relejem.

1. Izbrišite 3 linije koda koje ste dodali za testiranje releja. Zamijenite ih sljedećim kodom:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ovaj kod provjerava razinu vlažnosti tla iz senzora vlažnosti tla. Ako je iznad 450, uključuje relej, a isključuje ga kada padne ispod 450.

    > 💁 Zapamtite, kapacitivni senzor vlažnosti tla očitava: što je niža razina vlažnosti tla, to je više vlage u tlu i obrnuto.

1. Pokrenite Python aplikaciju. Vidjet ćete kako se relej uključuje ili isključuje ovisno o razini vlažnosti tla. Isprobajte u suhom tlu, a zatim dodajte vodu.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Vaš program za upravljanje relejem pomoću senzora vlažnosti tla bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.