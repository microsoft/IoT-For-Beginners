<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-24T21:52:57+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "fr"
}
-->
# Construire un détecteur de qualité des fruits

## Instructions

Construisez le détecteur de qualité des fruits !

Utilisez tout ce que vous avez appris jusqu'à présent pour créer le prototype du détecteur de qualité des fruits. Déclenchez la classification d'images en fonction de la proximité à l'aide d'un modèle d'IA fonctionnant en périphérie, stockez les résultats de la classification dans un espace de stockage, et contrôlez une LED en fonction du degré de maturité du fruit.

Vous devriez être en mesure de rassembler tout cela en utilisant le code que vous avez écrit dans toutes les leçons précédentes.

## Critères d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Configurer tous les services | A réussi à configurer un IoT Hub, une application de fonctions Azure et un espace de stockage Azure | A réussi à configurer le IoT Hub, mais pas l'application de fonctions Azure ou l'espace de stockage Azure | N'a pas réussi à configurer les services IoT |
| Surveiller la proximité et envoyer les données au IoT Hub si un objet est plus proche qu'une distance prédéfinie, et déclencher la caméra via une commande | A réussi à mesurer la distance et envoyer un message à un IoT Hub lorsqu'un objet est suffisamment proche, et à envoyer une commande pour déclencher la caméra | A réussi à mesurer la proximité et envoyer les données au IoT Hub, mais n'a pas réussi à envoyer une commande à la caméra | N'a pas réussi à mesurer la distance, envoyer un message au IoT Hub ou déclencher une commande |
| Capturer une image, la classifier et envoyer les résultats au IoT Hub | A réussi à capturer une image, la classifier à l'aide d'un appareil en périphérie et envoyer les résultats au IoT Hub | A réussi à classifier l'image mais pas à l'aide d'un appareil en périphérie, ou n'a pas réussi à envoyer les résultats au IoT Hub | N'a pas réussi à classifier une image |
| Allumer ou éteindre la LED en fonction des résultats de la classification via une commande envoyée à un appareil | A réussi à allumer une LED via une commande si le fruit était non mûr | A réussi à envoyer la commande à l'appareil mais pas à contrôler la LED | N'a pas réussi à envoyer une commande pour contrôler la LED |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.