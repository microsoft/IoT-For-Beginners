<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-24T21:28:41+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "fr"
}
-->
# Répondre aux résultats de classification

## Instructions

Votre appareil a classé des images et dispose des valeurs pour les prédictions. Votre appareil peut utiliser ces informations pour agir - il peut les envoyer à IoT Hub pour un traitement par d'autres systèmes, ou contrôler un actionneur tel qu'une LED qui s'allume lorsque le fruit n'est pas mûr.

Ajoutez du code à votre appareil pour répondre de la manière de votre choix - soit en envoyant des données à un IoT Hub, soit en contrôlant un actionneur, ou en combinant les deux et en envoyant des données à un IoT Hub avec un code sans serveur qui détermine si le fruit est mûr ou non et renvoie une commande pour contrôler un actionneur.

## Critères

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Répondre aux prédictions | A réussi à implémenter une réponse aux prédictions qui fonctionne de manière cohérente avec des prédictions de même valeur. | A réussi à implémenter une réponse qui n'est pas dépendante des prédictions, comme simplement envoyer des données brutes à un IoT Hub. | N'a pas réussi à programmer l'appareil pour répondre aux prédictions. |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.