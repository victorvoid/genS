# Gerador de números aleatórios e Ordenador

![C](https://img.shields.io/badge/language-c-green.svg?style=flat-square)

- [Qual o objetivo ?](#objetivo)
- [Algumas descrições do projeto](#dev)
- [Como compilar e executar](#como-compilar-e-executar)
- [Experimentos](#experimentos)
- [Contribuidores (membros)](#membros)

# Objetivo

O projeto visa implementar em alto nível um algoritmo que tem a função de ordenar arquivos que não cabem na memória principal do computador. Sendo assim, é preciso utilizar um algoritmo de ordenação externa para armazenar os arquivos em memória auxiliar. Para ordenar um arquivo de dados fornecido como entrada, o método de ordenação a ser utilizado será o Merge-Sort, e a estratégia será combinar vários blocos de arquivos ordenados em um único bloco de arquivo ordenado (intercalação).

# dev

    Algumas descrições do projeto:

1. Foi utilizada a linguagem C para a implementação.
2. Bibliotecas usadas: `stdlib.h`, `stdio.h`, `stdint.h`, `math.h`, `string.h`, `unistd.h` e `time.h`.
3. Estrutura de Dados: `Pilha`.

# Como compilar e executar

O processo é a forma simples de compilação de arquivos em C utilizando o [gcc](https://gcc.gnu.org/).

Para facilitar a digitacao, o projeto possui o Makefile para executar o comandoo por você.

Para usa-lo apenas digite **make** no seu terminal no local do arquivo. Em seguida escolha o que quer executar primeiro:

1. Gerar um arquivo de número aleatório
2. Ordenar os valores dentro de um arquivo

Para gerar um arquivo, execute:

> ./gerarArquivo primeiroPARAMETRO segundoPARAMETRO

Primeiro parâmetro é o nome do arquivo, e o segundo o TAMANHO EM MB

Para ordenar execute:

> ./msort primeiroPARAMETRO segundoPARAMETRO terceiroPARAMETRO quartoPARAMETRO

Primeiro parâmetro é o **nome do arquivo** que deseja ordenar, segundo é o **nome de saída**, terceiro a quantidade total de **memória** disponível para a ordenação, e o quarto o **K** (número de vias usadas pelo Merge-sort).

# Experimentos

    Gerando um arquivo de 6GB

Durou um tempo médio de ``64.4198s``. 

PC 4GB de RAM, i3.

    Ordenando de acordo com o K (memória disponível)

![](https://raw.githubusercontent.com/VictorVoid/gerador-e-ordenador/master/res/graficodetempo.png)

Membros
----
- Victor Igor Gomes Martins - 140921 
- Luciano de Oliveira Leite - 140616
- Everton Guilherme Machado Guerreiro - 140911
- Marcus Gabriel de Lima Soares - 120865
