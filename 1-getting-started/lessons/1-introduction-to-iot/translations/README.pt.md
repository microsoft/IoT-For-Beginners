# Introdução à IoT

![Um sketchnote de visão geral desta lição](../../../../sketchnotes/lesson-1.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Clique na imagem para uma versão maior.

## Questionário pré-aula

[Questionário pré-aula](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/1)

## Introdução

Esta lição cobre alguns dos tópicos introdutórios sobre a Internet das Coisas e mostra como configurar seu hardware.

Nesta lição, vamos cobrir:

* [O que é a 'Internet das Coisas'?](#o-que-é-a-internet-das-coisas)
* [Dispositivos IoT](#dispositivos-iot)
* [Configure seu dispositivo](#configure-seu-dispositivo)
* [Aplicações de IoT](#aplicações-de-iot)
* [Exemplos de dispositivos IoT que você pode ter ao seu redor](#exemplos-de-dispositivos-iot-que-você-pode-ter-ao-seu-redor)

## O que é a 'Internet das Coisas'?

O termo 'Internet das Coisas' foi cunhado por [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) em 1999, para se referir à conexão da Internet ao mundo físico por meio de sensores. Desde então, o termo tem sido usado para descrever qualquer dispositivo que interage com o mundo físico ao seu redor, seja reunindo dados de sensores ou fornecendo interações com o mundo real por meio de atuadores (dispositivos que fazem algo como ligar um interruptor ou acender um LED ), geralmente conectado a outros dispositivos ou à Internet.

> **Sensores** coletam informações do mundo, como medição de velocidade, temperatura ou localização.
>
> **Atuadores** convertem sinais elétricos em interações com o mundo real, como acionar um interruptor, acender luzes, fazer sons ou enviar sinais de controle para outro hardware, por exemplo, para ligar uma tomada.

A IoT como uma área de tecnologia é mais do que apenas dispositivos - inclui serviços baseados em nuvem que podem processar os dados do sensor ou enviar solicitações para atuadores conectados a dispositivos IoT. Também inclui dispositivos que não têm ou não precisam de conectividade com a Internet, geralmente chamados de dispositivos de borda. São dispositivos que podem processar e responder a dados de sensores eles próprios, geralmente usando modelos de IA treinados na nuvem.

A IoT é um campo de tecnologia em rápido crescimento. Estima-se que até o final de 2020, 30 bilhões de dispositivos IoT foram implantados e conectados à Internet. Olhando para o futuro, estima-se que até 2025, os dispositivos IoT estarão reunindo quase 80 zetabytes de dados ou 80 trilhões de gigabytes. São muitos dados!

![Um gráfico mostrando dispositivos IoT ativos ao longo do tempo, com uma tendência de aumento de menos de 5 bilhões em 2015 para mais de 30 bilhões em 2025](../../../../images/connected-iot-devices.svg)

✅ Faça uma pequena pesquisa: quanto dos dados gerados pelos dispositivos IoT é realmente usado e quanto é desperdiçado? Por que tantos dados são ignorados?

Esses dados são a chave para o sucesso da IoT. Para ser um desenvolvedor de IoT bem-sucedido, você precisa entender os dados que precisa coletar, como coletá-los, como tomar decisões com base neles e como usar essas decisões para interagir com o mundo físico, se necessário.

## Dispositivos IoT

O **T** em IoT significa **Coisas** - dispositivos que interagem com o mundo físico ao seu redor, seja coletando dados de sensores ou fornecendo interações com o mundo real por meio de atuadores.

Dispositivos para produção ou uso comercial, como rastreadores de condicionamento físico para consumidores ou controladores de máquinas industriais, geralmente são feitos sob medida. Eles usam placas de circuito personalizadas, talvez até processadores personalizados, projetados para atender às necessidades de uma tarefa específica, seja ela pequena o suficiente para caber em um pulso ou robusta o suficiente para funcionar em um ambiente de fábrica de alta temperatura, alto estresse ou alta vibração.

Como um desenvolvedor que está aprendendo sobre IoT ou criando um protótipo de dispositivo, você precisará começar com um kit de desenvolvedor. Esses são dispositivos IoT de uso geral projetados para serem usados ​​por desenvolvedores, geralmente com recursos que você não teria em um dispositivo de produção, como um conjunto de pinos externos para conectar sensores ou atuadores, hardware para suportar depuração ou recursos adicionais que adicionaria custos desnecessários ao fazer uma grande rodada de fabricação.

Esses kits de desenvolvedor geralmente se enquadram em duas categorias - microcontroladores e computadores de placa única. Eles serão apresentados aqui e entraremos em mais detalhes na próxima lição.

> 💁 Seu telefone também pode ser considerado um dispositivo IoT de uso geral, com sensores e atuadores integrados, com diferentes aplicativos que usam os sensores e atuadores de maneiras diferentes com diferentes serviços em nuvem. Você pode até encontrar alguns tutoriais de IoT que usam um aplicativo de telefone como um dispositivo de IoT.

### Microcontroladores

Um microcontrolador (também conhecido como MCU, abreviação de microcontroller unit) é um pequeno computador que consiste em:

🧠 Uma ou mais unidades de processamento central (CPUs) - o 'cérebro' do microcontrolador que executa seu programa

💾 Memória (RAM e memória de programa) - onde seu programa, dados e variáveis ​​são armazenados

🔌 Conexões de entrada/saída (I/O) programáveis ​​- para falar com periféricos externos (dispositivos conectados), como sensores e atuadores

Microcontroladores são tipicamente dispositivos de computação de baixo custo, com preços médios para aqueles usados ​​em hardware customizado caindo para cerca de US$0,50, e alguns dispositivos tão baratos quanto US$0,03. Os kits de desenvolvedor podem começar em US$4, com custos aumentando à medida que você adiciona mais recursos. O [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), um kit de desenvolvedor de microcontrolador da [Seeed studios](https://www.seeedstudio.com) que tem sensores, atuadores, Wi-Fi e uma tela custam cerca de US$30.

![Um Wio Terminal](../../../../images/wio-terminal.png)

> 💁 Ao pesquisar por microcontroladores na Internet, tenha cuidado ao pesquisar pelo termo **MCU**, pois isso trará muitos resultados para o Universo Cinematográfico Marvel (Marvel Cinematic Universe), não microcontroladores.

Os microcontroladores são projetados para serem programados para realizar um número limitado de tarefas muito específicas, em vez de serem computadores de uso geral, como PCs ou Macs. Exceto em cenários muito específicos, você não pode conectar um monitor, teclado e mouse e usá-los para tarefas de propósito geral.

Os kits de desenvolvedor de microcontroladores geralmente vêm com sensores e atuadores adicionais a bordo. A maioria das placas terá um ou mais LEDs que você pode programar, junto com outros dispositivos, como plugues padrão para adicionar mais sensores ou atuadores usando ecossistemas de vários fabricantes ou sensores embutidos (geralmente os mais populares, como sensores de temperatura). Alguns microcontroladores possuem conectividade sem fio integrada, como Bluetooth ou WiFi, ou possuem microcontroladores adicionais na placa para adicionar essa conectividade.

> 💁 Microcontroladores geralmente são programados em C/C++.

### Computadores de placa única

Um computador de placa única é um pequeno dispositivo de computação que possui todos os elementos de um computador completo contidos em uma única placa pequena. Esses são dispositivos que têm especificações próximas a um desktop ou laptop PC ou Mac, executam um sistema operacional completo, mas são pequenos, usam menos energia e são substancialmente mais baratos.

![Um Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

O Raspberry Pi é um dos computadores de placa única mais populares.

Como um microcontrolador, os computadores de placa única têm CPU, memória e pinos de entrada/saída, mas têm recursos adicionais, como um chip gráfico para permitir a conexão de monitores, saídas de áudio e portas USB para conectar teclados a mouses e outros dispositivos USB padrão como webcams ou armazenamento externo. Os programas são armazenados em cartões SD ou discos rígidos junto com um sistema operacional, em vez de um chip de memória embutido na placa.

> 🎓 Você pode pensar em um computador de placa única como uma versão menor e mais barata do PC ou Mac em que você está lendo isso, com a adição de pinos GPIO (entrada/saída de uso geral) para interagir com sensores e atuadores.

Os computadores de placa única são computadores completos, portanto, podem ser programados em qualquer linguagem. Os dispositivos IoT são normalmente programados em Python.

### Opções de hardware para o resto das lições

Todas as lições subsequentes incluem tarefas usando um dispositivo IoT para interagir com o mundo físico e se comunicar com a nuvem. Cada lição oferece suporte a 3 opções de dispositivo - Arduino (usando um Wio Terminal da Seeed Studios) ou um computador de placa única, seja ele um dispositivo físico (um Raspberry Pi 4) ou um computador de placa única virtual rodando em seu PC ou Mac.

Você pode ler sobre o hardware necessário para completar todas as tarefas no [guia do hardware](../../../../hardware.md).

> 💁 Você não precisa comprar nenhum hardware IoT para completar as atribuições, você pode fazer tudo usando um computador de placa única virtual.

A escolha do hardware depende de você - depende do que você tem disponível em casa ou na escola e de que linguagem de programação você conhece ou planeja aprender. Ambas as variantes de hardware usarão o mesmo ecossistema de sensores, portanto, se você começar por um caminho, poderá mudar para o outro sem ter que substituir a maior parte do kit. O computador de placa única virtual será o equivalente a aprender em um Raspberry Pi, com a maior parte do código transferível para o Pi se você eventualmente conseguir um dispositivo e sensores.

### Kit de desenvolvedor do Arduino

Se você estiver interessado em aprender o desenvolvimento de microcontroladores, poderá concluir as tarefas usando um dispositivo Arduino. Você precisará de um conhecimento básico de programação C/C++, pois as lições ensinarão apenas códigos relevantes para a estrutura do Arduino, os sensores e atuadores em uso e as bibliotecas que interagem com a nuvem.

As tarefas usarão o [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) com a [extensão PlatformIO para desenvolvimento de microcontrolador](https://platformio.org). Você também pode usar o IDE do Arduino se tiver experiência com essa ferramenta, pois as instruções não serão fornecidas.

### Kit de desenvolvedor de computador de placa única

Se estiver interessado em aprender o desenvolvimento de IoT usando computadores de placa única, você pode concluir as tarefas usando um Raspberry Pi ou um dispositivo virtual em execução no seu PC ou Mac.

Você precisará de um conhecimento básico de programação Python, já que as lições ensinarão apenas códigos relevantes para os sensores e atuadores em uso e as bibliotecas que interagem com a nuvem.

> 💁 Se você quiser aprender a codificar em Python, confira as duas séries de vídeo a seguir:
>
> * [Python para iniciantes](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mais Python para iniciantes](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

As tarefas usarão o [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Se estiver usando um Raspberry Pi, você pode executar seu Pi usando a versão desktop completa do Raspberry Pi OS e fazer toda a codificação diretamente no Pi usando [a versão do VS Code para o Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn) ou executar seu Pi como um dispositivo sem cabeça e codificar a partir de seu PC ou Mac usando o VS Code com a [extensão SSH remota](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) que permite que você se conecte ao seu Pi e edite, depure e execute o código como se você estivesse codificando nele diretamente.

Se você usar a opção de dispositivo virtual, codificará diretamente no seu computador. Em vez de acessar sensores e atuadores, você usará uma ferramenta para simular esse hardware, fornecendo valores de sensor que você pode definir e mostrando os resultados dos atuadores na tela.

## Configure seu dispositivo

Antes de começar a programar seu dispositivo IoT, você precisará fazer algumas configurações. Siga as instruções relevantes abaixo, dependendo de qual dispositivo você irá usar.

> 💁 Se você ainda não tem um dispositivo, consulte o [guia de hardware](../../../../hardware.md) para ajudar a decidir qual dispositivo você vai usar e qual hardware adicional você precisa comprar. Você não precisa comprar hardware, pois todos os projetos podem ser executados em hardware virtual.

Essas instruções incluem links para sites de terceiros dos criadores do hardware ou das ferramentas que você usará. Isso é para garantir que você esteja sempre usando as instruções mais atualizadas para as várias ferramentas e hardware.

Trabalhe com o guia relevante para configurar seu dispositivo e concluir um projeto 'Hello World'. Esta será a primeira etapa na criação de uma luz noturna IoT nas 4 lições desta parte de introdução.

* [Arduino - Wio Terminal](wio-terminal.pt.md)
* [Computador de placa única - Raspberry Pi](pi.pt.md)
* [Computador de placa única - Dispositivo virtual](virtual-device.pt.md)

✅ Você usará o VS Code para o Arduino e para computadores de placa única. Se você nunca usou isso antes, leia mais sobre isso no [site do VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Aplicações de IoT

A IoT cobre uma grande variedade de casos de uso, em alguns grupos amplos:

* IoT do Consumidor
* IoT Comercial
* IoT Industrial
* IoT para Infraestrutura

✅ Faça uma pequena pesquisa: para cada uma das áreas descritas abaixo, encontre um exemplo concreto que não seja fornecido no texto.

### IoT do Consumidor

A IoT do consumidor se refere a dispositivos IoT que os consumidores comprarão e usarão em casa. Alguns desses dispositivos são incrivelmente úteis, como alto-falantes inteligentes, sistemas de aquecimento inteligentes e aspiradores de pó robóticos. Outros são questionáveis ​​em sua utilidade, como torneiras controladas por voz, o que significa que você não pode desligá-los, pois o controle de voz não pode ouvi-lo por causa do som de água corrente.

Os dispositivos IoT do consumidor estão capacitando as pessoas a realizar mais em seus arredores, especialmente 1 bilhão de pessoas com algum tipo de deficiência. Aspiradores de pó robóticos podem fornecer pisos limpos para pessoas com problemas de mobilidade que não podem aspirar a si mesmas, fornos controlados por voz permitem que pessoas com visão ou controle motor limitados aqueçam seus fornos apenas com a voz, monitores de saúde podem permitir que os pacientes monitorem suas condições crônicas com atualizações mais regulares e mais detalhadas. Esses dispositivos estão se tornando tão onipresentes que até crianças pequenas estão usando-os como parte de suas vidas diárias, por exemplo, alunos fazendo aulas virtuais durante a pandemia do COVID configurando cronômetros em dispositivos domésticos inteligentes para rastrear seus trabalhos escolares ou alarmes para lembrá-los das próximas reuniões da turma.

✅ Quais dispositivos IoT do consumidor você tem consigo ou em casa?

### IoT comercial

A IoT comercial cobre o uso da IoT no local de trabalho. Em um ambiente de escritório, pode haver sensores de ocupação e detectores de movimento para gerenciar a iluminação e o aquecimento para apenas manter as luzes e o aquecimento desligados quando não forem necessários, reduzindo o custo e as emissões de carbono. Em uma fábrica, os dispositivos IoT podem monitorar os riscos à segurança, como trabalhadores sem capacete ou ruído que atingiu níveis perigosos. No varejo, os dispositivos IoT podem medir a temperatura do armazenamento refrigerado, alertando o proprietário da loja se uma geladeira ou freezer está fora da faixa de temperatura exigida, ou podem monitorar os itens nas prateleiras para direcionar os funcionários para reabastecer os produtos que foram vendidos. A indústria de transporte está confiando cada vez mais na IoT para monitorar a localização dos veículos, rastrear a quilometragem na estrada para cobrança do usuário da estrada, monitorar as horas do motorista e interromper a conformidade ou notificar a equipe quando um veículo se aproxima de um depósito para se preparar para carga ou descarga

✅ Quais dispositivos IoT comerciais você tem em sua escola ou local de trabalho?

### IoT Industrial (IIoT)

IoT industrial, ou IIoT, é o uso de dispositivos IoT para controlar e gerenciar máquinas em grande escala. Isso cobre uma ampla gama de casos de uso, desde fábricas até agricultura digital.

As fábricas usam dispositivos IoT de muitas maneiras diferentes. A maquinaria pode ser monitorada com vários sensores para rastrear coisas como temperatura, vibração e velocidade de rotação. Esses dados podem então ser monitorados para permitir que a máquina seja parada se ficar fora de certas tolerâncias - ela fica muito quente e é desligada, por exemplo. Esses dados também podem ser coletados e analisados ​​ao longo do tempo para fazer a manutenção preditiva, onde os modelos de IA examinam os dados que levam a uma falha e os usam para prever outras falhas antes que elas aconteçam.

A agricultura digital é importante se o planeta deseja alimentar a população crescente, especialmente para os 2 bilhões de pessoas em 500 milhões de famílias que sobrevivem da [agricultura de subsistência](https://pt.wikipedia.org/wiki/Agricultura_de_subsist%C3%AAncia). A agricultura digital pode variar de alguns sensores de um dígito de dólar a enormes configurações comerciais. Um agricultor pode começar monitorando as temperaturas e usar o [grau-dia de crescimento](https://wikipedia.org/wiki/Growing_degree-day) para prever quando uma safra estará pronta para a colheita. Eles podem conectar o monitoramento da umidade do solo a sistemas de rega automatizados para fornecer a suas plantas a quantidade necessária de água, mas não mais para garantir que suas safras não sequem sem desperdício de água. Os agricultores estão indo mais longe e usando drones, dados de satélite e IA para monitorar o crescimento da safra, doenças e qualidade do solo em grandes áreas de terras agrícolas.

✅ Que outros dispositivos IoT podem ajudar os agricultores?

### IoT para Infraestrutura

A IoT para infraestrutura monitora e controla a infraestrutura local e global que as pessoas usam todos os dias.

[Cidades inteligentes](https://pt.wikipedia.org/wiki/Cidade_inteligente) são áreas urbanas que usam dispositivos IoT para coletar dados sobre a cidade e usá-los para melhorar o funcionamento da mesma. Essas cidades geralmente são administradas com a colaboração entre governos locais, universidades e empresas locais, rastreando e gerenciando coisas que variam de transporte a estacionamento e poluição. Por exemplo, em Copenhague, Dinamarca, a poluição do ar é importante para os residentes locais, por isso é medida e os dados são usados ​​para fornecer informações sobre as rotas de ciclismo e corrida mais limpas.

[Redes de energia inteligentes](https://pt.wikipedia.org/wiki/Rede_el%C3%A9trica_inteligente) permitem uma melhor análise da demanda de energia, reunindo dados de uso no nível de residências individuais. Esses dados podem orientar decisões em nível de país, incluindo onde construir novas usinas de energia, e em nível pessoal, dando aos usuários insights sobre quanta energia eles estão usando, quando estão usando, e até mesmo sugestões sobre como reduzir custos, como por exemplo carregar carros elétricos à noite.

✅ Se você pudesse adicionar dispositivos IoT para medir qualquer coisa onde você mora, o que seria?

## Exemplos de dispositivos IoT que você pode ter ao seu redor

Você ficaria surpreso com a quantidade de dispositivos IoT que tem ao seu redor. Estou escrevendo isso de casa e tenho os seguintes dispositivos conectados à Internet com recursos inteligentes, como controle de aplicativos, controle de voz ou a capacidade de enviar dados para mim através do meu telefone:

* Vários alto-falantes inteligentes
* Geladeira, lava-louças, forno e micro-ondas
* Monitor de eletricidade para painéis solares
* Plugues inteligentes
* Campainha de vídeo e câmeras de segurança
* Termostato inteligente com vários sensores inteligentes de ambiente
* Abridor de porta de garagem
* Sistemas de entretenimento doméstico e TVs controladas por voz
* Luzes
* Rastreadores de condicionamento físico e de saúde

Todos esses tipos de dispositivos possuem sensores e/ou atuadores e se comunicam com a Internet. Posso dizer pelo meu telefone se a porta da garagem está aberta e pedir ao meu alto-falante inteligente para fechá-la para mim. Posso até definir um temporizador para que, se ainda estiver aberta à noite, feche automaticamente. Quando minha campainha toca, posso ver no meu telefone quem está lá em qualquer lugar do mundo e falar com eles por meio de um alto-falante e microfone embutidos na campainha. Posso monitorar minha glicemia, frequência cardíaca e padrões de sono, procurando padrões nos dados para melhorar minha saúde. Posso controlar minhas luzes por meio da nuvem e ficar sentado no escuro quando minha conexão com a Internet cair.

---

## 🚀 Desafio

Liste o máximo de dispositivos IoT que puder em sua casa, escola ou local de trabalho - pode haver mais do que você pensa!

## Questionário pós-aula

[Questionário pós-aula](https://thankful-pond-0eba8f10f.1.azurestaticapps.net/quiz/2)

## Revisão e autoestudo

Leia sobre os benefícios e as falhas dos projetos de IoT do consumidor. Verifique os sites de notícias para obter artigos sobre quando deu errado, como questões de privacidade, problemas de hardware ou problemas causados ​​por falta de conectividade.

Alguns exemplos:

* Verifique a conta do Twitter **[Internet of Sh*t](https://twitter.com/internetofshit) ** *(aviso de palavrões)* para obter alguns bons exemplos de falhas com a IoT do consumidor.
* [c|net - Meu Apple Watch salvou minha vida: 5 pessoas compartilham suas histórias](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Técnico ADT se declara culpado de espionar imagens de câmeras de clientes por anos](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on- customer-camera-feeds-for-years/) *(aviso de gatilho - voyeurismo não consensual)*

## Tarefa

[Investigar um projeto IoT](assignment.pt.md)