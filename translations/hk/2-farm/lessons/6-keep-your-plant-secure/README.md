<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-26T14:52:25+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "hk"
}
-->
# 保護你的植物安全

![本課程的手繪筆記概述](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.hk.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大的版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## 簡介

在過去幾節課中，你已經創建了一個土壤監測物聯網設備並將其連接到雲端。但如果競爭農民的黑客成功控制了你的物聯網設備會怎樣？如果他們發送高土壤濕度讀數，導致你的植物永遠得不到澆水，或者讓你的灌溉系統一直運行，導致植物因過度澆水而死亡，並讓你在水費上損失一大筆錢？

在本課程中，你將學習如何保護物聯網設備的安全。作為本項目的最後一課，你還將學習如何清理雲端資源，以減少潛在的成本。

本課程將涵蓋以下內容：

* [為什麼需要保護物聯網設備的安全？](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [加密技術](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [保護你的物聯網設備](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [生成並使用 X.509 證書](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 這是本項目的最後一課，因此在完成本課程和作業後，別忘了清理你的雲端服務。你需要這些服務來完成作業，因此請確保先完成作業。
>
> 如果需要，請參考[清理項目指南](../../../clean-up.md)以獲取相關指導。

## 為什麼需要保護物聯網設備的安全？

物聯網安全涉及確保只有預期的設備能夠連接到你的雲端物聯網服務並發送遙測數據，並且只有你的雲端服務能夠向你的設備發送指令。物聯網數據可能包含個人信息，包括醫療或隱私數據，因此整個應用程序需要考慮安全性，以防止這些數據洩漏。

如果你的物聯網應用程序不安全，可能會面臨以下風險：

* 假冒設備可能發送錯誤數據，導致你的應用程序做出錯誤反應。例如，它們可能發送持續的高土壤濕度讀數，導致你的灌溉系統永遠不啟動，植物因缺水而死亡。
* 未授權的用戶可能會讀取物聯網設備的數據，包括個人或商業關鍵數據。
* 黑客可能會發送指令以控制設備，可能會損壞設備或連接的硬件。
* 通過連接到物聯網設備，黑客可能利用此途徑訪問其他網絡，進而進入私人系統。
* 惡意用戶可能訪問個人數據並利用這些數據進行勒索。

這些是真實世界中的情景，並且經常發生。一些例子在之前的課程中已經提到，但以下是更多例子：

* 2018年，黑客利用魚缸溫控器上的開放WiFi接入點，成功侵入了一家賭場的網絡並竊取數據。[The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* 2016年，Mirai Botnet發起了一次針對Dyn（互聯網服務提供商）的拒絕服務攻擊，導致大部分互聯網癱瘓。該Botnet使用惡意軟件連接到使用默認用戶名和密碼的物聯網設備（如DVR和攝像頭），並從那裡發起攻擊。[The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys的CloudPets連接玩具用戶數據庫在互聯網上公開可用。[Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava標記了你跑過的跑者並顯示了他們的路線，讓陌生人能有效地看到你住在哪裡。[Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ 做一些研究：搜索更多物聯網攻擊和數據洩漏的例子，特別是與個人物品（如互聯網連接的牙刷或體重秤）相關的案例。思考這些攻擊可能對受害者或客戶造成的影響。

> 💁 安全是一個非常大的話題，本課程只會涉及一些基本內容，例如如何將設備連接到雲端。其他未涵蓋的主題包括監控數據在傳輸中的變化、直接攻擊設備或更改設備配置。物聯網攻擊是一個如此大的威脅，以至於像 [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) 這樣的工具已被開發出來。這些工具類似於你電腦上的防病毒和安全工具，但專為小型、低功耗的物聯網設備設計。

## 加密技術

當設備連接到物聯網服務時，它會使用一個ID來識別自己。問題是這個ID可能會被克隆——黑客可以設置一個惡意設備，使用與真實設備相同的ID，但發送虛假數據。

![有效設備和惡意設備可能使用相同的ID發送遙測數據](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.hk.png)

解決方法是將發送的數據轉換為一種加密格式，使用設備和雲端都知道的一個值來加密數據。這個過程稱為*加密*，用於加密數據的值稱為*加密密鑰*。

![如果使用加密，則只有加密的消息會被接受，其他消息會被拒絕](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.hk.png)

雲端服務可以使用一個過程將數據轉換回可讀格式，這個過程稱為*解密*，使用相同的加密密鑰或一個*解密密鑰*。如果加密的消息無法通過密鑰解密，則表明設備已被攻擊，消息會被拒絕。

進行加密和解密的技術稱為*密碼學*。

### 早期的密碼學

最早的密碼學類型是替換密碼，最早可追溯到3500年前。替換密碼涉及用一個字母替換另一個字母。例如，[凱撒密碼](https://wikipedia.org/wiki/Caesar_cipher)涉及按定義的數量移動字母表，只有加密消息的發送者和預期接收者知道要移動多少個字母。

[維吉尼亞密碼](https://wikipedia.org/wiki/Vigenère_cipher)進一步發展，使用單詞來加密文本，使原始文本中的每個字母都按不同的數量移動，而不是始終按相同的字母數移動。

密碼學被用於廣泛的用途，例如在古代美索不達米亞保護陶工的釉料配方、在印度寫秘密情書或在古埃及保密魔法咒語。

### 現代密碼學

現代密碼學更加先進，比早期方法更難破解。現代密碼學使用複雜的數學方法來加密數據，擁有太多可能的密鑰使得暴力破解攻擊幾乎不可能。

密碼學在安全通信中有很多用途。如果你正在GitHub上閱讀此頁面，你可能會注意到網站地址以*HTTPS*開頭，這意味著你的瀏覽器和GitHub的網絡服務器之間的通信是加密的。如果有人能夠讀取你的瀏覽器和GitHub之間的互聯網流量，他們將無法讀取數據，因為數據是加密的。你的電腦甚至可能加密硬盤上的所有數據，因此如果有人偷走它，他們在沒有你的密碼的情況下無法讀取任何數據。

> 🎓 HTTPS代表超文本傳輸協議**安全**

不幸的是，並非所有事物都是安全的。有些設備沒有安全性，有些設備使用容易破解的密鑰，有些甚至所有同類型的設備都使用相同的密鑰。有報導稱一些非常個人的物聯網設備都使用相同的密碼來通過WiFi或藍牙連接。如果你能連接到自己的設備，你也能連接到別人的。一旦連接，你可能訪問一些非常私密的數據，或者控制他們的設備。

> 💁 儘管現代密碼學的複雜性以及破解加密可能需要數十億年的說法，量子計算的興起使得在非常短的時間內破解所有已知加密成為可能！

### 對稱密鑰和非對稱密鑰

加密有兩種類型——對稱和非對稱。

**對稱**加密使用相同的密鑰來加密和解密數據。發送者和接收者都需要知道相同的密鑰。這是最不安全的類型，因為密鑰需要以某種方式共享。為了讓發送者向接收者發送加密消息，發送者可能首先需要向接收者發送密鑰。

![對稱密鑰加密使用相同的密鑰加密和解密消息](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ff.hk.png)

如果密鑰在傳輸過程中被竊取，或者發送者或接收者被黑客攻擊並且密鑰被找到，加密就可能被破解。

![對稱密鑰加密只有在黑客未獲得密鑰的情況下才安全——如果密鑰被竊取，他們可以攔截並解密消息](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb.hk.png)

**非對稱**加密使用兩個密鑰——加密密鑰和解密密鑰，稱為公鑰/私鑰對。公鑰用於加密消息，但不能用於解密；私鑰用於解密消息，但不能用於加密。

![非對稱加密使用不同的密鑰加密和解密。加密密鑰會發送給任何消息發送者，以便他們在向擁有密鑰的接收者發送消息之前加密消息](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c.hk.png)

接收者分享他們的公鑰，發送者使用這個公鑰加密消息。一旦消息被發送，接收者使用他們的私鑰解密消息。非對稱加密更安全，因為私鑰由接收者保密，從不共享。任何人都可以擁有公鑰，因為它只能用於加密消息。

對稱加密比非對稱加密更快，非對稱加密更安全。一些系統會同時使用兩者——使用非對稱加密來加密和共享對稱密鑰，然後使用對稱密鑰加密所有數據。這使得在發送者和接收者之間共享對稱密鑰更加安全，並且在加密和解密數據時更快。

## 保護你的物聯網設備

物聯網設備可以使用對稱或非對稱加密進行保護。對稱加密更簡單，但安全性較低。

### 對稱密鑰

當你設置物聯網設備與IoT Hub交互時，你使用了一個連接字符串。一個示例連接字符串如下：

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

這個連接字符串由三部分組成，使用分號分隔，每部分是一個鍵和值：

| 鍵 | 值 | 描述 |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | IoT Hub的URL |
| DeviceId | `soil-moisture-sensor` | 設備的唯一ID |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | 設備和IoT Hub都知道的對稱密鑰 |

連接字符串的最後一部分`SharedAccessKey`是設備和IoT Hub都知道的對稱密鑰。這個密鑰不會從設備發送到雲端，也不會從雲端發送到設備。它用於加密發送或接收的數據。

✅ 做一個實驗：如果你在連接物聯網設備時更改連接字符串中的`SharedAccessKey`部分，會發生什麼？試試看。

當設備首次嘗試連接時，它會發送一個共享訪問簽名（SAS）令牌，該令牌由IoT Hub的URL、一個訪問簽名的到期時間戳（通常是當前時間起的一天）和一個簽名組成。這個簽名由URL和到期時間組成，並使用連接字符串中的共享訪問密鑰加密。

IoT Hub使用共享訪問密鑰解密這個簽名，如果解密後的值與URL和到期時間匹配，設備就被允許連接。它還會驗證當前時間是否在到期時間之前，以防止惡意設備捕獲真實設備的SAS令牌並使用它。

這是一種優雅的方式來驗證發送者是否是正確的設備。通過以解密和加密形式發送一些已知數據，服務器可以通過解密加密數據並確保結果與發送的解密版本匹配來驗證設備。如果匹配，則表明發送者和接收者擁有相同的對稱加密密鑰。
> 💁 因為有過期時間，你的 IoT 裝置需要知道準確的時間，通常是從 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 伺服器讀取。如果時間不準確，連線將會失敗。
連接後，所有從設備發送到 IoT Hub 或從 IoT Hub 發送到設備的數據都將使用共享訪問密鑰進行加密。

✅ 你認為如果多個設備共享相同的連接字串會發生什麼？

> 💁 將此密鑰存儲在代碼中是一個糟糕的安全做法。如果黑客獲得你的源代碼，他們就能獲得你的密鑰。此外，在發布代碼時也會更加困難，因為你需要為每個設備重新編譯以更新密鑰。更好的方法是從硬件安全模組（HSM）加載此密鑰——這是一個存儲加密值的 IoT 設備芯片，代碼可以讀取這些值。
>
> 在學習 IoT 時，通常更容易將密鑰放入代碼中，就像你在之前的課程中所做的那樣，但你必須確保此密鑰未被提交到公共源代碼控制中。

設備有兩個密鑰以及兩個對應的連接字串。這使你可以輪換密鑰——即如果第一個密鑰被泄露，可以切換到另一個密鑰並重新生成第一個密鑰。

### X.509 證書

當你使用公鑰/私鑰對進行非對稱加密時，你需要向任何想要向你發送數據的人提供你的公鑰。問題是，接收者如何確定這確實是你的公鑰，而不是其他人冒充你？與其直接提供密鑰，你可以將公鑰放入由可信第三方驗證的證書中，這被稱為 X.509 證書。

X.509 證書是包含公鑰部分的數字文件。它們通常由一些被稱為[證書授權機構](https://wikipedia.org/wiki/Certificate_authority) (CAs) 的可信組織簽發，並由 CA 進行數字簽名以表明密鑰是有效的並且來自你。你信任證書以及公鑰的來源，因為你信任 CA，就像你信任護照或駕駛執照是由可信的國家簽發的一樣。證書需要付費，因此你也可以“自簽名”，即自己創建並簽署證書，用於測試目的。

> 💁 你絕不應該在生產環境中使用自簽名證書。

這些證書包含多個字段，包括公鑰的來源、簽發證書的 CA 的詳細信息、證書的有效期以及公鑰本身。在使用證書之前，最好通過檢查其是否由原始 CA 簽名來驗證它。

✅ 你可以在 [Microsoft Understanding X.509 Public Key Certificates tutorial](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields) 中查看證書字段的完整列表。

使用 X.509 證書時，發送方和接收方都會擁有自己的公鑰和私鑰，以及包含公鑰的 X.509 證書。然後他們以某種方式交換 X.509 證書，使用彼此的公鑰加密發送的數據，並使用自己的私鑰解密接收到的數據。

![與其共享公鑰，你可以共享證書。證書的使用者可以通過檢查簽署證書的授權機構來驗證它是否來自你。](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76e.hk.png)

使用 X.509 證書的一大優勢是它們可以在設備之間共享。你可以創建一個證書，將其上傳到 IoT Hub，並將其用於所有設備。每個設備只需要知道私鑰即可解密從 IoT Hub 接收到的消息。

設備用於加密發送到 IoT Hub 的消息的證書由 Microsoft 發布。這是許多 Azure 服務使用的相同證書，有時已內置於 SDK 中。

> 💁 記住，公鑰就是公鑰。Azure 公鑰只能用於加密發送到 Azure 的數據，不能用於解密，因此可以隨處共享，包括在源代碼中。例如，你可以在 [Azure IoT C SDK 源代碼](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c) 中看到它。

✅ X.509 證書有很多術語。你可以在 [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn) 中閱讀一些可能遇到的術語的定義。

## 生成並使用 X.509 證書

生成 X.509 證書的步驟如下：

1. 創建公鑰/私鑰對。最廣泛使用的生成公鑰/私鑰對的算法之一是 [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA)。

1. 提交公鑰及相關數據進行簽名，可以由 CA 簽名，也可以自簽名。

Azure CLI 提供了命令來在 IoT Hub 中創建新的設備身份，並自動生成公鑰/私鑰對以及自簽名證書。

> 💁 如果你想查看詳細步驟，而不是使用 Azure CLI，你可以在 [Microsoft IoT Hub 文檔中的使用 OpenSSL 創建自簽名證書教程](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn) 中找到。

### 任務 - 使用 X.509 證書創建設備身份

1. 運行以下命令以註冊新的設備身份，並自動生成密鑰和證書：

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    將 `<hub_name>` 替換為你用於 IoT Hub 的名稱。

    這將創建一個 ID 為 `soil-moisture-sensor-x509` 的設備，以區分你在上一課中創建的設備身份。此命令還會在當前目錄中創建兩個文件：

    * `soil-moisture-sensor-x509-key.pem` - 此文件包含設備的私鑰。
    * `soil-moisture-sensor-x509-cert.pem` - 此文件是設備的 X.509 證書。

    請妥善保管這些文件！私鑰文件不應提交到公共源代碼控制中。

### 任務 - 在設備代碼中使用 X.509 證書

按照相關指南，使用 X.509 證書將你的 IoT 設備連接到雲端：

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [單板計算機 - Raspberry Pi/虛擬 IoT 設備](single-board-computer-x509.md)

---

## 🚀 挑戰

創建、管理和刪除 Azure 服務（如資源組和 IoT Hub）有多種方法。一種方法是使用 [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn)——一個基於網頁的界面，提供 GUI 來管理你的 Azure 服務。

前往 [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) 並探索該入口。看看你是否能使用該入口創建一個 IoT Hub，然後將其刪除。

**提示** - 通過入口創建服務時，你不需要提前創建資源組，可以在創建服務時創建資源組。完成後請確保刪除它！

你可以在 [Azure portal documentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn) 中找到大量文檔、教程和指南。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## 回顧與自學

* 在 [Wikipedia 的密碼學歷史頁面](https://wikipedia.org/wiki/History_of_cryptography) 上閱讀密碼學的歷史。
* 在 [Wikipedia 的 X.509 頁面](https://wikipedia.org/wiki/X.509) 上閱讀 X.509 證書的相關內容。

## 作業

[構建一個新的 IoT 設備](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為具權威性的來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。