<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-24T21:06:53+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "fr"
}
-->
# Appelez votre détecteur d'objets depuis votre appareil IoT - Matériel IoT virtuel et Raspberry Pi

Une fois que votre détecteur d'objets a été publié, il peut être utilisé depuis votre appareil IoT.

## Copier le projet de classificateur d'images

La majorité de votre détecteur de stock est identique au classificateur d'images que vous avez créé dans une leçon précédente.

### Tâche - copier le projet de classificateur d'images

1. Créez un dossier appelé `stock-counter` soit sur votre ordinateur si vous utilisez un appareil IoT virtuel, soit sur votre Raspberry Pi. Si vous utilisez un appareil IoT virtuel, assurez-vous de configurer un environnement virtuel.

1. Configurez le matériel de la caméra.

    * Si vous utilisez un Raspberry Pi, vous devrez installer le PiCamera. Vous pourriez également vouloir fixer la caméra dans une position stable, par exemple, en suspendant le câble sur une boîte ou une canette, ou en fixant la caméra à une boîte avec du ruban adhésif double face.
    * Si vous utilisez un appareil IoT virtuel, vous devrez installer CounterFit et le shim CounterFit PyCamera. Si vous prévoyez d'utiliser des images fixes, capturez des images que votre détecteur d'objets n'a pas encore vues. Si vous utilisez votre webcam, assurez-vous qu'elle est positionnée de manière à voir le stock que vous détectez.

1. Reproduisez les étapes de la [leçon 2 du projet de fabrication](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pour capturer des images depuis la caméra.

1. Reproduisez les étapes de la [leçon 2 du projet de fabrication](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pour appeler le classificateur d'images. La majorité de ce code sera réutilisée pour détecter des objets.

## Modifier le code d'un classificateur à un détecteur d'images

Le code que vous avez utilisé pour classifier des images est très similaire à celui utilisé pour détecter des objets. La principale différence réside dans la méthode appelée sur le SDK Custom Vision et les résultats de cet appel.

### Tâche - modifier le code d'un classificateur à un détecteur d'images

1. Supprimez les trois lignes de code qui classifient l'image et traitent les prédictions :

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Supprimez ces trois lignes.

1. Ajoutez le code suivant pour détecter des objets dans l'image :

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ce code appelle la méthode `detect_image` sur le prédicteur pour exécuter le détecteur d'objets. Il rassemble ensuite toutes les prédictions avec une probabilité supérieure à un seuil, les affichant dans la console.

    Contrairement à un classificateur d'images qui ne retourne qu'un seul résultat par étiquette, le détecteur d'objets retournera plusieurs résultats. Par conséquent, ceux avec une faible probabilité doivent être filtrés.

1. Exécutez ce code, il capturera une image, l'enverra au détecteur d'objets et affichera les objets détectés. Si vous utilisez un appareil IoT virtuel, assurez-vous d'avoir une image appropriée définie dans CounterFit ou que votre webcam est sélectionnée. Si vous utilisez un Raspberry Pi, assurez-vous que votre caméra est orientée vers des objets sur une étagère.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Vous devrez peut-être ajuster le `threshold` à une valeur appropriée pour vos images.

    Vous pourrez voir l'image capturée et ces valeurs dans l'onglet **Predictions** de Custom Vision.

    ![4 boîtes de concentré de tomate sur une étagère avec des prédictions pour les 4 détections de 35,8 %, 33,5 %, 25,7 % et 16,6 %](../../../../../translated_images/fr/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Vous pouvez trouver ce code dans le dossier [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) ou [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Votre programme de comptage de stock a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.