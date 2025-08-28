<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T15:14:12+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "hr"
}
-->
# Objavljivanje temperature - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije objavit ćete vrijednosti temperature koje detektira Raspberry Pi ili Virtualni IoT uređaj putem MQTT-a kako bi se kasnije mogle koristiti za izračun GDD-a.

## Objavljivanje temperature

Nakon što se temperatura očita, može se objaviti putem MQTT-a nekom 'server' kodu koji će očitati vrijednosti i pohraniti ih za kasniju upotrebu u izračunu GDD-a.

### Zadatak - objavite temperaturu

Programirajte uređaj da objavi podatke o temperaturi.

1. Otvorite projekt aplikacije `temperature-sensor` ako već nije otvoren.

1. Ponovite korake koje ste radili u lekciji 4 za povezivanje s MQTT-om i slanje telemetrije. Koristit ćete isti javni Mosquitto broker.

    Koraci za to su:

    - Dodajte MQTT pip paket
    - Dodajte kod za povezivanje s MQTT brokerom
    - Dodajte kod za objavljivanje telemetrije

    > ⚠️ Pogledajte [upute za povezivanje s MQTT-om](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) i [upute za slanje telemetrije](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) iz lekcije 4 ako je potrebno.

1. Provjerite da `client_name` odražava naziv ovog projekta:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Za telemetriju, umjesto slanja vrijednosti svjetla, pošaljite vrijednost temperature očitanu s DHT senzora u svojstvu JSON dokumenta nazvanom `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Vrijednost temperature ne treba se očitavati često - neće se puno mijenjati u kratkom vremenskom razdoblju, pa postavite `time.sleep` na 10 minuta:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkcija `sleep` uzima vrijeme u sekundama, pa je za lakše čitanje vrijednost proslijeđena kao rezultat izračuna. 60 sekundi u minuti, dakle 10 x (60 sekundi u minuti) daje kašnjenje od 10 minuta.

1. Pokrenite kod na isti način kao što ste pokrenuli kod iz prethodnog dijela zadatka. Ako koristite virtualni IoT uređaj, provjerite da je CounterFit aplikacija pokrenuta i da su senzori za vlagu i temperaturu kreirani na ispravnim pinovima.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) ili u mapi [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Uspješno ste objavili temperaturu kao telemetriju s vašeg uređaja.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.