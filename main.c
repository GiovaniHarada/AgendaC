#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _contato{
	char nome[128];
	char endereco[128];
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
		printf("Memoria Cheia! n: %d - max %d", a->n, a->max);
		return;
	}
	puts("Nome: ");
	fgets( a->v[a->n].nome, 128, stdin );
	tiraLinha(a->v[a->n].nome);
	puts("Endereço: ");
	fgets( a->v[a->n].endereco, 128, stdin );
	tiraLinha(a->v[a->n].endereco);
	puts("Email: ");
	fgets( a->v[a->n].email, 64, stdin );
	tiraLinha(a->v[a->n].email);
	puts("Telefone: ");
	fgets( a->v[a->n].telefone, 16, stdin );	
	tiraLinha(a->v[a->n].telefone);;
	a->n++;
	printf("\n\n Contato inserido com sucesso !\n");
}
void gravaAgenda(Agenda a){
	FILE* f = fopen("Agenda.dat", "wb");
	Contato *atual = a.v;
	fwrite(&(a.n), sizeof(int), 1, f);
	fwrite(atual, sizeof(Contato), a.n, f);
	
	fclose(f);
}
Agenda leiaAgenda(){
	FILE* f = fopen("agenda.dat", "rb");	
	int n;
	fread(&n, sizeof(int), 1, f);
	Agenda ag = criaAgenda(2*(n+1));
	fread(ag.v, sizeof(Contato), n, f);
	ag.n = n;
	fclose(f);
	
	return ag;
}
int tamanhoAgenda(){
	FILE* f = fopen("agenda.dat", "rb");	
	int n = 0;
	fread(&n, sizeof(int), 1, f);
	fclose(f);
	return n;
}
void imprimeContato(const Contato* c){
	printf("Nome: %s | ", c->nome );
	printf("Email: %s | ", c->email);
	printf("Endereco: %s | ", c->endereco);
	printf("Telefone: %s\n", c->telefone);
}
void imprimeAgenda(Agenda a){
	int i;
	for(i=0;i < a.n;i++){
		printf("%d | ", i);
		imprimeContato( a.v + i  );
	}
	printf("\n\n");
}
int buscar(Contato* cts, int n, Contato procurado){
	int i;
	for(i=0;i<n; i++){
		if( stricmp(cts[i].nome, procurado.nome) == 0){
			return i;
		}
	}
	return -1;
}
int * buscarLetra(Contato* cts, int n, char letra){
	int * ids = malloc(sizeof(int)*n);
	int i;
	for(i = 0; i < n; i++)
		ids[i]= -1;
	
	for(i=0;i<n; i++){
		if(tolower(cts[i].nome[0])== tolower(letra)){
			ids[i] = i;
		}
	}
	return ids;
}
int buscarContato(Agenda ag){
	puts("Nome");
	Contato c;
	fflush(stdin);
	fgets(c.nome, 40, stdin);
	tiraLinha(c.nome);
	int idBuscado = buscar(ag.v, ag.n, c);
	if(idBuscado == -1)
	    printf("Contato Não Encontrado");
	else{
		puts("Resultado:");
		printf("Nome: %s | ", ag.v[idBuscado].nome);
		printf("Email: %s | ", ag.v[idBuscado].email);
		printf("Endereco: %s | ",  ag.v[idBuscado].endereco);
		printf("Telefone: %s\n\n\n", ag.v[idBuscado].telefone);
		
	}	
}
int buscarContatoLetra(Agenda ag){
	printf("Procurar contatos que comecam com a letra : ");
	Contato c;
	char letra;
	scanf(" %c", &letra);
	int* idBuscados = buscarLetra(ag.v, ag.n, letra);
	int i;
	int encontrados = 0;
	for(i = 0; i < ag.n; i++){
		if(idBuscados[i] > -1){
			printf("\n%d-", idBuscados[i]);
			printf("Nome: %s | ", ag.v[i].nome);
			printf("Email: %s | ", ag.v[i].email);
			printf("Endereco: %s | ",  ag.v[i].endereco);
			printf("Telefone: %s\n", ag.v[i].telefone);	
			encontrados++;
		}
	}
	printf("\n");
	if(encontrados == 0)
		printf("Nenhum contato encontrado ;( \n");
	
}
void alteraContato(Agenda* a){
	Contato c;
	puts("Nome do contato que deseja modificar: ");
	fflush(stdin);
	fgets(c.nome, 40, stdin);
	tiraLinha(c.nome);
	int idModificar = buscar(a->v, a->n, c);
	if(idModificar == -1 )
		printf("Contato Não Encontrado");
	else{
		fflush(stdin);
		char nInput[128];
		printf("Nome(%s): \n", a->v[idModificar].nome);
		fgets(nInput, 128, stdin );
		if(!strcmp(nInput, "") == 0)
			strcpy(a->v[idModificar].nome, nInput);		
		tiraLinha(a->v[idModificar].nome);	
		
		char eInput[128];
		printf("Endereco(%s): \n", a->v[idModificar].endereco);
		fgets( eInput, 128, stdin );
		if(!strcmp(eInput, "") == 0)
			strcpy(a->v[idModificar].endereco, eInput);
		tiraLinha(a->v[idModificar].endereco);		
		
		char mInput[64];
		printf("Email(%s): \n", a->v[idModificar].email);
		fgets(mInput, 64, stdin );
		if(!strcmp(eInput, "") == 0)
			strcpy(a->v[idModificar].email, mInput);
		tiraLinha(a->v[idModificar].email);
		
		char tInput[16];
		printf("Telefone(%s): \n", a->v[idModificar].telefone);
		fgets( tInput, 16, stdin );	
		if(!strcmp(tInput, "") == 0)
			strcpy(a->v[idModificar].telefone, tInput);
		tiraLinha(a->v[idModificar].telefone);;
		printf("\n\nContato atualizado !!");
	}
	
}
void excluiContato(Agenda* a){
	Contato c;
	puts("Nome do contato que deseja excluir: ");
	fflush(stdin);
	fgets(c.nome, 40, stdin);
	tiraLinha(c.nome);
	int idModificar = buscar(a->v, a->n, c);
	if(idModificar == -1 )
		printf("Contato Nao Encontrado");
	else{
		printf("Deseja realmente excluir o contato : %s ?", a->v[idModificar].nome);		
		char opt;
		printf("  S ou N \n");
		scanf("%c", &opt);
		if(opt == 's' || opt == 'S'){
			a->n--;
			int c;
			for(c  = idModificar; c < a->n; c++ ){
				a->v[c] = a->v[c+1];
			}
			printf("Apagado com sucesso !!\n");
		}		
	}	
}
int ordenaNome(Contato a, Contato b){
    if( strcmp(a.nome, b.nome) > 0 ){
		return 1;
	}
	return 0;
}
void BB(Contato* c, int n, int (*f)(Contato, Contato) ){	
	int i,j;
	for(i=0; i<n-1; i++ ){
        for(j=0; j<n-1; j++ ){
			//if( v[j].preco > v[j+1].preco ){
            if( f(c[j], c[j+1]) > 0 ){
				Contato temp = c[j];
				c[j] = c[j+1];
				c[j+1] = temp;
			}
		}
	}
}
void imprimeAgendaOrdenada(Agenda a){
	BB(a.v, a.n, ordenaNome);
	int i;
	for(i=0;i < a.n;i++){
		printf("%d | ", i);
		imprimeContato( a.v + i  );
	}
	printf("\n\n");
}
void limpaTela(){
	system("cls");
	printf("+---------------------------------------+\n");
	printf("|------------SUPER AGENDA---------------|\n");
	printf("|--------------v1.0---------------------|\n");
	printf("+---------------------------------------+\n");
	printf("\n\n");
}
int main(int argc, char *argv[]){
	int sair = 0;
	int opc = 0;
	if(tamanhoAgenda() == 0){
		Agenda ag = criaAgenda(10);
		gravaAgenda(ag);
	}
	
	
	do{
		limpaTela();		
		printf("+--------------------- MENU -----------------------+\n");
		printf("| 1 -> Adicionar contato                           |\n");
		printf("| 2 -> Alterar contato                             |\n");
		printf("| 3 -> Listar todos contatos                       |\n");
		printf("| 4 -> Listar todos contatos em ordem alfabetica   |\n");
		printf("| 5 -> Buscar contato                              |\n");	
		printf("| 6 -> Buscar Contatos por letra                   |\n");	
		printf("| 7 -> Excluir contato                             |\n");		
		printf("+--------------------------------------------------+\n");	
		printf("| 9 -> Sair                                        |\n");
		printf("+--------------------------------------------------+\n\n");
		printf("->");
		scanf("%d", &opc);
		switch (opc){
			case 1:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda() + 10);
				ag = leiaAgenda();
				insereContato(&ag);
				gravaAgenda(ag);
				system("pause");
				break;
			}
			case 2:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda());
				ag = leiaAgenda();
				alteraContato(&ag);
				gravaAgenda(ag);
				system("pause");
				break;
			}
			case 3:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda() + 10);
				ag = leiaAgenda();
				imprimeAgenda(ag);
				system("pause");
				break;
			}
			case 4:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda() + 10);
				ag = leiaAgenda();				
				imprimeAgendaOrdenada(ag);
				system("pause");
				break;
			}
			case 5:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda() + 10);
				ag = leiaAgenda();
				buscarContato(ag);
				system("pause");
				break;
			}
			case 6:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda() + 10);
				ag = leiaAgenda();
				buscarContatoLetra(ag);
				system("pause");
				break;
			}
			case 7:{
				limpaTela();
				Agenda ag = criaAgenda(tamanhoAgenda());
				ag = leiaAgenda();
				excluiContato(&ag);
				gravaAgenda(ag);
				system("pause");
				break;
			}
			case 9:{
				return;
				break;
			}
			default:
				printf("Opcao Invalidade, tente novamente\n");
				system("pause");
				break;
				
		}
	}while(sair == 0);
	
	
	
	//Agenda ag = criaAgenda(99);
	//ag = leiaAgenda();
	//gravaAgenda(ag);	
	//imprimeAgenda(ag);
	
	system("pause");
}
