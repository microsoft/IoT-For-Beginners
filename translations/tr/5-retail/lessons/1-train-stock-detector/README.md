# Stok Dedektörü Eğitimi

![Bu dersin genel bir sketchnote görünümü](../../../../../translated_images/tr/lesson-19.cf6973cecadf080c.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için resme tıklayın.

Bu video, Azure Custom Vision hizmeti ile Nesne Tespiti hakkında genel bir bakış sunar. Bu ders kapsamında bu hizmet ele alınacaktır.

[![Custom Vision 2 - Nesne Tespiti Kolaylaştırıldı | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Videoyu izlemek için yukarıdaki resme tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Giriş

Önceki projede, bir görüntü sınıflandırıcı eğitmek için yapay zeka kullandınız - bir model, bir görüntünün olgun meyve veya olgunlaşmamış meyve gibi bir şey içerip içermediğini söyleyebilir. Görüntülerle kullanılabilecek başka bir yapay zeka modeli türü ise nesne tespitidir. Bu modeller, bir görüntüyü etiketlerle sınıflandırmaz, bunun yerine nesneleri tanımak için eğitilir ve yalnızca görüntünün mevcut olduğunu değil, görüntüde nerede olduğunu da tespit edebilir. Bu, görüntülerdeki nesneleri saymanıza olanak tanır.

Bu derste nesne tespiti hakkında bilgi edineceksiniz, bunun perakende sektöründe nasıl kullanılabileceğini öğreneceksiniz ve bulutta bir nesne dedektörü eğitmeyi öğreneceksiniz.

Bu derste ele alınacak konular:

* [Nesne tespiti](../../../../../5-retail/lessons/1-train-stock-detector)
* [Perakende sektöründe nesne tespiti kullanımı](../../../../../5-retail/lessons/1-train-stock-detector)
* [Bir nesne dedektörü eğitmek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Nesne dedektörünüzü test etmek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Nesne dedektörünüzü yeniden eğitmek](../../../../../5-retail/lessons/1-train-stock-detector)

## Nesne Tespiti

Nesne tespiti, yapay zeka kullanarak görüntülerdeki nesneleri tespit etmeyi içerir. Son projede eğittiğiniz görüntü sınıflandırıcıdan farklı olarak, nesne tespiti bir görüntüye bir bütün olarak en iyi etiketi tahmin etmekle ilgili değildir, bir veya daha fazla nesneyi bir görüntüde bulmakla ilgilidir.

### Nesne Tespiti ve Görüntü Sınıflandırma Arasındaki Fark

Görüntü sınıflandırma, bir görüntüyü bir bütün olarak sınıflandırmakla ilgilidir - tüm görüntünün her etikete ne kadar uyduğuna dair olasılıkları belirler. Modeli eğitmek için kullanılan her etiket için olasılıkları geri alırsınız.

![Kaju fıstığı ve domates salçasının görüntü sınıflandırması](../../../../../translated_images/tr/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

Yukarıdaki örnekte, iki görüntü, kaju fıstığı kutuları veya domates salçası kutularını sınıflandırmak için eğitilmiş bir model kullanılarak sınıflandırılmıştır. İlk görüntü bir kaju fıstığı kutusudur ve görüntü sınıflandırıcıdan iki sonuç alır:

| Etiket         | Olasılık    |
| -------------- | ----------: |
| `kaju fıstığı` | %98.4       |
| `domates salçası` | %1.6       |

İkinci görüntü bir domates salçası kutusudur ve sonuçlar şunlardır:

| Etiket         | Olasılık    |
| -------------- | ----------: |
| `kaju fıstığı` | %0.7        |
| `domates salçası` | %99.3      |

Bu değerleri, görüntüde ne olduğunu tahmin etmek için bir eşik yüzdesi ile kullanabilirsiniz. Ancak bir görüntüde birden fazla domates salçası kutusu veya hem kaju fıstığı hem de domates salçası varsa ne olur? Sonuçlar muhtemelen istediğiniz şeyi vermez. İşte burada nesne tespiti devreye girer.

Nesne tespiti, bir modeli nesneleri tanımak için eğitmeyi içerir. Görüntüleri nesne içeren görüntüler olarak verip her görüntünün bir etiket veya başka bir şey olduğunu söylemek yerine, görüntünün belirli bir nesneyi içeren bölümünü vurgular ve etiketlersiniz. Bir görüntüde tek bir nesneyi veya birden fazla nesneyi etiketleyebilirsiniz. Bu şekilde model, nesnenin kendisinin nasıl göründüğünü öğrenir, sadece nesneyi içeren görüntülerin nasıl göründüğünü değil.

Sonrasında tahmin yapmak için kullandığınızda, etiketler ve yüzdeler listesi yerine, algılanan nesnelerin bir listesini, sınırlayıcı kutularını ve sınırlayıcı kutunun atanan etikete uyma olasılığını geri alırsınız.

> 🎓 *Sınırlayıcı kutular*, bir nesnenin etrafındaki kutulardır.

![Kaju fıstığı ve domates salçasının nesne tespiti](../../../../../translated_images/tr/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Yukarıdaki görüntüde hem bir kaju fıstığı kutusu hem de üç domates salçası kutusu bulunmaktadır. Nesne dedektörü, kaju fıstığını tespit etmiş ve kaju fıstığını içeren sınırlayıcı kutuyu ve sınırlayıcı kutunun nesneyi içerme olasılığını, bu durumda %97.6 olarak geri döndürmüştür. Nesne dedektörü ayrıca üç domates salçası kutusunu tespit etmiş ve her biri için ayrı sınırlayıcı kutular sağlamıştır. Her biri, sınırlayıcı kutunun bir domates salçası kutusunu içerme olasılığına sahiptir.

✅ Görüntü tabanlı yapay zeka modelleri için kullanmak isteyebileceğiniz farklı senaryoları düşünün. Hangileri sınıflandırma gerektirir ve hangileri nesne tespiti gerektirir?

### Nesne Tespiti Nasıl Çalışır?

Nesne tespiti, karmaşık ML modelleri kullanır. Bu modeller, görüntüyü birden fazla hücreye bölerek çalışır, ardından sınırlayıcı kutunun merkezi, modeli eğitmek için kullanılan görüntülerden birine uyan bir görüntünün merkezi olup olmadığını kontrol eder. Bunu, görüntünün farklı bölümlerinde eşleşmeler aramak için bir görüntü sınıflandırıcı çalıştırmak gibi düşünebilirsiniz.

> 💁 Bu, oldukça basitleştirilmiş bir açıklamadır. Nesne tespiti için birçok teknik vardır ve bunlar hakkında daha fazla bilgiyi [Wikipedia'daki Nesne Tespiti sayfasında](https://wikipedia.org/wiki/Object_detection) okuyabilirsiniz.

Nesne tespiti yapabilen bir dizi farklı model vardır. Özellikle ünlü bir model olan [YOLO (You Only Look Once)](https://pjreddie.com/darknet/yolo/), inanılmaz derecede hızlıdır ve insanlar, köpekler, şişeler ve arabalar gibi 20 farklı nesne sınıfını tespit edebilir.

✅ YOLO modeli hakkında [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/) adresinden bilgi edinin.

Nesne tespiti modelleri, transfer öğrenimi kullanılarak özel nesneleri tespit etmek için yeniden eğitilebilir.

## Perakende Sektöründe Nesne Tespiti Kullanımı

Nesne tespiti, perakende sektöründe birçok kullanım alanına sahiptir. Bazıları şunlardır:

* **Stok kontrolü ve sayımı** - raflardaki stokun azaldığını tanıma. Stok çok düşükse, personel veya robotlara yeniden stoklama bildirimleri gönderilebilir.
* **Maske tespiti** - halk sağlığı olayları sırasında maske politikası olan mağazalarda, nesne tespiti maskeli ve maskesiz insanları tanıyabilir.
* **Otomatik faturalandırma** - otomatik mağazalarda raflardan alınan ürünleri tespit ederek müşterilere uygun şekilde faturalandırma.
* **Tehlike tespiti** - zemindeki kırık nesneleri veya dökülmüş sıvıları tanıyarak temizlik ekiplerini uyarma.

✅ Araştırma yapın: Perakende sektöründe nesne tespiti için başka hangi kullanım alanları olabilir?

## Bir Nesne Dedektörü Eğitmek

Custom Vision kullanarak bir nesne dedektörü eğitebilirsiniz, tıpkı bir görüntü sınıflandırıcıyı eğittiğiniz gibi.

### Görev - Bir Nesne Dedektörü Oluşturun

1. Bu proje için `stock-detector` adlı bir Kaynak Grubu oluşturun.

1. `stock-detector` kaynak grubunda ücretsiz bir Custom Vision eğitim kaynağı ve ücretsiz bir Custom Vision tahmin kaynağı oluşturun. Bunlara `stock-detector-training` ve `stock-detector-prediction` adını verin.

    > 💁 Sadece bir ücretsiz eğitim ve tahmin kaynağına sahip olabilirsiniz, bu yüzden önceki derslerden projenizi temizlediğinizden emin olun.

    > ⚠️ [Proje 4, Ders 1'deki eğitim ve tahmin kaynakları oluşturma talimatlarına](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource) gerekirse başvurabilirsiniz.

1. [CustomVision.ai](https://customvision.ai) adresindeki Custom Vision portalını açın ve Azure hesabınızda kullandığınız Microsoft hesabıyla oturum açın.

1. Microsoft belgelerindeki [Bir nesne dedektörü oluşturma hızlı başlangıç bölümündeki Yeni bir Proje Oluşturma](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) talimatlarını takip ederek yeni bir Custom Vision projesi oluşturun. Kullanıcı arayüzü değişebilir ve bu belgeler her zaman en güncel referanstır.

    Projenize `stock-detector` adını verin.

    Projenizi oluştururken, daha önce oluşturduğunuz `stock-detector-training` kaynağını kullandığınızdan emin olun. *Nesne Tespiti* proje türünü ve *Raflardaki Ürünler* alanını seçin.

    ![Custom Vision projesi ayarları](../../../../../translated_images/tr/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Raflardaki ürünler alanı, mağaza raflarındaki stokları tespit etmek için özel olarak tasarlanmıştır. Microsoft belgelerindeki [Bir alan seçme dokümantasyonu](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection) bölümünde farklı alanlar hakkında daha fazla bilgi edinin.

✅ Nesne dedektörünüz için Custom Vision kullanıcı arayüzünü keşfetmek için biraz zaman ayırın.

### Görev - Nesne Dedektörünüzü Eğitin

Modelinizi eğitmek için tespit etmek istediğiniz nesneleri içeren bir dizi görüntüye ihtiyacınız olacak.

1. Tespit edilecek nesneyi içeren görüntüler toplayın. Her nesneyi tespit etmek için en az 15 görüntüye ihtiyacınız olacak, farklı açılardan ve farklı ışık koşullarında çekilmiş, ancak ne kadar çok olursa o kadar iyi. Bu nesne dedektörü *Raflardaki Ürünler* alanını kullanır, bu yüzden nesneleri bir mağaza rafındaymış gibi düzenlemeye çalışın. Ayrıca modeli test etmek için birkaç görüntüye ihtiyacınız olacak. Birden fazla nesneyi tespit ediyorsanız, tüm nesneleri içeren bazı test görüntülerine ihtiyacınız olacak.

    > 💁 Farklı nesneleri içeren görüntüler, görüntüdeki tüm nesneler için 15 görüntü minimumuna katkıda bulunur.

    Görüntüleriniz png veya jpeg formatında olmalı, 6MB'den küçük olmalıdır. Örneğin bir iPhone ile oluşturulmuşlarsa, yüksek çözünürlüklü HEIC görüntüler olabilir, bu yüzden dönüştürülmeleri ve muhtemelen küçültülmeleri gerekebilir. Ne kadar çok görüntü olursa o kadar iyi ve olgun ve olgunlaşmamış nesneler için benzer sayıda görüntüye sahip olmalısınız.

    Model, raflardaki ürünler için tasarlanmıştır, bu yüzden nesnelerin fotoğraflarını raflarda çekmeye çalışın.

    Kaju fıstığı ve domates salçası içeren bazı örnek görüntüleri [images](../../../../../5-retail/lessons/1-train-stock-detector/images) klasöründe bulabilirsiniz.

1. Microsoft belgelerindeki [Bir nesne dedektörü oluşturma hızlı başlangıç bölümündeki Görüntüleri Yükleme ve Etiketleme](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) talimatlarını takip ederek eğitim görüntülerinizi yükleyin. Tespit etmek istediğiniz nesne türlerine bağlı olarak ilgili etiketler oluşturun.

    ![Olgun ve olgunlaşmamış muz resimlerinin yükleme diyalogları](../../../../../translated_images/tr/image-upload-object-detector.77c7892c3093cb59.webp)

    Nesneler için sınırlayıcı kutular çizerken, kutuları nesnenin etrafında sıkı tutun. Tüm görüntüleri çevrelemek biraz zaman alabilir, ancak araç, sınırlayıcı kutuların ne olduğunu düşündüğünü tespit eder, bu da işlemi hızlandırır.

    ![Domates salçasını etiketleme](../../../../../translated_images/tr/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Her nesne için 15'ten fazla görüntünüz varsa, önce 15 görüntüyle eğitip ardından **Önerilen Etiketler** özelliğini kullanabilirsiniz. Bu, eğitilmiş modeli kullanarak etiketlenmemiş görüntülerdeki nesneleri tespit eder. Algılanan nesneleri onaylayabilir veya reddedip sınırlayıcı kutuları yeniden çizebilirsiniz. Bu, *çok* zaman kazandırabilir.

1. Microsoft belgelerindeki [Bir nesne dedektörü oluşturma hızlı başlangıç bölümündeki Dedektörü Eğitme](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) talimatlarını takip ederek etiketlenmiş görüntülerinizde nesne dedektörünü eğitin.

    Size bir eğitim türü seçeneği sunulacaktır. **Hızlı Eğitim** seçeneğini seçin.

Nesne dedektörü eğitilecektir. Eğitimin tamamlanması birkaç dakika sürecektir.

## Nesne Dedektörünüzü Test Edin

Nesne dedektörünüz eğitildikten sonra, yeni görüntüler vererek nesneleri tespit edip edemediğini test edebilirsiniz.

### Görev - Nesne Dedektörünüzü Test Edin

1. **Hızlı Test** düğmesini kullanarak test görüntülerinizi yükleyin ve nesnelerin tespit edilip edilmediğini doğrulayın. Daha önce oluşturduğunuz test görüntülerini kullanın, eğitim için kullandığınız görüntüleri değil.

    ![3 domates salçası kutusu %38, %35.5 ve %34.6 olasılıklarla tespit edildi](../../../../../translated_images/tr/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Erişiminiz olan tüm test görüntülerini deneyin ve olasılıkları gözlemleyin.

## Nesne Dedektörünüzü Yeniden Eğitin

Nesne dedektörünüzü test ettiğinizde, beklediğiniz sonuçları vermeyebilir, tıpkı önceki projedeki görüntü sınıflandırıcılar gibi. Nesne dedektörünüzü yanlış sonuçlar verdiği görüntülerle yeniden eğiterek geliştirebilirsiniz.

Hızlı test seçeneğini kullanarak her tahmin yaptığınızda, görüntü ve sonuçlar saklanır. Bu görüntüleri modelinizi yeniden eğitmek için kullanabilirsiniz.

1. **Tahminler** sekmesini kullanarak test için kullandığınız görüntüleri bulun.

1. Doğru tespitleri onaylayın, yanlış olanları silin ve eksik nesneleri ekleyin.

1. Modeli yeniden eğitin ve yeniden test edin.

---

## 🚀 Zorluk

Domates salçası ve doğranmış domates gibi benzer görünümlü ürünlerle nesne dedektörünü kullansaydınız ne olurdu?

Benzer görünümlü ürünleriniz varsa, nesne dedektörünüze bunların görüntülerini ekleyerek test edin.

## Ders Sonrası Test
[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Gözden Geçirme ve Kendi Kendine Çalışma

* Nesne algılayıcınızı eğittiğinizde, oluşturulan modeli değerlendiren *Precision*, *Recall* ve *mAP* değerlerini görmüş olmalısınız. Bu değerlerin ne olduğunu öğrenmek için [Microsoft dokümanlarındaki Nesne algılayıcıyı değerlendirme bölümünü](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector) okuyun.
* Nesne algılama hakkında daha fazla bilgi edinmek için [Wikipedia'daki Nesne algılama sayfasını](https://wikipedia.org/wiki/Object_detection) okuyun.

## Ödev

[Alanları karşılaştır](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.