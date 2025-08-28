<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T08:28:07+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "ro"
}
-->
# Construiește un detector de calitate a fructelor

## Instrucțiuni

Construiește detectorul de calitate a fructelor!

Folosește tot ce ai învățat până acum pentru a crea prototipul detectorului de calitate a fructelor. Activează clasificarea imaginilor pe baza proximității utilizând un model AI care rulează la margine, stochează rezultatele clasificării și controlează un LED în funcție de gradul de coacere al fructului.

Ar trebui să poți pune totul cap la cap folosind codul pe care l-ai scris în lecțiile anterioare.

## Criterii de evaluare

| Criteriu | Exemplu | Adecvat | Necesită îmbunătățiri |
| -------- | --------- | -------- | ----------------- |
| Configurarea tuturor serviciilor | A reușit să configureze un IoT Hub, o aplicație Azure Functions și stocare Azure | A reușit să configureze IoT Hub, dar nu și aplicația Azure Functions sau stocarea Azure | Nu a reușit să configureze niciun serviciu IoT |
| Monitorizarea proximității și trimiterea datelor către IoT Hub dacă un obiect este mai aproape decât o distanță predefinită și activarea camerei printr-o comandă | A reușit să măsoare distanța, să trimită un mesaj către IoT Hub când un obiect este suficient de aproape și să trimită o comandă pentru a activa camera | A reușit să măsoare proximitatea și să trimită date către IoT Hub, dar nu a reușit să trimită o comandă către cameră | Nu a reușit să măsoare distanța, să trimită un mesaj către IoT Hub sau să activeze o comandă |
| Capturarea unei imagini, clasificarea acesteia și trimiterea rezultatelor către IoT Hub | A reușit să captureze o imagine, să o clasifice utilizând un dispozitiv edge și să trimită rezultatele către IoT Hub | A reușit să clasifice imaginea, dar nu utilizând un dispozitiv edge, sau nu a reușit să trimită rezultatele către IoT Hub | Nu a reușit să clasifice o imagine |
| Pornirea sau oprirea LED-ului în funcție de rezultatele clasificării utilizând o comandă trimisă către un dispozitiv | A reușit să pornească un LED printr-o comandă dacă fructul era necopt | A reușit să trimită comanda către dispozitiv, dar nu a reușit să controleze LED-ul | Nu a reușit să trimită o comandă pentru a controla LED-ul |

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.