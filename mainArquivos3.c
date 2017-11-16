#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


struct Circulo{
	int x;
	int y;
	int r;
	char cor[8];
};


void geraDadosAleatorios(){
	srand(time(NULL));
	char *cores[10]={
			"#FF0000",
			"#00FF00",
			"#0000FF",
			"#000055",
			"#005500",
			"#550000",
			"#FF00FF",
			"#00FFFF",
			"#FFFF00",
			"#0F0F0F",
		};
	//escreveHTML("pagina.html");

	FILE *f = fopen("dados.txt", "w");
	int i;
	fprintf(f,"%d\n", 1000);
	for(i=0;i<1000;i++){
		fprintf(f,"%d\t%d\t%d\t%s\n",
			rand() % 1000,
			rand() % 1000,
			rand() % 30,
			cores[rand()%10]);
	}
	fclose(f);
}


void inicioHTML(char *str){
	strcpy(str, "<!DOCTYPE html> \
		<html>          \
		<body>          \
		<svg width=\"1000\" height=\"1000\">");
}

void fimHTML(char *str){
	strcpy(str, "</svg>\
					</body>\
					</html>");
}

void conteudoHTML(char *str, struct Circulo* c, int n){
	str[0]=0;
	int i;
	for(i=0;i<n;i++){
		sprintf(str, "%s<circle cx=\"%d\" cy=\"%d\"  \
					r=\"%d\" stroke=\"black\" \
					stroke-width=\"2\" fill=\"%s\" />",
					str,
					c[i].x,
					c[i].y,
					c[i].r,
					c[i].cor
					);
	}
	
}

void escreveHTML(char * arquivo, struct Circulo *c, int n){

	


	FILE* f = fopen(arquivo, "w");
	char str[4000];
	inicioHTML(str);
	fprintf(f, "%s\n", str);
	
	int i;
	for(i=0;i<n;i++){
		conteudoHTML(str, c+i, 1);
		fprintf(f, "%s\n", str);
	}
	
	fimHTML(str);
	fprintf(f, "%s\n", str);

	fclose(f);
}

void leiaTexto(char *arquivo, struct Circulo *c, int n){
	int i;
	int x,y,r;
	char cor[15];
	
	
	FILE* f = fopen(arquivo, "r");
	for(i=0;i<n;i++){
		fscanf(f, "%d", &x);
		fscanf(f, "%d", &y);
		fscanf(f, "%d", &r);
		fscanf(f, "%s", cor);
		c[i].x = x;
		c[i].y = y;
		c[i].r = r;
		strcpy( c[i].cor, cor);
	}
	fclose(f);

}

int contaLinhas(char* arquivo){
	FILE* f = fopen(arquivo, "r");
	char str[10000];
	int l=0;
	while( fgets(str, 10000, f) != NULL )
		l++;

	return l;
}

int main(int argc, char *argv[]) 
{
	int n = contaLinhas("dados.txt");
	struct Circulo *c = malloc(sizeof(struct Circulo) *n);
	leiaTexto("dados.txt", c, n);
	escreveHTML("pagina.html", c, n);
	free(c);
	return 0;
}
