<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-25T00:04:00+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "fr"
}
-->
# Annuler le minuteur

## Instructions

Jusqu'à présent dans cette leçon, vous avez entraîné un modèle à comprendre la mise en place d'un minuteur. Une autre fonctionnalité utile est d'annuler un minuteur - peut-être que votre pain est prêt et peut être sorti du four avant la fin du minuteur.

Ajoutez une nouvelle intention à votre application LUIS pour annuler le minuteur. Elle n'aura pas besoin d'entités, mais nécessitera quelques phrases d'exemple. Gérez cela dans votre code sans serveur si c'est l'intention principale, en enregistrant que l'intention a été reconnue et en renvoyant une réponse appropriée.

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Ajouter l'intention d'annuler le minuteur à l'application LUIS | A réussi à ajouter l'intention et à entraîner le modèle | A réussi à ajouter l'intention mais pas à entraîner le modèle | N'a pas réussi à ajouter l'intention et à entraîner le modèle |
| Gérer l'intention dans l'application sans serveur | A réussi à détecter l'intention comme intention principale et à l'enregistrer | A réussi à détecter l'intention comme intention principale | N'a pas réussi à détecter l'intention comme intention principale |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.