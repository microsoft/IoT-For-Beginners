<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-24T22:52:28+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "tw"
}
-->
# 保護您的植物安全

![本課程的手繪筆記概述](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.tw.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## 簡介

在前幾節課中，您已經創建了一個土壤監測物聯網設備並將其連接到雲端。但如果競爭農場的黑客成功控制了您的物聯網設備會怎樣？如果他們發送高土壤濕度讀數，導致您的植物永遠得不到澆水，或者讓您的灌溉系統一直運行，過度澆水殺死植物並讓您在水費上損失一大筆錢呢？

在本課程中，您將學習如何保護物聯網設備的安全。作為本項目的最後一課，您還將學習如何清理雲端資源，以減少潛在的成本。

本課程將涵蓋以下內容：

* [為什麼需要保護物聯網設備的安全？](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [加密技術](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [保護您的物聯網設備](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [生成並使用 X.509 證書](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 這是本項目的最後一課，因此在完成本課程和作業後，請記得清理您的雲端服務。您需要這些服務來完成作業，因此請確保先完成作業。
>
> 如有需要，請參考[清理項目指南](../../../clean-up.md)以獲取相關指導。

## 為什麼需要保護物聯網設備的安全？

物聯網安全涉及確保只有預期的設備能夠連接到您的雲端物聯網服務並發送遙測數據，並且只有您的雲端服務能夠向您的設備發送指令。物聯網數據可能包含個人信息，例如醫療或隱私數據，因此整個應用程序需要考慮安全性以防止數據洩漏。

如果您的物聯網應用程序不安全，可能會面臨以下風險：

* 假冒設備可能發送錯誤數據，導致您的應用程序做出錯誤反應。例如，它們可能發送持續的高土壤濕度讀數，導致您的灌溉系統永遠不啟動，植物因缺水而死亡。
* 未授權的用戶可能會讀取物聯網設備的數據，包括個人或商業關鍵數據。
* 黑客可能會發送指令以控制設備，可能對設備或連接的硬件造成損害。
* 通過連接到物聯網設備，黑客可能利用此途徑訪問其他網絡，進而進入私人系統。
* 惡意用戶可能訪問個人數據並利用這些數據進行勒索。

這些是真實世界中的情景，並且經常發生。之前的課程中已經提到了一些例子，以下是更多案例：

* 2018 年，黑客利用魚缸溫控器上的開放 WiFi 接入點進入一家賭場的網絡並竊取數據。[The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* 2016 年，Mirai Botnet 發動了一次針對 Dyn（互聯網服務提供商）的拒絕服務攻擊，導致大部分互聯網癱瘓。該僵屍網絡使用惡意軟件連接到使用默認用戶名和密碼的物聯網設備（如 DVR 和攝像頭），並從那裡發動攻擊。[The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys 的 CloudPets 連接玩具用戶數據庫在互聯網上公開。[Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/)
* Strava 標記了您跑步時經過的跑者並顯示他們的路線，讓陌生人能夠有效地看到您的住址。[Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/)

✅ 做一些研究：搜索更多物聯網攻擊和數據洩漏的例子，尤其是與個人物品（如互聯網連接牙刷或體重秤）相關的案例。思考這些攻擊可能對受害者或客戶造成的影響。

> 💁 安全性是一個非常廣泛的主題，本課程僅涉及一些基本內容，例如設備與雲端的連接。未涵蓋的主題包括監控數據在傳輸過程中的變化、直接攻擊設備或更改設備配置。物聯網攻擊威脅如此之大，像 [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) 這樣的工具已被開發出來。這些工具類似於您電腦上的防病毒和安全工具，但專為小型、低功耗的物聯網設備設計。

## 加密技術

當設備連接到物聯網服務時，它使用一個 ID 來識別自己。問題是這個 ID 可以被克隆——黑客可以設置一個惡意設備，使用與真實設備相同的 ID，但發送虛假數據。

![有效設備和惡意設備可能使用相同的 ID 發送遙測數據](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.tw.png)

解決方法是將發送的數據轉換為一種加密格式，使用設備和雲端都知道的某種值來加密數據。這個過程稱為*加密*，用於加密數據的值稱為*加密密鑰*。

![如果使用加密，則只有加密的消息會被接受，其他消息會被拒絕](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.tw.png)

雲端服務可以使用一個稱為*解密*的過程將數據轉換回可讀格式，使用相同的加密密鑰或一個*解密密鑰*。如果加密的消息無法通過密鑰解密，則表明設備已被攻擊，消息會被拒絕。

進行加密和解密的技術稱為*密碼學*。

### 早期的密碼學

最早的密碼學類型是替換密碼，最早可追溯到 3,500 年前。替換密碼涉及用一個字母替換另一個字母。例如，[凱撒密碼](https://wikipedia.org/wiki/Caesar_cipher) 通過定義的數量移動字母表，只有加密消息的發送者和預期接收者知道要移動多少個字母。

[維吉尼亞密碼](https://wikipedia.org/wiki/Vigenère_cipher) 更進一步，使用單詞來加密文本，使原始文本中的每個字母移動不同的數量，而不是始終移動相同的字母數。

密碼學被廣泛用於各種目的，例如在古代美索不達米亞保護陶工的釉料配方、在印度寫秘密情書或在古埃及保密魔法咒語。

### 現代密碼學

現代密碼學更加先進，比早期方法更難破解。現代密碼學使用複雜的數學方法來加密數據，擁有太多可能的密鑰使暴力破解攻擊變得不可能。

密碼學在安全通信中有很多用途。如果您正在 GitHub 上閱讀此頁面，您可能會注意到網站地址以 *HTTPS* 開頭，這意味著您的瀏覽器與 GitHub 的網絡服務器之間的通信是加密的。如果有人能夠讀取您的瀏覽器與 GitHub 之間流動的互聯網流量，他們將無法讀取數據，因為數據是加密的。您的電腦甚至可能加密硬盤上的所有數據，因此如果有人偷走它，沒有您的密碼他們將無法讀取任何數據。

> 🎓 HTTPS 代表超文本傳輸協議 **安全**

不幸的是，並非所有事物都是安全的。有些設備沒有安全性，有些設備使用容易破解的密鑰，有些甚至所有同類型的設備都使用相同的密鑰。有報導稱一些非常私密的物聯網設備都使用相同的密碼來通過 WiFi 或藍牙連接。如果您可以連接到自己的設備，您也可以連接到其他人的設備。一旦連接，您可能訪問一些非常私密的數據，或者控制他們的設備。

> 💁 儘管現代密碼學的複雜性以及破解加密可能需要數十億年的說法，量子計算的興起使得在非常短的時間內破解所有已知加密成為可能！

### 對稱密鑰和非對稱密鑰

加密有兩種類型——對稱和非對稱。

**對稱**加密使用相同的密鑰來加密和解密數據。發送者和接收者都需要知道相同的密鑰。這是最不安全的類型，因為密鑰需要以某種方式共享。發送者要向接收者發送加密消息，可能首先需要向接收者發送密鑰。

![對稱密鑰加密使用相同的密鑰加密和解密消息](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ff.tw.png)

如果密鑰在傳輸過程中被竊取，或者發送者或接收者被黑客攻擊並找到密鑰，加密就可能被破解。

![對稱密鑰加密只有在黑客未獲得密鑰的情況下才安全——如果密鑰被竊取，他們可以攔截並解密消息](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb.tw.png)

**非對稱**加密使用兩個密鑰——加密密鑰和解密密鑰，稱為公鑰/私鑰對。公鑰用於加密消息，但不能用於解密；私鑰用於解密消息，但不能用於加密。

![非對稱加密使用不同的密鑰加密和解密。加密密鑰發送給任何消息發送者，以便他們在向擁有密鑰的接收者發送消息之前加密消息](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c.tw.png)

接收者共享其公鑰，發送者使用此密鑰加密消息。一旦消息被發送，接收者使用其私鑰解密消息。非對稱加密更安全，因為私鑰由接收者保密，永不共享。任何人都可以擁有公鑰，因為它只能用於加密消息。

對稱加密比非對稱加密更快，非對稱加密更安全。一些系統會同時使用兩者——使用非對稱加密來加密並共享對稱密鑰，然後使用對稱密鑰加密所有數據。這使得在發送者和接收者之間共享對稱密鑰更安全，並且在加密和解密數據時更快。

## 保護您的物聯網設備

物聯網設備可以使用對稱或非對稱加密進行保護。對稱加密更簡單，但安全性較低。

### 對稱密鑰

當您設置物聯網設備與 IoT Hub 交互時，您使用了一個連接字符串。一個示例連接字符串如下：

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

此連接字符串由三部分組成，使用分號分隔，每部分包含一個鍵和值：

| 鍵 | 值 | 描述 |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | IoT Hub 的 URL |
| DeviceId | `soil-moisture-sensor` | 設備的唯一 ID |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | 設備和 IoT Hub 都知道的對稱密鑰 |

此連接字符串的最後一部分 `SharedAccessKey` 是設備和 IoT Hub 都知道的對稱密鑰。此密鑰不會從設備發送到雲端，也不會從雲端發送到設備。它僅用於加密發送或接收的數據。

✅ 做一個實驗：如果您在連接物聯網設備時更改連接字符串中的 `SharedAccessKey` 部分，您認為會發生什麼？試試看。

當設備首次嘗試連接時，它會發送一個共享訪問簽名（SAS）令牌，其中包括 IoT Hub 的 URL、一個訪問簽名到期的時間戳（通常是當前時間的一天後）以及一個簽名。此簽名由 URL 和到期時間組成，並使用連接字符串中的共享訪問密鑰加密。

IoT Hub 使用共享訪問密鑰解密此簽名，如果解密後的值與 URL 和到期時間匹配，則允許設備連接。它還會驗證當前時間是否早於到期時間，以防止惡意設備捕獲真實設備的 SAS 令牌並使用它。

這是一種優雅的方式來驗證發送者是否是正確的設備。通過以解密和加密形式發送一些已知數據，服務器可以通過解密加密數據並確保結果與發送的解密版本匹配來驗證設備。如果匹配，則表明發送者和接收者擁有相同的對稱加密密鑰。
💁 由於到期時間的限制，您的 IoT 設備需要知道準確的時間，通常是從 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 伺服器讀取。如果時間不準確，連線將會失敗。
在連接後，所有從設備發送到 IoT Hub 或從 IoT Hub 發送到設備的數據都將使用共享訪問密鑰進行加密。

✅ 如果多個設備共享相同的連接字串，您認為會發生什麼？

> 💁 將此密鑰存儲在程式碼中是一種不良的安全做法。如果駭客獲得您的原始碼，他們就能獲得您的密鑰。此外，在發布程式碼時也會更加困難，因為您需要為每個設備使用更新的密鑰重新編譯。更好的方法是從硬體安全模組（HSM）加載此密鑰——這是一種存儲加密值的 IoT 設備芯片，您的程式碼可以讀取這些值。
>
> 在學習 IoT 時，通常將密鑰放入程式碼中會更容易，就像您在之前的課程中所做的那樣，但您必須確保此密鑰未被提交到公共原始碼控制中。

設備有兩個密鑰以及兩個對應的連接字串。這使您可以輪換密鑰——即在第一個密鑰被洩露時切換到另一個密鑰，並重新生成第一個密鑰。

### X.509 證書

當您使用公鑰/私鑰對進行非對稱加密時，您需要向任何想要向您發送數據的人提供您的公鑰。問題是，接收者如何確定這確實是您的公鑰，而不是其他人冒充您？與其直接提供密鑰，您可以將公鑰放入由可信第三方驗證的證書中，這種證書稱為 X.509 證書。

X.509 證書是包含公鑰部分的數字文件。它們通常由一系列被信任的組織（稱為[證書授權機構](https://wikipedia.org/wiki/Certificate_authority) (CAs)）簽發，並由 CA 進行數字簽名以表明密鑰是有效的並且來自您。您信任證書以及公鑰的來源，因為您信任 CA，就像您信任護照或駕照是由可信的國家簽發的一樣。證書需要付費，因此您也可以“自簽”，即自己創建並簽署證書，用於測試目的。

> 💁 切勿在正式發布中使用自簽證書。

這些證書包含多個字段，包括公鑰的來源、簽發證書的 CA 的詳細信息、證書的有效期以及公鑰本身。在使用證書之前，最好通過檢查其是否由原始 CA 簽署來驗證它。

✅ 您可以在 [Microsoft 的 X.509 公鑰證書教程](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields) 中閱讀證書字段的完整列表。

使用 X.509 證書時，發送者和接收者都會擁有自己的公鑰和私鑰，以及包含公鑰的 X.509 證書。他們會以某種方式交換 X.509 證書，使用彼此的公鑰加密發送的數據，並使用自己的私鑰解密接收到的數據。

![與其共享公鑰，您可以共享證書。證書的使用者可以通過檢查簽署證書的授權機構來驗證它是否來自您。](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76e.tw.png)

使用 X.509 證書的一大優勢是它們可以在設備之間共享。您可以創建一個證書，將其上傳到 IoT Hub，並用於所有設備。每個設備只需要知道私鑰即可解密從 IoT Hub 接收到的消息。

設備用於加密發送到 IoT Hub 的消息的證書由 Microsoft 發布。這是許多 Azure 服務使用的相同證書，有時已內置於 SDK 中。

> 💁 請記住，公鑰就是公鑰——公開的。Azure 公鑰只能用於加密發送到 Azure 的數據，不能用於解密，因此可以隨處共享，包括在原始碼中。例如，您可以在 [Azure IoT C SDK 原始碼](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c) 中看到它。

✅ X.509 證書涉及許多術語。您可以在 [X.509 證書術語的簡明指南](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn) 中閱讀一些可能遇到的術語的定義。

## 生成並使用 X.509 證書

生成 X.509 證書的步驟如下：

1. 創建公鑰/私鑰對。最廣泛使用的生成公鑰/私鑰對的算法之一是 [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA)。

1. 提交公鑰及相關數據進行簽名，可以由 CA 簽名，也可以自簽。

Azure CLI 提供了命令來在 IoT Hub 中創建新的設備身份，並自動生成公鑰/私鑰對以及自簽證書。

> 💁 如果您希望詳細了解步驟，而不是使用 Azure CLI，您可以在 [Microsoft IoT Hub 文檔中的使用 OpenSSL 創建自簽證書教程](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn) 中找到。

### 任務 - 使用 X.509 證書創建設備身份

1. 運行以下命令以註冊新的設備身份，並自動生成密鑰和證書：

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為您用於 IoT Hub 的名稱。

    這將創建一個 ID 為 `soil-moisture-sensor-x509` 的設備，以區分您在上一課中創建的設備身份。此命令還會在當前目錄中創建兩個文件：

    * `soil-moisture-sensor-x509-key.pem` - 此文件包含設備的私鑰。
    * `soil-moisture-sensor-x509-cert.pem` - 此文件是設備的 X.509 證書。

    請妥善保管這些文件！私鑰文件不應提交到公共原始碼控制中。

### 任務 - 在設備程式碼中使用 X.509 證書

按照相關指南，使用 X.509 證書將您的 IoT 設備連接到雲端：

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [單板電腦 - Raspberry Pi/虛擬 IoT 設備](single-board-computer-x509.md)

---

## 🚀 挑戰

創建、管理和刪除 Azure 服務（如資源群組和 IoT Hub）有多種方法。一種方法是 [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn)——一個基於網頁的界面，提供 GUI 來管理您的 Azure 服務。

前往 [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) 並探索該入口。嘗試使用該入口創建一個 IoT Hub，然後刪除它。

**提示** - 通過入口創建服務時，您不需要提前創建資源群組，可以在創建服務時創建資源群組。完成後請確保刪除它！

您可以在 [Azure Portal 文檔](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn) 中找到大量文檔、教程和指南。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## 回顧與自學

* 在 [Wikipedia 的密碼學歷史頁面](https://wikipedia.org/wiki/History_of_cryptography) 上閱讀密碼學的歷史。
* 在 [Wikipedia 的 X.509 頁面](https://wikipedia.org/wiki/X.509) 上閱讀 X.509 證書的相關內容。

## 作業

[構建一個新的 IoT 設備](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。