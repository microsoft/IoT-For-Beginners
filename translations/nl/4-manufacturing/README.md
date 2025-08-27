<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:35:11+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "nl"
}
-->
# Productie en verwerking - IoT gebruiken om de verwerking van voedsel te verbeteren

Wanneer voedsel een centraal punt of verwerkingsfabriek bereikt, wordt het niet altijd direct naar supermarkten verzonden. Vaak doorloopt het voedsel een aantal verwerkingsstappen, zoals sorteren op kwaliteit. Dit was vroeger een handmatig proces - het begon op het veld, waar plukkers alleen rijp fruit plukten, en vervolgens werd in de fabriek het fruit op een lopende band geplaatst en verwijderden medewerkers handmatig beschadigd of rot fruit. Zelf heb ik als zomerbaan tijdens mijn schooltijd aardbeien geplukt en gesorteerd, en ik kan bevestigen dat dit geen leuk werk is.

Modernere systemen maken gebruik van IoT voor het sorteren. Sommige van de vroegste apparaten, zoals de sorteermachines van [Weco](https://wecotek.com), gebruiken optische sensoren om de kwaliteit van producten te detecteren, bijvoorbeeld om groene tomaten te weigeren. Deze kunnen worden ingezet in oogstmachines op de boerderij zelf, of in verwerkingsfabrieken.

Met de vooruitgang in Kunstmatige Intelligentie (AI) en Machine Learning (ML) kunnen deze machines steeds geavanceerder worden, met ML-modellen die getraind zijn om onderscheid te maken tussen fruit en vreemde objecten zoals stenen, aarde of insecten. Deze modellen kunnen ook worden getraind om de kwaliteit van fruit te detecteren, niet alleen beschadigd fruit, maar ook vroege signalen van ziektes of andere gewasproblemen.

> 🎓 De term *ML-model* verwijst naar het resultaat van het trainen van machine learning-software op een dataset. Bijvoorbeeld, je kunt een ML-model trainen om onderscheid te maken tussen rijpe en onrijpe tomaten, en vervolgens het model gebruiken op nieuwe afbeeldingen om te bepalen of de tomaten rijp zijn of niet.

In deze 4 lessen leer je hoe je op afbeeldingen gebaseerde AI-modellen kunt trainen om de kwaliteit van fruit te detecteren, hoe je deze kunt gebruiken vanaf een IoT-apparaat, en hoe je ze kunt uitvoeren aan de rand - dat wil zeggen op een IoT-apparaat in plaats van in de cloud.

> 💁 Deze lessen maken gebruik van enkele cloudbronnen. Als je niet alle lessen in dit project voltooit, zorg er dan voor dat je [je project opruimt](../clean-up.md).

## Onderwerpen

1. [Train een detector voor fruitkwaliteit](./lessons/1-train-fruit-detector/README.md)
1. [Controleer fruitkwaliteit vanaf een IoT-apparaat](./lessons/2-check-fruit-from-device/README.md)
1. [Voer je fruitdetector uit aan de rand](./lessons/3-run-fruit-detector-edge/README.md)
1. [Activeer fruitkwaliteitsdetectie via een sensor](./lessons/4-trigger-fruit-detector/README.md)

## Credits

Alle lessen zijn geschreven met ♥️ door [Jen Fox](https://github.com/jenfoxbot) en [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.