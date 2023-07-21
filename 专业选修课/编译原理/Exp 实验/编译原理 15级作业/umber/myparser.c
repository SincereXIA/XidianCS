/****************************************************************************
*                         A C A D E M I C   C O P Y
* 
* This file was produced by an ACADEMIC COPY of Parser Generator. It is for
* use in non-commercial software only. An ACADEMIC COPY of Parser Generator
* can only be used by a student, or a member of an academic community. If
* however you want to use Parser Generator for commercial purposes then you
* will need to purchase a license. For more information see the online help or
* go to the Bumble-Bee Software homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* myparser.c
* C source file generated from myparser.y.
* 
* Date: 06/28/18
* Time: 19:56:37
* 
* AYACC Version: 2.07
****************************************************************************/

#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#line 1 ".\\myparser.y"

#ifndef FPARSER
   #include "parser.h"
#endif
#include "mylexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#line 49 "myparser.c"
/* repeated because of possible precompiled header */
#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#include ".\myparser.h"

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/* (state) stack */
#if (YYSTACK_SIZE) != 0
static yystack_t YYNEAR yystack[(YYSTACK_SIZE)];
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = yystack;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = yystack;
#else
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = NULL;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = NULL;
#endif

/* attribute stack */
#if (YYSTACK_SIZE) != 0
static YYSTYPE YYNEAR yyattributestack[(YYSTACK_SIZE)];
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = yyattributestack;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = yyattributestack;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = (char YYFAR *) yyattributestack;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = (char YYFAR *) yyattributestack;
#endif
#else
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#endif
#endif

int YYNEAR YYDCDECL yysstack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_max = (YYSTACK_MAX);

/* attributes */
YYSTYPE YYNEAR yyval;
YYSTYPE YYNEAR yylval;
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yyvalptr = &yyval;
void YYFAR *YYNEAR YYDCDECL yylvalptr = &yylval;
#else
char YYFAR *YYNEAR YYDCDECL yyvalptr = (char *) &yyval;
char YYFAR *YYNEAR YYDCDECL yylvalptr = (char *) &yylval;
#endif

size_t YYNEAR YYDCDECL yyattribute_size = sizeof(YYSTYPE);

/* yyattribute */
#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static YYSTYPE YYFAR *yyattribute1(int index)
#else
static YYSTYPE YYFAR *yyattribute1(index)
int index;
#endif
{
	YYSTYPE YYFAR *p = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR *) yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static void yyinitdebug(YYSTYPE YYFAR **p, int count)
#else
static void yyinitdebug(p, count)
YYSTYPE YYFAR **p;
int count;
#endif
{
	int i;
	yyassert(p != NULL);
	yyassert(count >= 1);

	for (i = 0; i < count; i++) {
		p[i] = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

#ifdef YYPROTOTYPE
void YYCDECL yyparseraction(int action)
#else
void YYCDECL yyparseraction(action)
int action;
#endif
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 29 ".\\myparser.y"
printf("bye\n");exit(0);
#line 175 "myparser.c"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 40 ".\\myparser.y"
/*setMode(OP_CREATE_DATABASE);*/mode=OP_CREATE_DATABASE;
#line 188 "myparser.c"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 40 ".\\myparser.y"
add_database(name); return 0;
#line 201 "myparser.c"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 42 ".\\myparser.y"
mode = OP_DROP_DATABASE;
#line 214 "myparser.c"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 42 ".\\myparser.y"
del_database(name); return 0;
#line 227 "myparser.c"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 44 ".\\myparser.y"
mode = OP_SELECT;
#line 240 "myparser.c"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 44 ".\\myparser.y"
select_database(name); return 0;
#line 253 "myparser.c"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 45 ".\\myparser.y"
free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);
#line 266 "myparser.c"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 47 ".\\myparser.y"
show_databases();return 0;
#line 279 "myparser.c"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 49 ".\\myparser.y"
queue_c_num=0;queue_i_num=0;queue_d_num=0;
#line 292 "myparser.c"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[9];
			yyinitdebug(yya, 9);
#endif
			{
#line 49 ".\\myparser.y"
add_table(); return 0;
#line 305 "myparser.c"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 51 ".\\myparser.y"
/*setColumnTypeCreate('I');*/ queue_i[queue_i_num++] = 11;
#line 318 "myparser.c"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 52 ".\\myparser.y"
/*setColumnTypeCreate('S');*/ queue_i[queue_i_num++] = 12;
#line 331 "myparser.c"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 52 ".\\myparser.y"
/*setColumnSizeCreate(yylval.strval);*/
#line 344 "myparser.c"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 53 ".\\myparser.y"
/*setColumnTypeCreate('D');*/ queue_i[queue_i_num++] = 13;
#line 357 "myparser.c"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 56 ".\\myparser.y"
/*setColumnCreate(yytext);*/strcpy(queue_c[queue_c_num++], yytext);
#line 370 "myparser.c"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 58 ".\\myparser.y"
show_tables();return 0;
#line 383 "myparser.c"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 60 ".\\myparser.y"
del_table(name); return 0;
#line 396 "myparser.c"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 62 ".\\myparser.y"
/*setMode(OP_INSERT);*/queue_c_num=0;queue_i_num=0;queue_d_num=0;
#line 409 "myparser.c"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 63 ".\\myparser.y"
free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);table_now = (database_now == NULL) ? NULL:find_table(name);
#line 422 "myparser.c"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[12];
			yyinitdebug(yya, 12);
#endif
			{
#line 64 ".\\myparser.y"
insert_to_table();return 0;
#line 435 "myparser.c"
			}
		}
		break;
	case 21:
		{
#line 65 ".\\myparser.y"
int i; if(table_now !=NULL) for (i=0; i<table_now->column_num; i++) queue_i[queue_i_num++]=i;
#line 443 "myparser.c"
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 68 ".\\myparser.y"
strcpy(queue_c[queue_c_num++], yytext);
#line 455 "myparser.c"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 69 ".\\myparser.y"
strcpy(queue_c[queue_c_num++], yytext);
#line 468 "myparser.c"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 70 ".\\myparser.y"
strcpy(queue_c[queue_c_num++], yytext);
#line 481 "myparser.c"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 72 ".\\myparser.y"
queue_i[queue_i_num++] = get_column_position(yytext);
#line 494 "myparser.c"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 74 ".\\myparser.y"
queue_c_num=0;queue_i_num=0;queue_d_num=0;flag=0;
#line 507 "myparser.c"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[7];
			yyinitdebug(yya, 7);
#endif
			{
#line 75 ".\\myparser.y"
show_items(); return 0;
#line 520 "myparser.c"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 76 ".\\myparser.y"
free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);table_now = (database_now == NULL) ? NULL:find_table(name);transis();
#line 533 "myparser.c"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 77 ".\\myparser.y"
flag=1;
#line 546 "myparser.c"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 78 ".\\myparser.y"
strcpy(queue_c[queue_c_num++], yytext);
#line 559 "myparser.c"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 82 ".\\myparser.y"
strcpy(queue_c[queue_c_num++], yytext);
#line 572 "myparser.c"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "\',\'", 44 },
	{ "error", 256 },
	{ "INSERT", 257 },
	{ "INTO", 258 },
	{ "VALUES", 259 },
	{ "SELECT", 260 },
	{ "FROM", 261 },
	{ "CREATE", 262 },
	{ "TABLE", 263 },
	{ "INTEGER", 264 },
	{ "VARCHAR", 265 },
	{ "DOUBLE", 266 },
	{ "DATABASE", 271 },
	{ "DROP", 272 },
	{ "OBJECT", 273 },
	{ "NUMBER", 274 },
	{ "QUIT", 276 },
	{ "ALL", 288 },
	{ "FECHA_P", 290 },
	{ "ABRE_P", 291 },
	{ "STRING", 292 },
	{ "END", 293 },
	{ "USE", 294 },
	{ "SHOW", 295 },
	{ "DATABASES", 296 },
	{ "TABLES", 297 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: start",
	"start: create_database",
	"start: QUIT END",
	"start: drop_database",
	"start: select_database",
	"start: show_database",
	"start: create_table",
	"start: show_tables",
	"start: drop_table",
	"start: insert",
	"start: select",
	"$$1:",
	"create_database: CREATE DATABASE $$1 object END",
	"$$2:",
	"drop_database: DROP DATABASE $$2 object END",
	"$$3:",
	"select_database: USE $$3 object END",
	"object: OBJECT",
	"show_database: SHOW DATABASES END",
	"$$4:",
	"create_table: CREATE TABLE $$4 object ABRE_P table_column_attr FECHA_P END",
	"table_column_attr: column_create type",
	"table_column_attr: column_create type \',\' table_column_attr",
	"type: INTEGER",
	"$$5:",
	"$$6:",
	"type: VARCHAR $$5 ABRE_P NUMBER $$6 FECHA_P",
	"type: DOUBLE",
	"column_create: OBJECT",
	"show_tables: SHOW TABLES END",
	"drop_table: DROP TABLE object END",
	"$$7:",
	"$$8:",
	"insert: INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END",
	"opt_column_list:",
	"opt_column_list: ABRE_P column_list FECHA_P",
	"value_list: value",
	"value_list: value \',\' value_list",
	"value: DOUBLE",
	"value: NUMBER",
	"value: STRING",
	"column_list: column",
	"column_list: column \',\' column_list",
	"column: OBJECT",
	"$$9:",
	"select: SELECT $$9 selection FROM table_select END",
	"table_select: OBJECT",
	"selection: ALL",
	"$$10:",
	"selection: OBJECT $$10 selection2",
	"selection2:",
	"$$11:",
	"selection2: \',\' OBJECT $$11 selection2"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 2, 0 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 1, 1, -1 },
	{ 3, 0, 1 },
	{ 2, 5, 2 },
	{ 5, 0, 3 },
	{ 4, 5, 4 },
	{ 7, 0, 5 },
	{ 6, 4, 6 },
	{ 8, 1, 7 },
	{ 9, 3, 8 },
	{ 11, 0, 9 },
	{ 10, 8, 10 },
	{ 12, 2, -1 },
	{ 12, 4, -1 },
	{ 13, 1, 11 },
	{ 14, 0, 12 },
	{ 15, 0, 13 },
	{ 13, 6, -1 },
	{ 13, 1, 14 },
	{ 16, 1, 15 },
	{ 17, 3, 16 },
	{ 18, 4, 17 },
	{ 20, 0, 18 },
	{ 21, 0, 19 },
	{ 19, 11, 20 },
	{ 22, 0, 21 },
	{ 22, 3, -1 },
	{ 23, 1, -1 },
	{ 23, 3, -1 },
	{ 24, 1, 22 },
	{ 24, 1, 23 },
	{ 24, 1, 24 },
	{ 25, 1, -1 },
	{ 25, 3, -1 },
	{ 26, 1, 25 },
	{ 28, 0, 26 },
	{ 27, 6, 27 },
	{ 29, 1, 28 },
	{ 30, 1, 29 },
	{ 31, 0, 30 },
	{ 30, 3, -1 },
	{ 32, 0, -1 },
	{ 33, 0, 31 },
	{ 32, 4, -1 }
};

int YYNEAR YYDCDECL yytokenaction_size = 55;
YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 0, YYAT_SHIFT, 1 },
	{ 89, YYAT_SHIFT, 81 },
	{ 19, YYAT_SHIFT, 29 },
	{ 0, YYAT_SHIFT, 2 },
	{ 4, YYAT_SHIFT, 22 },
	{ 0, YYAT_SHIFT, 3 },
	{ 3, YYAT_SHIFT, 20 },
	{ 7, YYAT_SHIFT, 26 },
	{ 7, YYAT_SHIFT, 27 },
	{ 89, YYAT_SHIFT, 82 },
	{ 93, YYAT_SHIFT, 94 },
	{ 88, YYAT_SHIFT, 91 },
	{ 4, YYAT_SHIFT, 23 },
	{ 86, YYAT_SHIFT, 90 },
	{ 3, YYAT_SHIFT, 21 },
	{ 0, YYAT_SHIFT, 4 },
	{ 85, YYAT_SHIFT, 89 },
	{ 19, YYAT_SHIFT, 30 },
	{ 84, YYAT_SHIFT, 88 },
	{ 0, YYAT_SHIFT, 5 },
	{ 61, YYAT_SHIFT, 68 },
	{ 61, YYAT_SHIFT, 69 },
	{ 61, YYAT_SHIFT, 70 },
	{ 78, YYAT_SHIFT, 60 },
	{ 77, YYAT_SHIFT, 86 },
	{ 74, YYAT_SHIFT, 63 },
	{ 72, YYAT_SHIFT, 79 },
	{ 89, YYAT_SHIFT, 83 },
	{ 71, YYAT_SHIFT, 78 },
	{ 67, YYAT_SHIFT, 49 },
	{ 66, YYAT_SHIFT, 75 },
	{ 65, YYAT_SHIFT, 74 },
	{ 64, YYAT_SHIFT, 73 },
	{ 62, YYAT_SHIFT, 72 },
	{ 57, YYAT_SHIFT, 66 },
	{ 52, YYAT_SHIFT, 59 },
	{ 49, YYAT_SHIFT, 58 },
	{ 0, YYAT_SHIFT, 6 },
	{ 0, YYAT_SHIFT, 7 },
	{ 48, YYAT_SHIFT, 56 },
	{ 46, YYAT_SHIFT, 55 },
	{ 44, YYAT_SHIFT, 54 },
	{ 43, YYAT_SHIFT, 53 },
	{ 42, YYAT_SHIFT, 51 },
	{ 41, YYAT_SHIFT, 49 },
	{ 37, YYAT_SHIFT, 47 },
	{ 36, YYAT_SHIFT, 34 },
	{ 35, YYAT_SHIFT, 45 },
	{ 31, YYAT_SHIFT, 42 },
	{ 28, YYAT_SHIFT, 40 },
	{ 27, YYAT_SHIFT, 39 },
	{ 26, YYAT_SHIFT, 38 },
	{ 16, YYAT_ACCEPT, 0 },
	{ 5, YYAT_SHIFT, 24 },
	{ 1, YYAT_SHIFT, 18 }
};

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -257, 1, YYAT_ERROR, 0 },
	{ -204, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 44 },
	{ -257, 1, YYAT_ERROR, 0 },
	{ -259, 1, YYAT_ERROR, 0 },
	{ -240, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 15 },
	{ -289, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 10 },
	{ 0, 0, YYAT_REDUCE, 3 },
	{ 0, 0, YYAT_REDUCE, 9 },
	{ 0, 0, YYAT_REDUCE, 7 },
	{ 0, 0, YYAT_REDUCE, 5 },
	{ 0, 0, YYAT_REDUCE, 8 },
	{ 0, 0, YYAT_REDUCE, 1 },
	{ 0, 0, YYAT_REDUCE, 6 },
	{ 52, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 4 },
	{ 0, 0, YYAT_REDUCE, 31 },
	{ -271, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 19 },
	{ 0, 0, YYAT_REDUCE, 11 },
	{ 0, 0, YYAT_DEFAULT, 36 },
	{ 0, 0, YYAT_REDUCE, 13 },
	{ 0, 0, YYAT_REDUCE, 2 },
	{ 0, 0, YYAT_DEFAULT, 36 },
	{ -242, 1, YYAT_ERROR, 0 },
	{ -243, 1, YYAT_ERROR, 0 },
	{ -224, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 48 },
	{ 0, 0, YYAT_REDUCE, 47 },
	{ -213, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 36 },
	{ 0, 0, YYAT_DEFAULT, 36 },
	{ 0, 0, YYAT_REDUCE, 17 },
	{ -246, 1, YYAT_ERROR, 0 },
	{ -227, 1, YYAT_ERROR, 0 },
	{ -248, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 18 },
	{ 0, 0, YYAT_REDUCE, 29 },
	{ 0, 0, YYAT_REDUCE, 32 },
	{ 0, 1, YYAT_REDUCE, 50 },
	{ -230, 1, YYAT_ERROR, 0 },
	{ -249, 1, YYAT_ERROR, 0 },
	{ -252, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 30 },
	{ -253, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 16 },
	{ -252, 1, YYAT_REDUCE, 34 },
	{ -237, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 49 },
	{ 0, 0, YYAT_REDUCE, 46 },
	{ -258, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 78 },
	{ 0, 0, YYAT_REDUCE, 12 },
	{ 0, 0, YYAT_REDUCE, 14 },
	{ 0, 0, YYAT_DEFAULT, 74 },
	{ -225, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 51 },
	{ 0, 0, YYAT_REDUCE, 45 },
	{ 0, 0, YYAT_REDUCE, 28 },
	{ -244, 1, YYAT_ERROR, 0 },
	{ -257, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 43 },
	{ -258, 1, YYAT_ERROR, 0 },
	{ -13, 1, YYAT_REDUCE, 41 },
	{ -261, 1, YYAT_ERROR, 0 },
	{ -15, 1, YYAT_REDUCE, 50 },
	{ 0, 0, YYAT_REDUCE, 23 },
	{ 0, 0, YYAT_REDUCE, 24 },
	{ 0, 0, YYAT_REDUCE, 27 },
	{ -16, 1, YYAT_REDUCE, 21 },
	{ -267, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 35 },
	{ -248, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 89 },
	{ 0, 0, YYAT_REDUCE, 52 },
	{ -267, 1, YYAT_ERROR, 0 },
	{ -250, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 20 },
	{ 0, 0, YYAT_REDUCE, 42 },
	{ 0, 0, YYAT_REDUCE, 38 },
	{ 0, 0, YYAT_REDUCE, 39 },
	{ 0, 0, YYAT_REDUCE, 40 },
	{ -272, 1, YYAT_ERROR, 0 },
	{ -28, 1, YYAT_REDUCE, 36 },
	{ -261, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 22 },
	{ -282, 1, YYAT_ERROR, 0 },
	{ -265, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 25 },
	{ 0, 0, YYAT_REDUCE, 33 },
	{ 0, 0, YYAT_REDUCE, 37 },
	{ -280, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 26 }
};

int YYNEAR YYDCDECL yynontermgoto_size = 41;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 0, 16 },
	{ 0, 14 },
	{ 78, 87 },
	{ 0, 9 },
	{ 90, 93 },
	{ 0, 17 },
	{ 78, 61 },
	{ 75, 84 },
	{ 0, 12 },
	{ 0, 15 },
	{ 89, 92 },
	{ 89, 85 },
	{ 74, 80 },
	{ 74, 65 },
	{ 69, 77 },
	{ 67, 76 },
	{ 0, 11 },
	{ 0, 13 },
	{ 0, 10 },
	{ 61, 71 },
	{ 58, 67 },
	{ 56, 64 },
	{ 53, 62 },
	{ 48, 57 },
	{ 42, 52 },
	{ 41, 50 },
	{ 0, 8 },
	{ 40, 48 },
	{ 36, 46 },
	{ 33, 44 },
	{ 32, 43 },
	{ 29, 41 },
	{ 25, 37 },
	{ 23, 36 },
	{ 22, 35 },
	{ 21, 33 },
	{ 20, 32 },
	{ 19, 31 },
	{ 18, 28 },
	{ 6, 25 },
	{ 2, 19 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ -1, -1 },
	{ 0, -1 },
	{ 12, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 32, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 18, -1 },
	{ 7, -1 },
	{ 25, -1 },
	{ 32, -1 },
	{ 26, -1 },
	{ 28, -1 },
	{ 0, -1 },
	{ 24, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 22, -1 },
	{ 21, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 20, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 6, -1 },
	{ -7, -1 },
	{ -5, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 1, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 10, 78 },
	{ 0, -1 },
	{ 0, -1 },
	{ -4, 74 },
	{ 0, -1 },
	{ -13, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 6, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -17, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -13, -1 },
	{ -16, 89 },
	{ 0, -1 },
	{ 0, -1 },
	{ -10, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -13, -1 },
	{ -11, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

YYCONST yytokendest_t YYNEARFAR *YYNEAR YYDCDECL yytokendestptr = NULL;
int YYNEAR YYDCDECL yytokendest_size = 0;

YYCONST yytokendestbase_t YYNEARFAR *YYNEAR YYDCDECL yytokendestbaseptr = NULL;
int YYNEAR YYDCDECL yytokendestbase_size = 0;
#line 90 ".\\myparser.y"

int main(void)
{
	int n=0;
	database_init();
	while (!n)
	{
	    printf ("SQLtest>");
	    n = yyparse();
	}    
	return 0;
}

