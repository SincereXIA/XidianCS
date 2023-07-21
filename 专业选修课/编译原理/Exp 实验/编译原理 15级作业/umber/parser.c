#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void push_c(char *c) { strcpy(queue_c[queue_c_num++], c); }
void push_i(int i) { queue_i[queue_i_num++] = i; }
void push_d(double d) { queue_d[queue_i_num++] = d; }

int database_init()
{
	database_now = NULL;
	database_head = (database *)malloc(sizeof(database));
	database_tail = database_head;
	if (database_head == NULL) return 1;
    database_head->next = NULL;	
}


database *find_database (char *name)
{
	database *p = database_head->next, *q=NULL;
	database_last = database_head;
	while (p)
	{
		if (strcmp(p->name, name) == 0)
		{
			q = p;
			break;
		}
		database_last = p;
		p = p->next;
	}
	return q;
}

void select_database(char *name)
{
	database *p = database_head->next;
	database_now = find_database(name);
	if (database_now == NULL) printf ("error: database not exist\n");
	else printf("database %s\n", name);
}

void add_database(char *name)
{
	database *p = (database *)malloc(sizeof(database));
	table *q = (table *)malloc(sizeof(table));
	p->name = (char *)malloc((strlen(name)+1)*sizeof(char));
	strcpy(p->name, name);
	p->next = NULL;
	init_table(q);
	p->table_first = p->table_last = q;
	database_tail->next = p;
	database_tail = p;
	printf("database %s have created\n", name);
}

void del_database(char *name)
{
	database *p=find_database(name);
	if (p == database_now) database_now = NULL;
	if (p)
	{
		database_last->next = p->next;		
		free(p);
		printf ("database %s has been removed\n", name);
	}
	else printf ("database %s not exist\n", name);
}

void show_databases()
{
	printf("databases:\n");
	database *p = database_head->next;
	while (p)
	{
		printf("%s\n", p->name);
		p = p->next;
	}

}
void init_table(table *table)
{
	table->column_num = 0;
	table->item_first = table->item_last = (item *)malloc(sizeof(item));
	table->item_last->next = NULL;
	table->next = NULL;
}

table *find_table(char *name)
{
	table *p = database_now->table_first->next;
	table_last = database_now->table_first;
	while (p)
	{
		if (strcmp(p->table_name, name) == 0) return p;
		table_last = p;
		p = p->next;
	}
	return NULL;
}

void add_table()
{
	table *p = (table *)malloc(sizeof(table));
	int i;
	init_table(p);
	p->table_name = (char *)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(p->table_name, name);
	p->column_num = queue_c_num;
	p->column_name = (char **)malloc(queue_c_num*sizeof(char *));
	p->column_type = (int **)malloc(queue_c_num * sizeof(int *));
	for (i = 0; i < queue_c_num; i++)
	{
		p->column_name[i] = (char *)malloc((strlen(queue_c[i]) + 1) * sizeof(char));
		strcpy(p->column_name[i], queue_c[i]);
		p->column_type[i] = (int *)malloc(sizeof(int));
		*(p->column_type[i]) = queue_i[i];
	}	
	p->item_last = p->item_first = (item *)malloc(sizeof(item));
	p->item_first->next = NULL;
	p->item_first->it = (union content *)malloc(queue_c_num * sizeof(union content));
	if (database_now == NULL)
		printf("please select a database first\n");
	else
	{
		database_now->table_last->next = p;
		database_now->table_last = p;
		printf("table %s has created\n", p->table_name);
	}	
}

void show_tables()
{
	if (database_now == NULL)
	{
		printf("please select a database first\n");
		return;
	}
	table *p = database_now->table_first->next;
	printf("tables:\n");
	while (p)
	{
		printf("%s\n", p->table_name);
		p = p->next;
	}
}

void del_table(char *name)
{
	table *p = find_table(name);
	if (p)
	{
		table_last->next = p->next;
		free(p);
		printf("database %s has been removed\n", name);
	}
	else printf("database %s not exist\n", name);
}

void insert_to_table()
{
	int i;
	if (database_now == NULL)
	{
		printf("please select a database first\n");
		return;
	}
	else if (table_now == NULL)
	{
		printf("no such table:%s\n", name);
		return;
	}
	else
	{
		item *p = (item *)malloc(sizeof(item));
		p->it = (union content **)malloc(table_now->column_num*sizeof(union content *));
		p->next = NULL;
		
		for (i = 0; i < table_now->column_num; i++)  //³õÊ¼»¯ÐÐ
		{
			if (*(table_now->column_type[queue_i[i]]) == INTE) p->it[i].i = -1;
			else if (*(table_now->column_type[queue_i[i]]) == DOUB) p->it[i].d = -1.0;
			else if (*(table_now->column_type[queue_i[i]]) == VARC) strcpy(p->it[i].c, "");
		}
		for (i = 0; i < queue_i_num; i++)
		{
			if (queue_i[i] == -1)
			{
				printf("item %s not match a column\n", queue_c[i]);
				free(p);
				return;
			}
			else if (*(table_now->column_type[queue_i[i]]) == INTE) p->it[queue_i[i]].i = atoi(queue_c[i]);
			else if (*(table_now->column_type[queue_i[i]]) == DOUB) p->it[queue_i[i]].d = atof(queue_c[i]);
			else if (*(table_now->column_type[queue_i[i]]) == VARC) strcpy(p->it[queue_i[i]].c, queue_c[i]);
		}
		/*for (i = 0; i < queue_i_num; i++)
		{
            if (table_now->column_type[queue_i[i]] == INTE) printf("%d\n", p->it[queue_i[i]].i);
			else if (table_now->column_type[queue_i[i]] == DOUB) printf("%lf\n",p->it[queue_i[i]].d);
			else if (table_now->column_type[queue_i[i]] == VARC) printf("%s\n", p->it[queue_i[i]].c);
		}*/
			
		table_now->item_last->next = p;
		table_now->item_last = p;
		printf("insert completed\n");
	}
}

int get_column_position(char *name)
{
	if (table_now == NULL) return -1;
	int i = 0;
	for (i = 0; i < table_now->column_num; i++)
		if (strcmp(table_now->column_name[i], name) == 0) return i;
	return -1;
}

void show_items()
{
	int i;
	item *p;
	if (database_now == NULL)
	{
		printf("please select a database first\n");
		return;
	}
	else if (table_now == NULL)
	{
		printf("no such table:%s\n", name);
		return;
	}
	else
	{
		for (i = 0; i < queue_i_num; i++)
			printf("%15s", table_now->column_name[queue_i[i]]);
		printf("\n");
		p = table_now->item_first->next;
		while (p)
		{
			for (i = 0; i < queue_i_num; i++)
				if (*(table_now->column_type[queue_i[i]]) == INTE)
				{
					if (p->it[queue_i[i]].i < 0) printf("%15s", "NULL");
					else printf("%15d\t", p->it[queue_i[i]].i);
				}
				else if (*(table_now->column_type[queue_i[i]]) == DOUB)
				{
					if (p->it[queue_i[i]].d < 0) printf("%15s", "NULL");
					else printf("%15lf\t", p->it[queue_i[i]].d);
				}
				else if (*(table_now->column_type[queue_i[i]]) == VARC)
				{
					if (strlen(p->it[queue_i[i]].c) == 0) printf("%15s", "NULL");
					else printf("%15s\t", p->it[queue_i[i]].c);
				}
			printf("\n");
			p = p->next;
		}
	}
}

void transis()
{
	int i;
	if (database_now == NULL) return;
	else if (table_now == NULL) return;
	else
	{
		if (flag)
			for (i = 0; i < table_now->column_num; i++)
				queue_i[queue_i_num++] = i;
		else
			for (i = 0; i < queue_c_num; i++)
				queue_i[queue_i_num++] = get_column_position(queue_c[i]);
	}
}