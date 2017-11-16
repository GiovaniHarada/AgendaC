#include <stdio.h>

struct Ponto{
								int x; int y;
};

void gravaPonto(struct Ponto *p, int n){
								int i;

								FILE* f = fopen("ponto.txt", "w");
								for(i=0;i<n;i++){
																fprintf(f,"%d %d\n", p[i].x, p[i].y);
								}
								fclose(f);
}


struct Ponto * leiaPonto(int *n){
								int i=0;

								FILE* f = fopen("ponto.txt", "r");
								fscanf(f, "%d", n);
								struct Ponto* p = malloc(sizeof(struct Ponto) * (*n));

								for(i=0; i<*n;i++){
																fscanf(f,"%d", &(p[i].x));
																fscanf(f,"%d", &(p[i].y));
								}
							
								fclose(f);
								return p;
}

void gravaBinario(struct Ponto* p, int n){
								FILE* f = fopen("pontoBin.txt", "wb");
								fwrite(&n, sizeof(int), 1, f);
								fwrite(p, sizeof(struct Ponto), n, f);
								fclose(f);
}


struct Ponto* leiaBinario(int *n){
								FILE* f = fopen("pontoBin.txt", "rb");
								fread(n, sizeof(int), 1, f);
								struct Ponto* p = malloc(sizeof(struct Ponto) * (*n));
								fread(p, sizeof(struct Ponto), *n, f);
								fclose(f);
								return p;
}

int main(){
								int i;
								int n;
								struct Ponto * p = leiaPonto(&n);
								for(i=0; i<n;i++)
																printf("%d %d\n", p[i].x, p[i].y);
								gravaBinario(p, n);
					
								free(p);
								return 0;
}

