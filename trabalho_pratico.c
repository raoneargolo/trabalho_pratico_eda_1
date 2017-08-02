#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define tamanho_caracteres 100
#define tamanho_caracteres_linha 1000

void quebra_string(char *string_recebida);

void inserir_arvore(tipo_nodo nome_nodo_arvore, int matricula, char nome, char sobrenome, char email, char telefone, double salario);
void inserir_lista(tipo_nodo nome_nodo_lista, int matricula, char nome, char sobrenome, char email, char telefone, double salario);

int main() {	

	FILE *arquivo; //variável para conter o arquivo csv a ser lido
	char linha_atual [tamanho_caracteres_linha]; //ponteiro de caracter (string) para conter a linha atual lida do arquivo

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
			quebra_string(linha_atual); //função para "quebrar" string
		}
		
		qt_linhas_lidas++;
	}

	fclose(arquivo); //função para fechar o arquivo recebido e lido

	return 0;
}

//a função abaixo recebe a linha do arquivo csv e a quebra em várias strings a partir do delimitador ","
//para cada string gerada pela quebra, a mesma ocupa uma variável e faz procedimentos diferentes
void quebra_string(char *string_recebida)
{
	int matricula; //variável que armazena o dado da primeira coluna do arquivo csv: o número de matrícula
	char nome[tamanho_caracteres]; //varável que armazena o dado da segunda coluna do arquivo csv: o nome do empregado
	char sobrenome[tamanho_caracteres];//variável que armazena o dado da terceira coluna do arquivo csv: sobrenome do empregado
	char email[tamanho_caracteres]; //variável que armazena o dado da quarta coluna do arquivo csv: e-mail do empregado
	char telefone[tamanho_caracteres]; //variável que armazena o dado da quinta coluna do arquivo csv: telefone do empregado
	double salario; //variável que armazena o dado da sexta coluna do arquivo csv: salario do empregado

	char *string_recebida_copia = strdup(string_recebida); //duplicando para uma string temporária a string recebida na função
	
	char *string_cortada; //ponteiro de caracter (string) para as palavras quebradas

	string_cortada = strtok(string_recebida_copia, ","); //função para quebrar a string pela primeira vez
	
	matricula=atoi(string_cortada); //a função atoi converte de string para inteiro
	
	printf("Numero de Matricula: %d\n", matricula); //exibir primeira palavra da string cortada
	
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
				strcpy(nome,string_cortada); //função que copia o conteúdo da string cortada para a variável nome
				printf("Nome: %s\n", nome);
			}
			if(contador_variaveis_alocacao == 3) //Condição para colocar a string correta na variável sobrenome
			{
				strcpy(sobrenome,string_cortada); //função que copia o conteúdo da string cortada para a variável sobrenome
				printf("sobrenome: %s\n", sobrenome);
			}
			if(contador_variaveis_alocacao == 4) //Condição para colocar a string correta na variável e-mail
			{
				strcpy(email,string_cortada); //função que copia o conteúdo da string cortada para a variável e-mail
				printf("E-mail: %s\n", email);	
			}
			if(contador_variaveis_alocacao == 5) //Condição para colocar a string correta na variável telefone
			{
				strcpy(telefone,string_cortada); //função que copia o conteúdo da string cortada para a variável telefone
				printf("Telefone: %s\n", telefone);
			}
			if(contador_variaveis_alocacao == 6) //Condição para colocar a string correta na variável salário
			{
				salario=strtod(string_cortada,NULL); //função que converte o conteúdo da string cortada para double 
													 //e o armazena na variável salário
				printf("Salario: %.2lf\n", salario);
			}

			inserir_arvore(tipo_nodo nome_nodo_arvore, int matricula, char nome, char sobrenome, char email, char telefone, double salario);
			inserir_lista(tipo_nodo nome_nodo_lista, int matricula, char nome, char sobrenome, char email, char telefone, double salario);
		}
	}
	
	printf("\n");
}

