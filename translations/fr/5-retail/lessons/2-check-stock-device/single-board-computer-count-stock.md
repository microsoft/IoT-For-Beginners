<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-24T21:12:52+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "fr"
}
-->
# Compter le stock depuis votre appareil IoT - Matériel IoT virtuel et Raspberry Pi

Une combinaison des prédictions et de leurs boîtes englobantes peut être utilisée pour compter le stock dans une image.

## Afficher les boîtes englobantes

Comme étape utile de débogage, vous pouvez non seulement imprimer les boîtes englobantes, mais aussi les dessiner sur l'image qui a été enregistrée sur le disque lorsqu'une image a été capturée.

### Tâche - imprimer les boîtes englobantes

1. Assurez-vous que le projet `stock-counter` est ouvert dans VS Code et que l'environnement virtuel est activé si vous utilisez un appareil IoT virtuel.

1. Modifiez l'instruction `print` dans la boucle `for` comme suit pour imprimer les boîtes englobantes dans la console :

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Exécutez l'application avec la caméra pointée vers du stock sur une étagère. Les boîtes englobantes seront imprimées dans la console, avec des valeurs de gauche, haut, largeur et hauteur allant de 0 à 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tâche - dessiner les boîtes englobantes sur l'image

1. Le package Pip [Pillow](https://pypi.org/project/Pillow/) peut être utilisé pour dessiner sur des images. Installez-le avec la commande suivante :

    ```sh
    pip3 install pillow
    ```

    Si vous utilisez un appareil IoT virtuel, assurez-vous d'exécuter cette commande depuis l'environnement virtuel activé.

1. Ajoutez l'instruction d'import suivante en haut du fichier `app.py` :

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Cela importe le code nécessaire pour modifier l'image.

1. Ajoutez le code suivant à la fin du fichier `app.py` :

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Ce code ouvre l'image qui a été enregistrée précédemment pour la modifier. Il parcourt ensuite les prédictions, récupère les boîtes englobantes et calcule la coordonnée en bas à droite en utilisant les valeurs des boîtes englobantes allant de 0 à 1. Ces valeurs sont ensuite converties en coordonnées d'image en les multipliant par la dimension correspondante de l'image. Par exemple, si la valeur de gauche était 0.5 sur une image de 600 pixels de large, cela la convertirait en 300 (0.5 x 600 = 300).

    Chaque boîte englobante est dessinée sur l'image avec une ligne rouge. Enfin, l'image modifiée est enregistrée, remplaçant l'image originale.

1. Exécutez l'application avec la caméra pointée vers du stock sur une étagère. Vous verrez le fichier `image.jpg` dans l'explorateur de VS Code, et vous pourrez le sélectionner pour voir les boîtes englobantes.

    ![4 boîtes de concentré de tomate avec des boîtes englobantes autour de chaque boîte](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.fr.jpg)

## Compter le stock

Dans l'image ci-dessus, les boîtes englobantes ont un léger chevauchement. Si ce chevauchement était beaucoup plus important, les boîtes englobantes pourraient indiquer le même objet. Pour compter correctement les objets, vous devez ignorer les boîtes avec un chevauchement significatif.

### Tâche - compter le stock en ignorant le chevauchement

1. Le package Pip [Shapely](https://pypi.org/project/Shapely/) peut être utilisé pour calculer l'intersection. Si vous utilisez un Raspberry Pi, vous devrez d'abord installer une dépendance de bibliothèque :

    ```sh
    sudo apt install libgeos-dev
    ```

1. Installez le package Pip Shapely :

    ```sh
    pip3 install shapely
    ```

    Si vous utilisez un appareil IoT virtuel, assurez-vous d'exécuter cette commande depuis l'environnement virtuel activé.

1. Ajoutez l'instruction d'import suivante en haut du fichier `app.py` :

    ```python
    from shapely.geometry import Polygon
    ```

    Cela importe le code nécessaire pour créer des polygones afin de calculer le chevauchement.

1. Au-dessus du code qui dessine les boîtes englobantes, ajoutez le code suivant :

    ```python
    overlap_threshold = 0.20
    ```

    Cela définit le pourcentage de chevauchement autorisé avant que les boîtes englobantes ne soient considérées comme représentant le même objet. 0.20 définit un chevauchement de 20%.

1. Pour calculer le chevauchement avec Shapely, les boîtes englobantes doivent être converties en polygones Shapely. Ajoutez la fonction suivante pour le faire :

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Cela crée un polygone en utilisant la boîte englobante d'une prédiction.

1. La logique pour supprimer les objets qui se chevauchent implique de comparer toutes les boîtes englobantes et, si une paire de prédictions a des boîtes englobantes qui se chevauchent au-delà du seuil, de supprimer l'une des prédictions. Pour comparer toutes les prédictions, vous comparez la prédiction 1 avec 2, 3, 4, etc., puis 2 avec 3, 4, etc. Le code suivant fait cela :

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Le chevauchement est calculé en utilisant la méthode `Polygon.intersection` de Shapely qui retourne un polygone représentant le chevauchement. La surface est ensuite calculée à partir de ce polygone. Ce seuil de chevauchement n'est pas une valeur absolue, mais doit être un pourcentage de la boîte englobante, donc la plus petite boîte englobante est trouvée, et le seuil de chevauchement est utilisé pour calculer quelle surface le chevauchement peut avoir pour ne pas dépasser le seuil de pourcentage de chevauchement de la plus petite boîte englobante. Si le chevauchement dépasse cela, la prédiction est marquée pour suppression.

    Une fois qu'une prédiction a été marquée pour suppression, elle n'a plus besoin d'être vérifiée, donc la boucle interne se termine pour vérifier la prédiction suivante. Vous ne pouvez pas supprimer des éléments d'une liste tout en la parcourant, donc les boîtes englobantes qui se chevauchent au-delà du seuil sont ajoutées à la liste `to_delete`, puis supprimées à la fin.

    Enfin, le nombre d'objets est imprimé dans la console. Cela pourrait ensuite être envoyé à un service IoT pour alerter si les niveaux de stock sont bas. Tout ce code est exécuté avant que les boîtes englobantes ne soient dessinées, donc vous verrez les prédictions de stock sans chevauchements sur les images générées.

    > 💁 Ceci est une méthode très simpliste pour supprimer les chevauchements, en supprimant simplement le premier dans une paire qui se chevauche. Pour du code en production, vous voudriez ajouter plus de logique ici, comme prendre en compte les chevauchements entre plusieurs objets, ou si une boîte englobante est contenue dans une autre.

1. Exécutez l'application avec la caméra pointée vers du stock sur une étagère. La sortie indiquera le nombre de boîtes englobantes sans chevauchements qui dépassent le seuil. Essayez d'ajuster la valeur `overlap_threshold` pour voir des prédictions ignorées.

> 💁 Vous pouvez trouver ce code dans le dossier [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) ou [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Votre programme de comptage de stock a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.