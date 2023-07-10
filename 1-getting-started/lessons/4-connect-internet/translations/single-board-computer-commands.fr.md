# Contrôlez votre veilleuse à travers Internet - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous vous abonnerez aux commandes envoyées par un courtier MQTT à votre Raspberry Pi ou à un périphérique IoT virtuel.

## S'abonner aux commandes

L'étape suivante consiste à s'abonner aux commandes envoyées par le courtier MQTT et à y répondre.

### Tâche

S'abonner aux commandes.

1. Ouvrez le projet nightlight dans VS Code.

1. Si vous utilisez un appareil IoT virtuel, assurez-vous que le terminal exécute l'environnement virtuel. Si vous utilisez un Raspberry Pi, vous n'utiliserez pas d'environnement virtuel.

1. Ajoutez le code suivant après les définitions de `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    Le `server_command_topic` est le sujet MQTT auquel l'appareil s'abonnera pour recevoir les commandes des LED.

1. Ajoutez le code suivant juste au-dessus de la boucle principale, après la ligne `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message reçu:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Ce code définit une fonction, `handle_command`, qui lit un message en tant que document JSON et recherche la valeur de la propriété `led_on`. Si elle est définie à `True`, la LED est allumée, sinon elle est éteinte.

    Le client MQTT s'abonne au sujet sur lequel le serveur enverra des messages et définit la fonction `handle_command` à appeler lorsqu'un message est reçu.

    > 💁 Le gestionnaire `on_message` est appelé pour tous les sujets auxquels il s'est abonné. Si vous écrivez plus tard un code qui écoute plusieurs sujets, vous pouvez obtenir le sujet auquel le message a été envoyé à partir de l'objet `message` passé à la fonction handler.

1. Exécutez le code de la même manière que vous avez exécuté le code de la partie précédente de l'exercice. Si vous utilisez un dispositif IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que le capteur de lumière et la LED ont été créés sur les broches correctes.

1. Ajustez les niveaux de lumière détectés par votre appareil physique ou virtuel. Les messages reçus et les commandes envoyées seront écrits sur le terminal. La LED sera également allumée et éteinte en fonction du niveau de lumière.

> 💁 Vous trouverez ce code dans le dossier [code-commands/virtual-device](../code-commands/virtual-device) ou dans le dossier [code-commands/pi](../code-commands/pi).

😀 Vous avez réussi à coder votre appareil pour qu'il réponde aux commandes d'un courtier MQTT.
