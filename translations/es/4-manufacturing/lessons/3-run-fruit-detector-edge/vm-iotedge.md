<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-26T14:19:44+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "es"
}
-->
# Crear una máquina virtual con IoT Edge

En Azure, puedes crear una máquina virtual, es decir, un ordenador en la nube que puedes configurar como desees y ejecutar tu propio software en él.

> 💁 Puedes leer más sobre las máquinas virtuales en la [página de Wikipedia sobre Máquinas Virtuales](https://wikipedia.org/wiki/Virtual_machine).

## Tarea - Configurar una máquina virtual con IoT Edge

1. Ejecuta el siguiente comando para crear una máquina virtual que ya tenga Azure IoT Edge preinstalado:

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

    Sustituye `<vm_name>` por un nombre para esta máquina virtual. Este debe ser único a nivel global, así que utiliza algo como `fruit-quality-detector-vm-` seguido de tu nombre u otro valor.

    Sustituye `<username>` y `<password>` por un nombre de usuario y una contraseña para iniciar sesión en la máquina virtual. Estos deben ser relativamente seguros, por lo que no puedes usar algo como admin/password.

    Sustituye `<connection_string>` por la cadena de conexión de tu dispositivo IoT Edge `fruit-quality-detector-edge`.

    Esto creará una máquina virtual configurada como una máquina `DS1 v2`. Estas categorías indican qué tan potente es la máquina y, por ende, cuánto cuesta. Esta máquina virtual tiene 1 CPU y 3.5GB de RAM.

    > 💰 Puedes consultar los precios actuales de estas máquinas virtuales en la [guía de precios de Azure Virtual Machine](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Una vez que se haya creado la máquina virtual, el runtime de IoT Edge se instalará automáticamente y se configurará para conectarse a tu IoT Hub como tu dispositivo `fruit-quality-detector-edge`.

1. Necesitarás la dirección IP o el nombre DNS de la máquina virtual para llamar al clasificador de imágenes desde ella. Ejecuta el siguiente comando para obtener esta información:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copia el valor del campo `PublicIps` o del campo `Fqdns`.

1. Las máquinas virtuales tienen un costo. Al momento de escribir esto, una máquina DS1 cuesta aproximadamente $0.06 por hora. Para reducir costos, deberías apagar la máquina virtual cuando no la estés utilizando y eliminarla cuando termines con este proyecto.

    Puedes configurar tu máquina virtual para que se apague automáticamente a una hora específica cada día. Esto significa que, si olvidas apagarla, no se te cobrará más allá del tiempo hasta el apagado automático. Usa el siguiente comando para configurarlo:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Sustituye `<vm_name>` por el nombre de tu máquina virtual.

    Sustituye `<shutdown_time_utc>` por la hora UTC en la que deseas que la máquina virtual se apague, usando 4 dígitos en formato HHMM. Por ejemplo, si deseas que se apague a la medianoche UTC, deberías establecerlo en `0000`. Para las 7:30PM en la costa oeste de los EE. UU., usarías `0230` (7:30PM en la costa oeste de EE. UU. es 2:30AM UTC).

1. Tu clasificador de imágenes estará ejecutándose en este dispositivo Edge, escuchando en el puerto 80 (el puerto estándar de HTTP). Por defecto, las máquinas virtuales tienen los puertos de entrada bloqueados, por lo que necesitarás habilitar el puerto 80. Los puertos se habilitan en los grupos de seguridad de red, así que primero necesitas conocer el nombre del grupo de seguridad de red de tu máquina virtual, lo cual puedes encontrar con el siguiente comando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copia el valor del campo `Name`.

1. Ejecuta el siguiente comando para agregar una regla que abra el puerto 80 en el grupo de seguridad de red:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Sustituye `<nsg name>` por el nombre del grupo de seguridad de red del paso anterior.

### Tarea - Gestionar tu máquina virtual para reducir costos

1. Cuando no estés utilizando tu máquina virtual, deberías apagarla. Para apagar la máquina virtual, usa el siguiente comando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Sustituye `<vm_name>` por el nombre de tu máquina virtual.

    > 💁 Existe un comando `az vm stop` que detendrá la máquina virtual, pero mantendrá el ordenador asignado a ti, por lo que seguirás pagando como si estuviera en funcionamiento.

1. Para reiniciar la máquina virtual, usa el siguiente comando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Sustituye `<vm_name>` por el nombre de tu máquina virtual.

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.