<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-10-11T12:19:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "et"
}
-->
# Konfigureeri mikrofon ja kõlarid - Wio Terminal

Selles õppetunni osas lisad kõlarid oma Wio Terminalile. Wio Terminalil on juba sisseehitatud mikrofon, mida saab kasutada kõne salvestamiseks.

## Riistvara

Wio Terminalil on juba sisseehitatud mikrofon, mida saab kasutada heli salvestamiseks kõnetuvastuse jaoks.

![Mikrofon Wio Terminalil](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.et.png)

Kõlari lisamiseks võid kasutada [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). See on väline plaat, mis sisaldab 2 MEMS-mikrofoni, kõlariühendust ja kõrvaklapipesa.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.et.png)

Sul on vaja lisada kas kõrvaklapid, kõlar 3,5 mm pistikuga või kõlar JST-ühendusega, näiteks [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

ReSpeaker 2-Mics Pi Hat ühendamiseks on vaja 40 pin-to-pin (tuntud ka kui isane-isane) hüppajakaableid.

> 💁 Kui oled mugav jootmises, siis võid kasutada [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html), et ühendada ReSpeaker.

Samuti on sul vaja SD-kaarti, et alla laadida ja heli taasesitada. Wio Terminal toetab ainult kuni 16GB suuruseid SD-kaarte, mis peavad olema vormindatud FAT32 või exFAT failisüsteemiga.

### Ülesanne - ühenda ReSpeaker Pi Hat

1. Kui Wio Terminal on välja lülitatud, ühenda ReSpeaker 2-Mics Pi Hat Wio Terminaliga, kasutades hüppajakaableid ja GPIO pesasid Wio Terminali tagaküljel:

    Pinid tuleb ühendada järgmiselt:

    ![Pinide diagramm](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.et.png)

1. Aseta ReSpeaker ja Wio Terminal nii, et GPIO pesad oleksid ülespoole ja vasakul küljel.

1. Alusta ReSpeakeri GPIO pesa vasakust ülemisest pesast. Ühenda pin-to-pin hüppajakaabel ReSpeakeri vasakust ülemisest pesast Wio Terminali vasakusse ülemisse pesasse.

1. Korda seda kogu vasaku külje GPIO pesade ulatuses. Veendu, et pinid oleksid kindlalt paigas.

    ![ReSpeaker, mille vasakpoolne külg on ühendatud Wio Terminali vasakpoolse küljega](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.et.png)

    ![ReSpeaker, mille vasakpoolne külg on ühendatud Wio Terminali vasakpoolse küljega](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.et.png)

    > 💁 Kui sinu hüppajakaablid on ühendatud ribadena, hoia need kõik koos - see teeb lihtsamaks veenduda, et kõik kaablid on õiges järjekorras ühendatud.

1. Korda protsessi, kasutades ReSpeakeri ja Wio Terminali parempoolseid GPIO pesasid. Need kaablid peavad minema juba paigaldatud kaablite ümber.

    ![ReSpeaker, mille parempoolne külg on ühendatud Wio Terminali parempoolse küljega](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.et.png)

    ![ReSpeaker, mille parempoolne külg on ühendatud Wio Terminali parempoolse küljega](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.et.png)

    > 💁 Kui sinu hüppajakaablid on ühendatud ribadena, jaga need kaheks ribaks. Lase üks riba kummalegi poole olemasolevaid kaableid.

    > 💁 Võid kasutada kleeplinti, et kinnitada pinid plokiks, mis aitab vältida nende väljatulekut ühendamise ajal.
    >
    > ![Pinid kinnitatud kleeplindiga](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.et.png)

1. Sul on vaja lisada kõlar.

    * Kui kasutad kõlarit JST-kaabliga, ühenda see ReSpeakeri JST-pesasse.

      ![Kõlar ühendatud ReSpeakeriga JST-kaabli abil](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.et.png)

    * Kui kasutad kõlarit 3,5 mm pistikuga või kõrvaklappe, sisesta need 3,5 mm pistikupessa.

      ![Kõlar ühendatud ReSpeakeriga 3,5 mm pistikupesa kaudu](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.et.png)

### Ülesanne - seadista SD-kaart

1. Ühenda SD-kaart oma arvutiga, kasutades välist lugejat, kui sul pole SD-kaardi pesa.

1. Vorminda SD-kaart, kasutades oma arvuti sobivat tööriista, veendudes, et failisüsteemiks oleks FAT32 või exFAT.

1. Sisesta SD-kaart Wio Terminali SD-kaardi pesasse, mis asub vasakul küljel, vahetult toitelüliti all. Veendu, et kaart oleks täielikult sees ja klõpsaks paika - sul võib vaja minna õhukest tööriista või teist SD-kaarti, et aidata seda täielikult sisse lükata.

    ![SD-kaardi sisestamine SD-kaardi pesasse toitelüliti all](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.et.png)

    > 💁 SD-kaardi eemaldamiseks pead seda veidi sisse suruma, et see välja tuleks. Selleks on vaja õhukest tööriista, näiteks lapik kruvikeerajat või teist SD-kaarti.

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.