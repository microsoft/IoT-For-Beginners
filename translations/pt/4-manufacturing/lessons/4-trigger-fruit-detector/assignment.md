<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-25T21:12:24+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "pt"
}
-->
# Construir um detetor de qualidade de fruta

## Instruções

Construa o detetor de qualidade de fruta!

Utilize tudo o que aprendeu até agora para criar o protótipo do detetor de qualidade de fruta. Ative a classificação de imagens com base na proximidade, utilizando um modelo de IA a funcionar na edge, armazene os resultados da classificação e controle um LED com base no estado de maturação da fruta.

Deverá conseguir montar este projeto utilizando o código que escreveu em todas as lições até agora.

## Rubrica

| Critérios | Exemplar | Adequado | Necessita de Melhorias |
| --------- | --------- | -------- | ---------------------- |
| Configurar todos os serviços | Foi capaz de configurar um IoT Hub, uma aplicação de funções Azure e armazenamento Azure | Foi capaz de configurar o IoT Hub, mas não a aplicação de funções Azure ou o armazenamento Azure | Não conseguiu configurar nenhum serviço IoT na internet |
| Monitorizar a proximidade e enviar os dados para o IoT Hub se um objeto estiver mais próximo do que uma distância pré-definida e ativar a câmara através de um comando | Foi capaz de medir a distância e enviar uma mensagem para o IoT Hub quando um objeto estava suficientemente próximo, e enviar um comando para ativar a câmara | Foi capaz de medir a proximidade e enviar para o IoT Hub, mas não conseguiu enviar um comando para a câmara | Não conseguiu medir a distância, enviar uma mensagem para o IoT Hub ou ativar um comando |
| Capturar uma imagem, classificá-la e enviar os resultados para o IoT Hub | Foi capaz de capturar uma imagem, classificá-la utilizando um dispositivo edge e enviar os resultados para o IoT Hub | Foi capaz de classificar a imagem, mas não utilizando um dispositivo edge, ou não conseguiu enviar os resultados para o IoT Hub | Não conseguiu classificar uma imagem |
| Ligar ou desligar o LED dependendo dos resultados da classificação utilizando um comando enviado para um dispositivo | Foi capaz de ligar um LED através de um comando se a fruta estivesse verde | Foi capaz de enviar o comando para o dispositivo, mas não controlar o LED | Não conseguiu enviar um comando para controlar o LED |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.