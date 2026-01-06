<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T22:42:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "nl"
}
-->
# Configureer je microfoon en luidsprekers - Wio Terminal

In dit deel van de les voeg je luidsprekers toe aan je Wio Terminal. De Wio Terminal heeft al een ingebouwde microfoon, die gebruikt kan worden om spraak op te nemen.

## Hardware

De Wio Terminal heeft al een ingebouwde microfoon, die gebruikt kan worden om audio op te nemen voor spraakherkenning.

![De microfoon op de Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.nl.png)

Om een luidspreker toe te voegen, kun je de [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) gebruiken. Dit is een externe module met 2 MEMS-microfoons, een luidsprekerconnector en een hoofdtelefoonaansluiting.

![De ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.nl.png)

Je hebt een hoofdtelefoon, een luidspreker met een 3,5mm jack, of een luidspreker met een JST-verbinding nodig, zoals de [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Om de ReSpeaker 2-Mics Pi Hat aan te sluiten, heb je 40 pin-to-pin (ook wel male-to-male genoemd) jumperkabels nodig.

> 💁 Als je handig bent met solderen, kun je de [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) gebruiken om de ReSpeaker aan te sluiten.

Je hebt ook een SD-kaart nodig om audio te downloaden en af te spelen. De Wio Terminal ondersteunt alleen SD-kaarten tot 16GB, en deze moeten geformatteerd zijn als FAT32 of exFAT.

### Taak - sluit de ReSpeaker Pi Hat aan

1. Schakel de Wio Terminal uit en verbind de ReSpeaker 2-Mics Pi Hat met de Wio Terminal via de jumperkabels en de GPIO-sockets aan de achterkant van de Wio Terminal:

    De pinnen moeten op deze manier worden aangesloten:

    ![Een pin-diagram](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.nl.png)

1. Plaats de ReSpeaker en Wio Terminal met de GPIO-sockets naar boven gericht en aan de linkerkant.

1. Begin bij de socket linksboven in de GPIO-socket van de ReSpeaker. Verbind een pin-to-pin jumperkabel van de socket linksboven op de ReSpeaker naar de socket linksboven op de Wio Terminal.

1. Herhaal dit proces helemaal naar beneden langs de GPIO-sockets aan de linkerkant. Zorg ervoor dat de pinnen stevig vastzitten.

    ![Een ReSpeaker met de linker pinnen verbonden met de linker pinnen van de Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.nl.png)

    ![Een ReSpeaker met de linker pinnen verbonden met de linker pinnen van de Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.nl.png)

    > 💁 Als je jumperkabels in linten zijn verbonden, houd ze dan bij elkaar - dit maakt het makkelijker om ervoor te zorgen dat alle kabels in de juiste volgorde zijn aangesloten.

1. Herhaal het proces met de GPIO-sockets aan de rechterkant van de ReSpeaker en de Wio Terminal. Deze kabels moeten om de al aangesloten kabels heen worden geleid.

    ![Een ReSpeaker met de rechter pinnen verbonden met de rechter pinnen van de Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.nl.png)

    ![Een ReSpeaker met de rechter pinnen verbonden met de rechter pinnen van de Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.nl.png)

    > 💁 Als je jumperkabels in linten zijn verbonden, splits ze dan in twee linten. Leid elk lint aan een kant van de bestaande kabels langs.

    > 💁 Je kunt plakband gebruiken om de pinnen in een blok vast te zetten, zodat ze niet loskomen tijdens het aansluiten.
    >
    > ![De pinnen vastgezet met tape](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.nl.png)

1. Je moet een luidspreker toevoegen.

    * Als je een luidspreker met een JST-kabel gebruikt, sluit deze dan aan op de JST-poort van de ReSpeaker.

      ![Een luidspreker aangesloten op de ReSpeaker met een JST-kabel](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.nl.png)

    * Als je een luidspreker met een 3,5mm jack of een hoofdtelefoon gebruikt, steek deze dan in de 3,5mm jack-aansluiting.

      ![Een luidspreker aangesloten op de ReSpeaker via de 3,5mm jack-aansluiting](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.nl.png)

### Taak - stel de SD-kaart in

1. Sluit de SD-kaart aan op je computer, gebruik een externe lezer als je geen SD-kaartsleuf hebt.

1. Formatteer de SD-kaart met de juiste tool op je computer en zorg ervoor dat je het FAT32- of exFAT-bestandssysteem gebruikt.

1. Plaats de SD-kaart in de SD-kaartsleuf aan de linkerkant van de Wio Terminal, net onder de aan/uit-knop. Zorg ervoor dat de kaart helemaal is ingestoken en vastklikt - je hebt mogelijk een dun gereedschap of een andere SD-kaart nodig om hem helemaal in te duwen.

    ![De SD-kaart in de SD-kaartsleuf onder de aan/uit-knop steken](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.nl.png)

    > 💁 Om de SD-kaart uit te werpen, moet je deze iets indrukken en dan komt hij eruit. Je hebt een dun gereedschap nodig, zoals een platte schroevendraaier of een andere SD-kaart, om dit te doen.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.