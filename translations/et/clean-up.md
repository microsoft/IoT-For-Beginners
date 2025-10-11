<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-10-11T11:16:32+00:00",
  "source_file": "clean-up.md",
  "language_code": "et"
}
-->
# Korista oma projekt

Pärast iga projekti lõpetamist on hea oma pilveressursid kustutada.

Iga projekti õppetundides võisid sa luua mõningaid järgmistest:

* Ressursigrupp
* IoT Hub
* IoT seadme registreeringud
* Salvestuskonto
* Funktsioonide rakendus
* Azure Maps konto
* Kohandatud visiooniprojekt
* Azure Container Registry
* Kognitiivsete teenuste ressurss

Enamik neist ressurssidest ei tekita kulusid – kas need on täiesti tasuta või sa kasutasid tasuta taset. Teenuste puhul, mis nõuavad tasulist taset, kasutasid sa neid tõenäoliselt tasemel, mis on tasuta limiidi sees, või maksid vaid mõne sendi.

Isegi suhteliselt madalate kulude korral tasub need ressursid kustutada, kui oled lõpetanud. Näiteks saab tasuta tasemel kasutada ainult ühte IoT Hubi, nii et kui soovid luua teise, pead kasutama tasulist taset.

Kõik sinu teenused loodi ressursigruppide sees, mis teeb haldamise lihtsamaks. Sa saad kustutada ressursigrupi, ja kõik teenused selles ressursigrupis kustutatakse koos sellega.

Ressursigrupi kustutamiseks käivita oma terminalis või käsureal järgmine käsk:

```sh
az group delete --name <resource-group-name>
```

Asenda `<resource-group-name>` selle ressursigrupi nimega, mis sind huvitab.

Ilmub kinnitus:

```output
Are you sure you want to perform this operation? (y/n): 
```

Sisesta `y`, et kinnitada ja kustutada ressursigrupp.

Kõigi teenuste kustutamine võtab aega.

> 💁 Sa saad lugeda rohkem ressursigruppide kustutamise kohta [Microsofti dokumentatsioonist Azure Resource Manageri ressursigruppide ja ressursside kustutamise kohta](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.