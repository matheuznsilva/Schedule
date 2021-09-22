#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
#include "funcoes.h"
#include "quickSort.h"

struct elemento{		// Struct que define cada elemento da lista
	struct elemento *ant;		// Ponteiro que recebe a posição do nó anterior
	struct agenda dados;		// Struct dados do tipo aluno
	struct elemento *prox;		// Ponteiro que recebe a posição do nó posterior
};
typedef struct elemento Elem;		// Definição do tipo elemento

Lista* cria_lista(){		// Função de criação da lista
	Lista* li = (Lista*) malloc(sizeof(Lista));		// Alocação de memoria para o inicio da lista 
	if(li != NULL){		// Verificação se a lista foi criada
		*li = NULL;		// Caso tenha sido criada aponta para null
	}
	return li;		// retorna lista
}

void libera_lista(Lista *li){		// Função que Apaga a lista
	if(li != NULL){		// Confere se a lista existe
		Elem* no;		// Declaração de um ponteiro auxiliar
		while((*li) != NULL){		// Laço de repetição para percorrer a lista
			no = *li;		// Ponteiro auxiliar recebe a posição atual da lista
			*li = (*li)->prox;		// Ponteiro principal passa a apontar para o proximo elemento
			free(no);		// Libera o ponteiro auxiliar
		}
		free(li);		// Libera o ponteiro principal
	}
}

int insere_lista_ordenada(Lista* li, struct agenda ag){		// Função de inserção ao final da lista 
	if(li == NULL){		// Confere se a lista existe 
		return 0;		// Caso não exista retorna 0
		printf("\n\t\t\tNAO INSERIDO\n\n");
    	sleep(1);
	}
	Elem* no;		// Declaração de um ponteiro auxiliar
	no = (Elem*) malloc(sizeof(Elem));		// Alocação de memoria para o novo nó da lista
	if(no == NULL){		// Confere se o nó foi criado 
		printf("\n\t\t\tNAO INSERIDO\n\n");
    	sleep(1);
		return 0;		// Caso não tenha criado retorna 0
	}
	
	no->dados = ag;		// Preenchimento da lista com o dado fornecido 
	
	if((*li) == NULL){		// Confere se é a primeira posição da lista
		no->prox = NULL;		// Ponteiro prox é apontado para null
		no->ant = NULL;		// Se for o ponteiro ant vai receber null
		*li = no;		// e li recebe o nó atual
		printf("\n\t\t\tINSERIDO\n\n");
    	sleep(1);
		return 1;
	} else{		// Caso não seja a primeira posição do vetor executa as instuções abaixo
		Elem *ante, *atual = *li;		// Criação de um segundo ponteiro auxiliar para percorrer a lista
		while(atual != NULL && atual->dados.time_start < ag.time_start){		// Laço de repetição para percorrer a lista
			ante = atual;
			atual = atual->prox;		// Segundo ponteiro auxiliar recebe a proxima posição da lista
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

void imprime_Lista(Lista *li){		// Função de impressão da lista
	Elem *no = *li;		// Declaraçaõ de um ponteiro auxiliar
	
	while(no!=NULL){		// Laço de repetição para percorrer a lista
//		printf("%d \n", no->dados);		// printf para impressão dos dados na tela
		no = no->prox;		// Ponteiro auxiliar recebendo a posição do proximo nó 
	}
	
	printf("\n");		// Quebra de linha
}

int busca_lista(Lista* li, int num, struct agenda *ag){
	if(li == NULL){
		return 0;
	}
	Elem *no = *li;
	while(no != NULL && no->dados.time_start != num){
		no = no->prox;
	}
	if(no == NULL){
		return 0;
	} else {
		*ag = no->dados;
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
	while(no != NULL && no->dados.time_start != num){		// Laço de repetição para percorrer a lista
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

    while(no!=NULL){        // Laço de repetição para percorrer a lista
        if(no->dados.evento == 1){
            printf("\nASSUNTO: %s", no->dados.subject);
            printf("HORARIO DE INICIO: %d", no->dados.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->dados.time_end);
            printf("\nESFORCO: %d", no->dados.esforco);
            printf("\nPRIORIDADE: %d", no->dados.priority);

        } else if(no->dados.evento==2){
            printf("\nASSUNTO: %s", no->dados.subject);
            printf("HORARIO DE INICIO: %d", no->dados.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->dados.time_end);
            printf("\nLOCAL: %s", no->dados.local);
            if(no->dados.presenca == 1){
                printf("PRESENCA OBRIGATORIA");
            } else{
                printf("NAO EH OBRIGATORIA A PRESENCA");
            }

        } else if(no->dados.evento==3){
            printf("\nASSUNTO: %s", no->dados.subject);
            printf("HORARIO DE INICIO: %d", no->dados.time_start);
            printf("\nHORARIO DE TERMINO: %d", no->dados.time_end);
            printf("\nLOCAL: %s", no->dados.local);
            printf("ANIVERSARIANTE: %s", no->dados.name);

        } else{
            printf("ERRO!!!");
        }
    	printf("\n");
        no = no->prox;      // Ponteiro auxiliar recebendo a posição do proximo nó 
    }
}