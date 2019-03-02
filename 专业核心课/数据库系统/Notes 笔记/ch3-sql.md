# ch3 SQL 语言

## 三级模式体系结构

- 外模式：视图
- 模式：基本表
- 内模式：存储文件

**两级映像**

外模式/模式映像

模式/内模式映像

## SQL 功能

### 数据定义

> SQL提供了专门的语言用来定义数据库、表、索引等数据库对象，这些语言被称作数据定义语言（Data Definition Language，DDL）。

SQL 的数据定义语句

![1545524928840](ch3-sql.assets/1545524928840.png)

#### 创建基本表

```mssql
CREATE  TABLE  <表名>
  ( <列名> <数据类型>[ <列级完整性约束条件> ]
    [，<列名> <数据类型>[ <列级完整性约束条件>] ] …
    [，<表级完整性约束条件> ]  )；
```

- 常用数据类型

  - INTEGER或INT  全字长二进制整数
  - FLOAT  双字长浮点数
  - CHARACTER(n)或CHAR(n)     长度为n的定长字符串
  - VARCHAR(n)  　　最大长度为n的变长字符串
  - DATE       日期型，格式为yyyy-mm-dd
  - TIME       时间型，格式为hh.mm.ss
  - TIMESTAMP           日期加时间

- 常用完整性约束

  1. ==主码约束： PRIMARY  KEY==
  2. 唯一性约束：UNIQUE(不能取相同值但允许多个空值)
  3. 非空值约束：NOT NULL
  4. ==参照完整性约束：FOREIGN KEY (<列名>) REFERENCES <表名>(<列名>)==
  5. CHECK约束：CHECK ( <谓词>)
  6. 断言(Assertion)约束 （后讲）

  命名约束：

  ```
  CONSTRAINT  chk_ssex CHECK (Ssex IN (‘M’,’F’)),
  ```



  ![mark](http://media.sumblog.cn/blog/20181223/P43TA2vDIosE.png?imageMogr2/thumbnail/!60p)

#### 删除基本表

```
DROP  TABLE <表名> ; 
```

> 基本表删除后，**表里的数据、表上的索引都会被删除**，**表上的视图往往仍然保留，但无法引用。**
>
> 删除基本表时，系统会从数据字典中删去有关该基本表及其索引的描述。 

#### 修改基本表

```mssql
ALTER TABLE <表名>
[ ADD  <新列名>  <数据类型>  [ 完整性约束 ] ]
[ DROP  <完整性约束名>  <列名>]
[ ALTER  <列名> <数据类型> ]；
```

- ADD子句：增加新列和新的完整性约束条件
- DROP子句：删除指定的完整性约束条件
- ALTER子句：用于修改列名和数据类型

如需在表中添加列，请使用下列语法:

```
ALTER TABLE table_name
ADD column_name datatype
```

要删除表中的列，请使用下列语法：

```
ALTER TABLE table_name 
DROP COLUMN column_name
```

要改变表中列的数据类型，请使用下列语法：

```
ALTER TABLE table_name
ALTER COLUMN column_name datatype
```

#### 定义索引

> **CREATE INDEX 语句用于在表中创建索引。**
>
> **在不读取整个表的情况下，索引使数据库应用程序可以更快地查找数据。**

- 单一索引(Unique Index)：每一个索引值只对应唯一的数据记录。
- **聚簇索引**(Cluster Index)：索引项顺序与表中数据记录的物理顺序一致。
- 普通索引：允许一个Search-key项对应多条存储记录。

```mssql
CREATE [UNIQUE] [CLUSTER] INDEX <索引名>  ON 　<表名>(<列名>[<次序>][,<列名>[<次序>] ]…) ;
```

- <表名>：指定要建索引的基本表名字
- 索引可以建立在该表的一列或多列上，各列名之间用逗号分隔
- <次序>：指定索引值的排列次序。升序：ASC，降序：DESC，**缺省值：ASC**
- UNIQUE：表明此索引的每一个索引值只对应唯一的数据记录
- CLUSTER：表示要建立的索引是聚簇索引

![mark](http://media.sumblog.cn/blog/20181223/uU25hi40SG6d.png?imageMogr2/thumbnail/!50p)

### 数据查询

```mssql
SELECT  [ ALL | DISTINCT ] <目标列表达式1>
        [, <目标列表达式2>] …
FROM  <表名或视图名1> （别名）[,  <表名或视图名2> （别名）] …
[ WHERE  <条件表达式> ]
[ GROUP BY  <列名1> [ HAVING <条件表达式> ] ]
[ ORDER BY  <列名2> [ ASC | DESC ] ] ;
```

#### 单表查询

- 目标列为表达式的查询

  ```mssql
  SELECT  Sname, 1996 - Sage
  FROM  Student ;
  ```

- 使用别名改变查询结果的列标题

  ```mssql
  SELECT  Sname  NAME, 'Year of Birth:'  BIRTH,
  		1996 - Sage  BIRTHYEAR, 
  		ISLOWER ( Sdept )  DEPARTMENT
  ```

- 消除结果中重复的行

  ```mssql
   SELECT  DISTINCT  Sno FROM  SC ;
  ```

- 限定查询范围

  | 查询条件 | 谓　词                                                       |
  | -------- | ------------------------------------------------------------ |
  | 比　　较 | = , < ,  > ,    <= ,  >= ,  <> ,    != ,  !> ,  !<    ;   NOT + 上述比较符 |
  | 确定范围 | BETWEEN … AND … ,   NOT  BETWEEN … AND …                     |
  | 确定集合 | IN ,  NOT IN                                                 |
  | 字符匹配 | LIKE ,  NOT LIKE                                             |
  | 空　　值 | IS NULL ,  IS NOT NULL                                       |
  | 多重条件 | AND ,  OR   -                                                |

  - 确定范围

    ```mssql
    SELECT  Sname , Sdept , Sage
    FROM  Student
    WHERE  Sage  BETWEEN  20  AND  23 ;
    ```

  - 确定集合

    ```mssql
    SELECT  Sname , Ssex
    FROM  Student
    WHERE  Sdept  NOT  IN ( 'IS', 'MA', 'CS' ) ;
    ```

  - 字符串匹配

    ```mssql
    [NOT] LIKE  ‘<匹配模板>’  [ESCAPE ‘<换码字符>’]
    ```

    - **% (百分号)：代表任意长度(可以为0)的字符串。**

      例：a%b表示以a开头，以b结尾的任意长度的字符串。如acb，addgb，ab 等都满足该匹配串。

    - **_ (下横线)：代表任意单个字符。**

      例：a_b表示以a开头，以b结尾的长度为3的任意字符串。如acb，afb等都满足该匹配串，一个汉字两个下横线

    - **当要查询的字符串本身就含有 % 或 _ 时，要使用  `ESCAPE '<换码字符>'`短语对通配符进行转义。**

      ```mssql
      SELECT  Cno , Ccredit
      FROM  Course
      WHERE  Cname  LIKE  'DB\_Design'  ESCAPE '\' ;
      	　　;转义符‘\’表示模板中出现在其后的第一个字符不再是通配符，而是字符本身。
      ```

  - 涉及空值的查询

    **==使用谓词 IS NULL 或 IS NOT NULL，“IS NULL” 不能用 “= NULL” 代替！==**

- 排序输出

  ```mssql
  ORDER BY
  ```

  - **升序：ASC ，==排列为空值的元组最后显示 （空值最大）==**
  - 降序：DESC

#### 连接查询

- 等值连接、自然连接

  > SELECT子句和WHERE子句中出现的两个同名属性前要加所属表名作前辍以区别，无同名则可省前辍。

- 自身连接

  **需要给表起别名以示区别，由于所有的属性名都是同名属性， 因此必须使用别名前缀**

- 外连接 **Outer Join**

  - 左外连接：在连接的右边出现空行
  - 右外连接：在连接的左边出现空行
  - 左右外链接：在连接的左右出现空行

#### 分组查询

**集函数**

- 计数 COUNT (使用 DISTINCT 避免重复计数)
- 计算总和 SUM
- 计算平均值 AVG
- 求最大值 MAX
- 求最小值 MIN

```mssql
[ GROUP BY  <列名1>[, 列名2…] [ HAVING <条件表达式> ] ] 
```

==未对查询结果分组，集函数将作用于整个查询结果==

对查询结果分组后，集函数将分别作用于每个组 

**==使用GROUP BY子句后，SELECT子句的列名表中只能出现分组属性和集函数==**

集函数只能用于SELECT子句和 HAVING短语之中，而**绝对不能出现在 WHERE 子句**中(WHERE子句执行过程是对记录逐一检验，并没有结果集，故无法施加集函数)。  

![mark](http://media.sumblog.cn/blog/20181223/nPMQrirY1FGp.png?imageMogr2/thumbnail/!60p)

#### 嵌套查询

> 一个SELECT - FROM - WHERE语句称为一个查询块，**将一个查询块嵌套在另一个查询块的WHERE子句或HAVING短语的条件中的查询称为嵌套查询**

```mssql
SELECT  Sname		；外层查询/父查询
  FROM  Student
  WHERE  Sno  IN
    	  ( SELECT  Sno              ；内层查询/子查询
                FROM  SC
                WHERE  Cno = 'c2' ) ;
```

- 带有 IN 谓词的子查询

- 带有比较运算的子查询

  > 当能确切知道内层查询返回单值时，可用比较运算符（>，<，=，>=，<=，!=或<>)

- 带有 ANY 和 ALL 谓词的子查询

  ```
  > ANY(
  	SLLECT * 
  	...
  )
  ```

- 带有 EXISTS 谓词的子查询 相关子查询
  $$
  \forall x ( \mathbf { P } ( x ) \rightarrow \mathbf { Q } ) \Leftrightarrow \neg \exists x ( \mathbf { P } ( x ) \wedge \neg \mathbf { Q } )
  $$


  ![mark](http://media.sumblog.cn/blog/20181223/Hv7uCCV0ywCO.png?imageMogr2/thumbnail/!62p)

#### 集合查询

> 将两个SELECT – FROM – WHERE查询块用集合操作语句联结起来。

- 并 UNION
- 交 INTERSECT
- 差 MINUS

### 数据更新

#### 插入数据

```mssql
INSERT
INTO  <表名>  [(<属性列1>[, <属性列2 >…)]
VALUES  (<常量1> [, <常量2>]    … ) ;
```

#### 修改数据

```mssql
UPDATE  <表名>
SET  <列名>=<表达式>[, <列名>=<表达式>]…
[WHERE  <条件>] ;
```

> *可以修改多个记录*
>
> 将所有学生的年龄增加 1 岁：
>
> ```mssql
> UPDATE  Student
> SET  Sage = Sage+1 ;
> WHERE  Sdept = 'IS' ;
> ```

#### 删除数据

```mssql
DELETE
FROM  <表名>
[WHERE  <条件>] ;
```

### 数据控制

#### 授权

> 将数据库中的某些对象的某些操作权限赋予某些用户

```mssql
GRANT <权限>[,<权限>]... 
		[ON <对象类型> <对象名>]
		TO <用户>[,<用户>]...
		[WITH GRANT OPTION] ;
```

| 对象   | 对象类型 | 操作权限                                                   |
| ------ | -------- | ---------------------------------------------------------- |
| 属性列 | TABLE    | SELECT,   INSERT, UPDATE, DELETE,    ALL   PRIVILEGES      |
| 视　图 | TABLE    | SELECT,   INSERT, UPDATE, DELETE,    ALL   PRIVILEGES      |
| 基本表 | TABLE    | SELECT,  UPDATE, DELETE, ALTER, INDEX,    ALL   PRIVILEGES |
| 数据库 | DATABASE | CREATETAB                                                  |

![mark](http://media.sumblog.cn/blog/20181224/pL3S4qrVvXPI.png?imageMogr2/thumbnail/!60p)

#### 收回权限

```mssql
REVOKE  <权限>[,<权限>]... 
[ON  <对象类型> <对象名>]
FROM  <用户>[,<用户>]... ;
```



## 视图

### 建立视图

```mssql
  CREATE  VIEW  <视图名>  [(<列名>  [，<列名>]…)]
		AS  <子查询>
		[WITH  CHECK  OPTION] ;
```

下列情况需要制定视图的所有列名

- 某个目标列是集函数或列表达式
- 多表连接时选出了几个同名列作为视图的字段

数据库管理系统执行视图查询的方法有：**实体化视图、视图消解**

## 触发器

```
CREATE TRIGGER <触发器名>
	{BEFORE | AFTER} <INSERT | Delete| Update> on <表>
	For each {row | statement}
	as begin
	...
	end;
```

## 嵌入式 SQL

前缀 EXEC SQL

1. **主变量**
   -  主语言向SQL语句**提供参数**
   -  将SQL语句查询数据库的结果交主语言进一步处理

2. **SQL 通信区** ( SQLCA,  SQL Communication Area )
   - 向主语言**传递SQL语句的执行状态信息**
   - 主语言能够据此**控制程序流程**

3. **游标**：　解决**集合性操作语言与过程性操作语言的不匹配**
   - 游标是SQL查询语句向宿主语言提供查询结果集的一段公共缓冲区