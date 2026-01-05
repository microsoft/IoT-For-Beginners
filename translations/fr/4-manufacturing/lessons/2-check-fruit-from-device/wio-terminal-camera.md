<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-24T21:36:00+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "fr"
}
-->
# Capturer une image - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter une caméra à votre Wio Terminal et capturer des images avec celle-ci.

## Matériel

Le Wio Terminal a besoin d'une caméra.

La caméra que vous utiliserez est une [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Il s'agit d'une caméra de 2 mégapixels basée sur le capteur d'image OV2640. Elle communique via une interface SPI pour capturer des images et utilise I2C pour configurer le capteur.

## Connecter la caméra

L'ArduCam n'a pas de prise Grove, elle se connecte donc aux bus SPI et I2C via les broches GPIO du Wio Terminal.

### Tâche - connecter la caméra

Connectez la caméra.

![Un capteur ArduCam](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.fr.png)

1. Les broches à la base de l'ArduCam doivent être connectées aux broches GPIO du Wio Terminal. Pour faciliter l'identification des broches, attachez l'autocollant des broches GPIO fourni avec le Wio Terminal autour des broches :

    ![Le Wio Terminal avec l'autocollant des broches GPIO](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.fr.png)

1. À l'aide de fils de connexion, effectuez les connexions suivantes :

    | Broche ArduCAM | Broche Wio Terminal | Description                              |
    | -------------- | ------------------- | ---------------------------------------- |
    | CS             | 24 (SPI_CS)         | Sélection de puce SPI                    |
    | MOSI           | 19 (SPI_MOSI)       | Sortie du contrôleur SPI, entrée du périphérique |
    | MISO           | 21 (SPI_MISO)       | Entrée du contrôleur SPI, sortie du périphérique |
    | SCK            | 23 (SPI_SCLK)       | Horloge série SPI                        |
    | GND            | 6 (GND)             | Masse - 0V                               |
    | VCC            | 4 (5V)              | Alimentation 5V                          |
    | SDA            | 3 (I2C1_SDA)        | Données série I2C                        |
    | SCL            | 5 (I2C1_SCL)        | Horloge série I2C                        |

    ![Le Wio Terminal connecté à l'ArduCam avec des fils de connexion](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.fr.png)

    Les connexions GND et VCC fournissent une alimentation de 5V à l'ArduCam. Elle fonctionne à 5V, contrairement aux capteurs Grove qui fonctionnent à 3V. Cette alimentation provient directement de la connexion USB-C qui alimente l'appareil.

    > 💁 Pour la connexion SPI, les étiquettes des broches sur l'ArduCam et les noms des broches du Wio Terminal utilisés dans le code utilisent encore l'ancienne convention de nommage. Les instructions de cette leçon utiliseront la nouvelle convention de nommage, sauf lorsque les noms des broches sont utilisés dans le code.

1. Vous pouvez maintenant connecter le Wio Terminal à votre ordinateur.

## Programmer l'appareil pour se connecter à la caméra

Le Wio Terminal peut maintenant être programmé pour utiliser la caméra ArduCAM connectée.

### Tâche - programmer l'appareil pour se connecter à la caméra

1. Créez un nouveau projet Wio Terminal avec PlatformIO. Appelez ce projet `fruit-quality-detector`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

1. Ajoutez du code pour se connecter au WiFi, avec vos identifiants WiFi dans un fichier appelé `config.h`. N'oubliez pas d'ajouter les bibliothèques nécessaires dans le fichier `platformio.ini`.

1. La bibliothèque ArduCam n'est pas disponible en tant que bibliothèque Arduino installable depuis le fichier `platformio.ini`. Elle devra être installée depuis son dépôt GitHub. Vous pouvez l'obtenir en :

    * Clonant le dépôt depuis [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Accédant au dépôt sur GitHub à [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) et en téléchargeant le code en tant que fichier zip depuis le bouton **Code**

1. Vous n'avez besoin que du dossier `ArduCAM` de ce code. Copiez l'intégralité du dossier dans le dossier `lib` de votre projet.

    > ⚠️ Le dossier entier doit être copié, de sorte que le code soit dans `lib/ArduCam`. Ne copiez pas simplement le contenu du dossier `ArduCam` dans le dossier `lib`, copiez tout le dossier.

1. Le code de la bibliothèque ArduCam fonctionne pour plusieurs types de caméras. Le type de caméra que vous souhaitez utiliser est configuré à l'aide de drapeaux du compilateur - cela permet de garder la bibliothèque construite aussi petite que possible en supprimant le code pour les caméras que vous n'utilisez pas. Pour configurer la bibliothèque pour la caméra OV2640, ajoutez ce qui suit à la fin du fichier `platformio.ini` :

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Cela définit 2 drapeaux du compilateur :

      * `ARDUCAM_SHIELD_V2` pour indiquer à la bibliothèque que la caméra est sur une carte Arduino, appelée un shield.
      * `OV2640_CAM` pour indiquer à la bibliothèque d'inclure uniquement le code pour la caméra OV2640.

1. Ajoutez un fichier d'en-tête dans le dossier `src` appelé `camera.h`. Ce fichier contiendra le code pour communiquer avec la caméra. Ajoutez le code suivant à ce fichier :

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Il s'agit d'un code de bas niveau qui configure la caméra à l'aide des bibliothèques ArduCam et extrait les images lorsque nécessaire via le bus SPI. Ce code est très spécifique à l'ArduCam, vous n'avez donc pas besoin de vous soucier de son fonctionnement pour le moment.

1. Dans `main.cpp`, ajoutez le code suivant sous les autres déclarations `include` pour inclure ce nouveau fichier et créer une instance de la classe caméra :

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Cela crée une `Camera` qui enregistre les images au format JPEG avec une résolution de 640 par 480. Bien que des résolutions plus élevées soient prises en charge (jusqu'à 3280x2464), le classificateur d'images fonctionne sur des images beaucoup plus petites (227x227), il n'est donc pas nécessaire de capturer et d'envoyer des images plus grandes.

1. Ajoutez le code suivant en dessous pour définir une fonction permettant de configurer la caméra :

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Cette fonction `setupCamera` commence par configurer la broche de sélection de puce SPI (`PIN_SPI_SS`) comme étant haute, faisant du Wio Terminal le contrôleur SPI. Elle démarre ensuite les bus I2C et SPI. Enfin, elle initialise la classe caméra, ce qui configure les paramètres du capteur de la caméra et s'assure que tout est correctement câblé.

1. Appelez cette fonction à la fin de la fonction `setup` :

    ```cpp
    setupCamera();
    ```

1. Compilez et téléversez ce code, puis vérifiez la sortie du moniteur série. Si vous voyez `Error setting up the camera!`, vérifiez le câblage pour vous assurer que tous les fils connectent les bonnes broches sur l'ArduCam aux bonnes broches GPIO sur le Wio Terminal, et que tous les fils de connexion sont correctement insérés.

## Capturer une image

Le Wio Terminal peut maintenant être programmé pour capturer une image lorsqu'un bouton est pressé.

### Tâche - capturer une image

1. Les microcontrôleurs exécutent votre code en continu, il n'est donc pas facile de déclencher une action comme prendre une photo sans réagir à un capteur. Le Wio Terminal dispose de boutons, la caméra peut donc être configurée pour être déclenchée par l'un de ces boutons. Ajoutez le code suivant à la fin de la fonction `setup` pour configurer le bouton C (l'un des trois boutons sur le dessus, celui le plus proche de l'interrupteur d'alimentation).

    ![Le bouton C sur le dessus, le plus proche de l'interrupteur d'alimentation](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.fr.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Le mode `INPUT_PULLUP` inverse essentiellement une entrée. Par exemple, normalement un bouton enverrait un signal bas lorsqu'il n'est pas pressé, et un signal haut lorsqu'il est pressé. Lorsqu'il est configuré en `INPUT_PULLUP`, il envoie un signal haut lorsqu'il n'est pas pressé, et un signal bas lorsqu'il est pressé.

1. Ajoutez une fonction vide pour répondre à l'appui sur le bouton avant la fonction `loop` :

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Appelez cette fonction dans la méthode `loop` lorsque le bouton est pressé :

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Cette clé vérifie si le bouton est pressé. Si c'est le cas, la fonction `buttonPressed` est appelée, et la boucle est retardée de 2 secondes. Cela permet de laisser le temps au bouton d'être relâché pour qu'un appui long ne soit pas enregistré deux fois.

    > 💁 Le bouton sur le Wio Terminal est configuré en `INPUT_PULLUP`, il envoie donc un signal haut lorsqu'il n'est pas pressé, et un signal bas lorsqu'il est pressé.

1. Ajoutez le code suivant à la fonction `buttonPressed` :

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Ce code commence la capture de la caméra en appelant `startCapture`. Le matériel de la caméra ne fonctionne pas en renvoyant les données lorsque vous les demandez, à la place, vous envoyez une instruction pour commencer la capture, et la caméra travaille en arrière-plan pour capturer l'image, la convertir en JPEG, et la stocker dans un tampon local sur la caméra elle-même. L'appel `captureReady` vérifie ensuite si la capture de l'image est terminée.

    Une fois la capture terminée, les données de l'image sont copiées du tampon de la caméra dans un tampon local (tableau d'octets) avec l'appel `readImageToBuffer`. La longueur du tampon est ensuite envoyée au moniteur série.

1. Compilez et téléversez ce code, puis vérifiez la sortie sur le moniteur série. Chaque fois que vous appuyez sur le bouton C, une image sera capturée et vous verrez la taille de l'image envoyée au moniteur série.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Les différentes images auront des tailles différentes. Elles sont compressées en JPEG et la taille d'un fichier JPEG pour une résolution donnée dépend de ce qui se trouve dans l'image.

> 💁 Vous pouvez trouver ce code dans le dossier [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Vous avez réussi à capturer des images avec votre Wio Terminal.

## Optionnel - vérifier les images de la caméra à l'aide d'une carte SD

Le moyen le plus simple de voir les images capturées par la caméra est de les écrire sur une carte SD dans le Wio Terminal, puis de les visualiser sur votre ordinateur. Effectuez cette étape si vous avez une carte microSD de rechange et un lecteur de carte microSD sur votre ordinateur, ou un adaptateur.

Le Wio Terminal ne prend en charge que les cartes microSD d'une capacité maximale de 16 Go. Si vous avez une carte SD plus grande, elle ne fonctionnera pas.

### Tâche - vérifier les images de la caméra à l'aide d'une carte SD

1. Formatez une carte microSD en FAT32 ou exFAT à l'aide des applications pertinentes sur votre ordinateur (Utilitaire de disque sur macOS, Explorateur de fichiers sur Windows, ou des outils en ligne de commande sous Linux).

1. Insérez la carte microSD dans le lecteur juste en dessous de l'interrupteur d'alimentation. Assurez-vous qu'elle est complètement insérée jusqu'à ce qu'elle s'enclenche et reste en place. Vous devrez peut-être la pousser avec un ongle ou un outil fin.

1. Ajoutez les déclarations `include` suivantes en haut du fichier `main.cpp` :

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Ajoutez la fonction suivante avant la fonction `setup` :

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Cela configure la carte SD en utilisant le bus SPI.

1. Appelez cette fonction depuis la fonction `setup` :

    ```cpp
    setupSDCard();
    ```

1. Ajoutez le code suivant au-dessus de la fonction `buttonPressed` :

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Cela définit une variable globale pour un compteur de fichiers. Ce compteur est utilisé pour les noms de fichiers d'image afin que plusieurs images puissent être capturées avec des noms de fichiers incrémentés - `1.jpg`, `2.jpg`, etc.

    Ensuite, la fonction `saveToSDCard` est définie. Elle prend un tampon de données en octets et la longueur du tampon. Un nom de fichier est créé en utilisant le compteur de fichiers, et le compteur est incrémenté pour le fichier suivant. Les données binaires du tampon sont ensuite écrites dans le fichier.

1. Appelez la fonction `saveToSDCard` depuis la fonction `buttonPressed`. L'appel doit être **avant** que le tampon ne soit supprimé :

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Compilez et téléversez ce code, puis vérifiez la sortie sur le moniteur série. Chaque fois que vous appuyez sur le bouton C, une image sera capturée et enregistrée sur la carte SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Éteignez le Wio Terminal et éjectez la carte microSD en la poussant légèrement pour la libérer. Vous devrez peut-être utiliser un outil fin pour cela. Insérez la carte microSD dans votre ordinateur pour visualiser les images.

    ![Une photo d'une banane capturée avec l'ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.fr.jpg)
> 💁 Il peut falloir quelques images pour que la balance des blancs de la caméra s'ajuste. Vous le remarquerez en fonction de la couleur des images capturées, les premières peuvent sembler décolorées. Vous pouvez toujours contourner cela en modifiant le code pour capturer quelques images qui sont ignorées dans la fonction `setup`.


**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.