<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-24T21:46:12+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "ja"
}
-->
# IoT Edgeを実行する仮想マシンを作成する

Azureでは、仮想マシンを作成できます。これはクラウド上のコンピュータで、自由に設定を変更し、自分のソフトウェアを実行することができます。

> 💁 仮想マシンについて詳しくは、[Wikipediaの仮想マシンページ](https://wikipedia.org/wiki/Virtual_machine)をご覧ください。

## タスク - IoT Edge仮想マシンをセットアップする

1. 以下のコマンドを実行して、Azure IoT Edgeが事前にインストールされた仮想マシンを作成します:

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

    `<vm_name>`を仮想マシンの名前に置き換えてください。この名前はグローバルで一意である必要があるため、例えば`fruit-quality-detector-vm-`の後に自分の名前や他の値を付け加えると良いでしょう。

    `<username>`と`<password>`を仮想マシンにログインするためのユーザー名とパスワードに置き換えてください。これらは比較的安全なものである必要があり、admin/passwordのような簡単なものは使用できません。

    `<connection_string>`を`fruit-quality-detector-edge` IoT Edgeデバイスの接続文字列に置き換えてください。

    このコマンドは、`DS1 v2`カテゴリの仮想マシンとしてVMを作成します。このカテゴリはマシンの性能を示しており、それに応じてコストが変わります。このVMには1つのCPUと3.5GBのRAMが搭載されています。

    > 💰 現在のVMの価格については、[Azure Virtual Machine価格ガイド](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)をご覧ください。

    VMが作成されると、IoT Edgeランタイムが自動的にインストールされ、`fruit-quality-detector-edge`デバイスとしてIoT Hubに接続するように設定されます。

1. 画像分類器をVMから呼び出すには、VMのIPアドレスまたはDNS名が必要です。以下のコマンドを実行して取得してください:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps`フィールドまたは`Fqdns`フィールドの値をコピーしてください。

1. 仮想マシンは費用がかかります。執筆時点では、DS1 VMは約$0.06/時間の費用がかかります。コストを抑えるために、使用していないときはVMをシャットダウンし、このプロジェクトが終了したら削除してください。

    VMを毎日特定の時間に自動的にシャットダウンするように設定できます。これにより、シャットダウンを忘れても、自動シャットダウンまでの時間分しか請求されません。以下のコマンドを使用して設定してください:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>`を仮想マシンの名前に置き換えてください。

    `<shutdown_time_utc>`をUTC時間でシャットダウンしたい時間に置き換えてください。4桁のHHMM形式で指定します。例えば、UTCの午前0時にシャットダウンしたい場合は`0000`を設定します。アメリカ西海岸の午後7時30分の場合は`0230`（アメリカ西海岸の午後7時30分はUTCの午前2時30分）を使用します。

1. このエッジデバイス上で画像分類器がポート80（標準HTTPポート）で動作します。デフォルトでは、仮想マシンのインバウンドポートはブロックされています。そのため、ポート80を有効にする必要があります。ポートはネットワークセキュリティグループで有効化されるため、まず以下のコマンドを使用してVMのネットワークセキュリティグループ名を確認してください:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name`フィールドの値をコピーしてください。

1. 以下のコマンドを実行して、ネットワークセキュリティグループにポート80を開くルールを追加してください:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>`を前のステップで取得したネットワークセキュリティグループ名に置き換えてください。

### タスク - コストを削減するためのVM管理

1. VMを使用していないときはシャットダウンするべきです。以下のコマンドを使用してVMをシャットダウンしてください:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>`を仮想マシンの名前に置き換えてください。

    > 💁 `az vm stop`コマンドもありますが、このコマンドはVMを停止するだけで、コンピュータが割り当てられたままになるため、実行中と同じ料金が発生します。

1. VMを再起動するには、以下のコマンドを使用してください:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>`を仮想マシンの名前に置き換えてください。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された文書を正式な情報源としてお考えください。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解について、当社は責任を負いません。