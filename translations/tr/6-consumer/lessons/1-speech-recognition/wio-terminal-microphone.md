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

![Wio Terminal üzerindeki mikrofon](../../../../../translated_images/tr/wio-mic.3f8c843dbe8ad917.webp)

Bir hoparlör eklemek için [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) kullanabilirsiniz. Bu, 2 MEMS mikrofonu, bir hoparlör bağlantı noktası ve bir kulaklık soketi içeren harici bir karttır.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/tr/respeaker.f5d19d1c6b14ab16.webp)

Bir hoparlör eklemek için kulaklık, 3.5mm jaklı bir hoparlör veya [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) gibi JST bağlantılı bir hoparlör kullanmanız gerekecek.

ReSpeaker 2-Mics Pi Hat'i bağlamak için 40 pinli pin-to-pin (erkek-erkek olarak da adlandırılır) jumper kablolarına ihtiyacınız olacak.

> 💁 Lehim yapmaya alışkınsanız, ReSpeaker'ı bağlamak için [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) kullanabilirsiniz.

Ayrıca ses indirmek ve oynatmak için bir SD karta ihtiyacınız olacak. Wio Terminal yalnızca 16GB'a kadar SD Kartları destekler ve bu kartların FAT32 veya exFAT olarak formatlanmış olması gerekir.

### Görev - ReSpeaker Pi Hat'i bağlayın

1. Wio Terminal kapalıyken, ReSpeaker 2-Mics Pi Hat'i jumper kabloları ve Wio Terminal'in arkasındaki GPIO soketlerini kullanarak Wio Terminal'e bağlayın:

    Pinler şu şekilde bağlanmalıdır:

    ![Bir pin diyagramı](../../../../../translated_images/tr/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. ReSpeaker ve Wio Terminal'i GPIO soketleri yukarı bakacak şekilde ve sol tarafta olacak şekilde konumlandırın.

1. ReSpeaker'ın GPIO soketinin sol üst kısmındaki soketten başlayın. ReSpeaker'ın sol üst soketinden Wio Terminal'in sol üst soketine bir pin-to-pin jumper kablosu bağlayın.

1. GPIO soketlerinin sol tarafında bu işlemi aşağıya kadar tekrarlayın. Pinlerin sıkıca oturduğundan emin olun.

    ![ReSpeaker'ın sol tarafındaki pinlerin Wio Terminal'in sol tarafındaki pinlere bağlanmış hali](../../../../../translated_images/tr/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![ReSpeaker'ın sol tarafındaki pinlerin Wio Terminal'in sol tarafındaki pinlere bağlanmış hali](../../../../../translated_images/tr/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 Eğer jumper kablolarınız şeritler halinde bağlıysa, hepsini bir arada tutun - bu, tüm kabloları sırayla bağladığınızdan emin olmayı kolaylaştırır.

1. Aynı işlemi ReSpeaker ve Wio Terminal'in sağ tarafındaki GPIO soketleri için tekrarlayın. Bu kablolar, zaten bağlı olan kabloların etrafından geçmelidir.

    ![ReSpeaker'ın sağ tarafındaki pinlerin Wio Terminal'in sağ tarafındaki pinlere bağlanmış hali](../../../../../translated_images/tr/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![ReSpeaker'ın sağ tarafındaki pinlerin Wio Terminal'in sağ tarafındaki pinlere bağlanmış hali](../../../../../translated_images/tr/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 Eğer jumper kablolarınız şeritler halinde bağlıysa, bunları iki şeride ayırın. Mevcut kabloların her iki yanından birer şerit geçirin.

    > 💁 Pinlerin bir blok halinde kalmasını sağlamak ve bağlantı sırasında çıkmalarını önlemek için yapışkan bant kullanabilirsiniz.
    >
    > ![Bantla sabitlenmiş pinler](../../../../../translated_images/tr/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. Bir hoparlör eklemeniz gerekecek.

    * Eğer JST kablolu bir hoparlör kullanıyorsanız, bunu ReSpeaker üzerindeki JST portuna bağlayın.

      ![JST kablosuyla ReSpeaker'a bağlanmış bir hoparlör](../../../../../translated_images/tr/respeaker-jst-speaker.a441d177809df945.webp)

    * Eğer 3.5mm jaklı bir hoparlör veya kulaklık kullanıyorsanız, bunu 3.5mm jak soketine takın.

      ![3.5mm jak soketiyle ReSpeaker'a bağlanmış bir hoparlör](../../../../../translated_images/tr/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### Görev - SD kartı ayarlayın

1. SD Kartı bilgisayarınıza bağlayın, eğer bir SD Kart yuvası yoksa harici bir okuyucu kullanın.

1. Bilgisayarınızdaki uygun aracı kullanarak SD Kartı formatlayın ve FAT32 veya exFAT dosya sistemini seçtiğinizden emin olun.

1. SD kartı, Wio Terminal'in sol tarafındaki güç düğmesinin hemen altındaki SD Kart yuvasına yerleştirin. Kartın tamamen yerleştiğinden ve tıklandığından emin olun - bunu yapmak için ince bir alet veya başka bir SD Kart kullanmanız gerekebilir.

    ![SD kartı güç düğmesinin altındaki SD kart yuvasına yerleştirme](../../../../../translated_images/tr/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 SD Kartı çıkarmak için, hafifçe içeri itin ve kart dışarı fırlayacaktır. Bunu yapmak için düz uçlu bir tornavida veya başka bir SD Kart gibi ince bir alete ihtiyacınız olabilir.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.