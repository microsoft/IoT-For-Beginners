<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-11-18T19:01:12+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "pcm"
}
-->
# Build fruit quality detector

## Instructions

Make fruit quality detector!

Use wetin you don learn so far take build prototype fruit quality detector. Make image classification dey trigger based on how close e dey using AI model wey dey run for edge, store di classification result for storage, and control LED based on di fruit ripeness.

You suppose fit join all dis together using code wey you don write before for all di lessons wey don pass.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure all di services | Fit set up IoT Hub, Azure functions application and Azure storage | Fit set up IoT Hub, but no fit set up Azure functions app or Azure storage | No fit set up any internet IoT services |
| Monitor proximity and send di data go IoT Hub if object dey closer than di pre-defined distance and trigger di camera via command | Fit measure distance and send message go IoT Hub when object dey close enough, and send command to trigger di camera | Fit measure proximity and send go IoT Hub, but no fit send command go di camera | No fit measure distance and send message go IoT Hub, or trigger command |
| Capture image, classify am and send di results go IoT Hub | Fit capture image, classify am using edge device and send di results go IoT Hub | Fit classify di image but no use edge device, or no fit send di results go IoT Hub | No fit classify image |
| Turn di LED on or off based on di classification results using command wey dem send go device | Fit turn LED on via command if di fruit no ripe | Fit send di command go di device but no fit control di LED | No fit send command to control di LED |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make di transle-shon correct, abeg make you sabi say machine transle-shon fit get mistake or no dey accurate well. Di original dokyument wey dey for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->