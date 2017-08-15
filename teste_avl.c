//trabalhar a função de inserção
//resolver como inserir na avl dentro da função que quebra string


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000
#define COUNT 5

struct Nodo
{
    int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
    struct Nodo *esquerda;
    struct Nodo *direita;
    int altura;
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


int altura_arvore(struct Nodo *novo);
int maximo(int a, int b);
struct Nodo* novo_nodo(registro linha_arquivo);
struct Nodo *rotacao_direita(struct Nodo *atual);
struct Nodo *rotacao_esquerda(struct Nodo *atual);
int fator_balanceamento(struct Nodo *atual);
struct Nodo* inserir_avl(struct Nodo* nodo, registro linha_arquivo);
struct Nodo * menor_valor_avl(struct Nodo* nodo);
struct Nodo* deletar_avl(struct Nodo* raiz, int matricula);
struct Nodo* busca_nodo_nome(struct Nodo* raiz, char *nome);
struct Nodo* busca_nodo_matricula(struct Nodo* raiz, int matricula);
void impressao_formato_arvore(struct Nodo *raiz, int espaco);
struct registro quebra_string(char *string_recebida);

int main() {	

	FILE *arquivo; //variável para conter o arquivo csv a ser lido
	char linha_atual [tamanho_caracteres_linha]; //ponteiro de caracter (string) para conter a linha atual lida do arquivo

	struct Nodo *raiz = NULL;

	registro linha;

	arquivo=fopen("teste1.csv","r"); //Procedimento para leitura do arquivo csv
	
	if (arquivo == NULL) //Caso o arquivo não seja encontrado
	{
		printf("arquivo nao encontrado");
		return 0;
	}
	
	int qt_linhas_lidas=0; //variável para o controle do número de linhas dentro do arquivo csv
	
	//o loop abaixo tem como função ler cada linha do arquivo csv inserido (lê o arquivo csv até o seu final)
	//e partir da terceira linha lida (a primeira linha contém o número de registros dentro do arquivo e a segunda
	//o tipo de cada coluna) executar a quebra da linha em strings úteis para a aplicação
	while (fgets(linha_atual,tamanho_caracteres_linha,arquivo)!=NULL)
	{

		if(qt_linhas_lidas>1) //Assumind
		{
			linha = quebra_string(linha_atual); //função para "quebrar" string

			//inserir_avl(raiz,linha);
		}
		
		qt_linhas_lidas++;
	}

	impressao_formato_arvore(raiz,0);

	fclose(arquivo); //função para fechar o arquivo recebido e lido

	return 0;
}

// A utility function to get altura of the tree
int altura_arvore(struct Nodo *novo)
{
    if (novo == NULL)
    {
        return 0;
    }

    return novo->altura;
}

// Função para retornar o maior valor entre dois inteiros
int maximo(int a, int b)
{
    return (a > b)? a : b;
}

struct Nodo* novo_nodo(registro linha_arquivo)
{
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    

    nodo->matricula = linha_arquivo.matricula;
    strcpy(nodo->nome,linha_arquivo.nome);
    strcpy(nodo->sobrenome,linha_arquivo.sobrenome);
    strcpy(nodo->email,linha_arquivo.email);
    strcpy(nodo->telefone,linha_arquivo.telefone);
    nodo->salario = linha_arquivo.salario;
    

    nodo->esquerda   = NULL;

    nodo->direita  = NULL;
    

    nodo->altura = 1;  // novo nó é inicialmente adcionado nas folhas
    

    return(nodo);
}

struct Nodo *rotacao_direita(struct Nodo *atual)
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
struct Nodo *rotacao_esquerda(struct Nodo *atual)
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

int fator_balanceamento(struct Nodo *atual)
{
    if (atual == NULL)
    {
        return 0;
    }

    return altura_arvore(atual->esquerda) - altura_arvore(atual->direita);
}

struct Nodo* inserir_avl(struct Nodo* nodo, registro linha_arquivo)
{
    //1.  Faz a rotação normal na ABB
    if (nodo == NULL)
    {
    	printf("\nAVL Vazia. Criando nodo");
        return(novo_nodo(linha_arquivo));
    }
 
    if (linha_arquivo.matricula < nodo->matricula)
    {
    	printf("\nMatricula menor que o nodo atual");
        nodo->esquerda  = inserir_avl(nodo->esquerda, linha_arquivo);
    }
    else if (linha_arquivo.matricula > nodo->matricula)
    {
    	printf("\nMatricula maior que o nodo atual");
        nodo->direita = inserir_avl(nodo->direita, linha_arquivo);
    }
    else // Valores iguais não são permitidos
    {
    	printf("\nMatricula igual ao nodo atual");
        return nodo;
    }
 
    // 2. Atualiza altura do nó antecessor
    nodo->altura = 1 + maximo(altura_arvore(nodo->esquerda),altura_arvore(nodo->direita));
 
    // 3. Obtém o fator de balanceamento do nó antecessor para checar se o nó se tornou desbalanceado
    int balance = fator_balanceamento(nodo);
 
    // Se o nó se torna desbalanceado, então há quatro casos para considerar
 
    // Caso esquerda esquerda
    if (balance > 1 && linha_arquivo.matricula < nodo->esquerda->matricula)
    {
        return rotacao_direita(nodo);
    }
 
    // Caso direita direita
    if (balance < -1 && linha_arquivo.matricula > nodo->direita->matricula)
    {
        return rotacao_esquerda(nodo);
    }
 
    // Caso esquerda direita
    if (balance > 1 && linha_arquivo.matricula > nodo->esquerda->matricula)
    {
        nodo->esquerda =  rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }
 
    // Caso direita esquerda
    if (balance < -1 && linha_arquivo.matricula < nodo->direita->matricula)
    {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }
 
    //retorna o ponteiro de nó (inalterado)
    return nodo;
}

struct Nodo * menor_valor_avl(struct Nodo* nodo)
{
    struct Nodo* atual = nodo;
 
    /* laço "descendo" para encontrar o nó folha mais à esquerda */
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
 
    return atual;
}

struct Nodo* deletar_avl(struct Nodo* raiz, int matricula)
{
    // PASSO 1: Deleção padrão de ABB
 
    if (raiz == NULL)
    {
        printf("\n\t\t\tValor nao encontrado!\n");
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

struct Nodo* busca_nodo_nome(struct Nodo* raiz, char *nome)
{
	int auxiliar_comparador = strcmp(raiz->nome,nome);
    
    if(raiz == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
        return NULL;
    }
    else if(auxiliar_comparador > 0) //quando o valor buscado é menor que o valor presente no nó atual
    {
        return busca_nodo_nome(raiz->esquerda,nome);//busca na árvore continua pelo nó filho a esquerda do nó atual
    }
    else if(auxiliar_comparador < 0) //quando o valor buscado é maior que o valor presente no nó atual
    {
        return busca_nodo_nome(raiz->direita,nome);//busca na árvore continua pelo nó filho a direita do nó atual
    }
    else
    {
        return raiz; //quando o nó com o valor buscado é encontrado
    }
}

struct Nodo* busca_nodo_matricula(struct Nodo* raiz, int matricula)
{
    if(raiz == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
        return NULL;
    }
    else if(raiz->matricula > matricula) //quando o valor buscado é menor que o valor presente no nó atual
    {
        return busca_nodo_matricula(raiz->esquerda,matricula);//busca na árvore continua pelo nó filho a esquerda do nó atual
    }
    else if(raiz->matricula < matricula) //quando o valor buscado é maior que o valor presente no nó atual
    {
        return busca_nodo_matricula(raiz->direita,matricula);//busca na árvore continua pelo nó filho a direita do nó atual
    }
    else
    {
        return raiz; //quando o nó com o valor buscado é encontrado
    }
}

void impressao_formato_arvore(struct Nodo *raiz, int espaco)
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
    
    printf("\nImprimindo\n");
    printf("%d\n", raiz->matricula);
    printf("%s\n", raiz->nome);
    printf("%s\n", raiz->sobrenome);
    printf("%s\n", raiz->email);
    printf("%s\n", raiz->telefone);
    printf("%lf\n", raiz->salario);
 
    // Processa nós a esquerda
    impressao_formato_arvore(raiz->esquerda, espaco);
}

//a função abaixo recebe a linha do arquivo csv e a quebra em várias strings a partir do delimitador ","
//para cada string gerada pela quebra, a mesma ocupa uma variável e faz procedimentos diferentes
registro quebra_string(char *string_recebida)
{

	registro linha_arquivo;

	char *string_recebida_copia = strdup(string_recebida); //duplicando para uma string temporária a string recebida na função
	
	char *string_cortada; //ponteiro de caracter (string) para as palavras quebradas

	string_cortada = strtok(string_recebida_copia, ","); //função para quebrar a string pela primeira vez
	
	linha_arquivo.matricula = atoi(string_cortada); //a função atoi converte de string para inteiro
	
	printf("Numero de Matricula: %d\n", linha_arquivo.matricula); //exibir primeira palavra da string cortada
	
	//o contador abaixo é responsável por indicar em qual coluna a quebra de string está sendo efetuada, para armazenar o resultado
	//da quebra na variável correta
	int contador_variaveis_alocacao=1; //inciada com 1 pois a primeira coluna da linha foi quebrada

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
				printf("Nome: %s\n", linha_arquivo.nome);
			}
			if(contador_variaveis_alocacao == 3) //Condição para colocar a string correta na variável sobrenome
			{
				strcpy(linha_arquivo.sobrenome,string_cortada); //função que copia o conteúdo da string cortada para a variável sobrenome
				printf("Sobrenome: %s\n", linha_arquivo.sobrenome);
			}
			if(contador_variaveis_alocacao == 4) //Condição para colocar a string correta na variável e-mail
			{
				strcpy(linha_arquivo.email,string_cortada); //função que copia o conteúdo da string cortada para a variável e-mail
				printf("E-mail: %s\n", linha_arquivo.email);	
			}
			if(contador_variaveis_alocacao == 5) //Condição para colocar a string correta na variável telefone
			{
				strcpy(linha_arquivo.telefone,string_cortada); //função que copia o conteúdo da string cortada para a variável telefone
				printf("Telefone: %s\n", linha_arquivo.telefone);
			}
			if(contador_variaveis_alocacao == 6) //Condição para colocar a string correta na variável salário
			{
				linha_arquivo.salario=strtod(string_cortada,NULL); //função que converte o conteúdo da string cortada para double 
													 			   //e o armazena na variável salário
				printf("Salario: %.2lf\n", linha_arquivo.salario);
			}

			//printf("\nfim das impressoes dentro da funcao quebra string\n");

			return linha_arquivo;
		}
	}
	
	printf("\n");
}
