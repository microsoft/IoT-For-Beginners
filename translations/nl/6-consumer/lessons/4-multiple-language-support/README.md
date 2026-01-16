<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-27T22:15:03+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "nl"
}
-->
# Ondersteuning voor meerdere talen

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze video geeft een overzicht van de Azure spraakdiensten, met spraak-naar-tekst en tekst-naar-spraak uit eerdere lessen, evenals spraakvertaling, een onderwerp dat in deze les wordt behandeld:

[![Spraak herkennen met een paar regels Python van Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klik op de afbeelding hierboven om de video te bekijken

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introductie

In de afgelopen 3 lessen heb je geleerd over het omzetten van spraak naar tekst, taalbegrip en het omzetten van tekst naar spraak, allemaal aangedreven door AI. Een ander gebied van menselijke communicatie waarbij AI kan helpen, is taalvertaling - het omzetten van de ene taal naar de andere, zoals van Engels naar Frans.

In deze les leer je hoe je AI kunt gebruiken om tekst te vertalen, zodat je slimme timer met gebruikers in meerdere talen kan communiceren.

In deze les behandelen we:

* [Tekst vertalen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Vertaalservices](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Een vertaalresource maken](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Meerdere talen ondersteunen in applicaties met vertalingen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Tekst vertalen met een AI-service](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Dit is de laatste les in dit project, dus vergeet niet om na het voltooien van deze les en de opdracht je cloudservices op te schonen. Je hebt de services nodig om de opdracht te voltooien, dus zorg ervoor dat je dat eerst doet.
>
> Raadpleeg [de handleiding voor het opschonen van je project](../../../clean-up.md) indien nodig voor instructies.

## Tekst vertalen

Tekstvertaling is al meer dan 70 jaar een probleem in de computerwetenschap, en pas nu, dankzij vooruitgang in AI en computerkracht, is het bijna opgelost tot een punt waarop het bijna net zo goed is als menselijke vertalers.

> 💁 De oorsprong gaat zelfs nog verder terug, naar [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), een Arabische cryptograaf uit de 9e eeuw die technieken ontwikkelde voor taalvertaling.

### Machinevertalingen

Tekstvertaling begon als een technologie die bekend staat als Machine Translation (MT), die kan vertalen tussen verschillende taalparen. MT werkt door woorden in de ene taal te vervangen door woorden in een andere taal, met technieken om de juiste manieren te selecteren om zinnen of delen van zinnen te vertalen wanneer een eenvoudige woord-voor-woordvertaling niet logisch is.

> 🎓 Wanneer vertalers ondersteuning bieden voor het vertalen tussen twee talen, worden deze *taalparen* genoemd. Verschillende tools ondersteunen verschillende taalparen, en deze zijn mogelijk niet volledig. Bijvoorbeeld, een vertaler kan Engels naar Spaans ondersteunen als een taalpaar, en Spaans naar Italiaans als een taalpaar, maar niet Engels naar Italiaans.

Bijvoorbeeld, het vertalen van "Hello world" van Engels naar Frans kan worden uitgevoerd met een vervanging - "Bonjour" voor "Hello", en "le monde" voor "world", wat leidt tot de correcte vertaling "Bonjour le monde".

Vervangingen werken niet wanneer verschillende talen verschillende manieren gebruiken om hetzelfde te zeggen. Bijvoorbeeld, de Engelse zin "My name is Jim" wordt in het Frans vertaald naar "Je m'appelle Jim" - letterlijk "Ik noem mezelf Jim". "Je" is Frans voor "ik", "moi" is "me", maar wordt samengevoegd met het werkwoord omdat het begint met een klinker, dus wordt "m'", "appelle" betekent "roepen", en "Jim" wordt niet vertaald omdat het een naam is en geen woord dat vertaald kan worden. Ook de woordvolgorde wordt een probleem - een eenvoudige vervanging van "Je m'appelle Jim" wordt "I myself call Jim", met een andere woordvolgorde dan in het Engels.

> 💁 Sommige woorden worden nooit vertaald - mijn naam is Jim, ongeacht welke taal wordt gebruikt om me voor te stellen. Bij vertalingen naar talen die andere alfabetten gebruiken, of andere letters voor verschillende klanken, kunnen woorden *getranslitereerd* worden, dat wil zeggen dat letters of karakters worden gekozen die de juiste klank geven om hetzelfde te klinken als het gegeven woord.

Idiomatische uitdrukkingen vormen ook een probleem voor vertaling. Dit zijn zinnen die een begrepen betekenis hebben die anders is dan een directe interpretatie van de woorden. Bijvoorbeeld, in het Engels verwijst de uitdrukking "I've got ants in my pants" niet letterlijk naar mieren in je kleding, maar naar onrustig zijn. Als je dit naar het Duits zou vertalen, zou je de luisteraar in verwarring brengen, omdat de Duitse versie "Ich habe Hummeln im Hintern" is.

> 💁 Verschillende regio's voegen extra complexiteit toe. Bij de uitdrukking "ants in your pants" verwijst "pants" in Amerikaans Engels naar bovenkleding, terwijl "pants" in Brits Engels ondergoed betekent.

✅ Als je meerdere talen spreekt, bedenk dan enkele zinnen die niet direct vertaald kunnen worden.

Machinevertalingssystemen vertrouwen op grote databases met regels die beschrijven hoe bepaalde zinnen en idiomen vertaald moeten worden, samen met statistische methoden om de juiste vertalingen uit mogelijke opties te kiezen. Deze statistische methoden gebruiken enorme databases van door mensen vertaalde werken in meerdere talen om de meest waarschijnlijke vertaling te kiezen, een techniek genaamd *statistische machinevertaling*. Een aantal hiervan gebruikt tussenliggende representaties van de taal, waardoor één taal naar de tussenliggende taal kan worden vertaald, en vervolgens van de tussenliggende taal naar een andere taal. Op deze manier omvat het toevoegen van meer talen vertalingen naar en van de tussenliggende taal, en niet naar en van alle andere talen.

### Neurale vertalingen

Neurale vertalingen maken gebruik van de kracht van AI om te vertalen, meestal door hele zinnen te vertalen met één model. Deze modellen worden getraind op enorme datasets die door mensen zijn vertaald, zoals webpagina's, boeken en documentatie van de Verenigde Naties.

Neurale vertaalmodellen zijn meestal kleiner dan machinevertalingsmodellen omdat ze geen enorme databases met zinnen en idiomen nodig hebben. Moderne AI-diensten die vertalingen aanbieden, combineren vaak meerdere technieken, zoals statistische machinevertaling en neurale vertaling.

Er is geen 1:1-vertaling voor elk taalpaar. Verschillende vertaalmodellen zullen iets andere resultaten opleveren, afhankelijk van de gegevens die zijn gebruikt om het model te trainen. Vertalingen zijn niet altijd symmetrisch - als je een zin van de ene taal naar de andere vertaalt en vervolgens weer terug naar de eerste taal, kun je een iets andere zin als resultaat zien.

✅ Probeer verschillende online vertalers zoals [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) of de Apple Translate-app. Vergelijk de vertaalde versies van een paar zinnen. Probeer ook een zin in de ene vertaler te vertalen en vervolgens terug te vertalen in een andere.

## Vertaalservices

Er zijn een aantal AI-diensten die vanuit je applicaties kunnen worden gebruikt om spraak en tekst te vertalen.

### Cognitive Services Spraakservice

![Het logo van de spraakservice](../../../../../translated_images/nl/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

De spraakservice die je in de afgelopen lessen hebt gebruikt, heeft vertaalmogelijkheden voor spraakherkenning. Wanneer je spraak herkent, kun je niet alleen de tekst van de spraak in dezelfde taal opvragen, maar ook in andere talen.

> 💁 Dit is alleen beschikbaar via de spraak-SDK, de REST API heeft geen ingebouwde vertalingen.

### Cognitive Services Vertaler-service

![Het logo van de vertaler-service](../../../../../translated_images/nl/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

De Vertaler-service is een speciale vertaaldienst die tekst van de ene taal naar een of meer doeltalen kan vertalen. Naast vertalen ondersteunt het een breed scala aan extra functies, waaronder het maskeren van ongepaste taal. Het stelt je ook in staat om een specifieke vertaling voor een bepaald woord of een bepaalde zin te leveren, om te werken met termen die je niet wilt vertalen, of om een specifieke, bekende vertaling te gebruiken.

Bijvoorbeeld, bij het vertalen van de zin "I have a Raspberry Pi", verwijzend naar de single-board computer, naar een andere taal zoals Frans, wil je de naam "Raspberry Pi" behouden zoals die is, en niet vertalen, wat resulteert in "J’ai un Raspberry Pi" in plaats van "J’ai une pi aux framboises".

## Een vertaalresource maken

Voor deze les heb je een Vertaler-resource nodig. Je zult de REST API gebruiken om tekst te vertalen.

### Taak - een vertaalresource maken

1. Voer vanuit je terminal of opdrachtprompt het volgende commando uit om een vertaalresource te maken in je `smart-timer` resourcegroep.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Vervang `<location>` door de locatie die je hebt gebruikt bij het maken van de resourcegroep.

1. Haal de sleutel voor de vertalerservice op:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Maak een kopie van een van de sleutels.

## Meerdere talen ondersteunen in applicaties met vertalingen

In een ideale wereld zou je hele applicatie zoveel mogelijk verschillende talen moeten begrijpen, van luisteren naar spraak, tot taalbegrip, tot reageren met spraak. Dit is veel werk, dus vertaaldiensten kunnen de tijd tot levering van je applicatie versnellen.

![Een slimme timer-architectuur die Japans naar Engels vertaalt, verwerkt in Engels en vervolgens terug vertaalt naar Japans](../../../../../translated_images/nl/translated-smart-timer.08ac20057fdc5c37.webp)

Stel je voor dat je een slimme timer bouwt die volledig in het Engels werkt, waarbij gesproken Engels wordt begrepen en omgezet in tekst, taalbegrip in het Engels wordt uitgevoerd, reacties in het Engels worden opgebouwd en wordt gereageerd met Engelse spraak. Als je ondersteuning voor Japans wilt toevoegen, kun je beginnen met het vertalen van gesproken Japans naar Engelse tekst, vervolgens de kern van de applicatie hetzelfde houden, en dan de reactietekst naar Japans vertalen voordat je de reactie uitspreekt. Dit zou je in staat stellen om snel ondersteuning voor Japans toe te voegen, en je kunt later uitbreiden naar volledige end-to-end ondersteuning voor Japans.

> 💁 Het nadeel van het vertrouwen op machinevertaling is dat verschillende talen en culturen verschillende manieren hebben om dezelfde dingen te zeggen, dus de vertaling komt mogelijk niet overeen met de uitdrukking die je verwacht.

Machinevertalingen openen ook mogelijkheden voor apps en apparaten die door gebruikers gegenereerde inhoud kunnen vertalen terwijl deze wordt gemaakt. Sciencefiction bevat regelmatig 'universele vertalers', apparaten die van buitenaardse talen naar (meestal) Amerikaans Engels kunnen vertalen. Deze apparaten zijn minder sciencefiction en meer wetenschappelijk feit, als je het buitenaardse deel negeert. Er zijn al apps en apparaten die realtime vertaling van spraak en geschreven tekst bieden, met behulp van combinaties van spraak- en vertaaldiensten.

Een voorbeeld hiervan is de [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobiele telefoon-app, gedemonstreerd in deze video:

[![Microsoft Translator live-functie in actie](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klik op de afbeelding hierboven om de video te bekijken

Stel je voor dat je zo'n apparaat tot je beschikking hebt, vooral tijdens het reizen of bij interactie met mensen wiens taal je niet kent. Automatische vertaalapparaten in luchthavens of ziekenhuizen zouden broodnodige toegankelijkheidsverbeteringen bieden.

✅ Doe wat onderzoek: Zijn er commerciële vertaal-IoT-apparaten beschikbaar? Wat dacht je van vertaalmogelijkheden ingebouwd in slimme apparaten?

> 👽 Hoewel er geen echte universele vertalers zijn waarmee we met buitenaardse wezens kunnen praten, ondersteunt de [Microsoft Translator wel Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Tekst vertalen met een AI-service

Je kunt een AI-service gebruiken om deze vertaalmogelijkheid toe te voegen aan je slimme timer.

### Taak - tekst vertalen met een AI-service

Werk de relevante handleiding door om tekst te vertalen op je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Single-board computer - Raspberry Pi](pi-translate-speech.md)
* [Single-board computer - Virtueel apparaat](virtual-device-translate-speech.md)

---

## 🚀 Uitdaging

Hoe kunnen machinevertalingen andere IoT-toepassingen ten goede komen, naast slimme apparaten? Bedenk verschillende manieren waarop vertalingen kunnen helpen, niet alleen met gesproken woorden maar ook met tekst.

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Herziening & Zelfstudie

* Lees meer over machinevertaling op de [pagina over machinevertaling op Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Lees meer over neurale machinevertaling op de [pagina over neurale machinevertaling op Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Bekijk de lijst met ondersteunde talen voor de Microsoft spraakdiensten in de [taal- en stemondersteuning voor de Spraakservice-documentatie op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Opdracht

[Bouw een universele vertaler](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.