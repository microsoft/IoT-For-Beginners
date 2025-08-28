<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T13:36:38+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "sl"
}
-->
# Preiskovanje vezav funkcij

## Navodila

Vezave funkcij omogočajo, da vaša koda shranjuje blob podatke v blob shrambo tako, da jih vrne iz funkcije `main`. Azure Storage račun, zbirka in druge podrobnosti so konfigurirane v datoteki `function.json`.

Pri delu z Azure ali drugimi Microsoftovimi tehnologijami so najboljši vir informacij [Microsoftova dokumentacija na docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). V tej nalogi boste morali prebrati dokumentacijo o vezavah za Azure Functions, da ugotovite, kako nastaviti izhodno vezavo.

Nekatere strani, ki jih lahko pregledate za začetek, so:

* [Koncepti sprožilcev in vezav za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Pregled vezav za Azure Blob shrambo za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Izhodna vezava za Azure Blob shrambo za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Merila

| Merila | Odlično | Zadostno | Potrebne izboljšave |
| ------- | -------- | -------- | ------------------- |
| Konfiguracija izhodne vezave za blob shrambo | Uspešno konfigurirana izhodna vezava, vrnjen blob in uspešno shranjen v blob shrambo | Uspešno konfigurirana izhodna vezava ali vrnjen blob, vendar ni bil uspešno shranjen v blob shrambo | Ni uspelo konfigurirati izhodne vezave |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.