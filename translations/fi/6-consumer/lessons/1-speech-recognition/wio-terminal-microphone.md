<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T22:42:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "fi"
}
-->
# Konfiguroi mikrofonisi ja kaiuttimesi - Wio Terminal

Tässä oppitunnin osassa lisäät kaiuttimet Wio Terminal -laitteeseesi. Wio Terminalissa on jo sisäänrakennettu mikrofoni, jota voidaan käyttää puheen tallentamiseen.

## Laitteisto

Wio Terminalissa on jo sisäänrakennettu mikrofoni, jota voidaan käyttää äänen tallentamiseen puheentunnistusta varten.

![Wio Terminalin mikrofoni](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.fi.png)

Kaiuttimen lisäämiseksi voit käyttää [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) -lisäosaa. Tämä on ulkoinen piirilevy, joka sisältää 2 MEMS-mikrofonia, kaiutinliitännän ja kuulokeliitännän.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.fi.png)

Tarvitset joko kuulokkeet, kaiuttimen 3,5 mm liittimellä tai kaiuttimen JST-liitännällä, kuten [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

ReSpeaker 2-Mics Pi Hat -lisäosan liittämiseen tarvitset 40 pin-to-pin (tunnetaan myös nimellä uros-uros) hyppylankoja.

> 💁 Jos olet mukavuusalueellasi juottamisen kanssa, voit käyttää [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) -adapteria ReSpeakerin liittämiseen.

Tarvitset myös SD-kortin äänen lataamiseen ja toistamiseen. Wio Terminal tukee vain enintään 16 GB:n SD-kortteja, ja niiden on oltava FAT32- tai exFAT-muotoisia.

### Tehtävä - liitä ReSpeaker Pi Hat

1. Kun Wio Terminal on sammutettu, liitä ReSpeaker 2-Mics Pi Hat Wio Terminaliin hyppylankojen ja GPIO-liitäntöjen avulla laitteen takana:

    Nämä pinnit tulee liittää seuraavasti:

    ![Pinnien kaavio](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.fi.png)

1. Aseta ReSpeaker ja Wio Terminal siten, että GPIO-liitännät ovat ylöspäin ja vasemmalla puolella.

1. Aloita GPIO-liitännän vasemman yläkulman liitännästä ReSpeakerissä. Liitä hyppylanka vasemman yläkulman liitännästä ReSpeakerissä vasemman yläkulman liitäntään Wio Terminalissa.

1. Toista tämä prosessi koko vasemman puolen GPIO-liitäntöjen osalta. Varmista, että pinnit ovat tiukasti kiinni.

    ![ReSpeaker, jonka vasemman puolen pinnit on kytketty Wio Terminalin vasemman puolen pinneihin](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.fi.png)

    ![ReSpeaker, jonka vasemman puolen pinnit on kytketty Wio Terminalin vasemman puolen pinneihin](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.fi.png)

    > 💁 Jos hyppylankasi ovat nauhoina, pidä ne yhdessä - tämä helpottaa kaikkien kaapeleiden järjestyksessä liittämistä.

1. Toista prosessi oikean puolen GPIO-liitäntöjen osalta ReSpeakerissä ja Wio Terminalissa. Nämä kaapelit tulee kiertää jo olemassa olevien kaapeleiden ympärille.

    ![ReSpeaker, jonka oikean puolen pinnit on kytketty Wio Terminalin oikean puolen pinneihin](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.fi.png)

    ![ReSpeaker, jonka oikean puolen pinnit on kytketty Wio Terminalin oikean puolen pinneihin](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.fi.png)

    > 💁 Jos hyppylankasi ovat nauhoina, jaa ne kahteen nauhaan. Vie yksi nauha kummallekin puolelle olemassa olevia kaapeleita.

    > 💁 Voit käyttää teippiä pitämään pinnit yhdessä estääksesi niiden irtoamisen liittämisen aikana.
    >
    > ![Pinnit kiinnitetty teipillä](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.fi.png)

1. Sinun täytyy lisätä kaiutin.

    * Jos käytät kaiutinta JST-kaapelilla, liitä se ReSpeakerin JST-porttiin.

      ![Kaiutin liitetty ReSpeakeriin JST-kaapelilla](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.fi.png)

    * Jos käytät kaiutinta 3,5 mm liittimellä tai kuulokkeita, liitä ne 3,5 mm liitäntään.

      ![Kaiutin liitetty ReSpeakeriin 3,5 mm liittimen kautta](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.fi.png)

### Tehtävä - SD-kortin asettaminen

1. Liitä SD-kortti tietokoneeseesi, käyttäen ulkoista lukijaa, jos tietokoneessasi ei ole SD-korttipaikkaa.

1. Alusta SD-kortti tietokoneesi sopivalla työkalulla, varmistaen että käytät FAT32- tai exFAT-tiedostojärjestelmää.

1. Aseta SD-kortti Wio Terminalin vasemmalla puolella olevaan SD-korttipaikkaan, juuri virtapainikkeen alapuolelle. Varmista, että kortti menee kokonaan sisään ja napsahtaa paikalleen - saatat tarvita ohutta työkalua tai toista SD-korttia auttamaan sen työntämisessä kokonaan sisään.

    ![SD-kortin asettaminen SD-korttipaikkaan virtakytkimen alapuolella](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.fi.png)

    > 💁 SD-kortin poistamiseksi sinun täytyy painaa sitä hieman sisään, jolloin se ponnahtaa ulos. Tarvitset tähän ohutta työkalua, kuten litteäpäistä ruuvimeisseliä tai toista SD-korttia.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.