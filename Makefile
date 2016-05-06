all: compilando_objetos compilando_binarios excluir

compilando_objetos:
	gcc -c ./app/gerador\ de\ arquivo/main.c ./app/gerador\ de\ arquivo/gerarArquivo.c
	gcc -c ./app/ordena\ arquivo/ordenar_arquivo_main.c ./app/ordena\ arquivo/ordenar_arquivo.c

compilando_binarios:
	gcc main.o gerarArquivo.o -o gerarArquivo
	gcc ordenar_arquivo_main.o ordenar_arquivo.o -o msort

excluir:
	rm -f *.o kfile*.bin
