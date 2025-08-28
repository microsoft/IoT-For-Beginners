<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T02:55:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "tr"
}
-->
# Metinden sese - Sanal IoT cihazı

Bu dersin bu bölümünde, metni sese dönüştürmek için konuşma hizmetini kullanarak kod yazacaksınız.

## Metni sese dönüştürme

Bir önceki derste konuşmayı metne dönüştürmek için kullandığınız konuşma hizmetleri SDK'sı, metni tekrar sese dönüştürmek için de kullanılabilir. Ses talep ederken, kullanılacak sesi belirtmeniz gerekir çünkü konuşma, çeşitli farklı sesler kullanılarak oluşturulabilir.

Her dil, farklı seslerden oluşan bir yelpazeyi destekler ve konuşma hizmetleri SDK'sından her dil için desteklenen seslerin listesini alabilirsiniz.

### Görev - Metni sese dönüştürme

1. VS Code'da `smart-timer` projesini açın ve sanal ortamın terminalde yüklü olduğundan emin olun.

1. `azure.cognitiveservices.speech` paketinden `SpeechSynthesizer`'ı mevcut ithalatlara ekleyerek içe aktarın:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say` fonksiyonunun üstüne, konuşma sentezleyici ile kullanılacak bir konuşma yapılandırması oluşturun:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Bu, tanıyıcı tarafından kullanılan aynı API anahtarını, konumu ve dili kullanır.

1. Bunun altına, bir ses almak ve konuşma yapılandırmasında ayarlamak için aşağıdaki kodu ekleyin:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Bu, mevcut tüm seslerin bir listesini alır ve ardından kullanılan dile uyan ilk sesi bulur.

    > 💁 Desteklenen seslerin tam listesini [Microsoft Docs'taki Dil ve ses desteği dokümantasyonundan](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) alabilirsiniz. Belirli bir sesi kullanmak istiyorsanız, bu fonksiyonu kaldırabilir ve bu dokümantasyondan ses adını sabit kodlayabilirsiniz. Örneğin:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say` fonksiyonunun içeriğini, yanıt için SSML oluşturacak şekilde güncelleyin:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Bunun altına, konuşma tanımayı durdurun, SSML'i konuşun ve ardından tanımayı tekrar başlatın:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Metin konuşulurken, zamanlayıcının başlatıldığının duyurulmasının algılanmasını, LUIS'e gönderilmesini ve muhtemelen yeni bir zamanlayıcı ayarı olarak yorumlanmasını önlemek için tanıma durdurulur.

    > 💁 Bunu, tanımayı durdurma ve yeniden başlatma satırlarını yorumlayarak test edebilirsiniz. Bir zamanlayıcı ayarlayın ve duyurunun yeni bir zamanlayıcı ayarladığını, bunun yeni bir duyuruya neden olduğunu ve bunun sonsuza kadar devam ettiğini görebilirsiniz!

1. Uygulamayı çalıştırın ve işlev uygulamasının da çalıştığından emin olun. Bazı zamanlayıcılar ayarlayın ve zamanlayıcınızın ayarlandığını söyleyen bir sesli yanıt, ardından zamanlayıcı tamamlandığında başka bir sesli yanıt duyacaksınız.

> 💁 Bu kodu [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.