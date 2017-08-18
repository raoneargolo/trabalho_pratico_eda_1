//Autor: Eric Sampaio
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 50



int main(int argc, char **argv)
{	
//int result;

	FILE *arq;

	char frase [1000];
	char nome_arq[150];

	printf("informe o nome do arquivo\n");
	scanf("%s",nome_arq);

	//result = strcmp (nome_arq, "teste1");
	
	printf("Abrindo arquivo... \n\n");
		arq=fopen("nome_arq","r");		// Leitura de arquivo
		while (fgets(frase,1000,arq)!=NULL){
			printf("%s",frase);
		}
	
	/*if ( result== 0)
	{
		printf("Abrindo arquivo... \n\n");
		arq=fopen("%s",nome_arq);		// Leitura de arquivo
		while (fgets(frase,1000,arq)!=NULL){
			printf("%s",frase);
		}
	}
	else
	{					//Tratamento caso nao encontre o arquivo
		printf("Arquivo nao encontrado");
		return 0;
	}
	*/
	
	

	fclose(arq);
return 0;
}
