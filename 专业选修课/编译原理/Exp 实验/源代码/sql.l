%{
    #include <stdio.h>
    #include <vector>
    #include "dbCore.h"
    #include "sql.tab.h"
    #include <cstring>
    int cur_line = 1;
%}

CREATE CREATE|create
SHOW SHOW|show
DROP DROP|drop
USE USE|use
DATABASE DATABASE|database
DATABASES DATABASES|databases
TABLE TABLE|table
TABLES TABLES|tables
CHAR CHAR|char
INT INT|int
FROM from|FROM
SELECT SELECT|select
WHERE WHERE|where
AND AND|and
OR OR|or
INSERT INSERT|insert
INTO INTO|into
VALUES VALUES|VALUES
DELETE DELETE|delete
UPDATE UPDATE|update
SET SET|set
ID [a-zA-Z][a-zA-Z_0-9]*
NUMBER [-+]?[0-9][0-9]*
STRING '.*'

%%
{CHAR} {yylval.typeval = CHAR; return CHAR; }
{INT} {yylval.typeval = INT; return INT;}

{CREATE} { return CREATE;}
{SHOW} {return SHOW; }
{DROP} {return DROP; }
{USE} {return USE;}
{TABLE} {return TABLE;}
{TABLES} { return TABLES;}
{DATABASE} { return DATABASE;}
{DATABASES} { return DATABASES;}


{SELECT} {return SELECT;}
{FROM} {return FROM;}
{WHERE} {return WHERE;}
{AND} {return AND;}
{OR} {return OR;}

{INSERT} {return INSERT;}
{INTO} {return INTO;}
{VALUES} {return VALUES;}

{DELETE} {return DELETE;}
{UPDATE} {return UPDATE;}
{SET} {return SET;}


{ID} { yylval.chval = strdup(yytext); return ID;}
{NUMBER} {yylval.intval = atoi(yytext); return NUMBER;}
"("  { return '('; }
")"  { return ')'; }
";"  { return ';'; }
","  { return ','; }
"*"  { return '*'; }
"."  { return '.'; }
"<"  { return '<'; }
">"  { return '>'; }
"="  { return '='; }
"!"  { return '!'; }

\n   { cur_line++; }
{STRING} {*(yytext+strlen(yytext)-1) = '\0'; yylval.chval = strdup(yytext+1);  return STRING;}
[ \t]+                /* ignore whitespace */;
"//".*                                    { /* DO NOTHING */ }
%%

int yywrap()//此函数必须由用户提供
{
    return 1;
}