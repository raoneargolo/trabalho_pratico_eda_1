#include <stdlib.h>
#include <stdio.h>

//Criação da estrutura ListaDUP.............................OK
//Funcao de Criacao de lista................................PENDENTE
//Funcao de inserção de um elemento na lista................PENDENTE
//Funcao de busca na lista..................................PENDENTE
	//Funcao de busca pela matricula........................PENDENTE
	//Funcao de busca pelo nome ............................PENDENTE
//Funcao de inserção na Lista...............................PENDENTE
//Funcao de remocao de Lista................................PENDENTE


struct celula_DUP {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
	struct celula_DUP *proximo;
	struct celula_DUP *anterior;
};


typedef struct celula_DUP celula_DUP;
typedef celula_DUP *celula_DUP_ptr;

//Funcao de insercao

void insere (int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario, celula_DUP_ptr *lista_DUP){

if (lista_DUP == NULL) //quando a inserção for no inicio da lista
	{
		celula_DUP_ptr novo = ((celula_DUP_ptr*)malloc(sizeof(celula_DUP_ptr)));
		novo->matricula=matricula;
		strcpy(novo-> nome,nome);
		strcpy(novo->sobrenome,sobrenome);
		strcpy(novo->email,email);
		strcpy(novo->telefone,telefone);
		novo->salario=salario;
		novo->proximo = NULL;
		novo->anterior = NULL;
		if (Lista_DUP !=NULL)
			lista_DUP->proximo = novo;
		//return novo;
	}
	
}
