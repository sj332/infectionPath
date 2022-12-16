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
                
            case MENU_TRACK: //������� ����, ������ ������ 
            	//printf("Patient index :%i\n",);
			
			
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
