<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T12:39:09+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "hr"
}
-->
# Otkaži mjerač vremena

## Upute

Do sada ste u ovoj lekciji trenirali model za razumijevanje postavljanja mjerača vremena. Još jedna korisna funkcija je otkazivanje mjerača vremena - možda je kruh gotov i može se izvaditi iz pećnice prije nego što mjerač vremena istekne.

Dodajte novi intent u svoju LUIS aplikaciju za otkazivanje mjerača vremena. Neće trebati nikakve entitete, ali će trebati nekoliko primjera rečenica. Obradite ovo u svom serverless kodu ako je to glavni intent, zabilježite da je intent prepoznat i vratite odgovarajući odgovor.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | -------- | --------------- | -------------------- |
| Dodavanje intenta za otkazivanje mjerača vremena u LUIS aplikaciju | Uspješno dodan intent i model je treniran | Uspješno dodan intent, ali model nije treniran | Nije uspjelo dodavanje intenta i treniranje modela |
| Obrada intenta u serverless aplikaciji | Uspješno prepoznat intent kao glavni i zabilježen | Uspješno prepoznat intent kao glavni | Nije uspjelo prepoznavanje intenta kao glavnog |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za nesporazume ili pogrešne interpretacije koje mogu proizaći iz korištenja ovog prijevoda.