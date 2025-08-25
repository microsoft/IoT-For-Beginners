<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-24T21:00:52+00:00",
  "source_file": "clean-up.md",
  "language_code": "ja"
}
-->
# プロジェクトのクリーンアップ

各プロジェクトを完了した後は、クラウドリソースを削除することをお勧めします。

各プロジェクトのレッスンで、以下のようなものを作成した可能性があります:

* リソースグループ
* IoT Hub
* IoTデバイス登録
* ストレージアカウント
* Functions App
* Azure Mapsアカウント
* カスタムビジョンプロジェクト
* Azure Container Registry
* 認知サービスリソース

これらのリソースのほとんどは費用がかかりません。完全に無料であるか、無料の利用枠を使用している場合がほとんどです。有料の利用枠が必要なサービスについても、無料枠に含まれるレベルで使用しているか、数セント程度の費用しかかからないでしょう。

費用が比較的低い場合でも、作業が終わったらこれらのリソースを削除する価値があります。例えば、無料枠を使用できるIoT Hubは1つだけなので、別のIoT Hubを作成したい場合は有料枠を使用する必要があります。

すべてのサービスはリソースグループ内に作成されているため、管理が簡単です。リソースグループを削除すると、そのリソースグループ内のすべてのサービスが一緒に削除されます。

リソースグループを削除するには、ターミナルまたはコマンドプロンプトで以下のコマンドを実行してください:

```sh
az group delete --name <resource-group-name>
```

`<resource-group-name>` を削除したいリソースグループの名前に置き換えてください。

確認メッセージが表示されます:

```output
Are you sure you want to perform this operation? (y/n): 
```

`y` を入力して確認し、リソースグループを削除します。

すべてのサービスを削除するには少し時間がかかります。

> 💁 リソースグループの削除についてさらに詳しく知りたい場合は、[Microsoft DocsのAzure Resource Managerリソースグループとリソース削除に関するドキュメント](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)をご覧ください。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は責任を負いません。