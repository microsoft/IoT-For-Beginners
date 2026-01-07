<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2026-01-07T04:59:31+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "te"
}
-->
# ఫంక్షన్ బైండింగ్స్ పరిశీలించండి

## సూచనలు

ఫంక్షన్ బైండింగ్స్ మీ కోడ్‌ను `main` ఫంక్షన్ నుండి బ్లాబ్స్‌ను తిరిగి ఇవ్వడం ద్వారా బ్లాబ్ స్టోరేజ్‌కి సేవ్ చేయడానికి అనుమతిస్తాయి. Azure స్టోరేజ్ ఖాతా, కలెక్షన్ మరియు ఇతర వివరాలు `function.json` ఫైల్‌లో కాన్ఫిగర్ చేయబడతాయి.

Azure లేదా ఇతర Microsoft టెక్నాలజీలతో పని చేస్తున్నప్పుడు, ఉత్తమ సమాచారం మూలం [docs.com వద్ద Microsoft డాక్యుమెంటేషన్](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). ఈ అసైన్మెంట్‌లో మీరు అవుట్‌పుట్ బైండింగ్‌ను ఎలా సెట్ చేయాలో తెలుసుకోడానికి Azure Functions బైండింగ్ డాక్యుమెంటేషన్ చదవాలి.

ప్రారంభించడానికి కొన్ని పేజీలు ఉన్నాయి:

* [Azure Functions ట్రిగర్స్ మరియు బైండింగ్స్ కాన్సెప్ట్స్](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob స్టోరేజ్ బైండింగ్స్ కోసం Azure Functions అవలోకనం](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob స్టోరేజ్ అవుట్‌పుట్ బైండింగ్ కోసం Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## రూబ్రిక్

| ప్రమాణాలు | ఉత్తమం | సరిపోతుంది | మెరుగుదల అవసరం |
| -------- | --------- | -------- | ----------------- |
| బ్లాబ్ స్టోరేజ్ అవుట్‌పుట్ బైండింగ్‌ను కాన్ఫిగర్ చేయడం | అవుట్‌పుట్ బైండింగ్‌ను సక్సెస్‌గా కాన్ఫిగర్ చేసి, బ్లాబ్‌ను తిరిగి ఇచ్చి దాన్ని బ్లాబ్ స్టోరేజ్‌లో విజయవంతంగా నిల్వ చేయగలిగినది | అవుట్‌పుట్ బైండింగ్‌ను కాన్ఫిగర్ చేయగలిగింది, లేదా బ్లాబ్‌ను తిరిగి ఇచ్చింది కానీ దాన్ని బ్లాబ్ స్టోరేజ్‌లో విజయవంతంగా నిల్వ చేయలేకపోయింది |  అవుట్‌పుట్ బైండింగ్‌ను కాన్ఫిగర్ చేయలేకపోయింది |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**డిస్క్లేమర్**:  
ఈ డాక్యుమెంట్‌ను AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ద్వారా అనువదించడం జరిగింది. మేము సరైనదైన అనువాదం కోసం శ్రమిస్తున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాలలో తప్పులు లేదా అసత్యతలు ఉండవచ్చు. మూల భాషలో ఉన్న డాక్యుమెంట్‌ను అధికారికమైన మూలంగా పరిగణించాలి. ముఖ్యమైన సమాచారం కోసం ప్రొఫెషనల్ మానవ అనువాదం నిర్వహించడం సూచించబడుతుంది. ఈ అనువాదం వలన వచ్చిన ఏవైనా చేధింపులు లేదా తప్పు అర్థం చేసుకోవడంకకు మేము బాధ్యురాలేమి కాదం.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->