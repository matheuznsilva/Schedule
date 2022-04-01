#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

struct elemento{		// Struct que define cada elemento da lista
	struct elemento *ant;		// Ponteiro que recebe a posi��o do n� anterior
	struct info dados;		// Struct dados do tipo info
	struct elemento *prox;		// Ponteiro que recebe a posi��o do n� posterior
};
typedef struct elemento Elem;		// Defini��o do tipo elemento

Login* cria_login(){		// Fun��o de cria��o da lista
	Login* LO = (Login*) malloc(sizeof(Login));		// Aloca��o de memoria para o inicio da lista 
	if(LO != NULL){		// Verifica��o se a lista foi criada
		*LO= NULL;		// Caso tenha sido criada aponta para null
	}
	
	return LO;		// retorna lista
}

void libera_logins(Login *LO){		// Fun��o que Apaga a lista
	if(LO!= NULL){		// Confere se a lista existe
		Elem* no;		// Declara��o de um ponteiro auxiliar
		while((*LO) != NULL){		// La�o de repeti��o para percorrer a lista
			no = *LO;		// Ponteiro auxiliar recebe a posi��o atual da lista
			*LO= (*LO)->prox;		// Ponteiro principal passa a apontar para o proximo elemento
			free(no);		// Libera o ponteiro auxiliar
		}
		free(LO);		// Libera o ponteiro principal
		printf("\n\t\tFIM DA EXECUCAO\n");		// Aviso que a lista foi apagada
		sleep(1);
		system("clear");
	}
}

int insere_login(Login* LO, struct info al){		// Fun��o de inser��o ao final da lista 
	if(LO== NULL){		// Confere se a lista existe 
		return 0;		// Caso n�o exista retorna 0
	}
	Lista *LI = cria_lista();
	int i = 1;
	Elem* no;		// Declara��o de um ponteiro auxiliar
	no = (Elem*) malloc(sizeof(Elem));		// Aloca��o de memoria para o novo n� da lista
	if(no == NULL){		// Confere se o n� foi criado 
		return 0;		// Caso n�o tenha criado retorna 0
	}
	
	no->dados = al;		// Preenchimento do no com o dado fornecido
	no->dados.LI = LI;
	no->prox = NULL;		// Ponteiro prox � apontado para null
	if((*LO) == NULL){		// Confere se � a primeira posi��o da lista
		no->dados.id = i;
		no->ant = NULL;		// Se for o ponteiro ant vai receber null
		*LO = no;		// e li recebe o n� atual
	} else{		// Caso n�o seja a primeira posi��o do vetor executa as instu��es abaixo
		Elem *aux = *LO;		// Cria��o de um segundo ponteiro auxiliar para percorrer a lista
		while(aux->prox != NULL){		// La�o de repeti��o para percorrer a lista
			i = aux->dados.id+1;
			aux = aux->prox;		// Segundo ponteiro auxiliar recebe a proxima posi��o da lista
		}
		no->dados.id = i+1;
		aux->prox = no;			// Ponteiro prox do segundo ponteiro aponta para o primeiro n� auxiliar 
		no->ant = aux;		// Ponteiro ant do primeiro ponteiro aponta para o segundo ponteiro auxiliar
	}
	return 1;		// Caso tudo funcione retorna 1
}

void imprime_Logins(Login *LO){		// Fun��o de impress�o da lista
	Elem *no = *LO;		// Declara�a� de um ponteiro auxiliar
	
	while(no!=NULL){		// La�o de repeti��o para percorrer a lista
		printf("\nID: %d \nNAME: %s %s \nEMAIL: %s \nPASSWORD: %d\n", no->dados.id, no->dados.Name, no->dados.LastName, no->dados.email, no->dados.password);
		no = no->prox;		// Ponteiro auxiliar recebendo a posi��o do proximo n� 
	}
	
	printf("\n");		// Quebra de linha
}


int busca_email(Login* LO, char email[N], struct info *al){
	if(LO== NULL){
		return 0;
	}
	Elem *no = *LO;
	
	while(no != NULL && strcmp(no->dados.email,email) != 0){
		no = no->prox;
	}

	if(no == NULL){
		return 0;
	} else {
		*al = no->dados;
		return 1;
	}
}

int remove_login(Login* LO, int num){
	if(LO== NULL){
		return 0;
	}
	if((*LO) == NULL){
		return 0;
	}
	Elem *ant, *no = *LO;
	while(no != NULL && no->dados.id != num){
		ant = no;
		no = no->prox;
	}
	if(no == NULL){
		return 0;
	}
	if(no == *LO){
		*LO= no->prox;
	} else{
		ant->prox = no->prox;
	}
	free(no);
	return 1;
}


void EscreverLogins(Login *LO){
    int i=0, count=0;   

    Elem *NO = *LO;
    Elem *NO2 = *LO;

	while(NO != NULL){
    	NO = NO->prox;
    	count++;
    }

	struct info DADOS[count];	// "Vari�vel" do tipo struct aluno
	
	FILE *fp = fopen("tamanho.txt", "w");
	if(fp == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}
	fprintf(fp, "%d", count);//(count, fp);	
	fclose(fp);

    FILE *arq = fopen("login.bin", "w+b");
    
    if(arq == NULL){
        printf("ERRO NA LEITURA DE DADOS");
        exit(1);
    }

    for(int i=0; i<count; i++){
    	DADOS[i].id = NO2->dados.id;
    	strcpy(DADOS[i].Name , NO2->dados.Name);
    	strcpy(DADOS[i].LastName , NO2->dados.LastName);
    	strcpy(DADOS[i].email , NO2->dados.email);
    	//strcpy(DADOS[i].password , NO2->dados.password);
    	DADOS[i].password = NO2->dados.password;
    	NO2 = NO2->prox;
    }

    fwrite(DADOS, sizeof(struct info), count, arq);

	fclose(arq);
}

/*void loadingData(Lista* LI, char email[N]){
	strcat(email, ".bin");
	FILE *arq = fopen(email, "rb");
	if(arq == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}
	Elem ;

	fread(LI.DATA , sizeof(struct info), count, arq);

}*/

void loadingSchedule(Login* LO){
    if(LO == NULL){
		return 0;
	}
	Elem *no = *LO;

	while (no != NULL){
		loadingData(no->dados.LI, no->dados.email);
		no = no->prox;
	}
	
}