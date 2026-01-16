<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-25T00:46:01+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "fr"
}
-->
# Lire les données GPS - Matériel IoT Virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur GPS à votre appareil IoT virtuel et lire les valeurs qu'il fournit.

## Matériel Virtuel

L'appareil IoT virtuel utilisera un capteur GPS simulé accessible via UART par un port série.

Un capteur GPS physique possède une antenne pour capter les ondes radio des satellites GPS et convertir les signaux GPS en données GPS. La version virtuelle simule cela en vous permettant soit de définir une latitude et une longitude, d'envoyer des phrases NMEA brutes, soit de télécharger un fichier GPX contenant plusieurs emplacements qui peuvent être retournés séquentiellement.

> 🎓 Les phrases NMEA seront abordées plus tard dans cette leçon.

### Ajouter le capteur à CounterFit

Pour utiliser un capteur GPS virtuel, vous devez en ajouter un à l'application CounterFit.

#### Tâche - ajouter le capteur à CounterFit

Ajoutez le capteur GPS à l'application CounterFit.

1. Créez une nouvelle application Python sur votre ordinateur dans un dossier nommé `gps-sensor` avec un fichier unique appelé `app.py`, ainsi qu'un environnement virtuel Python, et ajoutez les packages pip de CounterFit.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer et configurer un projet Python CounterFit dans la leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installez un package Pip supplémentaire pour installer un shim CounterFit qui peut communiquer avec des capteurs basés sur UART via une connexion série. Assurez-vous de l'installer depuis un terminal avec l'environnement virtuel activé.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Assurez-vous que l'application web CounterFit est en cours d'exécution.

1. Créez un capteur GPS :

    1. Dans la boîte *Create sensor* du volet *Sensors*, déroulez la boîte *Sensor type* et sélectionnez *UART GPS*.

    1. Laissez le *Port* défini sur */dev/ttyAMA0*.

    1. Sélectionnez le bouton **Add** pour créer le capteur GPS sur le port `/dev/ttyAMA0`.

    ![Les paramètres du capteur GPS](../../../../../translated_images/fr/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Le capteur GPS sera créé et apparaîtra dans la liste des capteurs.

    ![Le capteur GPS créé](../../../../../translated_images/fr/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programmer le capteur GPS

L'appareil IoT virtuel peut maintenant être programmé pour utiliser le capteur GPS virtuel.

### Tâche - programmer le capteur GPS

Programmez l'application du capteur GPS.

1. Assurez-vous que l'application `gps-sensor` est ouverte dans VS Code.

1. Ouvrez le fichier `app.py`.

1. Ajoutez le code suivant en haut de `app.py` pour connecter l'application à CounterFit :

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ajoutez le code suivant en dessous pour importer des bibliothèques nécessaires, y compris la bibliothèque pour le port série CounterFit :

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Ce code importe le module `serial` du package Pip `counterfit_shims_serial`. Il se connecte ensuite au port série `/dev/ttyAMA0` - c'est l'adresse du port série utilisé par le capteur GPS virtuel pour son port UART.

1. Ajoutez le code suivant en dessous pour lire depuis le port série et afficher les valeurs dans la console :

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Une fonction appelée `print_gps_data` est définie pour afficher la ligne passée en paramètre dans la console.

    Ensuite, le code boucle indéfiniment, lisant autant de lignes de texte que possible depuis le port série à chaque itération. Il appelle la fonction `print_gps_data` pour chaque ligne.

    Une fois toutes les données lues, la boucle attend 1 seconde avant de recommencer.

1. Exécutez ce code, en vous assurant d'utiliser un terminal différent de celui où l'application CounterFit est en cours d'exécution, afin que l'application CounterFit reste active.

1. Depuis l'application CounterFit, modifiez la valeur du capteur GPS. Vous pouvez le faire de l'une des manières suivantes :

    * Définissez la **Source** sur `Lat/Lon`, et spécifiez une latitude, une longitude et un nombre de satellites utilisés pour obtenir la position GPS. Cette valeur sera envoyée une seule fois, alors cochez la case **Repeat** pour que les données se répètent toutes les secondes.

      ![Le capteur GPS avec lat lon sélectionné](../../../../../translated_images/fr/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Définissez la **Source** sur `NMEA` et ajoutez des phrases NMEA dans la boîte de texte. Toutes ces valeurs seront envoyées, avec un délai d'une seconde avant chaque nouvelle phrase GGA (fixation de position).

      ![Le capteur GPS avec des phrases NMEA définies](../../../../../translated_images/fr/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Vous pouvez utiliser un outil comme [nmeagen.org](https://www.nmeagen.org) pour générer ces phrases en dessinant sur une carte. Ces valeurs seront envoyées une seule fois, alors cochez la case **Repeat** pour que les données se répètent une seconde après leur envoi complet.

    * Définissez la **Source** sur fichier GPX, et téléchargez un fichier GPX contenant des emplacements de piste. Vous pouvez télécharger des fichiers GPX depuis plusieurs sites populaires de cartographie et de randonnée, tels que [AllTrails](https://www.alltrails.com/). Ces fichiers contiennent plusieurs emplacements GPS sous forme de parcours, et le capteur GPS renverra chaque nouvel emplacement à des intervalles d'une seconde.

      ![Le capteur GPS avec un fichier GPX défini](../../../../../translated_images/fr/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Ces valeurs seront envoyées une seule fois, alors cochez la case **Repeat** pour que les données se répètent une seconde après leur envoi complet.

    Une fois que vous avez configuré les paramètres GPS, sélectionnez le bouton **Set** pour valider ces valeurs dans le capteur.

1. Vous verrez la sortie brute du capteur GPS, quelque chose comme ceci :

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Votre programme de capteur GPS a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.