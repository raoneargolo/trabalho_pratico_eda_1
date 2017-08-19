                                                //Status das operações

//Inserção: OK
//Impressão: OK
//Busca por matricula: OK
//Busca por nome: OK
//Remoção: OK
//Inserção manual (busca e vê se não está na estrutura): 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000

#define MALLOC(a) (a *) malloc ( sizeof(a) )

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

/*
* imprimeLista - imprime todos os dados da lista
*/
void imprimeLista (void)
{
   struct no *atual = inicio;
        
   while (atual)
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
   return ;
}

/*
* procurar - procura um elemento na lista
*
* @ info - dado a ser pesquisado
*
* Retorno: ponteiro para o dado encontrado ou NULL caso não encontre
*/
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
}

/*
* remover - remove um nó da lista
* 
* @ dado - endereço do nó a ser removido
*/
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

// main...
int main ( void )
{
   inicio = fim = NULL;

   FILE *arquivo;

   char linha_atual[tamanho_caracteres_linha];

   registro linha;

   arquivo = fopen("teste1.csv","r");

   int qt_linhas_lidas = 0;

   if (arquivo == NULL) //Caso o arquivo não seja encontrado
   {
      printf("\nArquivo nao encontrado\n");
      return 0;
   }

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

   /*int matricula_busca;

   struct no *busca = (struct no*)malloc(sizeof(struct no));

   printf("\nDigite um numero de matricula para busca e posterior remocao: ");
   scanf("%d",&matricula_busca);

   if(busca_matricula(matricula_busca)!=NULL)
   {
      //raiz = deletar_avl(raiz,matricula_busca);
      //printf("\n\t\tArvore AVL apos remocao\n");
      //impressao_formato_arvore(raiz,0);
      printf("\n\t\tACHEI\n");
   }
   else
   {
      printf("\n\t\tVALOR NAO ENCONTRADO\n");
   }*/

   /*char nome_busca[tamanho_caracteres];
   
   printf("\nDigite um nome para busca: ");
   fflush(stdin);
   //fgets(nome_busca,tamanho_caracteres,stdin);
   scanf("%s",nome_busca);

   //struct no *busca = (struct no*)malloc(sizeof(struct no));

   if(busca_nome(nome_busca)!=NULL)
   {
      printf("\nDESGRACA! ACHEI\n");
   }
   else
   {
      printf("\nDESGRACA! NAO ACHEI\n");
   }*/

   /*int matricula_busca;

   struct no *busca = (struct no*)malloc(sizeof(struct no));

   printf("\nDigite um numero de matricula para busca e posterior remocao: ");
   scanf("%d",&matricula_busca);

   if(busca_matricula(matricula_busca)!=NULL)
   {
      printf("\n\t\tVALOR ENCONTRADO\n");
      remover(busca_matricula(matricula_busca));
   }
   else
   {
      printf("\n\t\tVALOR NAO ENCONTRADO\n");
   }

   imprimeLista();*/

   fclose(arquivo);

   return 0;
}