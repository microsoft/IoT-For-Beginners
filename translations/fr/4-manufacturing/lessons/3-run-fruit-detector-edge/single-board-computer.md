<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-24T21:47:47+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "fr"
}
-->
# Classifier une image à l'aide d'un classificateur d'images basé sur IoT Edge - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez utiliser le classificateur d'images fonctionnant sur l'appareil IoT Edge.

## Utiliser le classificateur IoT Edge

L'appareil IoT peut être redirigé pour utiliser le classificateur d'images IoT Edge. L'URL du classificateur d'images est `http://<adresse IP ou nom>/image`, en remplaçant `<adresse IP ou nom>` par l'adresse IP ou le nom d'hôte de l'ordinateur exécutant IoT Edge.

La bibliothèque Python pour Custom Vision fonctionne uniquement avec des modèles hébergés dans le cloud, et non avec des modèles hébergés sur IoT Edge. Cela signifie que vous devrez utiliser l'API REST pour appeler le classificateur.

### Tâche - utiliser le classificateur IoT Edge

1. Ouvrez le projet `fruit-quality-detector` dans VS Code s'il n'est pas déjà ouvert. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'environnement virtuel est activé.

1. Ouvrez le fichier `app.py`, et supprimez les instructions d'importation de `azure.cognitiveservices.vision.customvision.prediction` et `msrest.authentication`.

1. Ajoutez l'importation suivante en haut du fichier :

    ```python
    import requests
    ```

1. Supprimez tout le code après que l'image soit enregistrée dans un fichier, à partir de `image_file.write(image.read())` jusqu'à la fin du fichier.

1. Ajoutez le code suivant à la fin du fichier :

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Remplacez `<URL>` par l'URL de votre classificateur.

    Ce code effectue une requête POST REST au classificateur, en envoyant l'image comme corps de la requête. Les résultats reviennent sous forme de JSON, qui est décodé pour afficher les probabilités.

1. Exécutez votre code, en pointant votre caméra vers des fruits, ou un ensemble d'images approprié, ou des fruits visibles sur votre webcam si vous utilisez un matériel IoT virtuel. Vous verrez la sortie dans la console :

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ou [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Votre programme de classification de la qualité des fruits a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.