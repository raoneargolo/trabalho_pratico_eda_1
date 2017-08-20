#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000

#define MALLOC(a) (a *) malloc ( sizeof(a) )


// CAMPO DAS  ESTRUTURAS
//LISTA DUPLAMENTE ENCADEADA
struct no
{
   int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
   char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
   char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
   char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
   char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
   double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado        
   
   struct no *prox;
   struct no *ant;
};

typedef struct registro
{
   int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
   char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
   char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
   char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
   char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
   double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado
}registro;

// ponteiros de referência
struct no *inicio;
struct no *fim;

// CAMPO DOS PROTOTIPOS LISTA
void inserir (registro linha); 
void imprimeLista (void);
struct no *busca_matricula (int matricula);
struct no *busca_nome (char *nome);
void remover ( struct no *dado );
registro quebra_string(char *string_recebida);




int main(int argc, char const *argv[])
{   
	FILE *arquivo;
	float tempo;
	time_t t_ini, t_fim;
	int matricula_busca;
	int opc,tipo;
	//char frase [1000];
	char nome_arq[20];
	char linha_atual[tamanho_caracteres_linha];
	char nome_busca[tamanho_caracteres];
	inicio = fim = NULL;
    registro linha;
 	int qt_linhas_lidas = 0;

	printf(" \t\t\t ################## BEM VINDO ###################\n");
	printf(" Digite o nome do arquivo a ser importado (com a extensao)\n");
	scanf("%s",nome_arq);

	arquivo=fopen(nome_arq,"r");		// Leitura de arquivo
	while (arquivo== NULL)
	{
		printf("ERRO: Arquivo nao encontrado!\n");
		printf(" Digite o nome do arquivo a ser importado (com a extensao)\n");
		scanf("%s",nome_arq);
		arquivo=fopen(nome_arq,"r");		// Leitura de arquivo
	}
	printf("Abrindo arquivo... \n\n");
	while (fgets(linha_atual,tamanho_caracteres_linha,arquivo)!=NULL)
	   {
	      if(qt_linhas_lidas>1) //Assumind
	      {
	         linha = quebra_string(linha_atual); //função para "quebrar" string
	         inserir(linha);
	      }  
	      qt_linhas_lidas++;
	   }
	      imprimeLista();
	printf("Arquivo aberto! \n\n");
	fclose(arquivo);

	// JOGAR NAS DUAS ESTRTURUAS
	// MOSTRAR O TEMPO DE IMPORTACAO DE CADA ESTRUTURA


	printf(" \t\t\t ################## MENU ###################\n");
	printf("ESCOLHA UMA DAS OPCOES\n");
	printf("1-Manipulacao de dados na Arvore AVL \n");
	printf("2-Manipulacao de dados na Lista Duplamente Encadeada\n");
	printf(" \t\t\t ###########################################\n");
	scanf ("%d",&tipo);

	switch (tipo)
	{
		case 1://ARVORE
		{ 
			printf(" \t\t\t ################## MENU ###################\n");
			printf("ESOLHA UMA DAS OPCOES\n");
			printf("1-Exibicao dos registros\n");
			printf("2-Buscar registro por nome\n");
			printf("3-Buscar registro por matricula\n");
			printf("4-Insercao de um novo registro \n");
			printf("5-Remocao de um registro\n");
			printf(" \t\t\t ###########################################\n");
			scanf ("%d",&opc);
			switch (opc)
			{
				case 1:{
					printf("######### EXIBICAO DOS REGISTROS #########\n\n");
					//PRINTAR A ESTRUTURA 
					//PRINTAR A A QUANTIDADE DE REGISTROS
					//PRINTAR O TEMPO DA IMPORTACAO ???

				}
				case 2:
				{
					printf("############## BUSCA POR NOME #############\n\n");
					printf("Informe o nome para buscar\n");
					//scanf("%s",);

				}
				case 3:
				{
					printf("####### BUSCA POR MATRICULA #######\n\n");
					printf("Informe a matricula desejada\n");
					//scanf("%d",);
				}
				case 4:
				{
					printf("####### REMOVER UM REGISTRO #######\n\n");
					printf("Informe o numero da matricula\n");
					//scanf("%d",);
				}
				case 5:
				{
					printf("####### INSERIR UM NOVO REGISTRO #######\n\n");
					printf("Infome o numero da matricula\n");
					//scanf("%d",);

				}
				
					

			}
		}

		case 2: //LISTA
		{
			printf(" \t\t\t ################## MENU ###################\n");
			printf("ESOLHA UMA DAS OPCOES\n");
			printf("1-Exibicao dos registros\n");
			printf("2-Buscar registro por nome\n");
			printf("3-Buscar registro por matricula\n");
			printf("4-Insercao de um novo registro \n");
			printf("5-Remocao de um registro\n");
			printf(" \t\t\t ###########################################\n");
			scanf ("%d",&opc);
			switch (opc)
			{
				case 1:{
					printf("######### EXIBICAO DOS REGISTROS #########\n\n");
					imprimeLista();
   					printf("Quantidade de registros %d\n",qt_linhas_lidas-2);
   					break;
					//PRINTAR A ESTRUTURA  	OK
					//PRINTAR A A QUANTIDADE DE REGISTROS OK
					//PRINTAR O TEMPO DA IMPORTACAO ???

				}
				case 2:
				{
					printf("############## BUSCA POR NOME #############\n\n");
					printf("Informe o nome para buscar\n");
					fflush(stdin);
					scanf("%s",nome_busca);
				   if(busca_nome(nome_busca)!=NULL)
				   {
				      printf("\n NOME ENCONTRADO\n");
				   }
				   else
				   {
				      printf("\n NOME NAO ENCONTRADO\n");
				   }

				}
				case 3:
				{
					printf("####### BUSCA POR MATRICULA #######\n\n");
					printf("Informe a matricula desejada\n");
					scanf("%d",&matricula_busca);
					if(busca_matricula(matricula_busca)!=NULL)
				   {
				      printf("\n\t\t VALOR ENCONTRADO \n");
				   }
				   else
				   {
				      printf("\n\t\tVALOR NAO ENCONTRADO\n");
				   }

			    }
				case 4:
				{
					printf("####### INSERIR UM REGISTRO #######\n\n");
					printf("Informe o numero da matricula\n");
					scanf("%d",&matricula_busca);
					if(busca_matricula(matricula_busca)!=NULL)
					   {
					      printf("\nNUMERO DE MATRICULA EM USO\n");
					   }
				   else
					   {
					      printf("\nMATRICULA LIBERADA PARA INSERCAO\n");
					      printf("\nInforme os dados:\n");
					      
					      linha.matricula=matricula_busca;
					      printf("Nome:");
					      scanf("%s",linha.nome);
					      
					      printf("Sobrenome:");
						  scanf("%s",linha.sobrenome);
					      
					      printf("Email:");
						  scanf("%s",linha.email);
					      
					      printf("Telefone:");
						  scanf("%s",linha.telefone);

					      printf("Salario:");
						  scanf("%lf",&linha.salario);
						
					      t_ini = time (NULL);
					      
					      inserir(linha);

					      imprimeLista();

					      t_fim = time (NULL);
					      
					      // CALCULO DO TEMPO
					      tempo = difftime (t_fim, t_ini);
						  printf("Tempo apos inserir novo registro: %.2f\n", tempo );
					   }
				}
				case 5:
				{
					printf("####### REMOVER UM REGISTRO #######\n\n");
					printf("\nDigite um numero de matricula para busca e posterior remocao: ");
			   		scanf("%d",&matricula_busca);

					//struct no *busca = (struct no*)malloc(sizeof(struct no));

				   if(busca_matricula(matricula_busca)!=NULL)
				   {
				      printf("\n\t\tVALOR ENCONTRADO\n");
				      remover(busca_matricula(matricula_busca));
				   }
				   else
				   {
				      printf("\n\t\tVALOR NAO ENCONTRADO\n");
				   }

				   imprimeLista();

				}
			printf(" \t\t\t ################## MENU ###################\n");
			printf("ESOLHA UMA DAS OPCOES\n");
			printf("1-Exibicao dos registros\n");
			printf("2-Buscar registro por nome\n");
			printf("3-Buscar registro por matricula\n");
			printf("4-Insercao de um novo registro \n");
			printf("5-Remocao de um registro\n");
			printf(" \t\t\t ###########################################\n");
			scanf ("%d",&opc);
			}
		}
    }

	return 0;
}

// CAMPO DAS FUNCOES
void inserir (registro linha)
{
   struct no *novo = MALLOC (struct no);
   
   struct no *atual;
        
   if ( !novo )
   {
      perror ( "Malloc: " );
      return ;
   }
        
   // atribuição do novo valor...
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
        
   // se não for o primeiro elemento da lista...
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


void imprimeLista (void)
{
	int cont=0;
   struct no *atual = inicio;
        
   while (atual)
   {
      printf("\n\n");
	  printf("ELEMENTO : %d\n", cont);
      printf("Numero de Matricula: %d\n", atual->matricula);
      printf("Nome: %s\n", atual->nome);        
      printf("Sobrenome: %s\n", atual->sobrenome);
      printf("E-mail: %s\n", atual->email);
      printf("Telefone: %s\n", atual->telefone);
      printf("Salario: %.2lf\n", atual->salario);
      
      atual = atual->prox;
      cont++;
   }
   return ;
}

struct no *busca_matricula (int matricula)
{
   struct no *atual = inicio;
        
   while ( atual )
   {
      if ( atual->matricula == matricula)
      {
         return atual;
      }
      else
      {
         atual = atual->prox;
      }
   }
   return NULL;
}

struct no *busca_nome (char *nome)
{
   struct no *atual = inicio;

   int comparador;

   while ( atual )
   {
      comparador = strcmp(nome,atual->nome);

      if(comparador == 0)
      {
         return atual;
      }
      else
      {
         atual = atual->prox;
      }
   }
   return atual;
}


void remover ( struct no *dado )
{  
   if ( !dado )
   {
      return ;
   }
        
   // item intermediário
   if ( dado->prox && dado->ant )
   {
      dado->ant->prox = dado->prox;
      dado->prox->ant = dado->ant;
                
      free ( dado );
      return ;
   }
        
   // primeiro item
   if ( dado == inicio )
   {
      inicio = dado->prox;
      inicio->ant = NULL;
                
      free ( dado );
      return ;
   }
        
   // último elemento
   if ( dado == fim )
   {
      fim = dado->ant;
      fim->prox = NULL;
                
      free ( dado );
      return ;
   }
}

registro quebra_string(char *string_recebida)
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
