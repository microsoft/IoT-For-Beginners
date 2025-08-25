<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T00:05:08+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "ja"
}
-->
# タイマーを設定する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、サーバーレスコードを呼び出して音声を理解し、その結果に基づいて仮想IoTデバイスまたはRaspberry Piにタイマーを設定します。

## タイマーを設定する

音声認識から返ってきたテキストは、LUISで処理するためにサーバーレスコードに送信する必要があります。そして、タイマーの秒数を取得します。この秒数を使用してタイマーを設定できます。

タイマーはPythonの`threading.Timer`クラスを使用して設定できます。このクラスは遅延時間と関数を受け取り、遅延時間後にその関数を実行します。

### タスク - テキストをサーバーレス関数に送信する

1. VS Codeで`smart-timer`プロジェクトを開き、仮想IoTデバイスを使用している場合はターミナルで仮想環境がロードされていることを確認してください。

1. `process_text`関数の上に、RESTエンドポイントを呼び出すための`get_timer_time`という関数を宣言します:

    ```python
    def get_timer_time(text):
    ```

1. この関数に以下のコードを追加して、呼び出すURLを定義します:

    ```python
    url = '<URL>'
    ```

    `<URL>`を、前のレッスンで作成したRESTエンドポイントのURLに置き換えてください。これは、コンピュータ上またはクラウド上にあるものです。

1. 以下のコードを追加して、JSONとして送信するプロパティとしてテキストを設定します:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. その下に、レスポンスペイロードから`seconds`を取得し、呼び出しが失敗した場合は0を返します:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    HTTP呼び出しが成功すると、200番台のステータスコードが返されます。また、サーバーレスコードはテキストが処理され、タイマー設定の意図として認識された場合に200を返します。

### タスク - バックグラウンドスレッドでタイマーを設定する

1. ファイルの冒頭に以下のインポート文を追加して、Pythonのthreadingライブラリをインポートします:

    ```python
    import threading
    ```

1. `process_text`関数の上に、応答を話す関数を追加します。現時点ではコンソールに書き込むだけですが、このレッスンの後半ではテキストを話すようになります。

    ```python
    def say(text):
        print(text)
    ```

1. その下に、タイマーが完了したことを知らせるためにタイマーによって呼び出される関数を追加します:

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

    この関数はタイマーの分と秒を受け取り、タイマーが完了したことを知らせる文を作成します。分と秒の数を確認し、それぞれの時間単位に値がある場合のみメッセージに含めます。例えば、分が0の場合は秒のみがメッセージに含まれます。この文は`say`関数に送信されます。

1. その下に、タイマーを作成するための`create_timer`関数を追加します:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    この関数はコマンドで送信されるタイマーの総秒数を受け取り、それを分と秒に変換します。その後、総秒数を使用してタイマーオブジェクトを作成し、`announce_timer`関数と分と秒を含むリストを渡します。タイマーが経過すると、`announce_timer`関数が呼び出され、このリストの内容がパラメータとして渡されます。リストの最初の項目が`minutes`パラメータとして渡され、2番目の項目が`seconds`パラメータとして渡されます。

1. `create_timer`関数の最後に、タイマーが開始されることをユーザーに知らせるメッセージを作成するコードを追加します:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    ここでも、値がある時間単位のみが含まれます。この文は`say`関数に送信されます。

1. `process_text`関数の最後に以下を追加して、テキストからタイマーの時間を取得し、タイマーを作成します:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    秒数が0より大きい場合のみタイマーが作成されます。

1. アプリを実行し、関数アプリも実行されていることを確認してください。いくつかのタイマーを設定し、出力にタイマーが設定される様子と、タイマーが経過したときの様子が表示されることを確認してください:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 このコードは[code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi)または[code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device)フォルダにあります。

😀 タイマーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。