<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T04:12:55+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "tr"
}
-->
# GDD Verilerini Jupyter Notebook Kullanarak Görselleştirme

## Talimatlar

Bu derste, bir IoT sensörü kullanarak GDD verilerini topladınız. İyi GDD verileri elde etmek için, birkaç gün boyunca veri toplamanız gerekir. Sıcaklık verilerini görselleştirmek ve GDD hesaplamak için [Jupyter Notebooks](https://jupyter.org) gibi araçları kullanabilirsiniz.

Öncelikle birkaç gün boyunca veri toplayın. IoT cihazınız çalışırken sunucu kodunuzun sürekli çalıştığından emin olmanız gerekir. Bunun için güç yönetimi ayarlarını düzenleyebilir veya [bu sistemi aktif tutan Python scripti](https://github.com/jaqsparow/keep-system-active) gibi bir şey çalıştırabilirsiniz.

Sıcaklık verilerini topladıktan sonra, bu depodaki Jupyter Notebook'u kullanarak verileri görselleştirebilir ve GDD hesaplayabilirsiniz. Jupyter notebook'lar, genellikle Python'da kod ve talimatları *hücre* adı verilen bloklarda birleştirir. Talimatları okuyabilir, ardından kod bloklarını tek tek çalıştırabilirsiniz. Ayrıca kodu düzenleyebilirsiniz. Örneğin, bu notebook'ta bitkiniz için GDD hesaplamak üzere kullanılan taban sıcaklığı düzenleyebilirsiniz.

1. `gdd-calculation` adlı bir klasör oluşturun.

1. [gdd.ipynb](./code-notebook/gdd.ipynb) dosyasını indirin ve `gdd-calculation` klasörüne kopyalayın.

1. MQTT sunucusu tarafından oluşturulan `temperature.csv` dosyasını kopyalayın.

1. `gdd-calculation` klasöründe yeni bir Python sanal ortamı oluşturun.

1. Jupyter notebook'lar için bazı pip paketlerini ve verileri yönetmek ve görselleştirmek için gereken kütüphaneleri yükleyin:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Notebook'u Jupyter'de çalıştırın:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter başlatılacak ve notebook'u tarayıcınızda açacaktır. Notebook'taki talimatları takip ederek ölçülen sıcaklıkları görselleştirin ve büyüme derecesi günlerini hesaplayın.

    ![Jupyter notebook](../../../../../translated_images/tr/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Değerlendirme Ölçütleri

| Kriter | Mükemmel | Yeterli | Geliştirme Gerekiyor |
| ------- | -------- | ------- | -------------------- |
| Veri Toplama | En az 2 tam gün veri toplayın | En az 1 tam gün veri toplayın | Bir miktar veri toplayın |
| GDD Hesaplama | Notebook'u başarıyla çalıştırın ve GDD hesaplayın | Notebook'u başarıyla çalıştırın | Notebook'u çalıştıramayın |

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.