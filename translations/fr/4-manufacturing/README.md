<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-24T21:19:30+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "fr"
}
-->
# Fabrication et transformation - utiliser l'IoT pour améliorer le traitement des aliments

Une fois que les aliments atteignent un centre de traitement ou une usine, ils ne sont pas toujours simplement expédiés aux supermarchés. Souvent, les aliments passent par plusieurs étapes de transformation, comme le tri par qualité. C'était un processus qui se faisait manuellement - cela commençait dans les champs où les cueilleurs ne ramassaient que les fruits mûrs, puis à l'usine, les fruits passaient sur un tapis roulant et les employés retiraient manuellement les fruits abîmés ou pourris. Ayant moi-même cueilli et trié des fraises comme job d'été pendant mes études, je peux témoigner que ce n'est pas un travail agréable.

Les installations modernes s'appuient sur l'IoT pour le tri. Certains des premiers dispositifs, comme les trieurs de [Weco](https://wecotek.com), utilisent des capteurs optiques pour détecter la qualité des produits, rejetant par exemple les tomates vertes. Ces dispositifs peuvent être déployés dans les moissonneuses directement sur le champ ou dans les usines de transformation.

Avec les avancées en Intelligence Artificielle (IA) et en apprentissage automatique (ML), ces machines peuvent devenir plus sophistiquées, utilisant des modèles ML entraînés pour distinguer les fruits des objets étrangers tels que des pierres, de la terre ou des insectes. Ces modèles peuvent également être entraînés à détecter la qualité des fruits, non seulement les fruits abîmés, mais aussi les premiers signes de maladies ou d'autres problèmes de culture.

> 🎓 Le terme *modèle ML* fait référence au résultat de l'entraînement d'un logiciel d'apprentissage automatique sur un ensemble de données. Par exemple, vous pouvez entraîner un modèle ML à distinguer les tomates mûres des tomates non mûres, puis utiliser ce modèle sur de nouvelles images pour déterminer si les tomates sont mûres ou non.

Dans ces 4 leçons, vous apprendrez à entraîner des modèles d'IA basés sur des images pour détecter la qualité des fruits, à les utiliser depuis un appareil IoT, et à les exécuter en périphérie - c'est-à-dire sur un appareil IoT plutôt que dans le cloud.

> 💁 Ces leçons utiliseront certaines ressources cloud. Si vous ne terminez pas toutes les leçons de ce projet, assurez-vous de [nettoyer votre projet](../clean-up.md).

## Sujets

1. [Entraîner un détecteur de qualité des fruits](./lessons/1-train-fruit-detector/README.md)  
1. [Vérifier la qualité des fruits depuis un appareil IoT](./lessons/2-check-fruit-from-device/README.md)  
1. [Exécuter votre détecteur de fruits en périphérie](./lessons/3-run-fruit-detector-edge/README.md)  
1. [Déclencher la détection de qualité des fruits à partir d'un capteur](./lessons/4-trigger-fruit-detector/README.md)  

## Crédits

Toutes les leçons ont été écrites avec ♥️ par [Jen Fox](https://github.com/jenfoxbot) et [Jim Bennett](https://GitHub.com/JimBobBennett)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.