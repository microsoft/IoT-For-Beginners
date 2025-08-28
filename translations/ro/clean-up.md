<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T08:13:00+00:00",
  "source_file": "clean-up.md",
  "language_code": "ro"
}
-->
# Curăță-ți proiectul

După ce finalizezi fiecare proiect, este bine să ștergi resursele din cloud.

În lecțiile pentru fiecare proiect, este posibil să fi creat unele dintre următoarele:

* Un Resource Group
* Un IoT Hub
* Înregistrări de dispozitive IoT
* Un Storage Account
* O Functions App
* Un cont Azure Maps
* Un proiect de custom vision
* Un Azure Container Registry
* O resursă de cognitive services

Majoritatea acestor resurse nu vor genera costuri - fie sunt complet gratuite, fie utilizezi un nivel gratuit. Pentru serviciile care necesită un nivel plătit, le-ai folosit la un nivel inclus în alocația gratuită sau care va costa doar câțiva cenți.

Chiar și cu costurile relativ mici, merită să ștergi aceste resurse după ce ai terminat. De exemplu, poți avea un singur IoT Hub utilizând nivelul gratuit, așa că, dacă vrei să creezi altul, va trebui să folosești un nivel plătit.

Toate serviciile tale au fost create în interiorul Resource Groups, ceea ce face gestionarea mai ușoară. Poți șterge Resource Group, iar toate serviciile din acel Resource Group vor fi șterse împreună cu acesta.

Pentru a șterge Resource Group, rulează următoarea comandă în terminalul sau linia ta de comandă:

```sh
az group delete --name <resource-group-name>
```

Înlocuiește `<resource-group-name>` cu numele Resource Group-ului care te interesează.

Va apărea o confirmare:

```output
Are you sure you want to perform this operation? (y/n): 
```

Introdu `y` pentru a confirma și a șterge Resource Group.

Va dura ceva timp pentru a șterge toate serviciile.

> 💁 Poți citi mai multe despre ștergerea grupurilor de resurse în [documentația despre ștergerea grupurilor de resurse și resurselor din Azure Resource Manager pe Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.