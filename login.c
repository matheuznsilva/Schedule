#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

struct element{		// Struct que define cada elemento da lista
	struct element *prev;		// Ponteiro que recebe a posi��o do n� anterior
	struct info DICE;		// Struct dados do tipo info
	struct element *next;		// Ponteiro que recebe a posi��o do n� posterior
};
typedef struct element Elem;		// Defini��o do tipo elemento

Login* creatLogin(){		// Fun��o de cria��o da lista
	Login* LO = (Login*) malloc(sizeof(Login));		// Aloca��o de memoria para o inicio da lista 
	if(LO != NULL){		// Verifica��o se a lista foi criada
		*LO= NULL;		// Caso tenha sido criada aponta para null
	}
	return LO;		// retorna lista
}

void freeLogin(Login *LO){		// Fun��o que Apaga a lista
	if(LO!= NULL){		// Confere se a lista existe
		Elem* NO;		// Declara��o de um ponteiro auxiliar
		while((*LO) != NULL){		// La�o de repeti��o para percorrer a lista
			NO = *LO;		// Ponteiro auxiliar recebe a posi��o atual da lista
			*LO = (*LO)->next;		// Ponteiro principal passa a apontar para o proximo elemento
			free(NO);		// Libera o ponteiro auxiliar
		}
		free(LO);		// Libera o ponteiro principal
		system("clear");
	}
}

int insertLogin(Login* LO, struct info al){		// Fun��o de inser��o ao final da lista 
	if(LO== NULL){		// Confere se a lista existe 
		return 0;		// Caso n�o exista retorna 0
	}
	List *LI = creatList();
	int I = 1;
	Elem* NO;		// Declara��o de um ponteiro auxiliar
	NO = (Elem*) malloc(sizeof(Elem));		// Aloca��o de memoria para o novo n� da lista
	if(NO == NULL){		// Confere se o n� foi criado 
		return 0;		// Caso n�o tenha criado retorna 0
	}
	
	NO->DICE = al;		// Preenchimento do no com o dado fornecido
	NO->DICE.LI = LI;
	NO->next = NULL;		// Ponteiro prox � apontado para null
	if((*LO) == NULL){		// Confere se � a primeira posi��o da lista
		NO->DICE.id = I;
		NO->prev = NULL;		// Se for o ponteiro ant vai receber null
		*LO = NO;		// e li recebe o n� atual
	} else{		// Caso n�o seja a primeira posi��o do vetor executa as instu��es abaixo
		Elem *AUX = *LO;		// Cria��o de um segundo ponteiro auxiliar para percorrer a lista
		while(AUX->next != NULL){		// La�o de repeti��o para percorrer a lista
			I = AUX->DICE.id+1;
			AUX = AUX->next;		// Segundo ponteiro auxiliar recebe a proxima posi��o da lista
		}
		NO->DICE.id = I+1;
		AUX->next = NO;			// Ponteiro prox do segundo ponteiro aponta para o primeiro n� auxiliar 
		NO->prev = AUX;		// Ponteiro ant do primeiro ponteiro aponta para o segundo ponteiro auxiliar
	}
	return 1;		// Caso tudo funcione retorna 1
}

void printLogin(Login *LO){		// Fun��o de impress�o da lista
	Elem *NO = *LO;		// Declara�a� de um ponteiro auxiliar
    printf("\n======= REGISTERED USERS =======");
	while(NO!=NULL){		// La�o de repeti��o para percorrer a lista
		printf("\nID: %d \nNAME: %s %s \nEMAIL: %s" /*\nPASSWORD: %d\n"*/, NO->DICE.id, NO->DICE.Name, NO->DICE.LastName, NO->DICE.email/*, NO->DICE.password*/);
		printf("\n================================");
		NO = NO->next;		// Ponteiro auxiliar recebendo a posi��o do proximo n� 
	}
	printf("\n");		// Quebra de linha
}


int findEmail(Login* LO, char email[N], struct info *al){
	if(LO== NULL){
		return 0;
	}
	Elem *NO = *LO;
	
	while(NO != NULL && strcmp(NO->DICE.email,email) != 0){
		NO = NO->next;
	}

	if(NO == NULL){
		return 0;
	} else {
		*al = NO->DICE;
		return 1;
	}
}

int removeLogin(Login* LO, int num){
	if(LO== NULL){
		return 0;
	}
	if((*LO) == NULL){
		return 0;
	}
	Elem *PREV, *NO = *LO;
	while(NO != NULL && NO->DICE.id != num){
		PREV = NO;
		NO = NO->next;
	}
	if(NO == NULL){
		return 0;
	}
	if(NO == *LO){
		*LO= NO->next;
	} else{
		PREV->next = NO->next;
	}
	free(NO);
	return 1;
}


void writeLogin(Login *LO){
    int COUNT=0;   

    Elem *NO = *LO;
    Elem *NO2 = *LO;

	while(NO != NULL){
    	NO = NO->next;
    	COUNT++;
    }

	struct info DATA[COUNT];	// "Vari�vel" do tipo struct aluno
	
	FILE *fp = fopen("tamanho.txt", "w");
	if(fp == NULL){
		printf("\n================================");
		printf(" -> ERRO NA LEITURA DE DADOS <-");
		printf("\n================================");
		exit(1);
	}
	fprintf(fp, "%d", COUNT);//(count, fp);	
	fclose(fp);

    FILE *arq = fopen("login.bin", "w+b");
    
    if(arq == NULL){
        printf("\n================================");
		printf(" -> ERRO NA LEITURA DE DADOS <-");
		printf("\n================================");
        exit(1);
    }

    for(int I=0; I<COUNT; I++){
    	DATA[I].id = NO2->DICE.id;
    	strcpy(DATA[I].Name , NO2->DICE.Name);
    	strcpy(DATA[I].LastName , NO2->DICE.LastName);
    	strcpy(DATA[I].email , NO2->DICE.email);
    	//strcpy(DATA[I].password , NO2->DICE.password);
    	DATA[I].password = NO2->DICE.password;
    	NO2 = NO2->next;
    }

    fwrite(DATA, sizeof(struct info), COUNT, arq);

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

}

void loadingSchedule(Login* LO){
    if(LO == NULL){
		return 0;
	}
	Elem *NO = *LO;

	while (NO != NULL){
		loadingData(NO->DICE.LI, NO->DICE.email);
		NO = NO->next;
	}
	
}*/