# ਆਪਣੇ ਫਲ ਡਿਟੈਕਟਰ ਨੂੰ ਐਜ 'ਤੇ ਚਲਾਓ

![ਇਸ ਪਾਠ ਦਾ ਇੱਕ ਸਕੈਚਨੋਟ ਝਲਕ](../../../../../translated_images/pa/lesson-17.bc333c3c35ba8e42.webp)

> ਸਕੈਚਨੋਟ [ਨਿਤਿਆ ਨਰਸਿੰਮਨ](https://github.com/nitya) ਦੁਆਰਾ। ਵੱਡੇ ਵਰਜਨ ਲਈ ਚਿੱਤਰ 'ਤੇ ਕਲਿਕ ਕਰੋ।

ਇਹ ਵੀਡੀਓ IoT ਡਿਵਾਈਸਾਂ 'ਤੇ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਚਲਾਉਣ ਦੀ ਝਲਕ ਦਿੰਦੀ ਹੈ, ਜੋ ਕਿ ਇਸ ਪਾਠ ਵਿੱਚ ਕਵਰ ਕੀਤਾ ਗਿਆ ਹੈ।

[![Azure IoT Edge 'ਤੇ Custom Vision AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## ਪਾਠ ਤੋਂ ਪਹਿਲਾਂ ਕਵੀਜ਼

[ਪਾਠ ਤੋਂ ਪਹਿਲਾਂ ਕਵੀਜ਼](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## ਪਰਿਚਯ

ਪਿਛਲੇ ਪਾਠ ਵਿੱਚ ਤੁਸੀਂ ਆਪਣੇ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਪੱਕੇ ਅਤੇ ਕੱਚੇ ਫਲਾਂ ਦੀ ਪਛਾਣ ਕੀਤੀ ਸੀ, ਜਿਸ ਵਿੱਚ IoT ਡਿਵਾਈਸ ਦੇ ਕੈਮਰੇ ਦੁਆਰਾ ਕੈਪਚਰ ਕੀਤੀ ਗਈ ਚਿੱਤਰ ਨੂੰ ਕਲਾਉਡ ਸਰਵਿਸ ਨੂੰ ਭੇਜਿਆ ਗਿਆ ਸੀ। ਇਹ ਕਾਲਾਂ ਸਮਾਂ ਲੈਂਦੀਆਂ ਹਨ, ਪੈਸਾ ਖਰਚ ਹੁੰਦਾ ਹੈ, ਅਤੇ ਜਿਹੜੇ ਤਸਵੀਰ ਡਾਟਾ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾ ਰਹੀ ਹੈ, ਉਸ ਦੇ ਆਧਾਰ 'ਤੇ ਗੋਪਨੀਯਤਾ ਦੇ ਮਸਲੇ ਹੋ ਸਕਦੇ ਹਨ।

ਇਸ ਪਾਠ ਵਿੱਚ ਤੁਸੀਂ ਸਿੱਖੋਗੇ ਕਿ ਕਿਵੇਂ ਮਸ਼ੀਨ ਲਰਨਿੰਗ (ML) ਮਾਡਲਾਂ ਨੂੰ ਐਜ 'ਤੇ ਚਲਾਇਆ ਜਾ ਸਕਦਾ ਹੈ - ਆਪਣੇ ਨੈੱਟਵਰਕ 'ਤੇ ਚੱਲ ਰਹੇ IoT ਡਿਵਾਈਸਾਂ 'ਤੇ, ਕਲਾਉਡ ਦੀ ਬਜਾਏ। ਤੁਸੀਂ ਐਜ ਕੰਪਿਊਟਿੰਗ ਅਤੇ ਕਲਾਉਡ ਕੰਪਿਊਟਿੰਗ ਦੇ ਫਾਇਦੇ ਅਤੇ ਨੁਕਸਾਨਾਂ ਬਾਰੇ ਸਿੱਖੋਗੇ, ਆਪਣੇ AI ਮਾਡਲ ਨੂੰ ਐਜ 'ਤੇ ਕਿਵੇਂ ਡਿਪਲੌਇ ਕਰਨਾ ਹੈ, ਅਤੇ ਇਸ ਨੂੰ ਆਪਣੇ IoT ਡਿਵਾਈਸ ਤੋਂ ਕਿਵੇਂ ਐਕਸੈਸ ਕਰਨਾ ਹੈ।

ਇਸ ਪਾਠ ਵਿੱਚ ਅਸੀਂ ਕਵਰ ਕਰਾਂਗੇ:

* [ਐਜ ਕੰਪਿਊਟਿੰਗ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge ਡਿਵਾਈਸ ਰਜਿਸਟਰ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge ਡਿਵਾਈਸ ਸੈਟਅੱਪ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ਆਪਣਾ ਮਾਡਲ ਐਕਸਪੋਰਟ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ਡਿਪਲੌਇਮੈਂਟ ਲਈ ਆਪਣੇ ਕੰਟੇਨਰ ਦੀ ਤਿਆਰੀ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ਆਪਣਾ ਕੰਟੇਨਰ ਡਿਪਲੌਇ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [ਆਪਣੇ IoT Edge ਡਿਵਾਈਸ ਦੀ ਵਰਤੋਂ ਕਰੋ](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## ਐਜ ਕੰਪਿਊਟਿੰਗ

ਐਜ ਕੰਪਿਊਟਿੰਗ ਦਾ ਮਤਲਬ ਹੈ ਕਿ IoT ਡਾਟਾ ਨੂੰ ਜਿੱਥੇ ਇਹ ਜਨਰੇਟ ਹੁੰਦਾ ਹੈ, ਉਸ ਦੇ ਸਭ ਤੋਂ ਨੇੜੇ ਕੰਪਿਊਟਰਾਂ ਦੁਆਰਾ ਪ੍ਰੋਸੈਸ ਕੀਤਾ ਜਾਵੇ। ਇਸ ਪ੍ਰੋਸੈਸਿੰਗ ਨੂੰ ਕਲਾਉਡ ਵਿੱਚ ਕਰਨ ਦੀ ਬਜਾਏ, ਇਸਨੂੰ ਕਲਾਉਡ ਦੇ ਐਜ 'ਤੇ - ਤੁਹਾਡੇ ਅੰਦਰੂਨੀ ਨੈੱਟਵਰਕ 'ਤੇ ਲਿਆਂਦਾ ਜਾਂਦਾ ਹੈ।

![ਇੱਕ ਆਰਕੀਟੈਕਚਰ ਡਾਇਗ੍ਰਾਮ ਜੋ ਕਲਾਉਡ ਵਿੱਚ ਇੰਟਰਨੈੱਟ ਸਰਵਿਸਾਂ ਅਤੇ ਇੱਕ ਸਥਾਨਕ ਨੈੱਟਵਰਕ 'ਤੇ IoT ਡਿਵਾਈਸਾਂ ਨੂੰ ਦਿਖਾਉਂਦਾ ਹੈ](../../../../../translated_images/pa/cloud-without-edge.b4da641f6022c95e.webp)

ਹੁਣ ਤੱਕ ਦੇ ਪਾਠਾਂ ਵਿੱਚ, ਤੁਸੀਂ ਡਿਵਾਈਸਾਂ ਨੂੰ ਡਾਟਾ ਇਕੱਠਾ ਕਰਦੇ ਅਤੇ ਕਲਾਉਡ ਨੂੰ ਭੇਜਦੇ ਦੇਖਿਆ ਹੈ, ਜਿੱਥੇ ਇਹ ਡਾਟਾ ਸਰਵਰਲੈੱਸ ਫੰਕਸ਼ਨ ਜਾਂ AI ਮਾਡਲਾਂ ਦੁਆਰਾ ਵਿਸ਼ਲੇਸ਼ਣ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

![ਇੱਕ ਆਰਕੀਟੈਕਚਰ ਡਾਇਗ੍ਰਾਮ ਜੋ ਸਥਾਨਕ ਨੈੱਟਵਰਕ 'ਤੇ IoT ਡਿਵਾਈਸਾਂ ਨੂੰ ਐਜ ਡਿਵਾਈਸਾਂ ਨਾਲ ਜੁੜਦਾ ਦਿਖਾਉਂਦਾ ਹੈ, ਅਤੇ ਉਹ ਐਜ ਡਿਵਾਈਸ ਕਲਾਉਡ ਨਾਲ ਜੁੜਦੇ ਹਨ](../../../../../translated_images/pa/cloud-with-edge.1e26462c62c126fe.webp)

ਐਜ ਕੰਪਿਊਟਿੰਗ ਵਿੱਚ ਕੁਝ ਕਲਾਉਡ ਸਰਵਿਸਾਂ ਨੂੰ ਕਲਾਉਡ ਤੋਂ ਹਟਾ ਕੇ IoT ਡਿਵਾਈਸਾਂ ਦੇ ਨੈੱਟਵਰਕ 'ਤੇ ਚੱਲ ਰਹੇ ਕੰਪਿਊਟਰਾਂ 'ਤੇ ਲਿਆਂਦਾ ਜਾਂਦਾ ਹੈ, ਅਤੇ ਸਿਰਫ਼ ਜਰੂਰਤ ਪੈਣ 'ਤੇ ਹੀ ਕਲਾਉਡ ਨਾਲ ਸੰਚਾਰ ਕੀਤਾ ਜਾਂਦਾ ਹੈ। ਉਦਾਹਰਣ ਵਜੋਂ, ਤੁਸੀਂ ਐਜ ਡਿਵਾਈਸਾਂ 'ਤੇ AI ਮਾਡਲ ਚਲਾ ਸਕਦੇ ਹੋ ਜੋ ਫਲਾਂ ਦੀ ਪੱਕਣ ਦੀ ਜਾਂਚ ਕਰਦੇ ਹਨ, ਅਤੇ ਸਿਰਫ਼ ਵਿਸ਼ਲੇਸ਼ਣ ਨੂੰ ਕਲਾਉਡ 'ਤੇ ਭੇਜਦੇ ਹਨ, ਜਿਵੇਂ ਕਿ ਪੱਕੇ ਅਤੇ ਕੱਚੇ ਫਲਾਂ ਦੀ ਗਿਣਤੀ।

✅ ਸੋਚੋ ਕਿ ਤੁਸੀਂ ਹੁਣ ਤੱਕ ਜੋ IoT ਐਪਲੀਕੇਸ਼ਨ ਬਣਾਈਆਂ ਹਨ, ਉਹਨਾਂ ਵਿੱਚੋਂ ਕਿਹੜੇ ਹਿੱਸੇ ਐਜ 'ਤੇ ਲਿਆਂਦੇ ਜਾ ਸਕਦੇ ਹਨ।

### ਫਾਇਦੇ

ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੇ ਫਾਇਦੇ ਹਨ:

1. **ਗਤੀ** - ਐਜ ਕੰਪਿਊਟਿੰਗ ਸਮੇਂ ਸੰਵੇਦਨਸ਼ੀਲ ਡਾਟਾ ਲਈ ਆਦਰਸ਼ ਹੈ ਕਿਉਂਕਿ ਕਾਰਵਾਈਆਂ ਡਿਵਾਈਸ ਦੇ ਨੈੱਟਵਰਕ 'ਤੇ ਹੀ ਕੀਤੀਆਂ ਜਾਂਦੀਆਂ ਹਨ, ਇੰਟਰਨੈੱਟ 'ਤੇ ਕਾਲਾਂ ਕਰਨ ਦੀ ਲੋੜ ਨਹੀਂ ਹੁੰਦੀ। ਇਸ ਨਾਲ ਤੇਜ਼ ਗਤੀ ਸੰਭਵ ਹੁੰਦੀ ਹੈ ਕਿਉਂਕਿ ਅੰਦਰੂਨੀ ਨੈੱਟਵਰਕ ਇੰਟਰਨੈੱਟ ਕਨੈਕਸ਼ਨਾਂ ਨਾਲੋਂ ਕਾਫ਼ੀ ਤੇਜ਼ ਚੱਲ ਸਕਦੇ ਹਨ, ਅਤੇ ਡਾਟਾ ਨੂੰ ਛੋਟੇ ਦੂਰੀ 'ਤੇ ਯਾਤਰਾ ਕਰਨੀ ਪੈਂਦੀ ਹੈ।

    > 💁 ਹਾਲਾਂਕਿ ਇੰਟਰਨੈੱਟ ਕਨੈਕਸ਼ਨਾਂ ਲਈ ਆਪਟੀਕਲ ਕੇਬਲ ਵਰਤੇ ਜਾਂਦੇ ਹਨ ਜੋ ਡਾਟਾ ਨੂੰ ਰੌਸ਼ਨੀ ਦੀ ਗਤੀ ਨਾਲ ਯਾਤਰਾ ਕਰਨ ਦੇ ਯੋਗ ਬਣਾਉਂਦੇ ਹਨ, ਡਾਟਾ ਨੂੰ ਦੁਨੀਆ ਭਰ ਵਿੱਚ ਕਲਾਉਡ ਪ੍ਰੋਵਾਈਡਰਾਂ ਤੱਕ ਪਹੁੰਚਣ ਵਿੱਚ ਸਮਾਂ ਲੱਗਦਾ ਹੈ। ਉਦਾਹਰਣ ਵਜੋਂ, ਜੇ ਤੁਸੀਂ ਯੂਰਪ ਤੋਂ ਅਮਰੀਕਾ ਵਿੱਚ ਕਲਾਉਡ ਸਰਵਿਸਾਂ ਨੂੰ ਡਾਟਾ ਭੇਜ ਰਹੇ ਹੋ, ਤਾਂ ਆਪਟੀਕਲ ਕੇਬਲ ਵਿੱਚ ਡਾਟਾ ਨੂੰ ਐਟਲਾਂਟਿਕ ਪਾਰ ਕਰਨ ਵਿੱਚ ਘੱਟੋ-ਘੱਟ 28ms ਲੱਗਦੇ ਹਨ, ਅਤੇ ਇਹ ਸਮਾਂ ਡਾਟਾ ਨੂੰ ਟਰਾਂਸਐਟਲਾਂਟਿਕ ਕੇਬਲ ਤੱਕ ਪਹੁੰਚਾਉਣ, ਇਲੈਕਟ੍ਰਿਕਲ ਤੋਂ ਰੌਸ਼ਨੀ ਸਿਗਨਲਾਂ ਵਿੱਚ ਬਦਲਣ ਅਤੇ ਵਾਪਸ ਬਦਲਣ ਦੇ ਸਮੇਂ ਤੋਂ ਇਲਾਵਾ ਹੈ।

    ਐਜ ਕੰਪਿਊਟਿੰਗ ਵਿੱਚ ਘੱਟ ਨੈੱਟਵਰਕ ਟ੍ਰੈਫਿਕ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਜਿਸ ਨਾਲ ਇੰਟਰਨੈੱਟ ਕਨੈਕਸ਼ਨ ਲਈ ਉਪਲਬਧ ਸੀਮਤ ਬੈਂਡਵਿਡਥ ਦੇ ਭਾਰ ਦੇ ਕਾਰਨ ਡਾਟਾ ਦੇ ਹੌਲੀ ਹੋਣ ਦੇ ਖਤਰੇ ਨੂੰ ਘਟਾਇਆ ਜਾ ਸਕਦਾ ਹੈ।

1. **ਦੂਰ-ਦੁਰਸਤ ਪਹੁੰਚਯੋਗਤਾ** - ਜਦੋਂ ਤੁਹਾਡੇ ਕੋਲ ਸੀਮਤ ਜਾਂ ਕੋਈ ਕਨੈਕਟਿਵਿਟੀ ਨਹੀਂ ਹੁੰਦੀ, ਜਾਂ ਕਨੈਕਟਿਵਿਟੀ ਨੂੰ ਲਗਾਤਾਰ ਵਰਤਣ ਲਈ ਬਹੁਤ ਮਹਿੰਗਾ ਹੁੰਦਾ ਹੈ, ਤਾਂ ਐਜ ਕੰਪਿਊਟਿੰਗ ਕੰਮ ਕਰਦੀ ਹੈ। ਉਦਾਹਰਣ ਵਜੋਂ, ਜਦੋਂ ਤੁਸੀਂ ਹਮਦਰਦੀ ਦੇ ਤਬਾਹੀ ਵਾਲੇ ਖੇਤਰਾਂ ਵਿੱਚ ਕੰਮ ਕਰ ਰਹੇ ਹੋ ਜਿੱਥੇ ਬੁਨਿਆਦੀ ਢਾਂਚਾ ਸੀਮਤ ਹੈ, ਜਾਂ ਵਿਕਾਸਸ਼ੀਲ ਦੇਸ਼ਾਂ ਵਿੱਚ।

1. **ਘੱਟ ਲਾਗਤ** - ਡਾਟਾ ਇਕੱਠਾ ਕਰਨ, ਸਟੋਰੇਜ, ਵਿਸ਼ਲੇਸ਼ਣ ਕਰਨ, ਅਤੇ ਐਕਸ਼ਨ ਟ੍ਰਿਗਰ ਕਰਨ ਨੂੰ ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਕਰਨ ਨਾਲ ਕਲਾਉਡ ਸਰਵਿਸਾਂ ਦੀ ਵਰਤੋਂ ਘਟ ਜਾਂਦੀ ਹੈ, ਜਿਸ ਨਾਲ ਤੁਹਾਡੇ IoT ਐਪਲੀਕੇਸ਼ਨ ਦੀ ਕੁੱਲ ਲਾਗਤ ਘਟ ਸਕਦੀ ਹੈ। ਹਾਲ ਹੀ ਵਿੱਚ ਐਜ ਕੰਪਿਊਟਿੰਗ ਲਈ ਡਿਜ਼ਾਈਨ ਕੀਤੇ ਗਏ ਡਿਵਾਈਸਾਂ ਵਿੱਚ ਵਾਧਾ ਹੋਇਆ ਹੈ, ਜਿਵੇਂ ਕਿ [NVIDIA ਤੋਂ ਜੈਟਸਨ ਨੈਨੋ](https://developer.nvidia.com/embedded/jetson-nano-developer-kit) ਵਰਗੇ AI ਐਕਸਲੇਰੇਟਰ ਬੋਰਡ, ਜੋ US$100 ਤੋਂ ਘੱਟ ਕੀਮਤ ਵਾਲੇ ਡਿਵਾਈਸਾਂ 'ਤੇ GPU-ਅਧਾਰਤ ਹਾਰਡਵੇਅਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ AI ਵਰਕਲੋਡ ਚਲਾ ਸਕਦੇ ਹਨ।

1. **ਗੋਪਨੀਯਤਾ ਅਤੇ ਸੁਰੱਖਿਆ** - ਐਜ ਕੰਪਿਊਟਿੰਗ ਨਾਲ, ਡਾਟਾ ਤੁਹਾਡੇ ਨੈੱਟਵਰਕ 'ਤੇ ਹੀ ਰਹਿੰਦਾ ਹੈ ਅਤੇ ਕਲਾਉਡ 'ਤੇ ਅੱਪਲੋਡ ਨਹੀਂ ਹੁੰਦਾ। ਇਹ ਸੰਵੇਦਨਸ਼ੀਲ ਅਤੇ ਨਿੱਜੀ ਤੌਰ 'ਤੇ ਪਛਾਣਯੋਗ ਜਾਣਕਾਰੀ ਲਈ ਅਕਸਰ ਪਸੰਦ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਖਾਸ ਕਰਕੇ ਕਿਉਂਕਿ ਡਾਟਾ ਨੂੰ ਵਿਸ਼ਲੇਸ਼ਣ ਤੋਂ ਬਾਅਦ ਸਟੋਰ ਕਰਨ ਦੀ ਲੋੜ ਨਹੀਂ ਹੁੰਦੀ, ਜਿਸ ਨਾਲ ਡਾਟਾ ਲੀਕ ਦੇ ਖਤਰੇ ਨੂੰ ਕਾਫ਼ੀ ਘਟਾਇਆ ਜਾ ਸਕਦਾ ਹੈ। ਉਦਾਹਰਣਾਂ ਵਿੱਚ ਮੈਡੀਕਲ ਡਾਟਾ ਅਤੇ ਸੁਰੱਖਿਆ ਕੈਮਰੇ ਦੀ ਫੁਟੇਜ ਸ਼ਾਮਲ ਹਨ।

1. **ਅਸੁਰੱਖਿਅਤ ਡਿਵਾਈਸਾਂ ਨੂੰ ਸੰਭਾਲਣਾ** - ਜੇ ਤੁਹਾਡੇ ਕੋਲ ਅਜਿਹੇ ਡਿਵਾਈਸ ਹਨ ਜਿਨ੍ਹਾਂ ਵਿੱਚ ਜਾਣੇ-ਪਛਾਣੇ ਸੁਰੱਖਿਆ ਖਾਮੀਆਂ ਹਨ ਅਤੇ ਤੁਸੀਂ ਉਨ੍ਹਾਂ ਨੂੰ ਸਿੱਧੇ ਆਪਣੇ ਨੈੱਟਵਰਕ ਜਾਂ ਇੰਟਰਨੈੱਟ ਨਾਲ ਨਹੀਂ ਜੋੜਨਾ ਚਾਹੁੰਦੇ, ਤਾਂ ਤੁਸੀਂ ਉਨ੍ਹਾਂ ਨੂੰ ਇੱਕ ਵੱਖਰੇ ਨੈੱਟਵਰਕ 'ਤੇ IoT Edge ਗੇਟਵੇ ਡਿਵਾਈਸ ਨਾਲ ਜੋੜ ਸਕਦੇ ਹੋ। ਇਹ ਐਜ ਡਿਵਾਈਸ ਫਿਰ ਤੁਹਾਡੇ ਵੱਡੇ ਨੈੱਟਵਰਕ ਜਾਂ ਇੰਟਰਨੈੱਟ ਨਾਲ ਇੱਕ ਕਨੈਕਸ਼ਨ ਰੱਖ ਸਕਦਾ ਹੈ, ਅਤੇ ਡਾਟਾ ਦੇ ਪ੍ਰਵਾਹਾਂ ਨੂੰ ਅੱਗੇ-ਪਿੱਛੇ ਪ੍ਰਬੰਧਿਤ ਕਰ ਸਕਦਾ ਹੈ।

1. **ਅਣਕੰਪੈਟਿਬਲ ਡਿਵਾਈਸਾਂ ਲਈ ਸਹਾਇਤਾ** - ਜੇ ਤੁਹਾਡੇ ਕੋਲ ਅਜਿਹੇ ਡਿਵਾਈਸ ਹਨ ਜੋ IoT Hub ਨਾਲ ਨਹੀਂ ਜੁੜ ਸਕਦੇ, ਉਦਾਹਰਣ ਵਜੋਂ ਅਜਿਹੇ ਡਿਵਾਈਸ ਜੋ ਸਿਰਫ HTTP ਕਨੈਕਸ਼ਨਾਂ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹਨ ਜਾਂ ਜਿਨ੍ਹਾਂ ਕੋਲ ਸਿਰਫ ਬਲੂਟੂਥ ਹੈ, ਤੁਸੀਂ IoT Edge ਡਿਵਾਈਸ ਨੂੰ ਗੇਟਵੇ ਡਿਵਾਈਸ ਵਜੋਂ ਵਰਤ ਸਕਦੇ ਹੋ, ਜੋ IoT Hub ਨੂੰ ਸੁਨੇਹੇ ਅੱਗੇ ਭੇਜਦਾ ਹੈ।

✅ ਕੁਝ ਖੋਜ ਕਰੋ: ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੇ ਹੋਰ ਕਿਹੜੇ ਫਾਇਦੇ ਹੋ ਸਕਦੇ ਹਨ?

### ਨੁਕਸਾਨ

ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੇ ਕੁਝ ਨੁਕਸਾਨ ਹਨ, ਜਿੱਥੇ ਕਲਾਉਡ ਇੱਕ ਪਸੰਦੀਦਾ ਵਿਕਲਪ ਹੋ ਸਕਦਾ ਹੈ:

1. **ਪੈਮਾਨਾ ਅਤੇ ਲਚੀਲਾਪਨ** - ਕਲਾਉਡ ਕੰਪਿਊਟਿੰਗ ਨੈੱਟਵਰਕ ਅਤੇ ਡਾਟਾ ਦੀਆਂ ਜ਼ਰੂਰਤਾਂ ਨੂੰ ਤੁਰੰਤ ਪੂਰਾ ਕਰਨ ਲਈ ਸਰਵਰਾਂ ਅਤੇ ਹੋਰ ਸਰੋਤਾਂ ਨੂੰ ਵਧਾ ਜਾਂ ਘਟਾ ਸਕਦੀ ਹੈ। ਹੋਰ ਐਜ ਕੰਪਿਊਟਰਾਂ ਨੂੰ ਸ਼ਾਮਲ ਕਰਨ ਲਈ ਹੱਥੋਂ ਹੋਰ ਡਿਵਾਈਸ ਸ਼ਾਮਲ ਕਰਨ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ।

1. **ਭਰੋਸੇਯੋਗਤਾ ਅਤੇ ਲਚੀਲਾਪਨ** - ਕਲਾਉਡ ਕੰਪਿਊਟਿੰਗ ਅਕਸਰ ਬਹੁਤ ਸਾਰੇ ਸਥਾਨਾਂ ਵਿੱਚ ਬਹੁਤ ਸਾਰੇ ਸਰਵਰਾਂ ਪ੍ਰਦਾਨ ਕਰਦੀ ਹੈ, ਜੋ ਰਿਡੰਡੈਂਸੀ ਅਤੇ ਡਿਜਾਸਟਰ ਰਿਕਵਰੀ ਲਈ ਹੁੰਦੇ ਹਨ। ਐਜ 'ਤੇ ਇੱਕੋ ਜਿਹੇ ਪੱਧਰ ਦੀ ਰਿਡੰਡੈਂਸੀ ਲਈ ਵੱਡੇ ਨਿਵੇਸ਼ ਅਤੇ ਬਹੁਤ ਸਾਰੀ ਸੰਰਚਨਾ ਦੇ ਕੰਮ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ।

1. **ਰਖ-ਰਖਾਵ** - ਕਲਾਉਡ ਸਰਵਿਸ ਪ੍ਰਦਾਤਾ ਸਿਸਟਮ ਦੀ ਰਖ-ਰਖਾਵ ਅਤੇ ਅੱਪਡੇਟ ਪ੍ਰਦਾਨ ਕਰਦੇ ਹਨ।

✅ ਕੁਝ ਖੋਜ ਕਰੋ: ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੇ ਹੋਰ ਕਿਹੜੇ ਨੁਕਸਾਨ ਹੋ ਸਕਦੇ ਹਨ?

ਨੁਕਸਾਨ ਅਸਲ ਵਿੱਚ ਕਲਾਉਡ ਦੀ ਵਰਤੋਂ ਦੇ ਫਾਇਦਿਆਂ ਦੇ ਉਲਟ ਹਨ - ਤੁਹਾਨੂੰ ਇਹ ਡਿਵਾਈਸ ਖੁਦ ਬਣਾਉਣੇ ਅਤੇ ਪ੍ਰਬੰਧਿਤ ਕਰਨੇ ਪੈਂਦੇ ਹਨ, ਕਲਾਉਡ ਪ੍ਰਦਾਤਾਵਾਂ ਦੀ ਮਹਾਰਤ ਅਤੇ ਪੈਮਾਨੇ 'ਤੇ ਨਿਰਭਰ ਕਰਨ ਦੀ ਬਜਾਏ।

ਕੁਝ ਖਤਰੇ ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੀ ਕੁਦਰਤ ਦੁਆਰਾ ਘਟਾਏ ਜਾਂਦੇ ਹਨ। ਉਦਾਹਰਣ ਵਜੋਂ, ਜੇ ਤੁਹਾਡੇ ਕੋਲ ਇੱਕ ਐਜ ਡਿਵਾਈਸ ਹੈ ਜੋ ਫੈਕਟਰੀ ਵਿੱਚ ਮਸ਼ੀਨਰੀ ਤੋਂ ਡਾਟਾ ਇਕੱਠਾ ਕਰ ਰਿਹਾ ਹੈ, ਤਾਂ ਤੁਹਾਨੂੰ ਕੁਝ ਡਿਜਾਸਟਰ ਰਿਕਵਰੀ ਸਥਿਤੀਆਂ ਬਾਰੇ ਸੋਚਣ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ। ਜੇ ਫੈਕਟਰੀ ਨੂੰ ਬਿਜਲੀ ਦੀ ਸਪਲਾਈ ਬੰਦ ਹੋ ਜਾਂਦੀ ਹੈ, ਤਾਂ ਤੁਹਾਨੂੰ ਬੈਕਅੱਪ ਐਜ ਡਿਵਾਈਸ ਦੀ ਲੋੜ ਨਹੀਂ ਹੈ ਕਿਉਂਕਿ ਉਹ ਮਸ਼ੀਨ ਜਿਹੜੇ ਡਾਟਾ ਪੈਦਾ ਕਰਦੇ ਹਨ, ਉਹ ਵੀ ਬਿਜਲੀ ਤੋਂ ਬਿਨਾਂ ਹੋਣਗੇ।

IoT ਸਿਸਟਮਾਂ ਲਈ, ਤੁਸੀਂ ਅਕਸਰ ਕਲਾਉਡ ਅਤੇ ਐਜ ਕੰਪਿਊਟਿੰਗ ਦੇ ਮਿਸ਼ਰਣ ਦੀ ਲੋੜ ਪਾਉਂਦੇ ਹੋ, ਸਿਸਟਮ, ਇਸਦੇ ਗਾਹਕਾਂ, ਅਤੇ ਇਸਦੇ ਰਖ-ਰਖਾਵ ਕਰਨ ਵਾਲਿਆਂ ਦੀਆਂ ਜ਼ਰੂਰਤਾਂ ਦੇ ਆਧਾਰ 'ਤੇ ਹਰ ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਦੇ ਹੋ।

## Azure IoT Edge

![Azure IoT Edge ਦਾ ਲੋਗੋ](../../../../../translated_images/pa/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge ਇੱਕ ਸੇਵਾ ਹੈ ਜੋ ਤੁਹਾਨੂੰ ਵਰਕਲੋਡਾਂ ਨੂੰ ਕਲਾਉਡ ਤੋਂ ਐਜ 'ਤੇ ਲਿਜਾਣ ਵਿੱਚ ਮਦਦ ਕਰ ਸਕਦੀ ਹੈ। ਤੁਸੀਂ ਇੱਕ ਡਿਵਾਈਸ ਨੂੰ ਐਜ ਡਿਵਾਈਸ ਵਜੋਂ ਸੈਟਅੱਪ ਕਰਦੇ ਹੋ, ਅਤੇ ਕਲਾਉਡ ਤੋਂ ਉਸ ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਕੋਡ ਡਿਪਲੌਇ ਕਰਦੇ ਹੋ। ਇਹ ਤੁਹਾਨੂੰ ਕਲਾਉਡ ਅਤੇ ਐਜ ਦੀ ਸਮਰੱਥਾਵਾਂ ਨੂੰ ਮਿਲਾਉਣ ਦੀ ਆਗਿਆ ਦਿੰਦਾ ਹੈ।

> 🎓 *ਵਰਕਲੋਡ* ਕਿਸੇ ਵੀ ਸੇਵਾ ਲਈ ਇੱਕ ਸ਼ਬਦ ਹੈ ਜੋ ਕਿਸੇ ਕਿਸਮ ਦਾ ਕੰਮ ਕਰਦੀ ਹੈ, ਜਿਵੇਂ ਕਿ AI ਮਾਡਲ, ਐਪਲੀਕੇਸ਼ਨ, ਜਾਂ ਸਰਵਰਲੈੱਸ ਫੰਕਸ਼ਨ।

ਉਦਾਹਰਣ ਵਜੋਂ, ਤੁਸੀਂ ਕਲਾਉਡ ਵਿੱਚ ਇੱਕ ਇਮੇਜ ਕਲਾਸੀਫਾਇਰ ਨੂੰ ਟ੍ਰੇਨ ਕਰ ਸਕਦੇ ਹੋ, ਅਤੇ ਫਿਰ ਕਲਾਉਡ ਤੋਂ ਉਸਨੂੰ ਇੱਕ ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਡਿਪਲੌਇ ਕਰ ਸਕਦੇ ਹੋ। ਤੁਹਾਡਾ IoT ਡਿਵਾਈਸ ਫਿਰ ਇੰਟਰਨੈੱਟ 'ਤੇ ਤਸਵੀਰਾਂ ਭੇਜਣ ਦੀ ਬਜਾਏ, ਕਲਾਸੀਫਿਕੇਸ਼ਨ ਲਈ ਐਜ ਡਿਵਾਈਸ ਨੂੰ ਤਸਵੀਰਾਂ ਭੇਜਦਾ ਹੈ। ਜੇ ਤੁਹਾਨੂੰ ਮਾਡਲ ਦੇ ਨਵੇਂ ਸੰਸਕਰਣ ਨੂੰ ਡਿਪਲੌਇ ਕਰਨ ਦੀ ਲੋੜ ਹੈ, ਤਾਂ ਤੁਸੀਂ ਕਲਾਉਡ ਵਿੱਚ ਇਸਨੂੰ ਟ੍ਰੇਨ ਕਰ ਸਕਦੇ ਹੋ ਅਤੇ IoT Edge ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਐਜ ਡਿਵਾਈਸ 'ਤੇ ਮਾਡਲ ਨੂੰ ਆਪਣੇ ਨਵੇਂ ਸੰਸਕਰਣ ਵਿੱਚ ਅੱਪਡੇਟ ਕਰ ਸਕਦੇ ਹੋ।

> 🎓 ਜਿਹੜਾ ਸੌਫਟਵੇਅਰ IoT Edge 'ਤੇ ਡਿਪਲੌਇ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਉਸਨੂੰ *ਮੋਡੀਊਲ* ਕਿਹਾ ਜਾਂਦਾ ਹੈ। ਡਿਫੌਲਟ ਰੂਪ ਵਿੱਚ IoT Edge ਉਹ ਮੋਡੀਊ
1. [CustomVision.ai](https://customvision.ai) 'ਤੇ Custom Vision ਪੋਰਟਲ ਖੋਲ੍ਹੋ ਅਤੇ ਸਾਈਨ ਇਨ ਕਰੋ ਜੇਕਰ ਤੁਸੀਂ ਪਹਿਲਾਂ ਹੀ ਇਸਨੂੰ ਨਹੀਂ ਖੋਲ੍ਹਿਆ। ਫਿਰ ਆਪਣੇ `fruit-quality-detector` ਪ੍ਰੋਜੈਕਟ ਨੂੰ ਖੋਲ੍ਹੋ।

1. **Settings** ਬਟਨ (⚙ ਆਈਕਨ) ਚੁਣੋ।

1. *Domains* ਸੂਚੀ ਵਿੱਚ, *Food (compact)* ਚੁਣੋ।

1. *Export Capabilities* ਦੇ ਅਧੀਨ, ਯਕੀਨੀ ਬਣਾਓ ਕਿ *Basic platforms (Tensorflow, CoreML, ONNX, ...)* ਚੁਣਿਆ ਗਿਆ ਹੈ।

1. Settings ਪੇਜ ਦੇ ਹੇਠਾਂ **Save Changes** ਚੁਣੋ।

1. **Train** ਬਟਨ ਨਾਲ ਮਾਡਲ ਨੂੰ ਦੁਬਾਰਾ ਟ੍ਰੇਨ ਕਰੋ, *Quick training* ਚੁਣਦੇ ਹੋਏ।

### ਟਾਸਕ - ਆਪਣੇ ਮਾਡਲ ਨੂੰ ਐਕਸਪੋਰਟ ਕਰੋ

ਜਦੋਂ ਮਾਡਲ ਟ੍ਰੇਨ ਹੋ ਜਾਵੇ, ਇਸਨੂੰ ਇੱਕ ਕੰਟੇਨਰ ਵਜੋਂ ਐਕਸਪੋਰਟ ਕਰਨ ਦੀ ਲੋੜ ਹੈ।

1. **Performance** ਟੈਬ ਚੁਣੋ ਅਤੇ ਆਪਣੀ ਆਖਰੀ iteration ਨੂੰ ਲੱਭੋ ਜੋ compact domain ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਟ੍ਰੇਨ ਕੀਤਾ ਗਿਆ ਸੀ।

1. ਉੱਪਰ **Export** ਬਟਨ ਚੁਣੋ।

1. **DockerFile** ਚੁਣੋ, ਫਿਰ ਇੱਕ ਵਰਜਨ ਚੁਣੋ ਜੋ ਤੁਹਾਡੇ edge device ਨਾਲ ਮੇਲ ਖਾਂਦਾ ਹੈ:

    * ਜੇਕਰ ਤੁਸੀਂ IoT Edge ਨੂੰ Linux ਕੰਪਿਊਟਰ, Windows ਕੰਪਿਊਟਰ ਜਾਂ Virtual Machine 'ਤੇ ਚਲਾ ਰਹੇ ਹੋ, ਤਾਂ *Linux* ਵਰਜਨ ਚੁਣੋ।
    * ਜੇਕਰ ਤੁਸੀਂ IoT Edge ਨੂੰ Raspberry Pi 'ਤੇ ਚਲਾ ਰਹੇ ਹੋ, ਤਾਂ *ARM (Raspberry Pi 3)* ਵਰਜਨ ਚੁਣੋ।

    
> 🎓 Docker ਕੰਟੇਨਰਾਂ ਨੂੰ ਮੈਨੇਜ ਕਰਨ ਲਈ ਸਭ ਤੋਂ ਪ੍ਰਸਿੱਧ ਟੂਲਾਂ ਵਿੱਚੋਂ ਇੱਕ ਹੈ, ਅਤੇ DockerFile ਕੰਟੇਨਰ ਨੂੰ ਸੈਟ ਅਪ ਕਰਨ ਦੇ ਨਿਰਦੇਸ਼ਾਂ ਦਾ ਸੈੱਟ ਹੈ।

1. Custom Vision ਨੂੰ ਸੰਬੰਧਿਤ ਫਾਈਲਾਂ ਬਣਾਉਣ ਲਈ **Export** ਚੁਣੋ, ਫਿਰ **Download** ਚੁਣੋ ਅਤੇ ਫਾਈਲਾਂ ਨੂੰ zip ਫਾਈਲ ਵਿੱਚ ਡਾਊਨਲੋਡ ਕਰੋ।

1. ਫਾਈਲਾਂ ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ 'ਤੇ ਸੇਵ ਕਰੋ, ਫਿਰ ਫੋਲਡਰ ਨੂੰ unzip ਕਰੋ।

## ਆਪਣੇ ਕੰਟੇਨਰ ਨੂੰ ਡਿਪਲੌਇਮੈਂਟ ਲਈ ਤਿਆਰ ਕਰੋ

![ਕੰਟੇਨਰ ਬਣਾਏ ਜਾਂਦੇ ਹਨ ਫਿਰ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕੀਤੇ ਜਾਂਦੇ ਹਨ, ਫਿਰ IoT Edge ਦੀ ਵਰਤੋਂ ਕਰਕੇ edge device 'ਤੇ ਡਿਪਲੌਇ ਕੀਤੇ ਜਾਂਦੇ ਹਨ](../../../../../translated_images/pa/container-edge-flow.c246050dd60ceefd.webp)

ਜਦੋਂ ਤੁਸੀਂ ਆਪਣਾ ਮਾਡਲ ਡਾਊਨਲੋਡ ਕਰ ਲੈਂਦੇ ਹੋ, ਇਸਨੂੰ ਇੱਕ ਕੰਟੇਨਰ ਵਿੱਚ ਬਣਾਉਣ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਫਿਰ ਇਸਨੂੰ ਇੱਕ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕੀਤਾ ਜਾਂਦਾ ਹੈ - ਇੱਕ ਆਨਲਾਈਨ ਸਥਾਨ ਜਿੱਥੇ ਤੁਸੀਂ ਕੰਟੇਨਰ ਸਟੋਰ ਕਰ ਸਕਦੇ ਹੋ। IoT Edge ਫਿਰ ਰਜਿਸਟਰੀ ਤੋਂ ਕੰਟੇਨਰ ਨੂੰ ਡਾਊਨਲੋਡ ਕਰ ਸਕਦਾ ਹੈ ਅਤੇ ਇਸਨੂੰ ਤੁਹਾਡੇ ਡਿਵਾਈਸ 'ਤੇ ਪਹੁੰਚਾ ਸਕਦਾ ਹੈ।

![Azure Container Registry ਦਾ ਲੋਗੋ](../../../../../translated_images/pa/azure-container-registry-logo.09494206991d4b29.webp)

ਤੁਹਾਡੇ ਲਈ ਇਸ ਪਾਠ ਵਿੱਚ ਵਰਤਣ ਲਈ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ Azure Container Registry ਹੈ। ਇਹ ਮੁਫ਼ਤ ਸੇਵਾ ਨਹੀਂ ਹੈ, ਇਸ ਲਈ ਪੈਸਾ ਬਚਾਉਣ ਲਈ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਸੀਂ [clean up your project](../../../clean-up.md) ਜਦੋਂ ਤੁਸੀਂ ਖਤਮ ਕਰ ਲੈਂਦੇ ਹੋ।

> 💁 ਤੁਸੀਂ Azure Container Registry ਦੀ ਵਰਤੋਂ ਦੇ ਖਰਚੇ [Azure Container Registry pricing page](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) 'ਤੇ ਦੇਖ ਸਕਦੇ ਹੋ।

### ਟਾਸਕ - Docker ਇੰਸਟਾਲ ਕਰੋ

ਕਲਾਸੀਫਾਇਰ ਨੂੰ ਬਣਾਉਣ ਅਤੇ ਡਿਪਲੌਇ ਕਰਨ ਲਈ, ਤੁਹਾਨੂੰ [Docker](https://www.docker.com/) ਇੰਸਟਾਲ ਕਰਨ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

ਤੁਹਾਨੂੰ ਇਹ ਸਿਰਫ਼ ਉਸ ਸਥਿਤੀ ਵਿੱਚ ਕਰਨ ਦੀ ਲੋੜ ਹੋਵੇਗੀ ਜੇਕਰ ਤੁਸੀਂ IoT Edge ਇੰਸਟਾਲ ਕੀਤੇ ਗਏ ਡਿਵਾਈਸ ਤੋਂ ਵੱਖਰੇ ਡਿਵਾਈਸ ਤੋਂ ਆਪਣਾ ਕੰਟੇਨਰ ਬਣਾਉਣ ਦੀ ਯੋਜਨਾ ਬਣਾਉਂਦੇ ਹੋ - IoT Edge ਇੰਸਟਾਲ ਕਰਨ ਦੇ ਹਿੱਸੇ ਵਜੋਂ, Docker ਤੁਹਾਡੇ ਲਈ ਇੰਸਟਾਲ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

1. ਜੇਕਰ ਤੁਸੀਂ Docker ਕੰਟੇਨਰ ਨੂੰ IoT Edge ਡਿਵਾਈਸ ਤੋਂ ਵੱਖਰੇ ਡਿਵਾਈਸ 'ਤੇ ਬਣਾਉਣ ਦੀ ਯੋਜਨਾ ਬਣਾਉਂਦੇ ਹੋ, ਤਾਂ Docker Desktop ਜਾਂ Docker engine ਨੂੰ ਇੰਸਟਾਲ ਕਰਨ ਲਈ [Docker install page](https://www.docker.com/products/docker-desktop) 'ਤੇ Docker ਇੰਸਟਾਲੇਸ਼ਨ ਨਿਰਦੇਸ਼ਾਂ ਦੀ ਪਾਲਣਾ ਕਰੋ। ਇੰਸਟਾਲੇਸ਼ਨ ਤੋਂ ਬਾਅਦ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਇਹ ਚੱਲ ਰਿਹਾ ਹੈ।

### ਟਾਸਕ - ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਰਿਸੋਰਸ ਬਣਾਓ

1. ਆਪਣੀ ਟਰਮੀਨਲ ਜਾਂ ਕਮਾਂਡ ਪ੍ਰੋਮਪਟ ਤੋਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਚਲਾਓ ਤਾਂ ਜੋ Azure Container Registry ਰਿਸੋਰਸ ਬਣਾਇਆ ਜਾ ਸਕੇ:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਇੱਕ ਵਿਲੱਖਣ ਨਾਮ ਨਾਲ ਬਦਲੋ, ਸਿਰਫ਼ ਅੱਖਰ ਅਤੇ ਅੰਕਾਂ ਦੀ ਵਰਤੋਂ ਕਰਦੇ ਹੋਏ। ਇਸਨੂੰ `fruitqualitydetector` ਦੇ ਆਧਾਰ 'ਤੇ ਬਣਾਓ। ਇਹ ਨਾਮ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਤੱਕ ਪਹੁੰਚ ਕਰਨ ਲਈ URL ਦਾ ਹਿੱਸਾ ਬਣ ਜਾਂਦਾ ਹੈ, ਇਸ ਲਈ ਇਹ ਗਲੋਬਲ ਤੌਰ 'ਤੇ ਵਿਲੱਖਣ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ Azure Container Registry ਵਿੱਚ ਲੌਗ ਇਨ ਕਰੋ:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

1. ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਨੂੰ ਐਡਮਿਨ ਮੋਡ ਵਿੱਚ ਸੈਟ ਕਰੋ ਤਾਂ ਜੋ ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਪਾਸਵਰਡ ਜਨਰੇਟ ਕਰ ਸਕੋ:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਪਾਸਵਰਡ ਜਨਰੇਟ ਕਰੋ:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    `PASSWORD` ਦੀ ਵੈਲਿਊ ਦੀ ਕਾਪੀ ਲਵੋ, ਕਿਉਂਕਿ ਤੁਹਾਨੂੰ ਇਹ ਬਾਅਦ ਵਿੱਚ ਲੋੜੀਂਦੀ ਹੋਵੇਗੀ।

### ਟਾਸਕ - ਆਪਣੇ ਕੰਟੇਨਰ ਨੂੰ ਬਣਾਓ

Custom Vision ਤੋਂ ਜੋ ਤੁਸੀਂ ਡਾਊਨਲੋਡ ਕੀਤਾ ਸੀ, ਉਹ DockerFile ਸੀ ਜਿਸ ਵਿੱਚ ਕੰਟੇਨਰ ਨੂੰ ਕਿਵੇਂ ਬਣਾਇਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ ਇਸਦੇ ਨਿਰਦੇਸ਼ ਹਨ, ਨਾਲ ਹੀ ਐਪਲੀਕੇਸ਼ਨ ਕੋਡ ਜੋ ਕੰਟੇਨਰ ਦੇ ਅੰਦਰ ਚਲਾਇਆ ਜਾਵੇਗਾ ਤਾਂ ਜੋ ਤੁਹਾਡੇ custom vision ਮਾਡਲ ਨੂੰ ਹੋਸਟ ਕੀਤਾ ਜਾ ਸਕੇ, ਅਤੇ REST API ਨੂੰ ਕਾਲ ਕੀਤਾ ਜਾ ਸਕੇ। ਤੁਸੀਂ Docker ਦੀ ਵਰਤੋਂ ਕਰਕੇ DockerFile ਤੋਂ ਇੱਕ ਟੈਗ ਕੀਤੇ ਕੰਟੇਨਰ ਨੂੰ ਬਣਾਉਣ ਲਈ ਵਰਤ ਸਕਦੇ ਹੋ, ਫਿਰ ਇਸਨੂੰ ਆਪਣੀ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕਰ ਸਕਦੇ ਹੋ।

> 🎓 ਕੰਟੇਨਰਾਂ ਨੂੰ ਇੱਕ ਟੈਗ ਦਿੱਤਾ ਜਾਂਦਾ ਹੈ ਜੋ ਉਨ੍ਹਾਂ ਲਈ ਇੱਕ ਨਾਮ ਅਤੇ ਵਰਜਨ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ। ਜਦੋਂ ਤੁਹਾਨੂੰ ਕੰਟੇਨਰ ਨੂੰ ਅਪਡੇਟ ਕਰਨ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ, ਤੁਸੀਂ ਇਸਨੂੰ ਉਹੀ ਟੈਗ ਨਾਲ ਪਰ ਨਵੀਂ ਵਰਜਨ ਨਾਲ ਬਣਾਉਣ ਲਈ ਵਰਤ ਸਕਦੇ ਹੋ।

1. ਆਪਣੀ ਟਰਮੀਨਲ ਜਾਂ ਕਮਾਂਡ ਪ੍ਰੋਮਪਟ ਖੋਲ੍ਹੋ ਅਤੇ Custom Vision ਤੋਂ ਡਾਊਨਲੋਡ ਕੀਤੇ ਮਾਡਲ ਨੂੰ unzip ਕੀਤੇ ਗਏ ਸਥਾਨ 'ਤੇ ਜਾਓ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨੂੰ ਚਲਾਓ ਤਾਂ ਜੋ ਇਮੇਜ ਨੂੰ ਬਣਾਇਆ ਅਤੇ ਟੈਗ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>` ਨੂੰ ਉਸ ਪਲੇਟਫਾਰਮ ਨਾਲ ਬਦਲੋ ਜਿਸ 'ਤੇ ਇਹ ਕੰਟੇਨਰ ਚੱਲੇਗਾ। ਜੇਕਰ ਤੁਸੀਂ IoT Edge ਨੂੰ Raspberry Pi 'ਤੇ ਚਲਾ ਰਹੇ ਹੋ, ਇਸਨੂੰ `linux/armhf` ਸੈਟ ਕਰੋ, ਨਹੀਂ ਤਾਂ ਇਸਨੂੰ `linux/amd64` ਸੈਟ ਕਰੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ ਇਹ ਕਮਾਂਡ ਉਸ ਡਿਵਾਈਸ ਤੋਂ ਚਲਾ ਰਹੇ ਹੋ ਜਿਸ 'ਤੇ ਤੁਸੀਂ IoT Edge ਚਲਾ ਰਹੇ ਹੋ, ਜਿਵੇਂ ਕਿ Raspberry Pi ਤੋਂ, ਤਾਂ ਤੁਸੀਂ `--platform <platform>` ਹਿੱਸੇ ਨੂੰ ਛੱਡ ਸਕਦੇ ਹੋ ਕਿਉਂਕਿ ਇਹ ਮੌਜੂਦਾ ਪਲੇਟਫਾਰਮ ਨੂੰ ਡਿਫਾਲਟ ਕਰਦਾ ਹੈ।

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ Linux ਜਾਂ Raspberry Pi OS 'ਤੇ ਚੱਲ ਰਹੇ ਹੋ ਤਾਂ ਤੁਹਾਨੂੰ ਇਹ ਕਮਾਂਡ ਚਲਾਉਣ ਲਈ `sudo` ਦੀ ਵਰਤੋਂ ਕਰਨ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

    Docker ਇਮੇਜ ਨੂੰ ਬਣਾਏਗਾ, ਸਾਰਾ ਲੋੜੀਂਦਾ ਸੌਫਟਵੇਅਰ ਕਨਫਿਗਰ ਕਰੇਗਾ। ਇਮੇਜ ਨੂੰ `classifier:v1` ਵਜੋਂ ਟੈਗ ਕੀਤਾ ਜਾਵੇਗਾ।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### ਟਾਸਕ - ਆਪਣੇ ਕੰਟੇਨਰ ਨੂੰ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕਰੋ

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਆਪਣੇ ਕੰਟੇਨਰ ਨੂੰ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕਰੋ:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    > 💁 ਜੇਕਰ ਤੁਸੀਂ Linux 'ਤੇ ਚੱਲ ਰਹੇ ਹੋ ਤਾਂ ਤੁਹਾਨੂੰ ਇਹ ਕਮਾਂਡ ਚਲਾਉਣ ਲਈ `sudo` ਦੀ ਵਰਤੋਂ ਕਰਨ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

    ਕੰਟੇਨਰ ਨੂੰ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਵਿੱਚ ਪੁਸ਼ ਕੀਤਾ ਜਾਵੇਗਾ।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. ਪੁਸ਼ ਦੀ ਪੁਸ਼ਟੀ ਕਰਨ ਲਈ, ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨਾਲ ਆਪਣੀ ਰਜਿਸਟਰੀ ਵਿੱਚ ਕੰਟੇਨਰਾਂ ਦੀ ਸੂਚੀ ਦੇਖ ਸਕਦੇ ਹੋ:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    ਤੁਸੀਂ ਆਉਟਪੁੱਟ ਵਿੱਚ ਆਪਣਾ ਕਲਾਸੀਫਾਇਰ ਦੇਖੋਗੇ।

## ਆਪਣੇ ਕੰਟੇਨਰ ਨੂੰ ਡਿਪਲੌਇ ਕਰੋ

ਹੁਣ ਤੁਹਾਡਾ ਕੰਟੇਨਰ ਤੁਹਾਡੇ IoT Edge ਡਿਵਾਈਸ 'ਤੇ ਡਿਪਲੌਇ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। ਡਿਪਲੌਇ ਕਰਨ ਲਈ ਤੁਹਾਨੂੰ ਇੱਕ deployment manifest ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਨ ਦੀ ਲੋੜ ਹੈ - ਇੱਕ JSON ਦਸਤਾਵੇਜ਼ ਜੋ edge device 'ਤੇ ਡਿਪਲੌਇ ਕੀਤੇ ਜਾਣ ਵਾਲੇ ਮੋਡਿਊਲਾਂ ਦੀ ਸੂਚੀ ਦਿੰਦਾ ਹੈ।

### ਟਾਸਕ - deployment manifest ਬਣਾਓ

1. ਆਪਣੇ ਕੰਪਿਊਟਰ 'ਤੇ ਕਿਤੇ `deployment.json` ਨਾਮਕ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ।

1. ਇਸ ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 ਤੁਸੀਂ ਇਸ ਫਾਈਲ ਨੂੰ [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

    `<Container registry name>` ਦੇ ਤਿੰਨ ਉਦਾਹਰਣਾਂ ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਲਈ ਵਰਤੇ ਗਏ ਨਾਮ ਨਾਲ ਬਦਲੋ। ਇੱਕ `ImageClassifier` ਮੋਡਿਊਲ ਸੈਕਸ਼ਨ ਵਿੱਚ ਹੈ, ਦੂਜੇ ਦੋ `registryCredentials` ਸੈਕਸ਼ਨ ਵਿੱਚ ਹਨ।

    `registryCredentials` ਸੈਕਸ਼ਨ ਵਿੱਚ `<Container registry password>` ਨੂੰ ਆਪਣੇ ਕੰਟੇਨਰ ਰਜਿਸਟਰੀ ਪਾਸਵਰਡ ਨਾਲ ਬਦਲੋ।

1. ਆਪਣੀ deployment manifest ਵਾਲੇ ਫੋਲਡਰ ਤੋਂ, ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਨੂੰ ਚਲਾਓ:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>` ਨੂੰ ਆਪਣੇ IoT Hub ਦੇ ਨਾਮ ਨਾਲ ਬਦਲੋ।

    image classifier ਮੋਡਿਊਲ edge device 'ਤੇ ਡਿਪਲੌਇ ਕੀਤਾ ਜਾਵੇਗਾ।

### ਟਾਸਕ - ਕਲਾਸੀਫਾਇਰ ਚੱਲ ਰਿਹਾ ਹੈ ਇਸਦੀ ਪੁਸ਼ਟੀ ਕਰੋ

1. IoT edge device ਨਾਲ ਕਨੈਕਟ ਕਰੋ:

    * ਜੇਕਰ ਤੁਸੀਂ Raspberry Pi ਦੀ ਵਰਤੋਂ ਕਰਕੇ IoT Edge ਚਲਾ ਰਹੇ ਹੋ, ਤਾਂ ssh ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਆਪਣੇ ਟਰਮੀਨਲ ਤੋਂ ਜਾਂ VS Code ਵਿੱਚ ਇੱਕ ਰਿਮੋਟ SSH ਸੈਸ਼ਨ ਰਾਹੀਂ ਕਨੈਕਟ ਕਰੋ।
    * ਜੇਕਰ ਤੁਸੀਂ Windows 'ਤੇ Linux ਕੰਟੇਨਰ ਵਿੱਚ IoT Edge ਚਲਾ ਰਹੇ ਹੋ, ਤਾਂ IoT Edge ਡਿਵਾਈਸ ਨਾਲ ਕਨੈਕਟ ਕਰਨ ਲਈ [verify successful configuration guide](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) ਵਿੱਚ ਦਿੱਤੇ ਕਦਮਾਂ ਦੀ ਪਾਲਣਾ ਕਰੋ।
    * ਜੇਕਰ ਤੁਸੀਂ IoT Edge ਨੂੰ ਇੱਕ virtual machine 'ਤੇ ਚਲਾ ਰਹੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ VM ਬਣਾਉਣ ਸਮੇਂ ਸੈਟ ਕੀਤੇ `adminUsername` ਅਤੇ `password` ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਮਸ਼ੀਨ ਵਿੱਚ SSH ਕਰ ਸਕਦੇ ਹੋ, ਅਤੇ IP address ਜਾਂ DNS name ਦੀ ਵਰਤੋਂ ਕਰਕੇ:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        ਜਾਂ:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        ਪ੍ਰੋਮਪਟ ਹੋਣ 'ਤੇ ਆਪਣਾ ਪਾਸਵਰਡ ਦਾਖਲ ਕਰੋ।

1. ਜਦੋਂ ਤੁਸੀਂ ਕਨੈਕਟ ਹੋ ਜਾਵੋ, ਤਾਂ IoT Edge ਮੋਡਿਊਲਾਂ ਦੀ ਸੂਚੀ ਪ੍ਰਾਪਤ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਚਲਾਓ:

    ```sh
    iotedge list
    ```

    > 💁 ਤੁਹਾਨੂੰ ਇਹ ਕਮਾਂਡ `sudo` ਨਾਲ ਚਲਾਉਣ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

    ਤੁਸੀਂ ਚੱਲ ਰਹੇ ਮੋਡਿਊਲਾਂ ਨੂੰ ਦੇਖੋਗੇ:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Image classifier ਮੋਡਿਊਲ ਲਈ ਲਾਗਸ ਦੀ ਜਾਂਚ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕਮਾਂਡ ਚਲਾਓ:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 ਤੁਹਾਨੂੰ ਇਹ ਕਮਾਂਡ `sudo` ਨਾਲ ਚਲਾਉਣ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### ਟਾਸਕ - image classifier ਦੀ ਜਾਂਚ ਕਰੋ

1. ਤੁਸੀਂ CURL ਦੀ ਵਰਤੋਂ ਕਰਕੇ image classifier ਦੀ ਜਾਂਚ ਕਰ ਸਕਦੇ ਹੋ ਜੋ IoT Edge agent ਚਲਾ ਰਹੇ ਕੰਪਿਊਟਰ ਦੇ IP address ਜਾਂ host name ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ। IP address ਲੱਭੋ:

    * ਜੇਕਰ ਤੁਸੀਂ ਉਸੇ ਮਸ਼ੀਨ 'ਤੇ ਹੋ ਜਿਸ 'ਤੇ IoT Edge ਚੱਲ ਰਿਹਾ ਹੈ, ਤਾਂ ਤੁਸੀਂ host name ਵਜੋਂ `localhost` ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ।
    * ਜੇਕਰ ਤੁਸੀਂ VM ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ, ਤਾਂ ਤੁਸੀਂ VM ਦੇ IP address ਜਾਂ DNS name ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ।
    * ਨਹੀਂ ਤਾਂ ਤੁਸੀਂ IoT Edge ਚਲਾ ਰਹੇ ਮਸ਼ੀਨ ਦਾ IP address ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ:
      * Windows 10 'ਤੇ, [find your IP address guide](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) ਦੀ ਪਾਲਣਾ ਕਰੋ।
      * macOS 'ਤੇ, [how to find you IP address on a Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) ਦੀ ਪਾਲਣਾ ਕਰੋ।
      * Linux 'ਤੇ, [how to find your IP address in Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux) ਵਿੱਚ ਆਪਣੇ private IP address ਲੱਭਣ ਦੇ ਸੈਕਸ਼ਨ ਦੀ ਪਾਲਣਾ ਕਰੋ।

1. ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੇ curl ਕਮਾਂਡ ਨੂੰ ਚਲਾਕੇ ਇੱਕ ਸਥਾਨਕ ਫਾਈਲ ਨਾਲ ਕੰਟੇਨਰ ਦੀ ਜਾਂਚ ਕਰ ਸਕਦੇ ਹੋ:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address
* ਐਜ ਕੰਪਿਊਟਿੰਗ ਬਾਰੇ ਹੋਰ ਪੜ੍ਹੋ, ਇਸ 'ਤੇ ਜ਼ੋਰ ਦੇ ਕੇ ਕਿ 5G ਕਿਵੇਂ ਐਜ ਕੰਪਿਊਟਿੰਗ ਨੂੰ ਵਧਾਉਣ ਵਿੱਚ ਮਦਦ ਕਰ ਸਕਦਾ ਹੈ [ਐਜ ਕੰਪਿਊਟਿੰਗ ਕੀ ਹੈ ਅਤੇ ਇਹ ਕਿਉਂ ਮਹੱਤਵਪੂਰਨ ਹੈ? NetworkWorld ਦੇ ਲੇਖ](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html) ਵਿੱਚ।
* IoT Edge ਵਿੱਚ AI ਸੇਵਾਵਾਂ ਚਲਾਉਣ ਬਾਰੇ ਹੋਰ ਜਾਣਕਾਰੀ ਪ੍ਰਾਪਤ ਕਰੋ [Microsoft Channel9 ਦੇ Learn Live ਦੇ ਐਪਿਸੋਡ 'ਤੇ, ਜਿੱਥੇ Edge 'ਤੇ ਇੱਕ ਪ੍ਰੀ-ਬਿਲਟ AI ਸੇਵਾ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਭਾਸ਼ਾ ਪਛਾਣ ਕਰਨ ਦੇ ਤਰੀਕੇ ਸਿੱਖੋ](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)।

## ਅਸਾਈਨਮੈਂਟ

[ਐਜ 'ਤੇ ਹੋਰ ਸੇਵਾਵਾਂ ਚਲਾਓ](assignment.md)

---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦਾ ਯਤਨ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁੱਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੌਜੂਦ ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਪ੍ਰਮਾਣਿਕ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੇ ਪ੍ਰਯੋਗ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।  