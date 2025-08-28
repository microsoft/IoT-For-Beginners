<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T08:35:48+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "ro"
}
-->
# Crearea unei mașini virtuale care rulează IoT Edge

În Azure, poți crea o mașină virtuală - un computer în cloud pe care îl poți configura cum dorești și pe care poți rula propriul software.

> 💁 Poți citi mai multe despre mașinile virtuale pe [pagina Mașină Virtuală de pe Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Sarcină - Configurarea unei mașini virtuale IoT Edge

1. Rulează următoarea comandă pentru a crea o mașină virtuală care are Azure IoT Edge deja preinstalat:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Înlocuiește `<vm_name>` cu un nume pentru această mașină virtuală. Acesta trebuie să fie unic la nivel global, așa că folosește ceva de genul `fruit-quality-detector-vm-` urmat de numele tău sau o altă valoare.

    Înlocuiește `<username>` și `<password>` cu un nume de utilizator și o parolă pentru a te conecta la mașina virtuală. Acestea trebuie să fie relativ sigure, deci nu poți folosi admin/password.

    Înlocuiește `<connection_string>` cu șirul de conexiune al dispozitivului tău IoT Edge `fruit-quality-detector-edge`.

    Aceasta va crea o mașină virtuală configurată ca o mașină virtuală `DS1 v2`. Aceste categorii indică cât de puternică este mașina și, prin urmare, cât costă. Această mașină virtuală are 1 CPU și 3.5GB de RAM.

    > 💰 Poți vedea prețurile actuale ale acestor mașini virtuale în [Ghidul de prețuri pentru mașinile virtuale Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Odată ce mașina virtuală a fost creată, runtime-ul IoT Edge va fi instalat automat și configurat pentru a se conecta la IoT Hub ca dispozitivul tău `fruit-quality-detector-edge`.

1. Vei avea nevoie fie de adresa IP, fie de numele DNS al mașinii virtuale pentru a apela clasificatorul de imagini de pe aceasta. Rulează următoarea comandă pentru a obține aceste informații:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copiază fie câmpul `PublicIps`, fie câmpul `Fqdns`.

1. Mașinile virtuale costă bani. La momentul redactării, o mașină virtuală DS1 costă aproximativ 0,06 USD pe oră. Pentru a reduce costurile, ar trebui să oprești mașina virtuală atunci când nu o folosești și să o ștergi când ai terminat proiectul.

    Poți configura mașina virtuală să se oprească automat la o anumită oră în fiecare zi. Astfel, dacă uiți să o oprești, nu vei fi taxat pentru mai mult decât timpul până la oprirea automată. Folosește următoarea comandă pentru a seta acest lucru:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Înlocuiește `<vm_name>` cu numele mașinii tale virtuale.

    Înlocuiește `<shutdown_time_utc>` cu ora UTC la care vrei ca mașina virtuală să se oprească, folosind 4 cifre în format HHMM. De exemplu, dacă vrei să se oprească la miezul nopții UTC, setează `0000`. Pentru ora 7:30PM pe coasta de vest a SUA, folosește `0230` (7:30PM pe coasta de vest a SUA este 2:30AM UTC).

1. Clasificatorul tău de imagini va rula pe acest dispozitiv edge, ascultând pe portul 80 (portul standard HTTP). În mod implicit, mașinile virtuale au porturile de intrare blocate, așa că va trebui să activezi portul 80. Porturile sunt activate pe grupurile de securitate a rețelei, așa că mai întâi trebuie să știi numele grupului de securitate a rețelei pentru mașina ta virtuală, pe care îl poți găsi cu următoarea comandă:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copiază valoarea câmpului `Name`.

1. Rulează următoarea comandă pentru a adăuga o regulă care să deschidă portul 80 în grupul de securitate a rețelei:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Înlocuiește `<nsg name>` cu numele grupului de securitate a rețelei din pasul anterior.

### Sarcină - gestionează mașina virtuală pentru a reduce costurile

1. Când nu folosești mașina virtuală, ar trebui să o oprești. Pentru a opri mașina virtuală, folosește următoarea comandă:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Înlocuiește `<vm_name>` cu numele mașinii tale virtuale.

    > 💁 Există o comandă `az vm stop` care va opri mașina virtuală, dar aceasta păstrează computerul alocat pentru tine, așa că vei plăti ca și cum ar fi încă în funcțiune.

1. Pentru a reporni mașina virtuală, folosește următoarea comandă:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Înlocuiește `<vm_name>` cu numele mașinii tale virtuale.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.