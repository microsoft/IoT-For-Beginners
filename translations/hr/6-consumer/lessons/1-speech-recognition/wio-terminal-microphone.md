<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T12:55:42+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "hr"
}
-->
# Konfigurirajte mikrofon i zvučnike - Wio Terminal

U ovom dijelu lekcije, dodati ćete zvučnike svom Wio Terminalu. Wio Terminal već ima ugrađeni mikrofon koji se može koristiti za snimanje govora.

## Hardver

Wio Terminal već ima ugrađeni mikrofon koji se može koristiti za snimanje zvuka za prepoznavanje govora.

![Mikrofon na Wio Terminalu](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.hr.png)

Za dodavanje zvučnika možete koristiti [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Ovo je vanjska ploča koja sadrži 2 MEMS mikrofona, kao i priključak za zvučnik i utičnicu za slušalice.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.hr.png)

Trebat će vam ili slušalice, zvučnik s 3,5 mm priključkom ili zvučnik s JST konektorom, poput [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Za povezivanje ReSpeaker 2-Mics Pi Hat trebat će vam 40 pin-to-pin (također poznati kao muško-muški) skakači.

> 💁 Ako ste vješti u lemljenju, možete koristiti [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) za povezivanje ReSpeakera.

Također će vam trebati SD kartica za preuzimanje i reprodukciju zvuka. Wio Terminal podržava SD kartice do 16 GB kapaciteta, a one moraju biti formatirane kao FAT32 ili exFAT.

### Zadatak - povezivanje ReSpeaker Pi Hat

1. Kada je Wio Terminal isključen, povežite ReSpeaker 2-Mics Pi Hat s Wio Terminalom koristeći skakače i GPIO utičnice na stražnjoj strani Wio Terminala:

    Pinovi se trebaju povezati na sljedeći način:

    ![Dijagram pinova](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.hr.png)

1. Postavite ReSpeaker i Wio Terminal tako da GPIO utičnice budu okrenute prema gore, s lijeve strane.

1. Počnite od utičnice u gornjem lijevom kutu GPIO utičnice na ReSpeakeru. Spojite skakač od gornje lijeve utičnice ReSpeakera do gornje lijeve utičnice Wio Terminala.

1. Ponavljajte ovaj postupak niz GPIO utičnice na lijevoj strani. Provjerite jesu li pinovi čvrsto povezani.

    ![ReSpeaker s lijevim pinovima povezanima s lijevim pinovima Wio Terminala](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.hr.png)

    ![ReSpeaker s lijevim pinovima povezanima s lijevim pinovima Wio Terminala](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.hr.png)

    > 💁 Ako su vaši skakači povezani u trake, držite ih zajedno - to olakšava osiguravanje da su svi kablovi povezani redom.

1. Ponavljajte postupak koristeći desne GPIO utičnice na ReSpeakeru i Wio Terminalu. Ovi kablovi trebaju ići oko već povezanih kablova.

    ![ReSpeaker s desnim pinovima povezanima s desnim pinovima Wio Terminala](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.hr.png)

    ![ReSpeaker s desnim pinovima povezanima s desnim pinovima Wio Terminala](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.hr.png)

    > 💁 Ako su vaši skakači povezani u trake, podijelite ih u dvije trake. Provedite jednu sa svake strane postojećih kablova.

    > 💁 Možete koristiti ljepljivu traku kako biste pričvrstili pinove u blok i spriječili njihovo ispadanje tijekom povezivanja.
    >
    > ![Pinovi pričvršćeni trakom](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.hr.png)

1. Trebat ćete dodati zvučnik.

    * Ako koristite zvučnik s JST kabelom, povežite ga s JST priključkom na ReSpeakeru.

      ![Zvučnik povezan s ReSpeakerom pomoću JST kabela](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.hr.png)

    * Ako koristite zvučnik s 3,5 mm priključkom ili slušalice, umetnite ih u utičnicu od 3,5 mm.

      ![Zvučnik povezan s ReSpeakerom putem utičnice od 3,5 mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.hr.png)

### Zadatak - postavljanje SD kartice

1. Povežite SD karticu s računalom, koristeći vanjski čitač ako nemate utor za SD karticu.

1. Formatirajte SD karticu koristeći odgovarajući alat na svom računalu, pazeći da koristite FAT32 ili exFAT datotečni sustav.

1. Umetnite SD karticu u utor za SD karticu na lijevoj strani Wio Terminala, odmah ispod gumba za uključivanje. Provjerite je li kartica potpuno umetnuta i klikne na mjesto - možda će vam trebati tanak alat ili druga SD kartica kako biste je potpuno umetnuli.

    ![Umetanje SD kartice u utor za SD karticu ispod prekidača za napajanje](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.hr.png)

    > 💁 Za izbacivanje SD kartice, trebate je lagano pritisnuti i ona će se izbaciti. Trebat će vam tanak alat poput odvijača ravnog vrha ili druga SD kartica.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva pogrešna tumačenja ili nesporazume koji proizlaze iz korištenja ovog prijevoda.