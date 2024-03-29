#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

struct element{		// Struct que define cada elemento da lista
	struct element *prev;
	struct info DICE;		// Struct dados do tipo info
	struct element *next;
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
			NO = *LO;
			*LO = (*LO)->next;		// Ponteiro principal passa a apontar para o proximo elemento
			free(NO);		// Libera o ponteiro auxiliar
		}
		free(LO);		// Libera o ponteiro principal
		system("clear");
	}
}

int insertLogin(Login* LO, struct info al){		 
	if(LO == NULL){		// Confere se a lista existe 
		return 0;		// Caso n�o exista retorna 0
	}
	List *LI = creatList();
	int I = 1;
	Elem* NO;		// Declara��o de um ponteiro auxiliar
	NO = (Elem*) malloc(sizeof(Elem));		// Aloca��o de memoria para o novo n� da lista
	if(NO == NULL){		// Confere se o no foi criado 
		return 0;		// Caso n�o tenha criado retorna 0
	}
	
	NO->DICE = al;		// Preenchimento do no com o dado fornecido
	NO->DICE.LI = LI;
	NO->next = NULL;		// Ponteiro prox eh apontado para null
	if((*LO) == NULL){
		NO->DICE.id = I;
		NO->prev = NULL;		// Se for o ponteiro ant vai receber null
		*LO = NO;		// e li recebe o n� atual
	} else{		
		Elem *AUX = *LO;		// Cria��o de um segundo ponteiro auxiliar para percorrer a lista
		while(AUX->next != NULL){		// La�o de repeti��o para percorrer a lista
			I = AUX->DICE.id+1;
			AUX = AUX->next;
		}
		NO->DICE.id = I+1;
		AUX->next = NO;			// Ponteiro prox do segundo ponteiro aponta para o primeiro n� auxiliar 
		NO->prev = AUX;		// Ponteiro ant do primeiro ponteiro aponta para o segundo ponteiro auxiliar
	}
	return 1;		// Caso tudo funcione retorna 1
}

void printLogin(Login *LO){
	Elem *NO = *LO;		
    printf("\n======= REGISTERED USERS =======");
	while(NO!=NULL){	
		printf("\nID: %d \nNAME: %s %s \nEMAIL: %s" /*\nPASSWORD: %d\n"*/, NO->DICE.id, NO->DICE.Name, NO->DICE.LastName, NO->DICE.email/*, NO->DICE.password*/);
		printf("\n================================");
		NO = NO->next; 
	}
	printf("\n");		// Quebra de linha
}


int findEmail(Login* LO, char email[N], struct info *al){
	if(LO == NULL){
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
	if(LO == NULL){
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
		*LO = NO->next;
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

	struct info DATA[COUNT];	
	
	FILE *fp = fopen("size.bin", "w+b");
	if(fp == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
		exit(1);
	}
	fprintf(fp, "%d", COUNT);//(count, fp);	
	fclose(fp);

    FILE *arq = fopen("login.bin", "w+b");
    
    if(arq == NULL){
        printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
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

int menu(struct info *al) {
	
	int auxA = 0;
    char email[N];
	strcpy(email, al->email);
	//readSchedule(al->LI, email);
    
    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERT EVENT             |"
    	       "\n| 2 - VIEW EVENT               |"
    	       "\n| 3 - REMOVE EVENT             |"
               "\n|                              |"
    	       "\n|                              |"
    	       "\n| 0 - LOGOFF                   |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
            case 1:{ 
                insertEvent(al->LI);
                break;
            }
            case 2:{
                printEvent(al->LI);
                printf("\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordinates();
                break;
            }
            case 3:{
                removeEvent(al->LI);
                break;
            }
			case 0:{
				writeSchedule(al->LI, email);
                break;
			}
            default:{
                break;
            }

        } 
    }while(auxA!=0);
	
	return 0;
}