#include "headers/gerarArquivo.h"

int32_t main(int32_t argc, char *argv[])
{
	if (argc != 3){
		printf("Argumentos invalidos :'( \n");
		return 1;
	}else{
		clock_t start, end;
		start = clock();
		/* Para calcular o tempo gasto, logo que inicia o procedimento
			de gerar arquivo, a variável start recebe a funcao clock da
			biblioteca time.h que pega do sistema o tempo e logo quando 
			termina, a variável end recebe o o tempo para que possa fazer
			a diferenca deles, e assim sabendo o tempo gasto.
		 */
		FILE *fp = fopen(argv[1], "rb");
		if (fp != NULL){
			printf("\nA casa caiu, pois o arquivo ja existe!\n");
			fclose(fp);
			return 0;
		}
		gerarArquivo(argv[1], atol(argv[2]) * MB); //atol converte o char para long
		end = clock();
		double tempo_gasto = (double) (end - start) / CLOCKS_PER_SEC;
		FILE *relatorioDeTempo = fopen("tempogastoGerar.txt", "w");
		fprintf(relatorioDeTempo, "Tempo gasto para criação do arquivo\n%.4fs", tempo_gasto);
		fclose(relatorioDeTempo);
		printf("Arquivo gerado com sucesso... Caso queira saber o tempo gasto, verifique o arquivo <tempogastoGerar.txt>");
	}
	return 0;
}
