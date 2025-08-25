<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T01:07:36+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ja"
}
-->
# 関数バインディングを調査する

## 手順

関数バインディングを使用すると、`main`関数から返されたデータをBlobストレージに保存することができます。Azure Storageアカウント、コレクション、その他の詳細は`function.json`ファイルで設定されます。

Azureやその他のMicrosoftテクノロジーを使用する際、最も信頼できる情報源は[Microsoftのドキュメント](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)です。この課題では、Azure Functionsのバインディングに関するドキュメントを読み、出力バインディングの設定方法を理解する必要があります。

以下のページを参考にして始めてください：

* [Azure Functionsのトリガーとバインディングの概念](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure FunctionsのAzure Blobストレージバインディング概要](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure FunctionsのAzure Blobストレージ出力バインディング](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 評価基準

| 基準 | 優秀 | 適切 | 改善が必要 |
| -------- | --------- | -------- | ----------------- |
| Blobストレージの出力バインディングを設定する | 出力バインディングを設定し、Blobを返してBlobストレージに正常に保存できた | 出力バインディングを設定するか、Blobを返すことはできたが、Blobストレージに正常に保存することができなかった | 出力バインディングを設定することができなかった |

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の利用に起因する誤解や誤訳について、当社は一切の責任を負いません。