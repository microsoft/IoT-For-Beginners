<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-24T21:45:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "ja"
}
-->
# エッジで他のサービスを実行する

## 手順

エッジで実行できるのは画像分類器だけではありません。コンテナにパッケージ化できるものであれば、何でもIoT Edgeデバイスにデプロイ可能です。これまでのレッスンで作成したトリガーのようなAzure Functionsとして動作するサーバーレスコードも、コンテナ内で実行できるため、IoT Edge上で動作させることができます。

以前のレッスンの1つを選び、Azure FunctionsアプリをIoT Edgeコンテナで実行してみてください。別のFunctionsアプリプロジェクトを使用してこれを行う方法を示したガイドは、[チュートリアル: Azure FunctionsをIoT Edgeモジュールとしてデプロイする (Microsoft Docs)](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11)で確認できます。

## 評価基準

| 基準 | 優秀 | 適切 | 改善が必要 |
| ---- | ---- | ---- | ---------- |
| Azure FunctionsアプリをIoT Edgeにデプロイする | Azure FunctionsアプリをIoT Edgeにデプロイし、IoTデバイスと連携してIoTデータからトリガーを実行できた | FunctionsアプリをIoT Edgeにデプロイできたが、トリガーを実行することができなかった | FunctionsアプリをIoT Edgeにデプロイできなかった |

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。