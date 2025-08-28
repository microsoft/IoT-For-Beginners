<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T02:34:59+00:00",
  "source_file": "clean-up.md",
  "language_code": "tr"
}
-->
# Projenizi Temizleyin

Her projeyi tamamladıktan sonra, bulut kaynaklarınızı silmek iyi bir fikirdir.

Her proje için derslerde aşağıdakilerden bazılarını oluşturmuş olabilirsiniz:

* Bir Kaynak Grubu
* Bir IoT Hub
* IoT cihaz kayıtları
* Bir Depolama Hesabı
* Bir Functions Uygulaması
* Bir Azure Maps hesabı
* Bir özel görsel projesi
* Bir Azure Container Registry
* Bir bilişsel hizmetler kaynağı

Bu kaynakların çoğu maliyetsizdir - ya tamamen ücretsizdirler ya da ücretsiz bir katman kullanıyorsunuzdur. Ücretli bir katman gerektiren hizmetler için, ücretsiz kullanım hakkına dahil olan bir seviyede kullanıyor olmalısınız ya da yalnızca birkaç kuruş maliyeti olacaktır.

Göreceli olarak düşük maliyetlere rağmen, işiniz bittiğinde bu kaynakları silmek faydalıdır. Örneğin, yalnızca bir IoT Hub'ı ücretsiz katman kullanarak oluşturabilirsiniz, bu yüzden başka bir tane oluşturmak isterseniz ücretli bir katman kullanmanız gerekecektir.

Tüm hizmetleriniz Kaynak Grupları içinde oluşturuldu, bu da yönetimi kolaylaştırır. Kaynak Grubunu silebilirsiniz ve o Kaynak Grubundaki tüm hizmetler onunla birlikte silinir.

Kaynak Grubunu silmek için terminalinizde veya komut isteminde aşağıdaki komutu çalıştırın:

```sh
az group delete --name <resource-group-name>
```

`<resource-group-name>` kısmını ilgilendiğiniz Kaynak Grubunun adıyla değiştirin.

Bir onay ekranı görünecektir:

```output
Are you sure you want to perform this operation? (y/n): 
```

Kaynak Grubunu silmek için `y` yazın ve onaylayın.

Tüm hizmetlerin silinmesi biraz zaman alacaktır.

> 💁 Kaynak gruplarını silme hakkında daha fazla bilgiyi [Microsoft Docs'taki Azure Resource Manager kaynak grubu ve kaynak silme dokümantasyonunda](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli) okuyabilirsiniz.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.