<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-24T23:39:38+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "ja"
}
-->
# Wio Terminal

[Seeed StudiosのWio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)は、Arduino互換のマイクロコントローラーで、WiFiやいくつかのセンサー、アクチュエーターが内蔵されています。また、[Grove](https://www.seeedstudio.com/category/Grove-c-1003.html)というハードウェアエコシステムを使用して、さらに多くのセンサーやアクチュエーターを追加するためのポートも備えています。

![Seeed StudiosのWio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9a.ja.png)

## セットアップ

Wio Terminalを使用するには、コンピューターにいくつかの無料ソフトウェアをインストールする必要があります。また、WiFiに接続する前にWio Terminalのファームウェアを更新する必要があります。

### タスク - セットアップ

必要なソフトウェアをインストールし、ファームウェアを更新します。

1. Visual Studio Code (VS Code) をインストールします。これは、C/C++でデバイスコードを書くために使用するエディターです。[VS Codeのドキュメント](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)を参照して、インストール方法を確認してください。

    > 💁 Arduino開発のためのもう一つの人気のあるIDEは[Arduino IDE](https://www.arduino.cc/en/software)です。このツールに慣れている場合は、VS CodeとPlatformIOの代わりに使用することもできますが、レッスンではVS Codeを使用する方法を説明します。

1. VS Code PlatformIO拡張機能をインストールします。これは、C/C++でマイクロコントローラーをプログラミングするためのVS Code拡張機能です。[PlatformIO拡張機能のドキュメント](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide)を参照して、この拡張機能をVS Codeにインストールする方法を確認してください。この拡張機能は、C/C++コードを扱うためにMicrosoft C/C++拡張機能に依存しており、PlatformIOをインストールすると自動的にC/C++拡張機能もインストールされます。

1. Wio Terminalをコンピューターに接続します。Wio Terminalの底部にはUSB-Cポートがあり、これをコンピューターのUSBポートに接続する必要があります。Wio TerminalにはUSB-CからUSB-Aへのケーブルが付属していますが、コンピューターにUSB-Cポートしかない場合は、USB-CケーブルまたはUSB-AからUSB-Cへのアダプターが必要です。

1. [Wio Terminal Wiki WiFi Overview documentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)の指示に従って、Wio Terminalをセットアップし、ファームウェアを更新してください。

## Hello World

新しいプログラミング言語や技術を始める際には、通常「Hello World」アプリケーションを作成します。これは、すべてのツールが正しく設定されていることを確認するために、`"Hello World"`のようなテキストを出力する小さなアプリケーションです。

Wio TerminalのHello Worldアプリは、Visual Studio CodeがPlatformIOとともに正しくインストールされ、マイクロコントローラー開発の準備が整っていることを確認するためのものです。

### PlatformIOプロジェクトを作成する

最初のステップは、Wio Terminal用に設定されたPlatformIOを使用して新しいプロジェクトを作成することです。

#### タスク - PlatformIOプロジェクトを作成する

PlatformIOプロジェクトを作成します。

1. Wio Terminalをコンピューターに接続します。

1. VS Codeを起動します。

1. PlatformIOアイコンがサイドメニューバーに表示されます：

    ![Platform IOメニューオプション](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.ja.png)

    このメニュー項目を選択し、*PIO Home -> Open*を選択します。

    ![Platform IOオープンオプション](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.ja.png)

1. ウェルカム画面から**+ New Project**ボタンを選択します。

    ![新しいプロジェクトボタン](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.ja.png)

1. *Project Wizard*でプロジェクトを設定します：

    1. プロジェクト名を`nightlight`とします。

    1. *Board*ドロップダウンで`WIO`と入力してボードをフィルタリングし、*Seeeduino Wio Terminal*を選択します。

    1. *Framework*は*Arduino*のままにします。

    1. *Use default location*チェックボックスをチェックしたままにするか、チェックを外してプロジェクトの場所を選択します。

    1. **Finish**ボタンを選択します。

    ![完成したプロジェクトウィザード](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.ja.png)

    PlatformIOは、Wio Terminal用のコードをコンパイルするために必要なコンポーネントをダウンロードし、プロジェクトを作成します。これには数分かかる場合があります。

### PlatformIOプロジェクトを調査する

VS Codeのエクスプローラーには、PlatformIOウィザードによって作成された複数のファイルとフォルダーが表示されます。

#### フォルダー

* `.pio` - このフォルダーには、PlatformIOが必要とする一時データ（ライブラリやコンパイル済みコードなど）が含まれています。削除されても自動的に再作成されるため、GitHubなどでプロジェクトを共有する際にソースコード管理に追加する必要はありません。
* `.vscode` - このフォルダーには、PlatformIOとVS Codeの設定が含まれています。削除されても自動的に再作成されるため、GitHubなどでプロジェクトを共有する際にソースコード管理に追加する必要はありません。
* `include` - このフォルダーは、コードに追加のライブラリを追加する際に必要な外部ヘッダーファイル用です。このレッスンではこのフォルダーを使用しません。
* `lib` - このフォルダーは、コードから呼び出す外部ライブラリ用です。このレッスンではこのフォルダーを使用しません。
* `src` - このフォルダーには、アプリケーションのメインソースコードが含まれています。初期状態では、`main.cpp`という単一のファイルが含まれています。
* `test` - このフォルダーには、コードのユニットテストを配置します。

#### ファイル

* `main.cpp` - `src`フォルダー内のこのファイルには、アプリケーションのエントリーポイントが含まれています。このファイルを開くと、以下のコードが含まれています：

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    デバイスが起動すると、Arduinoフレームワークは`setup`関数を一度実行し、その後`loop`関数をデバイスがオフになるまで繰り返し実行します。

* `.gitignore` - このファイルには、Gitソースコード管理に追加しないファイルやディレクトリ（例：GitHubにアップロードする際）がリストされています。

* `platformio.ini` - このファイルには、デバイスとアプリの設定が含まれています。このファイルを開くと、以下のコードが含まれています：

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    `[env:seeed_wio_terminal]`セクションには、Wio Terminalの設定が含まれています。複数の`env`セクションを持つことで、複数のボード用にコードをコンパイルすることができます。

    他の値はプロジェクトウィザードの設定と一致しています：

  * `platform = atmelsam`は、Wio Terminalが使用するハードウェア（ATSAMD51ベースのマイクロコントローラー）を定義します。
  * `board = seeed_wio_terminal`は、マイクロコントローラーボードの種類（Wio Terminal）を定義します。
  * `framework = arduino`は、このプロジェクトがArduinoフレームワークを使用していることを定義します。

### Hello Worldアプリを書く

これでHello Worldアプリを書く準備が整いました。

#### タスク - Hello Worldアプリを書く

Hello Worldアプリを書きます。

1. VS Codeで`main.cpp`ファイルを開きます。

1. 以下のコードに変更します：

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    `setup`関数は、シリアルポート（この場合、Wio Terminalをコンピューターに接続するためのUSBポート）への接続を初期化します。パラメーター`9600`は[ボーレート](https://wikipedia.org/wiki/Symbol_rate)（シンボルレートとも呼ばれる）を指定し、シリアルポートでデータが送信される速度をビット毎秒で表します。この設定では、毎秒9,600ビット（0と1）のデータが送信されます。その後、シリアルポートが準備完了になるまで待機します。

    `loop`関数は、シリアルポートに`Hello World!`という行を送信します。この行には`Hello World!`の文字と改行文字が含まれます。その後、5,000ミリ秒（5秒）間スリープします。`loop`が終了すると、再び実行され、デバイスが電源オンの間ずっと繰り返されます。

1. Wio Terminalをアップロードモードにします。デバイスに新しいコードをアップロードするたびにこれを行う必要があります：

    1. 電源スイッチを素早く2回下に引きます。スイッチは毎回オンの位置に戻ります。

    1. USBポートの右側にある青いステータスLEDを確認します。LEDが点滅しているはずです。

    [![Wio Terminalをアップロードモードにする方法を示す動画](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)

    上記の画像をクリックすると、方法を示す動画が表示されます。

1. コードをビルドしてWio Terminalにアップロードします。

    1. VS Codeのコマンドパレットを開きます。

    1. `PlatformIO Upload`と入力してアップロードオプションを検索し、*PlatformIO: Upload*を選択します。

        ![コマンドパレット内のPlatformIOアップロードオプション](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.ja.png)

        PlatformIOは必要に応じてコードを自動的にビルドしてからアップロードします。

    1. コードがコンパイルされ、Wio Terminalにアップロードされます。

        > 💁 macOSを使用している場合、*DISK NOT EJECTED PROPERLY*という通知が表示されることがあります。これは、Wio Terminalがフラッシュプロセスの一環としてドライブとしてマウントされ、コンパイル済みコードがデバイスに書き込まれる際に切断されるためです。この通知は無視して構いません。

    ⚠️ アップロードポートが利用できないというエラーが表示された場合、まずWio Terminalがコンピューターに接続されていること、左側のスイッチでオンになっていること、アップロードモードに設定されていることを確認してください。底部の緑色のライトが点灯し、青色のライトが点滅しているはずです。それでもエラーが発生する場合は、電源スイッチを素早く2回下に引いてWio Terminalを強制的にアップロードモードにし、再度アップロードを試してください。

PlatformIOには、Wio TerminalからUSBケーブル経由で送信されるデータを監視するためのシリアルモニターがあります。これにより、`Serial.println("Hello World");`コマンドによって送信されたデータを監視できます。

1. VS Codeのコマンドパレットを開きます。

1. `PlatformIO Serial`と入力してシリアルモニターオプションを検索し、*PlatformIO: Serial Monitor*を選択します。

    ![コマンドパレット内のPlatformIOシリアルモニターオプション](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.ja.png)

    新しいターミナルが開き、シリアルポート経由で送信されたデータがこのターミナルにストリームされます：

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World`が5秒ごとにシリアルモニターに表示されます。

> 💁 このコードは[code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal)フォルダーにあります。

😀 'Hello World'プログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。