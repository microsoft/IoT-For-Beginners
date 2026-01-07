<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2026-01-07T04:59:49+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ml"
}
-->
# ഫംഗ്ഷൻ ബൈൻഡിംഗ് പരിശോധിക്കുക

## നിര്‍ദ്ദേശങ്ങള്‍

ഫംഗ്ഷൻ ബൈൻഡിംഗുകൾ നിങ്ങളുടെ കോഡ് `main` ഫംഗ്ഷനിൽ നിന്ന് ബ്ലോബുകൾ ബ്ലോബു സ്റ്റോറേജിലേക്ക് തിരിച്ചറിയുന്നതിനായി അനുവദിക്കുന്നു. Azure Storage അക്കൌണ്ട്, ശേഖരം, മറ്റ് വിശദാംശങ്ങൾ `function.json` ഫയലിൽ കോൺഫിഗർ ചെയ്യപ്പെട്ടിരിക്കുന്നു.

Azure അല്ലെങ്കിൽ മറ്റ് Microsoft സാങ്കേതികവിദ്യകളുമായി പ്രവർത്തിക്കുമ്പോൾ, ഏറ്റവും മികച്ച വിവരങ്ങളുടെ ഉറവിടം [docs.com ലെ Microsoft ഡോക്യുമെന്റേഷന്](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ആണ്. ഈ അസൈൻമെന്റിൽ നിങ്ങൾ എക്സ്പോർട്ട് ബൈൻഡിംഗ് സെറ്റ്-അപ്പിന് Azure Functions ബൈൻഡിംഗ് ഡോക്യുമെന്റേഷൻ വായിക്കേണ്ടതുണ്ട്.

പ്രാരംഭമായി നോക്കാനുള്ള ചില പേജുകൾ:

* [Azure Functions ട്രിഗറുകളും ബൈൻഡിങ്ങുകളും - അടിസ്ഥാനങ്ങൾ](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage ബൈൻഡിങ്ങുകൾ Azure Functions ക്കായി - അവലോകനം](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage ഔട്ട്പുട്ട് ബൈൻഡിംഗ് Azure Functions ക്കായി](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## റൂബ്രിക്

|Criteria|പ്രതിഷ്ഠിതം|മാകൂല്യം|സാധനശേഷി മെച്ചപ്പെടുത്തേണ്ടത്|
|--------|---------|-------|------------------|
|ബ്ലോബു സ്റ്റോറേജ് ഔട്ട്പുട്ട് ബൈൻഡിംഗ് കോൺഫിഗർ ചെയ്യുക|അവസാന ഫലമായി ഔട്ട്പുട്ട് ബൈൻഡിംഗ് കോൺഫിഗർ ചെയ്തു, ബ്ലോബു തിരികെ നൽകിയും അത് വിജയകരമായി സ്റ്റോറേജിലേക്ക് സൂക്ഷിച്ചു|ഔട്ട്പുട്ട് ബൈൻഡിംഗ് കോൺഫിഗർ ചെയ്യുവാനും അല്ലെങ്കിൽ ബ്ലോബു തിരികെ നൽകാനും സാധിച്ചു, എന്നാൽ അത് സ്റ്റോറേജിലേക്ക് വിജയകരമായി സൂക്ഷിക്കാൻ സാധിച്ചില്ല|ഔട്ട്പുട്ട് ബൈൻഡിംഗ് എവിടെയും കോൺഫിഗറുചെയ്യാനായില്ല|

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**വചനവിമുക്തി**:  
ഈ രേഖ AI വിവർത്തന സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവർത്തനം ചെയ്‌തു. നാം സമ്പൂർണമായ ശരിതൈല്യത്തിനായി പരിശ്രമിക്കുന്നുവെങ്കിലും, സ്വയംക്രമിത വിവർത്തനങ്ങളിൽ തെറ്റുകൾ അല്ലെങ്കിൽ അസാധുതകൾ ഉണ്ടാകാം എന്നതു ശ്രദ്ധിക്കുക. മാതൃഭാഷയിലെ യഥാർത്ഥ രേഖ യഥാർത്ഥ ഉറവിടമായി കണക്കാക്കേണ്ടതാണ്. നിർണായക വിവരങ്ങൾക്കായി പ്രൊഫഷണൽ മനുഷ്യ വിവർത്തനം ശുപാർശ ചെയ്യപ്പെടുന്നു. ഈ വിവർത്തനം ഉപയോഗിക്കുന്നതിനാൽ ഉണ്ടാകാവുന്ന ഏത് തെറ്റിദ്ധാരണകൾക്കും അല്ലെങ്കിൽ വ്യാഖ്യാന ത്‌വരണങ്ങൾക്കും ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->