/* 
Design and develop an integrated solution of a caterer billing system to run a small scale business in a day to day event transaction activities.
The solution provides complete details of the valid business details with user friendly environment along with the report details.


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

struct inventory_piece{
	char[25] name;
	float price;
	int status-flags;		//  1.2
};

struct invoice{
	
};


int load_inventory(char[] fn){
	
	return 1;
}
int save_inventory(char[] fn){
	
	return 1;
}

int save_invoice_log(struct inventory_piece a[]){
	return 1;
}

int billing(){
}


int main(){
	
	scanf();
	printf();
	return 0;
}
