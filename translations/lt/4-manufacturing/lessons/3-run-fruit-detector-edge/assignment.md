<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T19:07:36+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "lt"
}
-->
# Paleiskite kitas paslaugas krašte

## Instrukcijos

Krašte galima paleisti ne tik vaizdų klasifikatorius – bet ką, kas gali būti supakuota į konteinerį, galima diegti į IoT Edge įrenginį. Serverless kodas, veikiantis kaip Azure Functions, pavyzdžiui, trigeriai, kuriuos sukūrėte ankstesnėse pamokose, gali būti paleistas konteineriuose, o tai reiškia, kad jis gali veikti ir IoT Edge.

Pasirinkite vieną iš ankstesnių pamokų ir pabandykite paleisti Azure Functions programėlę IoT Edge konteineryje. Gidą, kuris parodo, kaip tai padaryti naudojant kitą Functions programėlės projektą, galite rasti [Pamokoje: Azure Functions diegimas kaip IoT Edge moduliai Microsoft dokumentacijoje](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinti |
| ---------- | ------- | ---------- | ------------------ |
| Azure Functions programėlės diegimas į IoT Edge | Sėkmingai įdiegė Azure Functions programėlę į IoT Edge ir naudojo ją su IoT įrenginiu, kad paleistų trigerį iš IoT duomenų | Sėkmingai įdiegė Functions programėlę į IoT Edge, bet nepavyko paleisti trigerio | Nepavyko įdiegti Functions programėlės į IoT Edge |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.