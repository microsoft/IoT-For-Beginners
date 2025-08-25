<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T00:43:46+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "ja"
}
-->
# Twilioを使用して通知を送信する

## 手順

これまでのコードでは、ジオフェンスまでの距離をログに記録するだけでした。この課題では、GPS座標がジオフェンス内にある場合に、テキストメッセージまたはメールで通知を追加する必要があります。

Azure Functionsには、Twilioのようなサードパーティサービスを含む多くのバインディングオプションがあります。

* [Twilio.com](https://www.twilio.com)で無料アカウントに登録してください。
* [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python)で、Azure FunctionsをTwilio SMSにバインドする方法についてのドキュメントを読んでください。
* [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python)で、Azure FunctionsをTwilio SendGridにバインドしてメールを送信する方法についてのドキュメントを読んでください。
* GPS座標がジオフェンス内または外にある場合に通知を受け取るように、Functionsアプリにバインディングを追加してください。ただし、両方ではありません。

## 評価基準

| 基準 | 優秀 | 適切 | 改善が必要 |
| -------- | --------- | -------- | ----------------- |
| Functionsバインディングを構成し、メールまたはSMSを受信する | Functionsバインディングを構成し、ジオフェンス内または外にいる場合にメールまたはSMSを受信できたが、両方ではない | バインディングを構成できたが、メールまたはSMSを送信できなかった、または座標が内外両方の場合にのみ送信できた | バインディングを構成できず、メールまたはSMSを送信できなかった |

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があることをご承知おきください。元の言語で記載された原文が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。