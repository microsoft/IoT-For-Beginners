<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-25T16:37:35+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "hi"
}
-->
# IoT Edge चलाने वाली वर्चुअल मशीन बनाएं

Azure में, आप एक वर्चुअल मशीन बना सकते हैं - क्लाउड में एक कंप्यूटर जिसे आप अपनी इच्छानुसार कॉन्फ़िगर कर सकते हैं और उस पर अपना सॉफ़्टवेयर चला सकते हैं।

> 💁 आप वर्चुअल मशीनों के बारे में अधिक जानकारी [वर्चुअल मशीन पेज पर विकिपीडिया](https://wikipedia.org/wiki/Virtual_machine) पर पढ़ सकते हैं।

## कार्य - IoT Edge वर्चुअल मशीन सेट अप करें

1. निम्नलिखित कमांड चलाएं ताकि एक VM बनाया जा सके जिसमें Azure IoT Edge पहले से ही इंस्टॉल हो:

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

    `<vm_name>` को इस वर्चुअल मशीन के लिए एक नाम से बदलें। यह नाम वैश्विक रूप से अद्वितीय होना चाहिए, इसलिए कुछ ऐसा उपयोग करें जैसे `fruit-quality-detector-vm-` और उसके अंत में अपना नाम या कोई अन्य मान जोड़ें।

    `<username>` और `<password>` को VM में लॉग इन करने के लिए उपयोग किए जाने वाले यूज़रनेम और पासवर्ड से बदलें। ये अपेक्षाकृत सुरक्षित होने चाहिए, इसलिए आप admin/password का उपयोग नहीं कर सकते।

    `<connection_string>` को अपने `fruit-quality-detector-edge` IoT Edge डिवाइस के कनेक्शन स्ट्रिंग से बदलें।

    यह VM को `DS1 v2` वर्चुअल मशीन के रूप में कॉन्फ़िगर करेगा। ये श्रेणियां मशीन की शक्ति और उसकी लागत को इंगित करती हैं। इस VM में 1 CPU और 3.5GB RAM है।

    > 💰 आप इन VMs की वर्तमान कीमतें [Azure वर्चुअल मशीन प्राइसिंग गाइड](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) पर देख सकते हैं।

    एक बार VM बन जाने के बाद, IoT Edge runtime स्वचालित रूप से इंस्टॉल हो जाएगा और आपके IoT Hub से `fruit-quality-detector-edge` डिवाइस के रूप में कनेक्ट होने के लिए कॉन्फ़िगर किया जाएगा।

1. आपको VM से इमेज क्लासिफायर को कॉल करने के लिए या तो IP एड्रेस या DNS नाम की आवश्यकता होगी। इसे प्राप्त करने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` फ़ील्ड या `Fqdns` फ़ील्ड में से किसी एक की कॉपी लें।

1. VMs पैसे खर्च करते हैं। लेखन के समय, एक DS1 VM की लागत लगभग $0.06 प्रति घंटे है। लागत कम रखने के लिए, आपको VM को तब बंद कर देना चाहिए जब आप इसका उपयोग नहीं कर रहे हों, और इस प्रोजेक्ट के समाप्त होने पर इसे हटा देना चाहिए।

    आप अपने VM को हर दिन एक निश्चित समय पर स्वचालित रूप से बंद करने के लिए कॉन्फ़िगर कर सकते हैं। इसका मतलब है कि यदि आप इसे बंद करना भूल जाते हैं, तो आपको स्वचालित शटडाउन तक के समय से अधिक बिल नहीं किया जाएगा। इसे सेट करने के लिए निम्नलिखित कमांड का उपयोग करें:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>` को अपने वर्चुअल मशीन के नाम से बदलें।

    `<shutdown_time_utc>` को UTC समय से बदलें जब आप चाहते हैं कि VM 4 अंकों के रूप में HHMM का उपयोग करके बंद हो जाए। उदाहरण के लिए, यदि आप इसे UTC में आधी रात को बंद करना चाहते हैं, तो इसे `0000` सेट करें। यदि आप यूएस वेस्ट कोस्ट पर शाम 7:30 बजे बंद करना चाहते हैं, तो आप 0230 का उपयोग करेंगे (यूएस वेस्ट कोस्ट पर शाम 7:30 बजे UTC में 2:30AM है)।

1. आपका इमेज क्लासिफायर इस एज डिवाइस पर पोर्ट 80 (मानक HTTP पोर्ट) पर चल रहा होगा। डिफ़ॉल्ट रूप से, वर्चुअल मशीनों में इनबाउंड पोर्ट ब्लॉक होते हैं, इसलिए आपको पोर्ट 80 को सक्षम करना होगा। पोर्ट नेटवर्क सुरक्षा समूहों पर सक्षम होते हैं, इसलिए पहले आपको अपने VM के नेटवर्क सुरक्षा समूह का नाम जानना होगा, जिसे आप निम्नलिखित कमांड से प्राप्त कर सकते हैं:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` फ़ील्ड का मान कॉपी करें।

1. नेटवर्क सुरक्षा समूह में पोर्ट 80 खोलने के लिए एक नियम जोड़ने के लिए निम्नलिखित कमांड चलाएं:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>` को पिछले चरण से नेटवर्क सुरक्षा समूह के नाम से बदलें।

### कार्य - अपने VM को प्रबंधित करें ताकि लागत कम हो

1. जब आप अपने VM का उपयोग नहीं कर रहे हों, तो आपको इसे बंद कर देना चाहिए। VM को बंद करने के लिए निम्नलिखित कमांड का उपयोग करें:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>` को अपने वर्चुअल मशीन के नाम से बदलें।

    > 💁 एक `az vm stop` कमांड है जो VM को रोक देगा, लेकिन यह कंप्यूटर को आपके लिए आवंटित रखता है, इसलिए आप अभी भी इसे चलाने के समान भुगतान करते हैं।

1. VM को पुनः शुरू करने के लिए निम्नलिखित कमांड का उपयोग करें:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>` को अपने वर्चुअल मशीन के नाम से बदलें।

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।