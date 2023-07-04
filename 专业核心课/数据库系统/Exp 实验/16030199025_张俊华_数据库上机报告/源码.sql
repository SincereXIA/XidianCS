---- 基本表，约束
CREATE TABLE S(
    SNO CHAR(5) PRIMARY KEY,
    SNAME CHAR(20),
    STATUS INTEGER,
    CITY CHAR(20),
);

CREATE TABLE P(
    PNO CHAR(5) PRIMARY KEY,
    PNAME CHAR(20),
    COLOR CHAR(20),
    WEIGHT INTEGER,
);

CREATE TABLE J(
    JNO CHAR(5) PRIMARY KEY,
    JNAME CHAR(20),
    CITY CHAR(20),
);

CREATE TABLE SPJ(
    SNO CHAR(5) NOT NULL,
    PNO CHAR(5) NOT NULL,
    JNO CHAR(5) NOT NULL,
    QTY INTEGER,
    PRIMARY KEY (SNO,PNO,JNO,QTY),
    FOREIGN key (PNO) REFERENCES P(PNO),
    FOREIGN key (JNO) REFERENCES J(JNO),
    FOREIGN key (SNO) REFERENCES S(SNO),
);
GO
----- 视图
CREATE VIEW spj_detail
AS
SELECT J.JNO,J.JNAME,J.CITY as JCITY,P.PNO,P.PNAME,P.COLOR,P.WEIGHT,S.SNO,S.SNAME,S.CITY AS SCITY
			FROM J,P,S,SPJ
			WHERE J.JNO = SPJ.JNO and
						P.PNO = SPJ.PNO and
						S.SNO = SPJ.SNO
GO
---- 实例数据插入
INSERT
into [dbo].[S]
VALUES
('S1','精益',20,'天津'),
('S2','盛锡',10,'北京'),
('S3','东方红',30,'北京'),
('S4','丰泰盛',20,'天津'),
('S5','为民',30,'上海');

INSERT
into [dbo].[P]
VALUES
('P1','螺母','红',12),
('P2','螺栓','绿',17),
('P3','螺丝刀','蓝',14),
('P4','螺丝刀','红',14),
('P5','凸轮','蓝',40),
('P6','齿轮','红',30);

INSERT
into [dbo].[J]
VALUES 
('J1','三建','北京'),
('J2','一汽','长春'),
('J3','弹簧厂','天津'),
('J4','造船厂','天津'),
('J5','机车厂','唐山'),
('J6','无线电厂','常州'),
('J7','半导体厂','南京');

INSERT
into SPJ
VALUES
('S1','P1','J1',200),
('S1','P1','J3',100),
('S1','P1','J4',700),
('S1','P2','J2',100),
('S2','P3','J1',400),
('S2','P3','J2',200),
('S2','P3','J4',500),
('S2','P3','J5',400),
('S2','P5','J1',400),
('S2','P5','J2',100),
('S3','P1','J1',200),
('S3','P3','J1',200),
('S4','P5','J1',100),
('S4','P6','J3',300),
('S4','P6','J4',200),
('S5','P2','J4',100),
('S5','P3','J1',200),
('S5','P6','J2',200),
('S5','P6','J4',500);
go
---- 存储过程，查询供应商的供应信息
CREATE PROC get_s_info
@sno CHAR(5)
AS
BEGIN
SELECT * FROM spj_detail WHERE Sno = @sno
END
GO
---- 修改基本表，加入level 属性列
ALTER TABLE S
    ADD level FLOAT NULL 
GO
---- 触发器自动计算 level
CREATE TRIGGER make_level 
on SPJ 
after update,INSERT,DELETE 
as
BEGIN
    declare @sumqty int
    -- Select rows from a Table 'spj'
        SELECT @sumqty = SUM(SPJ.QTY) FROM SPJ,inserted
        WHERE SPJ.SNO = inserted.SNO
    UPDATE S set level = @sumqty/100 FROM S, inserted
    WHERE S.SNO = inserted.SNO
END
GO
-------------------------
-------------------------
-- 课本作业内容
-------------------------
-------------------------
--求供应工程 J1 零件的供应商号码 SNO
use learnsql;
SELECT DISTINCT SNO FROM SPJ
WHERE JNO = 'J1'

--求供应工程 J1 零件的供应商号码 SNO
SELECT DISTINCT SNO FROM SPJ
WHERE   JNO = 'J1' AND
        PNO = 'P1';

--（3）求供应工程 J1 零件为红色的供应商号码SNO；
SELECT DISTINCT Sno
FROM SPJ
WHERE   Jno = 'J1' AND
        EXISTS(
            SELECT Pno 
            FROM P
            WHERE   Color = '红' AND
                    P.Pno = SPJ.Pno
        );

-- （4）求没有使用天津供应商生产的红色零件的工程号JNO；

SELECT DISTINCT Jno 
FROM   J
WHERE  not  EXISTS(
            SELECT *
            FROM S,P, SPJ
            WHERE   SPJ.JNO = J.JNO AND
                    S.Sno = SPJ.Sno AND
                    S.city = '天津' AND
                    P.Pno = SPJ.Pno AND
                    P.color = '红' 
        );

--（5）求至少用了供应商S1所供应的全部零件的工程号JNO。
SELECT Jno 
FROM SPJ AS spj        
EXCEPT
SELECT Jno 
FROM SPJ AS spja
WHERE EXISTS(
        SELECT *
        FROM SPJ as spjb
        WHERE   spjb.SNO = 'S1' AND
                NOT EXISTS (
                    SELECT *
                    FROM SPJ as spjc 
                    WHERE   spjc.PNO = spjb.PNO AND
                            spjc.JNO = spja.JNO 
                        
                )
);

-- （1）找出所有供应商的姓名和所在城市；
SELECT Sname ,city
FROM S;

-- （2）找出所有零件的名称、颜色、重量；
SELECT Pname,color,weight
FROM P;

-- （3）找出使用供应商S1所供应零件的工程号码；
SELECT DISTINCT Pno 
FROM SPJ
WHERE Sno = 'S1'

--（4）找出工程项目J2使用的各种零件的名称及其数量；
SELECT Pname, QTY 
FROM P,SPJ
WHERE   Jno = 'J2' AND
        P.PNO = SPJ.PNO

--（5）找出上海厂商供应的所有零件号码
SELECT DISTINCT Pno
FROM SPJ,S
WHERE   S.city = '上海' AND
        SPJ.Sno = S.Sno;

--（6）找出使用上海产的零件的工程名称；
SELECT PNAME
FROM P
WHERE   EXISTS(
        select * 
        FROM S, SPJ
        WHERE   P.PNO = SPJ.PNO AND
                S.city = '上海' AND
                SPJ.Sno = S.Sno
);

--（7）找出没有使用天津产的零件的工程号码；
SELECT Pno
FROM P
WHERE   not EXISTS(
        select * 
        FROM S, SPJ
        WHERE   P.PNO = SPJ.PNO AND
                S.city != '天津' AND
                SPJ.Sno = S.Sno
);

-- （8）把全部红色零件的颜色改成蓝色；
UPDATE P
SET color = '蓝'
WHERE P.color = '红';

-- （9）由S5供给J4的零件P6改为由S3供应，请作必要的修改；
UPDATE SPJ
SET Sno = 'S3'
where   Sno = 'S5' AND
        Jno = 'J4' AND 
        Pno = 'P6';

-- （10）从供应商关系中删除S2的记录，并从供应情况关系中删除相应的记录；
DELETE FROM S
WHERE   SNO = 'S2';
DELETE FROM SPJ
WHERE   SNO = 'S2';

-- （11）请将（S2，J6，P4，200）插入供应情况关系。
INSERT INTO SPJ
VALUES
('S2','J6','P4',200);
