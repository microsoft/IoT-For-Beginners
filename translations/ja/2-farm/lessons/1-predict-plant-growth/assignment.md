<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-24T22:03:30+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "ja"
}
-->
# Jupyter Notebookを使ったGDDデータの可視化

## 手順

このレッスンでは、IoTセンサーを使用してGDDデータを収集しました。良質なGDDデータを得るためには、複数日間のデータを収集する必要があります。温度データを可視化し、GDDを計算するために、[Jupyter Notebooks](https://jupyter.org)のようなツールを使用してデータを分析することができます。

まず、数日間のデータを収集してください。IoTデバイスが稼働している間、サーバーコードが常に動作していることを確認する必要があります。そのためには、電源管理設定を調整するか、[このシステムをアクティブに保つPythonスクリプト](https://github.com/jaqsparow/keep-system-active)のようなものを実行してください。

温度データを収集したら、このリポジトリ内のJupyter Notebookを使用してデータを可視化し、GDDを計算することができます。Jupyter Notebookは、コードと指示を*セル*と呼ばれるブロックに混在させる形式で構成されており、通常Pythonで記述されています。指示を読み、それぞれのコードブロックを順番に実行することができます。また、コードを編集することも可能です。このノートブックでは、例えば、植物のGDDを計算するために使用する基準温度を編集することができます。

1. `gdd-calculation`というフォルダーを作成してください。

1. [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb)ファイルをダウンロードし、`gdd-calculation`フォルダーにコピーしてください。

1. MQTTサーバーによって作成された`temperature.csv`ファイルをコピーしてください。

1. `gdd-calculation`フォルダー内に新しいPython仮想環境を作成してください。

1. Jupyter Notebook用のpipパッケージと、データの管理やプロットに必要なライブラリをインストールしてください：

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Jupyterでノートブックを実行してください：

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyterが起動し、ブラウザでノートブックが開きます。ノートブック内の指示に従って、測定された温度を可視化し、成長度日（GDD）を計算してください。

    ![Jupyter Notebookの画面](../../../../../translated_images/ja/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## 評価基準

| 基準 | 優秀 | 適切 | 改善が必要 |
| ---- | ---- | ---- | ---------- |
| データ収集 | 少なくとも2日分の完全なデータを収集 | 少なくとも1日分の完全なデータを収集 | 一部のデータを収集 |
| GDDの計算 | ノートブックを正常に実行し、GDDを計算 | ノートブックを正常に実行 | ノートブックを実行できない |

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は責任を負いません。