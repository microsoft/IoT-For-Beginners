<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T08:36:42+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "ro"
}
-->
# Rularea altor servicii la margine

## Instrucțiuni

Nu doar clasificatoarele de imagini pot fi rulate la margine, orice poate fi împachetat într-un container poate fi implementat pe un dispozitiv IoT Edge. Codul serverless care rulează ca Azure Functions, cum ar fi trigger-ele pe care le-ai creat în lecțiile anterioare, poate fi rulat în containere și, prin urmare, pe IoT Edge.

Alege una dintre lecțiile anterioare și încearcă să rulezi aplicația Azure Functions într-un container IoT Edge. Poți găsi un ghid care arată cum să faci acest lucru folosind un alt proiect de aplicație Functions în [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Criterii de evaluare

| Criterii | Exemplu | Adequat | Necesită îmbunătățiri |
| -------- | ------- | ------- | --------------------- |
| Implementarea unei aplicații Azure Functions pe IoT Edge | A reușit să implementeze o aplicație Azure Functions pe IoT Edge și să o folosească cu un dispozitiv IoT pentru a rula un trigger din datele IoT | A reușit să implementeze o aplicație Functions pe IoT Edge, dar nu a reușit să declanșeze trigger-ul | Nu a reușit să implementeze o aplicație Functions pe IoT Edge |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.