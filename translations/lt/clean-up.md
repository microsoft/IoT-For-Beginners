<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T18:56:52+00:00",
  "source_file": "clean-up.md",
  "language_code": "lt"
}
-->
# Išvalykite savo projektą

Baigę kiekvieną projektą, verta ištrinti debesų išteklius.

Pamokose, skirtose kiekvienam projektui, galėjote sukurti kai kuriuos iš šių išteklių:

* Išteklių grupę
* IoT centrą
* IoT įrenginių registracijas
* Saugyklos paskyrą
* Funkcijų programą
* Azure Maps paskyrą
* Individualų vaizdų atpažinimo projektą
* Azure konteinerių registrą
* Kognityvinių paslaugų išteklių

Dauguma šių išteklių nekainuos - jie arba visiškai nemokami, arba naudojate nemokamą planą. Paslaugoms, kurioms reikalingas mokamas planas, greičiausiai naudojote lygį, kuris įtrauktas į nemokamą kvotą, arba jos kainuos tik kelis centus.

Net ir esant palyginti mažoms išlaidoms, verta ištrinti šiuos išteklius, kai baigiate darbą. Pavyzdžiui, galite turėti tik vieną IoT centrą, naudojantį nemokamą planą, todėl, jei norėsite sukurti kitą, turėsite naudoti mokamą planą.

Visi jūsų paslaugos buvo sukurtos išteklių grupėse, ir tai palengvina valdymą. Galite ištrinti išteklių grupę, ir visi tos grupės ištekliai bus ištrinti kartu su ja.

Norėdami ištrinti išteklių grupę, terminale arba komandų eilutėje paleiskite šią komandą:

```sh
az group delete --name <resource-group-name>
```

Pakeiskite `<resource-group-name>` į jus dominančios išteklių grupės pavadinimą.

Pasirodys patvirtinimas:

```output
Are you sure you want to perform this operation? (y/n): 
```

Įveskite `y`, kad patvirtintumėte ir ištrintumėte išteklių grupę.

Visų paslaugų ištrynimas užtruks šiek tiek laiko.

> 💁 Daugiau apie išteklių grupių ištrynimą galite perskaityti [Azure Resource Manager išteklių grupių ir išteklių ištrynimo dokumentacijoje Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.