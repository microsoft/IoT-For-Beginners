<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-24T23:36:34+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "ja"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) はシングルボードコンピュータです。さまざまなデバイスやエコシステムを使用してセンサーやアクチュエータを追加することができ、このレッスンでは [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) というハードウェアエコシステムを使用します。Pythonを使ってRaspberry Piをプログラミングし、Groveセンサーにアクセスします。

![Raspberry Pi 4](../../../../../translated_images/ja/raspberry-pi-4.fd4590d308c3d456.webp)

## セットアップ

Raspberry PiをIoTハードウェアとして使用する場合、2つの選択肢があります。これらのレッスンをすべて進めてPi上で直接コードを書くか、ヘッドレスのPiにリモート接続してコンピュータからコードを書くかです。

始める前に、Grove Base HatをPiに接続する必要があります。

### タスク - セットアップ

Grove Base HatをPiに取り付け、Piを設定します。

1. Grove Base HatをPiに接続します。HatのソケットはPiのすべてのGPIOピンにフィットし、ピンにしっかりと差し込むことができます。HatはPiの上に取り付けられ、Piを覆います。

    ![Grove Hatの取り付け](../../../../../images/pi-grove-hat-fitting.gif)

1. Piをどのようにプログラミングするかを決め、以下の該当するセクションに進んでください：

    * [Pi上で直接作業する](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [リモートアクセスでPiをプログラミングする](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Pi上で直接作業する

Pi上で直接作業したい場合は、Raspberry Pi OSのデスクトップ版を使用し、必要なツールをすべてインストールできます。

#### タスク - Pi上で直接作業する

開発用にPiをセットアップします。

1. [Raspberry Piセットアップガイド](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) の指示に従い、Piをセットアップし、キーボード/マウス/モニターに接続し、WiFiまたはイーサネットネットワークに接続し、ソフトウェアを更新します。

Groveセンサーやアクチュエータを使用してPiをプログラミングするには、デバイスコードを書くためのエディタや、Groveハードウェアと連携するためのさまざまなライブラリやツールをインストールする必要があります。

1. Piが再起動したら、トップメニューバーの**Terminal**アイコンをクリックするか、*Menu -> Accessories -> Terminal*を選択してターミナルを起動します。

1. 次のコマンドを実行して、OSとインストール済みソフトウェアを最新の状態にします：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. 次のコマンドを実行して、Groveハードウェアに必要なすべてのライブラリをインストールします：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    これにより、GitとPythonパッケージをインストールするためのPipがインストールされます。

    Pythonの強力な機能の1つは、[Pipパッケージ](https://pypi.org) をインストールできることです。これらは他の人が書いたコードのパッケージで、インターネット上に公開されています。1つのコマンドでPipパッケージをコンピュータにインストールし、そのパッケージをコードで使用できます。

    Seeed Grove Pythonパッケージはソースからインストールする必要があります。これらのコマンドは、このパッケージのソースコードを含むリポジトリをクローンし、それをローカルにインストールします。

    > 💁 通常、パッケージをインストールすると、コンピュータ全体で利用可能になりますが、これによりパッケージのバージョンに関する問題が発生する可能性があります。たとえば、あるアプリケーションが特定のバージョンのパッケージに依存している場合、新しいバージョンを別のアプリケーションのためにインストールすると壊れることがあります。この問題を回避するために、[Python仮想環境](https://docs.python.org/3/library/venv.html) を使用できます。これは専用フォルダ内のPythonのコピーで、Pipパッケージをそのフォルダ内にのみインストールします。ただし、Piを使用する際には仮想環境を使用しません。GroveインストールスクリプトはGrove Pythonパッケージをグローバルにインストールするため、仮想環境を使用する場合は仮想環境を設定し、その環境内でGroveパッケージを手動で再インストールする必要があります。特に多くのPi開発者が各プロジェクトのためにクリーンなSDカードを再フラッシュするため、グローバルパッケージを使用する方が簡単です。

    最後に、I<sup>2</sup>Cインターフェースを有効にします。

1. メニューを使用するか、ターミナルで次のコマンドを実行してPiを再起動します：

    ```sh
    sudo reboot
    ```

1. Piが再起動したら、再度ターミナルを起動し、次のコマンドを実行して[Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) をインストールします。これはPythonでデバイスコードを書くために使用するエディタです。

    ```sh
    sudo apt install code
    ```

    インストールが完了すると、VS Codeはトップメニューから利用可能になります。

    > 💁 これらのレッスンではVS Codeを使用する指示が記載されていますが、好みのPython IDEやエディタを使用しても構いません。

1. Pylanceをインストールします。これはPython言語サポートを提供するVS Codeの拡張機能です。[Pylance拡張機能のドキュメント](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) を参照して、この拡張機能をVS Codeにインストールする方法を確認してください。

### リモートアクセスでPiをプログラミングする

Pi上で直接コードを書く代わりに、キーボード/マウス/モニターに接続せずに「ヘッドレス」で動作させ、コンピュータからVisual Studio Codeを使用して設定やコードを書くことができます。

#### Pi OSのセットアップ

リモートでコードを書くには、Pi OSをSDカードにインストールする必要があります。

##### タスク - Pi OSのセットアップ

ヘッドレスPi OSをセットアップします。

1. [Raspberry Pi OSソフトウェアページ](https://www.raspberrypi.org/software/) から**Raspberry Pi Imager**をダウンロードしてインストールします。

1. 必要に応じてアダプタを使用して、SDカードをコンピュータに挿入します。

1. Raspberry Pi Imagerを起動します。

1. Raspberry Pi Imagerで**CHOOSE OS**ボタンを選択し、*Raspberry Pi OS (Other)*を選択した後、*Raspberry Pi OS Lite (32-bit)*を選択します。

    ![Raspberry Pi ImagerでRaspberry Pi OS Liteを選択](../../../../../translated_images/ja/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Liteは、デスクトップUIやUIベースのツールが含まれていないRaspberry Pi OSのバージョンです。ヘッドレスPiにはこれらは必要なく、インストールサイズが小さくなり、起動時間が短縮されます。

1. **CHOOSE STORAGE**ボタンを選択し、SDカードを選択します。

1. `Ctrl+Shift+X`を押して**Advanced Options**を起動します。これらのオプションを使用すると、Raspberry Pi OSをSDカードに書き込む前にいくつかの事前設定が可能です。

    1. **Enable SSH**チェックボックスをオンにし、`pi`ユーザーのパスワードを設定します。このパスワードは後でPiにログインする際に使用します。

    1. PiにWiFiで接続する予定がある場合は、**Configure WiFi**チェックボックスをオンにし、WiFiのSSIDとパスワードを入力し、WiFiの国を選択します。イーサネットケーブルを使用する場合はこれを行う必要はありません。接続するネットワークがコンピュータと同じであることを確認してください。

    1. **Set locale settings**チェックボックスをオンにし、国とタイムゾーンを設定します。

    1. **SAVE**ボタンを選択します。

1. **WRITE**ボタンを選択してOSをSDカードに書き込みます。macOSを使用している場合、ディスクイメージを書き込むためのツールが特権アクセスを必要とするため、パスワードの入力を求められます。

OSがSDカードに書き込まれると、完了後にOSによってカードが取り出され、通知されます。SDカードをコンピュータから取り外し、Piに挿入して電源を入れ、約2分間待って完全に起動するのを待ちます。

#### Piに接続する

次のステップはPiにリモートアクセスすることです。これは、macOS、Linux、および最近のWindowsバージョンで利用可能な`ssh`を使用して行うことができます。

##### タスク - Piに接続する

Piにリモートアクセスします。

1. ターミナルまたはコマンドプロンプトを起動し、次のコマンドを入力してPiに接続します：

    ```sh
    ssh pi@raspberrypi.local
    ```

    古いバージョンのWindowsを使用していて`ssh`がインストールされていない場合は、OpenSSHを使用できます。[OpenSSHインストールドキュメント](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn) にインストール手順が記載されています。

1. Piに接続されると、パスワードの入力を求められます。

    `<hostname>.local`を使用してネットワーク上のコンピュータを見つける機能は、LinuxやWindowsでは比較的新しい機能です。LinuxまたはWindowsを使用していて、ホスト名が見つからないというエラーが発生した場合は、ZeroConfネットワーキング（AppleではBonjourと呼ばれる）を有効にするための追加ソフトウェアをインストールする必要があります：

    1. Linuxを使用している場合は、次のコマンドを使用してAvahiをインストールします：

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Windowsを使用している場合、ZeroConfを有効にする最も簡単な方法は、[Bonjour Print Services for Windows](http://support.apple.com/kb/DL999) をインストールすることです。また、[iTunes for Windows](https://www.apple.com/itunes/download/) をインストールして、より新しいバージョンのユーティリティを取得することもできます（スタンドアロンでは利用できません）。

    > 💁 `raspberrypi.local`を使用して接続できない場合は、PiのIPアドレスを使用できます。[Raspberry Pi IPアドレスドキュメント](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) を参照して、IPアドレスを取得するさまざまな方法を確認してください。

1. Raspberry Pi Imager Advanced Optionsで設定したパスワードを入力します。

#### Pi上のソフトウェアを設定する

Piに接続したら、OSを最新の状態にし、Groveハードウェアと連携するためのさまざまなライブラリやツールをインストールする必要があります。

##### タスク - Pi上のソフトウェアを設定する

インストールされたPiソフトウェアを設定し、Groveライブラリをインストールします。

1. `ssh`セッションから次のコマンドを実行してPiを更新し、再起動します：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Piが更新され、再起動されます。Piが再起動されると`ssh`セッションは終了するため、約30秒待ってから再接続してください。

1. 再接続した`ssh`セッションから、次のコマンドを実行してGroveハードウェアに必要なすべてのライブラリをインストールします：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    これにより、GitとPythonパッケージをインストールするためのPipがインストールされます。

    Pythonの強力な機能の1つは、[Pipパッケージ](https://pypi.org) をインストールできることです。これらは他の人が書いたコードのパッケージで、インターネット上に公開されています。1つのコマンドでPipパッケージをコンピュータにインストールし、そのパッケージをコードで使用できます。

    Seeed Grove Pythonパッケージはソースからインストールする必要があります。これらのコマンドは、このパッケージのソースコードを含むリポジトリをクローンし、それをローカルにインストールします。

    > 💁 通常、パッケージをインストールすると、コンピュータ全体で利用可能になりますが、これによりパッケージのバージョンに関する問題が発生する可能性があります。たとえば、あるアプリケーションが特定のバージョンのパッケージに依存している場合、新しいバージョンを別のアプリケーションのためにインストールすると壊れることがあります。この問題を回避するために、[Python仮想環境](https://docs.python.org/3/library/venv.html) を使用できます。これは専用フォルダ内のPythonのコピーで、Pipパッケージをそのフォルダ内にのみインストールします。ただし、Piを使用する際には仮想環境を使用しません。GroveインストールスクリプトはGrove Pythonパッケージをグローバルにインストールするため、仮想環境を使用する場合は仮想環境を設定し、その環境内でGroveパッケージを手動で再インストールする必要があります。特に多くのPi開発者が各プロジェクトのためにクリーンなSDカードを再フラッシュするため、グローバルパッケージを使用する方が簡単です。

    最後に、I<sup>2</sup>Cインターフェースを有効にします。

1. 次のコマンドを実行してPiを再起動します：

    ```sh
    sudo reboot
    ```

    Piが再起動されると`ssh`セッションは終了します。再接続する必要はありません。

#### リモートアクセス用にVS Codeを設定する

Piが設定されたら、コンピュータからVisual Studio Code (VS Code) を使用して接続できます。これは、Pythonでデバイスコードを書くために使用する無料の開発者向けテキストエディタです。

##### タスク - リモートアクセス用にVS Codeを設定する

必要なソフトウェアをインストールし、Piにリモート接続します。

1. [VS Codeドキュメント](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) に従って、コンピュータにVS Codeをインストールします。

1. [VS Codeリモート開発（SSH使用）ドキュメント](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) の指示に従って、必要なコンポーネントをインストールします。

1. 同じ指示に従って、VS CodeをPiに接続します。

1. 接続後、[拡張機能の管理](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) の指示に従って、[Pylance拡張機能](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) をPiにリモートでインストールします。

## Hello world
新しいプログラミング言語や技術を始める際には、伝統的に「Hello World」アプリケーションを作成します。これは、すべてのツールが正しく設定されていることを確認するために、`"Hello World"`のようなテキストを出力する小さなアプリケーションです。

Pi用のHello Worldアプリは、PythonとVisual Studio Codeが正しくインストールされていることを確認するためのものです。

このアプリは`nightlight`というフォルダー内に作成されます。このフォルダーは、この課題の後半でナイトライトアプリケーションを構築する際に、異なるコードで再利用されます。

### タスク - Hello World

Hello Worldアプリを作成します。

1. Pi上で直接、またはRemote SSH拡張機能を使用してコンピューターからPiに接続し、VS Codeを起動します。

1. *Terminal -> New Terminal*を選択するか、`` CTRL+` ``を押してVS Codeターミナルを起動します。ターミナルは`pi`ユーザーのホームディレクトリに開きます。

1. 以下のコマンドを実行してコード用のディレクトリを作成し、そのディレクトリ内に`app.py`というPythonファイルを作成します：

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. *File -> Open...*を選択し、*nightlight*フォルダーを選択して**OK**をクリックして、このフォルダーをVS Codeで開きます。

    ![VS Codeのオープンダイアログでnightlightフォルダーが表示されている](../../../../../translated_images/ja/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. VS Codeエクスプローラーから`app.py`ファイルを開き、以下のコードを追加します：

    ```python
    print('Hello World!')
    ```

    `print`関数は、渡された内容をコンソールに出力します。

1. VS Codeターミナルから以下を実行してPythonアプリを実行します：

    ```sh
    python app.py
    ```

    > 💁 Python 2がインストールされている場合、Python 3を実行するには明示的に`python3`を呼び出す必要があるかもしれません。Python 2がインストールされている場合、`python`を呼び出すとPython 2が使用されます。デフォルトでは、最新のRaspberry Pi OSバージョンにはPython 3のみがインストールされています。

    ターミナルに以下の出力が表示されます：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 このコードは[code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi)フォルダーにあります。

😀 あなたの「Hello World」プログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は一切の責任を負いません。