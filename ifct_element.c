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


static ifs_ele_t ifsarray[20];//링크드리스트,배열형태구조체
static int ifs_cnt;

/*
void* ifsele_genElement( 감염환자 정보들 )
{
	ifsarray[ifs_cnt] 배열의 ifs_cnt번째 요소에 입력 내용 저장;
	ifs_cnt++;
	
	(void*)생성된 구조체의 포인터 반환;
}*/

 /*
int function_{
	ifs_ele_t ifs1;
} 
*/

int ifctele_getAge(void* obj){
	//구조체에서 나이의 값을 뺴줌
	ifs_ele_t*strPtr=(ifs_ele_t*)obj;
	return(strPtr->age);//나이 출력,포인터로 멤버에 접근 문법
}

int ifctele_getHistPlaceIndex(void* obj, int index){
	ifs_ele_t*strPtr=(ifs_ele_t*)obj;
	return(strPtr->index);
}
unsigned int ifctele_getinfestedTime(void* obj){
	ifs_ele_t*strPtr=(ifs_ele_t*)obj;
	return(strPtr->detected_time);
}

char*ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}

/*
void ifsele_printElement()
{
	ifctele_t* strPtr = (obj를 적절히 형변환);
	for (ifs_cnt 반복)
{
	번호, 나이, 감염시간 출력
	for (이동 경로 별)
		이동 경로 상의 장소 출력
}
*/
