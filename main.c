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

int isMet(int index,int index_i){ //�� ȯ���� ���� ���� �Լ� 
	int i;
	int met_time; //������ ����	
	int time; //���� ȯ���� i���� �̵� ����  
	int time_i; //��� ȯ���� ���� ���� 
	int place_ifc; //��� ȯ���� index_i ��° ��� 
	int *ifct_element; //index�� ������ 
	int *ifct_element_i; //index_i�� ������ 
	ifct_element = ifctdb_getData(index); 
	ifct_element_i = ifctdb_getData(index_i);
	
	for(i=2;i<N_HISTORY;i++){
	
		time=(ifctele_getinfestedTime(ifct_element)-(N_HISTORY-i)-1); //����ȯ���� i���� �̵���� ���� ���
		time_i=ifctele_getinfestedTime(ifct_element_i); //��� ȯ���� ���� ���� ���  
		index_i=convertTimeToIndex((int)time,(int)time_i); //���� ���������� ���ȯ�� �̵���� ���
		place_ifc=ifctele_getHistPlaceIndex(ifct_element_i,index_i); //��� ȯ���� index_i��° �̵���� ��� 
		
		if(ifctele_getHistPlaceIndex(ifct_element,i)==place_ifc) //���� ȯ���� i��°�� ��� ȯ���� index_i��°�� ���� ��� 
		{
			met_time=time;
		}}
	return met_time; }

int trackInfester(int patient_no, int *dectected_time, int *place){ //���� ȯ�� 
	int i;
	int j;
	int met_time;
	int min_time[10];
	int patient_ifc=10;
	for(i=0;i<5;i++)//i��° ȯ�� 
	{
		
		met_time=isMet(patient_no,i);
		
		if(met_time>0&&met_time<100)//�����ٸ�
		{
			min_time[i]=met_time;
			for(j=0;j<5;j++){
				if(met_time<=min_time[j])
			{
					patient_ifc=i;
			}
				
		 } 
	}}
	return patient_ifc;
	
}



int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    int i;
    int age_min; //#3 ���� ��� ���� 
    int age_max; //#3 ���� ��� ���� 
    ifctele_getPlaceName(placeHist[1]);
	int patient_now=10;
	int patient_ifc=10;
	int patient_fir=10;
	int place_index[30];
	int detected_time; 
	int *timetest=&detected_time;
	int *placetest=&place_index[30];   
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
    while(3==fscanf(fp,"%d %d %d",&pIndex,&age,&time))  //3���� �б� 
    {	
    	int i;
    	for(i=0;i<5;i++){
			fscanf(fp,"%d",&placeHist[i]);
    		
    		
		}
		ifct_element=ifctele_genElement(pIndex,age,time,placeHist);
    	ifctdb_addTail(ifct_element); //��ũ�帮��Ʈ�� ȯ�� ���� ���� 
	}
	
	//isdb_tail�� ���ο� ���� 
	
	
	//#endif  
	
	
    //1-3. FILE pointer close
    fclose(fp);

    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");    //�˰���      //MENU_TRACK
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
                
            case MENU_PATIENT: //n��° ȯ�� ������ ��������, printelement�� ��� 
                
                printf("enter patient index: ");
				scanf("%i",&pIndex);				
				ifct_element = ifctdb_getData(pIndex);
				ifctele_printElement(ifct_element);
				break;//�����͸� �ѱ� 
                
            case MENU_PLACE: //������ҿ� ������ ����ϰ� �ƴϸ� skip 
            	{
				
				int i;
				char placeinput[40];//����� �迭  
                printf("Place Name: ");
				scanf("%s",&placeinput);
				int place_index;
				int cnt=0;
				for(i=0;i<5;i++)//ȯ�� ����ŭ �ݺ�  
				{
					ifct_element = ifctdb_getData(i);
					place_index=ifctele_getHistPlaceIndex(ifct_element,N_HISTORY-1); 
					
					if(!strcmp(ifctele_getPlaceName(place_index),placeinput))//���ڿ� ����� �� 
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
                scanf("%i",&age_min); //�ּ� ���� �Է� 
                printf("maximal age: ");
                scanf("%i",&age_max); //�ִ� ���� �Է� 
                for(i=0;i<5;i++){ //ȯ�� ����ŭ �ݺ� 
					ifct_element = ifctdb_getData(i);
                	if(age_min<=ifctele_getAge(ifct_element)&&ifctele_getAge(ifct_element)<=age_max)//���� ������ �� 
					{ifctele_printElement(ifct_element);}
				}
				
				break;
                
            case MENU_TRACK: //������� ����, ������ ������ 
				{printf("Patient index :");
				scanf("%i",&patient_now);
				ifct_element = ifctdb_getData(patient_now);
				detected_time=ifctele_getinfestedTime(ifct_element);
				for(i=0;i<N_HISTORY;i++){
					place_index[i]=ifctele_getHistPlaceIndex(ifct_element,i);}
				int *timetest=detected_time; 
				int *placetest=place_index[5];
			
						
				while((0<=(int)patient_now)&&((int)patient_now<=4)){
					
					patient_ifc=trackInfester((int)patient_now,timetest,placetest); //����ȯ���� ������ ã�� 	
					if(0<=(int)patient_ifc&&(int)patient_ifc<=4){
						printf("patient %i is infected by %i \n",patient_now, patient_ifc);
						if((int)patient_fir==(int)patient_ifc){
							printf("The first infector of %i is %i\n",patient_now,patient_fir);
							patient_now=patient_ifc;
							break;
					}}
					else{
						patient_fir=patient_now;
						printf("%i is the first infector!!\n",patient_fir); 
						break;}	
					}
				
		 		}
			break;	  
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
	
    return 0;
}
