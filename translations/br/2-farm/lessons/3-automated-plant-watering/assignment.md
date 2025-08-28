<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T04:19:01+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "br"
}
-->
# Construa um ciclo de irrigação mais eficiente

## Instruções

Esta lição abordou como controlar um relé usando dados de sensores, e esse relé, por sua vez, pode controlar uma bomba para um sistema de irrigação. Para um volume definido de solo, operar uma bomba por um tempo fixo deve sempre ter o mesmo impacto na umidade do solo. Isso significa que você pode ter uma ideia de quantos segundos de irrigação correspondem a uma certa queda na leitura de umidade do solo. Usando esses dados, você pode construir um sistema de irrigação mais controlado.

Para esta tarefa, você calculará quanto tempo a bomba deve funcionar para alcançar um aumento específico na umidade do solo.

> ⚠️ Se você estiver usando hardware IoT virtual, pode seguir este processo, mas simular os resultados aumentando manualmente a leitura de umidade do solo por uma quantidade fixa a cada segundo em que o relé estiver ligado.

1. Comece com o solo seco. Meça a umidade do solo.

1. Adicione uma quantidade fixa de água, seja operando a bomba por 1 segundo ou despejando uma quantidade fixa de água.

    > A bomba deve sempre operar a uma taxa constante, então, a cada segundo que a bomba funcionar, ela deve fornecer a mesma quantidade de água.

1. Aguarde até que o nível de umidade do solo se estabilize e faça uma leitura.

1. Repita isso várias vezes e crie uma tabela com os resultados. Um exemplo dessa tabela é dado abaixo.

    | Tempo total da bomba | Umidade do solo | Redução |
    | --- | --: | -: |
    | Seco | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calcule um aumento médio na umidade do solo por segundo de água. No exemplo acima, cada segundo de água reduz a leitura em uma média de 20,3.

1. Use esses dados para melhorar a eficiência do código do servidor, operando a bomba pelo tempo necessário para atingir o nível de umidade desejado.

## Rubrica

| Critério | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Capturar dados de umidade do solo | É capaz de capturar várias leituras após adicionar quantidades fixas de água | É capaz de capturar algumas leituras com quantidades fixas de água | Só consegue capturar uma ou duas leituras, ou não consegue usar quantidades fixas de água |
| Calibrar o código do servidor | É capaz de calcular uma redução média na leitura de umidade do solo e atualizar o código do servidor para usar isso | É capaz de calcular uma redução média, mas não consegue atualizar o código do servidor, ou não consegue calcular corretamente uma média, mas usa esse valor para atualizar corretamente o código do servidor | Não é capaz de calcular uma média ou atualizar o código do servidor |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.