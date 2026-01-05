<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-24T21:11:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "fr"
}
-->
# Compter le stock depuis votre appareil IoT - Wio Terminal

Une combinaison des prédictions et de leurs boîtes englobantes peut être utilisée pour compter le stock dans une image.

## Compter le stock

![4 boîtes de concentré de tomate avec des boîtes englobantes autour de chaque boîte](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.fr.jpg)

Dans l'image ci-dessus, les boîtes englobantes ont un léger chevauchement. Si ce chevauchement était beaucoup plus important, les boîtes englobantes pourraient indiquer le même objet. Pour compter correctement les objets, vous devez ignorer les boîtes avec un chevauchement significatif.

### Tâche - compter le stock en ignorant le chevauchement

1. Ouvrez votre projet `stock-counter` s'il n'est pas déjà ouvert.

1. Au-dessus de la fonction `processPredictions`, ajoutez le code suivant :

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Cela définit le pourcentage de chevauchement autorisé avant que les boîtes englobantes ne soient considérées comme le même objet. 0.20 définit un chevauchement de 20 %.

1. En dessous de cela, et au-dessus de la fonction `processPredictions`, ajoutez le code suivant pour calculer le chevauchement entre deux rectangles :

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Ce code définit une structure `Point` pour stocker les points sur l'image, et une structure `Rect` pour définir un rectangle à l'aide d'une coordonnée en haut à gauche et en bas à droite. Il définit ensuite une fonction `area` qui calcule la surface d'un rectangle à partir d'une coordonnée en haut à gauche et en bas à droite.

    Ensuite, il définit une fonction `overlappingArea` qui calcule la surface de chevauchement de 2 rectangles. S'ils ne se chevauchent pas, elle retourne 0.

1. En dessous de la fonction `overlappingArea`, déclarez une fonction pour convertir une boîte englobante en un `Rect` :

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Cela prend une prédiction de l'objet détecteur, extrait la boîte englobante et utilise les valeurs de la boîte englobante pour définir un rectangle. Le côté droit est calculé à partir de la gauche plus la largeur. Le bas est calculé comme le haut plus la hauteur.

1. Les prédictions doivent être comparées entre elles, et si 2 prédictions ont un chevauchement supérieur au seuil, l'une d'elles doit être supprimée. Le seuil de chevauchement est un pourcentage, donc il doit être multiplié par la taille de la plus petite boîte englobante pour vérifier que le chevauchement dépasse le pourcentage donné de la boîte englobante, et non le pourcentage donné de l'image entière. Commencez par supprimer le contenu de la fonction `processPredictions`.

1. Ajoutez ce qui suit à la fonction `processPredictions` vide :

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Ce code déclare un vecteur pour stocker les prédictions qui ne se chevauchent pas. Il parcourt ensuite toutes les prédictions, créant un `Rect` à partir de la boîte englobante.

    Ensuite, ce code parcourt les prédictions restantes, en commençant par celle qui suit la prédiction actuelle. Cela empêche les prédictions d'être comparées plus d'une fois - une fois que 1 et 2 ont été comparées, il n'est pas nécessaire de comparer 2 avec 1, seulement avec 3, 4, etc.

    Pour chaque paire de prédictions, la surface de chevauchement est calculée. Elle est ensuite comparée à la surface de la plus petite boîte englobante - si le chevauchement dépasse le pourcentage seuil de la plus petite boîte englobante, la prédiction est marquée comme non validée. Si après avoir comparé tous les chevauchements, la prédiction passe les vérifications, elle est ajoutée à la collection `passed_predictions`.

    > 💁 C'est une méthode très simpliste pour supprimer les chevauchements, en supprimant simplement la première dans une paire qui se chevauche. Pour du code en production, vous voudriez ajouter plus de logique ici, comme prendre en compte les chevauchements entre plusieurs objets, ou si une boîte englobante est contenue dans une autre.

1. Après cela, ajoutez le code suivant pour envoyer les détails des prédictions validées au moniteur série :

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Ce code parcourt les prédictions validées et imprime leurs détails sur le moniteur série.

1. En dessous de cela, ajoutez du code pour imprimer le nombre d'articles comptés sur le moniteur série :

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Cela pourrait ensuite être envoyé à un service IoT pour alerter si les niveaux de stock sont bas.

1. Téléchargez et exécutez votre code. Pointez la caméra vers des objets sur une étagère et appuyez sur le bouton C. Essayez d'ajuster la valeur `overlap_threshold` pour voir les prédictions ignorées.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Votre programme de compteur de stock a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.