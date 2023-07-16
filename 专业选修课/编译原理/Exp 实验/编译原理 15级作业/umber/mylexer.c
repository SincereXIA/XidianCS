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
* mylexer.c
* C source file generated from mylexer.l.
* 
* Date: 06/28/18
* Time: 19:56:36
* 
* ALex Version: 2.07
****************************************************************************/

#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#line 1 ".\\mylexer.l"

/****************************************************************************
mylexer.l
ParserWizard generated Lex file.

Date: 2012Äê4ÔÂ5ÈÕ
****************************************************************************/

#include "myparser.h"


#line 51 "mylexer.c"
/* repeated because of possible precompiled header */
#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#include ".\mylexer.h"

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/* yytext */
static char YYNEAR yysatext[(YYTEXT_SIZE) + 1];		/* extra char for \0 */
char YYFAR *YYNEAR YYDCDECL yystext = yysatext;
char YYFAR *YYNEAR YYDCDECL yytext = yysatext;
int YYNEAR YYDCDECL yystext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_max = (YYTEXT_MAX);

/* yystatebuf */
#if (YYTEXT_SIZE) != 0
static int YYNEAR yysastatebuf[(YYTEXT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysstatebuf = yysastatebuf;
int YYFAR *YYNEAR YYDCDECL yystatebuf = yysastatebuf;
#else
int YYFAR *YYNEAR YYDCDECL yysstatebuf = NULL;
int YYFAR *YYNEAR YYDCDECL yystatebuf = NULL;
#endif

/* yyunputbuf */
#if (YYUNPUT_SIZE) != 0
static int YYNEAR yysaunputbuf[(YYUNPUT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = yysaunputbuf;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = yysaunputbuf;
#else
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = NULL;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = NULL;
#endif
int YYNEAR YYDCDECL yysunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_max = (YYUNPUT_MAX);

/* backwards compatability with lex */
#ifdef input
#ifdef YYPROTOTYPE
int YYCDECL yyinput(void)
#else
int YYCDECL yyinput()
#endif
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
#ifdef YYPROTOTYPE
void YYCDECL yyoutput(int ch)
#else
void YYCDECL yyoutput(ch)
int ch;
#endif
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
#ifdef YYPROTOTYPE
void YYCDECL yyunput(int ch)
#else
void YYCDECL yyunput(ch)
int ch;
#endif
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		/* <warning: unreachable code> off */
#endif
#endif

#ifdef YYPROTOTYPE
int YYCDECL yylexeraction(int action)
#else
int YYCDECL yylexeraction(action)
int action;
#endif
{
	yyreturnflg = YYTRUE;
	switch (action) {
	case 1:
		{
#line 29 ".\\mylexer.l"
return USE;
#line 172 "mylexer.c"
		}
		break;
	case 2:
		{
#line 30 ".\\mylexer.l"
return SELECT;
#line 179 "mylexer.c"
		}
		break;
	case 3:
		{
#line 31 ".\\mylexer.l"
return CREATE;
#line 186 "mylexer.c"
		}
		break;
	case 4:
		{
#line 32 ".\\mylexer.l"
return DATABASE;
#line 193 "mylexer.c"
		}
		break;
	case 5:
		{
#line 33 ".\\mylexer.l"
return INTO;
#line 200 "mylexer.c"
		}
		break;
	case 6:
		{
#line 34 ".\\mylexer.l"
return VALUES;
#line 207 "mylexer.c"
		}
		break;
	case 7:
		{
#line 35 ".\\mylexer.l"
return INSERT;
#line 214 "mylexer.c"
		}
		break;
	case 8:
		{
#line 36 ".\\mylexer.l"
return FROM;
#line 221 "mylexer.c"
		}
		break;
	case 9:
		{
#line 37 ".\\mylexer.l"
return TABLE;
#line 228 "mylexer.c"
		}
		break;
	case 10:
		{
#line 38 ".\\mylexer.l"
return TABLES;
#line 235 "mylexer.c"
		}
		break;
	case 11:
		{
#line 39 ".\\mylexer.l"
return INTEGER;
#line 242 "mylexer.c"
		}
		break;
	case 12:
		{
#line 40 ".\\mylexer.l"
return VARCHAR;
#line 249 "mylexer.c"
		}
		break;
	case 13:
		{
#line 41 ".\\mylexer.l"
return DOUBLE;
#line 256 "mylexer.c"
		}
		break;
#line 42 ".\\mylexer.l"
			//return CHAR;
#line 261 "mylexer.c"
	case 14:
		{
#line 43 ".\\mylexer.l"
return PRIMARY;
#line 266 "mylexer.c"
		}
		break;
	case 15:
		{
#line 44 ".\\mylexer.l"
return KEY;
#line 273 "mylexer.c"
		}
		break;
	case 16:
		{
#line 45 ".\\mylexer.l"
return DROP;
#line 280 "mylexer.c"
		}
		break;
	case 17:
		{
#line 46 ".\\mylexer.l"
return VALUE;
#line 287 "mylexer.c"
		}
		break;
	case 18:
		{
#line 47 ".\\mylexer.l"
return QUIT;
#line 294 "mylexer.c"
		}
		break;
	case 19:
		{
#line 48 ".\\mylexer.l"
return LOGICO;
#line 301 "mylexer.c"
		}
		break;
	case 20:
		{
#line 49 ".\\mylexer.l"
return SHOW;
#line 308 "mylexer.c"
		}
		break;
	case 21:
		{
#line 50 ".\\mylexer.l"
return DATABASES;
#line 315 "mylexer.c"
		}
		break;
	case 22:
		{
#line 52 ".\\mylexer.l"
return END;
#line 322 "mylexer.c"
		}
		break;
	case 23:
		{
#line 53 ".\\mylexer.l"
yylval.strval = yytext; return OBJECT;
#line 329 "mylexer.c"
		}
		break;
	case 24:
		{
#line 54 ".\\mylexer.l"
yylval.strval = yytext; return NUMBER;
#line 336 "mylexer.c"
		}
		break;
	case 25:
		{
#line 55 ".\\mylexer.l"
yylval.strval = yytext; return DOUBLE;
#line 343 "mylexer.c"
		}
		break;
	case 26:
		{
#line 56 ".\\mylexer.l"
yylval.strval = yytext; return STRING;
#line 350 "mylexer.c"
		}
		break;
	case 27:
		{
#line 57 ".\\mylexer.l"

#line 357 "mylexer.c"
		}
		break;
	case 28:
		{
#line 58 ".\\mylexer.l"
return *yytext;
#line 364 "mylexer.c"
		}
		break;
	case 29:
		{
#line 59 ".\\mylexer.l"
yylval.strval = yytext; return FECHA_P;
#line 371 "mylexer.c"
		}
		break;
	case 30:
		{
#line 60 ".\\mylexer.l"
yylval.strval = yytext; return ABRE_P;
#line 378 "mylexer.c"
		}
		break;
	case 31:
		{
#line 61 ".\\mylexer.l"
yylval.strval = yytext; return ALL;
#line 385 "mylexer.c"
		}
		break;
	case 32:
		{
#line 62 ".\\mylexer.l"
 return 0; 
#line 392 "mylexer.c"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = YYFALSE;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		/* <warning: unreachable code> to the old state */
#endif
#endif
YYCONST yymatch_t YYNEARFAR YYBASED_CODE YYDCDECL yymatch[] = {
	0
};

int YYNEAR YYDCDECL yytransitionmax = 294;
YYCONST yytransition_t YYNEARFAR YYBASED_CODE YYDCDECL yytransition[] = {
	{ 0, 0 },
	{ 3, 1 },
	{ 4, 1 },
	{ 3, 3 },
	{ 59, 27 },
	{ 43, 15 },
	{ 39, 40 },
	{ 58, 26 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 40, 40 },
	{ 60, 27 },
	{ 44, 15 },
	{ 128, 99 },
	{ 61, 27 },
	{ 45, 15 },
	{ 105, 72 },
	{ 3, 1 },
	{ 115, 81 },
	{ 3, 3 },
	{ 80, 48 },
	{ 81, 48 },
	{ 106, 72 },
	{ 116, 99 },
	{ 5, 1 },
	{ 6, 1 },
	{ 7, 1 },
	{ 8, 1 },
	{ 116, 81 },
	{ 9, 1 },
	{ 98, 64 },
	{ 99, 64 },
	{ 62, 28 },
	{ 10, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 11, 1 },
	{ 89, 56 },
	{ 12, 1 },
	{ 68, 34 },
	{ 38, 5 },
	{ 52, 22 },
	{ 69, 34 },
	{ 90, 56 },
	{ 53, 22 },
	{ 63, 29 },
	{ 14, 1 },
	{ 15, 1 },
	{ 16, 1 },
	{ 17, 1 },
	{ 64, 30 },
	{ 65, 31 },
	{ 18, 1 },
	{ 66, 32 },
	{ 19, 1 },
	{ 20, 1 },
	{ 67, 33 },
	{ 46, 16 },
	{ 70, 35 },
	{ 21, 1 },
	{ 71, 36 },
	{ 72, 37 },
	{ 22, 1 },
	{ 23, 1 },
	{ 24, 1 },
	{ 25, 1 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 11, 11 },
	{ 5, 38 },
	{ 47, 17 },
	{ 26, 1 },
	{ 27, 1 },
	{ 28, 1 },
	{ 29, 1 },
	{ 48, 18 },
	{ 73, 41 },
	{ 30, 1 },
	{ 74, 42 },
	{ 31, 1 },
	{ 32, 1 },
	{ 75, 43 },
	{ 76, 44 },
	{ 77, 45 },
	{ 33, 1 },
	{ 78, 46 },
	{ 79, 47 },
	{ 34, 1 },
	{ 35, 1 },
	{ 36, 1 },
	{ 37, 1 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 49, 19 },
	{ 82, 49 },
	{ 83, 50 },
	{ 84, 51 },
	{ 85, 52 },
	{ 86, 53 },
	{ 87, 54 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 88, 55 },
	{ 50, 20 },
	{ 91, 57 },
	{ 92, 58 },
	{ 13, 174 },
	{ 93, 59 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 13, 174 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 39, 39 },
	{ 94, 60 },
	{ 95, 61 },
	{ 96, 62 },
	{ 97, 63 },
	{ 51, 21 },
	{ 82, 65 },
	{ 100, 66 },
	{ 101, 67 },
	{ 102, 68 },
	{ 103, 69 },
	{ 104, 70 },
	{ 88, 71 },
	{ 42, 14 },
	{ 107, 73 },
	{ 108, 74 },
	{ 109, 75 },
	{ 110, 76 },
	{ 111, 77 },
	{ 112, 78 },
	{ 113, 79 },
	{ 114, 80 },
	{ 54, 23 },
	{ 117, 83 },
	{ 118, 84 },
	{ 119, 85 },
	{ 120, 86 },
	{ 121, 87 },
	{ 122, 89 },
	{ 123, 90 },
	{ 107, 91 },
	{ 124, 92 },
	{ 125, 93 },
	{ 126, 94 },
	{ 111, 95 },
	{ 112, 96 },
	{ 113, 97 },
	{ 127, 98 },
	{ 55, 24 },
	{ 129, 100 },
	{ 130, 101 },
	{ 131, 102 },
	{ 120, 103 },
	{ 132, 104 },
	{ 133, 105 },
	{ 134, 106 },
	{ 135, 108 },
	{ 136, 109 },
	{ 137, 110 },
	{ 138, 114 },
	{ 139, 115 },
	{ 140, 117 },
	{ 141, 118 },
	{ 142, 119 },
	{ 143, 121 },
	{ 144, 122 },
	{ 41, 123 },
	{ 145, 124 },
	{ 146, 125 },
	{ 147, 126 },
	{ 148, 127 },
	{ 149, 128 },
	{ 150, 129 },
	{ 151, 130 },
	{ 152, 131 },
	{ 153, 132 },
	{ 154, 133 },
	{ 57, 134 },
	{ 155, 135 },
	{ 156, 136 },
	{ 157, 137 },
	{ 158, 138 },
	{ 159, 139 },
	{ 160, 140 },
	{ 161, 141 },
	{ 162, 142 },
	{ 163, 143 },
	{ 164, 144 },
	{ 155, 145 },
	{ 165, 146 },
	{ 157, 147 },
	{ 158, 148 },
	{ 166, 149 },
	{ 160, 150 },
	{ 167, 151 },
	{ 162, 152 },
	{ 163, 153 },
	{ 164, 154 },
	{ 168, 156 },
	{ 169, 159 },
	{ 170, 161 },
	{ 171, 165 },
	{ 169, 166 },
	{ 170, 167 },
	{ 172, 168 },
	{ 173, 171 },
	{ 174, 172 },
	{ 174, 173 },
	{ 56, 25 }
};

YYCONST yystate_t YYNEARFAR YYBASED_CODE YYDCDECL yystate[] = {
	{ 0, 0, 0 },
	{ 174, -8, 0 },
	{ 1, 0, 0 },
	{ 0, -6, 27 },
	{ 0, 0, 32 },
	{ -5, 14, 0 },
	{ 0, 0, 30 },
	{ 0, 0, 29 },
	{ 0, 0, 31 },
	{ 0, 0, 28 },
	{ 40, 0, 24 },
	{ 40, 31, 24 },
	{ 0, 0, 22 },
	{ 174, 0, 23 },
	{ 123, 126, 23 },
	{ 174, -60, 23 },
	{ 174, -18, 23 },
	{ 174, 8, 23 },
	{ 174, 17, 23 },
	{ 174, 52, 23 },
	{ 174, 76, 23 },
	{ 174, 118, 23 },
	{ 174, -15, 23 },
	{ 174, 152, 23 },
	{ 174, 150, 23 },
	{ 174, 228, 23 },
	{ 134, -107, 23 },
	{ 174, -93, 23 },
	{ 174, -81, 23 },
	{ 174, -56, 23 },
	{ 174, -47, 23 },
	{ 174, -37, 23 },
	{ 174, -45, 23 },
	{ 174, -45, 23 },
	{ 174, -49, 23 },
	{ 174, -26, 23 },
	{ 174, -42, 23 },
	{ 174, -23, 23 },
	{ 0, 50, 26 },
	{ 0, 138, 25 },
	{ 0, -40, 0 },
	{ 174, 31, 23 },
	{ 174, 29, 23 },
	{ 174, 17, 23 },
	{ 174, 17, 23 },
	{ 174, 24, 23 },
	{ 174, 32, 23 },
	{ 174, 27, 23 },
	{ 174, -56, 23 },
	{ 174, 33, 23 },
	{ 174, 52, 23 },
	{ 174, 51, 23 },
	{ 174, 49, 23 },
	{ 174, 47, 23 },
	{ 174, 61, 23 },
	{ 174, 85, 23 },
	{ 174, -26, 23 },
	{ 174, 59, 23 },
	{ 174, 56, 23 },
	{ 174, 43, 23 },
	{ 174, 79, 23 },
	{ 174, 86, 23 },
	{ 174, 93, 23 },
	{ 174, 88, 23 },
	{ 174, -78, 23 },
	{ 174, 80, 23 },
	{ 174, 99, 23 },
	{ 174, 98, 23 },
	{ 174, 96, 23 },
	{ 174, 94, 23 },
	{ 174, 108, 23 },
	{ 174, 106, 23 },
	{ 174, -85, 23 },
	{ 174, 127, 23 },
	{ 174, 145, 23 },
	{ 174, 146, 23 },
	{ 174, 146, 23 },
	{ 174, 133, 23 },
	{ 174, 130, 23 },
	{ 174, 138, 23 },
	{ 174, 147, 23 },
	{ 174, -44, 11 },
	{ 174, 0, 15 },
	{ 174, 145, 23 },
	{ 174, 142, 23 },
	{ 174, 151, 23 },
	{ 174, 134, 23 },
	{ 174, 146, 23 },
	{ 174, 0, 1 },
	{ 174, 138, 23 },
	{ 174, 157, 23 },
	{ 174, 111, 23 },
	{ 174, 129, 23 },
	{ 174, 130, 23 },
	{ 174, 130, 23 },
	{ 174, 117, 23 },
	{ 174, 114, 23 },
	{ 174, 122, 23 },
	{ 174, 131, 23 },
	{ 174, -81, 11 },
	{ 174, 129, 23 },
	{ 174, 126, 23 },
	{ 174, 135, 23 },
	{ 174, 118, 23 },
	{ 174, 130, 23 },
	{ 174, 122, 23 },
	{ 174, 141, 23 },
	{ 174, 0, 12 },
	{ 174, 157, 23 },
	{ 174, 176, 23 },
	{ 174, 167, 23 },
	{ 174, 0, 16 },
	{ 174, 0, 18 },
	{ 174, 0, 8 },
	{ 174, 162, 23 },
	{ 174, 174, 23 },
	{ 174, 0, 5 },
	{ 174, 179, 23 },
	{ 174, 182, 23 },
	{ 174, 181, 23 },
	{ 174, 0, 20 },
	{ 174, 180, 23 },
	{ 174, 181, 23 },
	{ 174, 179, 23 },
	{ 174, 136, 23 },
	{ 174, 155, 23 },
	{ 174, 146, 23 },
	{ 174, 141, 23 },
	{ 174, 153, 23 },
	{ 174, 158, 23 },
	{ 174, 161, 23 },
	{ 174, 160, 23 },
	{ 174, 159, 23 },
	{ 174, 160, 23 },
	{ 174, 158, 23 },
	{ 174, 194, 23 },
	{ 174, 199, 23 },
	{ 174, 196, 23 },
	{ 174, 182, 23 },
	{ 174, 198, 23 },
	{ 174, 189, 23 },
	{ 174, 187, 23 },
	{ 174, 186, 23 },
	{ 174, 188, 9 },
	{ 174, 189, 17 },
	{ 174, 172, 23 },
	{ 174, 177, 23 },
	{ 174, 174, 23 },
	{ 174, 160, 23 },
	{ 174, 176, 23 },
	{ 174, 167, 23 },
	{ 174, 165, 23 },
	{ 174, 164, 23 },
	{ 174, 166, 9 },
	{ 174, 167, 17 },
	{ 174, 0, 3 },
	{ 174, 200, 23 },
	{ 174, 0, 13 },
	{ 174, 0, 7 },
	{ 174, 202, 23 },
	{ 174, 0, 19 },
	{ 174, 196, 23 },
	{ 174, 0, 2 },
	{ 174, 0, 10 },
	{ 174, 0, 6 },
	{ 174, 171, 23 },
	{ 174, 173, 23 },
	{ 174, 167, 23 },
	{ 174, 220, 23 },
	{ 174, 0, 11 },
	{ 174, 0, 14 },
	{ 174, 189, 23 },
	{ 174, 208, 4 },
	{ 174, 177, 4 },
	{ 0, 63, 21 }
};

YYCONST yybackup_t YYNEARFAR YYBASED_CODE YYDCDECL yybackup[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

#line 66 ".\\mylexer.l"


/////////////////////////////////////////////////////////////////////////////
// programs section



