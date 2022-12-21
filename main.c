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


///�Ϲ����� ���ϵ� ����ǵ��� �� �Ϲ�ȭ ���� (���� ����) 
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
		//int index;
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
		
		//printf("%i %i %i",time,index_i,place_ifc);
		//ifctele_getHistPlaceIndex(ifct_element,time)
		
		//����ȯ���� i���� �̵���� ���� ���
		//���� ���������� ���ȯ�� �̵���� ���;
		if(ifctele_getHistPlaceIndex(ifct_element,i)==place_ifc){
			met_time=time; 
		} 
		/*if(i��° �̵����==���ȯ�� �̵����){
			�����ð�=i���� �̵���� ����; 
		} */
	}
	return (met_time); }

int trackInfester(int patient_no){//����ȯ �� 
	int i;
	//, int *detected_time, int *place
	int met_time;
	int max_time;
	int patient_ifc=100;
	for(i=0;i<5;i++)//i��° ȯ�� 
	{
		void *ifct_element;
		ifct_element = ifctdb_getData(i);
		//place_index=ifctele_getHistPlaceIndex(ifct_element,N_HISTORY-1)
		met_time=isMet(patient_no,i);
		/*
		detected_time=ifctele_getinfestedTime(ifct_element)
		place=*/
		
		if(met_time>0)//�����ٸ�
		{
			if(met_time<=max_time)
			{
				patient_ifc=i;
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
    //ifctele_genElement(pIndex,age,time,placeHist[N_HISTORY]);
    while(3==fscanf(fp,"%d %d %d",&pIndex,&age,&time))  //3���� �б� 
    {	
    	int i;
		//printf("%i ��° ȯ�� ���� ��� : ",pIndex);
    	for(i=0;i<5;i++){
			fscanf(fp,"%d",&placeHist[i]);
    		//printf("%s\t",ifctele_getPlaceName(placeHist[i])); //����ü �ѱ�� �ȴ�. 
    		
		}
		ifct_element=ifctele_genElement(pIndex,age,time,placeHist);
    	ifctdb_addTail(ifct_element); //��ũ�帮��Ʈ�� ȯ�� ���� ���� 
	//printf("\n");
	}
	
	//isdb_tail�� ���ο� ���� 
	
	
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
        printf("4. Track the root of the infection\n");    //�˰���, ���� �����, 15����                 //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
       
        
        switch(menu_selection) //n��° ȯ�� ������ ��������, printelement�� ��� 
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
				break;//�����͸� �ѱ� 
                
            case MENU_PLACE: //������ҿ� ������ ����ϰ� �ƴϸ� skip 
            	{
				
				int i;
				char placeinput[40];
                printf("Place Name: ");
				scanf("%s",&placeinput);
				int place_index;
				int cnt=0;
				for(i=0;i<5;i++){
					ifct_element = ifctdb_getData(i);
					place_index=ifctele_getHistPlaceIndex(ifct_element,N_HISTORY-1);
					
					if(!strcmp(ifctele_getPlaceName(place_index),placeinput)){
						cnt++;
						ifctele_printElement(ifct_element);
					}
					//ifctele_getPlaceName(pIndex)==placeinput
					/*
				    i��° ����ü instance ����; //ifctdb_getData() �Լ� Ȱ��
        			i���� ����ü instance�� �ߺ�Ȯ�ε� ��� ��ȣ ����; // getHistPlaceIndex �Լ� Ȱ��
        			if ( �ߺ��� ��� ��ȣ�� ��ȯ�� ���ڿ��� �Էµ� ���ڿ��� ������)
                		i��° ����ü instance�� ���;}
								}*/
				//ifctele_getPlaceName(pIndex)
				}
				printf("\n");
				printf("There are %i patients detected in %s",cnt,placeinput);/*
				ifct_element = ifctdb_getData(pIndex);
				ifctele_getHistPlaceIndex(ifct_element);
				ifctele_getHistPlaceIndex(ifct_element,pIndex);
				//for(int i = 0; i <5; i++){
  				
				  if(countryName[i] == placeinput)
				int index=i;
				else if
				int index=-1}*/
				/*printf("There are %i patients detected in %s",0,place;}
				ifct_element = ifctdb_getData(place);
                
				printf("Place Name:%i\n",ifctele_getHistPlaceIndex(&ifct_element,pIndex));
				ifctele_getHistPlaceIndex(ifct_element,pIndex);*/
				break;
                }
            case MENU_AGE:
            	
                //printf("age:%i\n",ifctele_getAge(ifct_element));
                printf("minimal age: ");
                scanf("%i",&age_min);
                printf("maximal age: ");
                scanf("%i",&age_max);
                for(i=0;i<5;i++){
					ifct_element = ifctdb_getData(i);
                	if(age_min<=ifctele_getAge(ifct_element)&&ifctele_getAge(ifct_element)<=age_max){
				ifctele_printElement(ifct_element);}
				}
				
				break;
                
            case MENU_TRACK: //������� ����, ������ ������ 
            	//printf("Patient index :%i\n",);
            	/*
				for(i=0;i<5;i++){
				ifct_element = ifctdb_getData(i);
				//pIndex=ifctele_getHistPlaceIndex(ifct_element,i);
            	}*/
				printf("Patient index :");
				scanf("%i",&patient_now);
				
				while(0<=patient_now&&patient_now<=4){
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
						patient_fir=patient_now;}
					patient_now=patient_ifc;  
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
			
			/*PPT���� �˰��� �� ����, 
			1) ���� ������ ���
			2) 1�� ��, 2�� ���� ���� ����
			3) , �ẹ���� ����x 2////�� ��,  3�� ��, 4�� ���� �ẹ ����
			�迭�� N������ �ٸ� ȯ���� N+2������ ������ 
			��¥ ������ �迭[N]==�ٸ��迭[F]�� �κ��� ã�Ƴ��� 
			isMet(), trackInfester ��� 
			*/
			/*
            for (i=2;i<N_HISTORY;i++)// �Լ�¥�� 
				{
				����ȯ���� i��° �̵���� ���� ���;
				���� ���������� ���ȯ�� �̵���� ���;
				if (i��° �̵���� == ���ȯ�� �̵����)
				{
				�����ð� = i��° �̵���� ����;
				}
				}
				return �����ð�;        
                break;
                
            for (i��° ȯ��)
				{
				�����ð� = isMet(����ȯ��, i��° ȯ��);
				if ( �����ð�> 0) //�����ٸ�
				{
				if (���ݱ��� ȯ�� �� �����ð��� ���� �̸���?)
				{
				������ = i;
				}
				}
				}
				return ������;  
			*/
			
			break;	  
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
	
    return 0;
}
