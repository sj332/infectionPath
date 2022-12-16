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
    //ifctele_genElement(pIndex,age,time,placeHist[N_HISTORY]);
    while(3==fscanf(fp,"%d %d %d",&pIndex,&age,&time))  //3가지 읽기 
    {	
    	int i;
		//printf("%i 번째 환자 감염 경로 : ",pIndex);
    	for(i=0;i<5;i++){
			fscanf(fp,"%d",&placeHist[i]);
    		//printf("%s\t",ifctele_getPlaceName(placeHist[i])); //구조체 넘기면 된다. 
    		
		}
		ifct_element=ifctele_genElement(pIndex,age,time,placeHist);
    	ifctdb_addTail(ifct_element); //링크드리스트에 환자 정보 전달 
	//printf("\n");
	}
	
	//isdb_tail로 메인에 전달 
	
	
	//#endif  
	
	
    //1-3. FILE pointer close
    fclose(fp);

    
    {
    	//int place1,place2;
		
		//place1=3;
		//place2=15;
		
		//printf("The first place is %s\n",ifctele_getPlaceName(place1));
		//printf("The second place is %s\n",ifctele_getPlaceName(place2));
	}
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");    //알고리즘, 가장 어려움, 15주차                 //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection) //n번째 환자 정보를 가져오고, printelement로 출력 
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                
				//printf("age:%i\n",ifctele_getAge(ifct_element)); 
                printf("enter patient index: ");
				scanf("%i",&pIndex);				
				ifct_element = ifctdb_getData(pIndex);
				ifctele_printElement(ifct_element);
				break;//포인터만 넘김 
                
            case MENU_PLACE: //지정장소와 같으면 출력하고 아니면 skip 
            	{
				
				int i;
				char placeinput;
                printf("Place Name: ");
				scanf("%s",&placeinput);
				int pIndex;
				
				for(i=0;i<place_t.size(place_t);i++){
					if placeinput==place_t[i]{
						pIndex=i;}
								}
				}
				ifct_element = ifctdb_getData(pIndex);
				ifctele_getHistPlaceIndex(ifct_element);
				ifctele_getHistPlaceIndex(ifct_element,pIndex);
				//for(int i = 0; i <5; i++){
  				
				  if(countryName[i] == placeinput)
				int index=i;
				else if
				int index=-1}
				printf("There are %i patients detected in %s",0,place;}
				ifct_element = ifctdb_getData(place);
                
				printf("place:%i\n",ifctele_getHistPlaceIndex(&ifct_element,pIndex));
				ifctele_getHistPlaceIndex(ifct_element,pIndex);
				break;
                }
            case MENU_AGE:
                printf("age:%i\n",ifctele_getAge(&ifct_element));
                
				break;
                
            case MENU_TRACK: //감염경로 추적, 최초의 전파자 
            	//printf("Patient index :%i\n",);
			
			
			/*PPT에서 알고리즘에 답 있음, 
			1) 같은 시점과 장소
			2) 1일 전, 2일 전에 전피 가능
			3) , 잠복기중 전염x 2////일 전,  3일 전, 4일 전에 잠복 가능
			배열의 N번쨰와 다른 환자의 N+2번쪠가 같은지 
			날짜 상으로 배열[N]==다른배열[F]인 부분을 찾아내야 
			isMet(), trackInfester 계싼 
			*/
			/*
            for (i=2;i<N_HISTORY;i++)// 함수짜기 
				{
				현재환자의 i번째 이동장소 시점 계산;
				계산된 시점에서의 대상환자 이동장소 계산;
				if (i번째 이동장소 == 대상환자 이동장소)
				{
				만난시간 = i번째 이동장소 시점;
				}
				}
				return 만난시간;        
                break;
                
            for (i번째 환자)
				{
				만난시간 = isMet(현재환자, i번째 환자);
				if ( 만난시간> 0) //만났다면
				{
				if (지금까지 환자 중 만난시간이 가장 이른가?)
				{
				전파자 = i;
				}
				}
				}
				return 전파자;  
			*/
			break;	  
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
	
    return 0;
}
