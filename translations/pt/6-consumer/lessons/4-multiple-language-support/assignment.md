<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-25T22:27:45+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "pt"
}
-->
# Construir um tradutor universal

## Instruções

Um tradutor universal é um dispositivo que pode traduzir entre várias línguas, permitindo que pessoas que falam idiomas diferentes consigam comunicar-se. Use o que aprendeu nas últimas lições para construir um tradutor universal utilizando 2 dispositivos IoT.

> Se não tiver 2 dispositivos, siga os passos das últimas lições para configurar um dispositivo IoT virtual como um dos dispositivos IoT.

Deve configurar um dispositivo para um idioma e outro para outro. Cada dispositivo deve aceitar fala, convertê-la em texto, enviá-la para o outro dispositivo através do IoT Hub e de uma aplicação Functions, depois traduzi-la e reproduzir a fala traduzida.

> 💁 Dica: Ao enviar a fala de um dispositivo para outro, envie também o idioma em que está, facilitando a tradução. Pode até fazer com que cada dispositivo se registe primeiro utilizando o IoT Hub e uma aplicação Functions, passando o idioma que suportam para ser armazenado no Azure Storage. Depois, pode usar uma aplicação Functions para realizar as traduções, enviando o texto traduzido para o dispositivo IoT.

## Critérios de Avaliação

| Critério | Exemplar | Adequado | Necessita Melhorias |
| -------- | --------- | -------- | ------------------- |
| Criar um tradutor universal | Conseguiu construir um tradutor universal, convertendo a fala detectada por um dispositivo em fala reproduzida por outro dispositivo num idioma diferente | Conseguiu fazer funcionar alguns componentes, como capturar fala ou traduzir, mas não conseguiu construir a solução completa de ponta a ponta | Não conseguiu construir nenhuma parte de um tradutor universal funcional |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.