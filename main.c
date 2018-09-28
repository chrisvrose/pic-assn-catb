/*
Design and develop an integrated solution of a caterer billing system to run a small scale business in a day to day event transaction activities.
The solution provides complete details of the valid business details with user friendly environment along with the report details.


Start
	Menu:
		1. Set Profits ( default 10% )
		2. Billing
		3. View saved invoice
		3. Generate reports
		4. View saved report



Input stuff:
	Billing invoices
	Profit Percentage (Setup as default 10%)
	
	
	
	
Structure definitions: 

Output stuff:








1.1 Sections:
		- Admin sections to add/modify products
		- Send invoices to clients
		- Log invoices
		- Generate financial reports
		-

1.2 - Status flags for every menu item in the inventory:
		321 in decimal
		- 3: Restriction (Age)
		- 2: Unlisted
		- 1: Availability
	
*/


#include<stdio.h>

#ifdef _WIN32
#include<Windows.h>
#else
#include<unistd.h>
#endif

#define ITEM_LEN 25
#define MOTD "Have a nice day!"
#define MAX_ITEM_LIST 50

typedef struct{
	int date[3];
	int time[2];
} datetime;


typedef struct{
	char name[25];
	float price;
} inventory_piece;

typedef struct{
	char recep[25];
	datetime ptime;
	inventory_piece *pieces;
	int piece_length;
	float profit_percentage;
} invoice;


int make_invoice(){
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
	int choice,p,flag=1;
	while(flag){
		printf("\n\n" MOTD "\nOptions:\n1. Set Profit percentage\n2. Billing\n3. View saved invoice\n4. View saved report\n5. Exit\n:");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				
			break;
			case 2:
				
			break;
			case 3:
				
			break;
			case 4:
				
			break;
			case 5:
				flag = 0;
				break;
			break;
			case 6:
			default:
				printf("Wrong Input - %d",choice);
				fflush(stdout);		//Flush output to prevent race
				u_sleep(1);
		}
	}
	// Stuff
	return 0;
}
