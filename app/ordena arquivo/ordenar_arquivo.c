#include "headers/ordenar_arquivo.h"

void iniciarPilhar (Pilha *q, int32_t n)
{
	q->tamanho = 0;
	q->heap = (nodo*) malloc(sizeof(nodo) * (n+1));
}

unsigned long getTamArquivo (FILE* fp)
{
	unsigned long fileLength;
	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return fileLength;
}

void inserir (nodo a_node, nodo *heap, int32_t tamanho)
{
	int32_t idx;
	idx = tamanho + 1;
	heap[idx] = a_node;
	nodo tmp;
	while (heap[idx].valor < heap[idx/2].valor && idx > 1)
	{
		tmp = heap[idx];
		heap[idx] = heap[idx/2];
		heap[idx/2] = tmp;
		idx /= 2;
	}
}


void vaiParaBaixo (nodo *heap, int32_t tamanho, int32_t idx)
{
	int32_t cidx;
	nodo tmp;
	for (;;)
	{
		cidx = idx*2;
		if (cidx > tamanho)
		{
			break;
		}
		if (cidx < tamanho)
		{
			if (heap[cidx].valor > heap[cidx+1].valor)
			{
				++cidx;
			}
		}
		if (heap[cidx].valor < heap[idx].valor)
		{
			tmp = heap[cidx];
			heap[cidx] = heap[idx];
			heap[idx] = tmp;
			idx = cidx;
		}
		else
		{
			break;
		}
	}
}

nodo remover (nodo *heap, int32_t tamanho)
{
	nodo rv = heap[1];
	heap[1] = heap[tamanho];
	--tamanho;
	vaiParaBaixo(heap, tamanho, 1);
	return rv;
}

nodo desempilhar (Pilha *q)
{
	nodo rv = remover(q->heap, q->tamanho);
	--q->tamanho;
	return rv;
}

void pilhaDinamica (nodo node, Pilha *q)
{
	inserir(node, q->heap, q->tamanho);
	++q->tamanho;
}

int32_t comparaFuncao (const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}
KFile* geraArquivos (const int32_t K)
{
	KFile *arquivos = malloc ((2 * K) * sizeof(KFile));
	int32_t i;
	for (i = 0; i < (2 * K); i++)
	{
		char *caracterTemp = malloc (sizeof(int));
		sprintf(caracterTemp, "%d", i);

		char *file_name = malloc(strlen("kfile_") + strlen(caracterTemp) + strlen(".bin") + 1);
		strcpy(file_name, "kfile_");
		strcat(file_name, caracterTemp);
		strcat(file_name, ".bin");

		arquivos[i].id = i;
		arquivos[i].nome = file_name;
		arquivos[i].fp = fopen(file_name, "w+b");
		arquivos[i].tamAtual = 0;
		arquivos[i].linhaAtual.tamanho = 0;
	}
	return arquivos;
}

int32_t getNumLinhas (unsigned long arquivoTAM, const int32_t MEMORIADISPONIVEL)
{
	int32_t number_of_runs = ceil((float) arquivoTAM / MEMORIADISPONIVEL);

	return number_of_runs;
}

int32_t getLog (double base, double x)
{
	return ceil((double) (log(x) / log(base)));
}

/* interpolando os arquivos, e vai me retornar um arquivo chave*/
int32_t interpola(KFile *arquivos, unsigned long arquivoEntradaTAM, const unsigned long MEMORIADISPONIVEL, const int32_t K)
{
	Pilha prioridadeFila;
	int32_t numDeInterpolacao = getLog(K, arquivoEntradaTAM / MEMORIADISPONIVEL);
	int32_t i_numDeInterpolacao;
	int32_t cont_numDeCombinacoesdaInterpolacao;

	/*apenas se a posicao for do index atual for a primeira*/
	int32_t posicaoAtualSaida = -1;
	for (i_numDeInterpolacao = 0; i_numDeInterpolacao < numDeInterpolacao; i_numDeInterpolacao++)
	{
		int32_t num_of_combinations_per_interpolation = numDeInterpolacao - i_numDeInterpolacao;
		int32_t inicio, end;
		if (i_numDeInterpolacao % 2 == 0)
		{
			inicio = 0;
			end = K;
			posicaoAtualSaida = K;
		}
		else
		{
			inicio = K;
			end = 2 * K;
			posicaoAtualSaida = 0;
		}
		for (cont_numDeCombinacoesdaInterpolacao = 0; cont_numDeCombinacoesdaInterpolacao < num_of_combinations_per_interpolation; cont_numDeCombinacoesdaInterpolacao++)
		{
			int32_t count;
			size_t totalDeBytesEscrito = 0;
			iniciarPilhar(&prioridadeFila, K);
			/* Inrindo primeiros valores na linha */
			for (count = inicio; count < end; count++)
			{
				if (arquivos[count].tamAtual == 0)
				{
					continue;
				}
				/*  sempre depois da primeira */
				if (cont_numDeCombinacoesdaInterpolacao == 0 && i_numDeInterpolacao > 0)
				{
					fseek(arquivos[count].fp, SEEK_SET, 0);
				}
				/* inicio do K */
				if (arquivos[count].tamAtual != 0 && arquivos[count].linhaAtual.tamanho == 0)
				{
					executar run;
					if(arquivos[count].tamAtual <= MEMORIADISPONIVEL)
					{
						run.tamanho = arquivos[count].tamAtual;
					}
					else
					{
						run.tamanho = (i_numDeInterpolacao + 1) * MEMORIADISPONIVEL;
					}
					arquivos[count].linhaAtual = run;
				}
				nodo tmp_pilha_no;
				tmp_pilha_no.index = count;
				fread(&tmp_pilha_no.valor, 1, TAM_ITEM, arquivos[count].fp);
				totalDeBytesEscrito += arquivos[count].linhaAtual.tamanho;
				arquivos[count].linhaAtual.tamanho -= sizeof(int);
				arquivos[count].tamAtual -= sizeof(int);
				pilhaDinamica(tmp_pilha_no, &prioridadeFila);
			}
			totalDeBytesEscrito = 0;
			//Isso na primeira combinação.
			if (cont_numDeCombinacoesdaInterpolacao == 0 && i_numDeInterpolacao > 0)
			{
				ftruncate(fileno(arquivos[posicaoAtualSaida].fp), 0);
				fseek(arquivos[posicaoAtualSaida].fp, SEEK_SET, 0);
			}
			while (prioridadeFila.tamanho > 0)
			{
				nodo nodo = desempilhar(&prioridadeFila);
				fwrite(&nodo.valor, sizeof(int), 1, arquivos[posicaoAtualSaida].fp);
				arquivos[posicaoAtualSaida].tamAtual += sizeof(int);
				totalDeBytesEscrito += sizeof(int);
				if (arquivos[nodo.index].linhaAtual.tamanho == 0)
				{
					continue;
				}
				fread(&nodo.valor, 1, TAM_ITEM, arquivos[nodo.index].fp);
				arquivos[nodo.index].linhaAtual.tamanho -= sizeof(int);
				arquivos[nodo.index].tamAtual = arquivos[nodo.index].tamAtual - sizeof(int);
				pilhaDinamica(nodo, &prioridadeFila);
			}
			/*Gerando a l da saída*/
			executar run;
			run.tamanho = totalDeBytesEscrito;
			if (arquivos[posicaoAtualSaida].linhaAtual.tamanho == 0)
			{
				arquivos[posicaoAtualSaida].linhaAtual = run;
			}
			posicaoAtualSaida++;
		}
	}
	return (posicaoAtualSaida - 1);
}


KFile* geraLinhas (FILE *fp, const int32_t MEMORIADISPONIVEL, const int32_t K)
{
	int32_t number_of_total_runs = getNumLinhas(getTamArquivo(fp), MEMORIADISPONIVEL);
	KFile* arquivos = geraArquivos(K);
	int32_t * buffer = NULL;
	int32_t x;
	for (x = 0; x < number_of_total_runs; x++)
	{
		buffer = (int32_t *) malloc(MEMORIADISPONIVEL);
		size_t lendoBytes = fread(buffer, 1, MEMORIADISPONIVEL, fp);
		qsort(buffer, lendoBytes / TAM_ITEM, sizeof(int), comparaFuncao);
		int32_t posicaoAtual = x % K;
		arquivos[posicaoAtual].tamAtual = arquivos[posicaoAtual].tamAtual + lendoBytes;

		executar run;
		run.tamanho = lendoBytes;
		if (arquivos[posicaoAtual].linhaAtual.tamanho == 0)
		{
			arquivos[posicaoAtual].linhaAtual = run;
		}
		fwrite(buffer, lendoBytes, 1, arquivos[posicaoAtual].fp);
	}
	/*dando inicio ao arquivo */
	for (x = 0; x < K + 1; x++)
	{
		fseek(arquivos[x].fp, SEEK_SET, 0);
	}
    free(buffer);

	return arquivos;
}
