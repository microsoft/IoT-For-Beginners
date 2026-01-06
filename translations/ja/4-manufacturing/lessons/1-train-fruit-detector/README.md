<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-24T21:22:49+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "ja"
}
-->
# 果物の品質検出器を訓練する

![このレッスンの概要を示すスケッチノート](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.ja.jpg)

> スケッチノート作成者：[Nitya Narasimhan](https://github.com/nitya)。画像をクリックすると拡大版が表示されます。

このビデオでは、Azure Custom Vision サービスの概要を説明しています。このレッスンで取り上げる内容です。

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 上の画像をクリックしてビデオを視聴してください

## 講義前のクイズ

[講義前のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## はじめに

近年の人工知能（AI）や機械学習（ML）の進化により、今日の開発者に幅広い能力が提供されています。MLモデルは画像内のさまざまなものを認識するように訓練することができ、未熟な果物を認識することも可能です。これにより、IoTデバイスを使用して収穫中や工場や倉庫での処理中に農産物を仕分けることができます。

このレッスンでは、画像分類について学びます。MLモデルを使用して異なるものの画像を区別する方法です。良い果物と悪い果物（未熟、熟しすぎ、傷ついたもの、腐ったもの）を区別する画像分類器を訓練する方法を学びます。

このレッスンで取り上げる内容は以下の通りです：

* [AIとMLを使った食品の仕分け](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [機械学習による画像分類](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [画像分類器を訓練する](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [画像分類器をテストする](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [画像分類器を再訓練する](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## AIとMLを使った食品の仕分け

世界の人口を養うことは困難です。特に、すべての人が手頃な価格で食料を手に入れられるようにするには大変です。最大のコストの一つは労働力であり、農家は労働コストを削減するために自動化やIoTのようなツールにますます依存しています。手作業での収穫は労働集約的（そしてしばしば過酷な作業）であり、特に裕福な国々では機械による収穫に置き換えられています。機械を使用することで収穫コストは削減されますが、収穫中に食品を仕分ける能力が失われるという欠点があります。

すべての作物が均一に熟すわけではありません。例えばトマトは、大部分が収穫可能な状態になっていても、まだ緑色の果実が残っていることがあります。これらを早く収穫するのは無駄ですが、農家にとっては機械を使ってすべてを収穫し、未熟な作物を後で廃棄する方が安価で簡単です。

✅ 農場や庭、またはお店で育っているさまざまな果物や野菜を観察してみてください。それらはすべて同じ熟度ですか、それともばらつきがありますか？

自動収穫の普及により、農産物の仕分けは収穫から工場へと移行しました。食品は長いコンベアベルトで運ばれ、チームが品質基準を満たさないものを取り除く作業を行います。機械による収穫でコストは削減されましたが、食品を手作業で仕分けるコストは依然として存在しました。

![赤いトマトが検出されるとそのまま進み、緑のトマトが検出されるとレバーで廃棄箱に弾かれる](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.ja.png)

次の進化は、収穫機や加工工場に組み込まれた機械を使用して仕分けを行うことでした。これらの機械の第一世代は、光学センサーを使用して色を検出し、アクチュエーターを制御して緑のトマトをレバーや空気の噴射で廃棄箱に押し込み、赤いトマトをコンベアベルトのネットワークにそのまま流す仕組みでした。

このビデオでは、トマトが一つのコンベアベルトから別のベルトに落ちる際に、緑のトマトが検出され、レバーで廃棄箱に弾かれる様子が示されています。

✅ 工場や畑でこれらの光学センサーが正しく機能するためには、どのような条件が必要だと思いますか？

これらの仕分け機の最新の進化形は、AIとMLを活用しています。モデルを訓練して、緑のトマトと赤いトマトのような明らかな色の違いだけでなく、病気や傷を示す微妙な外観の違いを識別できるようにしています。

## 機械学習による画像分類

従来のプログラミングでは、データを取得し、そのデータにアルゴリズムを適用して出力を得ます。例えば、前回のプロジェクトでは、GPS座標とジオフェンスを取得し、Azure Mapsが提供するアルゴリズムを適用して、そのポイントがジオフェンス内か外かの結果を得ました。より多くのデータを入力すれば、より多くの出力が得られます。

![従来の開発では入力とアルゴリズムから出力を得る。機械学習では入力データと出力データを使ってモデルを訓練し、このモデルが新しい入力データから新しい出力を生成する](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.ja.png)

機械学習ではこれが逆になります。データと既知の出力から始め、機械学習アルゴリズムがデータから学習します。その後、この訓練されたアルゴリズム（*機械学習モデル*または*モデル*と呼ばれる）を使用して新しいデータを入力し、新しい出力を得ることができます。

> 🎓 機械学習アルゴリズムがデータから学習するプロセスを*訓練*と呼びます。入力データと既知の出力は*訓練データ*と呼ばれます。

例えば、未熟なバナナの写真を何百万枚もモデルに入力データとして与え、訓練出力を`未熟`と設定し、熟したバナナの写真を何百万枚も訓練データとして与え、出力を`熟した`と設定します。MLアルゴリズムはこのデータを基にモデルを作成します。その後、このモデルに新しいバナナの写真を与えると、その写真が熟しているか未熟であるかを予測します。

> 🎓 MLモデルの結果は*予測*と呼ばれます。

![2本のバナナ。熟したバナナは99.7%熟している、0.3%未熟という予測。未熟なバナナは1.4%熟している、98.6%未熟という予測](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.ja.png)

MLモデルは二択の答えを出すのではなく、確率を提供します。例えば、モデルがバナナの写真を与えられた場合、`熟している`が99.7%、`未熟`が0.3%と予測するかもしれません。コードは最も高い予測を選び、そのバナナが熟していると判断します。

画像を検出するために使用されるMLモデルは*画像分類器*と呼ばれます。ラベル付けされた画像を与えられ、それに基づいて新しい画像を分類します。

> 💁 これは簡略化した説明です。ラベル付けされた出力を必要としない教師なし学習など、他にも多くのモデル訓練方法があります。MLについてもっと学びたい場合は、[ML for beginners（機械学習の24レッスンカリキュラム）](https://aka.ms/ML-beginners)をチェックしてください。

## 画像分類器を訓練する

画像分類器を成功裏に訓練するには、何百万枚もの画像が必要です。しかし、何百万枚、何十億枚ものさまざまな画像で訓練された画像分類器があれば、それを再利用して少量の画像で再訓練し、優れた結果を得ることができます。このプロセスは*転移学習*と呼ばれます。

> 🎓 転移学習とは、既存のMLモデルの学習を新しいデータに基づいた新しいモデルに転移することです。

一度幅広い画像で訓練された画像分類器は、形状、色、パターンを認識する能力に優れています。転移学習により、画像の部分を認識する能力を活用して、新しい画像を認識することができます。

![形状を認識できれば、それらを組み合わせてボートや猫を作ることができる](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.ja.png)

これは、子供向けの形状絵本のようなものです。半円、長方形、三角形を認識できれば、それらの配置によって帆船や猫を認識できるようになります。画像分類器は形状を認識し、転移学習によって帆船や猫、あるいは熟したバナナを構成する組み合わせを学びます。

これを実現するためのツールは幅広く存在し、クラウドベースのサービスを利用してモデルを訓練し、Web APIを通じて使用することができます。

> 💁 これらのモデルを訓練するには大量の計算能力が必要です。通常はグラフィックス処理ユニット（GPU）を使用します。Xboxのゲームを美しく見せるための特殊なハードウェアは、機械学習モデルの訓練にも使用できます。クラウドを利用することで、これらのモデルを訓練するために必要な強力なコンピュータを時間単位で借りることができ、必要な計算能力を必要な時間だけ利用できます。

## Custom Vision

Custom Visionは、画像分類器を訓練するためのクラウドベースのツールです。少量の画像を使用して分類器を訓練することができます。画像をWebポータル、Web API、またはSDKを通じてアップロードし、各画像にその分類を示す*タグ*を付けます。その後、モデルを訓練し、どれだけうまく機能するかをテストします。モデルに満足したら、Web APIやSDKを通じてアクセス可能なバージョンを公開できます。

![Azure Custom Visionのロゴ](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.ja.png)

> 💁 Custom Visionモデルは、分類ごとに最低5枚の画像で訓練できますが、多い方が良いです。少なくとも30枚の画像があると、より良い結果が得られます。

Custom Visionは、MicrosoftのAIツール群であるCognitive Servicesの一部です。これらは、訓練なし、または少量の訓練で使用できるAIツールです。音声認識や翻訳、言語理解、画像分析などが含まれます。これらはAzureのサービスとして無料枠で利用可能です。

> 💁 無料枠は、モデルを作成し、訓練し、開発作業に使用するには十分です。無料枠の制限については、[Microsoft DocsのCustom Visionの制限とクォータのページ](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn)をご覧ください。

### タスク - Cognitive Servicesリソースを作成する

Custom Visionを使用するには、Azure CLIを使用してAzureに2つのCognitive Servicesリソースを作成する必要があります。1つはCustom Visionの訓練用、もう1つはCustom Visionの予測用です。

1. このプロジェクト用に`fruit-quality-detector`という名前のリソースグループを作成します。

1. 以下のコマンドを使用して、無料のCustom Vision訓練リソースを作成します：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>`をリソースグループを作成した場所に置き換えてください。

    これにより、リソースグループ内にCustom Vision訓練リソースが作成されます。このリソースは`fruit-quality-detector-training`と呼ばれ、無料枠である`F0`スキューを使用します。`--yes`オプションは、Cognitive Servicesの利用規約に同意することを意味します。

> 💁 すでにCognitive Servicesの無料アカウントを使用している場合は、`S0`スキューを使用してください。

1. 以下のコマンドを使用して、無料のCustom Vision予測リソースを作成します：

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>`をリソースグループを作成した場所に置き換えてください。

    これにより、リソースグループ内にCustom Vision予測リソースが作成されます。このリソースは`fruit-quality-detector-prediction`と呼ばれ、無料枠である`F0`スキューを使用します。`--yes`オプションは、Cognitive Servicesの利用規約に同意することを意味します。

### タスク - 画像分類器プロジェクトを作成する

1. [CustomVision.ai](https://customvision.ai)のCustom Visionポータルを開き、Azureアカウントで使用しているMicrosoftアカウントでサインインします。

1. [Microsoft Docsの画像分類器クイックスタートの新しいプロジェクト作成セクション](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project)に従って、新しいCustom Visionプロジェクトを作成します。UIは変更される可能性があるため、これらのドキュメントが常に最新の参考資料です。

    プロジェクト名を`fruit-quality-detector`とします。

    プロジェクトを作成する際、先ほど作成した`fruit-quality-detector-training`リソースを使用してください。*分類*プロジェクトタイプ、*マルチクラス*分類タイプ、*食品*ドメインを選択します。

    ![Custom Visionプロジェクトの設定。名前はfruit-quality-detector、説明なし、リソースはfruit-quality-detector-training、プロジェクトタイプは分類、分類タイプはマルチクラス、ドメインは食品](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.ja.png)

✅ 画像分類器のCustom Vision UIを探索する時間を取ってみてください。

### タスク - 画像分類器プロジェクトを訓練する

画像分類器を訓練するには、良い品質と悪い品質の果物の写真が複数必要です。例えば、熟したバナナと熟しすぎたバナナなどを良いと悪いとしてタグ付けします。
💁 これらの分類器は、どんなものの画像でも分類できます。そのため、品質の異なる果物が手元にない場合は、異なる種類の果物や、猫と犬を使うこともできます！
理想的には、各写真には果物だけが写っているべきです。背景は一貫性があるか、または多様性があるべきですが、熟しているか未熟であるかを特定するような背景は避けてください。

> 💁 特定の背景や分類対象に関連しないアイテムがタグごとに含まれていると、分類器が背景に基づいて分類してしまう可能性があります。例えば、皮膚がんの分類器が正常なほくろとがん性のほくろを学習した際、がん性のほくろにはサイズを測るための定規が写っていました。その結果、分類器はがん性のほくろではなく、写真内の定規をほぼ100%の精度で識別するようになってしまいました。

画像分類器は非常に低解像度で動作します。例えば、Custom Visionでは最大10240x10240のトレーニングおよび予測画像を使用できますが、モデルは227x227の画像でトレーニングおよび実行されます。大きな画像はこのサイズに縮小されるため、分類対象が画像の大部分を占めるようにしないと、分類器が使用する小さな画像では対象が小さすぎる可能性があります。

1. 分類器用の写真を集めます。各ラベルに対して少なくとも5枚の写真が必要ですが、多ければ多いほど良いです。また、分類器をテストするための追加の画像も必要です。これらの画像はすべて同じ対象の異なる画像であるべきです。例えば：

    * 熟したバナナ2本を使用し、それぞれを異なる角度から撮影して少なくとも7枚の写真を撮ります（5枚はトレーニング用、2枚はテスト用）。理想的にはもっと多く撮影してください。

        ![異なるバナナ2本の写真](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.ja.png)

    * 同じプロセスを未熟なバナナ2本でも繰り返します。

    少なくとも10枚のトレーニング画像（熟したもの5枚、未熟なもの5枚）と4枚のテスト画像（熟したもの2枚、未熟なもの2枚）が必要です。画像はpngまたはjpeg形式で、6MB以下であるべきです。例えばiPhoneで作成した場合、高解像度のHEIC画像になる可能性があるため、変換して縮小する必要があります。画像は多ければ多いほど良く、熟したものと未熟なものの数を均等にするべきです。

    熟した果物と未熟な果物の両方がない場合は、異なる果物や手元にある任意の2つの物体を使用できます。また、熟したバナナと未熟なバナナの例画像を[images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images)フォルダーで見つけることができます。

1. [Microsoft Docsの分類器クイックスタートの画像アップロードとタグ付けセクション](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images)に従い、トレーニング画像をアップロードします。熟した果物には`ripe`、未熟な果物には`unripe`というタグを付けます。

    ![熟したバナナと未熟なバナナの写真をアップロードするダイアログ](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.ja.png)

1. [Microsoft Docsの分類器クイックスタートの分類器をトレーニングするセクション](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier)に従い、アップロードした画像で画像分類器をトレーニングします。

    トレーニングタイプの選択肢が表示されます。**Quick Training**を選択してください。

分類器がトレーニングを開始します。トレーニングが完了するまで数分かかります。

> 🍌 分類器のトレーニング中に果物を食べる場合は、テスト用の画像が十分にあることを確認してください！

## 画像分類器をテストする

分類器がトレーニングされたら、新しい画像を与えて分類をテストすることができます。

### タスク - 画像分類器をテストする

1. [Microsoft Docsのモデルをテストするドキュメント](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model)に従い、画像分類器をテストします。以前に作成したテスト画像を使用し、トレーニングに使用した画像は使用しないでください。

    ![未熟なバナナが98.9%の確率で未熟、1.1%の確率で熟していると予測された結果](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.ja.png)

1. 利用可能なすべてのテスト画像を試し、確率を観察してください。

## 画像分類器を再トレーニングする

分類器をテストした際、期待した結果が得られない場合があります。画像分類器は、画像内の特定の特徴が特定のラベルに一致する確率に基づいて予測を行います。画像の内容を理解しているわけではなく、バナナが何であるかやバナナがボートではなくバナナである理由を理解しているわけではありません。分類器が間違った結果を出した画像を使用して再トレーニングすることで、分類器を改善することができます。

クイックテストオプションを使用して予測を行うたびに、画像と結果が保存されます。これらの画像を使用してモデルを再トレーニングすることができます。

### タスク - 画像分類器を再トレーニングする

1. [Microsoft Docsの予測画像をトレーニングに使用するドキュメント](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training)に従い、各画像に正しいタグを付けてモデルを再トレーニングします。

1. モデルを再トレーニングしたら、新しい画像でテストしてください。

---

## 🚀 チャレンジ

バナナでトレーニングされたモデルにイチゴの写真を使用したらどうなると思いますか？または、空気で膨らませたバナナ、バナナの衣装を着た人、さらには黄色いアニメキャラクター（例えばシンプソンズのキャラクター）を使用したらどうなるでしょうか？

試してみて、予測結果を確認してください。[Bing画像検索](https://www.bing.com/images/trending)を使用して試す画像を見つけることができます。

## 講義後のクイズ

[講義後のクイズ](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## レビューと自己学習

* 分類器をトレーニングした際、作成されたモデルを評価するための*Precision*、*Recall*、*AP*の値が表示されます。[Microsoft Docsの分類器クイックスタートの分類器を評価するセクション](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)を使用してこれらの値について調べてください。
* [Microsoft DocsのCustom Visionモデルを改善する方法](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)を読んで分類器を改善する方法について学んでください。

## 課題

[複数の果物や野菜の分類器をトレーニングする](assignment.md)

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当社は一切の責任を負いません。