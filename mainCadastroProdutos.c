#include <stdio.h>
#include <stdlib.h>

struct _produto{
	char nome[40];
	char descricao[100];
	float preco;
};
typedef struct _produto Produto;

struct _catalogo{
	Produto* v;
	int n;
	int maximo;
};
typedef struct _catalogo Catalogo;

void imprimeProduto(const Produto* p){
		printf("Nome: %s\n", p->nome );
		printf("Desc: %s\n", p->descricao);
		printf("Prec: %f\n", p->preco);
}


void imprimeCatalogo(Catalogo c){
	int i;
	for(i=0;i < c.n;i++){
		imprimeProduto( c.v + i  );
	}
}


Catalogo criaCatalogo(int n){
	Catalogo c;
	c.n = 0;
	c.v = malloc(sizeof(Produto) * n);
	c.maximo = n;
	return c;
}

void destroiCatalogo(Catalogo c){
	free(c.v);
}


void tiraLinha(char *str){
	int i=0;
	while(str[i] != '\0' && str[i] != '\n' )
	    i++;
	str[i] = '\0';
}

void insereCatalogo(Catalogo* c){
	fflush(stdin);
	if( c->n >= c->maximo ){
		puts("PAN! Memoria Cheia!");
		return;
	}
	puts("nome");
	fgets( c->v[c->n].nome, 40, stdin );
	tiraLinha(c->v[c->n].nome);
	puts("desc");
	fgets( c->v[c->n].descricao, 100, stdin );
	tiraLinha(c->v[c->n].descricao);
	puts("preco");
	scanf("%f", &(c->v[c->n].preco) );
	c->n++;
}

void leiaPrimeiros(Catalogo* c, int n){

	int i;
	for(i=0;i<n;i++){
		insereCatalogo(c);
	}
}

int main(int argc, char *argv[]) 
{
	Catalogo c = criaCatalogo(100);

	leiaPrimeiros(&c, 2);
	imprimeCatalogo(c);
	destroiCatalogo(c);

	system("pause");	
	return 0;
}
