<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T13:52:44+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije pretplatit ćete se na naredbe poslane s MQTT brokera na vaš Raspberry Pi ili virtualni IoT uređaj.

## Pretplata na naredbe

Sljedeći korak je pretplata na naredbe poslane s MQTT brokera i odgovaranje na njih.

### Zadatak

Pretplatite se na naredbe.

1. Otvorite projekt noćne lampe u VS Code-u.

1. Ako koristite virtualni IoT uređaj, provjerite je li terminal pokrenut u virtualnom okruženju. Ako koristite Raspberry Pi, nećete koristiti virtualno okruženje.

1. Dodajte sljedeći kod nakon definicija `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` je MQTT tema na koju će se uređaj pretplatiti kako bi primao naredbe za LED.

1. Dodajte sljedeći kod neposredno iznad glavne petlje, nakon linije `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Ovaj kod definira funkciju `handle_command` koja čita poruku kao JSON dokument i traži vrijednost svojstva `led_on`. Ako je postavljeno na `True`, LED se uključuje, inače se isključuje.

    MQTT klijent se pretplaćuje na temu na koju će poslužitelj slati poruke i postavlja funkciju `handle_command` da se pozove kada se primi poruka.

    > 💁 Obradnik `on_message` poziva se za sve teme na koje ste pretplaćeni. Ako kasnije napišete kod koji sluša više tema, možete dobiti temu na koju je poruka poslana iz objekta `message` proslijeđenog funkciji obrade.

1. Pokrenite kod na isti način kao što ste pokrenuli kod iz prethodnog dijela zadatka. Ako koristite virtualni IoT uređaj, provjerite je li CounterFit aplikacija pokrenuta i jesu li senzor svjetla i LED stvoreni na ispravnim pinovima.

1. Prilagodite razine svjetla koje detektira vaš fizički ili virtualni uređaj. Poruke koje se primaju i naredbe koje se šalju bit će ispisane u terminalu. LED će se također uključivati i isključivati ovisno o razini svjetla.

> 💁 Ovaj kod možete pronaći u mapi [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) ili mapi [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Uspješno ste programirali svoj uređaj da odgovara na naredbe s MQTT brokera.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.