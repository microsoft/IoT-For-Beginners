<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T11:44:41+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "ro"
}
-->
# Construiește un ciclu de udare mai eficient

## Instrucțiuni

Această lecție a acoperit modul de control al unui releu prin intermediul datelor de la senzori, iar acel releu ar putea, la rândul său, să controleze o pompă pentru un sistem de irigație. Pentru o anumită cantitate de sol, funcționarea pompei pentru o durată fixă de timp ar trebui să aibă întotdeauna același impact asupra umidității solului. Acest lucru înseamnă că poți estima câte secunde de irigare corespund unei anumite scăderi a citirii umidității solului. Folosind aceste date, poți construi un sistem de irigație mai controlat.

Pentru această sarcină, vei calcula cât timp ar trebui să funcționeze pompa pentru a obține o creștere specifică a umidității solului.

> ⚠️ Dacă folosești hardware IoT virtual, poți parcurge acest proces, dar simulează rezultatele prin creșterea manuală a citirii umidității solului cu o valoare fixă pe secundă cât timp releul este activ.

1. Începe cu sol uscat. Măsoară umiditatea solului.

1. Adaugă o cantitate fixă de apă, fie prin funcționarea pompei timp de 1 secundă, fie prin turnarea unei cantități fixe de apă.

    > Pompa ar trebui să funcționeze întotdeauna la o rată constantă, astfel încât fiecare secundă de funcționare să furnizeze aceeași cantitate de apă.

1. Așteaptă până când nivelul de umiditate al solului se stabilizează și ia o citire.

1. Repetă acest proces de mai multe ori și creează un tabel cu rezultatele. Un exemplu de tabel este dat mai jos.

    | Timp total pompă | Umiditate sol | Scădere |
    | --- | --: | -: |
    | Uscat | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calculează o creștere medie a umidității solului pe secundă de apă. În exemplul de mai sus, fiecare secundă de apă scade citirea cu o medie de 20.3.

1. Folosește aceste date pentru a îmbunătăți eficiența codului serverului, funcționând pompa pentru timpul necesar pentru a aduce umiditatea solului la nivelul dorit.

## Criterii de evaluare

| Criterii | Exemplară | Adecvată | Necesită îmbunătățiri |
| -------- | --------- | -------- | --------------------- |
| Capturarea datelor despre umiditatea solului | Este capabil să captureze multiple citiri după adăugarea unor cantități fixe de apă | Este capabil să captureze câteva citiri cu cantități fixe de apă | Poate captura doar una sau două citiri, sau nu poate folosi cantități fixe de apă |
| Calibrarea codului serverului | Este capabil să calculeze o scădere medie a citirii umidității solului și să actualizeze codul serverului pentru a folosi această valoare | Este capabil să calculeze o scădere medie, dar nu poate actualiza codul serverului, sau nu poate calcula corect o medie, dar folosește această valoare pentru a actualiza corect codul serverului | Nu este capabil să calculeze o medie sau să actualizeze codul serverului |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.