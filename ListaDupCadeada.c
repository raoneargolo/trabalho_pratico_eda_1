//Criação da estrutura ListaDUP.............................OK
//Funcao de Criacao de lista................................PENDENTE
//Funcao de inserção de um elemento na lista................PENDENTE
//Funcao de busca na lista..................................PENDENTE
	//Funcao de busca pela matricula........................PENDENTE
	//Funcao de busca pelo nome ............................PENDENTE
//Funcao de inserção na Lista...............................PENDENTE
//Funcao de remocao de Lista................................PENDENTE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000
#define COUNT 5

typedef struct celula_DUP {
	int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
	char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
	char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
	char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
	char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
	double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado
	struct celula_DUP *proximo;
	struct celula_DUP *anterior;
}celula_DUP;

typedef struct registro
{
	int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
	char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
	char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
	char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
	char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
	double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado
}registro;

//PROTOTIPOS DE FUNCAO
void insere_lista (celula_DUP *lista_DUP, registro linha);
void Remove_Elemento (celula_DUP *lista_DUP,int matricula);
celula_DUP* Busca_Matricula (celula_DUP *lista_DUP, int matricula);
registro quebra_string(char *string_recebida);


//Funcao de insercao
void insere_lista (celula_DUP *inicio, registro linha)
{
	celula_DUP *novo,*atual;
	novo =(celula_DUP*)malloc(sizeof(celula_DUP));
	if (novo == NULL)
		return;

	if (inicio == NULL)
	{
		novo->matricula=linha.matricula;
		printf("\nMatricula\n");
		strcpy(novo->nome,linha.nome);
		printf("\nNome\n");
		strcpy(novo->sobrenome,linha.sobrenome);
		printf("\nSobrenome\n");
		strcpy(novo->email,linha.email);
		printf("\nEmail\n");
		strcpy(novo->telefone,linha.telefone);
		printf("\nTelefone\n");
		novo->salario=linha.salario;
		printf("\nSalario\n");
		novo->proximo = NULL;
		novo->anterior = NULL;
		inicio=novo;
	}
	else
	{
		atual = inicio; //atual aponta para o inicio
		while (atual->proximo != NULL) // enquanto o no atual nao for o ultimo
		{
			atual = atual->proximo;
		}
		novo->matricula=linha.matricula;
		printf("\nMatricula\n");
		strcpy(novo->nome,linha.nome);
		printf("\nNome\n");
		strcpy(novo->sobrenome,linha.sobrenome);
		printf("\nSobrenome\n");
		strcpy(novo->email,linha.email);
		printf("\nEmail\n");
		strcpy(novo->telefone,linha.telefone);
		printf("\nTelefone\n");
		novo->salario=linha.salario;
		printf("\nSalario\n");
		novo->anterior = atual;//o no anterior ao novo e o no atual
		novo->proximo = NULL;// nao existe proximo no, pois sera o ultimo
		atual->proximo = novo;// o no atual aponta para o novo no e nao e mais ultimo
	}
}

celula_DUP* novo_nodo(registro linha)
{
	//printf("\nentrei na funcao de criar um novo nodo\n");
    celula_DUP* nodo = (celula_DUP*)malloc(sizeof(celula_DUP));
    //printf("\nAloquei novo nodo\n");
	nodo->matricula = linha.matricula;
	
    strcpy(nodo->nome,linha.nome);
    strcpy(nodo->sobrenome,linha.sobrenome);
    strcpy(nodo->email,linha.email);
    strcpy(nodo->telefone,linha.telefone);

    nodo->salario = linha.salario;

    nodo->anterior = NULL;
    //printf("\nFilho a esquerda NULL\n");
    
    nodo->proximo = NULL;
    //printf("\nFilho a direita NULL\n");
    
    return(nodo);
}

registro quebra_string(char *string_recebida)
{

	registro linha_arquivo;

	char *string_recebida_copia = strdup(string_recebida); //duplicando para uma string temporária a string recebida na função
	
	char *string_cortada; //ponteiro de caracter (string) para as palavras quebradas

	string_cortada = strtok(string_recebida_copia, ","); //função para quebrar a string pela primeira vez
	
	linha_arquivo.matricula = atoi(string_cortada); //a função atoi converte de string para inteiro
	
	//printf("Numero de Matricula: %d\n", linha_arquivo.matricula); //exibir primeira palavra da string cortada
	
	//o contador abaixo é responsável por indicar em qual coluna a quebra de string está sendo efetuada, para armazenar o resultado
	//da quebra na variável correta
	int contador_variaveis_alocacao = 1; //inciada com 1 pois a primeira coluna da linha foi quebrada

	//o loop começa a operar a partir da segunda coluna (nome do empregado) até o final da linha
	while(string_cortada != NULL)
	{
		string_cortada = strtok(NULL, ","); //quebra de string feita da segunda coluna até o final da linha (sexta coluna)

		contador_variaveis_alocacao++;

		if(string_cortada != NULL) //Condição para atestar uma string válida para o registro
		{
			if(contador_variaveis_alocacao==2) //Condição para colocar a string correta na variável nome
			{
				strcpy(linha_arquivo.nome,string_cortada); //função que copia o conteúdo da string cortada para a variável nome
				//printf("Nome: %s\n", linha_arquivo.nome);
			}
			if(contador_variaveis_alocacao == 3) //Condição para colocar a string correta na variável sobrenome
			{
				strcpy(linha_arquivo.sobrenome,string_cortada); //função que copia o conteúdo da string cortada para a variável sobrenome
				//printf("Sobrenome: %s\n", linha_arquivo.sobrenome);
			}
			if(contador_variaveis_alocacao == 4) //Condição para colocar a string correta na variável e-mail
			{
				strcpy(linha_arquivo.email,string_cortada); //função que copia o conteúdo da string cortada para a variável e-mail
				//printf("E-mail: %s\n", linha_arquivo.email);	
			}
			if(contador_variaveis_alocacao == 5) //Condição para colocar a string correta na variável telefone
			{
				strcpy(linha_arquivo.telefone,string_cortada); //função que copia o conteúdo da string cortada para a variável telefone
				//printf("Telefone: %s\n", linha_arquivo.telefone);
			}
			if(contador_variaveis_alocacao == 6) //Condição para colocar a string correta na variável salário
			{
				linha_arquivo.salario=strtod(string_cortada,NULL); //função que converte o conteúdo da string cortada para double e o armazena na variável salário
				//printf("Salario: %.2lf\n", linha_arquivo.salario);
			}
		}
	}

	printf("\n");

	//printf("\nfim das impressoes dentro da funcao quebra string\n");
		
	return linha_arquivo;
}


//FUNCAO DE BUSCA POR MATRICULA
celula_DUP* Busca_Matricula (celula_DUP *lista_DUP, int matricula)
 {
	celula_DUP* lista_Aux;
	if(lista_DUP == NULL) //se a lista estiver vazia ou o valor não for encontrado
    {
    	printf("\n\tNODO NAO ENCONTRADO\n");
        return NULL;
    }
    else
    {
    	for(lista_Aux=lista_DUP; lista_Aux!=NULL;lista_Aux=lista_Aux->proximo)
    	{
			if(lista_Aux->matricula == matricula)
			// SE FOR PRECISO MOSTRAR AS OUTRAS INFORMACOES AQUI
			return lista_Aux;	
		}
		return NULL; //DUVIDA
    }
 }

//FUNCAO DE IMPRESSAO DA LISTA 
void imprime_lista (celula_DUP *lista)
{
	if (lista==NULL)
	{
		printf("Lista está vazia\n");
	}
	else
	{
		while(lista!=NULL)
		{
		    printf("Numero de Matricula: %d\n", lista->matricula);
			printf("Nome: %s\n", lista->nome);			
			printf("Sobrenome: %s\n", lista->sobrenome);
			printf("E-mail: %s\n", lista->email);
			printf("Telefone: %s\n", lista->telefone);
			printf("Salario: %.2lf\n", lista->salario);
			lista=lista->proximo;
		}
	}
}

//FUNCAO DE REMOCAO DE ELEMENTO
/*
void Remove_Elemento (celula_DUP *lista_DUP,int matricula)
{
	celula_DUP *a=NULL;
	celula_DUP p=*lista_DUP;
	while(p!=NULL && p->matricula !=matricula)
	{
		a=p;
		p=p->proximo;
	}
	return *lista_DUP;
}

*/

int main(int argc, char const *argv[])
{
		printf("\nInicio do main\n");

	//printf("\nCriando arquivo");
	FILE *arquivo; //variável para conter o arquivo csv a ser lido
	//printf("\nArquivo criado");
	//printf("\nCriando string (vetor de char)");
	char linha_atual[tamanho_caracteres_linha]; //ponteiro de caracter (string) para conter a linha atual lida do arquivo
	//printf("\nString criada (vetor de char)");
	//printf("\nCriando a lista");
	celula_DUP *lista = NULL;
	//printf("\nLista criada");
	//printf("\nStruct registro criada");
	registro linha;
	//printf("\nStruct registro criada");
	//printf("\nAbrindo arquivo");
	arquivo = fopen("teste1.csv","r"); //Procedimento para leitura do arquivo csv
	printf("\nArquivo criado");
	
	if (arquivo == NULL) //Caso o arquivo não seja encontrado
	{
		printf("\nArquivo nao encontrado\n");
		return 0;
	}
	
	int qt_linhas_lidas = 0; //variável para o controle do número de linhas dentro do arquivo csv
	
	//o loop abaixo tem como função ler cada linha do arquivo csv inserido (lê o arquivo csv até o seu final)
	//e partir da terceira linha lida (a primeira linha contém o número de registros dentro do arquivo e a segunda
	//o tipo de cada coluna) executar a quebra da linha em strings úteis para a aplicação

	int chamada_insercao = 1;

	while (fgets(linha_atual,tamanho_caracteres_linha,arquivo)!=NULL)
	{
		if(qt_linhas_lidas>1) //Assumind
		{
			linha = quebra_string(linha_atual); //função para "quebrar" string
			
			/*printf("\nValores contidos no registro (dentro do if)\n");
			printf("Numero de Matricula: %d\n", linha.matricula);
			printf("Nome: %s\n", linha.nome);			
			printf("Sobrenome: %s\n", linha.sobrenome);
			printf("E-mail: %s\n", linha.email);
			printf("Telefone: %s\n", linha.telefone);
			printf("Salario: %.2lf\n", linha.salario);*/

			//printf("\nChamada de insercao: %d\n",chamada_insercao);
			insere_lista(lista,linha);
			
			//chamada_insercao++;
			//raiz = inserir_avl(raiz,linha.matricula,linha.nome,linha.sobrenome,linha.email,linha.telefone,linha.salario);

			//raiz = novo_nodo(linha);
			//raiz = novo_nodo(linha.matricula,linha.nome,linha.sobrenome,linha.email,linha.telefone,linha.salario);
		}

		
		qt_linhas_lidas++;
	} 
	imprime_lista(lista);

	fclose(arquivo); //função para fechar o arquivo recebido e lido

	return 0;
}


