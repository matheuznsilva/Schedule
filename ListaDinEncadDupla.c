#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

struct component{		// Struct que define cada elemento da lista
	struct component *ant;		// Ponteiro que recebe a posi��o do n� anterior
	struct schedule DATA;		// Struct dados do tipo aluno
	struct component *prox;		// Ponteiro que recebe a posi��o do n� posterior
};
typedef struct component Comp;		// Defini��o do tipo elemento

List* creatList(){		// Fun��o de cria��o da lista
	List* LI = (List*) malloc(sizeof(List));		// Aloca��o de memoria para o inicio da lista 
	if(LI != NULL){		// Verifica��o se a lista foi criada
		*LI = NULL;		// Caso tenha sido criada aponta para null
	}
	return LI;		// retorna lista
}

void freeList(List *LI){		// Fun��o que Apaga a lista
	if(LI != NULL){		// Confere se a lista existe
		Comp* CO;		// Declara��o de um ponteiro auxiliar
		while((*LI) != NULL){		// La�o de repeti��o para percorrer a lista
			CO = *LI;		// Ponteiro auxiliar recebe a posi��o atual da lista
			*LI = (*LI)->prox;		// Ponteiro principal passa a apontar para o proximo elemento
			free(CO);		// Libera o ponteiro auxiliar
		}
		free(LI);		// Libera o ponteiro principal
	}
}

int sizeList(List* LI){	
	if(LI == NULL){		// confere se a lista existe
		return 0;		// caso não exista retorna -1 informando o erro
	}
	int cont = 0;		// declaração de variável local(contador) para armazenar a quantidade de elementos presentes na lista
	Comp* CO = *LI;		// declaração e atribuição do ponteiro auxiliar para percorrer a lista
	while(CO != NULL){		// loop para percorrer a lista com condição de para ser o final da lista
		cont++;		// incremento do contador
		CO = CO->prox;		// ponteiro auxiliar recebe a proxima posição da lista
	}
	return cont;		// retorna o contador
}

int insertList(List* LI, struct schedule SC){		// Fun��o de inser��o ao final da lista 
	if(LI == NULL){		// Confere se a lista existe 
		return 0;		// Caso n�o exista retorna 0
    	sleep(1);
	}
	Comp* CO;		// Declara��o de um ponteiro auxiliar
	CO = (Comp*) malloc(sizeof(Comp));		// Aloca��o de memoria para o novo n� da lista
	if(CO == NULL){		// Confere se o n� foi criado 
    	sleep(1);
		return 0;		// Caso n�o tenha criado retorna 0
	}
	
	CO->DATA = SC;		// Preenchimento da lista com o dado fornecido 
	
	if((*LI) == NULL){		// Confere se � a primeira posi��o da lista
		CO->prox = NULL;		// Ponteiro prox � apontado para null
		CO->ant = NULL;		// Se for o ponteiro ant vai receber null
		*LI = CO;		// e li recebe o n� atual
    	sleep(1);
		return 1;
	} else{		// Caso n�o seja a primeira posi��o do vetor executa as instu��es abaixo
		Comp *ante, *atual = *LI;		// Cria��o de um segundo ponteiro auxiliar para percorrer a lista
		while(atual != NULL && atual->DATA.startTime < SC.startTime){		// La�o de repeti��o para percorrer a lista
			ante = atual;
			atual = atual->prox;		// Segundo ponteiro auxiliar recebe a proxima posi��o da lista
		}

		if(atual == *LI){
			CO->ant = NULL;
			(*LI)->ant = CO;
			CO->prox = (*LI);
			*LI = CO;
		} else{
			CO->prox = ante->prox;
			CO->ant = ante;
			ante->prox = CO;
			if(atual != NULL){
				atual->ant = CO;
			}
		}
    	sleep(1);
		return 1;
	}
}

int findList(List* LI, int num, struct schedule *SC){
	if(LI == NULL){
		return 0;
	}
	Comp *CO = *LI;
	while(CO != NULL && CO->DATA.startTime != num){
		CO = CO->prox;
	}
	if(CO == NULL){
		return 0;
	} else {
		*SC = CO->DATA;
		return 1;
	}
}

int removeList(List *LI, int num){
	if(LI == NULL){
		return 0;
	}
	if((*LI) == NULL){
		return 0;
	}
	Comp *CO = *LI;
	while(CO != NULL && CO->DATA.startTime != num){		// La�o de repeti��o para percorrer a lista
		CO = CO->prox;	
	}
	if(CO == NULL){
		return 0;
	}
	if(CO->ant == NULL){
		*LI = CO->prox;
	} else{
		CO->ant->prox = CO->prox;
	}
	if(CO->prox != NULL){
		CO->prox->ant = CO->ant;
	}
	free(CO);
	system("clear");
	printf("\n====================================");
	printf("\n\n-> REMOVAL SUCCESSFULLY COMPLETED <-");
	printf("\n\n====================================");
	return 1;
}

void printEvent(List *LI){
    Comp *CO = *LI;
	if(CO == NULL){
		system("clear");
		printf("\n================================");
		printf("\n\n-> ERRO! NO EVENT REGISTERED <-");
		printf("\n\n================================");

	} else{
		while(CO!=NULL){        // La�o de repeti��o para percorrer a lista
			if(CO->DATA.event == 1){
				printf("\n============= TASK =============");
				printf("\nSUBJECT: %s", CO->DATA.subject);
				printf("START TIME: %d", CO->DATA.startTime);
				printf("\nEND TIME: %d", CO->DATA.endTime);
				printf("\nEFFORT: %d", CO->DATA.effort);
				printf("\nPRIORITY: %d", CO->DATA.priority);

			} else if(CO->DATA.event==2){
				printf("\n=========== MEETING ============");
				printf("\nSUBJECT: %s", CO->DATA.subject);
				printf("START TIME: %d", CO->DATA.startTime);
				printf("\nEND TIME: %d", CO->DATA.endTime);
				printf("\nLOCAL: %s", CO->DATA.local);
				if(CO->DATA.presence == 1){
					printf("ATTENDANCE: MANDATORY");
				} else{
					printf("ATTENDANCE: NOT MANDATORY");
				}

			} else if(CO->DATA.event==3){
				printf("\n=========== BIRTHDAY ===========");
				printf("\nANIVERSARIO:");
				printf("\nASSUNTO: %s", CO->DATA.subject);
				printf("HORARIO DE INICIO: %d", CO->DATA.startTime);
				printf("\nHORARIO DE TERMINO: %d", CO->DATA.endTime);
				printf("\nLOCAL: %s", CO->DATA.local);
				printf("ANIVERSARIANTE: %s", CO->DATA.name);

			} else{
				printf("\n================================");
				printf("\t\t -> ERRO <-");
				printf("\n================================");
			}
			printf("\n");
			CO = CO->prox;      // Ponteiro auxiliar recebendo a posi��o do proximo n� 
		}
		
		printf("\n================================");
	}
}

void writeSchedule(List* LI, char email[]){

	int COUNT = sizeList(LI);

    Comp *CO = *LI;

	struct schedule DATA[COUNT];

	FILE *fp = fopen("sizeList.bin", "w+b");
	if(fp == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
		exit(1);
	}
	fprintf(fp, "%d", COUNT);//(count, fp);	
	fclose(fp);

	strcat(email, "_DATA.bin");
	FILE *arq = fopen(email, "w+b");
	if(arq == NULL){
        printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
        exit(1);
    }

	for(int I=0; I<COUNT; I++){
    	strcpy(DATA[I].subject , CO->DATA.subject);
    	strcpy(DATA[I].local , CO->DATA.local);
    	strcpy(DATA[I].name , CO->DATA.name);
    	DATA[I].startTime = CO->DATA.startTime;
    	DATA[I].endTime = CO->DATA.endTime;
    	DATA[I].effort = CO->DATA.effort;
    	DATA[I].priority = CO->DATA.priority;
    	DATA[I].presence = CO->DATA.presence;
    	DATA[I].event = CO->DATA.event;
    	CO = CO->prox;
    }

	fwrite(DATA, sizeof(struct schedule), COUNT, arq);	
}

void learnSchedule(List* LI, char email[]){
	int I, COUNT;

	FILE *fp = fopen("sizeList.bin", "rb");
	if(fp == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
		exit(1);
	}
	fscanf(fp, "%d", &COUNT);	
	fclose(fp);

	struct schedule DADOS[COUNT];	// "Variável" do tipo struct aluno
	
	strcat(email, "_DATA.bin");
	FILE *ARQ = fopen(email, "rb");
	if(ARQ == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
		exit(1);
	}

	fread(DADOS, sizeof(struct info), COUNT, ARQ);

	for(I = 0; I < COUNT; I++){
		insertList(LI, DADOS[I]);
	}

	fclose(ARQ);

	//return LI;
}