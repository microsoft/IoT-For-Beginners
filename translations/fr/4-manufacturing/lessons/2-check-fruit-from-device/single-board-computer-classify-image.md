<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-24T21:31:19+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "fr"
}
-->
# Classifier une image - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez envoyer l'image capturée par la caméra au service Custom Vision pour la classifier.

## Envoyer des images à Custom Vision

Le service Custom Vision dispose d'un SDK Python que vous pouvez utiliser pour classifier des images.

### Tâche - envoyer des images à Custom Vision

1. Ouvrez le dossier `fruit-quality-detector` dans VS Code. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'environnement virtuel est actif dans le terminal.

1. Le SDK Python pour envoyer des images à Custom Vision est disponible sous forme de package Pip. Installez-le avec la commande suivante :

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Ajoutez les instructions d'importation suivantes en haut du fichier `app.py` :

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Cela importe certains modules des bibliothèques Custom Vision, l'un pour s'authentifier avec la clé de prédiction, et l'autre pour fournir une classe client de prédiction qui peut appeler Custom Vision.

1. Ajoutez le code suivant à la fin du fichier :

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Remplacez `<prediction_url>` par l'URL que vous avez copiée depuis la boîte de dialogue *Prediction URL* plus tôt dans cette leçon. Remplacez `<prediction key>` par la clé de prédiction que vous avez copiée depuis la même boîte de dialogue.

1. L'URL de prédiction fournie par la boîte de dialogue *Prediction URL* est conçue pour être utilisée lors de l'appel direct au point de terminaison REST. Le SDK Python utilise différentes parties de l'URL à différents endroits. Ajoutez le code suivant pour diviser cette URL en parties nécessaires :

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Cela divise l'URL, en extrayant le point de terminaison `https://<location>.api.cognitive.microsoft.com`, l'ID du projet, et le nom de l'itération publiée.

1. Créez un objet prédicteur pour effectuer la prédiction avec le code suivant :

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Les `prediction_credentials` encapsulent la clé de prédiction. Ces informations sont ensuite utilisées pour créer un objet client de prédiction pointant vers le point de terminaison.

1. Envoyez l'image à Custom Vision en utilisant le code suivant :

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Cela remet l'image au début, puis l'envoie au client de prédiction.

1. Enfin, affichez les résultats avec le code suivant :

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Cela parcourra toutes les prédictions retournées et les affichera dans le terminal. Les probabilités retournées sont des nombres à virgule flottante entre 0 et 1, où 0 correspond à 0 % de chance de correspondance avec le tag, et 1 correspond à 100 % de chance.

    > 💁 Les classificateurs d'images retourneront les pourcentages pour tous les tags utilisés. Chaque tag aura une probabilité indiquant que l'image correspond à ce tag.

1. Exécutez votre code, avec votre caméra pointée sur un fruit, ou un ensemble d'images approprié, ou un fruit visible sur votre webcam si vous utilisez un matériel IoT virtuel. Vous verrez la sortie dans la console :

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Vous pourrez voir l'image qui a été prise, ainsi que ces valeurs dans l'onglet **Predictions** de Custom Vision.

    ![Une banane dans Custom Vision prédite comme mûre à 56,8 % et non mûre à 43,1 %](../../../../../translated_images/fr/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Vous pouvez trouver ce code dans le dossier [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ou [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Votre programme de classification de la qualité des fruits est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.