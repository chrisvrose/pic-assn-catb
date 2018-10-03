#define ITEM_LEN 25
#define MOTD "Have a nice day!"
#define MAX_ITEM_LIST 150

int exists(const char *fname);
int check_substreq(char *,char *,int,int);

//Functions - Functionality has been finalized
//TODO - ADD safeguards for off-limit inputs

void print_cat_det();
int read_cat_det();
void write_cat_det();

void write_menulist();
void print_menulist();
int read_menulist();

int input_item_number();
int read_invoice_list();

int write_invoice();
void read_invoice();
void print_invoice();

//void read_invoice_list();

int report();



typedef struct{
	char name[64];
	char rest_code[16];		//Business id?
	float taxp;
	
}scat_details;


/*typedef struct{
	int date[3];
	int time[2];
} datetime;*/


typedef struct{
	char name[32];
	float sprice;
	float pcost;
} sinventory_piece;

typedef struct{
	int num_menu;
	sinventory_piece pieces[128];
} smenu;



typedef struct{
	char recep[32];
	//datetime ptime;
	int item_numbers[128][2];
	int pieces_len;
} sinvoice;


typedef struct{
	int num_invoice;
	char invoice_name_list[256][32];
} sinvoice_list;