<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T12:01:31+00:00",
  "source_file": "clean-up.md",
  "language_code": "sl"
}
-->
# Počistite svoj projekt

Ko dokončate vsak projekt, je dobro, da izbrišete svoje oblačne vire.

V lekcijah za vsak projekt ste morda ustvarili nekaj od naslednjega:

* Skupino virov (Resource Group)
* IoT Hub
* Registracije IoT naprav
* Račun za shranjevanje (Storage Account)
* Aplikacijo Functions
* Račun za Azure Maps
* Projekt za prilagojeno vizijo (custom vision project)
* Register za Azure Container (Azure Container Registry)
* Vir za kognitivne storitve (cognitive services resource)

Večina teh virov ne bo imela stroškov – bodisi so popolnoma brezplačni, bodisi uporabljate brezplačno raven. Za storitve, ki zahtevajo plačljivo raven, ste jih uporabljali na ravni, ki je vključena v brezplačno kvoto, ali pa vas bodo stale le nekaj centov.

Tudi ob relativno nizkih stroških se splača te vire izbrisati, ko končate. Na primer, lahko imate samo en IoT Hub, ki uporablja brezplačno raven, zato boste morali za ustvarjanje novega uporabiti plačljivo raven.

Vsi vaši viri so bili ustvarjeni znotraj skupin virov (Resource Groups), kar olajša upravljanje. Lahko izbrišete skupino virov, in vsi viri v tej skupini bodo izbrisani skupaj z njo.

Za brisanje skupine virov zaženite naslednji ukaz v svojem terminalu ali ukazni vrstici:

```sh
az group delete --name <resource-group-name>
```

Zamenjajte `<resource-group-name>` z imenom skupine virov, ki vas zanima.

Pojavi se potrditev:

```output
Are you sure you want to perform this operation? (y/n): 
```

Vnesite `y`, da potrdite in izbrišete skupino virov.

Brisanje vseh storitev bo trajalo nekaj časa.

> 💁 Več o brisanju skupin virov lahko preberete v [dokumentaciji o brisanju skupin virov in virov na Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.