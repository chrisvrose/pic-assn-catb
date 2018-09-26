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
	datetime ptime;
	inventory_piece *pieces;
	int piece_length;
	float total_profit; 
} invoice;


int save_invoice_log(inventory_piece a[],char location[]){
	return 1;
}

int load_invoice_log(char location[]){
}

int billing(){
}


int main(){
	printf("\f" MOTD "\nOptions:");
	// Stuff
	return 0;
}
