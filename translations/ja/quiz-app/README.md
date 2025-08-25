<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-25T01:09:33+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "ja"
}
-->
# クイズ

これらのクイズは、https://aka.ms/iot-beginners にある IoT for Beginners カリキュラムの講義前後のクイズです。

## プロジェクトセットアップ

```
npm install
```

### 開発用のコンパイルとホットリロード

```
npm run serve
```

### 本番用のコンパイルと最小化

```
npm run build
```

### ファイルのリントと修正

```
npm run lint
```

### 設定のカスタマイズ

[Configuration Reference](https://cli.vuejs.org/config/) を参照してください。

クレジット: このクイズアプリのオリジナルバージョンを作成してくれた https://github.com/arpan45/simple-quiz-vue に感謝します。


## Azure へのデプロイ

以下は、始めるためのステップバイステップガイドです：

1. GitHub リポジトリをフォークする  
静的ウェブアプリのコードを GitHub リポジトリに用意してください。このリポジトリをフォークします。

2. Azure Static Web App を作成する  
- [Azure アカウント](http://azure.microsoft.com) を作成します。  
- [Azure ポータル](https://portal.azure.com) にアクセスします。  
- 「リソースの作成」をクリックし、「Static Web App」を検索します。  
- 「作成」をクリックします。

3. Static Web App を構成する  
- #### 基本設定:  
  - サブスクリプション: 使用する Azure サブスクリプションを選択します。  
  - リソースグループ: 新しいリソースグループを作成するか、既存のものを使用します。  
  - 名前: 静的ウェブアプリの名前を入力します。  
  - リージョン: ユーザーに最も近いリージョンを選択します。

- #### デプロイの詳細:  
  - ソース: 「GitHub」を選択します。  
  - GitHub アカウント: Azure に GitHub アカウントへのアクセスを許可します。  
  - 組織: GitHub の組織を選択します。  
  - リポジトリ: 静的ウェブアプリを含むリポジトリを選択します。  
  - ブランチ: デプロイ元のブランチを選択します。

- #### ビルドの詳細:  
  - ビルドプリセット: アプリが構築されているフレームワークを選択します（例: React、Angular、Vue など）。  
  - アプリの場所: アプリコードが含まれるフォルダを指定します（例: ルートにある場合は /）。  
  - API の場所: API がある場合、その場所を指定します（オプション）。  
  - 出力の場所: ビルド出力が生成されるフォルダを指定します（例: build または dist）。

4. 設定の確認と作成  
設定を確認し、「作成」をクリックします。Azure が必要なリソースを設定し、GitHub Actions ワークフローをリポジトリに作成します。

5. GitHub Actions ワークフロー  
Azure はリポジトリ内に自動的に GitHub Actions ワークフロー ファイル (.github/workflows/azure-static-web-apps-<name>.yml) を作成します。このワークフローがビルドとデプロイのプロセスを処理します。

6. デプロイの監視  
GitHub リポジトリの「Actions」タブに移動します。  
ワークフローが実行中であることが確認できます。このワークフローは静的ウェブアプリを Azure にビルドしてデプロイします。  
ワークフローが完了すると、提供された Azure URL でアプリが公開されます。

### ワークフローファイルの例

以下は、GitHub Actions ワークフローファイルの例です：  
name: Azure Static Web Apps CI/CD  
```
on:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches:
      - main

jobs:
  build_and_deploy_job:
    runs-on: ubuntu-latest
    name: Build and Deploy Job
    steps:
      - uses: actions/checkout@v2
      - name: Build And Deploy
        id: builddeploy
        uses: Azure/static-web-apps-deploy@v1
        with:
          azure_static_web_apps_api_token: ${{ secrets.AZURE_STATIC_WEB_APPS_API_TOKEN }}
          repo_token: ${{ secrets.GITHUB_TOKEN }}
          action: "upload"
          app_location: "quiz-app" #App source code path
          api_location: ""API source code path optional
          output_location: "dist" #Built app content directory - optional
```

### 追加リソース
- [Azure Static Web Apps ドキュメント](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions ドキュメント](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。