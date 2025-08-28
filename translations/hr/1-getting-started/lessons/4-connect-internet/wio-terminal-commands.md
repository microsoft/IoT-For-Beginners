<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T13:49:31+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Wio Terminal

U ovom dijelu lekcije, pretplatit ćete se na naredbe poslane s MQTT brokera na vaš Wio Terminal.

## Pretplata na naredbe

Sljedeći korak je pretplata na naredbe poslane s MQTT brokera i odgovaranje na njih.

### Zadatak

Pretplatite se na naredbe.

1. Otvorite projekt noćne lampe u VS Code-u.

1. Dodajte sljedeći kod na dno datoteke `config.h` kako biste definirali naziv teme za naredbe:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` je tema na koju će se uređaj pretplatiti kako bi primio naredbe za LED.

1. Dodajte sljedeći redak na kraj funkcije `reconnectMQTTClient` kako biste se pretplatili na temu naredbi kada se MQTT klijent ponovno poveže:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Dodajte sljedeći kod ispod funkcije `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Ova funkcija bit će povratni poziv koji MQTT klijent poziva kada primi poruku s poslužitelja.

    Poruka se prima kao niz neoznačenih 8-bitnih cijelih brojeva, pa je potrebno pretvoriti je u niz znakova kako bi se tretirala kao tekst.

    Poruka sadrži JSON dokument, koji se dekodira pomoću ArduinoJson biblioteke. Svojstvo `led_on` iz JSON dokumenta se čita, i ovisno o vrijednosti LED se uključuje ili isključuje.

1. Dodajte sljedeći kod u funkciju `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ovaj kod postavlja `clientCallback` kao povratni poziv koji će se pozvati kada se primi poruka s MQTT brokera.

    > 💁 Povratni poziv `clientCallback` se poziva za sve teme na koje ste pretplaćeni. Ako kasnije napišete kod koji sluša više tema, možete dobiti temu na koju je poruka poslana iz parametra `topic` koji se prosljeđuje povratnom pozivu.

1. Prenesite kod na svoj Wio Terminal i koristite Serial Monitor za pregled razina svjetlosti koje se šalju MQTT brokeru.

1. Prilagodite razine svjetlosti koje detektira vaš fizički ili virtualni uređaj. Vidjet ćete poruke koje se primaju i naredbe koje se šalju u terminalu. Također ćete vidjeti kako se LED uključuje i isključuje ovisno o razini svjetlosti.

> 💁 Ovaj kod možete pronaći u mapi [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Uspješno ste programirali svoj uređaj da odgovara na naredbe s MQTT brokera.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva pogrešna shvaćanja ili tumačenja koja proizlaze iz korištenja ovog prijevoda.