<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T09:30:51+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "ro"
}
-->
# Construiește un translator universal

## Instrucțiuni

Un translator universal este un dispozitiv care poate traduce între mai multe limbi, permițând oamenilor care vorbesc limbi diferite să comunice. Folosește ceea ce ai învățat în lecțiile anterioare pentru a construi un translator universal utilizând 2 dispozitive IoT.

> Dacă nu ai 2 dispozitive, urmează pașii din lecțiile anterioare pentru a configura un dispozitiv IoT virtual ca unul dintre dispozitivele IoT.

Ar trebui să configurezi un dispozitiv pentru o limbă și altul pentru o altă limbă. Fiecare dispozitiv ar trebui să accepte vorbirea, să o convertească în text, să o trimită către celălalt dispozitiv prin IoT Hub și o aplicație Functions, apoi să o traducă și să redea vorbirea tradusă.

> 💁 Sfat: Când trimiți vorbirea de la un dispozitiv la altul, trimite și informația despre limba în care este, pentru a face traducerea mai ușoară. Ai putea chiar să faci ca fiecare dispozitiv să se înregistreze folosind IoT Hub și o aplicație Functions mai întâi, transmițând limba pe care o suportă pentru a fi stocată în Azure Storage. Apoi, poți folosi o aplicație Functions pentru a face traducerile, trimițând textul tradus către dispozitivul IoT.

## Criterii de evaluare

| Criteriu | Exemplu | Adecvat | Necesită îmbunătățiri |
| -------- | ------- | ------- | --------------------- |
| Construiește un translator universal | A reușit să construiască un translator universal, convertind vorbirea detectată de un dispozitiv în vorbirea redată de alt dispozitiv într-o limbă diferită | A reușit să facă să funcționeze unele componente, cum ar fi captarea vorbirii sau traducerea, dar nu a reușit să construiască soluția completă | Nu a reușit să construiască nicio parte a unui translator universal funcțional |

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.