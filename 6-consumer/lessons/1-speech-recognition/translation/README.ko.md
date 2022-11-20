# Recognize speech with an IoT device

![A sketchnote overview of this lesson](../../../sketchnotes/lesson-21.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This video gives an overview of the Azure speech service, a topic that will be covered in this lesson:

[![How to get started using your Cognitive Services Speech resource from the Microsoft Azure YouTube channel](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Click the image above to watch a video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Introduction

'Alexa, set a 12 minute timer'

'Alexa, timer status'

'Alexa, set a 8 minute timer called steam broccoli'

Smart devices are becoming more and more pervasive. Not just as smart speakers like HomePods, Echos and Google Homes, but embedded in our phones, watches, and even light fittings and thermostats.

> 💁 I have at least 19 devices in my home that have voice assistants, and that's just the ones I know about!

Voice control increases accessibility by allowing folks with limited movement to interact with devices. Whether it is a permanent disability such as being born without arms, to temporary disabilities such as broken arms, or having your hands full of shopping or young children, being able to control our houses from our voice instead of our hands opens up a world of access. Shouting 'Hey Siri, close my garage door' whilst dealing with a baby change and an unruly toddler can be a small but effective improvement on life.

One of the more popular uses for voice assistants is setting timers, especially kitchen timers. Being able to set multiple timers with just your voice is a great help in the kitchen - no need to stop kneading dough, stirring soup, or clean dumpling filling off your hands to use a physical timer.

In this lesson you will learn about building voice recognition into IoT devices. You'll learn about microphones as sensors, how to capture audio from a microphone attached to an IoT device, and how to use AI to convert what is heard into text. Throughout the rest of this project you will build a smart kitchen timer, able to set timers using your voice with multiple languages.

In this lesson we'll cover:

* [Microphones](#마이크)
* [Capture audio from your IoT device](#capture-audio-from-your-iot-device)
* [Speech to text](#speech-to-text)
* [Convert speech to text](#convert-speech-to-text)

## 마이크

마이크는 음파를 전기 신호로 변환하는 아날로그 센서입니다. 공기 중의 진동은 마이크의 구성 요소들을 아주 작은 양으로 움직이게 하고, 이것들은 전기 신호에 작은 변화를 일으킵니다. 이후 이러한 변화는 증폭되어 전기적 출력을 생성합니다.

### 마이크 유형

마이크는 다양한 종류가 있습니다.

* Dynamic - Dynamic 마이크에는 자석이 부착되어있어, 와이어 코일을 통해 움직이며 전류를 생성하는 움직이는 다이어프램이 있습니다. 이것은 대개 전류를 사용하여 와이어 코일에 있는 자석을 움직이는 확성기와는 반대로, 진동판을 움직여 소리를 생성합니다. 즉, 이것은 스피커가 Dynamic 마이크로 사용할 수 있고, dynamic 마이크를 스피커로 사용할 수 있음을 의미합니다. 사용자가 듣거나 말하는 intercom 같은 장치에서 스피커와 마이크의 역할을 동시에 수행할 수 있는 장치는 없습니다. 

    Dynamic 마이크는 작동하는데 전력이 필요하지 않으며, 전기 신호는 전적으로 마이크에서 생성됩니다.,

    ![Patti Smith singing into a Shure SM58 (dynamic cardioid type) microphone](../../../../images/dynamic-mic.jpg)

* Ribbon -Ribbon 마이크는 다이어프램 대신 금속 리본이 있다는 점을 제외하면 Dynamic 마이크와 유사합니다. 이 리본은 자기장에서 이동하며 전류를 생성합니다. Dynamic 마이크와 마찬가지로 리본 마이크는 전원이 필요하지 않습니다.

    ![Edmund Lowe, American actor, standing at radio microphone (labeled for (NBC) Blue Network), holding script, 1942](../../../../images/ribbon-mic.jpg)

* Condenser - Condenser 마이크는 얇은 금속 다이어프램과 고정 금속 백플레이트를 가지고 있습니다. 이 두 가지 모두에 전기가 적용되며 다이어프램이 진동함에 따라 플레이트 사이의 정전기가 변화하여 신호가 생성됩니다. 콘덴서 마이크가 작동하려면 *팬텀 전원*이 필요합니다.

    ![C451B small-diaphragm condenser microphone by AKG Acoustics](../../../../images/condenser-mic.jpg)

* MEMS - 마이크로 전기 기계 시스템 마이크, 또는 MEMS는 작은 칩에 있는 마이크입니다. 이들은 압력 감지 다이어프램을 실리콘 칩에 새기고, 콘덴서 마이크와 유사하게 작동합니다. 이 마이크들은 아주 작고 회로에 사용 될 수 있습니다.

    ![A MEMS microphone on a circuit board](../../../../images/mems-microphone.png)

    위 이미지에서 **LEFT**라고 표시된 칩은 MEMS 마이크이며 폭이 1mm 미만인 작은 다디어프램이 있습니다.
    
✅ 생각 해 봅시다 : 컴퓨터, 전화기, 헤드셋 또는 다른 전자기기에서는 어떠한 마이크를 가지고 있는지 조사 해 봅시다.

### Digital audio

오디오는 매우 미세한 정보를 전달하는 아날로그 신호입니다. 이 신호를 디지털로 변환하려면 오디오를 초당 수천번 샘플링 해야합니다.

> 🎓 샘플링이란 오디오 신호를 해당 지점의 신호를 나타내는 디지컬 값으로 변환하는 것 입니다.

![A line chart showing a signal, with discrete points at fixed intervals](../../../../images/sampling.png)

디지털 오디오는 펄스 코드 변조(Pulse Code Modulation, PCM)를 사용하여 샘플링 됩니다. PCM은 신호의 전압을 읽고 정의된 크기를 사용하여 해당 전압에 가장 가까운 이산 값을 선택하는 작업을 포함합니다.

> 💁 PCM은 펄스 폭 변조의 센서 버전 혹은 PWM(PWM은 [lesson 3 of the getting started project](../../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)에서 다룬 적 있습니다.). PCM은 아날로그 신호를 디지털 신호로 변환하고 PWM은 디지털 신호를 아날로그로 변환합니다.

예를 들어 대부분의 스트리밍 음악 서비스는 16비트 혹은 24비트 오디오를 제공합니다. 즉, 전압을 16비트 정수 또는 24비트 정수로 변환합니다. 16비트 오디오는 -32,768에서 32,767 사이의 숫자로 변환되고, 24비트는 -8,388,608에서 8,388,607 사이의 범위에 있습니다. 비트 수가 많을수록 샘플링 된 결과는 우리가 실제로 귀로 듣는 것과 유사해집니다.

> 💁 종종 LoFi라고 하는 하드 8비트 오디오를 사용할 때가 있습니다. 이것은 8비트만 사용하는 오디오 샘플링으로 범위는 -128에서 127까지입니다. 최초의 컴퓨터 오디오는 하드웨어의 한계로 인해 8비트로 제한되었기 때문에 이것은 레트로 게임에서 자주 볼 수 있습니다.

이러한 샘플은 KHz(초당 수천 개의 판독치) 단위로 잘 정의된 샘플 속도를 사용하여 초당 수천 번 수집됩니다. 스트리밍 음악 서비스는 대부분의 오디오에 48KHz를 사용하지만, 일부 `무손실` 오디오는 최대 96KHz 또는 심지어 192KHz를 사용합니다. 샘플링 속도가 높을수록 오디가 원본에 가깝습니다. 인간이 48KHz 이상의 차이를 구별할 수 있는지에 대한 논란이 있습니다.

✅ 생각 해 봅시다 : 스트리밍 음악 서비스를 사용한다면, 어떤 샘플링 정도와 크기를 사용하나요? CD를 사용할 경우 CD 오디오의 샘플링 비율과 크기는 어떻게 될까요?

오디오 데이터에는 여러가지 다른 형식이 있습니다. 음질을 잃지 않고 작게 만들기 위해서 만들어진 mp3 오디오 데이터에 대하여 들어본 적이 있을 것 입니다. 압축되지 않은 오디오는 종종 WAV 파일로 저장됩니다. 이 파일은 44 바이트릐 헤더 정보와 원시 오디오 데이터를 포합합니다. 헤더에는 샘플링 속도(예: 16KHz의 경우 16000), 샘플링 크기(16비트의 경우 16) 및 채널 수와 같은 정보가 포함됩니다.  WAV 파일의 헤더 뒤에 원시 오디오 데이터가 포함됩니다.

> 🎓 채널은 오디오를 구성하는 다양한 오디오 스트림 수를 나타냅니다. 예를 들어, 좌우 구분이 되는 스테레오 오디오의 경우 2개의 채널이 있습니다. 홈 시어터 시스템의 7.1 서라운드 사운드의 경우 8입니다.

### 오디오 

오디오 데이터는 상대적으로 큰 값을 가집니다. 압축되지 않은 16비트 오디오를 16KHz(스피치 대 텍스트 모델에서 사용하기에 충분한 속도)로 캡처하려면 오디오의 초당 32KB의 데이터가 필요합니다.

* 16비트는 샘플당 2바이트(1바이트는 8비트)를 의미합니다.
* 16KHz는 초당 16,000개의 샘플입니다.
* 16,000 x 2바이트 = 32,000 bytes/sec.

적은 양의 데이터처럼 느껴질 수 있지만 메모리가 제한된 마이크로 컨트롤러를 사용하는 경우 데이터가 훨씬 더 많게 느껴질 수 있습니다.  예를 들어, Wio Terminal은 192KB의 메모리를 가지고 있으며 프로그램 코드와 변수를 저장해야 합니다. 프로그램 코드의 길이가 짧더라도 5초 이상의 오디오를 캡쳐할 수 없습니다.

마이크로컨트롤러는 SD 카드나 플래시 메모리와 같은 추가 저장소에 액세스할 수 있습니다. 오디오를 캡처하는 IoT 장치를 구축할 때는 추가 저장소가 있어야 할 뿐만 아니라 코드가 마이크에서 캡처한 오디오를 해당 저장소에 직접 기록하고 클라우드로 전송할 때 저장소에서 웹 요청으로 스트리밍해야 합니다. 이렇게 하면 한 번에 전체적인 오디오 데이터 블록을 메모리에 저장하여 메모리 lack을 방지할 수 있습니다.

## Capture audio from your IoT device

Your IoT device can be connected to a microphone to capture audio, ready for conversion to text. It can also be connected to speakers to output audio. In later lessons this will be used to give audio feedback, but it is useful to set up speakers now to test the microphone.

### Task - configure your microphone and speakers

Work through the relevant guide to configure the microphone and speakers for your IoT device:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Single-board computer - Raspberry Pi](pi-microphone.md)
* [Single-board computer - Virtual device](virtual-device-microphone.md)

### Task - capture audio

Work through the relevant guide to capture audio on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Single-board computer - Raspberry Pi](pi-audio.md)
* [Single-board computer - Virtual device](virtual-device-audio.md)

## Speech to text

Speech to text, or speech recognition, involves using AI to convert words in an audio signal to text.

### Speech recognition models

To convert speech to text, samples from the audio signal are grouped together and fed into a machine learning model based around a Recurrent Neural network (RNN). This is a type of machine learning model that can use previous data to make a decision about incoming data. For example, the RNN could detect one block of audio samples as the sound 'Hel', and when it receives another that it thinks is the sound 'lo', it can combine this with the previous sound, find that 'Hello' is a valid word and select that as the outcome.

ML models always accept data of the same size every time. The image classifier you built in an earlier lesson resizes images to a fixed size and processes them. The same with speech models, they have to process fixed sized audio chunks. The speech models need to be able to combine the outputs of multiple predictions to get the answer, to allow it to distinguish between 'Hi' and 'Highway', or 'flock' and 'floccinaucinihilipilification'.

Speech models are also advanced enough to understand context, and can correct the words they detect as more sounds are processed. For example, if you say "I went to the shops to get two bananas and an apple too", you would use three words that sound the same, but are spelled differently - to, two and too. Speech models are able to understand the context and use the appropriate spelling of the word.

> 💁 Some speech services allow customization to make them work better in noisy environments such as factories, or with industry-specific words such as chemical names. These customizations are trained by providing sample audio and a transcription, and work using transfer learning, the same as how you trained an image classifier using only a few images in an earlier lesson.

### Privacy

When using speech to text in a consumer IoT device, privacy is incredibly important. These devices listen to audio continuously, so as a consumer you don't want everything you say being sent to the cloud and converted to text. Not only will this use a lot of Internet bandwidth, it also has massive privacy implications, especially when some smart device makers randomly select audio for [humans to validate against the text generated to help improve their model](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

You only want your smart device to send audio to the cloud for processing when you are using it, not when it hears audio in your home, audio that could include private meetings or intimate interactions. The way most smart devices work is with a *wake word*, a key phrase such as "Alexa", "Hey Siri", or "OK Google" that causes the device to 'wake up' and listen to what you are saying up until it detects a break in your speech, indicating you have finished talking to the device.

> 🎓 Wake word detection is also referred to as *Keyword spotting* or *Keyword recognition*.

These wake words are detected on the device, not in the cloud. These smart devices have small AI models that run on the device that listen for the wake work, and when it is detected, start streaming the audio to the cloud for recognition. These models are very specialized, and just listen for the wake word.

> 💁 Some tech companies are adding more privacy to their devices and doing some of the speech to text conversion on the device. Apple have announced that as part of their 2021 iOS and macOS updates they will support the speech to text conversion on device, and be able to handle many requests without needing to use the cloud. This is thanks to having powerful processors in their devices that can run ML models.

✅ What do you think are the privacy and ethical implications of storing the audio sent to the cloud? Should this audio be stored, and if so, how? Do you thing the use of recordings for law enforcement is a good trade off for the loss of privacy?

Wake word detection usually uses a technique know an TinyML, that is converting ML models to be able to run on microcontrollers. These models are small in size, and consume very little power to run.

To avoid the complexity of training and using a wake word model, the smart timer you are building in this lesson will use a button to turn on the speech recognition.

> 💁 If you want to try creating a wake word detection model to run on the Wio Terminal or Raspberry Pi, check out this [responding to your voice tutorial by Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). If you want to use your computer to do this, you can try the [get started with Custom Keyword quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Convert speech to text

![Speech services logo](../../../images/azure-speech-logo.png)

Just like with image classification in an earlier project, there are pre-built AI services that can take speech as an audio file and convert it to text. Once such service is the Speech Service, part of the Cognitive Services, pre-built AI services you can use in your apps.

### Task - configure a speech AI resource

1. Create a Resource Group for this project called `smart-timer`

1. Use the following command to create a free speech resource:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

1. You will need an API key to access the speech resource from your code. Run the following command to get the key:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Take a copy of one of the keys.

### Task - convert speech to text

Work through the relevant guide to convert speech to text on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Single-board computer - Raspberry Pi](pi-speech-to-text.md)
* [Single-board computer - Virtual device](virtual-device-speech-to-text.md)

---

## 🚀 Challenge

Speech recognition has been around for a long time, and is continuously improving. Research the current capabilities and compare how these have evolved over time, including how accurate machine transcriptions are compared to human.

What do you think the future holds for speech recognition?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Review & Self Study

* Read about the different microphone types and how they work on the [what's the difference between dynamic and condenser microphones article on Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Read more on the Cognitive Services speech service on the [speech service documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn)
* Read about keyword spotting on the [keyword recognition documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn)

## Assignment

[](assignment.md)
