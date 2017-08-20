/*Equipe composta por:
	1-Acacia Juriti
	2-Eric Sampaio
	3-Raone Argolo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000
#define MALLOC(a) (a *) malloc ( sizeof(a) )
#define COUNT 5

//Estrutura de nodo para árvore AVL
typedef struct Nodo
{
    int matricula;
	char nome[tamanho_caracteres];	
	char sobrenome[tamanho_caracteres];
	char email[tamanho_caracteres];
	char telefone[tamanho_caracteres];
	double salario;
    
    struct Nodo *esquerda;
    struct Nodo *direita;
    
    int altura;
}Nodo;

//Estrutura de nodo para lista duplamente encadeada
struct no
{
   int matricula;
   char nome[tamanho_caracteres];
   char sobrenome[tamanho_caracteres];
   char email[tamanho_caracteres];
   char telefone[tamanho_caracteres];
   double salario;
   
   struct no *prox;
   struct no *ant;
};

//Ponteiros de referência para lista duplamente encadeada
struct no *inicio;
struct no *fim;

//Estrutura para conter um registro (ou linha) com os dados do funcionário
typedef struct registro
{
	int matricula;
	char nome[tamanho_caracteres];
	char sobrenome[tamanho_caracteres];
	char email[tamanho_caracteres];
	char telefone[tamanho_caracteres];
	double salario;
}registro;


// Protótipos de função da lista duplamente encadeada
void inserir (registro linha); 
void imprimeLista (void);
struct no *busca_matricula (int matricula);
struct no *busca_nome (char *nome);
struct no *remover(int matricula);
registro quebra_string_lista(char *string_recebida);

//Protótipos de função da árvore AVL
int altura_arvore(Nodo *novo);
int maximo(int a, int b);
Nodo* novo_nodo(registro *linha_arquivo);
Nodo *rotacao_direita(Nodo *atual);
Nodo *rotacao_esquerda(Nodo *atual);
int fator_balanceamento(Nodo *atual);
Nodo* inserir_avl(Nodo *nodo, registro *linha);
Nodo * menor_valor_avl(Nodo *nodo);
Nodo* deletar_avl(Nodo *raiz, int matricula);
int busca_nodo_nome(Nodo *atual, char *nome);
Nodo* busca_nodo_matricula(Nodo *raiz, int matricula);
void impressao_formato_arvore(Nodo *raiz, int espaco);
registro* quebra_string_avl(char *string_recebida);

int main() {

	FILE *arquivo; //arquivo do tipo FILE para receber o arquivo de importação

	clock_t tempo_inicio, tempo_fim; //variáveis para contar o tempo de execução de trechos do código
	long double tempo_duracao; //variável para cronometar o tempo de duração da execução de um trecho do código

	char nome_arquivo[tamanho_caracteres]; //variável para ler o nome do arquivo a ser importado
	char linha_atual[tamanho_caracteres_linha]; //variável para ler linha do arquivo importado e inserir na lista
	char linha_atual_avl[tamanho_caracteres_linha]; //variável para ler linha do arquivo importado e inserir na arvore
	
	Nodo *raiz = NULL; //nodo raiz para arvore avl
	
    registro *linha_avl; //struct para conter um registro e inserir na arvore avl
    registro linha_lista; //struct para conter um registro e inserir na lista

    inicio = fim = NULL; //inicializando o ponteiro de inicio e fim da lista

    int qt_linhas_lidas; //variável de controle da quantidade de linhas lidas do arquivo
    int tipo_estrutura; //variável de escolha do tipo de estrutura (avl ou lista) para manipulação
    int opcao_funcao; //variável de escolha das funções de manipulação

    printf("\n\t\t\t################## BEM VINDO ###################\n");
	printf("\nDigite o nome do arquivo a ser importado (com a extensao): ");
	scanf("%s",nome_arquivo); //lendo nome do arquivo para importação

	arquivo = fopen(nome_arquivo,"r"); //Procedimento para leitura do arquivo csv

	while (arquivo == NULL) //Caso o arquivo não seja encontrado
	{
		printf("\n\t\t\t\t\tERRO: Arquivo nao encontrado!\n");
		printf("\nDigite o nome do arquivo a ser importado (com a extensao): ");
		scanf("%s",nome_arquivo);
		arquivo=fopen(nome_arquivo,"r");
	}

	printf("\n\t\t\t\tArquivo encontrado! Abrindo arquivo... \n\n");


	//Importação do arquivo e inserção na lista duplamente encadeada
	
	qt_linhas_lidas = 0;

	tempo_inicio = clock(); //Iniciando contagem de tempo de execução

	while (fgets(linha_atual,tamanho_caracteres_linha,arquivo)!=NULL) //O loop é executado até o final do arquivo
   	{
    	if(qt_linhas_lidas>1) //Assumindo que as duas primeiras linhas do arquivo contem a quantidade de registros e os nomes das colunas
      	{
		    linha_lista = quebra_string_lista(linha_atual); //função para "quebrar" string
		    inserir(linha_lista); //Função para inserir o registro devidamente organizado na lista duplamente encadeada
      	}  
      	
      	qt_linhas_lidas++;
   	}

   	fclose(arquivo); //Função para fechar o arquivo importado

   	tempo_fim = clock(); //Finalizando contagem de tempo de execução

   	tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC; //calculando a diferença de tempo entre o início e o fim da execução

   	printf("\nTempo da importacao e insercao dos registros na lista duplamente encadeada: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )


   	//Importação do arquivo e inserção na árvore AVL

   	qt_linhas_lidas = 0;

   	tempo_inicio = clock(); //Iniciando contagem de tempo de execução

   	arquivo = fopen(nome_arquivo,"r"); //Procedimento para leitura do arquivo csv
   	
   	while (fgets(linha_atual_avl,tamanho_caracteres_linha,arquivo)!=NULL) //O loop é executado até o final do arquivo
	{
		if(qt_linhas_lidas>1) //Assumind
		{
			linha_avl = quebra_string_avl(linha_atual_avl); //função para "quebrar" string

			raiz = inserir_avl(raiz, linha_avl); //Assumindo que as duas primeiras linhas do arquivo contem a quantidade de registros e os nomes das colunas
		}
		
		qt_linhas_lidas++; //Função para inserir o registro devidamente organizado na lista duplamente encadeada
	}

	fclose(arquivo); //função para fechar o arquivo recebido e lido
	
	tempo_fim = clock(); //Finalizando contagem de tempo de execução

   	tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC; //calculando a diferença de tempo entre o início e o fim da execução

   	printf("\nTempo da importacao e insercao dos registros na árvore AVL: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )

   	//Inicio do menu de opções de manipulação das estruturas

	printf("\n\n\n\t\t\t   ################## MENU ###################\n");
	printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
	printf("\n1 - Manipulacao de dados na Arvore AVL");
	printf("\n2 - Manipulacao de dados na Lista Duplamente Encadeada");
	printf("\n3 - Sair da aplicacao");
	printf("\n\nDigite a opcao desejada: ");
	scanf ("%d",&tipo_estrutura);

	while(tipo_estrutura != 3) //loop executa enquanto a escollha for avl (1) ou lista (2)
	{
		if(tipo_estrutura == 1) //Árvore AVL
		{
			printf("\n\n\n\t\t\t################## ARVORE AVL ###################\n");
			printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
			printf("\n1 - Busca por numero de matricula");
			printf("\n2 - Busca por nome");
			printf("\n3 - Imprimir arvore");
			printf("\n4 - Insercao manual");
			printf("\n5 - Remover um registro pelo numero de matricula");
			printf("\n6 - Escolher outra estrutura para manipular");
			
			printf("\n\nDigite a opcao desejada: ");
			int opcao;
			scanf("%d",&opcao);

			while(opcao!=6) //O loop executa até o usuário escolher sair da manipulação da árvore AVL
			{
				if(opcao == 1) //Busca por numero de matricula
				{
					int matricula_busca;

					Nodo *busca = (Nodo*)malloc(sizeof(Nodo));

					printf("\nDigite um numero de matricula para busca: ");
					scanf("%d",&matricula_busca);
					
					tempo_inicio = clock();

					busca_nodo_matricula(raiz,matricula_busca); //função de busca
					
					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
					
					printf("\nTempo da busca por matricula: %Lf (s) \n",tempo_duracao);
				}
				else if(opcao == 2) //Busca por nome
				{
					char nome_busca[tamanho_caracteres];
			
					printf("\nDigite um nome para busca: ");
					fflush(stdin);
					scanf("%s",nome_busca);

					tempo_inicio = clock();
					
					int resultado_busca = busca_nodo_nome(raiz,nome_busca); //Retorna o resultado da busca por nome
					
					tempo_fim = clock();

					if(resultado_busca == 1)
					{	
						printf("\n\t\tNOME ENCONTRADO!\n");
					}
					else
					{
						printf("\n\t\tNOME NAO ENCONTRADO!\n");
					}
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
					
					printf("\nTempo da busca por nome: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
				}
				else if(opcao == 3) //Imprimir árvore
				{
					tempo_inicio = clock();
					
					impressao_formato_arvore(raiz,0); //Funçao de impressão da árvore AVL
					
					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
					
					printf("\nTempo da exibicao dos registros: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
				}
				else if(opcao == 4) //Inserção manual
				{

					int matricula_busca;
					printf("\nDigite uma matricula para inserir: ");
					scanf(" %d",&matricula_busca);

					registro *insercao_manual = malloc(sizeof(registro)); //criando e alocando uma struct para conter o registro e inserí-lo na árvore
					
					tempo_inicio = clock();
					
					if(busca_nodo_matricula(raiz,matricula_busca) == NULL) //Função de busca retorna NULL se não houver registros com o mesmo número de matrícula e instrui o usuário a inserir os dados do mesmo
					{
						printf("\nMATRICULA LIBERADA. INSIRA OS DADOS\n");
						insercao_manual->matricula = matricula_busca;

						printf("\nNome: ");
						char nome[tamanho_caracteres];
						scanf("%s",nome);
						strcpy(insercao_manual->nome,nome);

						printf("\nSobrenome: ");
						char sobrenome[tamanho_caracteres];
						scanf("%s",sobrenome);
						strcpy(insercao_manual->sobrenome,sobrenome);

						printf("\nE-mail: ");
						char email[tamanho_caracteres];
						scanf("%s",email);
						strcpy(insercao_manual->email,email);

						printf("\nTelefone(sem espacos *troque os espacos por tracos ou parenteses*): ");
						char telefone[tamanho_caracteres];
						scanf("%s",telefone);
						strcpy(insercao_manual->telefone,telefone);

						printf("\nSalario: ");
						double salario;
						scanf("%lf",&salario);
						insercao_manual->salario=salario;

						raiz = inserir_avl(raiz,insercao_manual); //Função de inserção na árvore AVL

						printf("\nDeseja imprimir a arvore? Digite 1 para SIM e 2 para NAO: ");
						int opcao_2;
						scanf("%d",&opcao_2);

						if(opcao_2 == 1)
						{
							printf("\n\t\tArvore AVL apos insercao manual\n");
							impressao_formato_arvore(raiz,0);
						}
					}
					else
					{
						printf("\n\t\tMATRICULA BLOQUEADA. JA EXISTE USUARIO CADASTRADO\n");
					}

					tempo_fim = clock();
						
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
						
					printf("\nTempo da busca e insercao manual do registro: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
				}
				else if(opcao == 5) //Remoção de registro pelo numero de matricula
				{
					int matricula_busca;

					printf("\nDigite um numero de matricula para busca e posterior remocao: ");
					scanf("%d",&matricula_busca);
					
					if(busca_nodo_matricula(raiz,matricula_busca)!=NULL) //Função de busca por matrícula. Se a matrícula for encontrada, proceder remoção
					{	
						tempo_inicio = clock();

						raiz = deletar_avl(raiz,matricula_busca); //Função de remoção do registro pelo numero de matrícula
						
						tempo_fim = clock();
						
						printf("\nRegistro removido! Deseja imprimir a arvore? Digite 1 para SIM e 2 para NAO: ");
						int opcao_2;
						scanf("%d",&opcao_2);

						if(opcao_2 == 1)
						{
							printf("\n\t\tArvore AVL apos remocao\n");
							impressao_formato_arvore(raiz,0);
						}
					}
	
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
						
					printf("\nTempo da busca e remocao dos registros: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
				}
				else //Caso a opção desejada seja inválida
				{
					printf("\n\t\t\tOPCAO INVALIDA\n");
				}

				printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
				printf("\n1 - Busca por numero de matricula");
				printf("\n2 - Busca por nome");
				printf("\n3 - Imprimir arvore");
				printf("\n4 - Insercao manual");
				printf("\n5 - Remover um registro pelo numero de matricula");
				printf("\n6 - Escolher outra estrutura para manipular");
				
				printf("\n\nDigite a opcao desejada: ");
				scanf("%d",&opcao);
			}
		}
		else if(tipo_estrutura == 2) //Lista duplamente encadeada
		{
			printf("\n\n\n\t\t################## LISTA DUPLAMENTE ENCADEADA ###################\n");
			printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
			printf("\n1 - Busca por numero de matricula");
			printf("\n2 - Busca por nome");
			printf("\n3 - Imprimir arvore");
			printf("\n4 - Insercao manual");
			printf("\n5 - Remover um registro pelo numero de matricula");
			printf("\n6 - Escolher outra estrutura para manipular");
			
			printf("\n\nDigite a opcao desejada: ");
			int opcao;
			scanf("%d",&opcao);

			while(opcao!=6)  //O loop executa até o usuário escolher sair da manipulação da lista duplamente encadeada
			{
				if(opcao == 1) //Busca por numero de matrícula
				{
					int matricula_busca;

					printf("\nDigite um numero de matricula para busca: ");
					scanf("%d",&matricula_busca);
					
					tempo_inicio = clock();
					
					if(busca_matricula(matricula_busca)!=NULL) //Função de busca por matrícula retorna NULL caso não exista o número de matrícula pesquisado
					{
				    	printf("\n\t\tNUMERO DE MATRICULA ENCONTRADO NA LISTA DUPLAMENTE ENCADEADA\n");
				   	}
				   	else
				  	{
				    	printf("\n\t\tNUMERO DE MATRICULA NAO ENCONTRADO NA LISTA DUPLAMENTE ENCADEADA\n");
				   	}
					
					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

   					printf("\nTempo da busca por matricula na lista duplamente encadeada: %Lf (s) \n",tempo_duracao);
				}
				else if(opcao == 2) //Busca por nome
				{
					char nome_busca[tamanho_caracteres];
			
					printf("\nDigite um nome para busca: ");
					fflush(stdin);
					scanf("%s",nome_busca);
				   	
				   	tempo_inicio = clock();
					
				   	if(busca_nome(nome_busca)!=NULL) //Função de busca por nome retorna NULL caso o nome não seja encontrado na lista
				   	{	
				    	printf("\n\t\tNOME ENCONTRADO NA LISTA DUPLAMENTE ENCADEADA\n");
				   	}
				   	else
				   	{
				    	printf("\n\t\tNOME NAO ENCONTRADO NA LISTA DUPLAMENTE ENCADEADA\n");
				   	}

					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

   					printf("\nTempo da busca por nome na lista duplamente encadeada: %Lf (s) \n",tempo_duracao);
				}
				else if(opcao == 3) //Impressão da lista duplamente encadeada
				{
					tempo_inicio = clock();
					
					imprimeLista(); //Funções de impressão da lista duplamente encadeada

					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

   					printf("\nTempo da impressao na lista duplamente encadeada: %Lf (s) \n",tempo_duracao);
				}
				else if(opcao == 4) //Inserção manual
				{
					int matricula_busca;
					
					registro *insercao_manual = malloc(sizeof(registro));

					printf("\nDigite uma matricula para inserir: ");
					scanf("%d",&matricula_busca);
					
					tempo_inicio = clock();
					
					if(busca_matricula(matricula_busca)!=NULL) //Função de busca retorna NULL quando a matrícula não existe e a inserção é liberada
					{
					    printf("\n\t\tMATRICULA EM USO. NAO SERA POSSIVEL INSERIR REGISTRO\n");
					}
				    else //Ao permitir inserção, instrui usuário a preencher os dados restantes do registro
					{
						printf("\n\t\tMATRICULA LIBERADA. INSIRA OS DADOS\n\n");

						linha_lista.matricula=matricula_busca;
						
						printf("\nNome: ");
						scanf("%s",linha_lista.nome);

						printf("\nSobrenome: ");
						scanf("%s",linha_lista.sobrenome);

						printf("\nE-mail: ");
						scanf("%s",linha_lista.email);

						printf("\nTelefone(sem espacos *troque os espacos por tracos ou parenteses*): ");
						scanf("%s",linha_lista.telefone);

						printf("\nSalario: ");
						scanf("%lf",&linha_lista.salario);

						inserir(linha_lista);

						printf("\nDeseja imprimir a arvore? Digite 1 para SIM e 2 para NAO: ");
						int opcao_2;
						scanf("%d",&opcao_2);

						if(opcao_2 == 1)
						{
							printf("\n\t\tArvore AVL apos remocao\n");
							imprimeLista();
						}
					}

					tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

   					printf("\nTempo da insercao manual na lista duplamente encadeada: %Lf (s) \n",tempo_duracao);
				}
				else if(opcao == 5) //Remoção de um registro pelo número de matrícula
				{
					int matricula_busca;

					printf("\nDigite um numero de matricula para busca e posterior remocao: ");
			   		scanf("%d",&matricula_busca);

			   		tempo_inicio = clock();
					
				   	if(busca_matricula(matricula_busca)!=NULL)  //Função de busca retorna o nodo da matricula encontrado quando a mesma existe
				   	{
				    	printf("\n\t\tMATRICULA ENCONTRADA. PROCEDENDO REMOCAO\n");
				    	
				    	remover(matricula_busca); //Função de remoção

				    	printf("\nRemocao efetuada! Deseja imprimir a arvore? Digite 1 para SIM e 2 para NAO: ");
						int opcao_2;
						scanf("%d",&opcao_2);

						if(opcao_2 == 1)
						{
							printf("\n\t\tARVORE AVL APOS REMOCAO\n");
							imprimeLista();
						}
				   	}
				   	else
				   	{
				    	printf("\n\t\tVALOR NAO ENCONTRADO\n");
				   	}

				   	tempo_fim = clock();
					
					tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

   					printf("\nTempo de remocao na lista duplamente encadeada: %Lf (s) \n",tempo_duracao);
				}
				else
				{
					printf("\n\t\t\tOPCAO INVALIDA\n");
				}

				printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
				printf("\n1 - Busca por numero de matricula");
				printf("\n2 - Busca por nome");
				printf("\n3 - Imprimir arvore");
				printf("\n4 - Insercao manual");
				printf("\n5 - Remover um registro pelo numero de matricula");
				printf("\n6 - Escolher outra estrutura para manipular");
				
				printf("\n\nDigite a opcao desejada: ");
				scanf("%d",&opcao);
			}
		}
		else
		{
			printf("\n\t\t\tOPCAO INVALIDA\n");
		}

		printf("\n\n\n\t\t\t   ################## MENU ###################\n");
		printf("\n\t\t\t\t     ESCOLHA UMA DAS OPCOES\n");
		printf("\n1 - Manipulacao de dados na Arvore AVL");
		printf("\n2 - Manipulacao de dados na Lista Duplamente Encadeada");
		printf("\n3 - Sair da aplicacao");
		printf("\n\nDigite a opcao desejada: ");
		scanf ("%d",&tipo_estrutura);
	}

	printf("\n\n\t    ################## QUE A FORCA ESTEJA COM VOCE! ###################\n");
	printf("\n\t\t\t\t\t   versao 10.2.8\n");

	return 0;
}


//FUNÇÕES DE LISTA DUPLAMENTE ENCADEADA

void inserir (registro linha) //Função de inserção na lista duplamente encadeada
{
   struct no *novo = MALLOC (struct no);
   
   struct no *atual;
        
   if ( !novo )
   {
      perror ( "Malloc: " );
      return ;
   }
        
   // atribuição do novo valor
   novo->matricula=linha.matricula;
   strcpy(novo->nome,linha.nome);
   strcpy(novo->sobrenome,linha.sobrenome);
   strcpy(novo->email,linha.email);
   strcpy(novo->telefone,linha.telefone);
   novo->salario=linha.salario;
        
   // cria lista
   if ( !inicio )
   {
      novo->prox = NULL;
      novo->ant  = NULL;
                
      inicio = novo;
      fim = novo;
                
      return ;
   }
        
   // se não for o primeiro elemento da lista
   atual = inicio;
        
   while ( atual )
   {
      if ( atual->matricula < linha.matricula )
      {
         atual = atual->prox;
      }
      else
      {
         // elemento intermediário - caso 2
         if ( atual->ant )
         {
            novo->prox = atual;
            novo->ant = atual->ant;
            atual->ant->prox = novo;
            atual->ant = novo;
                                
            return ;
         }
         // novo primeiro elemento - caso 1
         novo->prox = atual;
         novo->ant = NULL;
         atual->ant = novo;
         inicio = novo;
                       
         return ;
      }
   }
   // novo último elemento - caso 3
   fim->prox = novo;
   novo->prox = NULL;
   novo->ant = fim;
   fim = novo;
   
   return ;
}

//Função de impressão da lista duplamente encadeada
void imprimeLista (void)
{

	struct no *atual = inicio;
        
   	while (atual) //Enquanto o nodo atual não for nulo
   	{
		printf("\n\n");
		printf("Numero de Matricula: %d\n", atual->matricula);
		printf("Nome: %s\n", atual->nome);        
		printf("Sobrenome: %s\n", atual->sobrenome);
		printf("E-mail: %s\n", atual->email);
		printf("Telefone: %s\n", atual->telefone);
		printf("Salario: %.2lf\n", atual->salario);

		atual = atual->prox;
   }

   printf("\n\t\tFIM DA LISTA DUPLAMENTE ENCADEADA\n");

   return ;
}

//Função de busca de matrícula da lista duplamente encadeada
struct no *busca_matricula (int matricula)
{
   struct no *atual = inicio;
        
   while ( atual ) //Enquanto o nodo atual não for nulo
   {
      if ( atual->matricula == matricula) //Se o valor for encontrado
      {
         return atual;
      }
      else //Se não for encontrado, procura no proximo nodo;
      {
         atual = atual->prox;
      }
   }

   return NULL; //retorna NULL se após percorrer toda a lista o número de matrícula não for encontrado
}

//Função de busca por nome da lista duplamente encadeada
struct no *busca_nome (char *nome)
{
   struct no *atual = inicio;

   int comparador;

	while ( atual ) //Enquanto o nodo atual não for nulo
   	{
      	comparador = strcmp(nome,atual->nome); //Comparação entre o nome presente no nodo atual e o nome buscado

      	if(comparador == 0) //Se o nome presente no nodo atual e o nome buscado forem iguais
      	{
         	return atual; //Retorna o nodo encontrado
      	}
      	else
      	{
         	atual = atual->prox; //Continua procurando, percorrendo o próximo nodo da lista
      	}
   }

   return atual; //Retorna NULL, pois não encontrou o nome nos registros da lista
}

//Função para remover um nodo da lista pelo número de matrícula do registro
struct no *remover(int matricula)
{
   struct no* atual = inicio; //Inicia pelo ponteiro do início da lista
   struct no* anterior = NULL;
	
	if(inicio == NULL) //Se não houver nodos na lista
   	{
		printf("\n\t\t\tLISTA VAZIA\n");
      	return NULL;
   	}

   	while(atual->matricula != matricula) //Navegando pela lista enquanto o número de matrícula não for encontrado
   	{	
    	if(atual->prox == NULL) //Se o nodo atual for o último nodo da lista
      	{
         	return NULL; //Retorna NULL sinalizando que o nodo com o número de matrícula não foi encontrado
      	}
      	else
      	{
        	anterior = atual; //Armazena um ponteiro para o nodo atual
			
         	atual = atual->prox; //Percorre a lista, indo para o próximo nodo
      	}
   	}

   	if(atual == inicio) //Caso o nodo a ser removido seja o primeiro da lista, atualiza o ponteiro que aponta para o início da lista
   	{
      	inicio = inicio->prox; //Atualiza o início da lista
   	}
   	else
   	{
      	atual->ant->prox = atual->prox; //Desvia o link atual
   	}    

   	if(atual == fim) //Caso o nodo a ser removido seja o último da lista
   	{
      	fim = atual->ant; //Muda o ponteiro apontando para o final da lista para o nodo anterior do nodo atual
   	}
   	else
   	{
      	atual->prox->ant = atual->ant;
   	}
	
   	return atual;
}

//Função de quebra de string para a lista duplamente encadeada
registro quebra_string_lista(char *string_recebida)
{

   registro linha_arquivo;

   char *string_recebida_copia = strdup(string_recebida); //duplicando para uma string temporária a string recebida na função
   
   char *string_cortada; //ponteiro de caracter (string) para as palavras quebradas

   string_cortada = strtok(string_recebida_copia, ","); //função para quebrar a string pela primeira vez
   
   linha_arquivo.matricula = atoi(string_cortada); //a função atoi converte de string para inteiro
   
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
         }
         if(contador_variaveis_alocacao == 3) //Condição para colocar a string correta na variável sobrenome
         {
            strcpy(linha_arquivo.sobrenome,string_cortada); //função que copia o conteúdo da string cortada para a variável sobrenome
         }
         if(contador_variaveis_alocacao == 4) //Condição para colocar a string correta na variável e-mail
         {
            strcpy(linha_arquivo.email,string_cortada); //função que copia o conteúdo da string cortada para a variável e-mail
         }
         if(contador_variaveis_alocacao == 5) //Condição para colocar a string correta na variável telefone
         {
            strcpy(linha_arquivo.telefone,string_cortada); //função que copia o conteúdo da string cortada para a variável telefone
         }
         if(contador_variaveis_alocacao == 6) //Condição para colocar a string correta na variável salário
         {
            linha_arquivo.salario=strtod(string_cortada,NULL); //função que converte o conteúdo da string cortada para double e o armazena na variável salário
         }
      }
   }
      
   return linha_arquivo;
}




//FUNÇÕES DE ÁRVORE AVL

//Função para obter altura de um nodo novo da árvore
int altura_arvore(Nodo *novo)
{
    if (novo == NULL)
    {
        return 0;
    }

    return novo->altura;
}

//Função para retornar o maior valor entre dois inteiros
int maximo(int a, int b)
{
    return (a > b)? a : b;
}

//Função para criar e alocar memória para um novo nodo
Nodo* novo_nodo(registro *linha)
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));

	nodo->matricula = linha->matricula;
    
    strcpy(nodo->nome,linha->nome);
    
    strcpy(nodo->sobrenome,linha->sobrenome);
    
    strcpy(nodo->email,linha->email);
    
    strcpy(nodo->telefone,linha->telefone);
    
    nodo->salario = linha->salario;
    
    nodo->esquerda = NULL;
    
    nodo->direita = NULL;

    nodo->altura = 1;  // novo nó é inicialmente adcionado nas folhas

    return(nodo);
}

// Função que rotaciona a direita a subàrvore do nó desbalanceado
Nodo *rotacao_direita(Nodo *atual)
{
    struct Nodo *novo_nodo = atual->esquerda;
    struct Nodo *temporario = novo_nodo->direita;
 
    // Fazendo rotação
    novo_nodo->direita = atual;
    atual->esquerda = temporario;
 
    // Atualizando altura dos nós
    atual->altura = maximo(altura_arvore(atual->esquerda), altura_arvore(atual->direita))+1;
    novo_nodo->altura = maximo(altura_arvore(novo_nodo->esquerda), altura_arvore(novo_nodo->direita))+1;
 
    // Retornando novo nó
    return novo_nodo;
}

// Função que rotaciona a esquerda a subàrvore do nó desbalanceado
Nodo *rotacao_esquerda(Nodo *atual)
{
    struct Nodo *novo_nodo = atual->direita;
    struct Nodo *temporario = novo_nodo->esquerda;
 
    // Fazendo rotação
    novo_nodo->esquerda = atual;
    atual->direita = temporario;
 
    // Atualizando altura dos nós
    atual->altura = maximo(altura_arvore(atual->esquerda), altura_arvore(atual->direita))+1;
    novo_nodo->altura = maximo(altura_arvore(novo_nodo->esquerda), altura_arvore(novo_nodo->direita))+1;
 
    // Retornando novo nó
    return novo_nodo;
}

//Função para calcular o fator de balanceamento de um nodo
int fator_balanceamento(Nodo *atual)
{
    if (atual == NULL)
    {
        return 0;
    }

    return altura_arvore(atual->esquerda) - altura_arvore(atual->direita);
}

//Função para inserir um registro à AVL
Nodo* inserir_avl(Nodo *nodo, registro *linha)
{
    //1.  Faz a rotação normal na ABB
    if (nodo == NULL)
    {
        return(novo_nodo(linha));
    }

    if (linha->matricula < nodo->matricula)
    {
        nodo->esquerda  = inserir_avl(nodo->esquerda, linha);
    }
	else if (linha->matricula > nodo->matricula)    	
    {
        nodo->direita = inserir_avl(nodo->direita, linha);
    }
    else // Valores iguais não são permitidos
    {
        return nodo;
    }
 
    // 2. Atualiza altura do nó antecessor
    nodo->altura = 1 + maximo(altura_arvore(nodo->esquerda),altura_arvore(nodo->direita));
 
    // 3. Obtém o fator de balanceamento do nó antecessor para checar se o nó se tornou desbalanceado
    int balance = fator_balanceamento(nodo);
 
    // Se o nó se torna desbalanceado, então há quatro casos para considerar
 
    // Caso esquerda esquerda
    if (balance > 1 && linha->matricula < nodo->esquerda->matricula)
    {
        return rotacao_direita(nodo);
    }
 
    // Caso direita direita
    if (balance < -1 && linha->matricula > nodo->direita->matricula)
    {
        return rotacao_esquerda(nodo);
    }
 
    // Caso esquerda direita
    if (balance > 1 && linha->matricula > nodo->esquerda->matricula)
    {
        nodo->esquerda =  rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }
 
    // Caso direita esquerda
    if (balance < -1 && linha->matricula < nodo->direita->matricula)
    {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }
 
    //retorna o ponteiro de nó (inalterado)
    return nodo;
}

//Função para obter o menor valor de matrícula presente na AVL
Nodo * menor_valor_avl(Nodo *nodo)
{
    struct Nodo* atual = nodo;
 
    /* laço "descendo" para encontrar o nó folha mais à esquerda */
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
 
    return atual;
}

//Função para deletar um registro da AVL pelo número de matrícula
Nodo* deletar_avl(Nodo *raiz, int matricula)
{
    // PASSO 1: Deleção padrão de ABB
 
    if (raiz == NULL)
    {
        return raiz;
    }
 
    // Se o valor a ser deletado é menor que o valor
    // na raiz, então a operação vai para a subárvore à esquerda
    if ( matricula < raiz->matricula )
    {
        raiz->esquerda = deletar_avl(raiz->esquerda, matricula);
    }
 
    // Se o valor a ser deletado é maior que o valor
    // na raiz, então a operação vai para a subárvore à direita
    else if( matricula > raiz->matricula )
    {
        raiz->direita = deletar_avl(raiz->direita, matricula);
    }
 
    // Se o valor for o mesmo que o presente no nó raiz, então este
    // é o nó a ser deletado
    else
    {
        // nó com apenas um filho ou nenhum filho
        if( (raiz->esquerda == NULL) || (raiz->direita == NULL) )
        {
            struct Nodo *temporario = raiz->esquerda ? raiz->esquerda : raiz->direita;
 
            // Caso em que o nó não possui filhos
            if (temporario == NULL)
            {
                temporario = raiz;
                raiz = NULL;
            }
            else // Caso em que o nó possui apenas um filho
            {
                *raiz = *temporario;   // Copia as informações do filho não vazio
            }

            free(temporario);
        }
        else
        {
            // Nó com dois filhos: Obter o sucessor inordem
            // (menor valor da subárvore á direita)
            struct Nodo* temporario = menor_valor_avl(raiz->direita);
 
            // Copia o valdor do nó sucessor inordem para o nó atual
            raiz->matricula = temporario->matricula;
 
            // Deleta o sucessor inordem
            raiz->direita = deletar_avl(raiz->direita, temporario->matricula);
        }
    }
 
    // Se a árvore tem apenas um nó então retorna ela mesma
    if (raiz == NULL)
    {
        return raiz;
    }
 
    // PASSO 2: ATUALIZAR A ALTURA DO NÓ ATUAL
    raiz->altura = 1 + maximo(altura_arvore(raiz->esquerda),altura_arvore(raiz->direita));
 
    // PASSO 3: PEGA O FATOR DE BALANCEAMENTO DO NÓ (para
    // checar se este nó se tornou desbalanceado)
    int balanceamento = fator_balanceamento(raiz);
 
    // Se o nó se tornou desbalanceado, então haverá quatro casos para analisar
 
    // Caso esquerda esquerda
    if (balanceamento > 1 && fator_balanceamento(raiz->esquerda) >= 0)
    {
        return rotacao_direita(raiz);
    }
 
    // Caso esquerda direita
    if (balanceamento > 1 && fator_balanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda =  rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
 
    // Caso direita direita
    if (balanceamento < -1 && fator_balanceamento(raiz->direita) <= 0)
    {
        return rotacao_esquerda(raiz);
    }
 
    // Caso direita esquerda
    if (balanceamento < -1 && fator_balanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }
 
    return raiz;
}

//Função para buscar um nome dentro dos registros da AVL
int busca_nodo_nome(Nodo *atual, char *nome)
{
    if(atual == NULL) //Caso o nodo não seja encontrado ou a AVL esteja vazia
    {
    	return 0;
    }
    else
    {
    	if(strcmp(atual->nome,nome) == 0) //Se o nome presente no nodo atual for igual ao nome buscado
    	{
    		return 1;
    	}

    	//Percorre a AVL a esquerda e a direita em busca do nome
    	int esquerda = busca_nodo_nome(atual->esquerda,nome);
    	
    	if(esquerda)
    	{
    		return 1;
    	}
    	else
    	{
    		int direita = busca_nodo_nome(atual->direita,nome);
    		if(direita)
    		{
    			return 1;
    		}
    	}
    }

	return 0;
}

//Função de busca pelo número de matrícula
Nodo* busca_nodo_matricula(Nodo *atual, int matricula)
{
    if(atual == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
    	//printf("\n\tNODO NAO ENCONTRADO\n");
        return NULL;
    }
    else if(matricula < atual->matricula) //quando o valor buscado é menor que o valor presente no nó atual
    {
        return busca_nodo_matricula(atual->esquerda,matricula);//busca na árvore continua pelo nó filho a esquerda do nó atual
    }
    else if(matricula > atual->matricula) //quando o valor buscado é maior que o valor presente no nó atual
    {
        return busca_nodo_matricula(atual->direita,matricula);//busca na árvore continua pelo nó filho a direita do nó atual
    }
    else
    {	
    	//printf("\n\t\t\tNODO ENCONTRADO\n");
        return atual; //quando o nó com o valor buscado é encontrado
    }
}

//Função de impressão da AVL
void impressao_formato_arvore(Nodo *raiz, int espaco)
{
    // Caso base
    if (raiz == NULL)
    {
        return;
    }
 
    // Incrementa a distância entre níveis
    espaco += COUNT;
 
    // Processa nó a direita primeiro
    impressao_formato_arvore(raiz->direita, espaco);
 
    // Imprime nó atual depois de dar o número de espaços
    // contador
    printf("\n");

    int i;

    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }

    printf("-Numero de matricula: %d\n", raiz->matricula);
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    printf("-Nome: %s\n", raiz->nome);
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    printf("-Sobrenome: %s\n", raiz->sobrenome);
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    printf("-E-mail: %s\n", raiz->email);
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    printf("-Telefone: %s\n", raiz->telefone);
    for (i = COUNT; i < espaco; i++)
    {
        printf(" ");
    }
    printf("-Salario: %.2lf\n", raiz->salario);
 
    // Processa nós a esquerda
    impressao_formato_arvore(raiz->esquerda, espaco);
}

//a função abaixo recebe a linha do arquivo csv e a quebra em várias strings a partir do delimitador ","
//para cada string gerada pela quebra, a mesma ocupa uma variável e faz procedimentos diferentes
registro* quebra_string_avl(char *string_recebida)
{
	registro *linha_arquivo = malloc(sizeof(registro));

	char *string_recebida_copia = strdup(string_recebida); //duplicando para uma string temporária a string recebida na função
	
	char *string_cortada; //ponteiro de caracter (string) para as palavras quebradas

	string_cortada = strtok(string_recebida_copia, ","); //função para quebrar a string pela primeira vez
	
	linha_arquivo->matricula = atoi(string_cortada); //a função atoi converte de string para inteiro
	
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
				strcpy(linha_arquivo->nome,string_cortada); //função que copia o conteúdo da string cortada para a variável nome
			}
			if(contador_variaveis_alocacao == 3) //Condição para colocar a string correta na variável sobrenome
			{
				strcpy(linha_arquivo->sobrenome,string_cortada); //função que copia o conteúdo da string cortada para a variável sobrenome
			}
			if(contador_variaveis_alocacao == 4) //Condição para colocar a string correta na variável e-mail
			{
				strcpy(linha_arquivo->email,string_cortada); //função que copia o conteúdo da string cortada para a variável e-
			}
			if(contador_variaveis_alocacao == 5) //Condição para colocar a string correta na variável telefone
			{
				strcpy(linha_arquivo->telefone,string_cortada); //função que copia o conteúdo da string cortada para a variável tele
			}
			if(contador_variaveis_alocacao == 6) //Condição para colocar a string correta na variável salário
			{
				linha_arquivo->salario=strtod(string_cortada,NULL); //função que converte o conteúdo da string cortada para double e o armazena na variável salário
			}
		}
	}
		
	return linha_arquivo;
}