#include <stdlib.h>
#include <stdio.h>

typedef struct Celula_DUP {
	int matricula;
	char *nome;	
	char *sobrenome;
	char *email;
	char *telefone;
	double salario;
	struct celula_DUP *proximo;
	struct celula_DUP *anterior;
}celula_DUP,*RegistroDUP;


typedef celula_DUP celula_DUP;
typedef celula_DUP *celula_DUP_ptr;

