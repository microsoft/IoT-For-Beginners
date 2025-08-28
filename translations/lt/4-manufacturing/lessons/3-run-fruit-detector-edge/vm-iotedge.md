<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T19:07:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "lt"
}
-->
# Sukurkite virtualią mašiną, veikiančią su IoT Edge

Azure platformoje galite sukurti virtualią mašiną – kompiuterį debesyje, kurį galite konfigūruoti pagal savo poreikius ir paleisti savo programinę įrangą.

> 💁 Daugiau apie virtualias mašinas galite perskaityti [Virtualių mašinų puslapyje Vikipedijoje](https://wikipedia.org/wiki/Virtual_machine).

## Užduotis - Nustatykite IoT Edge virtualią mašiną

1. Paleiskite šią komandą, kad sukurtumėte virtualią mašiną, kurioje jau įdiegta Azure IoT Edge:

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

    Pakeiskite `<vm_name>` į norimą virtualios mašinos pavadinimą. Jis turi būti unikalus visame pasaulyje, todėl naudokite, pavyzdžiui, `fruit-quality-detector-vm-` su savo vardu ar kitu reikšmingu priedu.

    Pakeiskite `<username>` ir `<password>` į vartotojo vardą ir slaptažodį, kuriuos naudosite prisijungdami prie virtualios mašinos. Jie turi būti pakankamai saugūs, todėl negalite naudoti, pavyzdžiui, admin/password.

    Pakeiskite `<connection_string>` į savo `fruit-quality-detector-edge` IoT Edge įrenginio prisijungimo eilutę.

    Ši komanda sukurs virtualią mašiną, sukonfigūruotą kaip `DS1 v2`. Šios kategorijos nurodo mašinos galingumą ir atitinkamai jos kainą. Ši virtuali mašina turi 1 procesorių ir 3,5 GB RAM.

    > 💰 Dabartines šių virtualių mašinų kainas galite peržiūrėti [Azure Virtualių mašinų kainų vadove](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Kai virtuali mašina bus sukurta, IoT Edge vykdymo aplinka bus automatiškai įdiegta ir sukonfigūruota prisijungti prie jūsų IoT Hub kaip `fruit-quality-detector-edge` įrenginys.

1. Jums reikės arba IP adreso, arba DNS pavadinimo, kad galėtumėte iškviesti vaizdų klasifikatorių iš šios mašinos. Paleiskite šią komandą, kad gautumėte šią informaciją:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Nukopijuokite `PublicIps` arba `Fqdns` lauką.

1. Virtualios mašinos kainuoja pinigus. Šiuo metu DS1 virtuali mašina kainuoja apie $0.06 per valandą. Kad sumažintumėte išlaidas, turėtumėte išjungti virtualią mašiną, kai jos nenaudojate, ir ištrinti ją, kai baigsite projektą.

    Galite sukonfigūruoti savo virtualią mašiną, kad ji automatiškai išsijungtų tam tikru laiku kiekvieną dieną. Tai reiškia, kad jei pamiršite ją išjungti, jums nebus skaičiuojama daugiau nei iki automatinio išjungimo laiko. Naudokite šią komandą, kad nustatytumėte automatinį išjungimą:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Pakeiskite `<vm_name>` į savo virtualios mašinos pavadinimą.

    Pakeiskite `<shutdown_time_utc>` į UTC laiką, kada norite, kad virtuali mašina išsijungtų, naudodami 4 skaitmenis kaip HHMM. Pavyzdžiui, jei norite išjungti vidurnaktį UTC, nustatykite `0000`. Jei norite išjungti 19:30 vakare JAV vakarų pakrantėje, naudokite 0230 (19:30 vakare JAV vakarų pakrantėje yra 2:30 ryto UTC).

1. Jūsų vaizdų klasifikatorius veiks šioje Edge įrenginyje, klausydamas 80 prievado (standartinio HTTP prievado). Pagal numatymą, virtualios mašinos turi užblokuotus įeinančius prievadus, todėl jums reikės įjungti 80 prievadą. Prievadai įjungiami tinklo saugumo grupėse, todėl pirmiausia turite sužinoti savo virtualios mašinos tinklo saugumo grupės pavadinimą, kurį galite rasti naudodami šią komandą:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Nukopijuokite `Name` lauko reikšmę.

1. Paleiskite šią komandą, kad pridėtumėte taisyklę, atveriančią 80 prievadą tinklo saugumo grupei:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Pakeiskite `<nsg name>` į tinklo saugumo grupės pavadinimą iš ankstesnio žingsnio.

### Užduotis - valdykite savo virtualią mašiną, kad sumažintumėte išlaidas

1. Kai nenaudojate savo virtualios mašinos, turėtumėte ją išjungti. Norėdami išjungti virtualią mašiną, naudokite šią komandą:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Pakeiskite `<vm_name>` į savo virtualios mašinos pavadinimą.

    > 💁 Yra komanda `az vm stop`, kuri sustabdys virtualią mašiną, tačiau ji vis tiek išlaiko kompiuterį priskirtą jums, todėl mokėsite taip, lyg ji vis dar veiktų.

1. Norėdami paleisti virtualią mašiną iš naujo, naudokite šią komandą:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Pakeiskite `<vm_name>` į savo virtualios mašinos pavadinimą.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudotis profesionalių vertėjų paslaugomis. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.