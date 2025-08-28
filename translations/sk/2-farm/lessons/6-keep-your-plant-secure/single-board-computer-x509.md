<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T11:17:41+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "sk"
}
-->
# Použitie certifikátu X.509 vo vašom zariadení - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie pripojíte svoje virtuálne IoT zariadenie alebo Raspberry Pi k IoT Hubu pomocou certifikátu X.509.

## Pripojenie zariadenia k IoT Hubu

Ďalším krokom je pripojenie vášho zariadenia k IoT Hubu pomocou certifikátov X.509.

### Úloha - pripojenie k IoT Hubu

1. Skopírujte súbory s kľúčom a certifikátom do priečinka obsahujúceho kód vášho IoT zariadenia. Ak používate Raspberry Pi cez VS Code Remote SSH a vytvorili ste kľúče na svojom PC alebo Macu, môžete súbory presunúť do prieskumníka vo VS Code a skopírovať ich.

1. Otvorte súbor `app.py`.

1. Na pripojenie pomocou certifikátu X.509 budete potrebovať názov hostiteľa IoT Hubu a certifikát X.509. Začnite vytvorením premennej obsahujúcej názov hostiteľa pridaním nasledujúceho kódu pred vytvorením klienta zariadenia:

    ```python
    host_name = "<host_name>"
    ```

    Nahraďte `<host_name>` názvom hostiteľa vášho IoT Hubu. Tento názov nájdete v sekcii `HostName` v `connection_string`. Bude to názov vášho IoT Hubu, končiaci na `.azure-devices.net`.

1. Pod týmto kódom deklarujte premennú s ID zariadenia:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Budete potrebovať inštanciu triedy `X509`, ktorá obsahuje súbory certifikátu X.509. Pridajte `X509` do zoznamu tried importovaných z modulu `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Vytvorte inštanciu triedy `X509` pomocou vašich certifikátových a kľúčových súborov pridaním tohto kódu pod deklaráciu `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Týmto sa vytvorí trieda `X509` pomocou súborov `soil-moisture-sensor-x509-cert.pem` a `soil-moisture-sensor-x509-key.pem`, ktoré ste vytvorili skôr.

1. Nahraďte riadok kódu, ktorý vytvára `device_client` z reťazca pripojenia, nasledujúcim:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Týmto sa pripojíte pomocou certifikátu X.509 namiesto reťazca pripojenia.

1. Odstráňte riadok s premennou `connection_string`.

1. Spustite svoj kód. Sledujte správy odosielané do IoT Hubu a posielajte požiadavky na priame metódy ako predtým. Uvidíte, že zariadenie sa pripája, odosiela údaje o vlhkosti pôdy a prijíma požiadavky na priame metódy.

> 💁 Tento kód nájdete v priečinku [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) alebo [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Program vášho senzora vlhkosti pôdy je pripojený k IoT Hubu pomocou certifikátu X.509!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.