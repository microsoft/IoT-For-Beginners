<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T21:06:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "da"
}
-->
# Konfigurer din mikrofon og højttalere - Wio Terminal

I denne del af lektionen vil du tilføje højttalere til din Wio Terminal. Wio Terminal har allerede en indbygget mikrofon, som kan bruges til at optage tale.

## Hardware

Wio Terminal har allerede en indbygget mikrofon, som kan bruges til at optage lyd til talegenkendelse.

![Mikrofonen på Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.da.png)

For at tilføje en højttaler kan du bruge [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Dette er et eksternt board, der indeholder 2 MEMS-mikrofoner samt en højttalerforbindelse og hovedtelefonstik.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.da.png)

Du skal tilføje enten hovedtelefoner, en højttaler med et 3,5 mm jackstik eller en højttaler med en JST-forbindelse, såsom [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

For at forbinde ReSpeaker 2-Mics Pi Hat skal du bruge 40 pin-til-pin (også kaldet han-til-han) jumperkabler.

> 💁 Hvis du er komfortabel med at lodde, kan du bruge [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) til at forbinde ReSpeaker.

Du skal også bruge et SD-kort til at downloade og afspille lyd. Wio Terminal understøtter kun SD-kort op til 16GB i størrelse, og de skal være formateret som FAT32 eller exFAT.

### Opgave - tilslut ReSpeaker Pi Hat

1. Sluk for Wio Terminal, og tilslut ReSpeaker 2-Mics Pi Hat til Wio Terminal ved hjælp af jumperkablerne og GPIO-stikkene på bagsiden af Wio Terminal:

    Stikkene skal forbindes på denne måde:

    ![Et pinddiagram](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.da.png)

1. Placer ReSpeaker og Wio Terminal med GPIO-stikkene opad og på venstre side.

1. Start fra stikket øverst til venstre på GPIO-stikket på ReSpeaker. Forbind et pin-til-pin jumperkabel fra det øverste venstre stik på ReSpeaker til det øverste venstre stik på Wio Terminal.

1. Gentag dette hele vejen ned ad GPIO-stikkene på venstre side. Sørg for, at stikkene sidder godt fast.

    ![En ReSpeaker med venstre pins forbundet til venstre pins på Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.da.png)

    ![En ReSpeaker med venstre pins forbundet til venstre pins på Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.da.png)

    > 💁 Hvis dine jumperkabler er samlet i bånd, så hold dem sammen - det gør det nemmere at sikre, at alle kablerne er forbundet i den rigtige rækkefølge.

1. Gentag processen med GPIO-stikkene på højre side af ReSpeaker og Wio Terminal. Disse kabler skal gå rundt om de kabler, der allerede er på plads.

    ![En ReSpeaker med højre pins forbundet til højre pins på Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.da.png)

    ![En ReSpeaker med højre pins forbundet til højre pins på Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.da.png)

    > 💁 Hvis dine jumperkabler er samlet i bånd, så del dem op i to bånd. Før et bånd på hver side af de eksisterende kabler.

    > 💁 Du kan bruge tape til at holde stikkene samlet i en blok for at forhindre, at de falder ud, mens du forbinder dem.
    >
    > ![Stikkene fastgjort med tape](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.da.png)

1. Du skal tilføje en højttaler.

    * Hvis du bruger en højttaler med et JST-kabel, skal du forbinde det til JST-porten på ReSpeaker.

      ![En højttaler forbundet til ReSpeaker med et JST-kabel](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.da.png)

    * Hvis du bruger en højttaler med et 3,5 mm jackstik eller hovedtelefoner, skal du indsætte dem i 3,5 mm jackstikket.

      ![En højttaler forbundet til ReSpeaker via 3,5 mm jackstikket](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.da.png)

### Opgave - opsæt SD-kortet

1. Tilslut SD-kortet til din computer ved hjælp af en ekstern kortlæser, hvis du ikke har en SD-kortslot.

1. Formater SD-kortet ved hjælp af det relevante værktøj på din computer, og sørg for at bruge FAT32 eller exFAT filsystem.

1. Indsæt SD-kortet i SD-kortslottet på venstre side af Wio Terminal, lige under tænd/sluk-knappen. Sørg for, at kortet er helt inde og klikker på plads - du kan have brug for et tyndt værktøj eller et andet SD-kort til at hjælpe med at skubbe det helt ind.

    ![Indsætning af SD-kortet i SD-kortslottet under tænd/sluk-knappen](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.da.png)

    > 💁 For at skubbe SD-kortet ud skal du trykke det lidt ind, og det vil springe ud. Du skal bruge et tyndt værktøj som en flad skruetrækker eller et andet SD-kort til dette.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.