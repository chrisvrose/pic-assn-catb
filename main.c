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
#include<stdlib.h>
#include<math.h>
#include<ncurses.h>
#include<time.h>

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
invoice last_invoice;
char invoice_name_list[20][256];


// Caterer details I/O

void print_cat_det(){
	printw("\n%s %f",company_details.name,company_details.taxp);
	refresh();
}

void read_cat_det(){
	
	FILE *fp = fopen("company.details","rb");
	fread(&company_details,sizeof(cat_details),1,fp);
	fclose(fp);
	print_cat_det();
	
}

void write_cat_det(){
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
}

// Menulist I/O

void write_menulist(){
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

void print_menulist(){
	for(int i=0;i<menu.num_menu;i++){
		printw("\n%s %f",menu.pieces[i].name,menu.pieces[i].pcost);
	}
	refresh();
}

void read_menulist(){
	FILE *fp = fopen("menu.details","rb");
	fread(&menu,sizeof(menu_list),1,fp);
	fclose(fp);
	
	print_menulist();
}

// Billing invoices

int input_item_number(){
	int input=-1;
	//print menu_list
	
	printw("\n");
	for(int i=0;i<menu.num_menu;i++){
		printw("\n%d. \t%s\t- %.2f",(i+1),menu.pieces[i].name,menu.pieces[i].sprice);
		refresh();
	}
	refresh();
	scanw("%d",&input);
	//cbreak();
	return input;
}


void write_invoice(){
	char fn[20];int i,buffer,flag;
	time_t t = time(NULL);
	struct tm *ct = localtime(&t);
	sprintf(fn,"%d%02d%02d %02d%02d%02d.bill",ct->tm_year+1900, ct->tm_mon + 1, ct->tm_mday, ct->tm_hour, ct->tm_min, ct->tm_sec);
	// last_invoice - Structure to store last generated invoice
	//nocbreak();		// prepare for input
	
	//Receipt recipient
	printw("Invoice Recipient\n:");
	refresh();
	scanw("%s",last_invoice.recep);
	
	
	for(i=0,flag=1;i<128&&flag;i++){
		/*printw();
		refresh();
		scanw();
		
		printw();
		refresh();
		scanw();*/
		if((buffer = input_item_number()) != -1){
			last_invoice.item_numbers[i][0] = buffer;
		
			printw("\nEnter item quantity\n:");
			refresh();
			scanw("%d", &(last_invoice.item_numbers[i][0]) );
		}
		else flag=0;
	}
	
	printw("\n%d",i);
	
	refresh();
	//nocbreak();
	
	//FILE *fp = fopen(fn,"wb+");
	//printw("\n%s\n",fn);
}                                                   
void print_invoice(){
}

void read_invoice(){
	print_invoice();
}



int main(){
	int choice,flag=1;
	initscr();		//init ncurses
	//cbreak();
	while(flag){
		clear();
		printw("\n\nMOTD: " MOTD "\nOptions:\n1. Set Profit percentage\n2. Billing\n3. View saved invoice\n4. Generate report\n5.View saved report\n8. Exit\n:");
		refresh();
		choice = getch();
		switch(choice){
			case '1':
				//set_profitper(&p);
			break;
			case '2':
				// Creating invoices
				printw("\nStart Billing");
				//make_invoice();
			break;
			case '3':
				write_invoice();
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
