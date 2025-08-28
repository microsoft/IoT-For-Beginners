<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T03:11:25+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "br"
}
-->
# Construir um tradutor universal

## Instruções

Um tradutor universal é um dispositivo que pode traduzir entre vários idiomas, permitindo que pessoas que falam línguas diferentes possam se comunicar. Use o que você aprendeu nas últimas aulas para construir um tradutor universal usando 2 dispositivos IoT.

> Se você não tiver 2 dispositivos, siga os passos das últimas aulas para configurar um dispositivo IoT virtual como um dos dispositivos IoT.

Você deve configurar um dispositivo para um idioma e outro para outro idioma. Cada dispositivo deve aceitar fala, convertê-la em texto, enviá-la para o outro dispositivo via IoT Hub e um aplicativo Functions, traduzi-la e reproduzir a fala traduzida.

> 💁 Dica: Ao enviar a fala de um dispositivo para outro, envie também o idioma em que ela está, facilitando a tradução. Você pode até fazer com que cada dispositivo se registre usando o IoT Hub e um aplicativo Functions primeiro, passando o idioma que suportam para ser armazenado no Azure Storage. Depois, você pode usar um aplicativo Functions para realizar as traduções, enviando o texto traduzido para o dispositivo IoT.

## Critérios de Avaliação

| Critério | Exemplar | Adequado | Precisa Melhorar |
| -------- | --------- | -------- | ---------------- |
| Criar um tradutor universal | Foi capaz de construir um tradutor universal, convertendo a fala detectada por um dispositivo em fala reproduzida por outro dispositivo em um idioma diferente | Foi capaz de fazer algumas partes funcionarem, como capturar fala ou traduzir, mas não conseguiu construir a solução completa de ponta a ponta | Não conseguiu construir nenhuma parte de um tradutor universal funcional |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.