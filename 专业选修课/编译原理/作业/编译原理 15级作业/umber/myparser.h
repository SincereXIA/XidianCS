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
* myparser.h
* C header file generated from myparser.y.
* 
* Date: 06/28/18
* Time: 19:56:37
* 
* AYACC Version: 2.07
****************************************************************************/

#ifndef _MYPARSER_H
#define _MYPARSER_H

#include <yypars.h>

#ifndef YYSTYPE
union tagYYSTYPE {
#line 10 ".\\myparser.y"

    int intval;
    double floatval;
    int subtok;
    char *strval;

#line 41 "myparser.h"
};

#define YYSTYPE union tagYYSTYPE
#endif

extern YYSTYPE YYNEAR yylval;

#define INSERT 257
#define INTO 258
#define VALUES 259
#define SELECT 260
#define FROM 261
#define CREATE 262
#define TABLE 263
#define INTEGER 264
#define VARCHAR 265
#define DOUBLE 266
#define CHAR 267
#define PRIMARY 268
#define KEY 269
#define REFERENCES 270
#define DATABASE 271
#define DROP 272
#define OBJECT 273
#define NUMBER 274
#define VALUE 275
#define QUIT 276
#define LIST_TABLES 277
#define LIST_TABLE 278
#define CONNECT 279
#define HELP 280
#define LIST_DBASES 281
#define CLEAR 282
#define CONTR 283
#define WHERE 284
#define OPERADOR 285
#define RELACIONAL 286
#define LOGICO 287
#define ALL 288
#define SINAL 289
#define FECHA_P 290
#define ABRE_P 291
#define STRING 292
#define END 293
#define USE 294
#define SHOW 295
#define DATABASES 296
#define TABLES 297
#endif
