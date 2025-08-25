<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-24T23:00:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez vous abonner aux commandes envoyées par un broker MQTT à votre Raspberry Pi ou à votre appareil IoT virtuel.

## S'abonner aux commandes

L'étape suivante consiste à s'abonner aux commandes envoyées par le broker MQTT et à y répondre.

### Tâche

Abonnez-vous aux commandes.

1. Ouvrez le projet de veilleuse dans VS Code.

1. Si vous utilisez un appareil IoT virtuel, assurez-vous que le terminal exécute l'environnement virtuel. Si vous utilisez un Raspberry Pi, vous n'aurez pas besoin d'utiliser un environnement virtuel.

1. Ajoutez le code suivant après les définitions de `client_telemetry_topic` :

    ```python
    server_command_topic = id + '/commands'
    ```

    Le `server_command_topic` est le sujet MQTT auquel l'appareil s'abonnera pour recevoir les commandes LED.

1. Ajoutez le code suivant juste au-dessus de la boucle principale, après la ligne `mqtt_client.loop_start()` :

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

    Ce code définit une fonction, `handle_command`, qui lit un message sous forme de document JSON et recherche la valeur de la propriété `led_on`. Si elle est définie sur `True`, la LED s'allume, sinon elle s'éteint.

    Le client MQTT s'abonne au sujet sur lequel le serveur enverra des messages et configure la fonction `handle_command` pour qu'elle soit appelée lorsqu'un message est reçu.

    > 💁 Le gestionnaire `on_message` est appelé pour tous les sujets auxquels on s'est abonné. Si vous écrivez plus tard du code qui écoute plusieurs sujets, vous pouvez obtenir le sujet auquel le message a été envoyé à partir de l'objet `message` passé à la fonction de gestion.

1. Exécutez le code de la même manière que vous avez exécuté le code de la partie précédente de l'exercice. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que le capteur de lumière et la LED ont été créés sur les broches correctes.

1. Ajustez les niveaux de lumière détectés par votre appareil physique ou virtuel. Les messages reçus et les commandes envoyées seront affichés dans le terminal. La LED s'allumera et s'éteindra également en fonction du niveau de lumière.

> 💁 Vous pouvez trouver ce code dans le dossier [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) ou dans le dossier [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Vous avez réussi à coder votre appareil pour qu'il réponde aux commandes d'un broker MQTT.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.