#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

struct elemento{		// Struct que define cada elemento da lista
	struct elemento *ant;		// Ponteiro que recebe a posi��o do n� anterior
	struct agenda DATA;		// Struct dados do tipo aluno
	struct elemento *prox;		// Ponteiro que recebe a posi��o do n� posterior
};
typedef struct elemento Elem;		// Defini��o do tipo elemento

Lista* cria_lista(){		// Fun��o de cria��o da lista
	Lista* li = (Lista*) malloc(sizeof(Lista));		// Aloca��o de memoria para o inicio da lista 
	if(li != NULL){		// Verifica��o se a lista foi criada
		*li = NULL;		// Caso tenha sido criada aponta para null
	}
	return li;		// retorna lista
}

void libera_lista(Lista *li){		// Fun��o que Apaga a lista
	if(li != NULL){		// Confere se a lista existe
		Elem* no;		// Declara��o de um ponteiro auxiliar
		while((*li) != NULL){		// La�o de repeti��o para percorrer a lista
			no = *li;		// Ponteiro auxiliar recebe a posi��o atual da lista
			*li = (*li)->prox;		// Ponteiro principal passa a apontar para o proximo elemento
			free(no);		// Libera o ponteiro auxiliar
		}
		free(li);		// Libera o ponteiro principal
	}
}

int insere_lista_ordenada(Lista* li, struct agenda ag){		// Fun��o de inser��o ao final da lista 
	if(li == NULL){		// Confere se a lista existe 
		return 0;		// Caso n�o exista retorna 0
		printf("\n\t\t\tNAO INSERIDO\n\n");
    	sleep(1);
	}
	Elem* no;		// Declara��o de um ponteiro auxiliar
	no = (Elem*) malloc(sizeof(Elem));		// Aloca��o de memoria para o novo n� da lista
	if(no == NULL){		// Confere se o n� foi criado 
		printf("\n\t\t\tNAO INSERIDO\n\n");
    	sleep(1);
		return 0;		// Caso n�o tenha criado retorna 0
	}
	
	no->DATA = ag;		// Preenchimento da lista com o dado fornecido 
	
	if((*li) == NULL){		// Confere se � a primeira posi��o da lista
		no->prox = NULL;		// Ponteiro prox � apontado para null
		no->ant = NULL;		// Se for o ponteiro ant vai receber null
		*li = no;		// e li recebe o n� atual
		printf("\n\t\t\tINSERIDO\n\n");
    	sleep(1);
		return 1;
	} else{		// Caso n�o seja a primeira posi��o do vetor executa as instu��es abaixo
		Elem *ante, *atual = *li;		// Cria��o de um segundo ponteiro auxiliar para percorrer a lista
		while(atual != NULL && atual->DATA.time_start < ag.time_start){		// La�o de repeti��o para percorrer a lista
			ante = atual;
			atual = atual->prox;		// Segundo ponteiro auxiliar recebe a proxima posi��o da lista
		}

		if(atual == *li){
			no->ant = NULL;
			(*li)->ant = no;
			no->prox = (*li);
			*li = no;
		} else{
			no->prox = ante->prox;
			no->ant = ante;
			ante->prox = no;
			if(atual != NULL){
				atual->ant = no;
			}
		}
		printf("\n\t\t\tINSERIDO\n\n");
    	sleep(1);
		return 1;
	}
}

int busca_lista(Lista* li, int num, struct agenda *ag){
	if(li == NULL){
		return 0;
	}
	Elem *no = *li;
	while(no != NULL && no->DATA.time_start != num){
		no = no->prox;
	}
	if(no == NULL){
		return 0;
	} else {
		*ag = no->DATA;
		return 1;
	}
}

int remove_lista(Lista *li, int num){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	Elem *no = *li;
	while(no != NULL && no->DATA.time_start != num){		// La�o de repeti��o para percorrer a lista
		no = no->prox;	
	}
	if(no == NULL){
		return 0;
	}
	if(no->ant == NULL){
		*li = no->prox;
	} else{
		no->ant->prox = no->prox;
	}
	if(no->prox != NULL){
		no->prox->ant = no->ant;
	}
	free(no);
    printf("\n\nEVENTO REMOVIDO COM SUCESSO");
	return 1;
}

void imprime_Evento(Lista *LI){
    Elem *no = *LI;

    while(no!=NULL){        // La�o de repeti��o para percorrer a lista
        if(no->DATA.evento == 1){
			printf("\nTAREFA:");
            printf("\nASSUNTO: %s", no->DATA.subject);
            printf("HORARIO DE INICIO: %d", no->DATA.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->DATA.time_end);
            printf("\nESFORCO: %d", no->DATA.esforco);
            printf("\nPRIORIDADE: %d", no->DATA.priority);

        } else if(no->DATA.evento==2){
			printf("\nREUNIAO:");
            printf("\nASSUNTO: %s", no->DATA.subject);
            printf("HORARIO DE INICIO: %d", no->DATA.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->DATA.time_end);
            printf("\nLOCAL: %s", no->DATA.local);
            if(no->DATA.presenca == 1){
                printf("PRESENCA OBRIGATORIA");
            } else{
                printf("NAO EH OBRIGATORIA A PRESENCA");
            }

        } else if(no->DATA.evento==3){
			printf("\nANIVERSARIO:");
            printf("\nASSUNTO: %s", no->DATA.subject);
            printf("HORARIO DE INICIO: %d", no->DATA.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->DATA.time_end);
            printf("\nLOCAL: %s", no->DATA.local);
            printf("ANIVERSARIANTE: %s", no->DATA.name);

        } else{
            printf("ERRO!!!");
        }
    	printf("\n");
        no = no->prox;      // Ponteiro auxiliar recebendo a posi��o do proximo n� 
    }
}