<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-24T23:54:02+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "fr"
}
-->
# Construire un traducteur universel

## Instructions

Un traducteur universel est un dispositif capable de traduire entre plusieurs langues, permettant à des personnes parlant des langues différentes de communiquer. Utilisez ce que vous avez appris au cours des dernières leçons pour construire un traducteur universel en utilisant 2 appareils IoT.

> Si vous ne disposez pas de 2 appareils, suivez les étapes des leçons précédentes pour configurer un appareil IoT virtuel comme l'un des appareils IoT.

Vous devez configurer un appareil pour une langue et un autre pour une autre langue. Chaque appareil doit accepter la parole, la convertir en texte, l'envoyer à l'autre appareil via IoT Hub et une application Functions, puis la traduire et lire la parole traduite.

> 💁 Astuce : Lorsque vous envoyez la parole d'un appareil à un autre, envoyez également la langue dans laquelle elle est exprimée, ce qui facilite la traduction. Vous pourriez même faire en sorte que chaque appareil s'enregistre d'abord via IoT Hub et une application Functions, en transmettant la langue qu'il prend en charge pour qu'elle soit stockée dans Azure Storage. Vous pourriez ensuite utiliser une application Functions pour effectuer les traductions et envoyer le texte traduit à l'appareil IoT.

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Créer un traducteur universel | A réussi à construire un traducteur universel, convertissant la parole détectée par un appareil en une parole jouée par un autre appareil dans une langue différente | A réussi à faire fonctionner certains composants, comme la capture de la parole ou la traduction, mais n'a pas pu construire la solution de bout en bout | N'a pas réussi à construire des parties fonctionnelles d'un traducteur universel |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.