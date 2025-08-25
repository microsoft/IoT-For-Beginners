<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-24T22:15:33+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "fr"
}
-->
# Construire un cycle d'arrosage plus efficace

## Instructions

Cette leçon a expliqué comment contrôler un relais à l'aide de données de capteurs, et ce relais peut à son tour contrôler une pompe pour un système d'irrigation. Pour une quantité définie de sol, faire fonctionner une pompe pendant une durée fixe devrait toujours avoir le même impact sur l'humidité du sol. Cela signifie que vous pouvez estimer combien de secondes d'irrigation correspondent à une certaine diminution de la lecture de l'humidité du sol. En utilisant ces données, vous pouvez construire un système d'irrigation plus contrôlé.

Pour cet exercice, vous allez calculer combien de temps la pompe doit fonctionner pour obtenir une augmentation particulière de l'humidité du sol.

> ⚠️ Si vous utilisez du matériel IoT virtuel, vous pouvez suivre ce processus, mais simulez les résultats en augmentant manuellement la lecture de l'humidité du sol d'une quantité fixe par seconde lorsque le relais est activé.

1. Commencez avec du sol sec. Mesurez l'humidité du sol.

1. Ajoutez une quantité fixe d'eau, soit en faisant fonctionner la pompe pendant 1 seconde, soit en versant une quantité fixe d'eau.

    > La pompe doit toujours fonctionner à un débit constant, donc chaque seconde de fonctionnement de la pompe doit fournir la même quantité d'eau.

1. Attendez que le niveau d'humidité du sol se stabilise et prenez une mesure.

1. Répétez cette opération plusieurs fois et créez un tableau des résultats. Un exemple de tableau est donné ci-dessous.

    | Temps total de la pompe | Humidité du sol | Diminution |
    | --- | --: | -: |
    | Sec | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calculez une augmentation moyenne de l'humidité du sol par seconde d'eau. Dans l'exemple ci-dessus, chaque seconde d'eau diminue la lecture de l'humidité de 20,3 en moyenne.

1. Utilisez ces données pour améliorer l'efficacité de votre code serveur, en faisant fonctionner la pompe pendant le temps nécessaire pour atteindre le niveau d'humidité souhaité.

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Capturer les données d'humidité du sol | Est capable de capturer plusieurs mesures après avoir ajouté des quantités fixes d'eau | Est capable de capturer quelques mesures avec des quantités fixes d'eau | Ne peut capturer qu'une ou deux mesures, ou est incapable d'utiliser des quantités fixes d'eau |
| Calibrer le code serveur | Est capable de calculer une diminution moyenne de la lecture de l'humidité du sol et de mettre à jour le code serveur en conséquence | Est capable de calculer une diminution moyenne, mais ne peut pas mettre à jour le code serveur, ou est incapable de calculer correctement une moyenne, mais utilise cette valeur pour mettre à jour correctement le code serveur | Est incapable de calculer une moyenne ou de mettre à jour le code serveur |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.