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

//place_t배열문법으로 


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
	int index;//번호 >> 정수 
	int age;//나이 >> 정수 
	int detected_time;//감염 시점>> (n일째) 정수 
	place_t history_place[N_HISTORY];//감염 직전 이동 경로>>place_t 배열 정수 배열(enum 이용)(문자열로 저장X)[N_HISTORY]
} ifs_ele_t;


//static ifs_ele_t ifsarray[20];//링크드리스트,배열형태구조체
/*database c에 있음, 동적 메모리로 잡아서 이용
데이터 인캡슐레이션
 
*/

static int ifs_cnt;
//p=malloc(sizeof(ifs_le_t));


void* ifctele_genElement(int index, int age, unsigned int detected_time,
 int history_place[N_HISTORY])//구조체 하나 만드는 것 요청 함수, 포인터로 main에 
{
	ifs_ele_t* ptr;
	
	ptr=(void*)malloc(sizeof(ifs_ele_t)*N_HISTORY);
	ptr->index=index;
	ptr->age=age;
	ptr->detected_time=detected_time;
	/*ifsarray[ifs_cnt].index=index;//배열의 ifs_cnt번째 요소에 입력 내용 저장;
	ifsarray[ifs_cnt].age=age;
	ifsarray[ifs_cnt].detected_time=detected_time;*/
	
	int i;
	for(i=0;i<N_HISTORY;i++){
    	ptr->history_place[i]=history_place[i];
		ifs_cnt++; //리턴 사이에 free 넣지 마세요 
	}
	//return &ifsarray[ifs_cnt-1];
	return ptr;
	//(void*)생성된 구조체의 포인터 반환;
	//return (void*)&ifsarray[인덱스];
}


int ifctele_getHistPlaceIndex(void* obj, int index){ //인덱스 포함하여 수정 
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
	//구조체에서 나이의 값을 뺴줌
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->age);//나이 출력,포인터로 멤버에 접근 문법
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
	//번호, 나이, 감염시간 출력
	/*for (이동 경로 별)
		이동 경로 상의 장소 출력*/
}	
	printf("\n");
	return 0;
}
/*
int trackInfester(int index){
	for(i번째 환자)
	{
		만난시간=isMet(현재환자,i번째 환자);
		if(만난시간>0)//만났다면
		{
			if(지금까지 환자 중 만난시간이 가장 이른가?)
			{
				전파자=i; 
			}
		 } 
	}
	return 전파자;
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
		//현재환자의 i번쨰 이동장소 시점 계산;
		index=convertTimeToIndex(time,ptr->detected_time);
		
		//계산된 시점에서의 대상환자 이동장소 계산;
		if(ptr->history_place[i]==ptr->history_place[index]){
			met_time=time; 
		} 
		/*if(i번째 이동장소==대상환자 이동장소){
			만난시간=i번쨰 이동장소 시점; 
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
