<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T08:56:10+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "ro"
}
-->
# Anulează temporizatorul

## Instrucțiuni

Până acum, în această lecție, ai antrenat un model pentru a înțelege setarea unui temporizator. O altă funcție utilă este anularea unui temporizator - poate pâinea ta este gata și poate fi scoasă din cuptor înainte ca temporizatorul să expire.

Adaugă o nouă intenție în aplicația ta LUIS pentru a anula temporizatorul. Nu va avea nevoie de entități, dar va necesita câteva exemple de propoziții. Gestionează acest lucru în codul tău serverless dacă este intenția principală, logând faptul că intenția a fost recunoscută și returnând un răspuns adecvat.

## Criterii de evaluare

| Criterii | Exemplu excelent | Adequat | Necesită îmbunătățiri |
| -------- | ---------------- | ------- | --------------------- |
| Adaugă intenția de anulare a temporizatorului în aplicația LUIS | A reușit să adauge intenția și să antreneze modelul | A reușit să adauge intenția, dar nu să antreneze modelul | Nu a reușit să adauge intenția și să antreneze modelul |
| Gestionează intenția în aplicația serverless | A reușit să detecteze intenția ca fiind cea principală și să o logheze | A reușit să detecteze intenția ca fiind cea principală | Nu a reușit să detecteze intenția ca fiind cea principală |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.