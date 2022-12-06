//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    ifctele_getPlaceName(placeHist[1]);
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r"); 
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    
    //1-2. loading each patient informations
   ifctele_genElement(pIndex,age,time,placeHist[N_HISTORY]);
    while(3==fscanf(fp,"%d %d %d",&pIndex,&age,&time))  //3가지 읽기 
    {	
    	int i;
		printf("%i 번째 환자 감염 경로 : ",pIndex);
    	for(i=0;i<5;i++)
    		//if(=="\n")
    		//placeHist[i]=fscanf(fp,)
			{fscanf(fp,"%d",&placeHist[i]);
    		printf("%s\t",ifctele_getPlaceName(placeHist[i]));
    		}//printf("%i",3);
    		 //5개 읽기
	printf("\n");
	}
	
	

	// 결과: 8개(한줄)가 읽어짐 
	
	char line[255];
	while(fgets(line,sizeof(line),fp)!=NULL){
		printf("%s",line);
	}
	
	
	//#endif 
	//출력해보기 
	
	
    //1-3. FILE pointer close
    fclose(fp);
    
    
    {
    	int place1,place2;
		
		place1=3;
		place2=15;
		
		printf("The first place is %s\n",ifctele_getPlaceName(place1));
		printf("The second place is %s\n",ifctele_getPlaceName(place2));
	}
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                //ifct_element
				//printf("age:%i\n",ifctele_getAge(ifct_element)); 
                break;//포인터만 넘김 
                
            case MENU_PLACE:
                printf("place:%i\n",ifctele_getHistPlaceIndex(&ifct_element,pIndex));
                break;
                
            case MENU_AGE:
                printf("age:%i\n",ifctele_getAge(&ifct_element));
                break;
                
            case MENU_TRACK:
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
	
    return 0;
}
