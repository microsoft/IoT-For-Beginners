<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-24T22:03:19+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "fr"
}
-->
# Visualiser les données GDD avec un Jupyter Notebook

## Instructions

Dans cette leçon, vous avez collecté des données GDD à l'aide d'un capteur IoT. Pour obtenir de bonnes données GDD, il est nécessaire de collecter des données sur plusieurs jours. Pour visualiser les données de température et calculer les GDD, vous pouvez utiliser des outils comme [Jupyter Notebooks](https://jupyter.org) pour analyser les données.

Commencez par collecter des données sur quelques jours. Vous devrez vous assurer que le code de votre serveur fonctionne en continu pendant que votre appareil IoT est actif, soit en ajustant les paramètres de gestion de l'alimentation, soit en exécutant quelque chose comme [ce script Python pour maintenir le système actif](https://github.com/jaqsparow/keep-system-active).

Une fois que vous avez des données de température, vous pouvez utiliser le Jupyter Notebook dans ce dépôt pour les visualiser et calculer les GDD. Les Jupyter Notebooks mélangent du code et des instructions dans des blocs appelés *cellules*, souvent du code en Python. Vous pouvez lire les instructions, puis exécuter chaque bloc de code, un par un. Vous pouvez également modifier le code. Dans ce notebook, par exemple, vous pouvez modifier la température de base utilisée pour calculer les GDD pour votre plante.

1. Créez un dossier appelé `gdd-calculation`

1. Téléchargez le fichier [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) et copiez-le dans le dossier `gdd-calculation`.

1. Copiez le fichier `temperature.csv` créé par le serveur MQTT.

1. Créez un nouvel environnement virtuel Python dans le dossier `gdd-calculation`.

1. Installez quelques packages pip pour les Jupyter Notebooks, ainsi que des bibliothèques nécessaires pour gérer et visualiser les données :

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Exécutez le notebook dans Jupyter :

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter démarrera et ouvrira le notebook dans votre navigateur. Suivez les instructions dans le notebook pour visualiser les températures mesurées et calculer les jours degrés de croissance.

    ![Le notebook Jupyter](../../../../../translated_images/fr/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Collecte de données | Collecter au moins 2 jours complets de données | Collecter au moins 1 jour complet de données | Collecter quelques données |
| Calcul des GDD | Exécuter avec succès le notebook et calculer les GDD | Exécuter avec succès le notebook | Impossible d'exécuter le notebook |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.