<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-24T22:40:59+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "fr"
}
-->
# Mesurer l'humidité du sol - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur d'humidité du sol capacitif à votre Raspberry Pi et lire les valeurs qu'il fournit.

## Matériel

Le Raspberry Pi nécessite un capteur d'humidité du sol capacitif.

Le capteur que vous utiliserez est un [Capteur d'humidité du sol capacitif](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), qui mesure l'humidité du sol en détectant la capacitance du sol, une propriété qui change en fonction de l'humidité. Lorsque l'humidité du sol augmente, la tension diminue.

C'est un capteur analogique, il utilise donc une broche analogique et le convertisseur analogique-numérique (ADC) 10 bits du Grove Base Hat sur le Pi pour convertir la tension en un signal numérique compris entre 1 et 1 023. Ce signal est ensuite envoyé via les broches GPIO du Pi.

### Connecter le capteur d'humidité du sol

Le capteur d'humidité du sol Grove peut être connecté au Raspberry Pi.

#### Tâche - connecter le capteur d'humidité du sol

Connectez le capteur d'humidité du sol.

![Un capteur d'humidité du sol Grove](../../../../../translated_images/fr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur d'humidité du sol. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à la prise analogique marquée **A0** sur le Grove Base Hat attaché au Pi. Cette prise est la deuxième à partir de la droite, sur la rangée de prises à côté des broches GPIO.

![Le capteur d'humidité du sol Grove connecté à la prise A0](../../../../../translated_images/fr/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. Insérez le capteur d'humidité du sol dans le sol. Il comporte une "ligne de position maximale" - une ligne blanche traversant le capteur. Insérez le capteur jusqu'à cette ligne, mais pas au-delà.

![Le capteur d'humidité du sol Grove dans le sol](../../../../../translated_images/fr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programmer le capteur d'humidité du sol

Le Raspberry Pi peut maintenant être programmé pour utiliser le capteur d'humidité du sol connecté.

### Tâche - programmer le capteur d'humidité du sol

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre.

1. Lancez VS Code, soit directement sur le Pi, soit en vous connectant via l'extension Remote SSH.

    > ⚠️ Vous pouvez vous référer [aux instructions pour configurer et lancer VS Code dans nightlight - leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Depuis le terminal, créez un nouveau dossier dans le répertoire personnel de l'utilisateur `pi` appelé `soil-moisture-sensor`. Créez un fichier dans ce dossier appelé `app.py`.

1. Ouvrez ce dossier dans VS Code.

1. Ajoutez le code suivant au fichier `app.py` pour importer les bibliothèques nécessaires :

    ```python
    import time
    from grove.adc import ADC
    ```

    L'instruction `import time` importe le module `time` qui sera utilisé plus tard dans cet exercice.

    L'instruction `from grove.adc import ADC` importe l'`ADC` des bibliothèques Python Grove. Cette bibliothèque contient du code pour interagir avec le convertisseur analogique-numérique sur le Pi Base Hat et lire les tensions des capteurs analogiques.

1. Ajoutez le code suivant en dessous pour créer une instance de la classe `ADC` :

    ```python
    adc = ADC()
    ```

1. Ajoutez une boucle infinie qui lit les données de cet ADC sur la broche A0 et écrit le résultat dans la console. Cette boucle peut ensuite attendre 10 secondes entre chaque lecture.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Exécutez l'application Python. Vous verrez les mesures d'humidité du sol s'afficher dans la console. Ajoutez de l'eau au sol ou retirez le capteur du sol et observez la variation des valeurs.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Dans l'exemple de sortie ci-dessus, vous pouvez voir la tension diminuer lorsque de l'eau est ajoutée.

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Votre programme pour le capteur d'humidité du sol a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.