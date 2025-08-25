<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-24T23:48:19+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "fr"
}
-->
# IoT pour les consommateurs - créer un assistant vocal intelligent

La nourriture a été cultivée, transportée vers une usine de transformation, triée pour sa qualité, vendue en magasin, et maintenant il est temps de cuisiner ! L'un des éléments essentiels de toute cuisine est un minuteur. À l'origine, ces minuteurs étaient des sabliers - votre plat était prêt lorsque tout le sable s'était écoulé dans le bulbe inférieur. Ensuite, ils sont devenus mécaniques, puis électriques.

Les dernières versions font désormais partie de nos appareils intelligents. Dans les cuisines du monde entier, on entend des cuisiniers crier : "Hey Siri - mets un minuteur de 10 minutes", ou "Alexa - annule mon minuteur pour le pain". Plus besoin de retourner à la cuisine pour vérifier un minuteur, vous pouvez le faire depuis votre téléphone ou simplement en lançant un appel à travers la pièce.

Dans ces 4 leçons, vous apprendrez à créer un minuteur intelligent, en utilisant l'IA pour reconnaître votre voix, comprendre ce que vous demandez, et répondre avec des informations sur votre minuteur. Vous ajouterez également la prise en charge de plusieurs langues.

> ⚠️ Travailler avec des données vocales et de microphone utilise beaucoup de mémoire, ce qui signifie qu'il est facile d'atteindre les limites des microcontrôleurs. Le projet présenté ici contourne ces problèmes, mais sachez que les laboratoires utilisant le Wio Terminal sont complexes et peuvent prendre plus de temps que d'autres laboratoires de ce programme.

> 💁 Ces leçons utiliseront certaines ressources cloud. Si vous ne terminez pas toutes les leçons de ce projet, assurez-vous de [nettoyer votre projet](../clean-up.md).

## Sujets

1. [Reconnaître la parole avec un appareil IoT](./lessons/1-speech-recognition/README.md)
1. [Comprendre le langage](./lessons/2-language-understanding/README.md)
1. [Configurer un minuteur et fournir un retour vocal](./lessons/3-spoken-feedback/README.md)
1. [Prendre en charge plusieurs langues](./lessons/4-multiple-language-support/README.md)

## Crédits

Toutes les leçons ont été écrites avec ♥️ par [Jim Bennett](https://GitHub.com/JimBobBennett)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.