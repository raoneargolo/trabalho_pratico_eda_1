#include <stdlib.h>
#include <stdio.h>

typedef struct CelulaDUP {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	long int *telefone;
	double salario;
	struct CelulaDUP *proximo;
	struct CelulaDUP *anterior;
}CelulaDUP,*RegistroDUP;


