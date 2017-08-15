#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 5
 
// Um nó de árvore AVL
struct Nodo
{
    int dado;
    struct Nodo *esquerda;
    struct Nodo *direita;
    int altura;
};
 
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
 
/*Função auxiliar que alocar um novo nó com o valor recebido e seta como NULL os ponteiros a esquerda e direita*/
struct Nodo* novo_nodo(int dado)
{
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->dado = dado;
    nodo->esquerda   = NULL;
    nodo->direita  = NULL;
    nodo->altura = 1;  // novo nó é inicialmente adcionado nas folhas
    return(nodo);
}
 
// Função que rotaciona a direita a subàrvore do nó desbalanceado
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
 
// Função para obter o fator de balanceamento do nó
int fator_balanceamento(struct Nodo *atual)
{
    if (atual == NULL)
    {
        return 0;
    }

    return altura_arvore(atual->esquerda) - altura_arvore(atual->direita);
}

// Função recursiva para inserir valor na subárvore correta
// com o nó e retorna o novo nó da subárvore
struct Nodo* inserir_avl(struct Nodo* nodo, int valor)
{
    /* 1.  Faz a rotação normal na ABB */
    if (nodo == NULL)
    {
        return(novo_nodo(valor));
    }
 
    if (valor < nodo->dado)
    {
        nodo->esquerda  = inserir_avl(nodo->esquerda, valor);
    }
    else if (valor > nodo->dado)
    {
        nodo->direita = inserir_avl(nodo->direita, valor);
    }
    else // Valores iguais não são permitidos
    {
        return nodo;
    }
 
    /* 2. Atualiza altura do nó antecessor */
    nodo->altura = 1 + maximo(altura_arvore(nodo->esquerda),altura_arvore(nodo->direita));
 
    /* 3. Obtém o fator de balanceamento do nó antecessor
        para checar se o nó se tornou desbalanceado */
    int balance = fator_balanceamento(nodo);
 
    // Se o nó se torna desbalanceado, então há quatro casos para considerar
 
    // Caso esquerda esquerda
    if (balance > 1 && valor < nodo->esquerda->dado)
    {
        return rotacao_direita(nodo);
    }
 
    // Caso direita direita
    if (balance < -1 && valor > nodo->direita->dado)
    {
        return rotacao_esquerda(nodo);
    }
 
    // Caso esquerda direita
    if (balance > 1 && valor > nodo->esquerda->dado)
    {
        nodo->esquerda =  rotacao_esquerda(nodo->esquerda);
        return rotacao_direita(nodo);
    }
 
    // Caso direita esquerda
    if (balance < -1 && valor < nodo->direita->dado)
    {
        nodo->direita = rotacao_direita(nodo->direita);
        return rotacao_esquerda(nodo);
    }
 
    /* retorna o ponteiro de nó (inalterado) */
    return nodo;
}

/* Dada uma ABB não vazia, retorna o nó com o menor valor
   encontrado na árvore. Não precisa buscar a árvore inteira */
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

// Função recursiva para deletar o nó com um certo valor 
// da subárvore com uma dada raiz. Retorna a raiz da
// subárvore modifica.
struct Nodo* deletar_avl(struct Nodo* raiz, int valor)
{
    // PASSO 1: Deleção padrão de ABB
 
    if (raiz == NULL)
    {
        printf("\n\t\t\tValor nao encontrado!\n");
        return raiz;
    }
 
    // Se o valor a ser deletado é menor que o valor
    // na raiz, então a operação vai para a subárvore à esquerda
    if ( valor < raiz->dado )
    {
        raiz->esquerda = deletar_avl(raiz->esquerda, valor);
    }
 
    // Se o valor a ser deletado é maior que o valor
    // na raiz, então a operação vai para a subárvore à direita
    else if( valor > raiz->dado )
    {
        raiz->direita = deletar_avl(raiz->direita, valor);
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
            raiz->dado = temporario->dado;
 
            // Deleta o sucessor inordem
            raiz->direita = deletar_avl(raiz->direita, temporario->dado);
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

struct Nodo* busca_nodo(struct Nodo* raiz, int valor)
{
    if(raiz == NULL) //se a árvore estiver vazia ou o valor não for encontrado
    {
        return NULL;
    }
    else if(raiz->dado > valor) //quando o valor buscado é menor que o valor presente no nó atual
    {
        return busca_nodo(raiz->esquerda,valor);//busca na árvore continua pelo nó filho a esquerda do nó atual
    }
    else if(raiz->dado < valor) //quando o valor buscado é maior que o valor presente no nó atual
    {
        return busca_nodo(raiz->direita,valor);//busca na árvore continua pelo nó filho a direita do nó atual
    }
    else
    {
        return raiz; //quando o nó com o valor buscado é encontrado
    }
}

// Função para imprimir o percurso em ordem da árvore
// A função também imprime a altura de cada nó
void em_ordem(struct Nodo *raiz)
{
    if(raiz != NULL)
    {
        em_ordem(raiz->esquerda);
        printf("%3d", raiz->dado);
        em_ordem(raiz->direita);
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
    
    printf("%d\n", raiz->dado);
 
    // Processa nós a esquerda
    impressao_formato_arvore(raiz->esquerda, espaco);
}

int main() {

    unsigned int i;
    int item;
    struct Nodo *raiz = NULL;
    srand(time(NULL));

    puts("Os numeros a serem inseridos na arvore sao:");

    for(i = 1; i <= 20; ++i)
    {
        item = rand() % 100;
        printf("%3d", item);
        raiz = inserir_avl(raiz, item);
    }

    // percorrendo percurso em ordem
    puts("\n\nO percuro em-ordem:");
    em_ordem(raiz);

    printf("\n\n");
    
    printf("\n\t\t\tArvore AVL impressa em 2D\n");
    impressao_formato_arvore(raiz,0);

    int valor_busca;

    char opcao;
    
    printf("\nDeseja remover algum valor da arvore? Digite 'S' para sim ou 'N' para sair do programa: ");
    
    fflush(stdin);
    scanf("%c",&opcao);
    
    while((opcao == 'S') || (opcao == 's') || (raiz != NULL))
    {
        if(raiz == NULL)
        {
            printf("\n\t\t\tArvore AVL vazia!\n");
            break;
        }

        printf("\nDigite um valor para remover da arvore: ");
        scanf("%d",&valor_busca);

        if(busca_nodo(raiz,valor_busca) != NULL)
        {
            printf("\n\t\t\tValor encontrado na arvore AVL! Efetuando remocao!\n");
            
            raiz = deletar_avl(raiz,valor_busca);

            printf("\n\t\t\tArvore AVL apos a remocao de %d: \n",valor_busca);

            if(raiz != NULL)
            {
                impressao_formato_arvore(raiz,0);
            }
        }
        else
        {
            if(raiz == NULL)
            {
                printf("\n\t\t\tArvore AVL vazia!\n");
                break;
            }

            if(busca_nodo(raiz,valor_busca) == NULL)
            {
                printf("\n\t\t\tValor nao encontrado! Por favor escolha outro valor para remover que exista na arvore. Reimprimindo arvore\n");
                impressao_formato_arvore(raiz,0);
            }
        }

        printf("\nDeseja remover algum valor da arvore? Digite 'S' para sim ou 'N' para nao: ");
        fflush(stdin);
        scanf(" %c",&opcao);
    }
    
    printf("\nSaindo da aplicacao.\n");

    exit(0);

    return 0;
}
