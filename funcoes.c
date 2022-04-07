#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ListaDinEncadDupla.h"
#include "login.h"
#include "funcoes.h"

Login* loading(){
	int I, COUNT;

	Login *LO;		// Declaração de ponteiro

	FILE *fp = fopen("size.bin", "rb");
	if(fp == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
		exit(1);
	}
	fscanf(fp, "%d", &COUNT);	
	fclose(fp);

	struct info DADOS[COUNT];	// "Variável" do tipo struct aluno

	FILE *ARQ = fopen("login.bin", "rb");
	if(ARQ == NULL){
		printf("\n================================");
		printf("\n\n-> ERROR 404 - FILE NOT FOUND <-");
		printf("\n\n================================");
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



int coordinates(){
	char AUX[2];
    setbuf(stdin,NULL);
	fgets(AUX, 2, stdin);
    setbuf(stdin,NULL);
	return AUX[0];
}

//====================================================

int menuLogin() {
	
	Login *LO;

	LO = loading();

	struct info dataAUX, dataAUX_1;	
	char EMAIL[N];
	int PASSWORD, VERIFICATION;
	int auxA = 0, auxB = 0, auxC = 0, auxD = 0, count;

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
                printf("\n============= LOGIN =============");
                printf("\n\nEMAIL: ");
                setbuf(stdin, NULL);
                gets(EMAIL);
                
                auxB = findEmail(LO, EMAIL, &dataAUX_1);

                if(auxB == 1){
                    do{
                        system("clear");
                        printf("\n============= LOGIN =============");
                        printf("\n\nNAME: %s %s", dataAUX_1.Name, dataAUX_1.LastName);
                        printf("\nPASSWORD: ");
                        scanf("%d", &PASSWORD);
                        if(PASSWORD == dataAUX_1.password){
                            auxD = 0;
                        } else{
                            system("clear");
                            printf("\n============= LOGIN =============");
                            printf("\n\n-> INCORRECT PASSWORD <- \n\nWANT TO TRY AGAIN? (0 - NO | 1 - YES): ");
                            scanf("%d", &auxD);
                        }
                    }while(auxD != 0);

                    menu(&dataAUX_1);
                } else{
                    system("clear");
                    printf("\n============= LOGIN =============");
                    printf("\n\n   -> ERROR - USER NOT FOUND <- ");
                    printf("\n\n=================================");
                    printf("\nDO YOU WANT TO REGISTER A NEW USER? (0 - NO | 1 - YES): ");
                    scanf("%d", &auxC);
                    if(auxC == 0){
                        system("clear");
                        printf("\n============= LOGIN =============");
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
                    printf("\n====== REGISTER A NEW USER ======");
                    printf("\n\nEMAIL: ");
                    setbuf(stdin, NULL);
                    gets(dataAUX.email);

                    auxB = findEmail(LO, dataAUX.email, &dataAUX_1);
                    
                    if(auxB == 1){
                        system("clear");
                        printf("\n====== REGISTER A NEW USER ======");
                        printf("\n\n  -> EMAIL ALREADY REGISTERED <- ");
                        printf("\n\n=================================");
                        printf("\nWANT TO LOGIN? (0 - NO | 1 - YES): ");
                        scanf("%d", &auxC);
                        if (auxC == 0){
                            printf("\n====== REGISTER A NEW USER ======");
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
                                    printf("\n====== REGISTER A NEW USER ======");
                                    printf("\n\n-> REGISTRATION SUCCESSFUL! <-");
                            		printf("\n\n================================");
                                    printf("\n");
                                    sleep(1);
                                    auxD = 0;
                                } else{
                                    system("clear");
                                    printf("\n========== REGISTER A NEW USER =========");
                                    printf("\n\n -> ERROR WHEN REGISTERING NEW USER <- \n TRY AGAIN");
                            		printf("\n\n=======================================");
                                    printf("\n");
                                    sleep(1);
                                    auxD = 1;
                                }
                                auxC = 0;
                            } else {
                                system("clear");
                                printf("\n====== REGISTER A NEW USER ======");
                                printf("\n\n   -> PASSWORD DON'T MATCH <-\n   TRY AGAIN");
                            	printf("\n\n================================");
                                printf("\n");
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
                            printf("\n========== REMOVE USER ==========");
                            printf("\nNAME: %s %s \nEMAIL: %s", dataAUX_1.Name, dataAUX_1.LastName, dataAUX_1.email);
                            printf("\nPASSWORD: ");
                            scanf("%d", &dataAUX.password);
                            if(dataAUX.password == dataAUX_1.password){
                                auxC = removeLogin(LO, dataAUX_1.id);
                                if(auxC == 1){
                                    system("clear");
                                    printf("\n========== REMOVE USER ==========");
                                    printf("\n\n-> USER SUCCESSFULLY REMOVED <-");
                                    printf("\n\n=================================");
                                    printf("\n");
                                    sleep(1);
                                    auxD = 0;
                                } else{
                                    printf("\n========== REMOVE USER ==========");
                                    printf("\n\n   -> ERROR - REMOVING USER <-\n   TRY AGAIN");
                                    printf("\n\n=================================");
                                    printf("\n");
                                    sleep(1);
                                    auxD = 1;
                                }
                            } else{
                                system("clear");
                                printf("\n========== REMOVE USER ==========");
                                printf("\n\n-> PASSWORD DON'T MATCH <-");
                                printf("\n\n=================================");
                                printf("\n\nTRY AGAIN? (0 - NO | 1 - YES): ");
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
                    printf("\n========== REMOVE USER ==========");
                    printf("\n\n   -> ERROR! USER NOT FOUND <-");
                    printf("\n\n=================================");
                    printf("\n\nGO BACK TO START? (0 - NO | 1 - YES): ");
                    scanf("%d", &auxC);
                    if (auxC == 0){
                        auxA = 0;
                    } else if(auxC == 1){
                        auxA = 1;
                    }
                    printf("\n");
                }
                break;
            }
            case 4:{
                printLogin(LO);        // Chamada de Função de impressão da Lista 
                printf("\nPRESS ENTER TO CONTINUE");
                coordinates();
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
    	       "\n|                              |"
    	       "\n| 0 - GO BACK                  |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
        	
        	case 1:{
                printf("\n========= INSERT TASK ==========");
        		printf("\n\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("START TIME: ");
                scanf("%d", &AUX.startTime);
                printf("END TIME: ");
                scanf("%d", &AUX.endTime);
                strcpy(AUX.local, "\0");
                strcpy(AUX.name, "\0");
                printf("EFFORT: ");
                scanf("%d", &AUX.effort);
                printf("PRIORITY: ");
                scanf("%d", &AUX.priority);
                AUX.presence = NULL;
                AUX.event = 1;

                insertList(LI, AUX);
                break;
            }

            case 2:{ 
                printf("\n======== INSERT MEETING ========");
        		printf("\n\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("START TIME: ");
                scanf("%d", &AUX.startTime);
                printf("END TIME: ");
                scanf("%d", &AUX.endTime);
                printf("LOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                strcpy(AUX.name, "\0");
                AUX.effort = NULL;
                AUX.priority = NULL;
                printf("IS YOUR PRESENCE MANDATORY? (0 - NO | 1 - YES): ");
                scanf("%d", &AUX.presence);
                AUX.event = 2;

                insertList(LI, AUX);
                break;
            }
            
            case 3:{ 
                printf("\n======= INSERT BIRTHDAY ========");
        		printf("\n\nSUBJECT: ");
        		setbuf(stdin, NULL);
                fgets(AUX.subject, N, stdin);
                printf("START TIME: ");
                scanf("%d", &AUX.startTime);
                printf("END TIME: ");
                scanf("%d", &AUX.endTime);
                printf("LOCAL: ");
        		setbuf(stdin, NULL);
                fgets(AUX.local, N, stdin);
                printf("BIRTHDAY NAME: ");
        		setbuf(stdin, NULL);
                fgets(AUX.name, N, stdin);
                AUX.effort = NULL;
                AUX.priority = NULL;
                AUX.presence = NULL;
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

int removeEvent(List *LI){
    int auxA = 0, NUM = 0;

    do{
        system("clear");
        printf("\n============= MENU =============");
        printf("\n| 1 - REMOVE TASK              |"
               "\n| 2 - REMOVE MEETING           |"
               "\n| 3 - REMOVE BIRTHDAY          |"
    	       "\n|                              |"
               "\n|                              |"
               "\n| 0 - GO BACK                  |");
        printf("\n================================\n\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &auxA);
        system("clear");

        switch(auxA){
            
            case 1:{
                printf("\n========= REMOVE TASK ==========");
                printf("\nTIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);                
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordinates();
                break;
            }

            case 2:{ 
                printf("\n======== REMOVE MEETING ========");
                printf("\nTIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);                
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordinates();
                break;
            }
            
            case 3:{ 
                printf("\n======= REMOVE BIRTHDAY ========");
                printf("\nTIME: ");
                scanf("%d", &NUM);
                removeList(LI, NUM);
                printf("\n\nPRESS ENTER TO CONTINUE");
                setbuf(stdin,NULL);
                coordinates();
                break;
            }
            default:{
                break;
            }
        }
    }while(auxA!=0);   
}