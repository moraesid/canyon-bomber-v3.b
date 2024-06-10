---
author:
- Luís Fernando de Moraes Santos
version: Versão Final - 3.b
title: Canyon Bomber
---

# 1 - Aspectos Gerais

Este trabalho utiliza como base o jogo Canyon Bomber, desenvolvido originalmente pela Atari. Sob esta implementação, Canyon Bomber versão 3.b é um jogo multiplayer, onde dois jogadores controlam respectivas naves, através das quais devem destruir a base inimiga. O ambiente do jogo é baseado em uma história fictícia criada a partir da mesclagem entre dois universos da ficção científica, Star Wars e Battlestar Galactica. A base dessa história é sintetizada no texto presente na animação de abertura, construída através de um modelo incial no software *Blender*.\
\
Toda a mecânica do jogo foi construída utilizando a biblioteca de desenvolvimento de jogos *Allegro 5*, junto à linguagem *C*.

# 2 - Telas 

A movimentação entre as opções de todos os menus é feita pelas setas
*UP* e *DOWN* do teclado. A seleção de determinada opção se dá através
da tecla *ENTER*.

## 2.1 - Menu Inicial

Após a apresentação da animação de abertura, é exebido o menu inicial com opções de acesso a alguns recursos do jogo, listados abaixo com um breve resumo de suas funções:

 * ***Iniciar***: avança para o próximo menu [*(ver seção 2.2)*](#22---menu-secundário);
 * ***Ajustes***: abre menu de configurações [*(ver seção 2.3)*](#23---ajustes);
 * ***Histórico***: abre a lista de usuários cadastrados [*(ver seção 2.5)*](#25---histórico);
 * ***Sair***: salva alterações de configurações e sai do jogo.

## 2.2 - Menu Secundário

Ao clicar em "*Iniciar*" no menu inicial, o usuário é levado a uma próxima tela onde os jogadores devem digitar seus respectivos *nicknames*, usados para identificar os atributos de cada jogador durante a partida, assim como sua posição no *Histórico*. Os nomes, ou *nicknames*, devem ser escolhidos sob os seguintes critérios:

 * podem conter apenas **números** e **letras**, ou seja, não são permitidos caracteres especiais;
 * devem ter no mínimo **três** e no máximo **quatro** caracteres.

## 2.3 - Ajustes

A tela de configurações é o ambiente de gestão dos recursos de mídia do jogo (essencialmente, recursos sonoros). A seguir estão listadas as opções presentes nessa tela e suas respectivas ações.

 * ***Música Geral***: **ativa/desativa** música de fundo reproduzida durante a partida;
 * ***Efeitos Sonoros***: **ativa/desativa** efeitos sonoros relativos a interação do usúario com objetos do cenário (sons de colisão, tiros, explosões, etc);
 * ***Música dos Menus***: **ativa/desativa** música de fundo dos menus;
 * ***Pular Abertura***: **ativa/desativa** animação de abertura.

Ainda nessa tela, existem mais duas opções importantes através da seguintes teclas:

 * ***H***: abre uma tela de ajuda com uma breve descrição do uso de algumas teclas;
 * ***V***: abre a tela de controles de volume.

***Aviso**: após qualquer alteração tecle "*S*" para salvá-las.*

## 2.4 - Menu Final

Após a conclusão da partida é apresentado um último menu, com a seguintes opções:

 * ***Jogar Novamente***: inicia uma nova partida, a partir do menu secundário [*(ver seção 2.2)*](#22---menu-secundário);
 * ***Histórico***: abre a lista de usuários cadastrados, atualizada com os jogadores da última partida;
 * ***Sair***: salva alterações de configurações, atualiza histórico e sai do jogo.

## 2.5 - Histórico

Essa tela apresenta uma lista de todos os jogadores cadastrados, onde são apresentados o nome (*nickname* escolhido), número de vitórias e potuação total de cada jogador, sendo a lista ordenada através da potuação total.\
\
São suportados no máximo **50** cadastros. Caso esse número seja excedido, os jogadores com menor pontuação são substituídos com os novos cadastros.

# 3 - Controles 

Cada jogador possui um conjuto de teclas para controlar os resursos de suas respectivas naves. Tais conjuntos de teclas são apresentados a seguir.

## 3.1 - Jogador 1

 * *SPACE*: aciona tiro vertical;
 * *D*: aciona tiro horizontal para a direita;
 * *A*: aciona tiro horizontal para a esquerda;
 * *G*: aciona escudo.

## 3.2 - Jogador 2 

 * *ENTER*: aciona tiro vertical;
 * *Seta RIGHT*: aciona tiro horizontal para a direita;
 * *Seta LEFT*: aciona tiro horizontal para a esquerda;\
 * *L*: aciona escudo.

Durante a partida os jogadores podem pressionar a tecla "*Q*", abrindo um menu de ajustes reduzido. Algumas opções da tela de Ajustes [(seção *2.3*)](#23---ajustes) estão disponíveis.

# 4 - O Jogo 

O objetivo principal do jogo é, a partir do controle sobre suas respectivas naves, os jogadores devem usar os recursos disponíveis (especialmente o sistema de tiros) para destruir a base inimiga (parte inferior da tela). A medida que a base é parcialmente destruída, o jogador responsável recebe determinada quantidade de pontos relativa a porção destruída. Cada nave pode disparar apenas um tiro por vez. Caso algum tiro não acerte nenhuma região ativa da base, o jogador perde uma vida de um total inicial de **três**.\
\
Adicionalmente, a medida que cada jogador acumula pontos vão surgindo naves inimigas com maior probabilidade. A cada jogador é associada uma nave inimiga diferente e independente. Quando uma nave inimiga surge, esta dispara um tiro horizontal na direção da nave do jogador associado, que deve se defender através do **escudo** e destruir a nave inimiga com **sistema de tiros horizontais** de sua nave [(ver seção *3*)](#3---controles). Caso os sistemas de defesa não sejam usados, o jagador perderá vidas ao ser atingido pelo tiro da nave inimiga e ao colidir com a mesma. Vale notar que o escudo possui níveis de integridade que diminuem com o uso.\
\
Além disso, os jogadores possuem um conjunto de **três** naves cada um, através dos quais são escolhidas naves aleatoriamente toda vez que saem da tela. Cada nave possui textura e velocidade diferentes entre si. Também ao saírem da tela, as posições verticais das naves são trocadas aleatoriamente.\
\
A partida se encerra em quatro cenários diferentes:

 1. **Missão falhou**: os dois jogadores perdem todas as vidas; ninguém vence;
 2. **Missão incompleta**: um dos jogadores perde todas as vidas, mas a base inimiga não é completamente destruída; o jogador que não perder todas as vidas vence;
 3. **Missão completa**: a base inimiga é totalmente destruída; o jogador com maior pontuação vence;
 4. **Missão completa (atalho)**: caso um dos jogadores acerte o ***ponto vermelho*** sobre a base inimiga, antes que o *tile* que contém o ponto seja atingido, o jogador vence imediatamente e ganha **100** pontos extra.

Associada a cada cenário de fim de jogo, é apresentada uma animação diferente.\
\
Por fim, em relação aos aspectos visuais do jogo, é utilizada a ideia de *sprites* para o desenho e texturas das naves, base inimiga e efeitos de explosão. As outras animações (cenário de fundo, tiros, escudos, etc) foram construídas usando as funções disponíveis na biblioteca *Allegro 5*.

# 5 - O Código

Canyon Bomber 3.b é essencialmente a versão finalizada e refatorada da versão 3.a, com várias melhorias de projeto e código. Em relação a primeira versão, esta foi modularizada, separando as diferentes estruturas e funções associadas em arquivos diferentes de modo que o desenvolvimento do código tornou-se um tanto mais simples e legível.\
\
Sobre alterações no código propriamente dito, consistem principalmente na remoção completa das instruções *goto*, substituídas pelo uso de funções, além de verifições mais precisas no carregamento de módulos do *Allegro 5* e de arquivos externos.\
\
Outro aspecto que recebeu mudanças foi a construção do projeto, em parte por conta do processo de modularização. Agora, a construção é feita em um ambiente (diretório) separado da raiz do projeto, evitando eventuais confusões entre arquivos de compilação e da base do projeto. Tais mudanças são refletidas em alterações significativas sobre o *Makefile*.
