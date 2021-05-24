%{
#ifndef FPARSER
   #include "parser.h"
#endif
#include "mylexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
%}
%union {
    int intval;
    double floatval;
    int subtok;
    char *strval;
}
%token  INSERT      INTO        VALUES      SELECT      FROM
        CREATE      TABLE       INTEGER     VARCHAR     DOUBLE
        CHAR        PRIMARY     KEY         REFERENCES  DATABASE
        DROP        OBJECT      NUMBER      VALUE       QUIT
        LIST_TABLES LIST_TABLE  CONNECT     HELP        LIST_DBASES
        CLEAR       CONTR       WHERE       OPERADOR    RELACIONAL
        LOGICO      ALL		    SINAL       FECHA_P     ABRE_P
        STRING		END			USE			SHOW		DATABASES
        TABLES


%%
start	: create_database
		| QUIT END{printf("bye\n");exit(0);}
		| drop_database
		| select_database
		| show_database
		| create_table
		| show_tables
		| drop_table
		| insert
		| select
		;
		
create_database: CREATE DATABASE {/*setMode(OP_CREATE_DATABASE);*/mode=OP_CREATE_DATABASE;} 
	object END {add_database(name); return 0;}/*semicolon {return 0;}*/;

drop_database: DROP DATABASE {mode = OP_DROP_DATABASE;} object END {del_database(name); return 0;};

select_database: USE {mode = OP_SELECT;} object END {select_database(name); return 0;};
object: OBJECT {free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);};

show_database: SHOW DATABASES END {show_databases();return 0;};

create_table: CREATE TABLE {queue_c_num=0;queue_i_num=0;queue_d_num=0;} object ABRE_P table_column_attr FECHA_P END {add_table(); return 0;};
table_column_attr: column_create type /*attribute*/ | column_create type /*attribute*/ ',' table_column_attr;
type: INTEGER {/*setColumnTypeCreate('I');*/ queue_i[queue_i_num++] = 11;}
    | VARCHAR {/*setColumnTypeCreate('S');*/ queue_i[queue_i_num++] = 12;} ABRE_P NUMBER {/*setColumnSizeCreate(yylval.strval);*/} FECHA_P
    | DOUBLE {/*setColumnTypeCreate('D');*/ queue_i[queue_i_num++] = 13;};
    //| CHAR {setColumnTypeCreate('C');};

column_create: OBJECT {/*setColumnCreate(yytext);*/strcpy(queue_c[queue_c_num++], yytext);};  //列名和表名不能用同一个变量

show_tables: SHOW TABLES END {show_tables();return 0;};

drop_table: DROP TABLE object END {del_table(name); return 0;};

insert: INSERT INTO {/*setMode(OP_INSERT);*/queue_c_num=0;queue_i_num=0;queue_d_num=0;} 
		OBJECT {free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);table_now = (database_now == NULL) ? NULL:find_table(name);} 
		opt_column_list VALUES ABRE_P value_list FECHA_P END{insert_to_table();return 0;};
opt_column_list: /*optional*/{int i; if(table_now !=NULL) for (i=0; i<table_now->column_num; i++) queue_i[queue_i_num++]=i;} 
			   | ABRE_P column_list FECHA_P;
value_list: value | value ',' value_list;
value: DOUBLE {strcpy(queue_c[queue_c_num++], yytext);}
     | NUMBER {strcpy(queue_c[queue_c_num++], yytext);}
     | STRING {strcpy(queue_c[queue_c_num++], yytext);};
column_list: column | column ',' column_list;
column: OBJECT {queue_i[queue_i_num++] = get_column_position(yytext);};

select: SELECT {queue_c_num=0;queue_i_num=0;queue_d_num=0;flag=0;} selection
        FROM table_select /*where*/ END {show_items(); return 0;};
table_select: OBJECT {free(name);name=(char *)malloc((strlen(yytext)+1)*sizeof(char));strcpy(name, yytext);table_now = (database_now == NULL) ? NULL:find_table(name);transis();};
selection: ALL {flag=1;}
         |  OBJECT {strcpy(queue_c[queue_c_num++], yytext);} selection2
         //|  ABRE_P OBJECT {adcProjSelect(yylval.strval);} selection2 FECHA_P
         ;
selection2: /* epsilon */
          | ',' OBJECT {strcpy(queue_c[queue_c_num++], yytext);} selection2;
//where:  /* epsilon */
//      | WHERE logics
//logics: relacoes repLogicos
//        |  adc_abre_p logicos FECHA_P {adcTokenWhere(yylval.strval,6);} repLogicos
//adc_abre_p: ABRE_P {adcTokenWhere(yylval.strval,5);}
//repLogicos: /* epsilon */
//          | LOGICO {adcTokenWhere(*yytext,1);} logics
%%
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
