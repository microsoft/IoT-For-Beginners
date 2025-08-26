<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-25T20:51:51+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "pt"
}
-->
# Fabrico e processamento - usar IoT para melhorar o processamento de alimentos

Quando os alimentos chegam a um centro de distribuição ou unidade de processamento, nem sempre são enviados diretamente para os supermercados. Muitas vezes, os alimentos passam por várias etapas de processamento, como a classificação por qualidade. Este era um processo que costumava ser manual - começava no campo, quando os trabalhadores colhiam apenas os frutos maduros, e depois, na fábrica, os frutos passavam por uma esteira transportadora, onde os funcionários removiam manualmente os frutos machucados ou podres. Tendo eu próprio colhido e classificado morangos como trabalho de verão durante a escola, posso confirmar que não é uma tarefa agradável.

Configurações mais modernas dependem de IoT para a classificação. Alguns dos primeiros dispositivos, como os classificadores da [Weco](https://wecotek.com), utilizam sensores óticos para detetar a qualidade dos produtos, rejeitando, por exemplo, tomates verdes. Estes dispositivos podem ser utilizados em colhedoras na própria quinta ou em unidades de processamento.

À medida que se fazem avanços na Inteligência Artificial (IA) e no Machine Learning (ML), estas máquinas podem tornar-se mais sofisticadas, utilizando modelos de ML treinados para distinguir entre frutos e objetos estranhos, como pedras, terra ou insetos. Estes modelos também podem ser treinados para detetar a qualidade dos frutos, não apenas frutos machucados, mas também sinais precoces de doenças ou outros problemas nas colheitas.

> 🎓 O termo *modelo de ML* refere-se ao resultado do treino de software de machine learning com um conjunto de dados. Por exemplo, pode treinar um modelo de ML para distinguir entre tomates maduros e verdes, e depois usar o modelo em novas imagens para verificar se os tomates estão maduros ou não.

Nestes 4 módulos, aprenderá como treinar modelos de IA baseados em imagens para detetar a qualidade dos frutos, como utilizá-los a partir de um dispositivo IoT e como executá-los na edge - ou seja, diretamente num dispositivo IoT em vez de na cloud.

> 💁 Estes módulos utilizarão alguns recursos na cloud. Se não concluir todos os módulos deste projeto, certifique-se de que [limpa o seu projeto](../clean-up.md).

## Tópicos

1. [Treinar um detetor de qualidade de frutos](./lessons/1-train-fruit-detector/README.md)
1. [Verificar a qualidade dos frutos a partir de um dispositivo IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Executar o seu detetor de frutos na edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [Acionar a deteção de qualidade de frutos a partir de um sensor](./lessons/4-trigger-fruit-detector/README.md)

## Créditos

Todos os módulos foram escritos com ♥️ por [Jen Fox](https://github.com/jenfoxbot) e [Jim Bennett](https://GitHub.com/JimBobBennett)

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se uma tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.