#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

Login* loading(){
	int i, count;

	Login *LO;		// Declaração de ponteiro

	FILE *fp = fopen("tamanho.txt", "r");
	if(fp == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}
	fscanf(fp, "%d", &count);	
	fclose(fp);

	struct info DADOS[count];	// "Variável" do tipo struct aluno

	FILE *arq = fopen("login.bin", "rb");
	if(arq == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}

	fread(DADOS, sizeof(struct info), count, arq);

	LO = cria_login();		// Criação da lista	

	for(i=0; i<count; i++){
		insere_login(LO, DADOS[i]);
	}

	fclose(arq);

	return LO;
}




int coordenates(){
	char AUX[1];
    setbuf(stdin,NULL);
	gets(AUX);
    setbuf(stdin,NULL);
	return AUX[0];
}


int menuLogin() {
	
	Login *LO;

	LO = loading();
    loadingSchedule(LO);

	struct info dataAUX, dataAUX_1;	// "Variável" do tipo struct aluno
	char EMAIL[N];
	int PASSWORD, VERIFICATION;
	int auxA=0, auxB=0, auxC=0, auxD=0;

	do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - ENTRAR                   |"
    	       "\n| 2 - NOVO USUÁRIO             |"
               "\n| 3 - REMOVER USUÁRIO          |"
    	       "\n| 4 - IMPRIMIR LISTA           |"
    	       "\n|                              |"
    	       "\n| 0 - SAIR                     |");
        printf("\n================================\n\n");
        printf("Digite sua escolha: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
        	
        	case 1:{ //fazer login
                system("clear");
                printf("\t\tLOGIN\n\nEMAIL: ");
                setbuf(stdin, NULL);
                gets(EMAIL);
                
                auxB = busca_email(LO, EMAIL, &dataAUX_1);

                if(auxB == 1){
                    do{
                        system("clear");
                        printf("NOME: %s %s\n", dataAUX_1.Name, dataAUX_1.LastName);
                        printf("\nSENHA: ");
                        scanf("%d", &PASSWORD);
                        if(PASSWORD == dataAUX_1.password){
                            auxD = 0;
                        } else{
                            system("clear");
                            printf("\t\tLOGIN\n\nSENHAS INCORRETA\n\nDESEJA TENTAR NOVAMENTE? (0 - NAO | 1 - SIM) ");
                            scanf("%d", &auxD);
                        }
                    }while(auxD != 0);

                    menu();
                } else{
                    system("clear");
                    printf("\t\tLOGIN\n\nUSUÁRIO NÃO ENCONTRADO \nDESEJA CADASTRAR NOVO USUÁRIO? (0 - NAO | 1 - SIM) ");
                    scanf("%d", &auxC);
                    if(auxC == 0){
                        system("clear");
                        printf("\t\tLOGIN\n\nDESEJA VOLTAR AO INICIO? (0 - NAO | 1 - SIM) ");
                        scanf("%d", &auxC);
                        if (auxC == 0){
                            auxA = 0;
                        }
                    } else if(auxC == 1){
                        auxA = 2;
                    }
                }   
                break;
            }

            case 2:{ // cadastrar novo usuário

        		do{
                    system("clear");
                    printf("\t\tCADASTRAR NOVO USUARIO\n\nEMAIL: ");
                    setbuf(stdin, NULL);
                    gets(dataAUX.email);

                    auxB = busca_email(LO, dataAUX.email, &dataAUX_1);
                    
                    if(auxB == 1){
                        system("clear");
                        printf("\t\tCADASTRAR NOVO USUARIO\n\nEMAIL JA CADASTRADO\nDESEJA FAZER LOGIN? (0 - NAO | 1 - SIM) ");
                        scanf("%d", &auxC);
                        if (auxC == 0){
                            printf("\t\tCADASTRAR NOVO USUARIO\n\nDESEJA CADASTRAR NOVO USUÁRIO? (0 - NAO | 1 - SIM) ");
                            scanf("%d", &auxC);
                            if (auxC == 0){
                                auxD = 0;
                                break;
                            } else if (auxC == 1){
                                auxD = 1;
                            }
                        } else{
                            auxD = 0;
                        }
                        
                    } else{
                        printf("\nNOME: ");
                        setbuf(stdin, NULL);
                        gets(dataAUX.Name);
                        printf("\nSOBRENOME: ");
                        setbuf(stdin, NULL);
                        gets(dataAUX.LastName);

                        do{
                            system("clear");
                            printf("\t\tCADASTRAR NOVO USUARIO\n\nEMAIL: %s", dataAUX.email);
                            printf("\nNOME: %s %s", dataAUX.Name, dataAUX.LastName);
                            printf("\nSENHA: ");
                            scanf("%d", &PASSWORD);

                            printf("\nDIGITE A SENHA NOVAMENTE: ");
                            scanf("%d", &VERIFICATION);

                            if (PASSWORD == VERIFICATION){
                                dataAUX.password = PASSWORD;
                                
                                auxB = insere_login(LO, dataAUX);
                                if(auxB = 1){
                                    system("clear");
                                    printf("\t\tCADASTRAR NOVO USUARIO\n\nCADASTRO EFETUADO COM SUCESSO ");
                                    sleep(1);
                                    auxD = 0;
                                } else{
                                    system("clear");
                                    printf("\t\tCADASTRAR NOVO USUARIO\n\nERRO AO CADASTRAR NOVO USUARIO \nTENTE NOVAMENTE ");
                                    sleep(1);
                                    auxD = 1;
                                }
                                auxC = 0;
                            } else {
                                system("clear");
                                printf("\t\tCADASTRAR NOVO USUARIO\n\nSENHAS NAO COINCIDEM \nTENTE NOVAMENTE ");
                                sleep(1);                                
                                auxC = 1;
                            }
                        }while(auxC != 0);

                    }

                }while(auxD != 0);
                break;
            }
            
            case 3:{
                system("clear");
                printf("\t\tREMOVER CONTA\n\nEMAIL: ");
                setbuf(stdin, NULL);
                gets(dataAUX.email, N, stdin);

                auxB = busca_email(LO, dataAUX.email, &dataAUX_1);
                
                if(auxB == 1){
                    printf("\nDESEJA REALIZAR A REMOCAO? (0 - NAO | 1 - SIM) ");
                    scanf("%d", &auxC);
                    if(auxC == 1){
                        do{
                            system("clear");
                            printf("\nSENHA: ");
                            scanf("%d", &dataAUX.password);
                            if(dataAUX.password == dataAUX_1.password){
                               auxC = remove_login(LO, dataAUX_1.id);
                                if(auxC == 1){
                                    system("clear");
                                    printf("\t\tREMOVE CONTA\n\nUSUARIO REMOVIDO COM SUCESSO ");
                                    sleep(1);
                                    
                                    auxD = 0;
                                } else{
                                    printf("\t\tREMOVER CONTA\n\nERRO AO REMOVER USUÁRIO \nTENTE NOVAMENTE ");
                                    auxD = 1;
                                    sleep(1);
                                }
                            } else{
                                system("clear");
                                printf("\nSENHAS NÃO CORRESPONDEM! \nDESEJA TENTAR NOVAMENTE? (0 - NAO | 1 - SIM) ");
                                scanf("%d", &auxC);
                                if(auxC == 0){
                                    auxD = 0;
                                } else{
                                    auxD = 1;
                                }
                            }
                        }while(auxD != 0);
                    }
                } else{
                    printf("\nUSUARIO NÃO EXISTE \n\nDESEJA VOLTAR AO INICIO? (0 - NAO | 1 - SIM) ");
                    scanf("%d", &auxC);
                    if (auxC == 0){
                        auxA = 0;
                    } else if(auxC == 1){
                        auxA = 1;
                    }
                }
                break;
        	
            }
            case 4:{
                imprime_Logins(LO);        // Chamada de Função de impressão da Lista 
                printf("\nPRESSIONE ENTER PARA CONTINUAR");
                coordenates();
                break;
            }
            case 0:{
                auxA = 0;
                break;
            }
            default:{
                break;
            }
        } 
    }while(auxA!=0);

    EscreverLogins(LO);
	
	libera_logins(LO);		// Chamada de Função de destruição da Lista 
		
	return 0;
}

// ==========================================================

int menu() {
	
	int a=0;
	
	Lista *LI;		// Declaracao do ponteiro do tipo Lista
	
	LI = cria_lista();		// Criacao da lista

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
                coordenates();
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

// ==========================================================

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
                coordenates();
                break;
            }

            case 2:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                busca_lista(LI, num, &AUX);
                //imprime_Evento(2, AUX);
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenates();
                
                break;
            }
            
            case 3:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                busca_lista(LI, num, &AUX);
                //imprime_Evento(3, AUX);
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenates();
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
                coordenates();
                break;
            }

            case 2:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                remove_lista(LI, num);                
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenates();
                
                break;
            }
            
            case 3:{ 
                printf("HORARIO: ");
                scanf("%d", &num);
                remove_lista(LI, num);                
                printf("\n\n DIGITE ENTER PARA VOLTAR ");
                setbuf(stdin,NULL);
                coordenates();
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

