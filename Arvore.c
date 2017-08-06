#include <stdlib.h>
#include <stdio.h>

//Funcao de menu............................................PENDENTE
//Funcao de Importacao de Arquivo...........................OK (Funcionando)

//Criação da estrutura ArvoreAVL............................OK (Testar)
//Funcao de Criacao de arvore...............................OK (Testar)
//Funcao de inserção de um elemento na Arvore...............OK (Testar)
//Funcao de Impressão da arvore.............................OK (Testar)
//Funcao de busca na arvore
	//Funcao de busca pela matricula........................OK (Testar)
	//Funcao de busca pelo nome ............................OK (Testar)
//Funcao de remocao de ArvoreAVL............................PENDENTE


typedef struct celula_AVL {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
	struct celula_AVL *filho_esq;
	struct celula_AVL *filho_dir;
};

typedef celula_AVL celula_AVL;
typedef celula_AVL *celula_AVL_ptr;



//Funcao de inserção na ArvoreAVL
void insere_AVL (int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario, celula_AVL_ptr* arvore_AVL) 
{
	if (arvore_AVL == NULL) //quando a inserção for na folha
	{
		arvore_AVL = ((celula_AVL_ptr*)malloc(sizeof(celula_AVL_ptr))) 
		arvore_AVL-> matricula=matricula;
		Strcpy(arvore_AVL-> nome,nome);
		Strcpy(arvore_AVL->sobrenome,sobrenome);
		Strcpy(arvore_AVL->email,email);
		Strcpy(arvore_AVL->telefone,telefone);
		arvore_AVL->salario=salario;
		arvore_AVL->filho_esq = NULL;
		arvore_AVL->filho_dir = NULL;
	}

	else if (matricula < arvore_AVL->matricula)  //quando a matricula for menor que a mat. raiz da arvore
		arvore_AVL-> filho_esq = insere_AVL(matricula, nome, sobrenome, email, telefone, salario, arvore_AVL->filho_esq);
	else
		arvore_AVL->filho_dir = insere_AVL(matricula, nome, sobrenome, email, telefone, salario, arvore_AVL->filho_dir);
}


//Funcao de Criacao de arvore
void celula_AVL_ptr *cria_arvore_AVL
{
	return NULL;
}


//Funcao de busca matricula na arvore
int busca_matricula(celula_AVL *arvore, int matricula)
{
	if (arvore != NULL) 
	{
		if arvore->matricula == matricula) 
		{
			printf(" matricula %d encontrada", matricula);
			printf("nome:%s\n", arvore ->nome);
			return 1; //Achou o elemento
		}
		else if (arvore->matricula > matricula) 
			busca_matricula (arvore->filho_esq, matricula);
		else 
			busca_matricula (arvore->filho_dir,matricula);
	}
	return 0; //não achou o elemento
}

int busca_nome(celula_AVL *arvore, char *nome, char *sobrenome)
{
	if (arvore != NULL) 
	{
		if (strcmp (arvore->nome,nome) == 0) && (strcmp arvore->sobrenome,sobrenome) == 0)
		{
			printf(" nome %s%s encontrado", nome,sobrenome);
			return 1; //Achou o elemento
		}
		busca_matricula (arvore->filho_esq, nome,sobrenome);
		busca_matricula (arvore->filho_dir,nome,sobrenome);
	}
	return 0; //não achou o elemento		
}
	
	
//Funcao de Impressão da arvore
void impressao_AVL(celula_AVL *arvore) // Falta melhorar
{

	if (arvore != NULL)
	{
		impressao_AVL(arvore->filho_esq);
		printf("%d\nmatricula:", aux->matricula);
		printf("%s\nnome:", aux->nome);
		printf("%s\nSobrenome:", aux->sobrenome);
		printf("%s\ne-mail:", aux->email);
		printf("%s\ne-mail:", aux->telefone);
		printf("%lf\nSalario:", aux->salario);
		impressao_AVL(arvore->filho_dir);
	}
	
}
