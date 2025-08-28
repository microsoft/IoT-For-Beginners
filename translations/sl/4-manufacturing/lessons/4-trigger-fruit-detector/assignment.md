<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T12:14:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "sl"
}
-->
# Zgradite detektor kakovosti sadja

## Navodila

Zgradite detektor kakovosti sadja!

Uporabite vse, kar ste se do zdaj naučili, in ustvarite prototip detektorja kakovosti sadja. Sprožite razvrščanje slik na podlagi bližine z uporabo AI modela, ki deluje na robu, shranite rezultate razvrščanja v shrambo in upravljajte LED lučko glede na zrelost sadja.

To bi morali sestaviti z uporabo kode, ki ste jo že napisali v vseh dosedanjih lekcijah.

## Merila ocenjevanja

| Merilo | Odlično | Zadostno | Potrebna izboljšava |
| ------- | -------- | -------- | ------------------- |
| Konfiguracija vseh storitev | Uspešno nastavil IoT Hub, aplikacijo Azure Functions in Azure Storage | Uspešno nastavil IoT Hub, vendar ne aplikacije Azure Functions ali Azure Storage | Ni uspel nastaviti nobene internetne IoT storitve |
| Spremljanje bližine in pošiljanje podatkov v IoT Hub, če je objekt bližje od vnaprej določene razdalje, ter sprožitev kamere prek ukaza | Uspešno izmeril razdaljo, poslal sporočilo v IoT Hub, ko je bil objekt dovolj blizu, in poslal ukaz za sprožitev kamere | Uspešno izmeril bližino in poslal podatke v IoT Hub, vendar ni uspel poslati ukaza za kamero | Ni uspel izmeriti razdalje, poslati sporočila v IoT Hub ali sprožiti ukaza |
| Zajem slike, njena razvrstitev in pošiljanje rezultatov v IoT Hub | Uspešno zajel sliko, jo razvrstil z uporabo robne naprave in poslal rezultate v IoT Hub | Uspešno razvrstil sliko, vendar ne z uporabo robne naprave, ali ni uspel poslati rezultatov v IoT Hub | Ni uspel razvrstiti slike |
| Vklop ali izklop LED lučke glede na rezultate razvrščanja z uporabo ukaza, poslanega napravi | Uspešno vklopil LED lučko prek ukaza, če je bilo sadje nezrelo | Uspešno poslal ukaz napravi, vendar ni uspel upravljati LED lučke | Ni uspel poslati ukaza za upravljanje LED lučke |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.