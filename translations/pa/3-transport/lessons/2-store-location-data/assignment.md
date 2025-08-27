<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T15:05:13+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "pa"
}
-->
# ਫੰਕਸ਼ਨ ਬਾਈਂਡਿੰਗ ਦੀ ਜਾਂਚ ਕਰੋ

## ਹਦਾਇਤਾਂ

ਫੰਕਸ਼ਨ ਬਾਈਂਡਿੰਗ ਤੁਹਾਡੇ ਕੋਡ ਨੂੰ `main` ਫੰਕਸ਼ਨ ਤੋਂ ਵਾਪਸ ਕਰਕੇ ਬਲਾਬ ਸਟੋਰੇਜ ਵਿੱਚ ਬਲਾਬ ਸੇਵ ਕਰਨ ਦੀ ਆਗਿਆ ਦਿੰਦੇ ਹਨ। Azure ਸਟੋਰੇਜ ਅਕਾਊਂਟ, ਕਲੈਕਸ਼ਨ ਅਤੇ ਹੋਰ ਵੇਰਵੇ `function.json` ਫਾਈਲ ਵਿੱਚ ਸੰਰਚਿਤ ਕੀਤੇ ਜਾਂਦੇ ਹਨ।

Azure ਜਾਂ ਹੋਰ Microsoft ਤਕਨਾਲੋਜੀ ਨਾਲ ਕੰਮ ਕਰਦੇ ਸਮੇਂ, ਜਾਣਕਾਰੀ ਦਾ ਸਭ ਤੋਂ ਵਧੀਆ ਸਰੋਤ [Microsoft ਡੌਕੂਮੈਂਟੇਸ਼ਨ docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ਹੈ। ਇਸ ਅਸਾਈਨਮੈਂਟ ਵਿੱਚ ਤੁਹਾਨੂੰ Azure Functions ਬਾਈਂਡਿੰਗ ਡੌਕੂਮੈਂਟੇਸ਼ਨ ਪੜ੍ਹਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ ਤਾਂ ਜੋ ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਸੈਟਅਪ ਕਰਨ ਦਾ ਤਰੀਕਾ ਸਮਝ ਸਕੋ।

ਸ਼ੁਰੂਆਤ ਕਰਨ ਲਈ ਕੁਝ ਪੰਨੇ ਇਹ ਹਨ:

* [Azure Functions ਟ੍ਰਿਗਰ ਅਤੇ ਬਾਈਂਡਿੰਗ ਦੇ ਸੰਕਲਪ](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob ਸਟੋਰੇਜ ਬਾਈਂਡਿੰਗ ਲਈ Azure Functions ਦਾ ਜਾਇਜ਼ਾ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob ਸਟੋਰੇਜ ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਲਈ Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## ਰੂਬ੍ਰਿਕ

| ਮਾਪਦੰਡ | ਸ਼ਾਨਦਾਰ | ਯੋਗ | ਸੁਧਾਰ ਦੀ ਲੋੜ |
| -------- | --------- | -------- | ----------------- |
| ਬਲਾਬ ਸਟੋਰੇਜ ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਸੰਰਚਿਤ ਕਰੋ | ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਸੰਰਚਿਤ ਕਰਨ, ਬਲਾਬ ਵਾਪਸ ਕਰਨ ਅਤੇ ਇਸਨੂੰ ਸਫਲਤਾਪੂਰਵਕ ਬਲਾਬ ਸਟੋਰੇਜ ਵਿੱਚ ਸੇਵ ਕਰਨ ਵਿੱਚ ਸਮਰਥ | ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਸੰਰਚਿਤ ਕਰਨ ਜਾਂ ਬਲਾਬ ਵਾਪਸ ਕਰਨ ਵਿੱਚ ਸਮਰਥ, ਪਰ ਇਸਨੂੰ ਬਲਾਬ ਸਟੋਰੇਜ ਵਿੱਚ ਸੇਵ ਕਰਨ ਵਿੱਚ ਅਸਮਰਥ | ਆਉਟਪੁੱਟ ਬਾਈਂਡਿੰਗ ਸੰਰਚਿਤ ਕਰਨ ਵਿੱਚ ਅਸਮਰਥ |

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਨਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤ ਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।