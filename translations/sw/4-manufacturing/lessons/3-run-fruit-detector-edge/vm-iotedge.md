<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:50:20+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "sw"
}
-->
# Unda mashine halisi inayoendesha IoT Edge

Katika Azure, unaweza kuunda mashine halisi - kompyuta kwenye wingu ambayo unaweza kuisanidi kwa njia yoyote unayotaka na kuendesha programu zako mwenyewe juu yake.

> 💁 Unaweza kusoma zaidi kuhusu mashine halisi kwenye [ukurasa wa Mashine Halisi kwenye Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Kazi - Sanidi mashine halisi ya IoT Edge

1. Endesha amri ifuatayo ili kuunda VM ambayo tayari ina Azure IoT Edge iliyosakinishwa:

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

    Badilisha `<vm_name>` na jina la mashine halisi hii. Jina hili linahitaji kuwa la kipekee kimataifa, kwa hivyo tumia kitu kama `fruit-quality-detector-vm-` na jina lako au thamani nyingine mwishoni.

    Badilisha `<username>` na `<password>` na jina la mtumiaji na nenosiri la kuingia kwenye VM. Hizi zinahitaji kuwa salama kiasi, kwa hivyo huwezi kutumia admin/password.

    Badilisha `<connection_string>` na mfuatano wa muunganisho wa kifaa chako cha IoT Edge `fruit-quality-detector-edge`.

    Hii itaunda VM iliyosanidiwa kama mashine halisi ya `DS1 v2`. Kategoria hizi zinaonyesha jinsi mashine ilivyo na nguvu, na kwa hivyo gharama yake. VM hii ina CPU 1 na RAM ya 3.5GB.

    > 💰 Unaweza kuona bei ya sasa ya VM hizi kwenye [Mwongozo wa Bei wa Mashine Halisi ya Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Mara tu VM itakapoundwa, mfumo wa IoT Edge utawekwa kiotomatiki, na kusanidiwa kuunganishwa na IoT Hub yako kama kifaa chako cha `fruit-quality-detector-edge`.

1. Utahitaji ama anwani ya IP au jina la DNS la VM ili kuita kigezo cha picha kutoka kwake. Endesha amri ifuatayo kupata hii:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Nakili thamani ya sehemu ya `PublicIps`, au sehemu ya `Fqdns`.

1. VM zinagharimu pesa. Kwa wakati wa kuandika, VM ya DS1 inagharimu takriban $0.06 kwa saa. Ili kupunguza gharama, unapaswa kuzima VM wakati hauitumii, na kuifuta unapomaliza mradi huu.

    Unaweza kusanidi VM yako kuzima kiotomatiki kwa wakati fulani kila siku. Hii inamaanisha ikiwa utasahau kuizima, hautatozwa zaidi ya muda hadi kuzima kiotomatiki. Tumia amri ifuatayo kuweka hili:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Badilisha `<vm_name>` na jina la mashine halisi yako.

    Badilisha `<shutdown_time_utc>` na muda wa UTC ambao unataka VM izime kwa kutumia tarakimu 4 kama HHMM. Kwa mfano, ikiwa unataka izime saa sita usiku UTC, ungeweka hii kuwa `0000`. Kwa 7:30PM kwenye pwani ya magharibi ya Marekani, ungetumia 0230 (7:30PM kwenye pwani ya magharibi ya Marekani ni 2:30AM UTC).

1. Kigezo chako cha picha kitakuwa kinaendesha kwenye kifaa hiki cha edge, kikisikiliza kwenye bandari 80 (bandari ya kawaida ya HTTP). Kwa chaguo-msingi, mashine halisi zina bandari za kuingia zilizofungwa, kwa hivyo utahitaji kuwezesha bandari 80. Bandari zinawezeshwa kwenye vikundi vya usalama wa mtandao, kwa hivyo kwanza unahitaji kujua jina la kikundi cha usalama wa mtandao cha VM yako, ambacho unaweza kupata kwa amri ifuatayo:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Nakili thamani ya sehemu ya `Name`.

1. Endesha amri ifuatayo kuongeza sheria ya kufungua bandari 80 kwenye kikundi cha usalama wa mtandao:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Badilisha `<nsg name>` na jina la kikundi cha usalama wa mtandao kutoka hatua ya awali.

### Kazi - simamia VM yako ili kupunguza gharama

1. Wakati hauitumii VM yako, unapaswa kuizima. Ili kuzima VM, tumia amri ifuatayo:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Badilisha `<vm_name>` na jina la mashine halisi yako.

    > 💁 Kuna amri ya `az vm stop` ambayo itasimamisha VM, lakini inaweka kompyuta imepewa kwako, kwa hivyo bado unalipa kama ingekuwa inaendelea.

1. Ili kuwasha tena VM, tumia amri ifuatayo:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Badilisha `<vm_name>` na jina la mashine halisi yako.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.