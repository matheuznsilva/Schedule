#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
#include "funcoes.h"
#include "quickSort.h"

int coordenadas();

int inserir_evento(Lista *LI){

	struct agenda AUX;	// "Variável" do tipo struct aluno
	
	int a=0;

	do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERIR UMA TAREFA       |"
    	       "\n| 2 - INSERIR UMA REUNIAO      |"
    	       "\n| 3 - INSERIR UM ANIVERSARIO   |"
    	       "\n|                              |"
    	       "\n| 0 - VOLTAR                   |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
        	
        	case 1:{
                
        		printf("\nASSUNTO: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nHORARIO DE INICIO: ");
                scanf("%d", &AUX.time_start);
                printf("\nHORARIO DE TERMINO: ");
                scanf("%d", &AUX.time_end);
                printf("\nESFORCO: ");
                scanf("%d", &AUX.esforco);
                printf("\nPRIORIDADE: ");
                scanf("%d", &AUX.priority);
                AUX.evento = 1;

                insere_lista_ordenada(LI, AUX);
                break;
            }

            case 2:{ 

        		printf("\nASSUNTO: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nHORARIO DE INICIO: ");
                scanf("%d", &AUX.time_start);
                printf("\nHORARIO DE TERMINO: ");
                scanf("%d", &AUX.time_end);
                printf("\nLOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                printf("\nPRESENCA OBRIGATORIA(1-sim/0-nao): ");
                scanf("%d", &AUX.presenca);
                AUX.evento = 2;

                insere_lista_ordenada(LI, AUX);
                break;
            }
            
            case 3:{ 

        		printf("\nASSUNTO: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nHORARIO DE INICIO: ");
                scanf("%d", &AUX.time_start);
                printf("\nHORARIO DE TERMINO: ");
                scanf("%d", &AUX.time_end);
                printf("\nLOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                printf("\nNOME ANIVERSARIANTE: ");
        		setbuf(stdin, NULL);
                fgets(AUX.name, N, stdin);
                AUX.evento = 3;
                
                insere_lista_ordenada(LI, AUX);
                break;
            }
            default:{
                break;
            }
        } 
    }while(a!=0);
}

int visualizar_evento(Lista *LI){
    struct agenda AUX;  // "Variável" do tipo struct aluno
    
    int a=0, B, num=0;

    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - BUSCAR UMA TAREFA        |"
               "\n| 2 - BUSCAR UMA REUNIAO       |"
               "\n| 3 - BUSCAR UM ANIVERSARIO    |"
               "\n|                              |"
               "\n| 0 - VOLTAR                   |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
            
            case 1:{
                printf("HORARIO: ");
                scanf("%d", &num);
                busca_lista(LI, num, &AUX);
                //imprime_Evento(1, AUX);
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }

            case 2:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                busca_lista(LI, num, &AUX);
                //imprime_Evento(2, AUX);
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                
                break;
            }
            
            case 3:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                busca_lista(LI, num, &AUX);
                //imprime_Evento(3, AUX);
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }
            default:{
                break;
            }

        }
    }while(a!=0);   
}

int remover_evento(Lista *LI){
    int a=0, num=0;

    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - REMOVER UMA TAREFA       |"
               "\n| 2 - REMOVER UMA REUNIAO      |"
               "\n| 3 - REMOVER UM ANIVERSARIO   |"
               "\n|                              |"
               "\n| 0 - VOLTAR                   |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a);
        system("clear");

        switch(a){
            
            case 1:{
                printf("HORARIO: ");
                scanf("%d", &num);
                remove_lista(LI, num);                
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }

            case 2:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                remove_lista(LI, num);                
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                
                break;
            }
            
            case 3:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                remove_lista(LI, num);                
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenadas();
                break;
            }
            default:{
                break;
            }

        }
    }while(a!=0);   
}

/*void imprime_Evento(int i, struct agenda ag){
    if(i==1){
        printf("\nASSUNTO: %s", ag.subject);
        printf("HORARIO DE INICIO: %d", ag.time_start);
        printf("\nHORARIO DE TERMINO: %d", ag.time_end);
        printf("\nESFORCO: %d", ag.esforco);
        printf("\nPRIORIDADE: %d", ag.priority);

    } else if(i==2){
        printf("\nASSUNTO: %s", ag.subject);
        printf("HORARIO DE INICIO: %d", ag.time_start);
        printf("\nHORARIO DE TERMINO: %d", ag.time_end);
        printf("\nLOCAL: %s", ag.local);
        if(ag.presenca == 1){
            printf("\nPRESENCA OBRIGATORIA");
        } else{
            printf("\nNAO É OBRIGATORIA A PRESENCA");
        }

    } else if(i==3){
        printf("\nASSUNTO: %s", ag.subject);
        printf("HORARIO DE INICIO: %d", ag.time_start);
        printf("\nHORARIO DE TERMINO: %d", ag.time_end);
        printf("\nLOCAL: %s", ag.local);
        printf("\nANIVERSARIANTE: %s", ag.name);

    } else{
        printf("ERRO!!!");
    }
} */


int coordenadas(){
	char A[1];
	gets(A);
    setbuf(stdin,NULL);
	return A[0];
}