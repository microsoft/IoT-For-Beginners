<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T12:01:20+00:00",
  "source_file": "clean-up.md",
  "language_code": "hr"
}
-->
# Očistite svoj projekt

Nakon što završite svaki projekt, dobro je izbrisati svoje cloud resurse.

Tijekom lekcija za svaki projekt, možda ste kreirali neke od sljedećih resursa:

* Grupu resursa
* IoT Hub
* Registracije IoT uređaja
* Račun za pohranu
* Functions App
* Azure Maps račun
* Projekt za prilagođenu viziju
* Azure Container Registry
* Resurs za kognitivne usluge

Većina ovih resursa neće imati troškove - ili su potpuno besplatni, ili koristite besplatni sloj. Za usluge koje zahtijevaju plaćeni sloj, koristili ste ih na razini koja je uključena u besplatnu kvotu ili će vas koštati samo nekoliko centi.

Čak i uz relativno niske troškove, vrijedi izbrisati ove resurse kada završite. Na primjer, možete imati samo jedan IoT Hub koji koristi besplatni sloj, pa ako želite stvoriti drugi, morat ćete koristiti plaćeni sloj.

Svi vaši resursi kreirani su unutar grupa resursa, što olakšava upravljanje. Možete izbrisati grupu resursa, a svi resursi unutar te grupe bit će izbrisani zajedno s njom.

Za brisanje grupe resursa, pokrenite sljedeću naredbu u svom terminalu ili naredbenom retku:

```sh
az group delete --name <resource-group-name>
```

Zamijenite `<resource-group-name>` imenom grupe resursa koja vas zanima.

Pojavit će se potvrda:

```output
Are you sure you want to perform this operation? (y/n): 
```

Unesite `y` za potvrdu i brisanje grupe resursa.

Trebat će neko vrijeme da se izbrišu svi resursi.

> 💁 Više o brisanju grupa resursa možete pročitati u [dokumentaciji o brisanju grupa resursa i resursa na Azure Resource Manageru na Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.