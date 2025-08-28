<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T00:09:39+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "tl"
}
-->
# Suriin ang mga function binding

## Mga Panuto

Ang mga function binding ay nagbibigay-daan sa iyong code na mag-save ng mga blob sa blob storage sa pamamagitan ng pagbabalik ng mga ito mula sa `main` function. Ang Azure Storage account, koleksyon, at iba pang detalye ay naka-configure sa `function.json` file.

Kapag nagtatrabaho gamit ang Azure o iba pang teknolohiya ng Microsoft, ang pinakamahusay na mapagkukunan ng impormasyon ay [ang Microsoft documentation sa docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Sa gawaing ito, kakailanganin mong basahin ang dokumentasyon ng Azure Functions binding upang malaman kung paano i-set up ang output binding.

Ilang mga pahina na maaaring tingnan upang makapagsimula ay:

* [Mga konsepto ng Azure Functions triggers at bindings](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Pangkalahatang-ideya ng Azure Blob storage bindings para sa Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding para sa Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubric

| Pamantayan | Natatangi | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | --------- | ----------------- | ------------------------ |
| I-configure ang blob storage output binding | Na-configure nang maayos ang output binding, naibalik ang blob, at matagumpay na na-store ito sa blob storage | Na-configure ang output binding, o naibalik ang blob ngunit hindi ito matagumpay na na-store sa blob storage | Hindi na-configure ang output binding |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.