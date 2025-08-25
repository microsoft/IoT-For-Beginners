<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-24T23:12:50+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Wio Terminal

Dans cette partie de la leçon, vous allez vous abonner aux commandes envoyées par un broker MQTT à votre Wio Terminal.

## S'abonner aux commandes

L'étape suivante consiste à s'abonner aux commandes envoyées par le broker MQTT et à y répondre.

### Tâche

Abonnez-vous aux commandes.

1. Ouvrez le projet de veilleuse dans VS Code.

1. Ajoutez le code suivant en bas du fichier `config.h` pour définir le nom du sujet des commandes :

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    Le `SERVER_COMMAND_TOPIC` est le sujet auquel l'appareil s'abonnera pour recevoir les commandes LED.

1. Ajoutez la ligne suivante à la fin de la fonction `reconnectMQTTClient` pour vous abonner au sujet des commandes lorsque le client MQTT est reconnecté :

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Ajoutez le code suivant sous la fonction `reconnectMQTTClient`.

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

    Cette fonction sera le callback que le client MQTT appellera lorsqu'il recevra un message du serveur.

    Le message est reçu sous forme de tableau d'entiers non signés de 8 bits, il doit donc être converti en tableau de caractères pour être traité comme du texte.

    Le message contient un document JSON, qui est décodé à l'aide de la bibliothèque ArduinoJson. La propriété `led_on` du document JSON est lue, et en fonction de sa valeur, la LED est allumée ou éteinte.

1. Ajoutez le code suivant à la fonction `createMQTTClient` :

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ce code définit le `clientCallback` comme le callback à appeler lorsqu'un message est reçu du broker MQTT.

    > 💁 Le gestionnaire `clientCallback` est appelé pour tous les sujets auxquels on s'est abonné. Si vous écrivez plus tard du code qui écoute plusieurs sujets, vous pouvez obtenir le sujet auquel le message a été envoyé à partir du paramètre `topic` passé à la fonction de callback.

1. Téléchargez le code sur votre Wio Terminal et utilisez le moniteur série pour voir les niveaux de lumière envoyés au broker MQTT.

1. Ajustez les niveaux de lumière détectés par votre appareil physique ou virtuel. Vous verrez des messages reçus et des commandes envoyées dans le terminal. Vous verrez également la LED s'allumer et s'éteindre en fonction du niveau de lumière.

> 💁 Vous pouvez trouver ce code dans le dossier [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Vous avez réussi à coder votre appareil pour répondre aux commandes d'un broker MQTT.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.