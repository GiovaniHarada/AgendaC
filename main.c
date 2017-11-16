#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _contato{
	char nome[128];
	char email[64];
	char telefone[16];
};
typedef struct _contato Contato;

struct _agenda{
	Contato* v;
	int n;
	int max;	
};
typedef struct _agenda Agenda;

Agenda criaAgenda(int n){
	Agenda a;
	a.n = 0;
	a.v = malloc(sizeof(Contato) * n);
	a.max = n;
	return a;
}

void tiraLinha(char *str){
	int i=0;
	while(str[i] != '\0' && str[i] != '\n' )
	    i++;
	str[i] = '\0';
}

void insereContato(Agenda* a){
	fflush(stdin);
	if( a->n >= a->max ){
		puts("PAN! Memoria Cheia!");
		return;
	}
	puts("Nome");
	fgets( a->v[a->n].nome, 128, stdin );
	tiraLinha(a->v[a->n].nome);
	puts("Email");
	fgets( a->v[a->n].email, 64, stdin );
	tiraLinha(a->v[a->n].email);
	puts("Telefone");
	fgets( a->v[a->n].telefone, 16, stdin );	
	tiraLinha(a->v[a->n].telefone);;
	a->n++;
}
void gravaAgenda(Agenda a){
	FILE* f = fopen("Agenda.dat", "wb");
	Contato *atual = a.v;
	
	fwrite(&(a.n), sizeof(int), 1, f);
	fwrite(atual, sizeof(Contato), a.n, f);
	
	fclose(f);
}

int main(int argc, char *argv[]){
	Agenda ag = criaAgenda(99);
	insereContato(&ag);
	gravaAgenda(ag);
	
	system("pause");
}
