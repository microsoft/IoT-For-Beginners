<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T03:03:46+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "tr"
}
-->
# Mikrofon ve hoparlörlerinizi yapılandırın - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize hoparlör ekleyeceksiniz. Wio Terminal zaten dahili bir mikrofona sahiptir ve bu mikrofon konuşmayı kaydetmek için kullanılabilir.

## Donanım

Wio Terminal zaten dahili bir mikrofona sahiptir ve bu mikrofon, konuşma tanıma için ses kaydetmek amacıyla kullanılabilir.

![Wio Terminal üzerindeki mikrofon](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.tr.png)

Bir hoparlör eklemek için [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) kullanabilirsiniz. Bu, 2 MEMS mikrofonu, bir hoparlör bağlantı noktası ve bir kulaklık soketi içeren harici bir karttır.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.tr.png)

Bir hoparlör eklemek için kulaklık, 3.5mm jaklı bir hoparlör veya [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) gibi JST bağlantılı bir hoparlör kullanmanız gerekecek.

ReSpeaker 2-Mics Pi Hat'i bağlamak için 40 pinli pin-to-pin (erkek-erkek olarak da adlandırılır) jumper kablolarına ihtiyacınız olacak.

> 💁 Lehim yapmaya alışkınsanız, ReSpeaker'ı bağlamak için [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) kullanabilirsiniz.

Ayrıca ses indirmek ve oynatmak için bir SD karta ihtiyacınız olacak. Wio Terminal yalnızca 16GB'a kadar SD Kartları destekler ve bu kartların FAT32 veya exFAT olarak formatlanmış olması gerekir.

### Görev - ReSpeaker Pi Hat'i bağlayın

1. Wio Terminal kapalıyken, ReSpeaker 2-Mics Pi Hat'i jumper kabloları ve Wio Terminal'in arkasındaki GPIO soketlerini kullanarak Wio Terminal'e bağlayın:

    Pinler şu şekilde bağlanmalıdır:

    ![Bir pin diyagramı](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.tr.png)

1. ReSpeaker ve Wio Terminal'i GPIO soketleri yukarı bakacak şekilde ve sol tarafta olacak şekilde konumlandırın.

1. ReSpeaker'ın GPIO soketinin sol üst kısmındaki soketten başlayın. ReSpeaker'ın sol üst soketinden Wio Terminal'in sol üst soketine bir pin-to-pin jumper kablosu bağlayın.

1. GPIO soketlerinin sol tarafında bu işlemi aşağıya kadar tekrarlayın. Pinlerin sıkıca oturduğundan emin olun.

    ![ReSpeaker'ın sol tarafındaki pinlerin Wio Terminal'in sol tarafındaki pinlere bağlanmış hali](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.tr.png)

    ![ReSpeaker'ın sol tarafındaki pinlerin Wio Terminal'in sol tarafındaki pinlere bağlanmış hali](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.tr.png)

    > 💁 Eğer jumper kablolarınız şeritler halinde bağlıysa, hepsini bir arada tutun - bu, tüm kabloları sırayla bağladığınızdan emin olmayı kolaylaştırır.

1. Aynı işlemi ReSpeaker ve Wio Terminal'in sağ tarafındaki GPIO soketleri için tekrarlayın. Bu kablolar, zaten bağlı olan kabloların etrafından geçmelidir.

    ![ReSpeaker'ın sağ tarafındaki pinlerin Wio Terminal'in sağ tarafındaki pinlere bağlanmış hali](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.tr.png)

    ![ReSpeaker'ın sağ tarafındaki pinlerin Wio Terminal'in sağ tarafındaki pinlere bağlanmış hali](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.tr.png)

    > 💁 Eğer jumper kablolarınız şeritler halinde bağlıysa, bunları iki şeride ayırın. Mevcut kabloların her iki yanından birer şerit geçirin.

    > 💁 Pinlerin bir blok halinde kalmasını sağlamak ve bağlantı sırasında çıkmalarını önlemek için yapışkan bant kullanabilirsiniz.
    >
    > ![Bantla sabitlenmiş pinler](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.tr.png)

1. Bir hoparlör eklemeniz gerekecek.

    * Eğer JST kablolu bir hoparlör kullanıyorsanız, bunu ReSpeaker üzerindeki JST portuna bağlayın.

      ![JST kablosuyla ReSpeaker'a bağlanmış bir hoparlör](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.tr.png)

    * Eğer 3.5mm jaklı bir hoparlör veya kulaklık kullanıyorsanız, bunu 3.5mm jak soketine takın.

      ![3.5mm jak soketiyle ReSpeaker'a bağlanmış bir hoparlör](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.tr.png)

### Görev - SD kartı ayarlayın

1. SD Kartı bilgisayarınıza bağlayın, eğer bir SD Kart yuvası yoksa harici bir okuyucu kullanın.

1. Bilgisayarınızdaki uygun aracı kullanarak SD Kartı formatlayın ve FAT32 veya exFAT dosya sistemini seçtiğinizden emin olun.

1. SD kartı, Wio Terminal'in sol tarafındaki güç düğmesinin hemen altındaki SD Kart yuvasına yerleştirin. Kartın tamamen yerleştiğinden ve tıklandığından emin olun - bunu yapmak için ince bir alet veya başka bir SD Kart kullanmanız gerekebilir.

    ![SD kartı güç düğmesinin altındaki SD kart yuvasına yerleştirme](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.tr.png)

    > 💁 SD Kartı çıkarmak için, hafifçe içeri itin ve kart dışarı fırlayacaktır. Bunu yapmak için düz uçlu bir tornavida veya başka bir SD Kart gibi ince bir alete ihtiyacınız olabilir.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.