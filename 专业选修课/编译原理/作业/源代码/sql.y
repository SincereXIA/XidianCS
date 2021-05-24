%{
    #include <ctype.h>
    #include <stdio.h>
    #include "myarray.h"
    #include "lex.yy.c"
    #include "dbShell.h"
    #include <iostream>
    #define YYDEBUG 1
    #define YYERROR_VERBOSE
    #include <vector>
    #include "dbCore.h"
    using namespace std;
    dbShell shell;


extern
void yyerror(char *s) {
// simple error-message
printf("Error '%s'\n", s);

}
%}

%union {
  int intval;
  char * chval;
  int typeval;
  table_field_node * tableField;
  table_node * tableNode;
  insert_node * insertNode;
  values_node * valuesNode;
  select_node * selectNode;
  condexp_node * condNode;
  update_node * updateNode;
  set_value * setNode;
}
%type<insertNode> insertsql
%type<chval> table STRING field
%type<valuesNode> values value
%type<tableField> fields fields_star table_fields table_field
%type<intval> NUMBER
%type<selectNode> selectsql deletesql
%type<tableNode> tables
%type<condNode> conditions condition comp_op comp_left comp_right
%type<updateNode> updatesql
%type<setNode> updates update
%token CREATE
%token DATABASE
%token SHOW
%token DATABASES
%token DROP
%token USE
%token TABLE
%token TABLES
%token INSERT
%token INTO
%token VALUES
%token SELECT
%token FROM
%token WHERE
%token UPDATE
%token SET
%token ID
%token CHAR
%token NUMBER
%token INT
%token STRING
%token DELETE
%left OR
%left AND


%%
statements: statements statement {printf("\nmysql> ");}
          | statement {printf("\nmysql> ");}
          ;
statement:   createsql
         |  selectsql
         |  insertsql
         |  deletesql
         |  updatesql
         |  dbsql
            ;
    // 数据库操作语句
dbsql: CREATE DATABASE database ';'{shell.CreateDatabase($<chval>3);}
     | SHOW DATABASES ';' {shell.ShowDatabases();}
     | SHOW TABLES ';' {shell.ShowTables();}
     | DROP DATABASE database ';' {shell.DropDatabases($<chval>3);}
     | DROP TABLE table ';' {shell.dropTable($<chval>3);}
     | USE database ';' {shell.UseDatabase($<chval>3);}
     ;
database: ID
        ;

    // 建表语句
createsql:   CREATE TABLE table '(' fieldsdefinition ')' ';' {shell.CreateTable($3, $<tableField>5);}
            ;
table: ID {}
     ;
fieldsdefinition: field_type {$<tableField>$ = $<tableField>1;
			      }
                | field_type ',' fieldsdefinition {$<tableField>1->next = $<tableField>3;
                				   $<tableField>$ = $<tableField>1;}
                ;
field_type: field type {$<tableField>$ = $<tableField>2;
 			$<tableField>$->field_name = $1;}
          ;
field:  ID {$$ = $<chval>1}
     ;
type: CHAR '(' NUMBER ')'  {$<tableField>$ = new table_field_node;
			    $<tableField>$->len = $3;}
    | INT {$<tableField>$ = new table_field_node;
           $<tableField>$->len = 0;}
    ;

    // 查询语句
selectsql:  SELECT fields_star FROM tables ';' {$$ = new select_node;
						$$->field = $2;
						$$->table = $4;
						shell.select($$);
						}
         |  SELECT fields_star FROM tables WHERE conditions ';' {$$ = new select_node;
								$$->field = $2;
								$$->table = $4;
								$$->cons = $6;
								shell.select($$);
								}
         ;
fields_star: table_fields { $$ = $1;}
           | '*' {$$ = new table_field_node;
           	  $$->field_name = _S("*");
           	  }
           ;
table_fields: table_field { $$ = $1; }
            | table_field ',' table_fields {$$ = $1;
            				    $$->next = $3;}
            ;
table_field: field  {$$ = new table_field_node;
		     $$->field_name = $1;
		    }
           | table '.' field
           ;
tables: table {$$ = new table_node;
		$$->tableName = $1;}
      | table ',' tables {$$ = new table_node;
                          $$->tableName = $1;
      			  $$->next = $3;
      			  }
      ;
conditions: condition {$$ = $1;}
          | '(' conditions ')' {$$ = $2;}
          | conditions AND conditions {$$ = new condexp_node;
          				$$->left = $1;
          				$$->right = $3;
          				$$->op = condexp_node::AND;
          				$$->type = condexp_node::LOGIC;
          				}
          | conditions OR conditions	{$$ = new condexp_node;
					$$->left = $1;
					$$->right = $3;
					$$->op = condexp_node::OR;
					$$->type = condexp_node::LOGIC;
					}
          ;
condition:  comp_left comp_op comp_right {$$ = $2;
					  $$->left = $1;
					  $$->right = $3;
					 }
         ;
comp_left:  table_field {$$ = new condexp_node;
			 $$->chval = $1->field_name;
			}
         ;
comp_op:  '<' {$$ = new condexp_node; $$->op = condexp_node::B;}
	| '>' {$$ = new condexp_node; $$->op = condexp_node::G;}
	| '=' {$$ = new condexp_node; $$->op = condexp_node::EQ;}
	| '!''=' {$$ = new condexp_node; $$->op = condexp_node::NOT;}
       ;
comp_right: table_field {$$ = new condexp_node;
			 $$->chval = $1->field_name;
			 $$->type = condexp_node::STRING;
			}
          | NUMBER	{$$ = new condexp_node;
			 $$->intval = $1;
			 $$->type = condexp_node::INT;
			}
	  | STRING     {$$ = new condexp_node;
			 $$->chval = $1;
			 $$->type = condexp_node::STRING;
			}
          ;

/// 插入语句
insertsql: INSERT INTO table VALUES '(' values ')' ';' {$$ = new insert_node;
							$$->table = new table_node;
							$$->table->tableName = $3;
							$$->values = $6;
							shell.sqlInsert($$);
							}
	 | INSERT INTO table '(' fields ')' VALUES '(' values ')' ';'  {$$ = new insert_node;
									$$->table = new table_node;
									$$->table->tableName = $3;
									$$->values = $9;
									$$->field = $5;
									shell.sqlInsert($$);
									}
	 ;
values: value {$$ = $1}
      | value ',' values {$$ = $1;
      			  $$->next = $3;
      			  }
      ;
value: STRING { $$ = new values_node;
		$$->type = values_node::STRING;
		$$->chval = $1;
		}
     | NUMBER { $$ = new values_node;
               	$$->type = values_node::INT;
               	$$->intval = $1;
     		}
     ;
fields: field {$$ = new table_field_node;
	       $$->field_name = $1;
		}
      | field ',' fields {$$ = new table_field_node;
      			  $$->field_name = $1;
      			  $$->next = $3;
                          }
      ;
//删除语句
deletesql: DELETE FROM table ';' {$$ = new select_node;
				   $$->table = new table_node;
				   $$->table->tableName = $3;
				   $$->cons = nullptr;
				   shell.sqldelete($$);}
	  | DELETE FROM table WHERE conditions ';' {$$ = new select_node;
	  					    $$->table = new table_node;
                                                    $$->table->tableName = $3;
	  					    $$->cons = $5;
	  					    shell.sqldelete($$);
	  					    }
	  ;
//更新语句
updatesql: UPDATE table SET updates WHERE conditions  ';'  {$$ = new update_node;
							    $$->table = new table_node;
							    $$->table->tableName = $2;
							    $$->cons = $6;
							    $$->setval = $4;
							    shell.sqlupdate($$);
							    } ;

updates:  update  {$$ = $1
		  }
	| update ',' updates {$$ = $1;
			      $1->next = $3;
			      }
	;

update: comp_left '=' comp_right  {$$ = new set_value;
				    $$->field_name = $1->chval;
				    $$->intval = $3->intval;
				    $$->chval = $3->chval;
				   }
	;



%%

int main(){
   printf("\nmysql>");
   while(1){
   	yyparse();
   }
}
