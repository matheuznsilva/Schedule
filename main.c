#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
#include "funcoes.h"
#include "quickSort.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	int a=0;
	
	Lista *TA;		// Declaração do ponteiro do tipo Lista
	Lista *RE;		// Declaração do ponteiro do tipo Lista
	Lista *AN;		// Declaração do ponteiro do tipo Lista
	
	TA = cria_lista();		// Criação da lista
	RE = cria_lista();		// Criação da lista
	AN = cria_lista();		// Criação da lista


	printf("\n\t\t\tBEM VINDO\n\n");
    sleep(1);
    
    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERIR UM EVENTO        |"
    	       "\n| 2 - VISUALIZAR UM EVENTO     |"
    	       "\n| 3 - IMPRIMIR TODOS EVENTOS   |"
    	       "\n| 4 - REMOVER UM EVENTO        |"
    	       "\n|                              |"
    	       "\n| 0 - SAIR                     |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
            case 1:{ 
                inserir_evento(TA, RE, AN);
                break;
            }
            case 2:{
                visualizar_evento(TA, RE, AN);
                break;
            }
            case 3:{
 
            }
            case 4:{
                remover_evento(TA, RE, AN);
                break;
            }
            default:{
                break;
            }
        } 
    }while(a!=0);

    libera_lista(TA);
    libera_lista(RE);
    libera_lista(AN);
	
	return 0;
}