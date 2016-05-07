#include "headers/ordena-header.h"

int32_t main(int32_t argc, char *argv[])
{

	if (argc != 5)
	{
		printf("OPA, ocorreu um erro, verifique se os parâmetros estão sendo passados corretamente!");
		return 1;
	}
	else
	{
		const int32_t K = atoi(argv[4]);
		int32_t memoria = atoi(argv[3]) * MB;
		FILE *fp = fopen(argv[1], "rb");
		clock_t inicio, fim;
		inicio = clock();
		KFile *arquivos = geraLinhas(fp, memoria, K);
		unsigned long arquivoEntradaTAM = getTamArquivo(fp);
		int32_t output_file_index = interpola(arquivos, arquivoEntradaTAM, memoria, K);
		fim = clock();
		double tempoGasto = (double) (fim - inicio) / CLOCKS_PER_SEC;
		int32_t x;
		for (x = 0; x < 2 * K; x++)
		{
			fclose(arquivos[x].fp);
			if (x == output_file_index)
			{
				continue;
			}
			remove(arquivos[x].nome);
		}
		rename(arquivos[output_file_index].nome, argv[2]);
		printf("Tempo de execucao gasto: %lf\n", tempoGasto);
		fclose(fp);
	}
	return 0;
}
