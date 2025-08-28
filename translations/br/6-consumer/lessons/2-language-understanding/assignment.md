<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T02:55:04+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "br"
}
-->
# Cancelar o temporizador

## Instruções

Até agora nesta lição, você treinou um modelo para entender como configurar um temporizador. Outra funcionalidade útil é cancelar um temporizador - talvez o pão já esteja pronto e possa ser retirado do forno antes que o tempo termine.

Adicione uma nova intenção ao seu aplicativo LUIS para cancelar o temporizador. Não será necessário usar entidades, mas será necessário fornecer algumas frases de exemplo. Lide com isso no seu código serverless se essa for a intenção principal, registrando que a intenção foi reconhecida e retornando uma resposta apropriada.

## Rubrica

| Critério | Exemplar | Adequado | Precisa de Melhorias |
| -------- | --------- | -------- | -------------------- |
| Adicionar a intenção de cancelar o temporizador ao aplicativo LUIS | Foi capaz de adicionar a intenção e treinar o modelo | Foi capaz de adicionar a intenção, mas não de treinar o modelo | Não foi capaz de adicionar a intenção nem de treinar o modelo |
| Lidar com a intenção no aplicativo serverless | Foi capaz de detectar a intenção como a principal e registrá-la | Foi capaz de detectar a intenção como a principal | Não foi capaz de detectar a intenção como a principal |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.