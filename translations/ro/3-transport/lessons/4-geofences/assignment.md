<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T09:46:34+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "ro"
}
-->
# Trimiterea notificărilor folosind Twilio

## Instrucțiuni

Până acum, în codul tău ai înregistrat doar distanța față de geofence. În această sarcină, va trebui să adaugi o notificare, fie un mesaj text, fie un email, atunci când coordonatele GPS se află în interiorul geofence-ului.

Azure Functions oferă multe opțiuni pentru legături, inclusiv cu servicii terțe, cum ar fi Twilio, o platformă de comunicații.

* Creează un cont gratuit pe [Twilio.com](https://www.twilio.com)
* Citește documentația despre legarea Azure Functions la Twilio SMS pe pagina [Microsoft docs Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Citește documentația despre legarea Azure Functions la Twilio SendGrid pentru a trimite emailuri pe pagina [Microsoft docs Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Adaugă legătura în aplicația ta Functions pentru a fi notificat atunci când coordonatele GPS sunt fie în interiorul, fie în afara geofence-ului - nu în ambele cazuri.

## Criterii de evaluare

| Criterii | Exemplu | Adequat | Necesită îmbunătățiri |
| -------- | ------- | ------- | --------------------- |
| Configurarea legăturilor funcțiilor și primirea unui email sau SMS | A reușit să configureze legăturile funcțiilor și să primească un email sau SMS atunci când coordonatele sunt în interiorul sau în afara geofence-ului, dar nu în ambele cazuri | A reușit să configureze legăturile, dar nu a reușit să trimită emailul sau SMS-ul, sau a reușit să trimită doar atunci când coordonatele erau atât în interiorul, cât și în afara geofence-ului | Nu a reușit să configureze legăturile și să trimită un email sau SMS |

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.