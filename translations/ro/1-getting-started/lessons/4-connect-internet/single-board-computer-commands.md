<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T10:13:38+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "ro"
}
-->
# Controlează lumina de noapte prin Internet - Hardware IoT virtual și Raspberry Pi

În această parte a lecției, vei abona dispozitivul tău Raspberry Pi sau IoT virtual la comenzile trimise de un broker MQTT.

## Abonare la comenzi

Următorul pas este să te abonezi la comenzile trimise de brokerul MQTT și să răspunzi la acestea.

### Sarcină

Abonează-te la comenzi.

1. Deschide proiectul de lumină de noapte în VS Code.

1. Dacă folosești un dispozitiv IoT virtual, asigură-te că terminalul rulează mediul virtual. Dacă folosești un Raspberry Pi, nu vei folosi un mediu virtual.

1. Adaugă următorul cod după definițiile `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` este subiectul MQTT la care dispozitivul se va abona pentru a primi comenzi pentru LED.

1. Adaugă următorul cod chiar deasupra buclei principale, după linia `mqtt_client.loop_start()`:

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

    Acest cod definește o funcție, `handle_command`, care citește un mesaj ca document JSON și caută valoarea proprietății `led_on`. Dacă este setată la `True`, LED-ul este aprins, altfel este stins.

    Clientul MQTT se abonează la subiectul pe care serverul va trimite mesaje și setează funcția `handle_command` să fie apelată atunci când un mesaj este primit.

    > 💁 Handler-ul `on_message` este apelat pentru toate subiectele la care te-ai abonat. Dacă mai târziu scrii cod care ascultă mai multe subiecte, poți obține subiectul la care a fost trimis mesajul din obiectul `message` transmis funcției handler.

1. Rulează codul în același mod în care ai rulat codul din partea anterioară a temei. Dacă folosești un dispozitiv IoT virtual, asigură-te că aplicația CounterFit este pornită și senzorul de lumină și LED-ul au fost create pe pinii corecți.

1. Ajustează nivelurile de lumină detectate de dispozitivul tău fizic sau virtual. Mesajele primite și comenzile trimise vor fi scrise în terminal. LED-ul va fi aprins și stins în funcție de nivelul de lumină.

> 💁 Poți găsi acest cod în folderul [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) sau în folderul [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Ai reușit să programezi dispozitivul tău să răspundă la comenzile de la un broker MQTT.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.