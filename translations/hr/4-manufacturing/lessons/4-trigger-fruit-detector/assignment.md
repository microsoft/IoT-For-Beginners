<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T12:13:57+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "hr"
}
-->
# Izgradite detektor kvalitete voća

## Upute

Izradite detektor kvalitete voća!

Iskoristite sve što ste dosad naučili i izradite prototip detektora kvalitete voća. Aktivirajte klasifikaciju slika na temelju blizine koristeći AI model koji radi na rubu, pohranite rezultate klasifikacije u spremište i kontrolirajte LED svjetlo ovisno o zrelosti voća.

Trebali biste moći sastaviti ovo koristeći kod koji ste prethodno napisali u svim dosadašnjim lekcijama.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | --------------- | -------------------- |
| Konfiguracija svih usluga | Uspješno postavljen IoT Hub, aplikacija za Azure funkcije i Azure spremište | Uspješno postavljen IoT Hub, ali ne i aplikacija za Azure funkcije ili Azure spremište | Nije uspio postaviti nijednu IoT internetsku uslugu |
| Praćenje blizine i slanje podataka u IoT Hub ako je objekt bliže od unaprijed definirane udaljenosti te aktiviranje kamere putem naredbe | Uspješno izmjerena udaljenost i poslana poruka u IoT Hub kada je objekt dovoljno blizu, te poslana naredba za aktiviranje kamere | Uspješno izmjerena blizina i poslano u IoT Hub, ali nije poslana naredba kameri | Nije uspio izmjeriti udaljenost i poslati poruku u IoT Hub ili aktivirati naredbu |
| Snimanje slike, klasifikacija i slanje rezultata u IoT Hub | Uspješno snimljena slika, klasificirana pomoću uređaja na rubu i poslani rezultati u IoT Hub | Uspješno klasificirana slika, ali ne pomoću uređaja na rubu, ili rezultati nisu poslani u IoT Hub | Nije uspio klasificirati sliku |
| Uključivanje ili isključivanje LED svjetla ovisno o rezultatima klasifikacije putem naredbe poslanoj uređaju | Uspješno uključeno LED svjetlo putem naredbe ako je voće nezrelo | Uspješno poslana naredba uređaju, ali nije kontrolirano LED svjetlo | Nije uspio poslati naredbu za kontrolu LED svjetla |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.