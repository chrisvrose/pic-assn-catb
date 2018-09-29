/*
Design and develop an integrated solution of a caterer billing system to run a small scale business in a day to day event transaction activities.
The solution provides complete details of the valid business details with user friendly environment along with the report details.


Start
	Menu:
	1. 
	2. 
	3. 
	4. 
	5. 
	6. 
	7. 
	8. Exit



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
menu_list menu;

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

// making menulist files
int write_menulist(){
	FILE *fp = fopen("menu.details","wb+");
	nocbreak();
	
	retry_menu_list:
	printw("\nNumber of items in menu\n:");
	refresh();
	scanw("%d",&(menu.num_menu));
	if(menu.num_menu>128)
		goto retry_menu_list;
	
	
	for(int i=0;i<menu.num_menu;i++){
		printw("Item %d",(i+1));
		
		printw("\nEnter item name\n:");
		refresh();
		scanw("%s",menu.pieces[i].name);
		
		printw("\nEnter item price and production cost\n:");
		refresh();
		scanw("%f %f",&(menu.pieces[i].sprice),&(menu.pieces[i].pcost) );
		
	}
	
	fwrite(&menu,sizeof(menu_list),1,fp);
	fclose(fp);
	
	cbreak();
}


int read_menulist(){
	FILE *fp = fopen("menu.details","rb");
	fread(&menu,sizeof(menu_list),1,fp);
	fclose(fp);
	for(int i=0;i<menu.num_menu;i++){
		printw("\n%s %f",menu.pieces[i].name,menu.pieces[i].pcost);
	}
	refresh();
	
}





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
				read_menulist();
			break;
			case '5':
				// View saved reports
				write_menulist();
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
