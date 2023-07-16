#define OP_INSERT 			1
#define OP_CREATE_TABLE 	2
#define OP_DROP_TABLE 		3
#define OP_CREATE_DATABASE 	4
#define OP_DROP_DATABASE 	5
#define OP_SELECT 			6

#define INTE 11
#define VARC 12
#define DOUB 13

int mode = 0, col_num;
char *name;
int queue_c_num = 0, queue_i_num = 0, queue_d_num = 0, flag=0;
char queue_c[30][30];
int queue_i[30];
double queue_d[30];

union content { int i; double d; char c[30]; }integer, fraction, string;

typedef struct item
{
	union content *it;
	struct item *next;
}item;
typedef struct table
{
	char *table_name;
	int column_num;
	char **column_name;
	int **column_type;
	item *item_first, *item_last;
	struct table *next;
}table;

table *table_last, *table_now;

typedef struct database 
{
	char *name;
	table *table_first, *table_last;
	struct database *next;
}database;

database *database_now, *database_head, *database_tail, *database_last;

void push_c(char *name);
void push_i(int i);
void push_d(double d);

int database_init();

database *find_database (char *name);

void select_database(char *name);

void add_database(char *name);

void del_database(char *name);

void show_databases();

void add_table();

void init_table(table *table);

void show_tables();

void del_table(char *name);

table *find_table(char *name);

void insert_to_table();

int get_column_position(char *name);

void show_items();

void transis();