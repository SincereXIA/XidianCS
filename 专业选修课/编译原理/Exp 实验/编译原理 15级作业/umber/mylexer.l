%{
/****************************************************************************
mylexer.l
ParserWizard generated Lex file.

Date: 2012年4月5日
****************************************************************************/

#include "myparser.h"

%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

//辅助定义正规式
/*digit	[0-9]
digits	{digit}+
optional_fraction	("."{digits})?
optional_exponent	(E[+-]?{digits})?*/

// place any declarations here
%%

/////////////////////////////////////////////////////////////////////////////
// rules section
//词法规则正规式

"use"|"USE"				return USE;
"select"|"SELECT"		return SELECT;
"create"|"CREATE"		return CREATE;
"database"|"DATABASE"	return DATABASE;
"into"|"INTO"			return INTO;
"values"|"VALUES"		return VALUES;
"insert"|"INSERT"		return INSERT;
"from"|"FROM"			return FROM;
"table"|"TABLE"			return TABLE;
"tables"|"TABLES"		return TABLES;
"int"|"INT"|"integer"|"INTEGER"		return INTEGER;
"char"|"CHAR"|"varchar"|"VARCHAR"		return VARCHAR;
"double"|"DOUBLE"		return DOUBLE;
			//return CHAR;
"primary"|"PRIMARY"		return PRIMARY;
"key"|"KEY"				return KEY;
"drop"|"DROP"			return DROP;
"value"|"VALUE"			return VALUE;
"exit"|"EXIT"			return QUIT;
"logico"|"LOGICO"		return LOGICO;
"show"|"SHOW"			return SHOW;
"databases"|"DATABASES" return DATABASES;

[;]			return END;	/*return *yytext;*/
([a-zA-Z_]+[0-9_]*)+		{yylval.strval = yytext; return OBJECT;}
[0]|([1-9][0-9]*)			{yylval.strval = yytext; return NUMBER;}
[0-9][0-9]*[\.][0-9]*		{yylval.strval = yytext; return DOUBLE;}
([\']([^']|'')*[\'])		{yylval.strval = yytext; return STRING;}
[ \t]+ {}
[,]								return *yytext;
[)]                     {yylval.strval = yytext; return FECHA_P;}
[(]                     {yylval.strval = yytext; return ABRE_P;}
[*]                     {yylval.strval = yytext; return ALL;}
"\n" { return 0; }

// place your Lex rules here

%%

/////////////////////////////////////////////////////////////////////////////
// programs section


