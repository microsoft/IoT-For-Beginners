<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T13:26:07+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "sl"
}
-->
# Pošiljanje obvestil z uporabo Twilio

## Navodila

V svoji kodi ste do sedaj le beležili razdaljo do geografske ograje. V tej nalogi boste morali dodati obvestilo, bodisi besedilno sporočilo ali e-pošto, ko so GPS koordinati znotraj geografske ograje.

Azure Functions ponuja veliko možnosti za povezave, vključno s storitvami tretjih oseb, kot je Twilio, komunikacijska platforma.

* Prijavite se za brezplačen račun na [Twilio.com](https://www.twilio.com)
* Preberite dokumentacijo o povezovanju Azure Functions s Twilio SMS na [Microsoft docs strani o Twilio povezavi za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Preberite dokumentacijo o povezovanju Azure Functions s Twilio SendGrid za pošiljanje e-pošte na [Microsoft docs strani o SendGrid povezavi za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Dodajte povezavo v svojo aplikacijo Functions, da boste obveščeni o GPS koordinatah bodisi znotraj bodisi zunaj geografske ograje - ne oboje.

## Merila ocenjevanja

| Merilo | Odlično | Zadostno | Potrebno izboljšanje |
| ------- | -------- | -------- | -------------------- |
| Konfiguracija povezav funkcij in prejem e-pošte ali SMS-a | Uspešno konfigurirane povezave funkcij in prejem e-pošte ali SMS-a, ko so znotraj ali zunaj geografske ograje, vendar ne oboje | Uspešno konfigurirane povezave, vendar neuspešno pošiljanje e-pošte ali SMS-a, ali pa je bilo sporočilo poslano tako znotraj kot zunaj geografske ograje | Neuspešna konfiguracija povezav in pošiljanje e-pošte ali SMS-a |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.