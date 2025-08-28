<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T02:59:45+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "tr"
}
-->
# Zamanlayıcı Ayarla - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, konuşmayı anlamak için sunucusuz kodunuzu çağıracak ve sonuçlara göre sanal IoT cihazınızda veya Raspberry Pi'de bir zamanlayıcı ayarlayacaksınız.

## Zamanlayıcı Ayarla

Konuşmadan metne dönüşüm çağrısından gelen metin, LUIS tarafından işlenmesi için sunucusuz kodunuza gönderilmelidir ve zamanlayıcı için saniye sayısı geri alınmalıdır. Bu saniye sayısı, bir zamanlayıcı ayarlamak için kullanılabilir.

Zamanlayıcılar, Python `threading.Timer` sınıfı kullanılarak ayarlanabilir. Bu sınıf, bir gecikme süresi ve bir işlev alır ve gecikme süresi sona erdiğinde işlev çalıştırılır.

### Görev - metni sunucusuz işleve gönderin

1. VS Code'da `smart-timer` projesini açın ve sanal IoT cihazı kullanıyorsanız terminalde sanal ortamın yüklü olduğundan emin olun.

1. `process_text` işlevinin üstünde, oluşturduğunuz REST uç noktasını çağırmak için `get_timer_time` adlı bir işlev tanımlayın:

    ```python
    def get_timer_time(text):
    ```

1. Bu işlevin içine aşağıdaki kodu ekleyerek çağrılacak URL'yi tanımlayın:

    ```python
    url = '<URL>'
    ```

    `<URL>` kısmını, önceki derste oluşturduğunuz REST uç noktasının URL'siyle değiştirin; bu URL bilgisayarınızda veya bulutta olabilir.

1. Çağrıya JSON olarak iletilen bir özellik olarak metni ayarlamak için aşağıdaki kodu ekleyin:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Bunun altına, yanıt yükünden `seconds` değerini alın ve çağrı başarısız olursa 0 döndürün:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Başarılı HTTP çağrıları 200 aralığında bir durum kodu döndürür ve sunucusuz kodunuz, metin işlenip zamanlayıcı niyeti olarak tanındığında 200 döndürür.

### Görev - arka plan iş parçacığında bir zamanlayıcı ayarlayın

1. Dosyanın üst kısmına aşağıdaki import ifadesini ekleyerek threading Python kütüphanesini içe aktarın:

    ```python
    import threading
    ```

1. `process_text` işlevinin üstünde bir yanıtı seslendirmek için bir işlev ekleyin. Şimdilik bu işlev sadece konsola yazacak, ancak bu derste daha sonra metni seslendirecek.

    ```python
    def say(text):
        print(text)
    ```

1. Bunun altına, zamanlayıcının tamamlandığını duyurmak için bir zamanlayıcı tarafından çağrılacak bir işlev ekleyin:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Bu işlev, zamanlayıcı için dakika ve saniye sayısını alır ve zamanlayıcının tamamlandığını belirten bir cümle oluşturur. Dakika ve saniye sayısını kontrol eder ve yalnızca bir zaman birimi varsa mesajda yer alır. Örneğin, dakika sayısı 0 ise yalnızca saniyeler mesajda yer alır. Bu cümle daha sonra `say` işlevine gönderilir.

1. Bunun altına, bir zamanlayıcı oluşturmak için aşağıdaki `create_timer` işlevini ekleyin:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Bu işlev, komutta gönderilecek zamanlayıcı için toplam saniye sayısını alır ve bunu dakikalar ve saniyelere dönüştürür. Daha sonra toplam saniye sayısını kullanarak bir zamanlayıcı nesnesi oluşturur ve başlatır, `announce_timer` işlevini ve dakikalar ile saniyeleri içeren bir listeyi geçirir. Zamanlayıcı sona erdiğinde, `announce_timer` işlevini çağırır ve bu listenin içeriğini parametre olarak geçirir - listenin ilk öğesi `minutes` parametresi olarak, ikinci öğesi ise `seconds` parametresi olarak iletilir.

1. `create_timer` işlevinin sonuna, zamanlayıcının başladığını duyurmak için kullanıcıya seslendirilmesi gereken bir mesaj oluşturmak için kod ekleyin:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Yine, yalnızca bir zaman birimi varsa mesajda yer alır. Bu cümle daha sonra `say` işlevine gönderilir.

1. `process_text` işlevinin sonuna, metinden zamanlayıcı için süreyi almak ve ardından zamanlayıcı oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Zamanlayıcı yalnızca saniye sayısı 0'dan büyükse oluşturulur.

1. Uygulamayı çalıştırın ve işlev uygulamasının da çalıştığından emin olun. Bazı zamanlayıcılar ayarlayın ve çıktı, zamanlayıcının ayarlandığını ve ardından sona erdiğini gösterecektir:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Bu kodu [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) veya [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Orijinal belgenin kendi dilindeki hali, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.