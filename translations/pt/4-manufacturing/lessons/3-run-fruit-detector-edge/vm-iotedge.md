<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-25T21:08:10+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "pt"
}
-->
# Criar uma máquina virtual com IoT Edge

No Azure, pode criar uma máquina virtual - um computador na nuvem que pode configurar da forma que desejar e executar o seu próprio software.

> 💁 Pode ler mais sobre máquinas virtuais na [página de Máquinas Virtuais na Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Tarefa - Configurar uma máquina virtual com IoT Edge

1. Execute o seguinte comando para criar uma máquina virtual que já tenha o Azure IoT Edge pré-instalado:

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

    Substitua `<vm_name>` por um nome para esta máquina virtual. Este nome precisa ser globalmente único, por isso use algo como `fruit-quality-detector-vm-` seguido do seu nome ou outro valor no final.

    Substitua `<username>` e `<password>` por um nome de utilizador e uma palavra-passe para aceder à máquina virtual. Estes devem ser relativamente seguros, por isso não pode usar algo como admin/password.

    Substitua `<connection_string>` pela cadeia de conexão do seu dispositivo IoT Edge `fruit-quality-detector-edge`.

    Isto criará uma máquina virtual configurada como uma máquina `DS1 v2`. Estas categorias indicam o poder da máquina e, consequentemente, o custo. Esta máquina virtual tem 1 CPU e 3.5GB de RAM.

    > 💰 Pode consultar os preços atuais destas máquinas virtuais no [guia de preços de Máquinas Virtuais do Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Assim que a máquina virtual for criada, o runtime do IoT Edge será instalado automaticamente e configurado para se conectar ao seu IoT Hub como o dispositivo `fruit-quality-detector-edge`.

1. Vai precisar do endereço IP ou do nome DNS da máquina virtual para chamar o classificador de imagens a partir dela. Execute o seguinte comando para obter esta informação:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copie o valor do campo `PublicIps` ou do campo `Fqdns`.

1. Máquinas virtuais têm custos associados. No momento da redação, uma máquina DS1 custa cerca de $0.06 por hora. Para reduzir os custos, deve desligar a máquina virtual quando não estiver a utilizá-la e eliminá-la quando terminar este projeto.

    Pode configurar a sua máquina virtual para desligar automaticamente a uma determinada hora todos os dias. Isto significa que, caso se esqueça de desligá-la, não será cobrado por mais tempo do que até ao desligamento automático. Use o seguinte comando para configurar isto:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

    Substitua `<shutdown_time_utc>` pela hora UTC em que deseja que a máquina virtual seja desligada, utilizando 4 dígitos no formato HHMM. Por exemplo, se quiser desligar à meia-noite UTC, deve definir como `0000`. Para as 19:30 na costa oeste dos EUA, deve usar 0230 (19:30 na costa oeste dos EUA corresponde às 2:30 UTC).

1. O seu classificador de imagens estará a funcionar neste dispositivo edge, ouvindo na porta 80 (a porta padrão para HTTP). Por padrão, as máquinas virtuais têm as portas de entrada bloqueadas, por isso será necessário ativar a porta 80. As portas são ativadas em grupos de segurança de rede, então primeiro precisa saber o nome do grupo de segurança de rede da sua máquina virtual, que pode encontrar com o seguinte comando:

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

    Substitua `<nsg name>` pelo nome do grupo de segurança de rede obtido no passo anterior.

### Tarefa - gerir a sua máquina virtual para reduzir custos

1. Quando não estiver a utilizar a sua máquina virtual, deve desligá-la. Para desligar a máquina virtual, use o seguinte comando:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

    > 💁 Existe um comando `az vm stop` que irá parar a máquina virtual, mas mantém o computador alocado para si, o que significa que continuará a pagar como se estivesse a funcionar.

1. Para reiniciar a máquina virtual, use o seguinte comando:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Substitua `<vm_name>` pelo nome da sua máquina virtual.

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.