#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
#include "funcoes.h"
#include "quickSort.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	int a=0;
	
	Lista *LI;		// Declaração do ponteiro do tipo Lista
	
	LI = cria_lista();		// Criação da lista

	printf("\n\t\t\tBEM VINDO\n\n");
    sleep(1);
    
    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERIR UM EVENTO        |"
    	       "\n| 2 - VISUALIZAR UM EVENTO     |"
    	       "\n| 3 - REMOVER UM EVENTO        |"
               "\n|                              |"
    	       "\n|                              |"
    	       "\n| 0 - SAIR                     |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
            case 1:{ 
                inserir_evento(LI);
                break;
            }
            case 2:{
                imprime_Evento(LI);
                printf("\nDIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }
            case 3:{
                remover_evento(LI);
                break;
            }
            default:{
                break;
            }
        } 
    }while(a!=0);

    libera_lista(LI);
	
	return 0;
}