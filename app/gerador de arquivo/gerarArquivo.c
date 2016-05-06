#include "headers/gerarArquivo.h"

/**** GERANDO NÚMERO ALEATÓRIO *****/
int32_t numeroRand()
{	
	int32_t num = rand();
	return num;
}

int32_t gerarArquivo(char *arq, long tam)
{
	FILE *fp = fopen(arq, "wb"); //arquivo em binário
	long indice = 0;
	if (!fp) //verifica se o arquivo existe ou não.
	{
		printf("Puts, a casa caiu :/ [ERROR]");
		return 1;
	}
	while (indice < tam)
	{
		int numero = numeroRand();
		fwrite(&numero, sizeof(int32_t), 1, fp);
		indice = indice + sizeof(int32_t);
	}
	fclose(fp);
	return 0;
}
