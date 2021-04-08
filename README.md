<<<<<<< HEAD
# Projeto da disciplina de ITP - 2020.2

O projeto da disciplina de ITP deste semestre consiste em você desenvolver uma bot para jogar um jogo clássico de cartas: **Buraco**.
Para quem nunca jogou, é possível experimentar o jogo em sites online, como https://buracoon.com.br/game ou jogar contra o bot exemplo do projeto (apresentado mais pra frente).

- [Regras adotadas](#regras-adotadas)
- [Funcionamento da partida](#funcionamento-da-partida)
- [Pontapé inicial](#pontapé-inicial)
- [Comunicação](#comunicação)
- [Término da partida](#término-da-partida)
- [Debugar](#debugar)


# Regras adotadas

O jogo de Buraco foi criado na década de 40 no Uruguai e, desde então, foi sofrendo adaptações e alterações. Isso fez com que haja diferentes versões de regras. Existe o Buraco simples, Buraco duro, Buraco com ou sem trincas, com ou sem Joker etc. Devido a essas variações e às simplificações que realizamos para o projeto de ITP, é necessário especificar o que vale ou não vale na versão do projeto.

De qualquer forma, em todas as versões, o objetivo do jogo é fazer o máximo de pontos que puder, baixando jogos (sequências de cartas) na mesa.

### Preparação

Antes de começar a partida, cada jogador recebe 11 cartas (que não devem ser reveladas), uma é colocada no centro da mesa com a face para cima e o resto das cartas é colocada em pilha com as faces para baixo. As cartas de cada jogador são chamadas de **mão** do jogador (aquelas que só ele conhece). A carta no centro servirá como início das cartas descartadas, ou **lixo**, enquanto as cartas voltadas para baixo servirão para puxar novas cartas, também chamado de  **deque de compra**.

Nessa versão do jogo, não teremos *mortos*, mas numa versão normal do Buraco, teríamos 2 outros conjuntos de 11 cartas separados que serviriam para os jogadores que terminarem suas cartas na mão.

### Partida

O jogo começa com um jogador qualquer (no projeto um jogador é escolhido aleatoriamente), que deve realizar a seguinte sequência de ações:

1. **Puxar uma carta**. A carta pode ser puxada do topo do deque de compra ou do topo do lixo. Porém, se for do lixo, é preciso baixar um novo jogo com a carta do topo e cartas da mão do jogador. Nesse novo jogo, pode ser usado um melé (coringa) para completar uma carta que esteja faltando. Depois que o jogo é baixado, todas as cartas restantes do lixo vão pra mão do jogador. Obs: o topo do lixo não pode ser "encaixado" em jogos existentes (já baixados).

2. **Formar jogos**. Depois da carta puxada, o jogador poderá baixar novos jogos ou completar jogos existentes com as cartas da mão. Essa etapa não é obrigatória, visto que nem sempre se tem jogos ou cartas para baixar.

3. **Descartar uma carta**. O jogador deve descartar uma de suas cartas na pilha de descarte (lixo). Ao fazer isso, seu turno termina e passa a vez ao próximo jogador.

O jogo continua com cada jogador repetindo essas 3 etapas (a segunda é opcional) até que um jogador não tenha mais carta na mão. Quando isso ocorrer, a partida termina (não há *morto* nessa versão) e passa a contagem de pontos. Veja portanto que não ganha quem baixa todas as cartas primeiro, mas quem faz mais pontos com os jogos baixados.

## Jogos

Jogos são sequências de no mínimo 3 cartas consecutivas do mesmo naipe. Na sequência, o Ás pode ser colocado tanto antes do 2 quando depois do rei (K). Assim, temos a sequinte ordem de cartas: *Ás, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K e Ás*, onde J é o valete (Jack), Q a rainha (Queen) e K o rei (King).

Qualquer sequência de 3 cartas ou mais do mesmo naipe nessa ordem é considerada um jogo e pode ser baixada. O 2 pode também servir de *coringa* (ou *melé*), substituindo uma carta da sequência que esteja faltando. Nesse caso, o naipe do 2 não importa. Assim, a sequência `[ 4♥ 5♥ 2♣ 7♥ ]` é um jogo válido. Vale salientar que apenas um melé pode ser usado num jogo. Logo, a sequência `[ 4♥ 5♥ 2♣ 7♥ 2♦ 9♥ ]` não é válida.

Quando um jogo é formado por 7 ou mais cartas é chamado de canastra. Para esse projeto, serão consideradas apenas 2 tipos de canastras, cada uma com uma pontuação própria:
* Canastra limpa: sequência de pelo menos 7 cartas sem usar melé (carta 2).
* Canastra suja: sequência de pelo menos 7 cartas, mas com o uso do melé.

Nessa versão do jogo, não é permitido trincas, que são sequência de cartas de mesmo valor e pelo menos 3 naipes diferentes.

## Pontuação

Quando a partida termina, os pontos dos jogadores são contabilizados e ganha quem somar mais pontos. São somados os pontos dos jogos baixados (os que estão na mão do jogador não conta), descontados os pontos das cartas da mão do jogador (ou seja, se tiver muita carta na mão vai ser descontado) e somados pontos para da "batida" (quem tiver descartado todas as cartas primeiro ganha um pouco mais).

Para calcular os pontos dos jogos baixados, soma-se os valores individuais das cartas de todos os jogos, mais os pontos de eventuais canastras formadas. As cartas valem os seguintes pontos:
* do 3 ao 7: 5 pontos
* 2 e do 8 ao K: 10 pontos
* Ás: 15 pontos

As canastram valem:
* Canastra limpa: 200 pontos.
* Canastra suja: 100 pontos.

O jogador que bater (descartar todas as cartas primeiro) terá um adicional de 100 pontos. O jogador que não bater terá consequente cartas na mão, cuja soma dos pontos (apresentados acima) será deduzida de seus jogos baixados.

## Dicas

Na elaboração das estratégias de seu bot, leve em consideração que pegar o lixo é muito importante. Como só pode pegar o lixo formando um jogo, suas cartas podem se acumular ao longo das rodadas. Quem o pegar terá, portanto, uma grande quantidade de cartas para formar novos jogos. Assim, é importante considerar, quando for descartar, cartas em que o adversário provavelmente não conseguirá formar jogo, para não permitir que o lixo seja pego.

# Funcionamento da partida

Buraco é um jogo onde duas duplas competem entre si. Ou seja é um jogo tanto competitivo quanto cooperativo (entre os integrantes da dupla). Portanto, normalmente se joga com 4 jogadores, mas pode-se também jogar apenas com 2 jogadores, numa versão *player vs. player*, e é dessa forma que iremos considerar no projeto. Seu bot jogará, portanto, contra outro bot.

No computador, cada bot será um processo diferente rodando de foma concorrente. Ambos serão gerenciados por um terceiro processo, que servirá de "juiz", definindo as jogadas válidas, calculando os pontos e dizendo quem ganhou, mas também gerenciando a troca de mensagens entre os processos dos bots.

É o juiz que irá lançar os processos dos bots (executar seus programas) e ficará de intermediário recebendo as ações dos bots em cada turno e repassando as ações válidas (e visíveis) para os outros bots. Essas informações são trocadas via entrada e saída padrão. Ou seja, o juiz irá ler da entrada-padrão e escrever na saída-padrão dos processos conforme as ações no jogo são realizadas. Assim, para o bot ler um dado do jogo (juiz) é necessário usar `scanf()`, `fgets()` ou equivalentes, enquanto para enviar dados para o jogo (juiz), é necessário usar `printf()`. 

# Pontapé inicial

### Código de base

Um códido que serve de exemplo para dar início ao desenvolvimento de um bot encontra-se no arquivo [bot.c](./bot.c). Nesse código, o bot no seu turno irá puxar uma carta da pilha de compra e depois descartar a carta puxada. Cabe a você melhorar sua estragégia de jogo.

Para testá-lo, você deve compilá-lo gerando um executável e, em seguida, executar o programa juiz (`./buraco`) passando o executável gerado como parâmetro. O programa `buraco` é um script desenvolvido em Javascript e, portanto, deve ser chamado usando o nodeJs.

Caso você não tenha o nodeJs instalado, pode fazê-lo a partir do endereço https://nodejs.org/pt-br/. O programa funciona com a versão 10 do Node ou mais recentes.

Se não desejar ou não puder instalar o nodeJs, é possível acessar estes mesmo arquivos no repl.it no endereço: https://replit.com/@Andre_MauricioM/itp-prj-20202. No repl.it, o botão "Play" irá compilar o arquivo `bot.c` e executará o script.

Porém, se estiver trabalhando localmente, as linhas a seguir fará esses passos.

```sh
$ gcc bot.c -o bot
$ node buraco.js bot
```

No exemplo acima, como apenas um executável foi passado como parâmetro (`bot`), o juiz irá lançar um processo especial que irá substituir o bot adversário. Esse processo irá interagir com o usuário, permitindo que você jogue contra seu bot e teste suas estratégias.

Caso queira competir com outro bot (ou mesmo fazer com que seu bot compita contra ele mesmo), é necessário passar o nome dos dois executáveis. Nesse caso, não haverá interação com o usuário.

```sh
$ node buraco.js bot1 bot2
```

### Estratégia de um bot simples

Para incrementar o bot de base, que apenas puxa uma carta e a solta, você pode quebrar o comportamento do seu bot em 2 possíveis estados e tentar implementar a seguinte estratégia:

1. **Puxar uma carta**: Verifique se a carta que seu adversário descartou forma jogo com as cartas que tem na mão. Se formar, pegue o lixo formando o jogo. Se não, puxe uma do deque de compras.
2. **Descartar uma carta**: Busque a carta da mão que esteja o mais longe de um possível jogo. Por exemplo, Se as cartas da mão forem `[ 4♥ 5♥ J♥ 3♣ 5♣ 8♣ ]`, `J♥` está mais longe de `5♥` (carta mais próxima dele) do que qualquer outra combinação de cartas. Assim, `J♥` seria uma carta potencial para ser descartada.

Vale salientar que, para realizar ações como *verificar se forma jogo* ou *buscar carta mais longe*, fica muito mais simples se as cartas estiverem ordenadas. Então, uma das principais rotinas do seu bot será *ordene um conjunto de cartas*.

Para ir além da estratégia descrita acima, será importante guardar informações do andamento da partida. Memorizar as cartas que estão no lixo, bem como os jogos que já foram baixados por seu bot e pelo seu adversário, é essencial. Mas memorizar não é problema para um bot. Basta guardar essas informações em arrays (lixo) e arrays de arrays (jogos do bot e jogos do adversário).

Quando seu bot estiver armazenando as cartas, o próximo passo será incrementar seus jogos já baixados. Assim, teria um estado entre *1. Puxar uma carta* e *2. Descartar uma carta* uma carta, que seria:

1. ½. **Anexar cartas a um jogo existente**: Verifique se cartas da mão encaixa em algum jogo já baixado. Enquanto existir adicione as cartas no jogo.

Com essas estratégias simples, seu bot já será capaz de ganhar de lavada do bot de base. Mas será que ganharia do bot de seu colega?! 😉


# Comunicação

## Início da partida

No início da partida, o juiz irá enviar para todos os bots as seguintes informações (uma em cada linha):
- Os identificadores de todos os jogadores (bots) separados por espaço
- O identificador do bot (seu identificador)
- As cartas que o bot tem na mão
- A carta que se encontra no topo da pilha de descarte (lixo).

O bot deverá, portanto, realizar a leitura de 4 linhas, como no exemplo abaixo.
```
bot1 bot2
bot1
2♥ 8♥ 10♥ Q♦ Q♦ 5♣ 6♠ 7♠ 10♠ K♠ A♠
4♣
```
Nesse exemplo, o `bot1` recebeu na 1ª linha a identificação dos bots participantes da partida (`bot1 bot2`), seguido de uma linha com seu identificador (`bot1`), seguido das 11 cartas de sua mão (`2♥ 8♥ 10♥ Q♦ Q♦ 5♣ 6♠ 7♠ 10♠ K♠ A♠`), seguido da carta que inicia o lixo (`4♣`). Seu adversário (`bot2`) irá receber dados diferentes na 2ª e na 3ª linhas.

O formato das cartas sempre começará com o valor da carta (`A`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`, `10`, `J`, `Q` ou `K`), seguido do seu naipe (`♥`, `♦`, `♣` ou `♠`).

Vale salientar que os caracteres dos naipes **não são caracteres ASCII**. São caracteres [Unicode](https://pt.wikipedia.org/wiki/Unicode), em específico o [UTF-8](https://pt.wikipedia.org/wiki/UTF-8). O padrão UTF-8 permite caracteres especiais da nossa língua, como `ç`, `ã`, `é` e outros que não estão presentes na tabela ASCII. O padrão UTF-8 estende a tabela ASCII permitindo que um caractere seja formado por mais de um byte. Assim, não leiam o `♥` como se fosse um único byte (usando `%c`), mas como string(`%s`). Além disso, quando forem comparar os naipes, usem `strcmp()` (ex: `if (strcmp(x, "♥") == 0)`).

Porém, para quem quiser entrar nos detalhes de cada byte dos naipes, eles são formados por 3, com os seguintes valores em hexa e decimal:
* `♦`: E2 (226) - 99 (153) - A6 (166)
* `♠`: E2 (226) - 99 (153) - A0 (160)
* `♥`: E2 (226) - 99 (153) - A5 (165)
* `♣`: E2 (226) - 99 (153) - A3 (163)

## A cada turno

No início de cada turno, o juiz enviará para todos os bots o identificador do bot que está "na vez" e aguardará uma ação desse bot a ser tomada.

A primeira ação deve obrigatoriamente puxar uma carta, que pode ser do deque de compra ou da pilha de descarte (lixo). Se puxar do lixo, o bot terá que formar um jogo com a carta que está no topo, encaixando-a numa sequência de cartas da mão. Ou seja, não é permitido encaixar num jogo já baixado. Formando o jogo, ele pegará todas as demais cartas do lixo para si.

Em seguida, o bot poderá baixar novos jogos, incluir cartas em jogos existentes ou descartar uma carta no lixo. No momento que descartar, termina sua vez e o próximo bot deve realizar suas ações.

Para realizar uma dessas ações o bot deverá enviar para a saída-padrão um dos seguintes comandos (strings):

- `GET_STOCK`:
  Puxa uma carta do deque de compra. Depois do comando, o bot deve ler da entrada-padrão a carta que puxou.
  Por exemplo:
  * envia: `GET_STOCK` (ex: `printf("GET_STOCK\n");`)
  * lê: `Q♣` (ex: `scanf("%s", &card);`)

- `GET_DISCARD [ c1 c2 ... ]`:
  Pega toda a pilha de descarte (lixo).
  Para isso, é necessário fazer um jogo com a carta do topo da pilha.
  `[ c1 c2 ... ]` são as cartas da mão a serem usadas no jogo. Pelo menos duas cartas da mão devem ser especificadas uma vez que um jogo válido tem no mínimo três cartas.
  Depois do comando, o bot deve ler uma linha com as cartas que se encontravam no lixo e que serão incorparadas à sua mão.
  Por exemplo (considerando que o topo do lixo é `5♠`):
  * envia para saída-padrão: `GET_DISCARD [ 6♠ 7♠ ]`
  * lê da entrada-padrão: `[ K♥ 4♦ 7♣ 9♣ J♣ J♣ 5♠ ]`

- `MELD_NEW [ c1 c2 c3 ... ]`:
  Baixa um jogo na mesa.
  `[ c1 c2 c3 ... ]` são as cartas da mão usadas para formar o jogo. Pelo menos três cartas da mão devem ser especificadas uma vez que um jogo válido tem no mínimo essa quantidade.
  Depois do comando, não há dados para ler da entrada-padrão.
  Por exemplo:
  * envia para saída-padrão: `MELD_NEW [ 5♠ 6♠ 7♠ ]`

- `MELD_JOIN ind [ c1 ... ]`:
  Anexa cartas a um jogo já existente.
  `ind` é o índice do jogo na ordem em que ele foi criado. Ou seja, o primeiro jogo criado pelo bot terá índice 0, o segundo 1 e assim por diante.
  `[ c1 ... ]` são as cartas da mão a serem anexadas no jogo. Deve-se especificar pelo menos uma carta.
  Depois do comando, não há dados para ler da entrada-padrão.
  Por exemplo:
  * envia para saída-padrão: `MELD_JOIN 0 [ 8♠ ]`

- `DISCARD c`:
  Descarta uma carta na pilha de descarte (lixo).
  `c` é a carta da mão que será descartada.
  Depois do comando, não há dados para ler da entrada-padrão.
  Por exemplo:
  * envia para saída-padrão: `DISCARD 3♠`

Todas os comandos executados por um bot são repassados para os demais bots, permitindo assim que todos os jogadores vejam o que está ocorrendo na partida. Porém, as respostas dos comandos são enviadas apenas para o bot autor do comando. Por exemplo, todos receberão uma mensagem de `GET_STOCK` quando esta for realizada por um bot, mas apenas ele receberá a carta que foi puxada.

Assim que um bot enviar o comando para descartar (`DISCARD`), seu turno termina e passa a ser a vez do outro bot jogar.

Seu bot deve seguir estritamente a sequência de envio e recebimento dos comandos. Se, por exemplo, o programa juiz estiver esperando um comando do seu bot e este estiver esperando dados do juiz, então seu bot não seguiu a sequência correta e o sistema entrou no que chamamos de **[deadlock](https://pt.wikipedia.org/wiki/Deadlock)**. Caso seu bot não responda em 3 segundos, o juíz irá matar o processo do seu bot e terminar a partida.

## Término da partida

A partida terminará normalmente quando 1) um dos jogadores descartarem todas as suas cartas, ou 2) acabarem todas as cartas do deque de compra. Os pontos serão então contabilizados de acordo com [seus valores](#pontuação) e o vencedor apresentado.

Porém, a partida também terminará quando houver um erro de comunicação. O bot autor do erro será automaticamente eliminado e a vitória é dada para seu adversário independentemente da quantidade de pontos que cada um possui.

Assim, a partida terminará em qualquer um dos seguintes casos:
* Caso a mensagem enviada não seja nenhum dos comandos predefinidos (por exemplo, o bot enviar a mensagem `Pegue do lixo`);
* Caso algum comando seja enviado fora de ordem (por exemplo, caso a primeira ação de um bot NÃO seja `GET_STOCK` ou `GET_DISCARD`);
* Caso o formato do comando não siga o padrão (por exemplo, `MELD_JOIN` sem parâmetro algum ou `MELD_JOIN e aí cara?!`);
* Caso a jogada seja inválida (por exemplo, `MELD_NEW [ 4♦ 7♣ 9♣ ]`, que não forma um jogo válido);
* Caso a carta utilizada não esteja na mão do jogador (por exemplo, `DISCARD 4♦` e o jogador não possui `4♦` na mão.
* Caso o tempo de resposta do bot ultrapassar 3 segundos.


# Debugar

Como o programa de seu bot será lançando por outro programa (`buraco`), você **não** vai ter acesso direto a algumas ferramentas de debugagem presentes nas IDEs. Caso você queira/precise encontrar um erro no seu bot ou entender o que está acontecendo, algumas possibilidades foram adicionadas ao jogo.

### Ver a troca de mensagens

Para ver ou confirmar o que está sendo enviado do jogo para os bots e o que o jogo está recebendo dos bots, basta você lançar o programa com o parâmetro `-d` na linha de comando. Por exemplo:
```sh
$ node buraco -d bot
```

Com isso, toda mensagem enviada ou recebida de bots (não do usuário) será impresso no terminal.


### Imprimir uma mensagem qualquer

Caso você queira imprimir um valor ou uma mensagem para debugar o que está ocorrendo em determinado trecho do seu código, você deve enviar os dados para a saída de erro-padrão. A escolha da saída de erro é devido ao canal de saída padrão já estar sendo utilizado para comunicação com o jogo propriamente dito. Assim, se quiser realizar um *log-based debugging*, é possível usar o `fprintf()`, como o exemplo abaixo:
```c
int v = 5;
fprintf(stderr, "O valor que quero consultar é: %i\n", v);
```

A string `O valor que quero consultar é: 5` será então impressa no terminal.

### Definir um estado inicial do jogo

Muitas vezes, você terá que testar sua estratégia em uma determinada situação. Porém, como o buraco é um jogo de azar, é difícil replicar uma situação específica. Nesses casos, você pode definir um estado inicial das mãos dos jogadores, da carta que se encontra no lixo (só a carta do topo) e de quem irá jogar em seguida. Assim, você poderá colocar a situação desejada para verificar se sua estratégia funciona.

Para definir esse estado inicial, basta lançar o programa com o parâmetro `-i` seguido do nome de um arquivo. Este arquivo deverá conter os dados do estado no seguinte formato: para 2 jogadores, haverá inicialmente linhas com as sequências de cartas dos jogadores (envolvidas por `[ ]`), depois a carta do lixo e, por fim, um número indicando o índice do jogador que irá começar.

O arquivo `game1.in` que se encontra na pasta `test_files` exemplifica o formato do arquivo. Se você quiser um estado diferente, pode renomear ou fazer uma cópia deste arquivo e alterar os dados que lá se encontram. O nome pode ser qualquer um. Por exemplo, se você criar o arquivo `test_files/caso_1.txt`, você poderá testá-lo com a linha de comando:
```sh
node buraco -i test_files/caso_1.txt bot
```
=======
# itp-prj-2020.2
>>>>>>> 7da894900aba4af1caa74a1243480974820a0af5
