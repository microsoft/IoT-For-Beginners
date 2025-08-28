<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T02:46:14+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "tr"
}
-->
# IoT Edge tabanlı bir görüntü sınıflandırıcı kullanarak bir görüntüyü sınıflandırma - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, IoT Edge cihazında çalışan Görüntü Sınıflandırıcıyı kullanacaksınız.

## IoT Edge sınıflandırıcıyı kullanma

IoT cihazı, IoT Edge görüntü sınıflandırıcıyı kullanacak şekilde yönlendirilebilir. Görüntü Sınıflandırıcı için URL `http://<IP adresi veya adı>/image` şeklindedir. `<IP adresi veya adı>` kısmını IoT Edge çalıştıran bilgisayarın IP adresi veya ana bilgisayar adı ile değiştirin.

Custom Vision için Python kütüphanesi yalnızca bulut barındırmalı modellerle çalışır, IoT Edge üzerinde barındırılan modellerle çalışmaz. Bu, sınıflandırıcıyı çağırmak için REST API kullanmanız gerektiği anlamına gelir.

### Görev - IoT Edge sınıflandırıcıyı kullanma

1. VS Code'da `fruit-quality-detector` projesini açın, eğer zaten açık değilse. Sanal bir IoT cihazı kullanıyorsanız, sanal ortamın etkinleştirildiğinden emin olun.

1. `app.py` dosyasını açın ve `azure.cognitiveservices.vision.customvision.prediction` ve `msrest.authentication` içe aktarma ifadelerini kaldırın.

1. Dosyanın en üstüne aşağıdaki içe aktarma ifadesini ekleyin:

    ```python
    import requests
    ```

1. Görüntü bir dosyaya kaydedildikten sonraki tüm kodu silin, `image_file.write(image.read())` ifadesinden dosyanın sonuna kadar.

1. Dosyanın sonuna aşağıdaki kodu ekleyin:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    `<URL>` kısmını sınıflandırıcınızın URL'si ile değiştirin.

    Bu kod, sınıflandırıcıya bir REST POST isteği gönderir ve görüntüyü isteğin gövdesi olarak iletir. Sonuçlar JSON formatında geri döner ve bu, olasılıkları yazdırmak için çözülür.

1. Kodunuzu çalıştırın, kameranızı bir meyveye doğrultarak, uygun bir görüntü seti kullanarak veya sanal IoT donanımı kullanıyorsanız webcam üzerinde görünen meyvelerle. Konsolda çıktıyı göreceksiniz:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Bu kodu [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) veya [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Meyve kalite sınıflandırıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul edilmez.