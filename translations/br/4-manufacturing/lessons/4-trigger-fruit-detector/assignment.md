<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T02:41:38+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "br"
}
-->
# Construir um detector de qualidade de frutas

## Instruções

Construa o detector de qualidade de frutas!

Utilize tudo o que você aprendeu até agora para criar o protótipo do detector de qualidade de frutas. Acione a classificação de imagens com base na proximidade usando um modelo de IA executado na borda, armazene os resultados da classificação em um armazenamento e controle um LED com base no grau de maturação da fruta.

Você deve ser capaz de montar isso utilizando o código que escreveu anteriormente em todas as lições até agora.

## Critérios de Avaliação

| Critério | Exemplar | Adequado | Precisa Melhorar |
| -------- | --------- | -------- | ---------------- |
| Configurar todos os serviços | Foi capaz de configurar um IoT Hub, uma aplicação de funções do Azure e o armazenamento do Azure | Foi capaz de configurar o IoT Hub, mas não a aplicação de funções do Azure ou o armazenamento do Azure | Não conseguiu configurar nenhum serviço de IoT na internet |
| Monitorar proximidade e enviar os dados para o IoT Hub se um objeto estiver mais próximo do que uma distância pré-definida e acionar a câmera via um comando | Foi capaz de medir a distância e enviar uma mensagem para o IoT Hub quando um objeto estava próximo o suficiente, e enviar um comando para acionar a câmera | Foi capaz de medir a proximidade e enviar para o IoT Hub, mas não conseguiu enviar um comando para a câmera | Não conseguiu medir a distância e enviar uma mensagem para o IoT Hub, ou acionar um comando |
| Capturar uma imagem, classificá-la e enviar os resultados para o IoT Hub | Foi capaz de capturar uma imagem, classificá-la usando um dispositivo de borda e enviar os resultados para o IoT Hub | Foi capaz de classificar a imagem, mas não usando um dispositivo de borda, ou não conseguiu enviar os resultados para o IoT Hub | Não conseguiu classificar uma imagem |
| Ligar ou desligar o LED dependendo dos resultados da classificação usando um comando enviado para um dispositivo | Foi capaz de ligar um LED via comando se a fruta estivesse verde | Foi capaz de enviar o comando para o dispositivo, mas não controlar o LED | Não conseguiu enviar um comando para controlar o LED |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte oficial. Para informações críticas, recomenda-se a tradução profissional feita por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.