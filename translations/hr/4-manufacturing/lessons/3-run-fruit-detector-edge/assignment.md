<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T12:21:49+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "hr"
}
-->
# Pokretanje drugih servisa na rubu mreže

## Upute

Na rubu mreže ne mogu se pokretati samo klasifikatori slika, već bilo što što se može zapakirati u kontejner može se implementirati na IoT Edge uređaj. Bezserverski kod koji se izvršava kao Azure Functions, poput okidača koje ste kreirali u prethodnim lekcijama, može se pokretati u kontejnerima, a samim time i na IoT Edge uređaju.

Odaberite jednu od prethodnih lekcija i pokušajte pokrenuti Azure Functions aplikaciju u IoT Edge kontejneru. Vodič koji pokazuje kako to učiniti koristeći drugačiji projekt Functions aplikacije možete pronaći u [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | --------------- | -------------------- |
| Implementacija Azure Functions aplikacije na IoT Edge | Uspješno implementirana Azure Functions aplikacija na IoT Edge i korištena s IoT uređajem za pokretanje okidača iz IoT podataka | Uspješno implementirana Functions aplikacija na IoT Edge, ali okidač nije uspio pokrenuti | Nije uspjelo implementirati Functions aplikaciju na IoT Edge |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.