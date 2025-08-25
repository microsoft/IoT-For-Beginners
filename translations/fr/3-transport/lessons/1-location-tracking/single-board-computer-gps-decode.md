<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T00:52:19+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "fr"
}
-->
# Décoder les données GPS - Matériel IoT Virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez décoder les messages NMEA lus depuis le capteur GPS par le Raspberry Pi ou le dispositif IoT virtuel, et extraire la latitude et la longitude.

## Décoder les données GPS

Une fois les données brutes NMEA lues depuis le port série, elles peuvent être décodées à l'aide d'une bibliothèque NMEA open source.

### Tâche - décoder les données GPS

Programmez le dispositif pour décoder les données GPS.

1. Ouvrez le projet de l'application `gps-sensor` s'il n'est pas déjà ouvert.

1. Installez le package Pip `pynmea2`. Ce package contient le code nécessaire pour décoder les messages NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Ajoutez le code suivant aux imports dans le fichier `app.py` pour importer le module `pynmea2` :

    ```python
    import pynmea2
    ```

1. Remplacez le contenu de la fonction `print_gps_data` par ce qui suit :

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Ce code utilise la bibliothèque `pynmea2` pour analyser la ligne lue depuis le port série UART.

    Si le type de phrase du message est `GGA`, alors il s'agit d'un message de position fixe, et il est traité. Les valeurs de latitude et de longitude sont extraites du message et converties en degrés décimaux à partir du format NMEA `(d)ddmm.mmmm`. La fonction `dm_to_sd` effectue cette conversion.

    La direction de la latitude est ensuite vérifiée, et si la latitude est au sud, la valeur est convertie en un nombre négatif. Il en va de même pour la longitude : si elle est à l'ouest, elle est convertie en un nombre négatif.

    Enfin, les coordonnées sont affichées sur la console, ainsi que le nombre de satellites utilisés pour obtenir la position.

1. Exécutez le code. Si vous utilisez un dispositif IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que les données GPS sont envoyées.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), ou dans le dossier [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Votre programme de capteur GPS avec décodage des données a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.