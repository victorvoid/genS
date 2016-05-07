all: compilando_objetos compilando_binarios excluir

compilando_objetos:
	gcc -c ./app/gerador\ de\ arquivo/main.c ./app/gerador\ de\ arquivo/gerarArquivo.c
	gcc -c ./app/ordena\ arquivo/main-ordena.c ./app/ordena\ arquivo/ordena.c

compilando_binarios:
	gcc main.o gerarArquivo.o -o gerarArquivo
	gcc main-ordena.o ordena.o -o msort -lm

excluir:
	rm -f *.o kfile*.bin
