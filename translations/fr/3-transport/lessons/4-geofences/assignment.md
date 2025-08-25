<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T00:43:36+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "fr"
}
-->
# Envoyer des notifications avec Twilio

## Instructions

Dans votre code jusqu'à présent, vous avez simplement enregistré la distance par rapport à la géofence. Dans cet exercice, vous devrez ajouter une notification, soit un message texte, soit un email, lorsque les coordonnées GPS se trouvent à l'intérieur de la géofence.

Azure Functions propose de nombreuses options pour les liaisons, y compris avec des services tiers tels que Twilio, une plateforme de communication.

* Inscrivez-vous pour un compte gratuit sur [Twilio.com](https://www.twilio.com)
* Lisez la documentation sur la liaison des Azure Functions avec Twilio SMS sur la [page de documentation Microsoft sur la liaison Twilio pour Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lisez la documentation sur la liaison des Azure Functions avec Twilio SendGrid pour envoyer des emails sur la [page de documentation Microsoft sur les liaisons SendGrid pour Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Ajoutez la liaison à votre application Functions pour être notifié lorsque les coordonnées GPS sont soit à l'intérieur, soit à l'extérieur de la géofence - mais pas les deux.

## Grille d'évaluation

| Critères | Exemplaire | Adéquat | À améliorer |
| -------- | ---------- | ------- | ----------- |
| Configurer les liaisons des fonctions et recevoir un email ou un SMS | A réussi à configurer les liaisons des fonctions et à recevoir un email ou un SMS lorsque les coordonnées sont à l'intérieur ou à l'extérieur de la géofence, mais pas les deux | A réussi à configurer les liaisons mais n'a pas pu envoyer l'email ou le SMS, ou a seulement pu envoyer lorsque les coordonnées étaient à la fois à l'intérieur et à l'extérieur | N'a pas réussi à configurer les liaisons et à envoyer un email ou un SMS |

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.