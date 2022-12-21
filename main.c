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

int trackInfester(int patient_no, int *dectected_time, int *place);

int convertTimeToIndex(int time,int infestedTime){
	int Index=-1;
	
	if((time<=infestedTime)&&(time>(infestedTime-N_HISTORY)))
	{
		Index=N_HISTORY-(infestedTime-time)-1;
		printf("result: %i",Index);
	}
	
	return Index;
} 
int isMet(int index,int index_i){
	int i;
	int met_time;	
	int time;
	int time_i;
	int place_ifc;
	for(i=2;i<N_HISTORY;i++){
		void *ifct_element;
		void *ifct_element_i;
		ifct_element = ifctdb_getData(index);
		ifct_element_i = ifctdb_getData(index_i);
		//time_i=ifctele_getinfestedTime(ifct_element_i);
		time=ifctele_getinfestedTime(ifct_element)-(N_HISTORY-i)+1;
		time_i=ifctele_getinfestedTime(ifct_element_i);
		printf("time: %i",time);
		printf("time_i: %i",time_i);
		index_i=convertTimeToIndex((int)time,(int)time_i);
		printf("index_i: %i",index_i);
		place_ifc=ifctele_getHistPlaceIndex(ifct_element_i,index_i);
		
		printf("\n time: %i index_i: %i place_ifc: %i\n",time,index_i,place_ifc);
		//ifctele_getHistPlaceIndex(ifct_element,time)
		
		//현재환자의 i번쨰 이동장소 시점 계산
		//계산된 시점에서의 대상환자 이동장소 계산;
		if(ifctele_getHistPlaceIndex(ifct_element,i)==place_ifc)
		{
			met_time=time;
		} 
		/*if(i번째 이동장소==대상환자 이동장소){
			만난시간=i번쨰 이동장소 시점; 
		} */
	}
	return (met_time); }

int trackInfester(int patient_no, int *dectected_time, int *place){//현재환 자 
	int i;
	//, int *detected_time, int *place
	int met_time;
	int max_time;
	int patient_ifc=100;
	for(i=0;i<5;i++)//i번째 환자 
	{
		//void *ifct_element;
		//ifct_element = ifctdb_getData(i);
		//place_index=ifctele_getHistPlaceIndex(ifct_element,N_HISTORY-1)
		met_time=isMet(patient_no,i);
		/*
		detected_time=ifctele_getinfestedTime(ifct_element)
		place=*/
		
		if(met_time>0)//만났다면
		{
				if(met_time<=max_time)
			{
				patient_ifc=i;
				max_time=met_time;
			}
		 } 
	}
	return patient_ifc;
}



int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    int i;
    int age_min;
    int age_max;
    ifctele_getPlaceName(placeHist[1]);
	int patient_now;
	int patient_ifc;
	int patient_fir;
	int place_index[30];
	int detected_time; 
	
	int *timetest;
	int *placetest;   
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
	}
	
	//isdb_tail로 메인에 전달 
	
	
	//#endif  
	
	
    //1-3. FILE pointer close
    fclose(fp);

    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");    //알고리즘      //MENU_TRACK
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
                
                printf("enter patient index: ");
				scanf("%i",&pIndex);				
				ifct_element = ifctdb_getData(pIndex);
				ifctele_printElement(ifct_element);
				break;//포인터만 넘김 
                
            case MENU_PLACE: //지정장소와 같으면 출력하고 아니면 skip 
            	{
				
				int i;
				char placeinput[40];//나라명 배열  
                printf("Place Name: ");
				scanf("%s",&placeinput);
				int place_index;
				int cnt=0;
				for(i=0;i<5;i++)//환자 수만큼 반복  
				{
					ifct_element = ifctdb_getData(i);
					place_index=ifctele_getHistPlaceIndex(ifct_element,N_HISTORY-1);
					
					if(!strcmp(ifctele_getPlaceName(place_index),placeinput))//문자열 나라명 비교 
					{
						cnt++;
						ifctele_printElement(ifct_element);
					}
				}
				printf("\n");
				printf("There are %i patients detected in %s",cnt,placeinput);
				break;
                }
            case MENU_AGE:
            	
                //printf("age:%i\n",ifctele_getAge(ifct_element));
                printf("minimal age: ");
                scanf("%i",&age_min); //최소 나이 입력 
                printf("maximal age: ");
                scanf("%i",&age_max); //최대 나이 입력 
                for(i=0;i<5;i++){ //환자 수만큼 반복 
					ifct_element = ifctdb_getData(i);
                	if(age_min<=ifctele_getAge(ifct_element)&&ifctele_getAge(ifct_element)<=age_max)//나이 범위로 비교 
					{ifctele_printElement(ifct_element);}
				}
				
				break;
                
            case MENU_TRACK: //감염경로 추적, 최초의 전파자 
            	//printf("Patient index :%i\n",);
            	/*
				for(i=0;i<5;i++){
				ifct_element = ifctdb_getData(i);
				//pIndex=ifctele_getHistPlaceIndex(ifct_element,i);
            	}*/
				printf("Patient index :");
				scanf("%i",&patient_now);
				isMet(2,3);
				while((0<=patient_now)&&(patient_now<=4)){
					ifct_element = ifctdb_getData(patient_now);
					detected_time=ifctele_getinfestedTime(ifct_element);
					patient_ifc=trackInfester(patient_now); 
					if((0<=patient_ifc)&&(patient_ifc<=4)){
						printf("patient %i is infected by %i \n",patient_now, patient_ifc);
						if(patient_fir==patient_ifc){
						printf("%i is the first infector!!",patient_fir);
						break;
					}}
					
					else{
						patient_fir=patient_now;
						patient_now=patient_ifc;}  
					}
					
					//convertTimeToIndex(8,10);
					//convertTimeToIndex(10,12);
					//convertTimeToIndex(5,7);
					//convertTimeToIndex(11,13);
					//convertTimeToIndex(6,8);
					/*
					while(PPT )
					{
					if	patient_ifc=trackinfester(patient_now)
					 else PPT
					 } */
					  
			//"%i is the first infector!!"
			//printf("The first infector of %i is %i",patient_now,patient_fir);
			//printf("%i",convertTimeToIndex(5,time));
			
			/*PPT에서 알고리즘에 답 있음, 
			1) 같은 시점과 장소
			2) 1일 전, 2일 전에 전피 가능 
			3) , 잠복기중 전염x 2////일 전,  3일 전, 4일 전에 잠복 가능
			배열의 N번쨰와 다른 환자의 N+2번쪠가 같은지 
			날짜 상으로 배열[N]==다른배열[F]인 부분을 찾아내야 
			isMet(), trackInfester 계싼 
			*/
		
			
			break;	  
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
	
    return 0;
}
