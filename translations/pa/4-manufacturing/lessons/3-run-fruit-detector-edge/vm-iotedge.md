<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T10:42:51+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "pa"
}
-->
# IoT Edge ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਬਣਾਓ

Azure ਵਿੱਚ, ਤੁਸੀਂ ਇੱਕ ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਬਣਾਉਣ ਲਈ ਸਮਰੱਥ ਹੋ - ਕਲਾਉਡ ਵਿੱਚ ਇੱਕ ਕੰਪਿਊਟਰ ਜਿਸਨੂੰ ਤੁਸੀਂ ਆਪਣੇ ਤਰੀਕੇ ਨਾਲ ਕਨਫਿਗਰ ਕਰ ਸਕਦੇ ਹੋ ਅਤੇ ਇਸ 'ਤੇ ਆਪਣਾ ਸੌਫਟਵੇਅਰ ਚਲਾ ਸਕਦੇ ਹੋ।

> 💁 ਤੁਸੀਂ ਵਰਚੁਅਲ ਮਸ਼ੀਨਾਂ ਬਾਰੇ ਹੋਰ ਜਾਣਕਾਰੀ [ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਪੰਨਾ ਵਿੱਖੇ ਵਿਕੀਪੀਡੀਆ](https://wikipedia.org/wiki/Virtual_machine) 'ਤੇ ਪੜ੍ਹ ਸਕਦੇ ਹੋ।

## ਕੰਮ - IoT Edge ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਸੈਟਅੱਪ ਕਰੋ

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨੂੰ ਚਲਾਓ ਤਾਂ ਜੋ ਇੱਕ VM ਬਣਾਇਆ ਜਾਵੇ ਜਿਸ ਵਿੱਚ Azure IoT Edge ਪਹਿਲਾਂ ਹੀ ਪ੍ਰੀ-ਇੰਸਟਾਲ ਹੈ:

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

    `<vm_name>` ਨੂੰ ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਲਈ ਇੱਕ ਨਾਮ ਨਾਲ ਬਦਲੋ। ਇਹ ਗਲੋਬਲ ਤੌਰ 'ਤੇ ਵਿਲੱਖਣ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ, ਇਸ ਲਈ `fruit-quality-detector-vm-` ਦੇ ਨਾਲ ਆਪਣਾ ਨਾਮ ਜਾਂ ਹੋਰ ਕੋਈ ਮੁੱਲ ਜੋੜੋ।

    `<username>` ਅਤੇ `<password>` ਨੂੰ VM ਵਿੱਚ ਲੌਗਇਨ ਕਰਨ ਲਈ ਵਰਤਣ ਵਾਲੇ ਯੂਜ਼ਰਨੇਮ ਅਤੇ ਪਾਸਵਰਡ ਨਾਲ ਬਦਲੋ। ਇਹ ਕਾਫ਼ੀ ਸੁਰੱਖਿਅਤ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ, ਇਸ ਲਈ ਤੁਸੀਂ admin/password ਵਰਤ ਨਹੀਂ ਸਕਦੇ।

    `<connection_string>` ਨੂੰ ਆਪਣੇ `fruit-quality-detector-edge` IoT Edge ਡਿਵਾਈਸ ਦੇ ਕਨੈਕਸ਼ਨ ਸਟ੍ਰਿੰਗ ਨਾਲ ਬਦਲੋ।

    ਇਹ VM ਨੂੰ `DS1 v2` ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਵਜੋਂ ਕਨਫਿਗਰ ਕਰੇਗਾ। ਇਹ ਸ਼੍ਰੇਣੀਆਂ ਮਸ਼ੀਨ ਦੀ ਸ਼ਕਤੀ ਅਤੇ ਇਸ ਲਈ ਇਸਦੀ ਲਾਗਤ ਨੂੰ ਦਰਸਾਉਂਦੀਆਂ ਹਨ। ਇਸ VM ਵਿੱਚ 1 CPU ਅਤੇ 3.5GB RAM ਹੈ।

    > 💰 ਤੁਸੀਂ ਇਸ ਸਮੇਂ ਦੀਆਂ VM ਦੀਆਂ ਕੀਮਤਾਂ [Azure ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਕੀਮਤਾਂ ਗਾਈਡ](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) 'ਤੇ ਵੇਖ ਸਕਦੇ ਹੋ।

    ਜਦੋਂ VM ਬਣਾਇਆ ਜਾਂਦਾ ਹੈ, IoT Edge ਰਨਟਾਈਮ ਆਪਣੇ ਆਪ ਇੰਸਟਾਲ ਹੋ ਜਾਵੇਗਾ ਅਤੇ ਤੁਹਾਡੇ IoT Hub ਨਾਲ `fruit-quality-detector-edge` ਡਿਵਾਈਸ ਵਜੋਂ ਕਨੈਕਟ ਕਰਨ ਲਈ ਕਨਫਿਗਰ ਕੀਤਾ ਜਾਵੇਗਾ।

1. ਤੁਹਾਨੂੰ VM ਤੋਂ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਨੂੰ ਕਾਲ ਕਰਨ ਲਈ ਜਾਂ ਤਾਂ IP ਐਡਰੈਸ ਜਾਂ DNS ਨਾਮ ਦੀ ਲੋੜ ਹੋਵੇਗੀ। ਇਸ ਨੂੰ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਚਲਾਓ:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` ਫੀਲਡ ਜਾਂ `Fqdns` ਫੀਲਡ ਦੀ ਕਾਪੀ ਲਵੋ।

1. VM ਪੈਸਾ ਲਗਦਾ ਹੈ। ਇਸ ਲੇਖਨ ਦੇ ਸਮੇਂ, ਇੱਕ DS1 VM ਦੀ ਲਾਗਤ ਲਗਭਗ $0.06 ਪ੍ਰਤੀ ਘੰਟਾ ਹੈ। ਖਰਚੇ ਘਟਾਉਣ ਲਈ, ਤੁਹਾਨੂੰ VM ਨੂੰ ਬੰਦ ਕਰ ਦੇਣਾ ਚਾਹੀਦਾ ਹੈ ਜਦੋਂ ਤੁਸੀਂ ਇਸਨੂੰ ਵਰਤ ਨਹੀਂ ਰਹੇ ਹੋ, ਅਤੇ ਇਸ ਪ੍ਰੋਜੈਕਟ ਦੇ ਸਮਾਪਤ ਹੋਣ 'ਤੇ ਇਸਨੂੰ ਮਿਟਾ ਦੇਣਾ ਚਾਹੀਦਾ ਹੈ।

    ਤੁਸੀਂ ਆਪਣੇ VM ਨੂੰ ਹਰ ਦਿਨ ਇੱਕ ਨਿਰਧਾਰਿਤ ਸਮੇਂ 'ਤੇ ਆਪਣੇ ਆਪ ਬੰਦ ਕਰਨ ਲਈ ਕਨਫਿਗਰ ਕਰ ਸਕਦੇ ਹੋ। ਇਸਦਾ ਮਤਲਬ ਹੈ ਕਿ ਜੇ ਤੁਸੀਂ ਇਸਨੂੰ ਬੰਦ ਕਰਨਾ ਭੁੱਲ ਜਾਂਦੇ ਹੋ, ਤਾਂ ਤੁਹਾਨੂੰ ਸਿਰਫ਼ ਆਟੋਮੈਟਿਕ ਸ਼ਟਡਾਊਨ ਤੱਕ ਦੇ ਸਮੇਂ ਲਈ ਬਿਲ ਕੀਤਾ ਜਾਵੇਗਾ। ਇਸ ਨੂੰ ਸੈਟ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਵਰਤੋ:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>` ਨੂੰ ਆਪਣੇ ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਦੇ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    `<shutdown_time_utc>` ਨੂੰ UTC ਸਮੇਂ ਨਾਲ ਬਦਲੋ ਜਿਸ 'ਤੇ ਤੁਸੀਂ VM ਨੂੰ 4 ਅੰਕਾਂ ਦੇ ਰੂਪ ਵਿੱਚ HHMM ਵਰਤ ਕੇ ਬੰਦ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ। ਉਦਾਹਰਣ ਲਈ, ਜੇ ਤੁਸੀਂ ਮਿਡਨਾਈਟ UTC 'ਤੇ ਬੰਦ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ ਇਸਨੂੰ `0000` ਸੈਟ ਕਰੋਗੇ। USA ਦੇ ਵੈਸਟ ਕੋਸਟ 'ਤੇ 7:30PM ਲਈ, ਤੁਸੀਂ 0230 ਵਰਤੋਗੇ (USA ਦੇ ਵੈਸਟ ਕੋਸਟ 'ਤੇ 7:30PM UTC 'ਤੇ 2:30AM ਹੈ)।

1. ਤੁਹਾਡਾ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਇਸ ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਚੱਲ ਰਿਹਾ ਹੋਵੇਗਾ, ਜੋ ਪੋਰਟ 80 (ਮਿਆਰੀ HTTP ਪੋਰਟ) 'ਤੇ ਸੁਣ ਰਿਹਾ ਹੈ। ਡਿਫਾਲਟ ਤੌਰ 'ਤੇ, ਵਰਚੁਅਲ ਮਸ਼ੀਨਾਂ ਵਿੱਚ ਇਨਬਾਊਂਡ ਪੋਰਟਾਂ ਬਲੌਕ ਕੀਤੀਆਂ ਜਾਂਦੀਆਂ ਹਨ, ਇਸ ਲਈ ਤੁਹਾਨੂੰ ਪੋਰਟ 80 ਨੂੰ ਐਨਬਲ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ। ਪੋਰਟਾਂ ਨੂੰ ਨੈਟਵਰਕ ਸੁਰੱਖਿਆ ਸਮੂਹਾਂ 'ਤੇ ਐਨਬਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਇਸ ਲਈ ਪਹਿਲਾਂ ਤੁਹਾਨੂੰ ਆਪਣੇ VM ਲਈ ਨੈਟਵਰਕ ਸੁਰੱਖਿਆ ਸਮੂਹ ਦਾ ਨਾਮ ਜਾਣਨ ਦੀ ਲੋੜ ਹੈ, ਜਿਸਨੂੰ ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` ਫੀਲਡ ਦਾ ਮੁੱਲ ਕਾਪੀ ਕਰੋ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨੂੰ ਚਲਾਓ ਤਾਂ ਜੋ ਨੈਟਵਰਕ ਸੁਰੱਖਿਆ ਸਮੂਹ ਵਿੱਚ ਪੋਰਟ 80 ਖੋਲ੍ਹਣ ਲਈ ਇੱਕ ਨਿਯਮ ਜੋੜਿਆ ਜਾਵੇ:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>` ਨੂੰ ਪਿਛਲੇ ਕਦਮ ਤੋਂ ਨੈਟਵਰਕ ਸੁਰੱਖਿਆ ਸਮੂਹ ਦੇ ਨਾਮ ਨਾਲ ਬਦਲੋ।

### ਕੰਮ - ਆਪਣੇ VM ਨੂੰ ਪ੍ਰਬੰਧਿਤ ਕਰੋ ਤਾਂ ਜੋ ਖਰਚੇ ਘਟ ਸਕਣ

1. ਜਦੋਂ ਤੁਸੀਂ ਆਪਣੇ VM ਨੂੰ ਵਰਤ ਨਹੀਂ ਰਹੇ ਹੋ, ਤਾਂ ਤੁਹਾਨੂੰ ਇਸਨੂੰ ਬੰਦ ਕਰ ਦੇਣਾ ਚਾਹੀਦਾ ਹੈ। VM ਨੂੰ ਬੰਦ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਵਰਤੋ:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>` ਨੂੰ ਆਪਣੇ ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਦੇ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    > 💁 ਇੱਕ `az vm stop` ਕਮਾਂਡ ਹੈ ਜੋ VM ਨੂੰ ਰੋਕ ਦੇਵੇਗਾ, ਪਰ ਇਹ ਕੰਪਿਊਟਰ ਨੂੰ ਤੁਹਾਡੇ ਲਈ ਅਲੋਕੇਟ ਰੱਖਦਾ ਹੈ, ਇਸ ਲਈ ਤੁਸੀਂ ਅਜੇ ਵੀ ਇਸਨੂੰ ਚਲਾਉਣ ਦੇ ਤੌਰ 'ਤੇ ਭੁਗਤਾਨ ਕਰਦੇ ਹੋ।

1. VM ਨੂੰ ਮੁੜ ਚਾਲੂ ਕਰਨ ਲਈ, ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਵਰਤੋ:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>` ਨੂੰ ਆਪਣੇ ਵਰਚੁਅਲ ਮਸ਼ੀਨ ਦੇ ਨਾਮ ਨਾਲ ਬਦਲੋ।

---

**ਅਸਵੀਕਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਅਤ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੌਜੂਦ ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।