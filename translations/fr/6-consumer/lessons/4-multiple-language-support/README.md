# Prise en charge de plusieurs langues

![Un aperçu en sketchnote de cette leçon](../../../../../translated_images/fr/lesson-24.4246968ed058510a.webp)

> Sketchnote par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette vidéo donne un aperçu des services vocaux d'Azure, couvrant la conversion de la parole en texte et du texte en parole des leçons précédentes, ainsi que la traduction de la parole, un sujet abordé dans cette leçon :

[![Reconnaître la parole avec quelques lignes de Python depuis Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Cliquez sur l'image ci-dessus pour regarder la vidéo

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduction

Dans les 3 dernières leçons, vous avez appris à convertir la parole en texte, à comprendre le langage et à convertir le texte en parole, tout cela grâce à l'IA. Un autre domaine de la communication humaine où l'IA peut être utile est la traduction linguistique - convertir d'une langue à une autre, comme de l'anglais au français.

Dans cette leçon, vous apprendrez à utiliser l'IA pour traduire du texte, permettant à votre minuteur intelligent d'interagir avec les utilisateurs dans plusieurs langues.

Dans cette leçon, nous aborderons :

* [Traduire du texte](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Services de traduction](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Créer une ressource de traducteur](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prise en charge de plusieurs langues dans les applications avec des traductions](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Traduire du texte à l'aide d'un service d'IA](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 C'est la dernière leçon de ce projet, donc après avoir terminé cette leçon et l'exercice, n'oubliez pas de nettoyer vos services cloud. Vous aurez besoin des services pour terminer l'exercice, alors assurez-vous de le faire en premier.
>
> Consultez [le guide de nettoyage de votre projet](../../../clean-up.md) si nécessaire pour obtenir des instructions sur la façon de procéder.

## Traduire du texte

La traduction de texte est un problème en informatique qui a été étudié pendant plus de 70 ans, et ce n'est que maintenant, grâce aux avancées de l'IA et de la puissance informatique, qu'elle est proche d'être résolue à un niveau presque aussi bon que celui des traducteurs humains.

> 💁 Les origines remontent encore plus loin, à [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), un cryptographe arabe du 9ème siècle qui a développé des techniques de traduction linguistique.

### Traductions automatiques

La traduction de texte a commencé avec une technologie connue sous le nom de traduction automatique (MT), qui peut traduire entre différentes paires de langues. La MT fonctionne en substituant des mots d'une langue à une autre, en ajoutant des techniques pour sélectionner les bonnes façons de traduire des phrases ou des parties de phrases lorsque la traduction mot à mot ne fait pas sens.

> 🎓 Lorsque les traducteurs prennent en charge la traduction entre une langue et une autre, on parle de *paires de langues*. Différents outils prennent en charge différentes paires de langues, et celles-ci peuvent ne pas être complètes. Par exemple, un traducteur peut prendre en charge l'anglais vers l'espagnol comme paire de langues, et l'espagnol vers l'italien comme paire de langues, mais pas l'anglais vers l'italien.

Par exemple, traduire "Hello world" de l'anglais au français peut être réalisé par substitution - "Bonjour" pour "Hello", et "le monde" pour "world", ce qui donne la traduction correcte "Bonjour le monde".

Les substitutions ne fonctionnent pas lorsque différentes langues utilisent des façons différentes de dire la même chose. Par exemple, la phrase anglaise "My name is Jim" se traduit par "Je m'appelle Jim" en français - littéralement "Je m'appelle Jim". "Je" est le français pour "I", "moi" est "me", mais est concaténé avec le verbe car il commence par une voyelle, donc devient "m'", "appelle" signifie appeler, et "Jim" n'est pas traduit car c'est un nom, et non un mot pouvant être traduit. L'ordre des mots devient également un problème - une simple substitution de "Je m'appelle Jim" devient "I myself call Jim", avec un ordre des mots différent de l'anglais.

> 💁 Certains mots ne sont jamais traduits - mon nom est Jim, peu importe la langue utilisée pour me présenter. Lorsqu'on traduit vers des langues qui utilisent des alphabets différents ou des lettres différentes pour des sons différents, les mots peuvent être *translittérés*, c'est-à-dire choisir des lettres ou des caractères qui donnent le son approprié pour sonner comme le mot donné.

Les idiomes posent également problème pour la traduction. Ce sont des phrases qui ont un sens compris différent d'une interprétation directe des mots. Par exemple, en anglais, l'idiome "I've got ants in my pants" ne fait pas littéralement référence à avoir des fourmis dans ses vêtements, mais à être agité. Si vous traduisiez cela en allemand, vous finiriez par confondre l'auditeur, car la version allemande est "I have bumble bees in the bottom".

> 💁 Différents lieux ajoutent des complexités différentes. Avec l'idiome "ants in your pants", en anglais américain "pants" fait référence aux vêtements extérieurs, en anglais britannique, "pants" est des sous-vêtements.

✅ Si vous parlez plusieurs langues, pensez à quelques phrases qui ne se traduisent pas directement.

Les systèmes de traduction automatique reposent sur de grandes bases de données de règles qui décrivent comment traduire certaines phrases et idiomes, ainsi que sur des méthodes statistiques pour choisir les traductions appropriées parmi les options possibles. Ces méthodes statistiques utilisent d'énormes bases de données d'œuvres traduites par des humains dans plusieurs langues pour choisir la traduction la plus probable, une technique appelée *traduction automatique statistique*. Un certain nombre de ces systèmes utilisent des représentations intermédiaires de la langue, permettant à une langue d'être traduite vers l'intermédiaire, puis de l'intermédiaire vers une autre langue. De cette façon, l'ajout de langues supplémentaires implique des traductions vers et depuis l'intermédiaire, et non vers et depuis toutes les autres langues.

### Traductions neuronales

Les traductions neuronales utilisent la puissance de l'IA pour traduire, généralement en traduisant des phrases entières à l'aide d'un seul modèle. Ces modèles sont entraînés sur d'énormes ensembles de données traduits par des humains, tels que des pages web, des livres et des documents des Nations Unies.

Les modèles de traduction neuronale sont généralement plus petits que les modèles de traduction automatique car ils n'ont pas besoin de grandes bases de données de phrases et d'idiomes. Les services d'IA modernes qui fournissent des traductions mélangent souvent plusieurs techniques, combinant traduction automatique statistique et traduction neuronale.

Il n'existe pas de traduction 1:1 pour aucune paire de langues. Différents modèles de traduction produiront des résultats légèrement différents en fonction des données utilisées pour entraîner le modèle. Les traductions ne sont pas toujours symétriques - c'est-à-dire que si vous traduisez une phrase d'une langue à une autre, puis revenez à la première langue, vous pouvez obtenir une phrase légèrement différente comme résultat.

✅ Essayez différents traducteurs en ligne tels que [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), ou l'application de traduction d'Apple. Comparez les versions traduites de quelques phrases. Essayez également de traduire dans un, puis de revenir dans un autre.

## Services de traduction

Il existe un certain nombre de services d'IA que vous pouvez utiliser dans vos applications pour traduire la parole et le texte.

### Service vocal des services cognitifs

![Le logo du service vocal](../../../../../translated_images/fr/azure-speech-logo.a1f08c4befb0159f.webp)

Le service vocal que vous avez utilisé au cours des dernières leçons dispose de capacités de traduction pour la reconnaissance vocale. Lorsque vous reconnaissez la parole, vous pouvez demander non seulement le texte de la parole dans la même langue, mais aussi dans d'autres langues.

> 💁 Ceci est uniquement disponible via le SDK vocal, l'API REST n'a pas de traductions intégrées.

### Service de traduction des services cognitifs

![Le logo du service de traduction](../../../../../translated_images/fr/azure-translator-logo.c6ed3a4a433edfd2.webp)

Le service Translator est un service de traduction dédié qui peut traduire du texte d'une langue vers une ou plusieurs langues cibles. En plus de traduire, il prend en charge un large éventail de fonctionnalités supplémentaires, y compris le masquage des propos injurieux. Il vous permet également de fournir une traduction spécifique pour un mot ou une phrase particulière, afin de travailler avec des termes que vous ne souhaitez pas traduire ou qui ont une traduction bien connue.

Par exemple, lorsque vous traduisez la phrase "I have a Raspberry Pi", en faisant référence à l'ordinateur monocarte, dans une autre langue comme le français, vous voudriez conserver le nom "Raspberry Pi" tel quel, et ne pas le traduire, donnant "J’ai un Raspberry Pi" au lieu de "J’ai une pi aux framboises".

## Créer une ressource de traducteur

Pour cette leçon, vous aurez besoin d'une ressource Translator. Vous utiliserez l'API REST pour traduire du texte.

### Tâche - créer une ressource de traducteur

1. Depuis votre terminal ou invite de commande, exécutez la commande suivante pour créer une ressource de traducteur dans votre groupe de ressources `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Remplacez `<location>` par l'emplacement que vous avez utilisé lors de la création du groupe de ressources.

1. Obtenez la clé pour le service de traduction :

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Prenez une copie de l'une des clés.

## Prise en charge de plusieurs langues dans les applications avec des traductions

Dans un monde idéal, toute votre application devrait comprendre autant de langues différentes que possible, de l'écoute de la parole à la compréhension du langage, en passant par la réponse avec la parole. Cela représente beaucoup de travail, donc les services de traduction peuvent accélérer le temps de livraison de votre application.

![Une architecture de minuteur intelligent traduisant le japonais en anglais, traitant en anglais puis traduisant en japonais](../../../../../translated_images/fr/translated-smart-timer.08ac20057fdc5c37.webp)

Imaginez que vous construisez un minuteur intelligent qui utilise l'anglais de bout en bout, comprenant l'anglais parlé et le convertissant en texte, exécutant la compréhension du langage en anglais, construisant des réponses en anglais et répondant avec une parole en anglais. Si vous vouliez ajouter la prise en charge du japonais, vous pourriez commencer par traduire le japonais parlé en texte anglais, puis garder le cœur de l'application identique, puis traduire le texte de réponse en japonais avant de prononcer la réponse. Cela vous permettrait d'ajouter rapidement la prise en charge du japonais, et vous pourriez étendre cela pour fournir une prise en charge complète du japonais de bout en bout plus tard.

> 💁 L'inconvénient de s'appuyer sur la traduction automatique est que différentes langues et cultures ont différentes façons de dire les mêmes choses, donc la traduction peut ne pas correspondre à l'expression que vous attendez.

Les traductions automatiques ouvrent également des possibilités pour les applications et les appareils qui peuvent traduire du contenu créé par les utilisateurs au fur et à mesure de sa création. La science-fiction présente régulièrement des "traducteurs universels", des appareils capables de traduire des langues extraterrestres en (généralement) anglais américain. Ces appareils sont moins de la science-fiction, plus de la science réelle, si l'on ignore la partie extraterrestre. Il existe déjà des applications et des appareils qui fournissent une traduction en temps réel de la parole et du texte écrit, en utilisant des combinaisons de services vocaux et de traduction.

Un exemple est l'application mobile [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), démontrée dans cette vidéo :

[![Fonctionnalité en direct de Microsoft Translator en action](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Cliquez sur l'image ci-dessus pour regarder la vidéo

Imaginez avoir un tel appareil à votre disposition, surtout en voyage ou en interaction avec des personnes dont vous ne connaissez pas la langue. Avoir des appareils de traduction automatiques dans les aéroports ou les hôpitaux offrirait des améliorations d'accessibilité très nécessaires.

✅ Faites des recherches : Existe-t-il des appareils IoT de traduction disponibles dans le commerce ? Qu'en est-il des capacités de traduction intégrées aux appareils intelligents ?

> 👽 Bien qu'il n'existe pas de véritables traducteurs universels qui nous permettent de parler aux extraterrestres, le [Microsoft Translator prend en charge le klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Traduire du texte à l'aide d'un service d'IA

Vous pouvez utiliser un service d'IA pour ajouter cette capacité de traduction à votre minuteur intelligent.

### Tâche - traduire du texte à l'aide d'un service d'IA

Suivez le guide correspondant pour convertir le texte traduit sur votre appareil IoT :

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Ordinateur monocarte - Raspberry Pi](pi-translate-speech.md)
* [Ordinateur monocarte - Appareil virtuel](virtual-device-translate-speech.md)

---

## 🚀 Défi

Comment les traductions automatiques peuvent-elles bénéficier à d'autres applications IoT au-delà des appareils intelligents ? Pensez à différentes façons dont les traductions peuvent aider, pas seulement avec les mots parlés mais aussi avec le texte.

## Quiz après la leçon

[Quiz après la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Révision et auto-apprentissage

* Lisez-en davantage sur la traduction automatique sur la [page de traduction automatique sur Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Lisez-en davantage sur la traduction neuronale sur la [page de traduction neuronale sur Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Consultez la liste des langues prises en charge par les services vocaux de Microsoft dans la [documentation sur le support des langues et des voix pour le service vocal sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Exercice

[Construire un traducteur universel](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.