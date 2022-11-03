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

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
	
	int menu_selection;
    void *ifct_element;
    FILE* fp=NULL;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //------------- 1. loading patient info file ------------------------------
    
	argv=fopen("/Users/user/Desktop/infectionPath/patientInfo_sample.txt","r");//1-1. FILE pointer open
    
	
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
	
	
	fclose(fp);
	
	return 0;
}
