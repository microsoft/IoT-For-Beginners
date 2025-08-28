<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T02:50:36+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "br"
}
-->
# Responder aos resultados da classificação

## Instruções

Seu dispositivo classificou imagens e possui os valores das previsões. Ele pode usar essas informações para realizar alguma ação - pode enviá-las para o IoT Hub para serem processadas por outros sistemas, ou pode controlar um atuador, como acender um LED quando a fruta estiver verde.

Adicione código ao seu dispositivo para responder de uma maneira à sua escolha - seja enviando dados para um IoT Hub, controlando um atuador, ou combinando as duas opções e enviando dados para um IoT Hub com algum código serverless que determine se a fruta está madura ou não e envie de volta um comando para controlar um atuador.

## Critérios de Avaliação

| Critério | Exemplary (Exemplar) | Adequate (Adequado) | Needs Improvement (Precisa Melhorar) |
| -------- | --------------------- | ------------------- | ------------------------------------- |
| Responder às previsões | Foi capaz de implementar uma resposta às previsões que funciona de forma consistente com previsões do mesmo valor. | Foi capaz de implementar uma resposta que não depende das previsões, como apenas enviar dados brutos para um IoT Hub. | Não foi capaz de programar o dispositivo para responder às previsões. |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.