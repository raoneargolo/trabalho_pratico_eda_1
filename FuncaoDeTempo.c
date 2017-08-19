
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ITEMS 1000

int main(int argc, char **argv)
{
	clock_t start, end;	// declaracoes importantes
	double cpu_time_used; // declaracoes imporantes
	int i,item; // declacao so para o for que estou usando ( nao importante)
	
	//INCICIO DA OPERACAO ( NO CASO IMPRESSAO DE X's ELEMENTOS)
	
	start = clock(); //inicio da contagem 
	
	for ( i = 0; i < ITEMS; ++i ) {
        item = rand() % 100;
        printf( "%d,", item );
    }
	 end = clock(); // final da contagem


	// CALCULO DO TEMPO
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("\n momento de inicio %f (s) \n",((double)start/CLOCKS_PER_SEC));// exibe o momento do inicio t=0
    printf("\n momento de fim %f\n (s) ",((double)end/CLOCKS_PER_SEC)); //exibe o hora final
    printf("\n tempo total depois da importacao %f (s) \n",cpu_time_used); // exibe a diferenca do (inicio - final )
	return 0;
}

