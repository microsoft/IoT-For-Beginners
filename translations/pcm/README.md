<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6c354ec3487e4f6cfafbe44557996cd9",
  "translation_date": "2026-01-07T00:59:22+00:00",
  "source_file": "README.md",
  "language_code": "pcm"
}
-->
### Join di Azure AI Foundry Community 

If you jam for corner or get any question about how to build AI apps, join other learners and experienced developers for discussions about MCP. E be supportive community wey questions dey welcome and knowledge dey share free.

If you get product feedback or errors as you dey build, visit:

Follow these steps to start to use all dis resources:
1. **Fork di Repository**: Click
2. **Clone di Repository**:   `git clone https://github.com/microsoft/IoT-For-Beginners.git`
3. [**Join di Microsoft Foundry Discord and meet experts and other developers**](https://discord.com/invite/ByRwuEEgH4)


### 🌐 Multi-Language Support

#### Supported via GitHub Action (Automated & Always Up-to-Date)

> **You fit prefer to Clone Locally?**

> Dis repository get 50+ language translations wey make di download size big. To clone without translations, use sparse checkout:
> ```bash
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone '/*' '!translations' '!translated_images'
> ```
> Dis go give you everything wey you need to finish di course with faster download.

# IoT for Beginners - A Curriculum

Azure Cloud Advocates for Microsoft happy to offer 12-week, 24-lesson curriculum about IoT basics. Each lesson get pre- and post-lesson quizzes, instructions to finish di lesson, solution, assignment and more. Our project-based teaching style dey let you learn as you dey build, na way wey dem don confirm say e dey help new skills stick.

Di projects cover how food journey from farm reach table. E cover farming, logistics, manufacturing, retail and consumer - all be popular IoT areas.

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click di image for bigger version.

**Big thanks to our authors [Jen Fox](https://github.com/jenfoxbot), [Jen Looper](https://github.com/jlooper), [Jim Bennett](https://github.com/jimbobbennett), and our sketchnote artist [Nitya Narasimhan](https://github.com/nitya).**

**Thanks also to our team of [Microsoft Learn Student Ambassadors](https://studentambassadors.microsoft.com?WT.mc_id=academic-17441-jabenn) wey don dey review and translate dis curriculum - [Aditya Garg](https://github.com/AdityaGarg00), [Anurag Sharma](https://github.com/Anurag-0-1-A), [Arpita Das](https://github.com/Arpiiitaaa), [Aryan Jain](https://www.linkedin.com/in/aryan-jain-47a4a1145/), [Bhavesh Suneja](https://github.com/EliteWarrior315), [Faith Hunja](https://faithhunja.github.io/), [Lateefah Bello](https://www.linkedin.com/in/lateefah-bello/), [Manvi Jha](https://github.com/Severus-Matthew), [Mireille Tan](https://www.linkedin.com/in/mireille-tan-a4834819a/), [Mohammad Iftekher (Iftu) Ebne Jalal](https://github.com/Iftu119), [Mohammad Zulfikar](https://github.com/mohzulfikar), [Priyanshu Srivastav](https://www.linkedin.com/in/priyanshu-srivastav-b067241ba), [Thanmai Gowducheruvu](https://github.com/innovation-platform), and [Zina Kamel](https://www.linkedin.com/in/zina-kamel/).**

Meet di team!

**Gif by** [Mohit Jaisal](https://linkedin.com/in/mohitjaisal)

> 🎥 Click di image above for video about di project!

> **Teachers**, we don [include some suggestions](for-teachers.md) on how to use dis curriculum. If you wan create your own lessons, we also get [lesson template](lesson-template/README.md).

> **[Students](https://aka.ms/student-page)**, to use dis curriculum by yourself, fork di whole repo and finish di exercises by yourself, start with pre-lecture quiz, then read di lecture and finish all activities. Try create di projects by understanding di lessons rather than just copy di solution code; but dat code dey for /solutions folders inside each project lesson. Another idea be to form study group with friends and go through di content together. For more learning, we recommend [Microsoft Learn](https://docs.microsoft.com/users/jimbobbennett/collections/ke2ehd351jopwr?WT.mc_id=academic-17441-jabenn).

For video overview of dis course, check dis video:

> 🎥 Click di image above for video about di project!

## Pedagogy

We choose two main teaching principles while building dis curriculum: make e project-based and make e get quizzes regularly. By di end of dis series, students go don build plant monitoring and watering system, vehicle tracker, smart factory setup to track and check food, and voice-controlled cooking timer, and go don learn di basics of Internet of Things including how to write device code, connect to cloud, analyze telemetry and run AI on di edge.

Making di content align with projects make di learning process dey more interesting for students and help dem remember concepts well.

Also, a small quiz before class dey set student mind for learning the topic, while second quiz after class go help further retention. Dis curriculum dey flexible and fun, you fit take all or part of am. Di projects start small and become more complex as di 12 week cycle end.

Each project based on real-world hardware wey students and hobbyists dey get. Each project focus on specific domain, give relevant background knowledge. To be a good developer, e good to sabi di domain where you dey solve problems, dis background knowledge dey help students think about their IoT solutions and how dem relate to real-world problems wey dem fit face as IoT developer. Students learn why dem dey build their solutions, and appreciate di end user.

## Hardware

We get two options of IoT hardware to use for di projects based on personal preference, programming language knowledge, learning goals and availability. We also provide 'virtual hardware' version for those wey no get hardware, or wan learn more before buying. You fit read more and find 'shopping list' for [hardware page](./hardware.md), plus links to buy complete kits from our friends at Seeed Studio.
> 💁 Find our [Code of Conduct](CODE_OF_CONDUCT.md), [Contributing](CONTRIBUTING.md), and [Translation](TRANSLATIONS.md) guidelines. We welcome your constructive feedback!
>
> 🔧 You get any wahala? Check our [Troubleshooting Guide](TROUBLESHOOTING.md) for how to solve common gbege dem.

## Each lesson get:

- sketchnote
- optional supplemental video
- pre-lesson warmup quiz
- written lesson
- for project-based lessons, step-by-step guides on how to build the project
- knowledge checks
- one challenge
- supplemental reading
- assignment
- [post-lesson quiz](https://ff-quizzes.netlify.app/en/)

> **One note about quizzes**: All quizzes dey for quiz-app folder, total na 48 quizzes each get three questions. Dem link from inside the lessons but you fit run the quiz app for your local machine or deploy am to Azure; just follow the instruction for `quiz-app` folder. Dem dey slowly dey localize.

## Lessons

|       |              Project Name              |                       Concepts Taught                       | Learning Objectives                                                                                                                                                 |                                                        Linked Lesson                                                         |
| :---: | :------------------------------------: | :---------------------------------------------------------: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------: |
|  01   | [Getting started](./1-getting-started/README.md) |                     Introduction to IoT                     | Learn the basic principles of IoT and the basic building blocks of IoT solutions like sensors and cloud services as you dey set up your first IoT device |                      [Introduction to IoT](./1-getting-started/lessons/1-introduction-to-iot/README.md)                      |
|  02   | [Getting started](./1-getting-started/README.md) |                   A deeper dive into IoT                    | Learn more about the parts wey make up IoT system, plus microcontrollers and single-board computers                                                            |                        [A deeper dive into IoT](./1-getting-started/lessons/2-deeper-dive/README.md)                         |
|  03   | [Getting started](./1-getting-started/README.md) | Interact with the physical world with sensors and actuators | Learn about sensors wey gather data from the physical world, and actuators wey dey give feedback, as you dey build one nightlight                                           | [Interact with the physical world with sensors and actuators](./1-getting-started/lessons/3-sensors-and-actuators/README.md) |
|  04   | [Getting started](./1-getting-started/README.md) |             Connect your device to the Internet             | Learn how to connect IoT device to Internet to send and receive messages by connecting your nightlight to one MQTT broker                               |               [Connect your device to the Internet](./1-getting-started/lessons/4-connect-internet/README.md)                |
|  05   |            [Farm](./2-farm/README.md)            |                    Predict plant growth                     | Learn how to predict plant growth using temperature data wey IoT device capture                                                                                  |                          [Predict plant growth](./2-farm/lessons/1-predict-plant-growth/README.md)                           |
|  06   |            [Farm](./2-farm/README.md)            |                    Detect soil moisture                     | Learn how to detect soil moisture and how to calibrate soil moisture sensor                                                                                              |                          [Detect soil moisture](./2-farm/lessons/2-detect-soil-moisture/README.md)                           |
|  07   |            [Farm](./2-farm/README.md)            |                  Automated plant watering                   | Learn how to automate and time watering using relay and MQTT                                                                                                      |                      [Automated plant watering](./2-farm/lessons/3-automated-plant-watering/README.md)                       |
|  08   |            [Farm](./2-farm/README.md)            |               Migrate your plant to the cloud               | Learn about cloud and cloud-hosted IoT services and how to connect your plant to one of these instead of public MQTT broker                                   |               [Migrate your plant to the cloud](./2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md)                |
|  09   |            [Farm](./2-farm/README.md)            |         Migrate your application logic to the cloud         | Learn how you fit write application logic for cloud that dey respond to IoT messages                                                                          |         [Migrate your application logic to the cloud](./2-farm/lessons/5-migrate-application-to-the-cloud/README.md)         |
|  10   |            [Farm](./2-farm/README.md)            |                   Keep your plant secure                    | Learn about IoT security and how to keep your plant secure with keys and certificates                                                                          |                        [Keep your plant secure](./2-farm/lessons/6-keep-your-plant-secure/README.md)                         |
|  11   |       [Transport](./3-transport/README.md)       |                      Location tracking                      | Learn about GPS location tracking for IoT devices                                                                                                                   |                           [Location tracking](./3-transport/lessons/1-location-tracking/README.md)                           |
|  12   |       [Transport](./3-transport/README.md)       |                     Store location data                     | Learn how to store IoT data so you fit view am or analyse am later                                                                                                      |                         [Store location data](./3-transport/lessons/2-store-location-data/README.md)                         |
|  13   |       [Transport](./3-transport/README.md)       |                   Visualize location data                   | Learn about how to show location data for map, and how maps dey show real 3D world for 2 dimensions                                                            |                     [Visualize location data](./3-transport/lessons/3-visualize-location-data/README.md)                     |
|  14   |       [Transport](./3-transport/README.md)       |                          Geofences                          | Learn about geofences, and how dem fit alert when vehicles wey dey supply chain dey near their destination                                           |                                   [Geofences](./3-transport/lessons/4-geofences/README.md)                                   |
|  15   |   [Manufacturing](./4-manufacturing/README.md)   |               Train a fruit quality detector                | Learn about how to train image classifier for cloud to detect fruit quality                                                                                       |                 [Train a fruit quality detector](./4-manufacturing/lessons/1-train-fruit-detector/README.md)                 |
|  16   |   [Manufacturing](./4-manufacturing/README.md)   |           Check fruit quality from an IoT device            | Learn how to use your fruit quality detector from IoT device                                                                                                    |           [Check fruit quality from an IoT device](./4-manufacturing/lessons/2-check-fruit-from-device/README.md)            |
|  17   |   [Manufacturing](./4-manufacturing/README.md)   |             Run your fruit detector on the edge             | Learn how to run fruit detector on IoT device for edge                                                                                                |             [Run your fruit detector on the edge](./4-manufacturing/lessons/3-run-fruit-detector-edge/README.md)             |
|  18   |   [Manufacturing](./4-manufacturing/README.md)   |        Trigger fruit quality detection from a sensor        | Learn how to trigger fruit quality detection from one sensor                                                                                                        |        [Trigger fruit quality detection from a sensor](./4-manufacturing/lessons/4-trigger-fruit-detector/README.md)         |
|  19   |          [Retail](./5-retail/README.md)          |                   Train a stock detector                    | Learn how to use object detection to train stock detector to count stock for shop                                                                                |                        [Train a stock detector](./5-retail/lessons/1-train-stock-detector/README.md)                         |
|  20   |          [Retail](./5-retail/README.md)          |               Check stock from an IoT device                | Learn how to check stock from IoT device using object detection model                                                                                         |                     [Check stock from an IoT device](./5-retail/lessons/2-check-stock-device/README.md)                      |
|  21   |        [Consumer](./6-consumer/README.md)        |             Recognize speech with an IoT device             | Learn how to recognize speech from IoT device to build smart timer                                                                                             |                  [Recognize speech with an IoT device](./6-consumer/lessons/1-speech-recognition/README.md)                  |
|  22   |        [Consumer](./6-consumer/README.md)        |                     Understand language                     | Learn how to understand sentences wey person talk to IoT device                                                                                                           |                        [Understand language](./6-consumer/lessons/2-language-understanding/README.md)                        |
|  23   |        [Consumer](./6-consumer/README.md)        |           Set a timer and provide spoken feedback           | Learn how to set timer for IoT device and give spoken feedback on when timer don set and when e done                                                    |                 [Set a timer and provide spoken feedback](./6-consumer/lessons/3-spoken-feedback/README.md)                  |
|  24   |        [Consumer](./6-consumer/README.md)        |                 Support multiple languages                  | Learn how to support many languages, both the ones wey dem speak to am and the answers from your smart timer                                                               |                   [Support multiple languages](./6-consumer/lessons/4-multiple-language-support/README.md)                   |

## Offline access

You fit run this documentation for offline mode by using [Docsify](https://docsify.js.org/#/). Fork this repo, [install Docsify](https://docsify.js.org/#/quickstart) for your local machine, then for root folder of this repo, type `docsify serve`. Website go dey serve for port 3000 for your localhost: `localhost:3000`.

## Quiz

Thanks to community for hosting interactive quiz wey dey test your knowledge for every chapter. You fit test your knowledge [here](https://ff-quizzes.netlify.app/en/) 

### PDF

You fit generate PDF of this content for offline use if you want. To do am, make sure say you get [npm installed](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) then run these commands for root folder of this repo:

```sh
npm i
npm run convert
```

### Slides

Some of the lessons get slide decks for the [slides](../../slides) folder.


## Other Curricula

Our team dey produce other curricula! Check am out:

<!-- CO-OP TRANSLATOR OTHER COURSES START -->
### LangChain
[![LangChain4j for Beginners](https://img.shields.io/badge/LangChain4j%20for%20Beginners-22C55E?style=for-the-badge&&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchain4j-for-beginners)
[![LangChain.js for Beginners](https://img.shields.io/badge/LangChain.js%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchainjs-for-beginners?WT.mc_id=m365-94501-dwahlin)

---

### Azure / Edge / MCP / Agents
[![AZD for Beginners](https://img.shields.io/badge/AZD%20for%20Beginners-0078D4?style=for-the-badge&labelColor=E5E7EB&color=0078D4)](https://github.com/microsoft/AZD-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Edge AI for Beginners](https://img.shields.io/badge/Edge%20AI%20for%20Beginners-00B8E4?style=for-the-badge&labelColor=E5E7EB&color=00B8E4)](https://github.com/microsoft/edgeai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![MCP for Beginners](https://img.shields.io/badge/MCP%20for%20Beginners-009688?style=for-the-badge&labelColor=E5E7EB&color=009688)](https://github.com/microsoft/mcp-for-beginners?WT.mc_id=academic-105485-koreyst)
[![AI Agents for Beginners](https://img.shields.io/badge/AI%20Agents%20for%20Beginners-00C49A?style=for-the-badge&labelColor=E5E7EB&color=00C49A)](https://github.com/microsoft/ai-agents-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Generative AI Series
[![Generative AI for Beginners](https://img.shields.io/badge/Generative%20AI%20for%20Beginners-8B5CF6?style=for-the-badge&labelColor=E5E7EB&color=8B5CF6)](https://github.com/microsoft/generative-ai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Generative AI (.NET)](https://img.shields.io/badge/Generative%20AI%20(.NET)-9333EA?style=for-the-badge&labelColor=E5E7EB&color=9333EA)](https://github.com/microsoft/Generative-AI-for-beginners-dotnet?WT.mc_id=academic-105485-koreyst)
[![Generative AI (Java)](https://img.shields.io/badge/Generative%20AI%20(Java)-C084FC?style=for-the-badge&labelColor=E5E7EB&color=C084FC)](https://github.com/microsoft/generative-ai-for-beginners-java?WT.mc_id=academic-105485-koreyst)
[![Generative AI (JavaScript)](https://img.shields.io/badge/Generative%20AI%20(JavaScript)-E879F9?style=for-the-badge&labelColor=E5E7EB&color=E879F9)](https://github.com/microsoft/generative-ai-with-javascript?WT.mc_id=academic-105485-koreyst)

---
 
### Core Learning
[![ML for Beginners](https://img.shields.io/badge/ML%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=22C55E)](https://aka.ms/ml-beginners?WT.mc_id=academic-105485-koreyst)
[![Data Science for Beginners](https://img.shields.io/badge/Data%20Science%20for%20Beginners-84CC16?style=for-the-badge&labelColor=E5E7EB&color=84CC16)](https://aka.ms/datascience-beginners?WT.mc_id=academic-105485-koreyst)
[![AI for Beginners](https://img.shields.io/badge/AI%20for%20Beginners-A3E635?style=for-the-badge&labelColor=E5E7EB&color=A3E635)](https://aka.ms/ai-beginners?WT.mc_id=academic-105485-koreyst)
[![Cybersecurity for Beginners](https://img.shields.io/badge/Cybersecurity%20for%20Beginners-F97316?style=for-the-badge&labelColor=E5E7EB&color=F97316)](https://github.com/microsoft/Security-101?WT.mc_id=academic-96948-sayoung)
[![Web Dev for Beginners](https://img.shields.io/badge/Web%20Dev%20for%20Beginners-EC4899?style=for-the-badge&labelColor=E5E7EB&color=EC4899)](https://aka.ms/webdev-beginners?WT.mc_id=academic-105485-koreyst)
[![IoT for Beginners](https://img.shields.io/badge/IoT%20for%20Beginners-14B8A6?style=for-the-badge&labelColor=E5E7EB&color=14B8A6)](https://aka.ms/iot-beginners?WT.mc_id=academic-105485-koreyst)
[![XR Development for Beginners](https://img.shields.io/badge/XR%20Development%20for%20Beginners-38BDF8?style=for-the-badge&labelColor=E5E7EB&color=38BDF8)](https://github.com/microsoft/xr-development-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Copilot Series
[![Copilot for AI Paired Programming](https://img.shields.io/badge/Copilot%20for%20AI%20Paired%20Programming-FACC15?style=for-the-badge&labelColor=E5E7EB&color=FACC15)](https://aka.ms/GitHubCopilotAI?WT.mc_id=academic-105485-koreyst)
[![Copilot for C#/.NET](https://img.shields.io/badge/Copilot%20for%20C%23/.NET-FBBF24?style=for-the-badge&labelColor=E5E7EB&color=FBBF24)](https://github.com/microsoft/mastering-github-copilot-for-dotnet-csharp-developers?WT.mc_id=academic-105485-koreyst)
[![Copilot Adventure](https://img.shields.io/badge/Copilot%20Adventure-FDE68A?style=for-the-badge&labelColor=E5E7EB&color=FDE68A)](https://github.com/microsoft/CopilotAdventures?WT.mc_id=academic-105485-koreyst)
<!-- CO-OP TRANSLATOR OTHER COURSES END -->

## Image attributions

You fit find all di attributions dem for di images wey dem use for dis curriculum where e dey needed for di [Attributions](./attributions.md).

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:
Dis document na AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) wey dem use translate am. Even tho we try make am correct, abeg sabi say automated translation fit get some mistakes or no too correct. Di original document wey e dey for im own language na di correct one for trust. If na serious information, e better make person wey sabi do proper translation do am. We no gree for any wrong understanding or wahala wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->