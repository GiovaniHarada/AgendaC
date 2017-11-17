//  Created by Victoria Gonzales Lopes on 28/10/2017.
//  Copyright © 2017 Victoria Gonzales Lopes. All rights reserved.

#include <stdio.h>
#include <string.h>

typedef struct {
    char Nome[50];
    char Endereco[100];
    char Telefone[12];
    char Email[50];
}contato;

void imprimeContatos(contato *pessoa, int quantidade) {
	int i=0;
	for (i=0; i<quantidade; i++) {
		printf("Nome: %s | Endereco: %s | Telefone: %s | Email: %s\n", pessoa[i].Nome, pessoa[i].Endereco, pessoa[i].Telefone, pessoa[i].Email);
	}
}

void salvaArquivo(contato *pessoa, FILE *arquivo, int *quantidade) {
    arquivo = fopen("agenda.txt", "a+");
    fprintf(arquivo, "%s\n%s\n%s\n%s\n", pessoa->Nome, pessoa->Endereco, pessoa->Telefone, pessoa->Email);
    fclose(arquivo);
    *quantidade = *quantidade + 1;
}

void consultaContato (contato *pessoa, int *quantidade) {
	int i = 0;
	FILE *arquivo;
	arquivo = fopen("agenda.txt", "r+");
	if(arquivo == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else {
		while (fgets(pessoa[i].Nome, sizeof(pessoa[i].Nome), arquivo) != NULL){
			//fgets(pessoa->Nome, sizeof(pessoa->Nome), arquivo);
			fgets(pessoa[i].Endereco, sizeof(pessoa[i].Endereco), arquivo);
			fgets(pessoa[i].Telefone, sizeof(pessoa[i].Telefone), arquivo);
			fgets(pessoa[i].Email, sizeof(pessoa[i].Email), arquivo);


			/*printf("\n %d Nome: %s", i+1, pessoa[i].Nome);
			printf("   Endereco: %s", pessoa[i].Endereco);
			printf("   Telefone: %s", pessoa[i].Telefone);
			printf("   Email: %s", pessoa[i].Email); */

  			i++;

		}
	}
	fclose(arquivo);
}

void criaContato(contato *pessoa) {
	system("cls");
	fflush(stdin);
    printf("Digite o nome do novo contato: ");
    gets(pessoa->Nome);
    fflush(stdin);
    printf("Digite o endereco do novo contato: ");
    gets(pessoa->Endereco);
    fflush(stdin);
    printf("Digite o telefone do novo contato: ");
    scanf("%s", pessoa->Telefone);
    fflush(stdin);
    printf("Digite o e-mail do novo contato: ");
    scanf("%s", pessoa->Email);
    fflush(stdin);
}

void excluiContato (contato *pessoa, int quantidade) {
	consultaContato(pessoa, &quantidade);
	fflush(stdin);
	int i = 0;
	char Nome[50];
	printf("Qual o nome do contato que deseja excluir? ");
	gets(Nome);
		printf("%s == %s", Nome, pessoa[i].Nome);
	while (strcmp(Nome,pessoa[i].Nome) != 0 && i<quantidade){
		printf("%s %s", Nome, pessoa[i].Nome);
		i = i+1;
	}
	printf("Entrou");
	for (i; i<quantidade; i++){
		pessoa[i] = pessoa[i+1];
	}
	imprimeContatos(pessoa, quantidade);
}
int main(int argc, const char * argv[]) {
    printf("Agenda de Contatos \n\n");
	contato vetContatos[100];
    int opc, quantidade = 0;
	char Letra[1];
	contato pessoa;
    FILE *arquivo = NULL;
    while (1) {
        printf("\nMenu de Opcoes: \n\n");
        printf("1 - Incluir Contato\n");
        printf("2 - Alterar Contato\n");
        printf("3 - Consultar Contatos\n");
        printf("4 - Excluir Contato\n");
        printf("5 - Sair da Agenda\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opc);
        if (opc == 1) {
            criaContato(&pessoa);
            salvaArquivo(&pessoa, arquivo, &quantidade);
        }
        else if (opc == 2) {
            // alteraContato(&pessoa);
        }
        else if (opc == 3) {
			printf("1 - Buscar contato por nome: ");
			printf("2 - Buscar contato por letra: ");
			printf("3 - Exibir todos os contatos: ");
			scanf("%d", &opc);
			/*if (opc == 1) {
				printf("Digite o nome do contato que deseja buscar: ");
				scanf("%s", &Nome);
			}
			else if (opc == 2) {
                printf("Digite a letra que deseja buscar: ");
				scanf("%s", &Letra);
			}
			else if (opc == 3) {
            	consultaContato(vetContatos, &quantidade); */
        	}
        else if (opc == 4) {
            excluiContato(vetContatos, quantidade);
        }
        else if (opc == 5) {
            return 0;
        }
        else {
            printf("Opcao Invalida, tente novamente \n");
        }
    }
    return 0;
}
