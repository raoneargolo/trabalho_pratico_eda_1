#include <stdlib.h>
#include <stdio.h>

typedef struct CelulaAVL {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	long int *telefone;
	double salario;
	struct CelulaAVL *esq;
	struct CelulaAVL *dir;
}CelulaAVR,*RegistroAVL;
