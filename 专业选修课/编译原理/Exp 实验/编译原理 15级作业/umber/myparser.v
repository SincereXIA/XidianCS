#############################################################################
#                         A C A D E M I C   C O P Y
# 
# This file was produced by an ACADEMIC COPY of Parser Generator. It is for
# use in non-commercial software only. An ACADEMIC COPY of Parser Generator
# can only be used by a student, or a member of an academic community. If
# however you want to use Parser Generator for commercial purposes then you
# will need to purchase a license. For more information see the online help or
# go to the Bumble-Bee Software homepage at:
# 
# http://www.bumblebeesoftware.com
# 
# This notice must remain present in the file. It cannot be removed.
#############################################################################

#############################################################################
# myparser.v
# YACC verbose file generated from myparser.y.
# 
# Date: 06/28/18
# Time: 19:56:37
# 
# AYACC Version: 2.07
#############################################################################


##############################################################################
# Rules
##############################################################################

    0  $accept : start $end

    1  start : create_database
    2        | QUIT END
    3        | drop_database
    4        | select_database
    5        | show_database
    6        | create_table
    7        | show_tables
    8        | drop_table
    9        | insert
   10        | select

   11  $$1 :

   12  create_database : CREATE DATABASE $$1 object END

   13  $$2 :

   14  drop_database : DROP DATABASE $$2 object END

   15  $$3 :

   16  select_database : USE $$3 object END

   17  object : OBJECT

   18  show_database : SHOW DATABASES END

   19  $$4 :

   20  create_table : CREATE TABLE $$4 object ABRE_P table_column_attr FECHA_P END

   21  table_column_attr : column_create type
   22                    | column_create type ',' table_column_attr

   23  type : INTEGER

   24  $$5 :

   25  $$6 :

   26  type : VARCHAR $$5 ABRE_P NUMBER $$6 FECHA_P
   27       | DOUBLE

   28  column_create : OBJECT

   29  show_tables : SHOW TABLES END

   30  drop_table : DROP TABLE object END

   31  $$7 :

   32  $$8 :

   33  insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END

   34  opt_column_list :
   35                  | ABRE_P column_list FECHA_P

   36  value_list : value
   37             | value ',' value_list

   38  value : DOUBLE
   39        | NUMBER
   40        | STRING

   41  column_list : column
   42              | column ',' column_list

   43  column : OBJECT

   44  $$9 :

   45  select : SELECT $$9 selection FROM table_select END

   46  table_select : OBJECT

   47  selection : ALL

   48  $$10 :

   49  selection : OBJECT $$10 selection2

   50  selection2 :

   51  $$11 :

   52  selection2 : ',' OBJECT $$11 selection2


##############################################################################
# States
##############################################################################

state 0
	$accept : . start $end

	INSERT  shift 1
	SELECT  shift 2
	CREATE  shift 3
	DROP  shift 4
	QUIT  shift 5
	USE  shift 6
	SHOW  shift 7

	select  goto 8
	drop_database  goto 9
	insert  goto 10
	show_tables  goto 11
	show_database  goto 12
	drop_table  goto 13
	create_database  goto 14
	create_table  goto 15
	start  goto 16
	select_database  goto 17


state 1
	insert : INSERT . INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END

	INTO  shift 18


state 2
	select : SELECT . $$9 selection FROM table_select END
	$$9 : .  (44)

	.  reduce 44

	$$9  goto 19


state 3
	create_database : CREATE . DATABASE $$1 object END
	create_table : CREATE . TABLE $$4 object ABRE_P table_column_attr FECHA_P END

	TABLE  shift 20
	DATABASE  shift 21


state 4
	drop_database : DROP . DATABASE $$2 object END
	drop_table : DROP . TABLE object END

	TABLE  shift 22
	DATABASE  shift 23


state 5
	start : QUIT . END

	END  shift 24


state 6
	select_database : USE . $$3 object END
	$$3 : .  (15)

	.  reduce 15

	$$3  goto 25


state 7
	show_tables : SHOW . TABLES END
	show_database : SHOW . DATABASES END

	DATABASES  shift 26
	TABLES  shift 27


state 8
	start : select .  (10)

	.  reduce 10


state 9
	start : drop_database .  (3)

	.  reduce 3


state 10
	start : insert .  (9)

	.  reduce 9


state 11
	start : show_tables .  (7)

	.  reduce 7


state 12
	start : show_database .  (5)

	.  reduce 5


state 13
	start : drop_table .  (8)

	.  reduce 8


state 14
	start : create_database .  (1)

	.  reduce 1


state 15
	start : create_table .  (6)

	.  reduce 6


state 16
	$accept : start . $end  (0)

	$end  accept


state 17
	start : select_database .  (4)

	.  reduce 4


state 18
	insert : INSERT INTO . $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END
	$$7 : .  (31)

	.  reduce 31

	$$7  goto 28


state 19
	select : SELECT $$9 . selection FROM table_select END

	OBJECT  shift 29
	ALL  shift 30

	selection  goto 31


state 20
	create_table : CREATE TABLE . $$4 object ABRE_P table_column_attr FECHA_P END
	$$4 : .  (19)

	.  reduce 19

	$$4  goto 32


state 21
	create_database : CREATE DATABASE . $$1 object END
	$$1 : .  (11)

	.  reduce 11

	$$1  goto 33


state 22
	drop_table : DROP TABLE . object END

	OBJECT  shift 34

	object  goto 35


state 23
	drop_database : DROP DATABASE . $$2 object END
	$$2 : .  (13)

	.  reduce 13

	$$2  goto 36


state 24
	start : QUIT END .  (2)

	.  reduce 2


state 25
	select_database : USE $$3 . object END

	OBJECT  shift 34

	object  goto 37


state 26
	show_database : SHOW DATABASES . END

	END  shift 38


state 27
	show_tables : SHOW TABLES . END

	END  shift 39


state 28
	insert : INSERT INTO $$7 . OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END

	OBJECT  shift 40


state 29
	selection : OBJECT . $$10 selection2
	$$10 : .  (48)

	.  reduce 48

	$$10  goto 41


state 30
	selection : ALL .  (47)

	.  reduce 47


state 31
	select : SELECT $$9 selection . FROM table_select END

	FROM  shift 42


state 32
	create_table : CREATE TABLE $$4 . object ABRE_P table_column_attr FECHA_P END

	OBJECT  shift 34

	object  goto 43


state 33
	create_database : CREATE DATABASE $$1 . object END

	OBJECT  shift 34

	object  goto 44


state 34
	object : OBJECT .  (17)

	.  reduce 17


state 35
	drop_table : DROP TABLE object . END

	END  shift 45


state 36
	drop_database : DROP DATABASE $$2 . object END

	OBJECT  shift 34

	object  goto 46


state 37
	select_database : USE $$3 object . END

	END  shift 47


state 38
	show_database : SHOW DATABASES END .  (18)

	.  reduce 18


state 39
	show_tables : SHOW TABLES END .  (29)

	.  reduce 29


state 40
	insert : INSERT INTO $$7 OBJECT . $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END
	$$8 : .  (32)

	.  reduce 32

	$$8  goto 48


state 41
	selection : OBJECT $$10 . selection2
	selection2 : .  (50)

	','  shift 49
	.  reduce 50

	selection2  goto 50


state 42
	select : SELECT $$9 selection FROM . table_select END

	OBJECT  shift 51

	table_select  goto 52


state 43
	create_table : CREATE TABLE $$4 object . ABRE_P table_column_attr FECHA_P END

	ABRE_P  shift 53


state 44
	create_database : CREATE DATABASE $$1 object . END

	END  shift 54


state 45
	drop_table : DROP TABLE object END .  (30)

	.  reduce 30


state 46
	drop_database : DROP DATABASE $$2 object . END

	END  shift 55


state 47
	select_database : USE $$3 object END .  (16)

	.  reduce 16


state 48
	insert : INSERT INTO $$7 OBJECT $$8 . opt_column_list VALUES ABRE_P value_list FECHA_P END
	opt_column_list : .  (34)

	ABRE_P  shift 56
	.  reduce 34

	opt_column_list  goto 57


state 49
	selection2 : ',' . OBJECT $$11 selection2

	OBJECT  shift 58


state 50
	selection : OBJECT $$10 selection2 .  (49)

	.  reduce 49


state 51
	table_select : OBJECT .  (46)

	.  reduce 46


state 52
	select : SELECT $$9 selection FROM table_select . END

	END  shift 59


state 53
	create_table : CREATE TABLE $$4 object ABRE_P . table_column_attr FECHA_P END

	OBJECT  shift 60

	column_create  goto 61
	table_column_attr  goto 62


state 54
	create_database : CREATE DATABASE $$1 object END .  (12)

	.  reduce 12


state 55
	drop_database : DROP DATABASE $$2 object END .  (14)

	.  reduce 14


state 56
	opt_column_list : ABRE_P . column_list FECHA_P

	OBJECT  shift 63

	column_list  goto 64
	column  goto 65


state 57
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list . VALUES ABRE_P value_list FECHA_P END

	VALUES  shift 66


state 58
	selection2 : ',' OBJECT . $$11 selection2
	$$11 : .  (51)

	.  reduce 51

	$$11  goto 67


state 59
	select : SELECT $$9 selection FROM table_select END .  (45)

	.  reduce 45


state 60
	column_create : OBJECT .  (28)

	.  reduce 28


state 61
	table_column_attr : column_create . type ',' table_column_attr
	table_column_attr : column_create . type

	INTEGER  shift 68
	VARCHAR  shift 69
	DOUBLE  shift 70

	type  goto 71


state 62
	create_table : CREATE TABLE $$4 object ABRE_P table_column_attr . FECHA_P END

	FECHA_P  shift 72


state 63
	column : OBJECT .  (43)

	.  reduce 43


state 64
	opt_column_list : ABRE_P column_list . FECHA_P

	FECHA_P  shift 73


state 65
	column_list : column .  (41)
	column_list : column . ',' column_list

	','  shift 74
	.  reduce 41


state 66
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES . ABRE_P value_list FECHA_P END

	ABRE_P  shift 75


state 67
	selection2 : ',' OBJECT $$11 . selection2
	selection2 : .  (50)

	','  shift 49
	.  reduce 50

	selection2  goto 76


state 68
	type : INTEGER .  (23)

	.  reduce 23


state 69
	type : VARCHAR . $$5 ABRE_P NUMBER $$6 FECHA_P
	$$5 : .  (24)

	.  reduce 24

	$$5  goto 77


state 70
	type : DOUBLE .  (27)

	.  reduce 27


state 71
	table_column_attr : column_create type . ',' table_column_attr
	table_column_attr : column_create type .  (21)

	','  shift 78
	.  reduce 21


state 72
	create_table : CREATE TABLE $$4 object ABRE_P table_column_attr FECHA_P . END

	END  shift 79


state 73
	opt_column_list : ABRE_P column_list FECHA_P .  (35)

	.  reduce 35


state 74
	column_list : column ',' . column_list

	OBJECT  shift 63

	column_list  goto 80
	column  goto 65


state 75
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P . value_list FECHA_P END

	DOUBLE  shift 81
	NUMBER  shift 82
	STRING  shift 83

	value_list  goto 84
	value  goto 85


state 76
	selection2 : ',' OBJECT $$11 selection2 .  (52)

	.  reduce 52


state 77
	type : VARCHAR $$5 . ABRE_P NUMBER $$6 FECHA_P

	ABRE_P  shift 86


state 78
	table_column_attr : column_create type ',' . table_column_attr

	OBJECT  shift 60

	column_create  goto 61
	table_column_attr  goto 87


state 79
	create_table : CREATE TABLE $$4 object ABRE_P table_column_attr FECHA_P END .  (20)

	.  reduce 20


state 80
	column_list : column ',' column_list .  (42)

	.  reduce 42


state 81
	value : DOUBLE .  (38)

	.  reduce 38


state 82
	value : NUMBER .  (39)

	.  reduce 39


state 83
	value : STRING .  (40)

	.  reduce 40


state 84
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list . FECHA_P END

	FECHA_P  shift 88


state 85
	value_list : value . ',' value_list
	value_list : value .  (36)

	','  shift 89
	.  reduce 36


state 86
	type : VARCHAR $$5 ABRE_P . NUMBER $$6 FECHA_P

	NUMBER  shift 90


state 87
	table_column_attr : column_create type ',' table_column_attr .  (22)

	.  reduce 22


state 88
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P . END

	END  shift 91


state 89
	value_list : value ',' . value_list

	DOUBLE  shift 81
	NUMBER  shift 82
	STRING  shift 83

	value_list  goto 92
	value  goto 85


state 90
	type : VARCHAR $$5 ABRE_P NUMBER . $$6 FECHA_P
	$$6 : .  (25)

	.  reduce 25

	$$6  goto 93


state 91
	insert : INSERT INTO $$7 OBJECT $$8 opt_column_list VALUES ABRE_P value_list FECHA_P END .  (33)

	.  reduce 33


state 92
	value_list : value ',' value_list .  (37)

	.  reduce 37


state 93
	type : VARCHAR $$5 ABRE_P NUMBER $$6 . FECHA_P

	FECHA_P  shift 94


state 94
	type : VARCHAR $$5 ABRE_P NUMBER $$6 FECHA_P .  (26)

	.  reduce 26


##############################################################################
# Summary
##############################################################################

27 token(s), 34 nonterminal(s)
53 grammar rule(s), 95 state(s)


##############################################################################
# End of File
##############################################################################
