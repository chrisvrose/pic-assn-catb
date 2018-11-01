/*
Design and develop an integrated solution of a caterer billing system to run a small scale business in a day to day event transaction activities.
The solution provides complete details of the valid business details with user friendly environment along with the report details.


Start
	Menu:
	1. Save Caterer Info
	2. Read Caterer Info
	3. Save Menu List
	4. View Menu List
	5. Make invoice
	6. Load and view invoice
	7. Generate report
	0. Exit

Other non standard functions used:
	printw(): ncurses function used to print to screen. Identical to printf()
	refresh(): ncurses function, just flushes all pending printw onto the screen
	scanw(): ncurses function used to take input. Identical to scanf()
	getstr(): ncurses function that returns a string that has been taken as input, including spaces
	getch(): ncurses function that takes a single character input

	
	
*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ncurses.h>
#include<time.h>

#include "main.h"

scat_details cat_details;
smenu menu;
sinvoice last_invoice;
sinvoice_list invoice_list;


int exists(const char *fname){
	FILE *file;
	if ((file = fopen(fname, "r")))
	{
		fclose(file);
		return 1;
    }
    return 0;
}



int check_substreq(char *str1,char *str2,int len_start,int len_end){
	int fl = 1;
	for(int i=len_start;i<len_end;i++){
		if(str1[i]!=str2[i]){
			fl = 0;
			break;
		}
	}
	
	return fl;
}


// Caterer details I/O

void print_cat_det(){
	printw("\nCompany Name:%s\nTax Percent:%.2f",cat_details.name,cat_details.taxp);
	refresh();
}

int read_cat_det(){
	if(exists("company.details")){
		FILE *fp = fopen("company.details","rb");
		fread(&cat_details,sizeof(scat_details),1,fp);
		fclose(fp);
		return 1;
	}
	else return 0;
	//print_cat_det();
	
}

void write_cat_det(){
	FILE *fp = fopen("company.details","wb+");
	clear();
	//nocbreak();

	printw("Enter company name\n:");
	refresh();
	getstr(cat_details.name);

	printw("Enter Tax%%\n:");
	refresh();
	scanw("%f",&(cat_details.taxp));
	//cbreak();
	
	fwrite(&cat_details,sizeof(scat_details),1,fp);
	fclose(fp);
}

// Menulist I/O

void write_menulist(){
	//FILE *fp = fopen("menu.details","wb+");
	//nocbreak();
	
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
		getstr(menu.pieces[i].name);
		
		printw("\nEnter item price and production cost\n:");
		refresh();
		scanw("%f %f",&(menu.pieces[i].sprice),&(menu.pieces[i].pcost) );
		
	}
	FILE *fp = fopen("menu.details","wb+");
	fwrite(&menu,sizeof(smenu),1,fp);
	fclose(fp);
	
	//cbreak();
}

void print_menulist(){
	printw("\nItem name\tPrice\tProduction");
	for(int i=0;i<menu.num_menu;i++){
		printw("\n%s\t%.2f\t%.2f",menu.pieces[i].name,menu.pieces[i].sprice,menu.pieces[i].pcost);
	}
	refresh();
}

int read_menulist(){
	if(exists("menu.details")){
		FILE *fp = fopen("menu.details","rb");
		fread(&menu,sizeof(smenu),1,fp);
		fclose(fp);
		return 1;
	}
	else return 0;
	
	//print_menulist();
}

// Random required functions

int input_item_number(){
	int input=-1;
	//print smenu
	clear();
	
	printw("Enter items in menu(Enter 0 to exit):\n");
	printw("\nItem name\tPrice");
	for(int i=0;i<menu.num_menu;i++){
		printw("\n%d. \t%s\t- %.2f",(i+1),menu.pieces[i].name,menu.pieces[i].sprice);
		refresh();
	}
	printw("\n:");
	refresh();
	
	scanw("%d",&input);
	//cbreak();
	return input;
}

int read_invoice_list(){
	if(exists("bill_list.details")){
		FILE *fp = fopen("bill_list.details","rb+");
		fread(&invoice_list,sizeof(sinvoice_list),1,fp);
		fclose(fp);
		return 1;
	}
	else return 0;
}


// Billing invoices

int write_invoice(){
	char fn[32];int i,buffer,flag;
	time_t t = time(NULL);
	struct tm *ct = localtime(&t);
	sprintf(fn,"%d%02d%02d %02d%02d%02d.bill",ct->tm_year+1900, ct->tm_mon + 1, ct->tm_mday, ct->tm_hour, ct->tm_min, ct->tm_sec);
	// last_invoice - Structure to store last generated invoice
	
	//Receipt recipient
	printw("\nInvoice Recipient\n:");
	refresh();
	getstr(last_invoice.recep);
	
	printw("Enter item numbers(0 to exit):\n");
	for(i=0;i<128&&(buffer);i++){
		if(buffer = input_item_number()){		// Can be anything but zero
			last_invoice.item_numbers[i][0] = buffer-1;
		
			printw("\nEnter item quantity\n:");
			refresh();
			scanw("%d", &(last_invoice.item_numbers[i][1]) );
		}
	}
	
	printw("\nNumber of items ordered: %d",i-1);
	last_invoice.pieces_len = i-1;
	
	if(last_invoice.pieces_len==0) {
		printw("\nNothing in bill. Cancelling order");
		refresh();
		return 0;
	}
	
	FILE *fp = fopen(fn,"wb+");
	fwrite(&last_invoice,sizeof(sinvoice),1,fp);
	fclose(fp);
	
	
	if(!exists("bill_list.details"))
		invoice_list.num_invoice = 0; 
	else
		read_invoice_list();
	
	//write down this new stuff
	//strcpy(invoice_list.invoice_name_list[invoice_list.num_invoice],fn);
	for(int i=0;i<32;i++) invoice_list.invoice_name_list[invoice_list.num_invoice][i] = fn[i];
	invoice_list.num_invoice+=1;
	
	fp = fopen("bill_list.details","wb+");
	fwrite(&invoice_list,sizeof(sinvoice_list),1,fp);
	fclose(fp);
	//printw("\n%s\n",fn);
	
	printw("\nBill saved and updated");
	refresh();
	
	return last_invoice.pieces_len;
}

int read_invoice(){
	clear();int choice;
	
	if(!exists("bill_list.details"))
		invoice_list.num_invoice = 0; 
	else
		read_invoice_list();
	
	if(invoice_list.num_invoice == 0){
		printw("\nNo invoices. Try again");
		/* refresh(); */
	}
	
	
	printw("Choose invoice to print:\n");
	for(int i=0;i<invoice_list.num_invoice;i++){
		printw("\n%d. %s",i+1,invoice_list.invoice_name_list[i]);
		refresh();
	}
	printw("\n:");
	refresh();
	scanw("%d",&choice);
	
	FILE *fp = fopen(invoice_list.invoice_name_list[choice-1],"rb");
	fread(&last_invoice,sizeof(sinvoice),1,fp);
	fclose(fp);
	return 1;
}

void print_invoice(){
	//print_invoice();
	printw("\n%s\n",last_invoice.recep);float total_price=0;
	printw("Items:\n");
	refresh();
	for(int i=0;i<last_invoice.pieces_len;i++){
		total_price += menu.pieces[ last_invoice.item_numbers[i][0] ].sprice * last_invoice.item_numbers[i][1];		//Price * quantity
		// Print corresponding menu items
		printw("\n%d.\t%s\t - %.2f * %d",(i+1) , menu.pieces[ last_invoice.item_numbers[i][0] ].name , menu.pieces[ last_invoice.item_numbers[i][0] ].sprice , last_invoice.item_numbers[i][1] );
		refresh();
	}
	printw("\nBilled Amount:%.2f",total_price);
}

//Print Report

int report(){
	int choice;char fn[32];
	int str_datebounds[] = {0,4,6,8};
	clear();
	time_t t = time(NULL);
	struct tm *ct = localtime(&t);
	sprintf(fn,"%d%02d%02d %02d%02d%02d.bill",ct->tm_year+1900, ct->tm_mon + 1, ct->tm_mday, ct->tm_hour, ct->tm_min, ct->tm_sec);		//store the current bill date if it were to be generated, in fn
	
	
	int num_items=0;
	float total_sprice=0,total_profit=0,total_pcost=0,total_tax=0;
	
	printw("\nChoose interval:\n1. Year\n2. Month\n3. Day\n:");
	refresh();
	scanw("%d",&choice);
	if(choice>3&&choice<0){
		printw("\nError.Retry");
		refresh();
		return 0;
	}
	
	
	for(int i=0;i<invoice_list.num_invoice;i++){
		if( check_substreq(invoice_list.invoice_name_list[i],fn,0,str_datebounds[choice]) ){
			
			FILE *fp = fopen(invoice_list.invoice_name_list[i],"rb");
			fread(&last_invoice,sizeof(sinvoice),1,fp);
			for(int j=0;j<last_invoice.pieces_len;j++){
				total_sprice+= menu.pieces[ last_invoice.item_numbers[j][0] ].sprice * last_invoice.item_numbers[j][1];
				total_pcost += menu.pieces[ last_invoice.item_numbers[j][0] ].pcost * last_invoice.item_numbers[j][1];
				num_items += last_invoice.item_numbers[j][1];
			}
			fclose(fp);
		}
	}
	
	if(num_items != 0){
		total_tax = total_sprice*cat_details.taxp/100;
		total_profit = total_sprice+total_tax-total_pcost;
		printw("\nTotalling - \nNumber of items:%d \nTotal tax:%f \nTotal Production Costs:%f \nTotal Sales:%f \nTotal Profit", num_items, total_tax , total_pcost , total_sprice ,total_profit);
	}
	else{
		printw("\nNo items. Try a wider range, maybe.");
	}
	
	refresh();
	return 1;
}


int main(){
	int choice,flag=1,flag_hasloadedmenu,flag_hasloadedcat,flag_hasloadedinvoicelist;
	initscr();		//init ncurses
	
	//Init stuff from memory
	flag_hasloadedmenu=read_menulist();
	flag_hasloadedcat=read_cat_det();
	flag_hasloadedinvoicelist = read_invoice_list();
	
	//cbreak();
	while(flag){
		clear();
		printw("\n\nMOTD: " MOTD "\nOptions:\n1. Save Caterer Info\n2. Read Caterer Info\n3. Save Menu List\n4. View Menu List\n5. Make invoice\n6. Load and view invoice\n7. Generate report\n0. Exit\n:");
		refresh();
		choice = getch();
		switch(choice){
			case '1':
				// Write caterer details
				write_cat_det();
			break;
			case '2':
				// Get caterer details
				flag_hasloadedcat = read_cat_det();
				if(flag_hasloadedcat)
					print_cat_det();
				else
					printw("\nCaterer details not present. Please make one");
			break;
			case '3':
				// Write menu list
				write_menulist();
				
			break;
			case '4':
				// Load the menu list and print
				flag_hasloadedmenu = read_menulist();
				if(flag_hasloadedmenu)
					print_menulist();
				else
					printw("\nNo menu list present. Please make one");
			break;
			case '5':
				// Make invoice
				write_invoice();
				flag_hasloadedinvoicelist = 1;
			break;
			case '6':
				// Load invoice
				flag_hasloadedinvoicelist = read_invoice();
				print_invoice();
			break;
			case '7':
				// Make report
				if(flag_hasloadedinvoicelist)
					report();
				else
					printw("\nNo invoices generated. Please generate one.");
			break;
			case '0':
				// Exit
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
