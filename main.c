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
		6. Load inventory
		7. Make and save inventory

Input stuff:
	Billing invoices
	Profit Percentage (Setup as default 10%)
	
Structure definitions: 
Output stuff:

Functions:
	- Read caterer details
	- Read inventory

*/


#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ncurses.h>

#include "main.h"

#ifdef _WIN32
#include<Windows.h>
#define u_sleep(x) Sleep(x)
#else
#include<unistd.h>
#define u_sleep(x) sleep(x)
#endif


cat_details company_details;

void read_cat_det(){
	
	FILE *fp = fopen("company.details","rb");
	fread(&company_details,sizeof(cat_details),1,fp);
	fclose(fp);
	printw("\n%s %f",company_details.name,company_details.taxp);
	refresh();
	
}

int write_cat_det(){
	FILE *fp = fopen("company.details","wb+");
	clear();
	nocbreak();

	printw("Enter company name\n:");
	refresh();
	scanw("%s",company_details.name);

	printw("Enter Tax%%\n:");
	refresh();
	scanw("%f",&(company_details.taxp));
	cbreak();
	
	fwrite(&company_details,sizeof(cat_details),1,fp);
	fclose(fp);
	return 1;
}

//read_inventory






/*int set_profitper(float* p){
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
}*/


int make_invoice(){
	printw("%d %d",sizeof(invoice),sizeof(inventory_piece));
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


int main(){
	int choice,flag=1;
	initscr();		//init ncurses
	cbreak();
	while(flag){
		clear();
		printw("\n\nMOTD: " MOTD "\nOptions:\n1. Set Profit percentage\n2. Billing\n3. View saved invoice\n4. Generate report\n5.View saved report\n8. Exit\n:");
		refresh();
		choice = getch();
		switch(choice){
			case '1':
				// Profit percentages
				//set_profitper(&p);
			break;
			case '2':
				// Creating invoices
				printw("\nStart Billing");
				make_invoice();
			break;
			case '3':
				// View saved invoices
			break;
			case '4':
				// Generate reports
			break;
			case '5':
				// View saved reports
			break;
			case '6':
				// Load inventory
				read_cat_det();
			break;
			case '7':
				// Make and save inventory
				write_cat_det();
			break;
			case '8':
				//send request for exit
				flag = 0;
			break;
			default:
				printw("\nWrong Input - %d",choice);
				
		}
		refresh();
		printw("\nPress key to continue...");getch();
	}
	clear();
	printw("\nExiting. Press any key");
	refresh();
	getch();
	endwin();
	// Stuff
	return 0;
}
