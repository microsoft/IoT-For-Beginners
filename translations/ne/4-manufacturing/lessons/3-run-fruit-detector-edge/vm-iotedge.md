<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T10:42:33+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "ne"
}
-->
# IoT Edge चलाउने भर्चुअल मेसिन बनाउनुहोस्

Azure मा, तपाईं भर्चुअल मेसिन बनाउन सक्नुहुन्छ - क्लाउडमा रहेको कम्प्युटर जसलाई तपाईं आफ्नो इच्छाअनुसार कन्फिगर गर्न सक्नुहुन्छ र आफ्नो सफ्टवेयर चलाउन सक्नुहुन्छ।

> 💁 तपाईं भर्चुअल मेसिनको बारेमा [विकिपिडियाको भर्चुअल मेसिन पृष्ठ](https://wikipedia.org/wiki/Virtual_machine) मा थप जानकारी पढ्न सक्नुहुन्छ।

## कार्य - IoT Edge भर्चुअल मेसिन सेटअप गर्नुहोस्

1. Azure IoT Edge पहिले नै प्रि-इन्स्टल गरिएको VM बनाउन निम्न कमाण्ड चलाउनुहोस्:

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

    `<vm_name>` लाई आफ्नो भर्चुअल मेसिनको नामले बदल्नुहोस्। यो नाम विश्वव्यापी रूपमा अद्वितीय हुनुपर्छ, त्यसैले `fruit-quality-detector-vm-` जस्तै नामको अन्त्यमा आफ्नो नाम वा अन्य मान प्रयोग गर्नुहोस्।

    `<username>` र `<password>` लाई VM मा लगइन गर्न प्रयोग गरिने युजरनेम र पासवर्डले बदल्नुहोस्। यी सुरक्षित हुनुपर्छ, त्यसैले admin/password जस्ता सामान्य पासवर्ड प्रयोग गर्न सकिँदैन।

    `<connection_string>` लाई आफ्नो `fruit-quality-detector-edge` IoT Edge उपकरणको कनेक्शन स्ट्रिङले बदल्नुहोस्।

    यो VM `DS1 v2` भर्चुअल मेसिनको रूपमा कन्फिगर हुनेछ। यी श्रेणीहरूले मेसिन कति शक्तिशाली छ र त्यसैले कति खर्च लाग्छ भन्ने संकेत गर्छ। यस VM मा 1 CPU र 3.5GB RAM छ।

    > 💰 यी VM हरूको हालको मूल्य [Azure Virtual Machine मूल्य मार्गदर्शन](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) मा हेर्न सक्नुहुन्छ।

    VM बनिसकेपछि, IoT Edge रनटाइम स्वतः इन्स्टल हुनेछ र तपाईंको `fruit-quality-detector-edge` उपकरणको रूपमा IoT Hub मा जडान गर्न कन्फिगर हुनेछ।

1. VM बाट इमेज क्लासिफायरलाई कल गर्नको लागि तपाईंलाई VM को IP ठेगाना वा DNS नाम चाहिन्छ। यो प्राप्त गर्न निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` फील्ड वा `Fqdns` फील्डको प्रतिलिपि लिनुहोस्।

1. VM हरूको खर्च लाग्छ। लेख्ने समयमा, DS1 VM को लागत लगभग $0.06 प्रति घण्टा छ। खर्च कम गर्नको लागि, तपाईंले VM प्रयोग नगर्दा बन्द गर्नुपर्छ र यो प्रोजेक्ट समाप्त भएपछि मेटाउनुपर्छ।

    तपाईं आफ्नो VM लाई प्रत्येक दिन निश्चित समयमा स्वतः बन्द हुने गरी कन्फिगर गर्न सक्नुहुन्छ। यसले तपाईंले बन्द गर्न बिर्सनुभयो भने पनि स्वतः बन्द हुने समयसम्म मात्र बिल हुनेछ। यो सेट गर्न निम्न कमाण्ड प्रयोग गर्नुहोस्:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>` लाई आफ्नो भर्चुअल मेसिनको नामले बदल्नुहोस्।

    `<shutdown_time_utc>` लाई UTC समयको रूपमा 4 अंक HHMM प्रयोग गरेर VM बन्द गर्न चाहेको समयले बदल्नुहोस्। उदाहरणका लागि, यदि तपाईं UTC मा मध्यरातमा बन्द गर्न चाहनुहुन्छ भने, यसलाई `0000` सेट गर्नुहोस्। पश्चिमी अमेरिका तटको 7:30PM को लागि, तपाईंले `0230` प्रयोग गर्नुहुनेछ (पश्चिमी अमेरिका तटको 7:30PM UTC मा 2:30AM हो)।

1. तपाईंको इमेज क्लासिफायर यो एज उपकरणमा चलिरहेको हुनेछ, पोर्ट 80 (मानक HTTP पोर्ट) मा सुन्दै। डिफल्ट रूपमा, भर्चुअल मेसिनहरूमा इनबाउन्ड पोर्टहरू ब्लक गरिन्छ, त्यसैले तपाईंले पोर्ट 80 सक्षम गर्न आवश्यक छ। पोर्टहरू नेटवर्क सुरक्षा समूहहरूमा सक्षम गरिन्छ, त्यसैले पहिलोमा तपाईंलाई आफ्नो VM को नेटवर्क सुरक्षा समूहको नाम थाहा हुनुपर्छ, जुन निम्न कमाण्ड चलाएर पत्ता लगाउन सकिन्छ:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` फील्डको मान प्रतिलिपि गर्नुहोस्।

1. पोर्ट 80 खोल्न नेटवर्क सुरक्षा समूहमा नियम थप्न निम्न कमाण्ड चलाउनुहोस्:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>` लाई अघिल्लो चरणबाट नेटवर्क सुरक्षा समूहको नामले बदल्नुहोस्।

### कार्य - आफ्नो VM व्यवस्थापन गरेर खर्च घटाउनुहोस्

1. जब तपाईं आफ्नो VM प्रयोग गरिरहनुभएको छैन, तपाईंले यसलाई बन्द गर्नुपर्छ। VM बन्द गर्न निम्न कमाण्ड प्रयोग गर्नुहोस्:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>` लाई आफ्नो भर्चुअल मेसिनको नामले बदल्नुहोस्।

    > 💁 `az vm stop` कमाण्ड छ जसले VM बन्द गर्छ, तर यसले कम्प्युटरलाई तपाईंको लागि छुट्याएर राख्छ, त्यसैले तपाईंले अझै पनि चलिरहेको जस्तै तिर्नुपर्छ।

1. VM पुनः सुरु गर्न निम्न कमाण्ड प्रयोग गर्नुहोस्:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>` लाई आफ्नो भर्चुअल मेसिनको नामले बदल्नुहोस्।

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव सटीकता सुनिश्चित गर्न प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छन्। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार हुने छैनौं।  