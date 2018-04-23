# genS

![C](https://img.shields.io/badge/language-c-green.svg?style=flat-square)

- [Objective](#objective)
- [Some project descriptions](#dev)
- [How to compile and run](#how-to-compile-and-run)
- [Experiments](#experiments)

# Objective

The project aims to implement a high level algorithm that has the function of ordering files that do not fit into the main memory of the computer. Therefore, it is necessary to use an external sorting algorithm to store the files in auxiliary memory. To sort a given data file as input, the sorting method to use will be Merge-Sort, and the strategy will be to combine multiple ordered file units into a single sorted file block (merge).

# dev

1. The C language was used for implementation.
2. Used libraries: `stdlib.h`, `stdio.h`, `stdint.h`, `math.h`, `string.h`, `unistd.h` e `time.h`.
3. Data structure: `Stack`.

### Complexity

- The height of the execution tree can be defined by O (log n)..
- The number of operations at each level of the execution tree is defined by O (n).
- Therefore, the complexity of the algorithm for any case is O (n log n).

# How to compile and run

The process is the simple way to compile C files using [gcc](https://gcc.gnu.org/).

To facilitate typing, the project has the Makefile to execute the command for you.

To use it just type ** make ** on your terminal at the file location. Then choose the one you want to run first:

1. Generate a random number file
2. Sort values within a file

To generate a file, run:

> ./gerarArquivo primeiroPARAMETRO segundoPARAMETRO

First parameter is the name of the file, and the second is the SIZE IN MB

To sort execute:

> ./msort primeiroPARAMETRO segundoPARAMETRO terceiroPARAMETRO quartoPARAMETRO

First parameter is the ** filename ** that you want to sort, second is the ** output name **, third the total amount of ** memory ** available for sorting, and the fourth the ** K ** (number of routes used by Merge-sort).

# Experiments

## Generating a 6GB file
    
It lasted an average time of `` 64.4198s``.

PC 4GB de RAM, i3.

## Sorting according to available memory

![](https://raw.githubusercontent.com/VictorVoid/genS/master/res/graficodetempo.png)
