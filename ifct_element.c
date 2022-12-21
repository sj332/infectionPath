//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

//place_t�迭�������� 


typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
}place_t;

//place_t p[N_HISTORY];

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};


typedef struct ifs_ele{
	int index;//��ȣ >> ���� 
	int age;//���� >> ���� 
	int detected_time;//���� ����>> (n��°) ���� 
	place_t history_place[N_HISTORY];//���� ���� �̵� ���>>place_t �迭 ���� �迭(enum �̿�)(���ڿ��� ����X)[N_HISTORY]
} ifs_ele_t;


//static ifs_ele_t ifsarray[20];//��ũ�帮��Ʈ,�迭���±���ü
/*database c�� ����, ���� �޸𸮷� ��Ƽ� �̿�
������ ��ĸ�����̼�
 
*/

static int ifs_cnt;



void* ifctele_genElement(int index, int age, unsigned int detected_time,
 int history_place[N_HISTORY])//����ü �ϳ� ����� �� ��û �Լ�, �����ͷ� main�� 
{
	ifs_ele_t* ptr;
	
	ptr=(void*)malloc(sizeof(ifs_ele_t)*N_HISTORY);
	ptr->index=index;
	ptr->age=age;
	ptr->detected_time=detected_time;
	
	int i;
	for(i=0;i<N_HISTORY;i++){
    	ptr->history_place[i]=history_place[i];
		ifs_cnt++; 
	}
	return ptr;
	//������ ����ü�� ������ ��ȯ
}


int ifctele_getHistPlaceIndex(void* obj, int index){
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->history_place[index]);
}


int ifctele_getAge(void* obj){
	//����ü���� ������ ���� ����
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->age);//���� ���,�����ͷ� ����� ����
}


unsigned int ifctele_getinfestedTime(void* obj){
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->detected_time);
}

char*ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}

void ifctele_printElement(void* obj){
	int i;
	ifs_ele_t*ptr = (ifs_ele_t*)obj;
	printf("index:%i\n",ptr->index);
	printf("age: %i\n",ptr->age);
	printf("time:%i\n",ptr->detected_time);
	printf("place: ");
	for (i=0;i<5;i++){ //�̵� ��� ���� ��� ���
		printf("%s(%i)\t",ifctele_getPlaceName(ptr->history_place[i]),ptr->history_place[i]);
}	
	printf("\n");
}

int convertTimeToIndex(int time,int infestedTime){
	int Index=-1;
	
	if((time<=infestedTime)&&(time>(infestedTime-N_HISTORY)))
	{
		Index=N_HISTORY-(infestedTime-time)-1;
	}
	
	return Index;
} /*
int isMet(int index,int index_i){
	int i;
	int met_time;	
	int time;
	int time_i;
	int place;
	int place_ifc;
	void *ifct_element;
	void *ifct_element_i;
	ifct_element = ifctdb_getData(index);
	ifct_element_i = ifctdb_getData(index_i);
	
	for(i=2;i<N_HISTORY;i++){
	
		time=(ifctele_getinfestedTime(ifct_element)-(N_HISTORY-i)+1);
		time_i=ifctele_getinfestedTime(ifct_element_i);
		index_i=convertTimeToIndex((int)time,(int)time_i);
		place_ifc=ifctele_getHistPlaceIndex(ifct_element_i,index_i);
		
		//ifctele_getHistPlaceIndex(ifct_element,time)
		
		//����ȯ���� i���� �̵���� ���� ���
		//���� ���������� ���ȯ�� �̵���� ���;
		if(ifctele_getHistPlaceIndex(ifct_element,i+1)==place_ifc)
		{
			met_time=time-i;
		} 
		
	}printf("met time %i",met_time);
	return met_time; }*/
