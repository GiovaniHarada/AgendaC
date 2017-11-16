#include <stdio.h>
#include <stdlib.h>

struct Aluno{
	char nome[50];
	float p1;
	float p2;
	float p3;
};

struct Aluno criaAluno(){
	struct Aluno a;
	printf("Nome:\n");
	fflush(stdin);
	gets(a.nome);
	printf("p1:\n");
	scanf("%f", &(a.p1));
	printf("p2:\n");
	scanf("%f", &(a.p2));
	a.p3 = 0;
	return a;
}


void medias(struct Aluno* v, int n, float *m){
	int i;
	for(i=0;i<n;i++){
		m[i] = 0.4*v[i].p1 + 0.6*v[i].p2;
	}
}

void f(){
    	FILE* f;
	char str[100];
	f = fopen("C:/Temp/blablabla.txt", "ab");
	int i;
	for(i=0; i<5; i++)
		fprintf(f, "o numero eh: %d\n", i);

	/*while(fscanf(f, "%s", str) == 1){
		printf("%s\n", str);
	}*/
	fclose(f);
}

int main(int argc, char *argv[]){
	int i=0;
	char str[5];
	FILE* f = fopen("C:/Temp/blablabla.txt", "rb");
	while( fgets(str, 5, f) != NULL)
		printf("%s", str);
	fclose(f);
	system("pause");
}


int main2(int argc, char *argv[])
{
	int n = 3;
	float m[3];
	struct Aluno *v = malloc(sizeof(struct Aluno) * n);
	
	int i;
	for(i=0; i< n; i++)
		v[i] = criaAluno();

    medias(v, n, m);
	for(i=0; i< n; i++){
		printf("aluno %d media: %f\n", i+1, m[i]);
	}
	
	free(v);
	system("pause");	
	return 0;
}
