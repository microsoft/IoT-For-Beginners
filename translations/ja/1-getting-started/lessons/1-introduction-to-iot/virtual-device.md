<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-24T23:33:23+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "ja"
}
-->
# 仮想シングルボードコンピュータ

IoTデバイスやセンサー、アクチュエータを購入する代わりに、自分のコンピュータを使ってIoTハードウェアをシミュレートすることができます。[CounterFitプロジェクト](https://github.com/CounterFit-IoT/CounterFit)を利用すると、センサーやアクチュエータのようなIoTハードウェアをシミュレートするアプリをローカルで実行し、Raspberry Piで物理ハードウェアを使う場合と同じ方法で書かれたローカルのPythonコードからセンサーやアクチュエータにアクセスできます。

## セットアップ

CounterFitを使用するには、コンピュータにいくつかの無料ソフトウェアをインストールする必要があります。

### タスク

必要なソフトウェアをインストールします。

1. Pythonをインストールします。最新バージョンのPythonをインストールする手順については、[Pythonダウンロードページ](https://www.python.org/downloads/)を参照してください。

1. Visual Studio Code (VS Code) をインストールします。これは、Pythonで仮想デバイスコードを書くために使用するエディタです。[VS Codeのドキュメント](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)を参照して、VS Codeのインストール手順を確認してください。

    > 💁 好きなPython IDEやエディタを使用しても構いませんが、このレッスンではVS Codeを使用する前提で説明が進みます。

1. VS CodeのPylance拡張機能をインストールします。これは、Pythonの言語サポートを提供するVS Codeの拡張機能です。[Pylance拡張機能のドキュメント](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)を参照して、この拡張機能のインストール手順を確認してください。

CounterFitアプリのインストールと設定に関する手順は、プロジェクトごとにインストールされるため、課題の指示に従って進めてください。

## Hello World

新しいプログラミング言語や技術を始める際には、通常「Hello World」アプリケーションを作成します。これは、すべてのツールが正しく設定されていることを確認するために、`"Hello World"`のようなテキストを出力する小さなアプリケーションです。

仮想IoTハードウェア用のHello Worldアプリでは、PythonとVisual Studio Codeが正しくインストールされていることを確認します。また、仮想IoTセンサーやアクチュエータ用のCounterFitに接続します。このアプリではハードウェアを使用せず、すべてが正常に動作していることを確認するための接続のみを行います。

このアプリは`nightlight`というフォルダ内に作成され、課題の後半でナイトライトアプリケーションを構築する際に異なるコードで再利用されます。

### Python仮想環境の設定

Pythonの強力な機能の1つに、[Pipパッケージ](https://pypi.org)をインストールできる点があります。これらは他の人が書いてインターネット上に公開したコードのパッケージです。1つのコマンドでPipパッケージをコンピュータにインストールし、そのパッケージをコード内で使用できます。CounterFitと通信するためのパッケージをインストールする際にPipを使用します。

デフォルトでは、パッケージをインストールするとコンピュータ全体で利用可能になりますが、これによりパッケージのバージョンに関する問題が発生する可能性があります。例えば、あるアプリケーションが特定のバージョンのパッケージに依存している場合、新しいバージョンを別のアプリケーションのためにインストールすると問題が発生することがあります。この問題を回避するために、[Python仮想環境](https://docs.python.org/3/library/venv.html)を使用できます。これは専用フォルダ内のPythonのコピーであり、Pipパッケージをインストールするとそのフォルダ内だけにインストールされます。

> 💁 Raspberry Piを使用している場合、Pipパッケージを管理するために仮想環境を設定していません。その代わりに、Groveパッケージがインストーラースクリプトによってグローバルにインストールされているため、グローバルパッケージを使用しています。

#### タスク - Python仮想環境の設定

Python仮想環境を設定し、CounterFit用のPipパッケージをインストールします。

1. ターミナルまたはコマンドラインから、以下を実行して新しいディレクトリを作成し、そのディレクトリに移動します：

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. 次に、以下を実行して`.venv`フォルダ内に仮想環境を作成します：

    ```sh
    python3 -m venv .venv
    ```

    > 💁 仮想環境を作成する際に`python3`を明示的に呼び出す必要があります。これは、Python 2がインストールされている場合に備えるためです。Python 2がインストールされている場合、`python`を呼び出すとPython 2が使用されるためです。

1. 仮想環境を有効化します：

    * Windowsの場合：
        * コマンドプロンプト、またはWindows Terminalのコマンドプロンプトを使用している場合、以下を実行します：

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShellを使用している場合、以下を実行します：

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > スクリプトの実行が無効になっているというエラーが表示された場合、適切な実行ポリシーを設定してスクリプトの実行を有効にする必要があります。これを行うには、管理者としてPowerShellを起動し、以下のコマンドを実行します：

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            確認を求められたら`Y`を入力してください。その後、PowerShellを再起動して再試行してください。

            必要に応じて、後でこの実行ポリシーをリセットすることができます。詳細は[Microsoft Docsの実行ポリシーページ](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn)を参照してください。

    * macOSまたはLinuxの場合、以下を実行します：

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 これらのコマンドは、仮想環境を作成した場所と同じ場所で実行する必要があります。`.venv`フォルダに移動する必要はなく、仮想環境を有効化するコマンドやパッケージをインストールするコマンドは、仮想環境を作成したフォルダで実行してください。

1. 仮想環境が有効化されたら、デフォルトの`python`コマンドは仮想環境を作成するために使用されたPythonのバージョンを実行します。以下を実行してバージョンを確認してください：

    ```sh
    python --version
    ```

    出力には以下が含まれるはずです：

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Pythonのバージョンは異なる場合がありますが、バージョン3.6以上であれば問題ありません。それ以下の場合、このフォルダを削除し、新しいバージョンのPythonをインストールして再試行してください。

1. 以下のコマンドを実行して、CounterFit用のPipパッケージをインストールします。これらのパッケージには、CounterFitアプリのメイン部分とGroveハードウェア用のシムが含まれています。このシムを使用すると、Groveエコシステムの物理センサーやアクチュエータを使用しているかのようにコードを書くことができますが、仮想IoTデバイスに接続されます。

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    これらのPipパッケージは仮想環境内にのみインストールされ、仮想環境外では利用できません。

### コードを書く

Python仮想環境が準備できたら、'Hello World'アプリケーションのコードを書きます。

#### タスク - コードを書く

コンソールに`"Hello World"`を出力するPythonアプリケーションを作成します。

1. 仮想環境内で以下を実行して、`app.py`というPythonファイルを作成します：

    * Windowsの場合：

        ```cmd
        type nul > app.py
        ```

    * macOSまたはLinuxの場合：

        ```cmd
        touch app.py
        ```

1. 現在のフォルダをVS Codeで開きます：

    ```sh
    code .
    ```

    > 💁 macOSでターミナルが`command not found`を返す場合、VS CodeがPATHに追加されていないことを意味します。[VS Codeドキュメントのコマンドラインからの起動セクション](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line)の手順に従ってVS CodeをPATHに追加し、その後コマンドを実行してください。WindowsおよびLinuxでは、VS CodeはデフォルトでPATHに追加されています。

1. VS Codeが起動すると、Python仮想環境が有効化されます。選択された仮想環境は、下部のステータスバーに表示されます：

    ![VS Codeに選択された仮想環境が表示されている](../../../../../translated_images/ja/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. VS Codeターミナルが起動時にすでに実行中の場合、仮想環境がターミナル内で有効化されていない可能性があります。この場合、**Kill the active terminal instance**ボタンを使用してターミナルを終了するのが最も簡単です：

    ![VS CodeのKill the active terminal instanceボタン](../../../../../translated_images/ja/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    ターミナルに仮想環境が有効化されているかどうかは、ターミナルプロンプトに仮想環境の名前がプレフィックスとして表示されるかどうかで確認できます。例えば、以下のように表示される場合があります：

    ```sh
    (.venv) ➜  nightlight
    ```

    プロンプトに`.venv`がプレフィックスとして表示されていない場合、ターミナル内で仮想環境が有効化されていません。

1. **Terminal -> New Terminal**を選択するか、`` CTRL+` ``を押して、新しいVS Codeターミナルを起動します。新しいターミナルは仮想環境をロードし、その呼び出しがターミナルに表示されます。プロンプトにも仮想環境の名前（`.venv`）が表示されます：

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Codeエクスプローラーから`app.py`ファイルを開き、以下のコードを追加します：

    ```python
    print('Hello World!')
    ```

    `print`関数は、渡された内容をコンソールに出力します。

1. VS Codeターミナルから以下を実行してPythonアプリを実行します：

    ```sh
    python app.py
    ```

    出力には以下が表示されます：

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 'Hello World'プログラムが成功しました！

### 'ハードウェア'を接続する

2つ目の'Hello World'ステップとして、CounterFitアプリを実行し、コードを接続します。これは、IoTハードウェアを開発キットに接続する仮想的な手順に相当します。

#### タスク - 'ハードウェア'を接続する

1. VS Codeターミナルから以下のコマンドを実行してCounterFitアプリを起動します：

    ```sh
    counterfit
    ```

    アプリが実行され、ブラウザで開きます：

    ![ブラウザで実行中のCounterFitアプリ](../../../../../translated_images/ja/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    アプリは*Disconnected*と表示され、右上のLEDがオフになっています。

1. `app.py`の先頭に以下のコードを追加します：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    このコードは、`counterfit_connection`モジュールから`CounterFitConnection`クラスをインポートします。その後、`127.0.0.1`（ローカルコンピュータに常にアクセスできるIPアドレス、*localhost*とも呼ばれる）上のポート5000で実行中のCounterFitアプリに接続を初期化します。

    > 💁 ポート5000で他のアプリが実行中の場合、このポートをコード内で更新し、`CounterFit --port <port_number>`を使用してCounterFitを起動することで変更できます。`<port_number>`には使用したいポート番号を指定してください。

1. CounterFitアプリが現在のターミナルで実行中のため、新しいVS Codeターミナルを起動する必要があります。**Create a new integrated terminal**ボタンを選択してください：

    ![VS CodeのCreate a new integrated terminalボタン](../../../../../translated_images/ja/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. この新しいターミナルで、先ほどと同じように`app.py`ファイルを実行します。CounterFitのステータスが**Connected**に変わり、LEDが点灯します。

    ![接続された状態を示すCounterFit](../../../../../translated_images/ja/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 このコードは[code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device)フォルダにあります。

😀 ハードウェアへの接続が成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。原文（元の言語で記載された文書）が信頼できる情報源として優先されるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。