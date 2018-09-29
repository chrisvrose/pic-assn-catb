
// Objective 1
int set_profitper(float*);

// Objective 2
int make_invoice(float);

//Objective 3


//Objective 4

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
