#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void gravaCatalogo(Catalogo c){
	FILE* f = fopen("catalogo.cat", "wb");
	Produto *atual = c.v;
	
	fwrite(&(c.n), sizeof(int), 1, f);
	fwrite(atual, sizeof(Produto), c.n, f);
	
	fclose(f);
}

Catalogo leiaCatalogo(){
	FILE* f = fopen("catalogo.cat", "rb");
	
	int n;
	fread(&n, sizeof(int), 1, f);
	Catalogo c = criaCatalogo(2*n);
	fread(c.v, sizeof(Produto), n, f);
	c.n = n;
	fclose(f);
	
	return c;
}


void gravaCatalogoTxt(Catalogo c){
	FILE* f = fopen("catalogo.txt", "w");
	Produto *atual = c.v;

	int i;
	fprintf(f, "%d\n", c.n);
	for(i=0; i<c.n; i++){
		fprintf(f, "%s\n", c.v[i].nome);
		fprintf(f, "%s\n", c.v[i].descricao);
		fprintf(f, "%f\n", c.v[i].preco);
	}

	fclose(f);
}

Catalogo leiaCatalogoTxt(){
	FILE* f = fopen("catalogo.txt", "r");

	int n;
	
	fscanf(f, "%d\n", &n);
	
	Catalogo c = criaCatalogo(2*n);
	int i;
	for(i=0; i<n;i++){
		fgets(c.v[i].nome, 40, f);
		tiraLinha(c.v[i].nome);
		fgets(c.v[i].descricao, 100, f);
		tiraLinha(c.v[i].descricao);
		fscanf(f, "%f\n", &(c.v[i].preco));
		
	}
	c.n = n;
	fclose(f);

	return c;
}

int devoTrocarPorPreco(Produto a, Produto b){
    if( a.preco > b.preco  ){
		return 1;
	}
	return 0;
}


int devoTrocarPorNome(Produto a, Produto b){
    if( strcmp(a.nome, b.nome) > 0 ){
		return 1;
	}
	return 0;
}

int devoTrocarPorDesc(Produto a, Produto b){
    if( strcmp(a.descricao, b.descricao) > 0 ){
		return 1;
	}
	return 0;
}

int devoTrocarPorDescDec(Produto a, Produto b){
	return !devoTrocarPorDesc(a,b);
}

int Busca(Produto* v, int n, Produto oque){
	int i;
	for(i=0;i<n; i++){
		if( stricmp(v[i].nome, oque.nome) == 0){
			return i;
		}
	}
	return -1;
}




void BB(Produto* v, int n, int (*f)(Produto, Produto) ){

	
	
	int i,j;
	for(i=0; i<n-1; i++ ){
        for(j=0; j<n-1; j++ ){
			//if( v[j].preco > v[j+1].preco ){
            if( f(v[j], v[j+1]) > 0 ){
				Produto temp = v[j];
				v[j] = v[j+1];
				v[j+1] = temp;
			}
		}
	}

}



int menuBusca(Catalogo c){
	puts("Nome do produto");
	Produto p;
	fflush(stdin);
	fgets(p.nome, 40, stdin);
	tiraLinha(p.nome);
	int idx = Busca(c.v, c.n, p);
	if(idx == -1)
	    puts("Nao achei miseravi!");
	else{
		puts("Resultado:");
		printf("%s\n", c.v[idx].nome);
		printf("%s\n", c.v[idx].descricao);
		printf("%f\n", c.v[idx].preco);
	}
	
}
/*
void menuRemove(Catalogo c){

	int idx = menuBusca(c);
	remove(c, idx);
	

}

void menuImprime(Catalogo c){

	int idx = menuBusca(c);
	imprime(c, idx);


}*/

int main(int argc, char *argv[])
{
	Catalogo c = leiaCatalogoTxt();
	
	
	BB(c.v, c.n, devoTrocarPorDesc);
	imprimeCatalogo(c);
	puts("============");
	menuBusca(c);

 	//gravaCatalogo(c);
 	//gravaCatalogoTxt(c);
	destroiCatalogo(c);

	system("pause");
	return 0;
}

int main2(int argc, char *argv[])
{
	Catalogo c = criaCatalogo(100);

	leiaPrimeiros(&c, 2);
	imprimeCatalogo(c);
	gravaCatalogo(c);
	destroiCatalogo(c);

	system("pause");
	return 0;
}
