<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T22:56:09+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "pt"
}
-->
# Enviar notificações usando Twilio

## Instruções

No teu código até agora, apenas registaste a distância até à geofence. Nesta tarefa, precisarás de adicionar uma notificação, seja uma mensagem de texto ou um email, quando as coordenadas GPS estiverem dentro da geofence.

O Azure Functions oferece várias opções para bindings, incluindo serviços de terceiros como o Twilio, uma plataforma de comunicações.

* Cria uma conta gratuita em [Twilio.com](https://www.twilio.com)
* Lê a documentação sobre como ligar Azure Functions ao Twilio SMS na [página de bindings Twilio para Azure Functions nos documentos da Microsoft](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lê a documentação sobre como ligar Azure Functions ao Twilio SendGrid para enviar emails na [página de bindings SendGrid para Azure Functions nos documentos da Microsoft](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Adiciona o binding à tua aplicação Functions para seres notificado sobre as coordenadas GPS estarem dentro ou fora da geofence - mas não ambas.

## Critérios de Avaliação

| Critérios | Exemplar | Adequado | Necessita de Melhorias |
| --------- | -------- | -------- | ---------------------- |
| Configurar os bindings das funções e receber um email ou SMS | Foi capaz de configurar os bindings das funções e receber um email ou SMS quando dentro ou fora da geofence, mas não ambas | Foi capaz de configurar os bindings, mas não conseguiu enviar o email ou SMS, ou apenas conseguiu enviar quando as coordenadas estavam tanto dentro como fora | Não conseguiu configurar os bindings nem enviar um email ou SMS |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.