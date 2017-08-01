//Autor: Eric Sampaio
#include <stdlib.h>
#include <stdio.h>
#define TAM 50

//Arvore
typedef struct Celula {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
	struct Celula *proximo;
	struct Celula *anterior;
}Celula,*RegistroARV;

//Lista Duplamente
typedef struct CelulaDUP {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	long int *telefone;
	double salario;
	struct CelulaDUP *proximo;
	struct CelulaDUP *anterior;
}CelulaDUP,*RegistroLIST;

//FUNCOES

//Funcao na insere na lista
//Funcao insere na arvore
//Funcao Importação

void ImportacaoAquivo(){
};


int main(int argc, char **argv)
{	
	char c;
	int x,y,z;
	RegistroARV *Arv;
	FILE *arq;
	int mat;
	char nome[TAM],Snome[TAM],email[TAM],telefone[TAM];
	double salario;
	char frase [1000];

	
	arq=fopen("teste1.txt","r");		// Leitura de arquivo
	
	if (arq == NULL){					//Tratamento caso nao encontre o arquivo
		printf("Arquivo nao encontrado");
		return 0;
	}
//	fscan (arq,"%d",)Arv->email=
/*
	while (fgets(frase,1000,arq)!=NULL){
		printf("%s",frase);
		
	}
	*/
//	while (!feof(arq)){
		fscanf(arq,"%d %s %s %s %s %lf",&mat,nome,Snome,email,telefone,&salario);
		printf("%d %s %s %s %s %.2lf\n",mat,nome,Snome,email,telefone,salario);
//	}
	fclose(arq);
return 0;
}
