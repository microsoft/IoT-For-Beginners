<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T02:45:30+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "tr"
}
-->
# IoT Edge çalıştıran bir sanal makine oluşturma

Azure'da, bulutta bir bilgisayar olan ve istediğiniz şekilde yapılandırabileceğiniz, kendi yazılımınızı çalıştırabileceğiniz bir sanal makine oluşturabilirsiniz.

> 💁 Sanal makineler hakkında daha fazla bilgiyi [Wikipedia'daki Sanal Makine sayfasında](https://wikipedia.org/wiki/Virtual_machine) bulabilirsiniz.

## Görev - IoT Edge sanal makinesi kurma

1. Azure IoT Edge'in önceden yüklü olduğu bir sanal makine oluşturmak için aşağıdaki komutu çalıştırın:

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

    `<vm_name>` yerine bu sanal makine için bir ad yazın. Bu adın küresel olarak benzersiz olması gerektiğinden, adın sonuna kendi adınızı veya başka bir değer ekleyerek `fruit-quality-detector-vm-` gibi bir şey kullanabilirsiniz.

    `<username>` ve `<password>` yerine sanal makineye giriş yapmak için kullanacağınız bir kullanıcı adı ve şifre yazın. Bu bilgilerin nispeten güvenli olması gerektiğinden, admin/password gibi basit kombinasyonlar kullanamazsınız.

    `<connection_string>` yerine `fruit-quality-detector-edge` IoT Edge cihazınızın bağlantı dizesini yazın.

    Bu komut, `DS1 v2` kategorisinde bir sanal makine oluşturacaktır. Bu kategoriler, makinenin ne kadar güçlü olduğunu ve dolayısıyla ne kadar maliyetli olduğunu belirtir. Bu sanal makine 1 CPU ve 3.5GB RAM'e sahiptir.

    > 💰 Bu sanal makinelerin güncel fiyatlarını [Azure Sanal Makine fiyat rehberinde](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) görebilirsiniz.

    Sanal makine oluşturulduktan sonra, IoT Edge runtime otomatik olarak yüklenecek ve `fruit-quality-detector-edge` cihazınız olarak IoT Hub'a bağlanacak şekilde yapılandırılacaktır.

1. Görüntü sınıflandırıcısını bu sanal makineden çağırmak için IP adresine veya DNS adına ihtiyacınız olacak. Bunu öğrenmek için aşağıdaki komutu çalıştırın:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` veya `Fqdns` alanındaki değeri kopyalayın.

1. Sanal makineler maliyetlidir. Bu yazının yazıldığı sırada, bir DS1 sanal makinesi saatte yaklaşık 0,06 $ maliyetlidir. Maliyetleri düşürmek için sanal makineyi kullanmadığınız zaman kapatmalı ve bu projeyi tamamladıktan sonra silmelisiniz.

    Sanal makinenizi her gün belirli bir saatte otomatik olarak kapanacak şekilde yapılandırabilirsiniz. Bu, kapatmayı unutursanız, otomatik kapanma zamanına kadar olan süre dışında faturalandırılmamanızı sağlar. Bunu ayarlamak için aşağıdaki komutu kullanın:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>` yerine sanal makinenizin adını yazın.

    `<shutdown_time_utc>` yerine sanal makinenin UTC saatine göre kapanmasını istediğiniz zamanı 4 haneli HHMM formatında yazın. Örneğin, UTC'de gece yarısı kapanmasını istiyorsanız, `0000` olarak ayarlayın. ABD'nin batı kıyısında saat 7:30PM için `0230` kullanabilirsiniz (ABD batı kıyısında 7:30PM, UTC'de 2:30AM'dir).

1. Görüntü sınıflandırıcınız bu edge cihazında çalışacak ve port 80'de (standart HTTP portu) dinleyecektir. Varsayılan olarak, sanal makinelerde gelen bağlantı portları engellenmiştir, bu yüzden port 80'i etkinleştirmeniz gerekecek. Portlar, ağ güvenlik gruplarında etkinleştirilir, bu yüzden önce sanal makinenizin ağ güvenlik grubunun adını bilmeniz gerekir. Bunu öğrenmek için aşağıdaki komutu çalıştırın:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` alanındaki değeri kopyalayın.

1. Port 80'i ağ güvenlik grubuna açmak için aşağıdaki komutu çalıştırın:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>` yerine önceki adımda aldığınız ağ güvenlik grubu adını yazın.

### Görev - Maliyetleri azaltmak için sanal makinenizi yönetin

1. Sanal makinenizi kullanmadığınızda kapatmalısınız. Sanal makineyi kapatmak için aşağıdaki komutu kullanın:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>` yerine sanal makinenizin adını yazın.

    > 💁 `az vm stop` adında bir komut vardır, ancak bu komut sanal makineyi durdurur ancak bilgisayarı size tahsis edilmiş halde tutar, bu yüzden hala çalışıyormuş gibi ödeme yaparsınız.

1. Sanal makineyi yeniden başlatmak için aşağıdaki komutu kullanın:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>` yerine sanal makinenizin adını yazın.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.