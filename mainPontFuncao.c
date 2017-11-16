#include <stdio.h>
#include <stdlib.h>

void troca(int* a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int crescente(int a, int b){
	return a < b;
}

void BubbleSort(int *v, int n, int (*devoTrocar)(int,int)){


	

	int i,j;
	for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++){
			if( devoTrocar(v[j+1], v[j]) == 1 )
		    	troca(v+j, v+j+1);
		}
	}
}

void imprime(int *v, int n){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", v[i]);
	}
	puts("");
}

int decrescente(int a, int b){
	return b < a;
}

int ordenaQuadrados(int a, int b){
	return crescente(a*a, b*b);
}

int main(int argc, char *argv[])
{
	int v[] = {1,5,-2,7,-5,4,3,9};
	BubbleSort(v, 8, crescente);
	imprime(v,8);
	BubbleSort(v, 8, decrescente);
	imprime(v,8);
	BubbleSort(v, 8, ordenaQuadrados);
	imprime(v,8);

	system("pause");	
	return 0;
}




void F1(int t){
	printf("oi %d\n", t);
}

void F2(){
	printf("oi \n");
}


int main2(int argc, char *argv[])
{
	F1(9999);
	void (*blabla)(int);
	blabla = F1;
	// blabla = F2; -> ERRADO, Protótipo não bate!!
	
	blabla(6);

	system("pause");
	return 0;
}










