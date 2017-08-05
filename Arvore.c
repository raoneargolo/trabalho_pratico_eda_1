#include <stdlib.h>
#include <stdio.h>

typedef struct celulaAVL {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
	struct celula_AVL *filho_esq;
	struct celula_AVL *filho_dir;
}celula_AVL,*RegistroAVL;


//Funcao de menu
//Funcao de inserção na ListaDUP
//Funcao de inserção na ArvoreAVL
	//Funcao de Criacao de arvore
	//Funcao de inserção de um elemento na Arvore
	//Funcao de busca na arvore
	//
//Funcao de remocao de ListaDUP
//Funcaode remocao de ArvoreAVL
//Funcao de Importacao de Arquivo
//Funcao de 