<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-24T21:14:05+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "fr"
}
-->
# Appelez votre détecteur d'objets depuis votre appareil IoT - Wio Terminal

Une fois votre détecteur d'objets publié, vous pouvez l'utiliser depuis votre appareil IoT.

## Copier le projet de classificateur d'images

La majorité de votre détecteur de stock est identique au classificateur d'images que vous avez créé dans une leçon précédente.

### Tâche - copier le projet de classificateur d'images

1. Connectez votre ArduCam à votre Wio Terminal, en suivant les étapes de la [leçon 2 du projet de fabrication](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Vous pourriez également vouloir fixer la caméra dans une position stable, par exemple, en suspendant le câble sur une boîte ou une boîte de conserve, ou en fixant la caméra à une boîte avec du ruban adhésif double face.

1. Créez un tout nouveau projet Wio Terminal en utilisant PlatformIO. Appelez ce projet `stock-counter`.

1. Reproduisez les étapes de la [leçon 2 du projet de fabrication](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pour capturer des images depuis la caméra.

1. Reproduisez les étapes de la [leçon 2 du projet de fabrication](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pour appeler le classificateur d'images. La majorité de ce code sera réutilisée pour détecter des objets.

## Modifier le code d'un classificateur à un détecteur d'images

Le code que vous avez utilisé pour classifier des images est très similaire à celui pour détecter des objets. La principale différence réside dans l'URL appelée, que vous avez obtenue depuis Custom Vision, et les résultats de cet appel.

### Tâche - modifier le code d'un classificateur à un détecteur d'images

1. Ajoutez la directive d'inclusion suivante en haut du fichier `main.cpp` :

    ```cpp
    #include <vector>
    ```

1. Renommez la fonction `classifyImage` en `detectStock`, à la fois le nom de la fonction et l'appel dans la fonction `buttonPressed`.

1. Au-dessus de la fonction `detectStock`, déclarez un seuil pour filtrer les détections ayant une faible probabilité :

    ```cpp
    const float threshold = 0.3f;
    ```

    Contrairement à un classificateur d'images qui ne retourne qu'un seul résultat par étiquette, le détecteur d'objets renverra plusieurs résultats. Il est donc nécessaire de filtrer ceux ayant une faible probabilité.

1. Au-dessus de la fonction `detectStock`, déclarez une fonction pour traiter les prédictions :

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Cette fonction prend une liste de prédictions et les affiche dans le moniteur série.

1. Dans la fonction `detectStock`, remplacez le contenu de la boucle `for` qui parcourt les prédictions par ce qui suit :

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Cette boucle parcourt les prédictions, compare la probabilité au seuil, et ajoute toutes les prédictions ayant une probabilité supérieure au seuil à une `list`, qui est ensuite transmise à la fonction `processPredictions`.

1. Téléversez et exécutez votre code. Pointez la caméra vers des objets sur une étagère et appuyez sur le bouton C. Vous verrez la sortie dans le moniteur série :

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Vous devrez peut-être ajuster le `threshold` à une valeur appropriée pour vos images.

    Vous pourrez voir l'image capturée, ainsi que ces valeurs dans l'onglet **Predictions** de Custom Vision.

    ![4 boîtes de concentré de tomate sur une étagère avec des prédictions pour les 4 détections de 35,8 %, 33,5 %, 25,7 % et 16,6 %](../../../../../translated_images/fr/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Vous pouvez trouver ce code dans le dossier [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Votre programme de compteur de stock est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.