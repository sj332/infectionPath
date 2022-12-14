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
}place_t;//place_t p[N_HISTORY];



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



static int ifs_cnt;



void* ifctele_genElement(int index, int age, unsigned int detected_time,
 int history_place[N_HISTORY])//구조체 하나 만드는 것 요청 함수, 포인터로 main에 
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
	//생성된 구조체의 포인터 반환
}



int ifctele_getHistPlaceIndex(void* obj, int index){ //index번째 장소 반환 함수  
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->history_place[index]);
}



int ifctele_getAge(void* obj){ //연령 함수  
	//구조체에서 나이의 값을 뺴줌
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->age);//나이 출력,포인터로 멤버에 접근
}



unsigned int ifctele_getinfestedTime(void* obj){ //감염시점 함수 
	ifs_ele_t*ptr=(ifs_ele_t*)obj;
	return(ptr->detected_time);
}



char*ifctele_getPlaceName(int placeIndex) //인덱스->나라명(영문) 함수 
{
	return countryName[placeIndex];
}



void ifctele_printElement(void* obj){ //프린트 함수  
	int i;
	ifs_ele_t*ptr = (ifs_ele_t*)obj;
	printf("index:%i\n",ptr->index);
	printf("age: %i\n",ptr->age);
	printf("time:%i\n",ptr->detected_time);
	printf("place: ");
	for (i=0;i<5;i++){ //이동 경로 상의 장소 출력
		printf("%s(%i)\t",ifctele_getPlaceName(ptr->history_place[i]),ptr->history_place[i]);
}	
	printf("\n");
}



int convertTimeToIndex(int time,int infestedTime){ //time에서의 장소 반환 함수 
	int Index=-1;
	
	if((time<=infestedTime)&&(time>(infestedTime-N_HISTORY)))
	{
		Index=N_HISTORY-(infestedTime-time)-1;
	}
	
	return Index;
} 


