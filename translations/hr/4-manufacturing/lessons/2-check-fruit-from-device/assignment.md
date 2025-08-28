<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T12:31:00+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "hr"
}
-->
# Odgovor na rezultate klasifikacije

## Upute

Vaš uređaj je klasificirao slike i ima vrijednosti za predikcije. Uređaj može koristiti te informacije za određene radnje - može ih poslati na IoT Hub za obradu od strane drugih sustava ili može kontrolirati aktuator, poput LED diode, koja se pali kada voće nije zrelo.

Dodajte kod na svoj uređaj kako bi odgovorio na način koji odaberete - bilo da šalje podatke na IoT Hub, kontrolira aktuator ili kombinira oba pristupa i šalje podatke na IoT Hub uz serverless kod koji određuje je li voće zrelo ili nije te šalje naredbu za kontrolu aktuatora.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | -------- | --------------- | -------------------- |
| Odgovor na predikcije | Uspješno implementiran odgovor na predikcije koji dosljedno radi s predikcijama iste vrijednosti. | Uspješno implementiran odgovor koji nije ovisan o predikcijama, poput slanja sirovih podataka na IoT Hub. | Nije uspio programirati uređaj da odgovori na predikcije. |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.