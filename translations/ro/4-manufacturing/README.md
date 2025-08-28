<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T08:15:31+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "ro"
}
-->
# Producție și procesare - utilizarea IoT pentru îmbunătățirea procesării alimentelor

Odată ce alimentele ajung la un centru de colectare sau la o fabrică de procesare, nu sunt întotdeauna trimise direct către supermarketuri. De multe ori, alimentele trec prin mai multe etape de procesare, cum ar fi sortarea în funcție de calitate. Acesta era un proces manual - începea pe câmp, când culegătorii alegeau doar fructele coapte, iar apoi, la fabrică, fructele erau transportate pe o bandă rulantă, iar angajații eliminau manual fructele lovite sau stricate. După ce am cules și sortat căpșuni ca job de vară în timpul școlii, pot confirma că nu este o muncă plăcută.

Configurațiile mai moderne se bazează pe IoT pentru sortare. Unele dintre cele mai timpurii dispozitive, cum ar fi sortatoarele de la [Weco](https://wecotek.com), folosesc senzori optici pentru a detecta calitatea produselor, respingând, de exemplu, roșiile verzi. Acestea pot fi utilizate în combinele agricole direct pe câmp sau în fabricile de procesare.

Pe măsură ce se fac progrese în Inteligența Artificială (AI) și Învățarea Automată (ML), aceste mașini pot deveni mai avansate, folosind modele ML antrenate pentru a distinge între fructe și obiecte străine, cum ar fi pietre, pământ sau insecte. Aceste modele pot fi, de asemenea, antrenate pentru a detecta calitatea fructelor, nu doar fructele lovite, ci și pentru detectarea timpurie a bolilor sau altor probleme ale culturilor.

> 🎓 Termenul *model ML* se referă la rezultatul antrenării unui software de învățare automată pe un set de date. De exemplu, poți antrena un model ML pentru a distinge între roșii coapte și necoapte, apoi să folosești modelul pe imagini noi pentru a verifica dacă roșiile sunt coapte sau nu.

În aceste 4 lecții vei învăța cum să antrenezi modele AI bazate pe imagini pentru a detecta calitatea fructelor, cum să le utilizezi de pe un dispozitiv IoT și cum să le rulezi la margine - adică pe un dispozitiv IoT, nu în cloud.

> 💁 Aceste lecții vor folosi unele resurse din cloud. Dacă nu finalizezi toate lecțiile din acest proiect, asigură-te că [eliberezi resursele proiectului](../clean-up.md).

## Subiecte

1. [Antrenează un detector de calitate a fructelor](./lessons/1-train-fruit-detector/README.md)
1. [Verifică calitatea fructelor de pe un dispozitiv IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Rulează detectorul de fructe la margine](./lessons/3-run-fruit-detector-edge/README.md)
1. [Declanșează detectarea calității fructelor de la un senzor](./lessons/4-trigger-fruit-detector/README.md)

## Credite

Toate lecțiile au fost scrise cu ♥️ de [Jen Fox](https://github.com/jenfoxbot) și [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă utilizarea unei traduceri profesionale realizate de un specialist. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.