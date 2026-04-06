# Configurez votre microphone et vos haut-parleurs - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un microphone et des haut-parleurs à votre Raspberry Pi.

## Matériel

Le Raspberry Pi a besoin d'un microphone.

Le Pi n'a pas de microphone intégré, vous devrez donc ajouter un microphone externe. Il existe plusieurs façons de le faire :

* Microphone USB  
* Casque USB  
* Haut-parleur tout-en-un USB  
* Adaptateur audio USB et microphone avec prise jack 3,5 mm  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Les microphones Bluetooth ne sont pas tous pris en charge sur le Raspberry Pi. Si vous avez un microphone ou un casque Bluetooth, vous pourriez rencontrer des problèmes de couplage ou de capture audio.

Les Raspberry Pi sont équipés d'une prise casque 3,5 mm. Vous pouvez l'utiliser pour connecter des écouteurs, un casque ou un haut-parleur. Vous pouvez également ajouter des haut-parleurs en utilisant :

* Audio HDMI via un moniteur ou une TV  
* Haut-parleurs USB  
* Casque USB  
* Haut-parleur tout-en-un USB  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) avec un haut-parleur connecté, soit à la prise jack 3,5 mm, soit au port JST  

## Connectez et configurez le microphone et les haut-parleurs

Le microphone et les haut-parleurs doivent être connectés et configurés.

### Tâche - connecter et configurer le microphone

1. Connectez le microphone en utilisant la méthode appropriée. Par exemple, connectez-le via l'un des ports USB.

1. Si vous utilisez le ReSpeaker 2-Mics Pi HAT, vous pouvez retirer le Grove base hat, puis installer le ReSpeaker hat à sa place.

    ![Un Raspberry Pi avec un ReSpeaker hat](../../../../../translated_images/fr/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Vous aurez besoin d'un bouton Grove plus tard dans cette leçon, mais un bouton est intégré à ce hat, donc le Grove base hat n'est pas nécessaire.

    Une fois le hat installé, vous devrez installer des pilotes. Consultez les [instructions de démarrage de Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) pour les instructions d'installation des pilotes.

    > ⚠️ Les instructions utilisent `git` pour cloner un dépôt. Si vous n'avez pas `git` installé sur votre Pi, vous pouvez l'installer en exécutant la commande suivante :
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Exécutez la commande suivante dans votre terminal, soit sur le Pi, soit connecté via VS Code et une session SSH distante, pour voir les informations sur le microphone connecté :

    ```sh
    arecord -l
    ```

    Vous verrez une liste des microphones connectés. Cela ressemblera à quelque chose comme ceci :

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    En supposant que vous n'ayez qu'un seul microphone, vous ne devriez voir qu'une seule entrée. La configuration des microphones peut être compliquée sous Linux, il est donc plus simple d'utiliser un seul microphone et de débrancher les autres.

    Notez le numéro de la carte, car vous en aurez besoin plus tard. Dans l'exemple ci-dessus, le numéro de la carte est 1.

### Tâche - connecter et configurer le haut-parleur

1. Connectez les haut-parleurs en utilisant la méthode appropriée.

1. Exécutez la commande suivante dans votre terminal, soit sur le Pi, soit connecté via VS Code et une session SSH distante, pour voir les informations sur les haut-parleurs connectés :

    ```sh
    aplay -l
    ```

    Vous verrez une liste des haut-parleurs connectés. Cela ressemblera à quelque chose comme ceci :

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Vous verrez toujours `card 0: Headphones`, car il s'agit de la prise casque intégrée. Si vous avez ajouté des haut-parleurs supplémentaires, comme un haut-parleur USB, ils seront également listés.

1. Si vous utilisez un haut-parleur supplémentaire, et non un haut-parleur ou des écouteurs connectés à la prise casque intégrée, vous devez le configurer comme haut-parleur par défaut. Pour ce faire, exécutez la commande suivante :

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Cela ouvrira un fichier de configuration dans `nano`, un éditeur de texte basé sur le terminal. Faites défiler vers le bas à l'aide des touches fléchées de votre clavier jusqu'à trouver la ligne suivante :

    ```output
    defaults.pcm.card 0
    ```

    Changez la valeur de `0` au numéro de la carte que vous souhaitez utiliser, en fonction de la liste obtenue avec la commande `aplay -l`. Par exemple, dans l'exemple ci-dessus, il y a une deuxième carte son appelée `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, utilisant la carte 1. Pour l'utiliser, je mettrais à jour la ligne comme suit :

    ```output
    defaults.pcm.card 1
    ```

    Définissez cette valeur sur le numéro de carte approprié. Vous pouvez naviguer jusqu'au numéro à l'aide des touches fléchées de votre clavier, puis supprimer et taper le nouveau numéro comme pour éditer un fichier texte.

1. Enregistrez les modifications et fermez le fichier en appuyant sur `Ctrl+x`. Appuyez sur `y` pour enregistrer le fichier, puis sur `Entrée` pour confirmer le nom du fichier.

### Tâche - tester le microphone et le haut-parleur

1. Exécutez la commande suivante pour enregistrer 5 secondes d'audio via le microphone :

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Pendant que cette commande s'exécute, faites du bruit dans le microphone, par exemple en parlant, chantant, faisant du beatbox, jouant d'un instrument ou tout ce qui vous amuse.

1. Après 5 secondes, l'enregistrement s'arrêtera. Exécutez la commande suivante pour lire l'audio :

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Vous entendrez l'audio joué à travers les haut-parleurs. Ajustez le volume de sortie sur votre haut-parleur si nécessaire.

1. Si vous devez ajuster le volume du port microphone intégré ou le gain du microphone, vous pouvez utiliser l'utilitaire `alsamixer`. Vous pouvez en savoir plus sur cet utilitaire sur la [page man de Linux alsamixer](https://linux.die.net/man/1/alsamixer).

1. Si vous rencontrez des erreurs lors de la lecture de l'audio, vérifiez la carte que vous avez définie comme `defaults.pcm.card` dans le fichier `alsa.conf`.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.