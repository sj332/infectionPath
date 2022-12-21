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
//p=malloc(sizeof(ifs_le_t));


void* ifctele_genElement(int index, int age, unsigned int detected_time,
 int history_place[N_HISTORY])//����ü �ϳ� ����� �� ��û �Լ�, �����ͷ� main�� 
{
	ifs_ele_t* ptr;
	
	ptr=(void*)malloc(sizeof(ifs_ele_t)*N_HISTORY);
	ptr->index=index;
	ptr->age=age;
	ptr->detected_time=detected_time;
	/*ifsarray[ifs_cnt].index=index;//�迭�� ifs_cnt��° ��ҿ� �Է� ���� ����;
	ifsarray[ifs_cnt].age=age;
	ifsarray[ifs_cnt].detected_time=detected_time;*/
	
	int i;
	for(i=0;i<N_HISTORY;i++){
    	ptr->history_place[i]=history_place[i];
		ifs_cnt++; //���� ���̿� free ���� ������ 
	}
	//return &ifsarray[ifs_cnt-1];
	return ptr;
	//(void*)������ ����ü�� ������ ��ȯ;
	//return (void*)&ifsarray[�ε���];
}


int ifctele_getHistPlaceIndex(void* obj, int index){ //�ε��� �����Ͽ� ���� 
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	/*
	char ppp;
	for(i=0;i<5;i++)){
	if index==ptr->history_place[4]){
			ifctele_printElement(ptr->index)
			cnt++}*/
	//ifctele_getPlaceName(ptr->history_place[4])
	
	/*		
	else{
		printf("There are %i patients detected in %s",cnt,ifctele_getPlaceName(ptr->index));}
	*/
	//int i;
	return(ptr->history_place[index]);
}
/*
	for(i=0;i<40;i++){  ///ERROR
		if(ptr->history_place[4]==i){
			index=i;
		}
	}
	return(index);*/
 /*
int function_{
	ifs_ele_t ifs1;
} 
*/

int ifctele_getAge(void* obj){
	//����ü���� ������ ���� ����
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->age);//���� ���,�����ͷ� ����� ���� ����
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
	for (i=0;i<5;i++){ //ifs_cnt
		printf("%s(%i)\t",ifctele_getPlaceName(ptr->history_place[i]),ptr->history_place[i]);
	//��ȣ, ����, �����ð� ���
	/*for (�̵� ��� ��)
		�̵� ��� ���� ��� ���*/
}	
	printf("\n");
	return 0;
}
/*
int trackInfester(int index){
	for(i��° ȯ��)
	{
		�����ð�=isMet(����ȯ��,i��° ȯ��);
		if(�����ð�>0)//�����ٸ�
		{
			if(���ݱ��� ȯ�� �� �����ð��� ���� �̸���?)
			{
				������=i; 
			}
		 } 
	}
	return ������;
}*/
/*
int isMet(void* obj,int index,int index_i){
	int i;
	ifs_ele_t*ptr = (ifs_ele_t*)obj;
	int met_time;	
	
	for(i=2;i<N_HISTORY;i++){
		
		//int index;
		
		int time;
		
		printf("I");
		
		time=ptr->detected_time-(N_HISTORY-i);
		//����ȯ���� i���� �̵���� ���� ���;
		index=convertTimeToIndex(time,ptr->detected_time);
		
		//���� ���������� ���ȯ�� �̵���� ���;
		if(ptr->history_place[i]==ptr->history_place[index]){
			met_time=time; 
		} 
		/*if(i��° �̵����==���ȯ�� �̵����){
			�����ð�=i���� �̵���� ����; 
		} */
	/*
	return (met_time); 
}*/
/*
int convertTimeToIndex(int time,int infestedTime){
	int index=-1;
	
	if(time<=infestedTime&&time>infestedTime-N_HISTORY)
	{
		index=N_HISTORY-(infestedTime-time)-1;
	}
	
	return index;
} */
