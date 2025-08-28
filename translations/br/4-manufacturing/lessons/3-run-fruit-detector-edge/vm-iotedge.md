<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T02:45:17+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "br"
}
-->
# Criar uma máquina virtual executando IoT Edge

No Azure, você pode criar uma máquina virtual - um computador na nuvem que você pode configurar da maneira que desejar e executar seu próprio software nele.

> 💁 Você pode ler mais sobre máquinas virtuais na [página de Máquina Virtual na Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Tarefa - Configurar uma máquina virtual IoT Edge

1. Execute o seguinte comando para criar uma VM que já tenha o Azure IoT Edge pré-instalado:

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

    Substitua `<vm_name>` por um nome para esta máquina virtual. Este nome precisa ser globalmente único, então use algo como `fruit-quality-detector-vm-` com seu nome ou outro valor no final.

    Substitua `<username>` e `<password>` por um nome de usuário e senha para usar ao fazer login na VM. Estes precisam ser relativamente seguros, então você não pode usar admin/password.

    Substitua `<connection_string>` pela string de conexão do seu dispositivo IoT Edge `fruit-quality-detector-edge`.

    Isso criará uma VM configurada como uma máquina virtual `DS1 v2`. Essas categorias indicam o quão poderosa é a máquina e, consequentemente, quanto ela custa. Esta VM possui 1 CPU e 3,5GB de RAM.

    > 💰 Você pode ver os preços atuais dessas VMs no [guia de preços de Máquinas Virtuais do Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Assim que a VM for criada, o runtime do IoT Edge será instalado automaticamente e configurado para se conectar ao seu IoT Hub como seu dispositivo `fruit-quality-detector-edge`.

1. Você precisará do endereço IP ou do nome DNS da VM para chamar o classificador de imagens a partir dela. Execute o seguinte comando para obter isso:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copie o valor do campo `PublicIps` ou do campo `Fqdns`.

1. VMs têm custo. No momento da redação, uma VM DS1 custa cerca de $0,06 por hora. Para reduzir os custos, você deve desligar a VM quando não estiver usando e excluí-la quando terminar este projeto.

    Você pode configurar sua VM para desligar automaticamente em um horário específico todos os dias. Isso significa que, se você esquecer de desligá-la, não será cobrado por mais tempo do que até o desligamento automático. Use o seguinte comando para configurar isso:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

    Substitua `<shutdown_time_utc>` pelo horário UTC em que você deseja que a VM seja desligada, usando 4 dígitos no formato HHMM. Por exemplo, se você quiser desligar à meia-noite UTC, defina como `0000`. Para 19:30 na costa oeste dos EUA, use 0230 (19:30 na costa oeste dos EUA é 2:30 UTC).

1. Seu classificador de imagens estará sendo executado neste dispositivo edge, ouvindo na porta 80 (a porta padrão HTTP). Por padrão, máquinas virtuais têm portas de entrada bloqueadas, então você precisará habilitar a porta 80. As portas são habilitadas em grupos de segurança de rede, então primeiro você precisa saber o nome do grupo de segurança de rede da sua VM, que pode ser encontrado com o seguinte comando:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copie o valor do campo `Name`.

1. Execute o seguinte comando para adicionar uma regra que abra a porta 80 no grupo de segurança de rede:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Substitua `<nsg name>` pelo nome do grupo de segurança de rede obtido na etapa anterior.

### Tarefa - gerenciar sua VM para reduzir custos

1. Quando você não estiver usando sua VM, deve desligá-la. Para desligar a VM, use o seguinte comando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

    > 💁 Existe um comando `az vm stop` que irá parar a VM, mas ele mantém o computador alocado para você, então você ainda paga como se ela estivesse funcionando.

1. Para reiniciar a VM, use o seguinte comando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.