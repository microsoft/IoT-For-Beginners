<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T10:10:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ro"
}
-->
# Controlează-ți lumina de noapte prin Internet - Wio Terminal

În această parte a lecției, vei abona dispozitivul Wio Terminal la comenzile trimise de un broker MQTT.

## Abonare la comenzi

Următorul pas este să te abonezi la comenzile trimise de brokerul MQTT și să răspunzi la acestea.

### Sarcină

Abonează-te la comenzi.

1. Deschide proiectul de lumină de noapte în VS Code.

1. Adaugă următorul cod la sfârșitul fișierului `config.h` pentru a defini numele topicului pentru comenzi:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` este topicul la care dispozitivul se va abona pentru a primi comenzi pentru LED.

1. Adaugă următoarea linie la sfârșitul funcției `reconnectMQTTClient` pentru a te abona la topicul de comenzi atunci când clientul MQTT este reconectat:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Adaugă următorul cod sub funcția `reconnectMQTTClient`.

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

    Această funcție va fi callback-ul pe care clientul MQTT îl va apela atunci când primește un mesaj de la server.

    Mesajul este primit ca un array de numere întregi nesemnate pe 8 biți, așa că trebuie convertit într-un array de caractere pentru a fi tratat ca text.

    Mesajul conține un document JSON, care este decodat folosind biblioteca ArduinoJson. Proprietatea `led_on` din documentul JSON este citită, iar în funcție de valoare, LED-ul este aprins sau stins.

1. Adaugă următorul cod în funcția `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Acest cod setează `clientCallback` ca fiind callback-ul care va fi apelat atunci când un mesaj este primit de la brokerul MQTT.

    > 💁 Handler-ul `clientCallback` este apelat pentru toate topicurile la care ești abonat. Dacă mai târziu scrii cod care ascultă mai multe topicuri, poți obține topicul la care a fost trimis mesajul din parametrul `topic` transmis funcției callback.

1. Încarcă codul pe dispozitivul Wio Terminal și folosește Serial Monitor pentru a vedea nivelurile de lumină trimise către brokerul MQTT.

1. Ajustează nivelurile de lumină detectate de dispozitivul tău fizic sau virtual. Vei vedea mesaje primite și comenzi trimise în terminal. De asemenea, vei observa cum LED-ul se aprinde și se stinge în funcție de nivelul de lumină.

> 💁 Poți găsi acest cod în folderul [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Ai reușit să programezi dispozitivul să răspundă la comenzile de la un broker MQTT.

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea umană realizată de profesioniști. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.