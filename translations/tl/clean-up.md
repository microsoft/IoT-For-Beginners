<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:34:24+00:00",
  "source_file": "clean-up.md",
  "language_code": "tl"
}
-->
# Linisin ang iyong proyekto

Kapag natapos mo na ang bawat proyekto, maganda na tanggalin ang iyong mga cloud resources.

Sa mga aralin para sa bawat proyekto, maaaring nakagawa ka ng ilan sa mga sumusunod:

* Isang Resource Group
* Isang IoT Hub
* Mga rehistrasyon ng IoT device
* Isang Storage Account
* Isang Functions App
* Isang Azure Maps account
* Isang custom vision project
* Isang Azure Container Registry
* Isang cognitive services resource

Karamihan sa mga resources na ito ay walang gastos - alinman sa ganap na libre, o ginagamit mo ang libreng tier. Para sa mga serbisyo na nangangailangan ng bayad na tier, malamang na ginamit mo ang mga ito sa antas na kasama sa libreng allowance, o magkakaroon lamang ng kaunting halaga.

Kahit na mababa ang mga gastos, sulit na tanggalin ang mga resources na ito kapag tapos ka na. Halimbawa, maaari ka lamang magkaroon ng isang IoT Hub na gumagamit ng libreng tier, kaya kung nais mong gumawa ng isa pa, kailangan mong gumamit ng bayad na tier.

Ang lahat ng iyong mga serbisyo ay nilikha sa loob ng Resource Groups, at mas madali itong pamahalaan. Maaari mong tanggalin ang Resource Group, at lahat ng mga serbisyo sa Resource Group na iyon ay matatanggal din.

Upang tanggalin ang Resource Group, patakbuhin ang sumusunod na command sa iyong terminal o command prompt:

```sh
az group delete --name <resource-group-name>
```

Palitan ang `<resource-group-name>` ng pangalan ng Resource Group na nais mong tanggalin.

Magpapakita ng kumpirmasyon:

```output
Are you sure you want to perform this operation? (y/n): 
```

Ilagay ang `y` upang kumpirmahin at tanggalin ang Resource Group.

Aabutin ng ilang sandali upang tanggalin ang lahat ng mga serbisyo.

> 💁 Maaari kang magbasa pa tungkol sa pagtanggal ng mga resource groups sa [Azure Resource Manager resource group and resource deletion documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.