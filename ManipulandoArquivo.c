//Autor: Eric Sampaio
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 50



int main(int argc, char **argv)
{	
//int result;

	FILE *arquivo;

	char frase [1000];
	char nome_arq[20];

	printf("informe o nome do arquivo\n");
	scanf("%s",nome_arq);

		arquivo=fopen(nome_arq,"r");		// Leitura de arquivo
	if (arquivo == NULL)
	{
		printf("ERROR: Arquivo nao encontrado\n");
	}
	else 
	{
		printf("Abrindo arquivo... \n\n");
		while (fgets(frase,1000,arquivo)!=NULL)
		{
		printf("%s",frase);
		}
	}
	
	

	fclose(arquivo);
return 0;
}
