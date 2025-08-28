<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T13:52:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Virtualni IoT uređaj i Raspberry Pi

U ovom dijelu lekcije, poslat ćete telemetriju s razinama svjetlosti s vašeg Raspberry Pi uređaja ili virtualnog IoT uređaja na MQTT broker.

## Slanje telemetrije

Sljedeći korak je kreiranje JSON dokumenta s telemetrijom i njegovo slanje na MQTT broker.

### Zadatak

Pošaljite telemetriju na MQTT broker.

1. Otvorite projekt noćne lampe u VS Code-u.

1. Ako koristite virtualni IoT uređaj, provjerite je li terminal pokrenut u virtualnom okruženju. Ako koristite Raspberry Pi, nećete koristiti virtualno okruženje.

1. Dodajte sljedeći import na vrh datoteke `app.py`:

    ```python
    import json
    ```

    Biblioteka `json` koristi se za kodiranje telemetrije u JSON dokument.

1. Dodajte sljedeće nakon deklaracije `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` je MQTT tema na koju će uređaj objavljivati razine svjetlosti.

1. Zamijenite sadržaj petlje `while True:` na kraju datoteke sa sljedećim:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ovaj kod pakira razinu svjetlosti u JSON dokument i objavljuje ga na MQTT broker. Zatim se program pauzira kako bi se smanjila učestalost slanja poruka.

1. Pokrenite kod na isti način kao što ste pokrenuli kod iz prethodnog dijela zadatka. Ako koristite virtualni IoT uređaj, provjerite je li aplikacija CounterFit pokrenuta i jesu li senzor svjetlosti i LED kreirani na odgovarajućim pinovima.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ili mapi [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Uspješno ste poslali telemetriju s vašeg uređaja.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.