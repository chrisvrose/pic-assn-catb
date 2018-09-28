/*
Design and develop an integrated solution of a caterer billing system to run a small scale business in a day to day event transaction activities.
The solution provides complete details of the valid business details with user friendly environment along with the report details.


Start
	Menu:
		1. Set Profits ( default 10% )		- Done
		2. Billing				- 
		3. View saved invoice			-
		4. Generate reports			-
		5. View saved report			-



Input stuff:
	Billing invoices
	Profit Percentage (Setup as default 10%)
		
Structure definitions: 
Output stuff:


*/


#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "main.h"

#ifdef _WIN32
#include<Windows.h>
#else
#include<unistd.h>
#endif

#define ITEM_LEN 25
#define MOTD "Have a nice day!"
#define MAX_ITEM_LIST 50





int set_profitper(float* p){
	int c;

	printf("\nCurrent profit percentage: %0.2f\n",(*p)*100 );
	printf("Do you want to change it?(Y-1/N-0)\n:");
	//fflush(stdin);fflush(stdout);
	scanf("%d",&c);
	if(c){
		printf("Set profit percentage (Without %% symbol)\n:",*p);
		scanf("%f",p);
		(*p)/=100.0;
		if(abs(*p)<=1.0){
			printf("Set to: %.2f %%",(*p)*100);
			return 1;
		}
		else{
			printf("Range -> 0 - 100. Retry.\n");
			return set_profitper(p);
		}
	}else{
		return 0;
	}
}


int make_invoice(float profit_percentage){

	return 1;
}





int save_invoice_log(inventory_piece a[],char location[]){
	return 1;
}

int load_invoice_log(char location[]){
	return 1;
}

int billing(){
	return 1;
}

void u_sleep(){
	#ifdef _WIN32
		Sleep(1);
	#else
		sleep(1);
	#endif
}


int main(){
	int choice,flag=1;
	float p = 0.1;
	while(flag){
		printf("\n\nMOTD: " MOTD "\nOptions:\n1. Set Profit percentage\n2. Billing\n3. View saved invoice\n4. Generate report\n5.View saved report\n6. Exit\n:");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				// Profit percentages
				set_profitper(&p);
			break;
			case 2:
				// Creating invoices
				printf("\nStart Billing");
				make_invoice(p);
			break;
			case 3:
				// View saved invoices
			break;
			case 4:
				// Generate reports
			break;
			case 5:
				// VIew saved reports
			break;
			case 6:
				//send request for exit
				flag = 0;
			break;
			default:
				printf("Wrong Input - %d",choice);
				fflush(stdout);		//Flush output to prevent race
				u_sleep(1);
		}
	}
	// Stuff
	return 0;
}
