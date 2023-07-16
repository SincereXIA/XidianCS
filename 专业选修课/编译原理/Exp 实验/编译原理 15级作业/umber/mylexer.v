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
# mylexer.v
# Lex verbose file generated from mylexer.l.
# 
# Date: 06/28/18
# Time: 19:56:36
# 
# ALex Version: 2.07
#############################################################################


#############################################################################
# Expressions
#############################################################################

    1  "use"|"USE"

    2  "select"|"SELECT"

    3  "create"|"CREATE"

    4  "database"|"DATABASE"

    5  "into"|"INTO"

    6  "values"|"VALUES"

    7  "insert"|"INSERT"

    8  "from"|"FROM"

    9  "table"|"TABLE"

   10  "tables"|"TABLES"

   11  "int"|"INT"|"integer"|"INTEGER"

   12  "char"|"CHAR"|"varchar"|"VARCHAR"

   13  "double"|"DOUBLE"

   14  "primary"|"PRIMARY"

   15  "key"|"KEY"

   16  "drop"|"DROP"

   17  "value"|"VALUE"

   18  "exit"|"EXIT"

   19  "logico"|"LOGICO"

   20  "show"|"SHOW"

   21  "databases"|"DATABASES"

   22  [;]

   23  ([a-zA-Z_]+[0-9_]*)+

   24  [0]|([1-9][0-9]*)

   25  [0-9][0-9]*[\.][0-9]*

   26  ([\']([^']|'')*[\'])

   27  [ \t]+

   28  [,]

   29  [)]

   30  [(]

   31  [*]

   32  "\n"


#############################################################################
# States
#############################################################################

state 1
	INITIAL

	0x09               goto 3
	0x0a               goto 4
	0x20               goto 3
	0x27               goto 5
	0x28               goto 6
	0x29               goto 7
	0x2a               goto 8
	0x2c               goto 9
	0x30               goto 10
	0x31 - 0x39 (9)    goto 11
	0x3b               goto 12
	0x41 - 0x42 (2)    goto 13
	0x43               goto 14
	0x44               goto 15
	0x45               goto 16
	0x46               goto 17
	0x47 - 0x48 (2)    goto 13
	0x49               goto 18
	0x4a               goto 13
	0x4b               goto 19
	0x4c               goto 20
	0x4d - 0x4f (3)    goto 13
	0x50               goto 21
	0x51 - 0x52 (2)    goto 13
	0x53               goto 22
	0x54               goto 23
	0x55               goto 24
	0x56               goto 25
	0x57 - 0x5a (4)    goto 13
	0x5f               goto 13
	0x61 - 0x62 (2)    goto 13
	0x63               goto 26
	0x64               goto 27
	0x65               goto 28
	0x66               goto 29
	0x67 - 0x68 (2)    goto 13
	0x69               goto 30
	0x6a               goto 13
	0x6b               goto 31
	0x6c               goto 32
	0x6d - 0x6f (3)    goto 13
	0x70               goto 33
	0x71 - 0x72 (2)    goto 13
	0x73               goto 34
	0x74               goto 35
	0x75               goto 36
	0x76               goto 37
	0x77 - 0x7a (4)    goto 13


state 2
	^INITIAL

	0x09               goto 3
	0x0a               goto 4
	0x20               goto 3
	0x27               goto 5
	0x28               goto 6
	0x29               goto 7
	0x2a               goto 8
	0x2c               goto 9
	0x30               goto 10
	0x31 - 0x39 (9)    goto 11
	0x3b               goto 12
	0x41 - 0x42 (2)    goto 13
	0x43               goto 14
	0x44               goto 15
	0x45               goto 16
	0x46               goto 17
	0x47 - 0x48 (2)    goto 13
	0x49               goto 18
	0x4a               goto 13
	0x4b               goto 19
	0x4c               goto 20
	0x4d - 0x4f (3)    goto 13
	0x50               goto 21
	0x51 - 0x52 (2)    goto 13
	0x53               goto 22
	0x54               goto 23
	0x55               goto 24
	0x56               goto 25
	0x57 - 0x5a (4)    goto 13
	0x5f               goto 13
	0x61 - 0x62 (2)    goto 13
	0x63               goto 26
	0x64               goto 27
	0x65               goto 28
	0x66               goto 29
	0x67 - 0x68 (2)    goto 13
	0x69               goto 30
	0x6a               goto 13
	0x6b               goto 31
	0x6c               goto 32
	0x6d - 0x6f (3)    goto 13
	0x70               goto 33
	0x71 - 0x72 (2)    goto 13
	0x73               goto 34
	0x74               goto 35
	0x75               goto 36
	0x76               goto 37
	0x77 - 0x7a (4)    goto 13


state 3
	0x09               goto 3
	0x20               goto 3

	match 27


state 4
	match 32


state 5
	0x00 - 0x26 (39)   goto 5
	0x27               goto 38
	0x28 - 0xff (216)  goto 5


state 6
	match 30


state 7
	match 29


state 8
	match 31


state 9
	match 28


state 10
	0x2e               goto 39
	0x30 - 0x39 (10)   goto 40

	match 24


state 11
	0x2e               goto 39
	0x30 - 0x39 (10)   goto 11

	match 24


state 12
	match 22


state 13
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 14
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x47 (7)    goto 13
	0x48               goto 41
	0x49 - 0x51 (9)    goto 13
	0x52               goto 42
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 15
	0x30 - 0x39 (10)   goto 13
	0x41               goto 43
	0x42 - 0x4e (13)   goto 13
	0x4f               goto 44
	0x50 - 0x51 (2)    goto 13
	0x52               goto 45
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 16
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x57 (23)   goto 13
	0x58               goto 46
	0x59 - 0x5a (2)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 17
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 47
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 18
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4d (13)   goto 13
	0x4e               goto 48
	0x4f - 0x5a (12)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 19
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 49
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 20
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4e (14)   goto 13
	0x4f               goto 50
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 21
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 51
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 22
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 52
	0x46 - 0x47 (2)    goto 13
	0x48               goto 53
	0x49 - 0x5a (18)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 23
	0x30 - 0x39 (10)   goto 13
	0x41               goto 54
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 24
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 55
	0x54 - 0x5a (7)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 25
	0x30 - 0x39 (10)   goto 13
	0x41               goto 56
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 26
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x67 (7)    goto 13
	0x68               goto 57
	0x69 - 0x71 (9)    goto 13
	0x72               goto 58
	0x73 - 0x7a (8)    goto 13

	match 23


state 27
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 59
	0x62 - 0x6e (13)   goto 13
	0x6f               goto 60
	0x70 - 0x71 (2)    goto 13
	0x72               goto 61
	0x73 - 0x7a (8)    goto 13

	match 23


state 28
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x77 (23)   goto 13
	0x78               goto 62
	0x79 - 0x7a (2)    goto 13

	match 23


state 29
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 63
	0x73 - 0x7a (8)    goto 13

	match 23


state 30
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6d (13)   goto 13
	0x6e               goto 64
	0x6f - 0x7a (12)   goto 13

	match 23


state 31
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 65
	0x66 - 0x7a (21)   goto 13

	match 23


state 32
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6e (14)   goto 13
	0x6f               goto 66
	0x70 - 0x7a (11)   goto 13

	match 23


state 33
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 67
	0x73 - 0x7a (8)    goto 13

	match 23


state 34
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 68
	0x66 - 0x67 (2)    goto 13
	0x68               goto 69
	0x69 - 0x7a (18)   goto 13

	match 23


state 35
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 70
	0x62 - 0x7a (25)   goto 13

	match 23


state 36
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 71
	0x74 - 0x7a (7)    goto 13

	match 23


state 37
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 72
	0x62 - 0x7a (25)   goto 13

	match 23


state 38
	0x27               goto 5

	match 26


state 39
	0x30 - 0x39 (10)   goto 39

	match 25


state 40
	0x2e               goto 39
	0x30 - 0x39 (10)   goto 40


state 41
	0x30 - 0x39 (10)   goto 13
	0x41               goto 73
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 42
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 74
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 43
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x53 (19)   goto 13
	0x54               goto 75
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 44
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x54 (20)   goto 13
	0x55               goto 76
	0x56 - 0x5a (5)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 45
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4e (14)   goto 13
	0x4f               goto 77
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 46
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x48 (8)    goto 13
	0x49               goto 78
	0x4a - 0x5a (17)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 47
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4e (14)   goto 13
	0x4f               goto 79
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 48
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 80
	0x54               goto 81
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 49
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x58 (24)   goto 13
	0x59               goto 82
	0x5a               goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 50
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x46 (6)    goto 13
	0x47               goto 83
	0x48 - 0x5a (19)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 51
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x48 (8)    goto 13
	0x49               goto 84
	0x4a - 0x5a (17)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 52
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4b (11)   goto 13
	0x4c               goto 85
	0x4d - 0x5a (14)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 53
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4e (14)   goto 13
	0x4f               goto 86
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 54
	0x30 - 0x39 (10)   goto 13
	0x41               goto 13
	0x42               goto 87
	0x43 - 0x5a (24)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 55
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 88
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 56
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4b (11)   goto 13
	0x4c               goto 89
	0x4d - 0x51 (5)    goto 13
	0x52               goto 90
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 57
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 91
	0x62 - 0x7a (25)   goto 13

	match 23


state 58
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 92
	0x66 - 0x7a (21)   goto 13

	match 23


state 59
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x73 (19)   goto 13
	0x74               goto 93
	0x75 - 0x7a (6)    goto 13

	match 23


state 60
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x74 (20)   goto 13
	0x75               goto 94
	0x76 - 0x7a (5)    goto 13

	match 23


state 61
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6e (14)   goto 13
	0x6f               goto 95
	0x70 - 0x7a (11)   goto 13

	match 23


state 62
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x68 (8)    goto 13
	0x69               goto 96
	0x6a - 0x7a (17)   goto 13

	match 23


state 63
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6e (14)   goto 13
	0x6f               goto 97
	0x70 - 0x7a (11)   goto 13

	match 23


state 64
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 98
	0x74               goto 99
	0x75 - 0x7a (6)    goto 13

	match 23


state 65
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x78 (24)   goto 13
	0x79               goto 82
	0x7a               goto 13

	match 23


state 66
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x66 (6)    goto 13
	0x67               goto 100
	0x68 - 0x7a (19)   goto 13

	match 23


state 67
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x68 (8)    goto 13
	0x69               goto 101
	0x6a - 0x7a (17)   goto 13

	match 23


state 68
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6b (11)   goto 13
	0x6c               goto 102
	0x6d - 0x7a (14)   goto 13

	match 23


state 69
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6e (14)   goto 13
	0x6f               goto 103
	0x70 - 0x7a (11)   goto 13

	match 23


state 70
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 13
	0x62               goto 104
	0x63 - 0x7a (24)   goto 13

	match 23


state 71
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 88
	0x66 - 0x7a (21)   goto 13

	match 23


state 72
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6b (11)   goto 13
	0x6c               goto 105
	0x6d - 0x71 (5)    goto 13
	0x72               goto 106
	0x73 - 0x7a (8)    goto 13

	match 23


state 73
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 107
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 74
	0x30 - 0x39 (10)   goto 13
	0x41               goto 108
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 75
	0x30 - 0x39 (10)   goto 13
	0x41               goto 109
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 76
	0x30 - 0x39 (10)   goto 13
	0x41               goto 13
	0x42               goto 110
	0x43 - 0x5a (24)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 77
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4f (15)   goto 13
	0x50               goto 111
	0x51 - 0x5a (10)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 78
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x53 (19)   goto 13
	0x54               goto 112
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 79
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4c (12)   goto 13
	0x4d               goto 113
	0x4e - 0x5a (13)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 80
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 114
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 81
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 115
	0x46 - 0x4e (9)    goto 13
	0x4f               goto 116
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 11


state 82
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 15


state 83
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x48 (8)    goto 13
	0x49               goto 117
	0x4a - 0x5a (17)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 84
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4c (12)   goto 13
	0x4d               goto 118
	0x4e - 0x5a (13)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 85
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 119
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 86
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x56 (22)   goto 13
	0x57               goto 120
	0x58 - 0x5a (3)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 87
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4b (11)   goto 13
	0x4c               goto 121
	0x4d - 0x5a (14)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 88
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 1


state 89
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x54 (20)   goto 13
	0x55               goto 122
	0x56 - 0x5a (5)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 90
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x42 (2)    goto 13
	0x43               goto 123
	0x44 - 0x5a (23)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 91
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 107
	0x73 - 0x7a (8)    goto 13

	match 23


state 92
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 124
	0x62 - 0x7a (25)   goto 13

	match 23


state 93
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 125
	0x62 - 0x7a (25)   goto 13

	match 23


state 94
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 13
	0x62               goto 126
	0x63 - 0x7a (24)   goto 13

	match 23


state 95
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6f (15)   goto 13
	0x70               goto 111
	0x71 - 0x7a (10)   goto 13

	match 23


state 96
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x73 (19)   goto 13
	0x74               goto 112
	0x75 - 0x7a (6)    goto 13

	match 23


state 97
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6c (12)   goto 13
	0x6d               goto 113
	0x6e - 0x7a (13)   goto 13

	match 23


state 98
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 127
	0x66 - 0x7a (21)   goto 13

	match 23


state 99
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 128
	0x66 - 0x6e (9)    goto 13
	0x6f               goto 116
	0x70 - 0x7a (11)   goto 13

	match 11


state 100
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x68 (8)    goto 13
	0x69               goto 129
	0x6a - 0x7a (17)   goto 13

	match 23


state 101
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6c (12)   goto 13
	0x6d               goto 130
	0x6e - 0x7a (13)   goto 13

	match 23


state 102
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 131
	0x66 - 0x7a (21)   goto 13

	match 23


state 103
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x76 (22)   goto 13
	0x77               goto 120
	0x78 - 0x7a (3)    goto 13

	match 23


state 104
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6b (11)   goto 13
	0x6c               goto 132
	0x6d - 0x7a (14)   goto 13

	match 23


state 105
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x74 (20)   goto 13
	0x75               goto 133
	0x76 - 0x7a (5)    goto 13

	match 23


state 106
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x62 (2)    goto 13
	0x63               goto 134
	0x64 - 0x7a (23)   goto 13

	match 23


state 107
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 12


state 108
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x53 (19)   goto 13
	0x54               goto 135
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 109
	0x30 - 0x39 (10)   goto 13
	0x41               goto 13
	0x42               goto 136
	0x43 - 0x5a (24)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 110
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4b (11)   goto 13
	0x4c               goto 137
	0x4d - 0x5a (14)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 111
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 16


state 112
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 18


state 113
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 8


state 114
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 138
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 115
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x46 (6)    goto 13
	0x47               goto 139
	0x48 - 0x5a (19)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 116
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 5


state 117
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x42 (2)    goto 13
	0x43               goto 140
	0x44 - 0x5a (23)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 118
	0x30 - 0x39 (10)   goto 13
	0x41               goto 141
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 119
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x42 (2)    goto 13
	0x43               goto 142
	0x44 - 0x5a (23)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 120
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 20


state 121
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 143
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 122
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 144
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 123
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x47 (7)    goto 13
	0x48               goto 41
	0x49 - 0x5a (18)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 124
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x73 (19)   goto 13
	0x74               goto 145
	0x75 - 0x7a (6)    goto 13

	match 23


state 125
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 13
	0x62               goto 146
	0x63 - 0x7a (24)   goto 13

	match 23


state 126
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6b (11)   goto 13
	0x6c               goto 147
	0x6d - 0x7a (14)   goto 13

	match 23


state 127
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 148
	0x73 - 0x7a (8)    goto 13

	match 23


state 128
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x66 (6)    goto 13
	0x67               goto 149
	0x68 - 0x7a (19)   goto 13

	match 23


state 129
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x62 (2)    goto 13
	0x63               goto 150
	0x64 - 0x7a (23)   goto 13

	match 23


state 130
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 151
	0x62 - 0x7a (25)   goto 13

	match 23


state 131
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x62 (2)    goto 13
	0x63               goto 152
	0x64 - 0x7a (23)   goto 13

	match 23


state 132
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 153
	0x66 - 0x7a (21)   goto 13

	match 23


state 133
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 154
	0x66 - 0x7a (21)   goto 13

	match 23


state 134
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x67 (7)    goto 13
	0x68               goto 57
	0x69 - 0x7a (18)   goto 13

	match 23


state 135
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 155
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 136
	0x30 - 0x39 (10)   goto 13
	0x41               goto 156
	0x42 - 0x5a (25)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 137
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 157
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 138
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x53 (19)   goto 13
	0x54               goto 158
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 139
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 159
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 140
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x4e (14)   goto 13
	0x4f               goto 160
	0x50 - 0x5a (11)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 141
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 161
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 142
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x53 (19)   goto 13
	0x54               goto 162
	0x55 - 0x5a (6)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 143
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 163
	0x54 - 0x5a (7)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 9


state 144
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 164
	0x54 - 0x5a (7)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 17


state 145
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 155
	0x66 - 0x7a (21)   goto 13

	match 23


state 146
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61               goto 165
	0x62 - 0x7a (25)   goto 13

	match 23


state 147
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 157
	0x66 - 0x7a (21)   goto 13

	match 23


state 148
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x73 (19)   goto 13
	0x74               goto 158
	0x75 - 0x7a (6)    goto 13

	match 23


state 149
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 166
	0x66 - 0x7a (21)   goto 13

	match 23


state 150
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x6e (14)   goto 13
	0x6f               goto 160
	0x70 - 0x7a (11)   goto 13

	match 23


state 151
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 167
	0x73 - 0x7a (8)    goto 13

	match 23


state 152
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x73 (19)   goto 13
	0x74               goto 162
	0x75 - 0x7a (6)    goto 13

	match 23


state 153
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 163
	0x74 - 0x7a (7)    goto 13

	match 9


state 154
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 164
	0x74 - 0x7a (7)    goto 13

	match 17


state 155
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 3


state 156
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 168
	0x54 - 0x5a (7)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 157
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 13


state 158
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 7


state 159
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x51 (17)   goto 13
	0x52               goto 169
	0x53 - 0x5a (8)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 160
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 19


state 161
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x58 (24)   goto 13
	0x59               goto 170
	0x5a               goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 162
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 2


state 163
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 10


state 164
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 6


state 165
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 171
	0x74 - 0x7a (7)    goto 13

	match 23


state 166
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x71 (17)   goto 13
	0x72               goto 169
	0x73 - 0x7a (8)    goto 13

	match 23


state 167
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x78 (24)   goto 13
	0x79               goto 170
	0x7a               goto 13

	match 23


state 168
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x44 (4)    goto 13
	0x45               goto 172
	0x46 - 0x5a (21)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 23


state 169
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 11


state 170
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 14


state 171
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x64 (4)    goto 13
	0x65               goto 173
	0x66 - 0x7a (21)   goto 13

	match 23


state 172
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x52 (18)   goto 13
	0x53               goto 174
	0x54 - 0x5a (7)    goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 4


state 173
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x72 (18)   goto 13
	0x73               goto 174
	0x74 - 0x7a (7)    goto 13

	match 4


state 174
	0x30 - 0x39 (10)   goto 13
	0x41 - 0x5a (26)   goto 13
	0x5f               goto 13
	0x61 - 0x7a (26)   goto 13

	match 21


#############################################################################
# Summary
#############################################################################

1 start state(s)
32 expression(s), 174 state(s)


#############################################################################
# End of File
#############################################################################
