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
registro* quebra_string(char *string_recebida);
int erd (Nodo *atual, char *nome);

int main() {	

	FILE *arquivo; //variável para conter o arquivo csv a ser lido
	
	char linha_atual[tamanho_caracteres_linha]; //ponteiro de caracter (string) para conter a linha atual lida do arquivo
	
	Nodo *raiz = NULL;
	
    registro *linha;

    //time_t tempo_inicio, tempo_fim;
    clock_t tempo_inicio, tempo_fim;

    long double tempo_duracao;

    char nome_arquivo[tamanho_caracteres];

    printf("\nDigite o nome do arquivo (com a extensao): ");
	scanf("%s",nome_arquivo);

    arquivo = fopen(nome_arquivo,"r"); //Procedimento para leitura do arquivo csv
	
	if (arquivo == NULL) //Caso o arquivo não seja encontrado
	{
		printf("\nArquivo nao encontrado\n");
		return 0;
	}

	//tempo_inicio = time(NULL);
	tempo_inicio = clock();

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

			raiz = inserir_avl(raiz, linha);
		}
		
		qt_linhas_lidas++;
	}

	//impressao_formato_arvore(raiz,0);

	//tempo_fim = time(NULL);
	tempo_fim = clock();

	//tempo_duracao = difftime(tempo_fim,tempo_inicio);
	tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

	//printf("\nMomento de inicio: %f (s) \n",((double)tempo_inicio/CLOCKS_PER_SEC));// exibe o momento do inicio t=0
    //printf("\nMomento de fim: %f (s) \n",((double)tempo_fim/CLOCKS_PER_SEC)); //exibe o hora final
    printf("\nTempo da importacao e insercao dos registros: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )

	//printf("\nTempo de duracao da insercao e importacao: %.10Lf\n", tempo_duracao);
	fclose(arquivo); //função para fechar o arquivo recebido e lido

	//impressao_formato_arvore(raiz,0);

	printf("\n\t\tOpcoes disponiveis\n");
	printf("\n1-Busca por numero de matricula");
	printf("\n2-Busca por nome");
	printf("\n3-Imprimir arvore");
	printf("\n4-Insercao manual");
	printf("\n5-Remover um registro pelo numero de matricula");
	printf("\n6-Sair");
	
	printf("\n\nDigite a opcao desejada: ");
	int opcao;
	scanf("%d",&opcao);

	while(opcao!=6)
	{
		if(opcao == 1)
		{
			
			int matricula_busca;

			Nodo *busca = (Nodo*)malloc(sizeof(Nodo));

			printf("\nDigite um numero de matricula para busca: ");
			scanf("%d",&matricula_busca);
			
			tempo_inicio = clock();

			busca_nodo_matricula(raiz,matricula_busca);
			
			tempo_fim = clock();
			
			tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
			
			printf("\nTempo da busca por matricula: %Lf (s) \n",tempo_duracao);
		}
		else if(opcao == 2)
		{
			char nome_busca[tamanho_caracteres];
	
			printf("\nDigite um nome para busca: ");
			fflush(stdin);
			scanf("%s",nome_busca);

			tempo_inicio = clock();
			
			int resultado_busca = busca_nodo_nome(raiz,nome_busca);
			
			tempo_fim = clock();
			if(resultado_busca == 1)
			{	
				printf("\nNome encontrado!\n");
			}
			else
			{
				printf("\nNome nao encontrado!\n");
			}
			
			tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
			
			printf("\nTempo da busca por nome: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
		}
		else if(opcao == 3)
		{
			tempo_inicio = clock();
			
			impressao_formato_arvore(raiz,0);
			
			tempo_fim = clock();
			
			tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
			
			printf("\nTempo da exibicao dos registros: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
		}
		else if(opcao == 4)
		{

			int matricula_busca;
			printf("\nDigite uma matricula para inserir: ");
			scanf(" %d",&matricula_busca);

			registro *insercao_manual = malloc(sizeof(registro));
			
			tempo_inicio = clock();
			
			if(busca_nodo_matricula(raiz,matricula_busca) == NULL)
			{
				printf("\nMatricula liberada. Insira os dados");
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


				raiz = inserir_avl(raiz,insercao_manual);

				printf("\nResultado da arvore apos insercao manual\n");
				impressao_formato_arvore(raiz,0);
			}
			else
			{
				printf("\nMatricula bloqueada. Ja existe um usuario cadastrado\n");
			}

			tempo_fim = clock();
				
			tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
				
			printf("\nTempo da busca e insercao manual do registro: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
		}
		else if(opcao == 5)
		{

			int matricula_busca;

			printf("\nDigite um numero de matricula para busca e posterior remocao: ");
			scanf("%d",&matricula_busca);

			
			if(busca_nodo_matricula(raiz,matricula_busca)!=NULL)
			{
				printf("\n\t\tO valor foi encontrado e removido!");
				
				tempo_inicio = clock();

				raiz = deletar_avl(raiz,matricula_busca);
				
				tempo_fim = clock();
				
				printf("\nDeseja imprimir a arvore? Digite 1 para SIM e 2 para NAO: ");
				int opcao_2;
				scanf("%d",&opcao_2);

				if(opcao_2 == 1)
				{
					printf("\n\t\tArvore AVL apos remocao\n");
					impressao_formato_arvore(raiz,0);
				}
			}
			else
			{
				printf("\n\t\tO valor não foi encontrado\n");
			}

				
			tempo_duracao = ((long double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
				
			printf("\nTempo da importacao e insercao dos registros: %Lf (s) \n",tempo_duracao); // exibe a diferenca do (inicio - final )
		}

		printf("\n\t\tOpcoes disponiveis\n");
		printf("\n1-Busca por numero de matricula");
		printf("\n2-Busca por nome");
		printf("\n3-Imprimir arvore");
		printf("\n4-Insercao manual");
		printf("\n5-Remover um registro pelo numero de matricula");
		printf("\n6-Sair");
		printf("\n\nDigite a opcao desejada: ");
		scanf("%d",&opcao);
	}

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

int busca_nodo_nome(Nodo *atual, char *nome)
{
    if(atual == NULL)
    {
    	return 0;
    }
    else
    {
    	if(strcmp(atual->nome,nome) == 0)
    	{
    		printf("%s\n",atual->nome);
    		return 1;
    	}

    	int ta_na_esquerda = busca_nodo_nome(atual->esquerda,nome); 
    	
    	if(ta_na_esquerda)
    	{
    		return 1;
    	}
    	else
    	{
    		int ta_na_direita = busca_nodo_nome(atual->direita,nome);
    		if(ta_na_direita)
    		{
    			return 1;
    		}
    	}
    }
	return 0;
}// fim da função busca por nome

Nodo* busca_nodo_matricula(Nodo *atual, int matricula)
{
    if(atual == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
    	printf("\n\tNODO NAO ENCONTRADO\n");
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
    	printf("\n\t\tNODO ENCONTRADO\n");
        return atual; //quando o nó com o valor buscado é encontrado
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
registro* quebra_string(char *string_recebida)
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
