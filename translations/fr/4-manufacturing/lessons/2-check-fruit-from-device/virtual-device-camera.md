# Capturer une image - Matériel IoT Virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur de caméra à votre appareil IoT virtuel et lire des images à partir de celui-ci.

## Matériel

L'appareil IoT virtuel utilisera une caméra simulée qui envoie soit des images provenant de fichiers, soit de votre webcam.

### Ajouter la caméra à CounterFit

Pour utiliser une caméra virtuelle, vous devez en ajouter une à l'application CounterFit.

#### Tâche - ajouter la caméra à CounterFit

Ajoutez la caméra à l'application CounterFit.

1. Créez une nouvelle application Python sur votre ordinateur dans un dossier appelé `fruit-quality-detector` avec un seul fichier nommé `app.py`, ainsi qu'un environnement virtuel Python, et ajoutez les packages pip de CounterFit.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer et configurer un projet Python CounterFit dans la leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installez un package Pip supplémentaire pour installer un shim CounterFit qui peut communiquer avec des capteurs de caméra en simulant une partie du [package Pip Picamera](https://pypi.org/project/picamera/). Assurez-vous de l'installer depuis un terminal avec l'environnement virtuel activé.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Assurez-vous que l'application web CounterFit est en cours d'exécution.

1. Créez une caméra :

    1. Dans la boîte *Créer un capteur* du volet *Capteurs*, déroulez la boîte *Type de capteur* et sélectionnez *Caméra*.

    1. Définissez le *Nom* sur `Picamera`.

    1. Sélectionnez le bouton **Ajouter** pour créer la caméra.

    ![Les paramètres de la caméra](../../../../../translated_images/fr/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    La caméra sera créée et apparaîtra dans la liste des capteurs.

    ![La caméra créée](../../../../../translated_images/fr/counterfit-camera.001ec52194c8ee5d.webp)

## Programmer la caméra

L'appareil IoT virtuel peut maintenant être programmé pour utiliser la caméra virtuelle.

### Tâche - programmer la caméra

Programmez l'appareil.

1. Assurez-vous que l'application `fruit-quality-detector` est ouverte dans VS Code.

1. Ouvrez le fichier `app.py`.

1. Ajoutez le code suivant en haut de `app.py` pour connecter l'application à CounterFit :

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ajoutez le code suivant à votre fichier `app.py` :

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Ce code importe certaines bibliothèques nécessaires, y compris la classe `PiCamera` de la bibliothèque counterfit_shims_picamera.

1. Ajoutez le code suivant en dessous pour initialiser la caméra :

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Ce code crée un objet PiCamera et définit la résolution sur 640x480. Bien que des résolutions plus élevées soient prises en charge, le classificateur d'images fonctionne sur des images beaucoup plus petites (227x227), il n'est donc pas nécessaire de capturer et d'envoyer des images plus grandes.

    La ligne `camera.rotation = 0` définit la rotation de l'image en degrés. Si vous devez faire pivoter l'image provenant de la webcam ou du fichier, ajustez cette valeur en conséquence. Par exemple, si vous souhaitez changer l'image d'une banane sur une webcam en mode paysage pour qu'elle soit en mode portrait, définissez `camera.rotation = 90`.

1. Ajoutez le code suivant en dessous pour capturer l'image sous forme de données binaires :

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ce code crée un objet `BytesIO` pour stocker des données binaires. L'image est lue depuis la caméra sous forme de fichier JPEG et stockée dans cet objet. Cet objet possède un indicateur de position pour savoir où il se trouve dans les données afin que d'autres données puissent être écrites à la fin si nécessaire. La ligne `image.seek(0)` déplace cette position au début pour que toutes les données puissent être lues plus tard.

1. En dessous, ajoutez le code suivant pour enregistrer l'image dans un fichier :

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ce code ouvre un fichier appelé `image.jpg` en écriture, puis lit toutes les données de l'objet `BytesIO` et les écrit dans le fichier.

    > 💁 Vous pouvez capturer l'image directement dans un fichier au lieu d'un objet `BytesIO` en passant le nom du fichier à l'appel `camera.capture`. La raison d'utiliser l'objet `BytesIO` est qu'ultérieurement dans cette leçon, vous pourrez envoyer l'image à votre classificateur d'images.

1. Configurez l'image que la caméra dans CounterFit capturera. Vous pouvez soit définir la *Source* sur *Fichier*, puis télécharger un fichier image, soit définir la *Source* sur *WebCam*, et les images seront capturées depuis votre webcam. Assurez-vous de sélectionner le bouton **Définir** après avoir choisi une image ou votre webcam.

    ![CounterFit avec un fichier défini comme source d'image, et une webcam montrant une personne tenant une banane dans un aperçu de la webcam](../../../../../translated_images/fr/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. Une image sera capturée et enregistrée sous le nom `image.jpg` dans le dossier actuel. Vous verrez ce fichier dans l'explorateur de VS Code. Sélectionnez le fichier pour afficher l'image. Si elle nécessite une rotation, mettez à jour la ligne `camera.rotation = 0` selon les besoins et prenez une autre photo.

> 💁 Vous pouvez trouver ce code dans le dossier [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Votre programme de caméra a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous ne sommes pas responsables des malentendus ou des interprétations erronées résultant de l'utilisation de cette traduction.