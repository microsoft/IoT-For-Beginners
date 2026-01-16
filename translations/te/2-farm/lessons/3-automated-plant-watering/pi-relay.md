<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2026-01-07T05:20:50+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "te"
}
-->
# Control a relay - Raspberry Pi

ఈ పాఠంలో, మీరు మీ Raspberry Piకి relay ని మరియు నేల ఆర్ద్రత సెన్సార్ తో పాటు జోడించి, నేల ఆర్ద్రత స్థాయిని ఆధారంగా దాన్ని నియంత్రించబోతున్నారు.

## హార్డ్వేర్

Raspberry Pi కి relay అవసరం.

మీరు ఉపయోగించబోయేది [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), ఇది సాధారణంగా-ఓపెన్ relay (అర్థం relay కి సిగ్నల్ పంపబడకుండా ఉన్నప్పుడు అవుట్పుట్ సర్క్యూట్ తెరచి ఉంటుంది లేదా కనెక్ట్ కాకపోతుంది) ఇది 250V మరియు 10A వరకు అవుట్పుట్ సర్క్యూట్లను నిర్వహించగలదు.

ఇది ఒక డిజిటల్ యాక్చుఏటర్, కనుక Grove Base Hat పై డిజిటల్ పిన్ కు కनेक్ట్ అవుతుంది.

### రీలేను కనెక్ట్ చేయండి

Grove relay ని Raspberry Piకి కనెక్ట్ చేయవచ్చు.

#### టాస్క్

రీలేను కనెక్ట్ చేయండి.

![A grove relay](../../../../../translated_images/te/grove-relay.d426958ca210fbd0.png)

1. Grove కేబుల్ యొక్క ఒక ముడి relay లో సాకెట్‌లోకి చొప్పించండి. అది ఒక దిక్కులో మాత్రమే సరిపోతుంది.

1. Raspberry Pi పవర్ ఆఫ్ చేసినప్పుడు, Grove కేబుల్ యొక్క మరొక ముడిని Pi కి కనెక్ట్ చేయబడిన Grove Base hat పై **D5** అనే డిజిటల్ సాకెట్ కి కనెక్ట్ చేయండి. ఈ సాకెట్ ఎడమ నుండి రెండవది, GPIO పిన్స్ సమీపంలో ఉన్న సాకెట్ల వరుసలో. నేల ఆర్ద్రత సెన్సార్ ఇంకా **A0** సాకెట్ కు కనెక్ట్ చేయబడింది.

![The grove relay connected to the D5 socket, and the soil moisture sensor connected to the A0 socket](../../../../../translated_images/te/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.png)

1. నేల ఆర్ద్రత సెన్సార్ నేలలో చొప్పించండి, గత పాఠం నుండి అది లేకపోతే.

## రీలేను ప్రోగ్రామ్ చేయండి

Raspberry Pi ఇప్పుడు జోడించిన relay ఉపయోగించట్లుగా ప్రోగ్రామ్ చేయవచ్చు.

### టాస్క్

పరికరాన్ని ప్రోగ్రామ్ చేయండి.

1. Pi ని పవర్ అప్ చేసి, బూట్ కావడానికి సమయం ఇవ్వండి

1. పాత పాఠం నుండి వున్న `soil-moisture-sensor` ప్రాజెక్ట్ ని VS Code లో తెరవండి, అది ఇంకా తెరవలేదంటే. మీరు ఈ ప్రాజెక్ట్‌కు కోడ్ జోడిస్తున్నాం.

1. ఈ క్రింది కోడ్ ను ఉన్న ఇంపోర్ట్ల కింద `app.py` ఫైల్లో జోడించండి:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    ఈ స్టేట్‌మెంట్ Grove Python లైబ్రరీలలోని `GroveRelay`ని దిగుమతి చేసుకుంటుంది, Grove relay తో ఇন্টারాక్ట్ కావడానికి.

1. `ADC` క్లాస్ డిక్లరేషన్ కింద క్రింది కోడ్ ని జోడించి `GroveRelay` ఇన్స్టాన్స్ సృష్టించండి:

    ```python
    relay = GroveRelay(5)
    ```

    ఇది మీరు కనెక్ట్ చేసిన డిజిటల్ పిన్ **D5** ఉపయోగించి relay ని సృష్టిస్తుంది.

1. relay పనిచేస్తున్నదో లేదో పరీక్షించడానికి, `while True:` లూప్ లో క్రింది కోడ్ జోడించండి:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    కోడ్ relay ని ఆన్ చేసి, 0.5 సెకన్ల పాటు వేచి, relay ని ఆఫ్ చేస్తుంది.

1. Python ఆప్‌ను రన్ చేయండి. relay ప్రతి 10 సెకన్లకు ఒకసారి ఆన్ మరియు ఆఫ్ అవుతుంది, ఆన్ మరియు ఆఫ్ చేయడము మధ్య సగం సెకన్ల ఆలస్యం ఉంటుంది. Relay ఆన్ అవుతుండగా క్లిక్ శబ్దం వినిపిస్తుంది, ఆన్ అవ్వగా Grove బోర్డ్ పై LED వెలిగుతుంది, ఆఫ్ అయినప్పుడు LED ఆపుతుంది.

    ![The relay turning on and off](../../../../../images/relay-turn-on-off.gif)

## నేల ఆర్ద్రత ఆధారంగా relay ని నియంత్రించండి

ఇప్పుడు relay పనిచేస్తున్నది, అది నేల ఆర్ద్రత చదువుల ఆధారంగా నియంత్రించవచ్చు.

### టాస్క్

relayని నియంత్రించండి.

1. relay ని పరీక్షించడానికి మీరు జోడించిన 3 కోడ్ లైన్లను తొలగించి, క్రింద ఇచ్చిన కోడ్ తో మార్చండి:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    ఈ కోడ్ నేల ఆర్ద్రత సెన్సార్ నుంచి నేల ఆర్ద్రత స్థాయిని చెక్ చేస్తుంది. ఇది 450 కంటే ఎక్కువైతే relay ఆన్ చేస్తుంది, 450 కంటే తక్కువైతే relay ఆఫ్ చేస్తుంది.

    > 💁 గుర్తుంచుకోండి capacitive soil moisture sensor కింది వివరణను చదివినప్పుడు నేల ఆర్ద్రత స్థాయి తక్కువైతే నేలలో తేమ ఎక్కువగా ఉంటుంది మరియు పిల్లోడ్ ఉంటే తేమ తక్కువగా ఉంటుంది.

1. Python ఆప్‌ను రన్ చేయండి. మీరు relay నీ ఆన్ లేదా ఆఫ్ అవుతున్న దాన్ని నేల ఆర్ద్రత స్థాయిని ఆధారంగా చూడగలరు. ఎండిన నేలలో ప్రయత్నించండి, తర్వాత నీరు జోడించండి.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 మీరు ఈ కోడ్ ని [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) ఫోల్డర్ లో కనుగొనవచ్చు.

😀 మీ నేల ఆర్ద్రత సెన్సార్ relayని నియంత్రించే ప్రోగ్రామ్ విజయవంతమయింది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**హ్నీతి నిరాకరణ**:  
ఈ పత్రం AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము సక్రమత కోసం ప్రయత్నిస్తున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాలలో పొరపాట్లు లేదా అసత్యతలు ఉండవచ్చు. మూల పత్రాన్ని దాని స్వదేశీ భాషలోనే అధికారిక మూలంగా పరిగణించాలి. ముఖ్యమైన సమాచారం కోసం, నైపుణ్యవంతులైన మానవ అనువాదాన్ని సూచిస్తాము. ఈ అనువాదం ఉపయోగంతో కలిగే ఏవైనా అవగాహన లోపాలు లేదా అవ్యాఖ్యానాల కోసం మేము బాధ్యుడం కావము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->