#define ITEM_LEN 25
#define MOTD "Have a nice day!"
#define MAX_ITEM_LIST 150


void print_cat_det();
void read_cat_det();
void write_cat_det();
void write_menulist();
void print_menulist();
void read_menulist();


typedef struct{
	char name[64];
	char rest_code[16];		//Business id?
	float taxp;
	
}cat_details;




typedef struct{
	int date[3];
	int time[2];
} datetime;




typedef struct{
	char name[32];
	float sprice;
	float pcost;
} inventory_piece;

typedef struct{
	int num_menu;
	inventory_piece pieces[128];
} menu_list;


typedef struct{
	char recep[32];
	datetime ptime;
	int item_numbers[128][2];
	int pieces_len;
} invoice;
