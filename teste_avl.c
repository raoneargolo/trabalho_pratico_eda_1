//Quebra de string: ok
//Inserção no nó da árvore: ok
//Impressão: ok
//Remoção:
//Busca por matricula:
//Busca por nome:

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000
#define COUNT 5

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

typedef struct registro
{
	int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
	char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
	char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
	char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
	char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
	double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado
}registro;

/*typedef struct registro
{
	int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
	char *nome; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
	char *sobrenome;//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
	char *email; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
	char *telefone; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
	double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado
}registro;*/


int altura_arvore(Nodo *novo);
int maximo(int a, int b);
Nodo* novo_nodo(registro linha_arquivo);
//Nodo* novo_nodo (int matricula, char nome, char sobrenome, char email, char telefone, double salario);
//Nodo* novo_nodo (int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario);
Nodo *rotacao_direita(Nodo *atual);
Nodo *rotacao_esquerda(Nodo *atual);
int fator_balanceamento(Nodo *atual);
Nodo* inserir_avl(Nodo *nodo, registro linha);
//Nodo* inserir_avl(Nodo *nodo, int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario);
//Nodo* inserir_avl(Nodo *nodo, int matricula, char nome, char sobrenome, char email, char telefone, double salario);
Nodo * menor_valor_avl(Nodo *nodo);
Nodo* deletar_avl(Nodo *raiz, int matricula);
Nodo* busca_nodo_nome(Nodo *raiz, char *nome);
Nodo* busca_nodo_matricula(Nodo *raiz, int matricula);
void impressao_formato_arvore(Nodo *raiz, int espaco);
registro quebra_string(char *string_recebida);

int main() {	

	//printf("\nInicio do main\n");

	//printf("\nCriando arquivo");
	FILE *arquivo; //variável para conter o arquivo csv a ser lido
	//printf("\nArquivo criado");
	//printf("\nCriando string (vetor de char)");
	char linha_atual[tamanho_caracteres_linha]; //ponteiro de caracter (string) para conter a linha atual lida do arquivo
	//printf("\nString criada (vetor de char)");
	//printf("\nCriando raiz da AVL");
	Nodo *raiz = NULL;
	//printf("\nRaiz da AVL criada");
	//printf("\nStruct registro criada");
	registro linha;
	//printf("\nStruct registro criada");
	//printf("\nAbrindo arquivo");
	arquivo = fopen("teste1.csv","r"); //Procedimento para leitura do arquivo csv
	//printf("\nArquivo criado");
	
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
			raiz = inserir_avl(raiz,linha);
			//chamada_insercao++;
			//raiz = inserir_avl(raiz,linha.matricula,linha.nome,linha.sobrenome,linha.email,linha.telefone,linha.salario);

			//raiz = novo_nodo(linha);
			//raiz = novo_nodo(linha.matricula,linha.nome,linha.sobrenome,linha.email,linha.telefone,linha.salario);
		}
		
		qt_linhas_lidas++;
	}

	//printf("\nFim do main\n");

	//printf("\nChamando funcao de impressao\n");

	impressao_formato_arvore(raiz,0);

	fclose(arquivo); //função para fechar o arquivo recebido e lido

	return 0;
}

// A utility function to get altura of the tree
int altura_arvore(Nodo *novo)
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

//Nodo* novo_nodo (int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario)
//Nodo* novo_nodo (int matricula, char nome, char sobrenome, char email, char telefone, double salario)
Nodo* novo_nodo(registro linha)
{
	//printf("\nentrei na funcao de criar um novo nodo\n");
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    //printf("\nAloquei novo nodo\n");

    /*printf("\nValores passados para a funcao de criar novo nodo\n");
    printf("Numero de Matricula: %d\n", linha.matricula);
	printf("Nome: %s\n", linha.nome);			
	printf("Sobrenome: %s\n", linha.sobrenome);
	printf("E-mail: %s\n", linha.email);
	printf("Telefone: %s\n", linha.telefone);
	printf("Salario: %.2lf\n", linha.salario);*/

    /*printf("\nValores passados para a funcao\n");
	printf("Numero de Matricula: %d\n", matricula);
	printf("Nome: %s\n", nome);			
	printf("Sobrenome: %s\n", sobrenome);
	printf("E-mail: %s\n", email);
	printf("Telefone: %s\n", telefone);
	printf("Salario: %.2lf\n", salario);*/

	nodo->matricula = linha.matricula;
	//nodo->matricula = matricula;
	//printf("\nMatricula: ok\n");

	/*printf("\nAntes de strcpy - Dentro de nodo->nome: %s\n",nodo->nome);
	printf("\nAntes de strcpy - Dentro de linha.nome: %s\n",linha.nome);*/
    strcpy(nodo->nome,linha.nome);
    /*printf("\nDepois de strcpy - Dentro de nodo->nome: %s\n",nodo->nome);
    printf("\nDepois de strcpy - Dentro de linha.nome: %s\n",linha.nome);*/
    //strcpy(nodo->nome,nome);
    //printf("\nNome: ok\n");
    
    strcpy(nodo->sobrenome,linha.sobrenome);
    //strcpy(nodo->sobrenome,sobrenome);
    //printf("\nSobrenome: ok\n");
    
    strcpy(nodo->email,linha.email);
    //strcpy(nodo->email,email);
    //printf("\nEmail: ok\n");
    
    strcpy(nodo->telefone,linha.telefone);
    //strcpy(nodo->telefone,telefone);
    //printf("\nTelefone: ok\n");
    
    nodo->salario = linha.salario;
    //nodo->salario = salario;
    //printf("\nSalario: ok\n");

    nodo->esquerda = NULL;
    //printf("\nFilho a esquerda NULL\n");
    
    nodo->direita = NULL;
    //printf("\nFilho a direita NULL\n");

    nodo->altura = 1;  // novo nó é inicialmente adcionado nas folhas
    //printf("\nAltura 1\n");

    return(nodo);
}

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

int fator_balanceamento(Nodo *atual)
{
    if (atual == NULL)
    {
        return 0;
    }

    return altura_arvore(atual->esquerda) - altura_arvore(atual->direita);
}

//Nodo* inserir_avl(Nodo *nodo, int matricula, char *nome, char *sobrenome, char *email, char *telefone, double salario)
//Nodo* inserir_avl(Nodo *nodo, int matricula, char nome, char sobrenome, char email, char telefone, double salario)
Nodo* inserir_avl(Nodo *nodo, registro linha)
{
	//printf("\nEntrei na funcao de insercao\n");

	/*printf("\nValores passados para a funcao de insercao\n");
	printf("Numero de Matricula: %d\n", linha.matricula);
	printf("Nome: %s\n", linha.nome);			
	printf("Sobrenome: %s\n", linha.sobrenome);
	printf("E-mail: %s\n", linha.email);
	printf("Telefone: %s\n", linha.telefone);
	printf("Salario: %.2lf\n", linha.salario);*/

	/*printf("Numero de Matricula: %d\n",matricula);
	printf("Nome: %s\n",nome);			
	printf("Sobrenome: %s\n",sobrenome);
	printf("E-mail: %s\n",email);
	printf("Telefone: %s\n",telefone);
	printf("Salario: %.2lf\n",salario);*/

    //1.  Faz a rotação normal na ABB
    //printf("\nVerificando se a arvore esta vazia\n");
    if (nodo == NULL)
    {
    	//printf("\nAVL Vazia. Criando nodo");
        return(novo_nodo(linha));
        //return(novo_nodo(matricula,&nome,&sobrenome,&email,&telefone,salario));
    }
 	//printf("\nVerificando se a matricula e menor que o nodo atual\n");
    if (linha.matricula < nodo->matricula)
    //if (matricula < nodo->matricula)
    {
    	//printf("\nMatricula menor que o nodo atual");
        nodo->esquerda  = inserir_avl(nodo->esquerda, linha);
        //nodo->esquerda  = inserir_avl(nodo->esquerda,matricula,nome,sobrenome,email,telefone,salario);
    }
    //printf("\nVerificando se a matricula e maior que o nodo atual\n");
    //else if (matricula > nodo->matricula)
	else if (linha.matricula > nodo->matricula)    	
    {
    	//printf("\nMatricula maior que o nodo atual");
        nodo->direita = inserir_avl(nodo->direita, linha);
        //nodo->direita  = inserir_avl(nodo->direita,matricula,nome,sobrenome,email,telefone,salario);
    }
    //printf("\nA matricula e igual ao nodo atual\n");
    else // Valores iguais não são permitidos
    {
    	//printf("\nMatricula igual ao nodo atual");
        return nodo;
    }
 
    // 2. Atualiza altura do nó antecessor
    nodo->altura = 1 + maximo(altura_arvore(nodo->esquerda),altura_arvore(nodo->direita));
 
    // 3. Obtém o fator de balanceamento do nó antecessor para checar se o nó se tornou desbalanceado
    int balance = fator_balanceamento(nodo);
 
    // Se o nó se torna desbalanceado, então há quatro casos para considerar
 
    // Caso esquerda esquerda
    if (balance > 1 && linha.matricula < nodo->esquerda->matricula)
    //if (balance > 1 && matricula < nodo->esquerda->matricula)
    {
        return rotacao_direita(nodo);
    }
 
    // Caso direita direita
    if (balance < -1 && linha.matricula > nodo->direita->matricula)
    //if (balance < -1 && matricula > nodo->direita->matricula)
    {
        return rotacao_esquerda(nodo);
    }
 
    // Caso esquerda direita
    if (balance > 1 && linha.matricula > nodo->esquerda->matricula)
    //if (balance > 1 && matricula > nodo->esquerda->matricula)
    {
        nodo->esquerda =  rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }
 
    // Caso direita esquerda
    if (balance < -1 && linha.matricula < nodo->direita->matricula)
    //if (balance < -1 && matricula < nodo->direita->matricula)
    {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }
 
    //retorna o ponteiro de nó (inalterado)
    return nodo;
}

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

Nodo* deletar_avl(Nodo *raiz, int matricula)
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

Nodo* busca_nodo_nome(Nodo *raiz, char *nome)
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

Nodo* busca_nodo_matricula(Nodo *raiz, int matricula)
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
    
    //printf("\nImprimindo\n");
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