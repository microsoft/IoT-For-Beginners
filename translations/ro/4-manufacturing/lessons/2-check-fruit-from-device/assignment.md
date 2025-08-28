<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T08:47:15+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "ro"
}
-->
# Răspunde la rezultatele clasificării

## Instrucțiuni

Dispozitivul tău a clasificat imagini și are valorile pentru predicții. Dispozitivul tău ar putea folosi aceste informații pentru a face ceva - ar putea trimite datele către IoT Hub pentru procesare de către alte sisteme sau ar putea controla un actuator, cum ar fi un LED, care se aprinde atunci când fructul este necopt.

Adaugă cod pe dispozitivul tău pentru a răspunde într-un mod ales de tine - fie trimite date către un IoT Hub, controlează un actuator, sau combină cele două și trimite date către un IoT Hub cu un cod serverless care determină dacă fructul este copt sau nu și trimite înapoi o comandă pentru a controla un actuator.

## Criterii de evaluare

| Criteriu | Exemplu | Adecvat | Necesită îmbunătățiri |
| -------- | -------- | ------- | --------------------- |
| Răspuns la predicții | A reușit să implementeze un răspuns la predicții care funcționează constant cu predicții de aceeași valoare. | A reușit să implementeze un răspuns care nu depinde de predicții, cum ar fi doar trimiterea datelor brute către un IoT Hub. | Nu a reușit să programeze dispozitivul pentru a răspunde la predicții. |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.