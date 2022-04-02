#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

Login* loading(){
	int I, COUNT;

	Login *LO;		// Declaração de ponteiro

	FILE *fp = fopen("tamanho.txt", "r");
	if(fp == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}
	fscanf(fp, "%d", &COUNT);	
	fclose(fp);

	struct info DADOS[COUNT];	// "Variável" do tipo struct aluno

	FILE *ARQ = fopen("login.bin", "rb");
	if(ARQ == NULL){
		printf("ERRO NA LEITURA DE DADOS");
		exit(1);
	}

	fread(DADOS, sizeof(struct info), COUNT, ARQ);

	LO = creatLogin();		// Criação da lista	

	for(I = 0; I < COUNT; I++){
		insertLogin(LO, DADOS[I]);
	}

	fclose(ARQ);

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
    //loadingSchedule(LO);

	struct info dataAUX, dataAUX_1;	// "Variável" do tipo struct aluno
	char EMAIL[N];
	int PASSWORD, VERIFICATION;
	int auxA = 0, auxB = 0, auxC = 0, auxD = 0;

	do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - LOGIN                    |"
    	       "\n| 2 - NEW USER                 |"
               "\n| 3 - REMOVE USER              |"
    	       "\n| 4 - SHOW USER LIST           |"
    	       "\n|                              |"
    	       "\n| 0 - EXIT                     |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
        	
        	case 1:{ //fazer login
                system("clear");
                printf("\n\n============= LOGIN =============");
                printf("\n\nEMAIL: ");
                setbuf(stdin, NULL);
                gets(EMAIL);
                
                auxB = findEmail(LO, EMAIL, &dataAUX_1);

                if(auxB == 1){
                    do{
                        system("clear");
                        printf("\n\n============= LOGIN =============");
                        printf("\nNAME: %s %s", dataAUX_1.Name, dataAUX_1.LastName);
                        printf("\nPASSWORD: ");
                        scanf("%d", &PASSWORD);
                        if(PASSWORD == dataAUX_1.password){
                            auxD = 0;
                        } else{
                            system("clear");
                            printf("\n\n============= LOGIN =============");
                            printf("\n\n-> INCORRECT PASSWORD <- \n\nWANT TO TRY AGAIN? (0 - NO | 1 - YES): ");
                            scanf("%d", &auxD);
                        }
                    }while(auxD != 0);

                    menu();
                } else{
                    system("clear");
                    printf("\n\n============= LOGIN =============");
                    printf("\n\n-> ERRO 404! - USER NOT FOUND <- \nDO YOU WANT TO REGISTER A NEW USER? (0 - NO | 1 - YES): ");
                    scanf("%d", &auxC);
                    if(auxC == 0){
                        system("clear");
                        printf("\n\n============= LOGIN =============");
                        printf("\n\nGO BACK TO START? (0 - NO | 1 - YES): ");
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
                    printf("\n\n====== REGISTER A NEW USER ======");
                    printf("\n\nEMAIL: ");
                    setbuf(stdin, NULL);
                    gets(dataAUX.email);

                    auxB = findEmail(LO, dataAUX.email, &dataAUX_1);
                    
                    if(auxB == 1){
                        system("clear");
                        printf("\n\n====== REGISTER A NEW USER ======");
                        printf("\n\n-> EMAIL ALREADY REGISTERED <- \nWANT TO LOGIN? (0 - NO | 1 - YES): ");
                        scanf("%d", &auxC);
                        if (auxC == 0){
                            printf("\n\n====== REGISTER A NEW USER ======");
                            printf("\n\nDO YOU WANT TO REGISTER A NEW USER? (0 - NO | 1 - YES): ");
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
                        printf("NAME: ");
                        setbuf(stdin, NULL);
                        gets(dataAUX.Name);
                        printf("LAST NAME: ");
                        setbuf(stdin, NULL);
                        gets(dataAUX.LastName);

                        do{
                            system("clear");
                            printf("\n\n====== REGISTER A NEW USER ======");
                            printf("\n\nEMAIL: %s", dataAUX.email);
                            printf("\nNAME: %s %s", dataAUX.Name, dataAUX.LastName);
                            printf("\nPASSWORD: ");
                            scanf("%d", &PASSWORD);
                            printf("ENTER PASSWORD AGAIN: ");
                            scanf("%d", &VERIFICATION);

                            if (PASSWORD == VERIFICATION){
                                dataAUX.password = PASSWORD;
                                
                                auxB = insertLogin(LO, dataAUX);
                                if(auxB = 1){
                                    system("clear");
                                    printf("\n\n====== REGISTER A NEW USER ======");
                                    printf("\n\n-> REGISTRATION SUCCESSFUL! <-");
                                    sleep(1);
                                    auxD = 0;
                                } else{
                                    system("clear");
                                    printf("\n\n====== REGISTER A NEW USER ======");
                                    printf("\n\n-> ERROR WHEN REGISTERING NEW USER <- \nTRY AGAIN");
                                    sleep(1);
                                    auxD = 1;
                                }
                                auxC = 0;
                            } else {
                                system("clear");
                                printf("\n\n====== REGISTER A NEW USER ======");
                                printf("\n\n-> PASSWORD DON'T MATCH <-\nTRY AGAIN");
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
                printf("\n\n========== REMOVE USER ==========");
                printf("\n\nEMAIL: ");
                setbuf(stdin, NULL);
                gets(dataAUX.email, N, stdin);

                auxB = findEmail(LO, dataAUX.email, &dataAUX_1);
                
                if(auxB == 1){
                    printf("\nDO YOU WANT TO REMOVE? (0 - NO | 1 - YES) ");
                    scanf("%d", &auxC);
                    if(auxC == 1){
                        do{
                            system("clear");
                            printf("\n\n========== REMOVE USER ==========");
                            printf("\nNAME: %s %s \nEMAIL: %s", dataAUX_1.Name, dataAUX_1.LastName, dataAUX_1.email);
                            printf("\nPASSWORD: ");
                            scanf("%d", &dataAUX.password);
                            if(dataAUX.password == dataAUX_1.password){
                               auxC = removeLogin(LO, dataAUX_1.id);
                                if(auxC == 1){
                                    system("clear");
                                    printf("\n\n========== REMOVE USER ==========");
                                    printf("\n\n-> USER SUCCESSFULLY REMOVED <-");
                                    sleep(1);
                                    
                                    auxD = 0;
                                } else{
                                    printf("\n\n========== REMOVE USER ==========");
                                    printf("\n\n-> ERROR REMOVING USER <-\nTRY AGAIN");
                                    auxD = 1;
                                    sleep(1);
                                }
                            } else{
                                system("clear");
                                printf("\n\n========== REMOVE USER ==========");
                                printf("\n\n-> PASSWORD DON'T MATCH <-");
                                printf("\nTRY AGAIN? (0 - NO | 1 - YES): ");
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
                    system("clear");
                    printf("\n\n========== REMOVE USER ==========");
                    printf("\n\n-> ERRO 404! - USER NOT FOUND <-\nGO BACK TO START? (0 - NO | 1 - YES): ");
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
                printLogin(LO);        // Chamada de Função de impressão da Lista 
                printf("\nPRESS ENTER TO CONTINUE");
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

    writeLogin(LO);
	
	freeLogin(LO);		// Chamada de Função de destruição da Lista 
		
	return 0;
}

// ==========================================================

int menu() {
	
	int auxA = 0;
	
	List *LI;		// Declaracao do ponteiro do tipo Lista
	
	LI = creatList();		// Criacao da lista

    sleep(1);
    
    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERT EVENT             |"
    	       "\n| 2 - VIEW EVENT               |"
    	       "\n| 3 - REMOVE EVENT             |"
               "\n|                              |"
    	       "\n|                              |"
    	       "\n| 0 - EXIT                     |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
            case 1:{ 
                insertEvent(LI);
                break;
            }
            case 2:{
                printEvent(LI);
                printf("\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                break;
            }
            case 3:{
                removeEvent(LI);
                break;
            }
            default:{
                break;
            }
        } 
    }while(auxA!=0);

    freeList(LI);
	
	return 0;
}

// ==========================================================

int insertEvent(List *LI){

	struct schedule AUX;	// "Variável" do tipo struct aluno
	
	int auxA = 0;

	do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - INSERT TASK              |"
    	       "\n| 2 - INSERT MEETING           |"
    	       "\n| 3 - INSERT BIRTHDAY          |"
    	       "\n|                              |"
    	       "\n| 0 - GO BACK                  |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
        	
        	case 1:{
                
        		printf("\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nSTART TIME: ");
                scanf("%d", &AUX.startTime);
                printf("\nEND TIME: ");
                scanf("%d", &AUX.endTime);
                printf("\nEFFORT: ");
                scanf("%d", &AUX.effort);
                printf("\nPRIORITY: ");
                scanf("%d", &AUX.priority);
                AUX.event = 1;

                insertList(LI, AUX);
                break;
            }

            case 2:{ 

        		printf("\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nSTART TIME: ");
                scanf("%d", &AUX.startTime);
                printf("\nEND TIME: ");
                scanf("%d", &AUX.endTime);
                printf("\nLOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                printf("\nIS YOUR PRESENCE MANDATORY? (0 - NO | 1 - YES): ");
                scanf("%d", &AUX.presence);
                AUX.event = 2;

                insertList(LI, AUX);
                break;
            }
            
            case 3:{ 

        		printf("\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("\nSTART TIME: ");
                scanf("%d", &AUX.startTime);
                printf("\nEND TIME: ");
                scanf("%d", &AUX.endTime);
                printf("\nLOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                printf("\nBIRTHDAY NAME: ");
        		setbuf(stdin, NULL);
                fgets(AUX.name, N, stdin);
                AUX.event = 3;
                
                insertList(LI, AUX);
                break;
            }
            default:{
                break;
            }
        } 
    }while(auxA!=0);
}

int viewEvent(List *LI){
    
    struct schedule AUX;  // "Variável" do tipo struct aluno
    
    int auxA = 0, NUM = 0;

    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - FIND TASK                |"
               "\n| 2 - FIND MEETING             |"
               "\n| 3 - FIND BIRTHDAY            |"
               "\n|                              |"
               "\n| 0 - GO BACK                  |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
            
            case 1:{
                printf("TIME: ");
                scanf("%d", &NUM);
                findList(LI, NUM, &AUX);
                //printEvent(1, AUX);
                printf("\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                break;
            }

            case 2:{ 
                printf("TIME: ");
                scanf("%d", &NUM);
                findList(LI, NUM, &AUX);
                //printEvent(2, AUX);
                printf("\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                
                break;
            }
            
            case 3:{ 
                printf("TIME: ");
                scanf("%d", &NUM);
                findList(LI, NUM, &AUX);
                //printEvent(3, AUX);
                printf("\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                break;
            }
            default:{
                break;
            }

        }
    }while(auxA!=0);   
}

int removeEvent(List *LI){
    int auxA = 0, NUM = 0;

    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - REMOVE TASK              |"
               "\n| 2 - REMOVE MEETING           |"
               "\n| 3 - REMOVE BIRTHDAY          |"
               "\n|                              |"
               "\n| 0 - GO BACK                  |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
            
            case 1:{
                printf("\n========= REMOVE TASK ==========");
                printf("TIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);                
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                break;
            }

            case 2:{ 
                printf("\n======== REMOVE MEETING ========");
                printf("TIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);                
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                
                break;
            }
            
            case 3:{ 
                printf("\n======= REMOVE BIRTHDAY ========");
                printf("TIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);                
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordenates();
                break;
            }
            default:{
                break;
            }

        }
    }while(auxA!=0);   
}

/*void printEvent(int I, struct schedule SC){
    if(I == 1){
        printf("\nASSUNTO: %s", SC.subject);
        printf("HORARIO DE INICIO: %d", SC.startTime);
        printf("\nHORARIO DE TERMINO: %d", SC.endTime);
        printf("\nESFORCO: %d", SC.effort);
        printf("\nPRIORIDADE: %d", SC.priority);

    } else if(I == 2){
        printf("\nASSUNTO: %s", SC.subject);
        printf("HORARIO DE INICIO: %d", SC.startTime);
        printf("\nHORARIO DE TERMINO: %d", SC.endTime);
        printf("\nLOCAL: %s", SC.local);
        if(SC.presence == 1){
            printf("\nPRESENCA OBRIGATORIA");
        } else{
            printf("\nNAO É OBRIGATORIA A PRESENCA");
        }

    } else if(I == 3){
        printf("\nASSUNTO: %s", SC.subject);
        printf("HORARIO DE INICIO: %d", SC.startTime);
        printf("\nHORARIO DE TERMINO: %d", SC.endTime);
        printf("\nLOCAL: %s", SC.local);
        printf("\nANIVERSARIANTE: %s", SC.name);

    } else{
        printf("ERRO!!!");
    }
}*/

