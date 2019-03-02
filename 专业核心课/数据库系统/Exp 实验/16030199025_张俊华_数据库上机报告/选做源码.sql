CREATE TABLE [department] (
[dno] int NOT NULL,
[dname] varchar(100) NOT NULL,
PRIMARY KEY ([dno]) 
)
GO
CREATE TABLE [major] (
[mno] int NOT NULL,
[mname] varchar(100) NOT NULL,
[dno] int NULL,
PRIMARY KEY ([mno]) 
)
GO
CREATE TABLE [class] (
[cno] int NOT NULL,
[mno] int NOT NULL,
PRIMARY KEY ([cno]) 
)
GO
CREATE TABLE [student] (
[sno] int NOT NULL,
[sname] varchar(20) NOT NULL,
[cno] int NOT NULL,
PRIMARY KEY ([sno]) 
)
GO
CREATE TABLE [teacher] (
[tno] int NOT NULL,
[tname] varchar(20) NOT NULL,
[dno] int NOT NULL,
PRIMARY KEY ([tno]) 
)
GO
CREATE TABLE [lesson] (
[lno] int NOT NULL,
[lname] varchar(255) NOT NULL,
[credit] int NOT NULL,
[property] varchar(10) NOT NULL,
PRIMARY KEY ([lno]) 
)
GO
CREATE TABLE [curricual-variable] (
[sno] int NOT NULL,
[lno] int NOT NULL,
[grade] int NOT NULL,
PRIMARY KEY ([sno], [lno]) 
)
GO
CREATE TABLE [plan] (
[pno] int NOT NULL,
[dno] int NOT NULL,
[mno] int NOT NULL,
[year] int NOT NULL,
[b-credit] int NOT NULL,
[x-credit] int NOT NULL,
[r-credit] int NOT NULL,
PRIMARY KEY ([pno], [dno], [mno], [year]) 
)
GO
CREATE TABLE [conduct] (
[tno] int NOT NULL,
[lno] int NOT NULL,
[cno] int NOT NULL,
PRIMARY KEY ([lno], [cno], [tno]) 
)
GO

ALTER TABLE [major] ADD CONSTRAINT [major-department] FOREIGN KEY ([dno]) REFERENCES [department] ([dno])
GO
ALTER TABLE [class] ADD CONSTRAINT [class-major] FOREIGN KEY ([mno]) REFERENCES [major] ([mno])
GO
ALTER TABLE [student] ADD CONSTRAINT [student-class] FOREIGN KEY ([cno]) REFERENCES [class] ([cno])
GO
ALTER TABLE [teacher] ADD CONSTRAINT [teacher-department] FOREIGN KEY ([dno]) REFERENCES [department] ([dno])
GO
ALTER TABLE [curricual-variable] ADD CONSTRAINT [cur-stu] FOREIGN KEY ([sno]) REFERENCES [student] ([sno])
GO
ALTER TABLE [curricual-variable] ADD CONSTRAINT [cur-les] FOREIGN KEY ([lno]) REFERENCES [lesson] ([lno])
GO
ALTER TABLE [plan] ADD CONSTRAINT [plan-dep] FOREIGN KEY ([dno]) REFERENCES [department] ([dno])
GO
ALTER TABLE [plan] ADD CONSTRAINT [plan-maj] FOREIGN KEY ([mno]) REFERENCES [major] ([mno])
GO
ALTER TABLE [conduct] ADD CONSTRAINT [cond-teacher] FOREIGN KEY ([tno]) REFERENCES [teacher] ([tno])
GO
ALTER TABLE [conduct] ADD CONSTRAINT [cond-class] FOREIGN KEY ([cno]) REFERENCES [class] ([cno])
GO
ALTER TABLE [conduct] ADD CONSTRAINT [cond-lesson] FOREIGN KEY ([lno]) REFERENCES [lesson] ([lno])
GO

CREATE TRIGGER conduct_instead
on conduct
INSTEAD of update,insert
as 
IF exists (
    SELECT * FROM conduct,inserted
    where conduct.cno = inserted.cno AND
          conduct.tno = inserted.tno AND
          not exists(
            SELECT * FROM inserted,deleted
            WHERE inserted.tno = deleted.tno
          )
)
    RAISERROR('同一老师不允许给同一个班带多门课程',16,10)
ELSE
BEGIN
    DELETE FROM conduct
    WHERE  exists(
        select * from deleted
        WHERE conduct.tno = deleted.tno AND
                conduct.cno = deleted.cno AND
                conduct.lno = deleted.lno
    )

    INSERT into conduct
    SELECT * FROM inserted
end
GO

CREATE VIEW student_grade
AS
SELECT student.sno, sname,lname,grade,credit,property,[curricual-variable].year
FROM student,[curricual-variable],lesson
WHERE student.sno = [curricual-variable].sno AND
        [curricual-variable].[lno] = lesson.lno
GO


SELECT * FROM student_grade
GO

create view student_avg
AS
SELECT distinct stu.sno,stu.sname,必修均分,限选均分,任选均分,总均分,必修总学分,限选总学分,任选总学分
FROM student_grade as stu
INNER JOIN (
    SELECT sno,sname,AVG(grade) as '必修均分',SUM(credit) as '必修总学分'
    FROM student_grade
    WHERE property = '必修'
    group by sno,sname
) as b
on stu.sno = b.sno
INNER JOIN (
    SELECT sno,sname,AVG(grade) as '限选均分',SUM(credit) as '限选总学分'
    FROM student_grade
    WHERE property = '限选'
    group by sno,sname
)as x
on stu.sno = x.sno
INNER JOIN (
    SELECT sno,sname,AVG(grade) as '任选均分',SUM(credit) as '任选总学分'
    FROM student_grade
    WHERE property = '任选'
    group by sno,sname
)as r
on stu.sno = r.sno
INNER JOIN (
    SELECT sno,sname,AVG(grade) as '总均分',SUM(credit) as '总学分'
    FROM student_grade
    group by sno,sname
)as z
on stu.sno = z.sno
go

SELECT * FROM student_avg
order by 总均分 desc
GO

CREATE view student_teacher
AS
SELECT student.sno,sname,tname,lname
FROM student,teacher,conduct,[curricual-variable],lesson
WHERE student.cno = conduct.cno AND
        teacher.tno = conduct.tno and
        conduct.lno = [curricual-variable].lno and
        student.sno = [curricual-variable].sno AND
        lesson.lno = conduct.lno
GO

SELECT * FROM student_teacher
GO

create view student_pass_credit
AS
SELECT distinct stu.sno,stu.sname,stu.year,isNULL(bx,0) as 必修通过学分,isNULL(xx,0) as 限选通过学分,isNULL(rx,0) as 任选通过学分
FROM student_grade as stu
left JOIN (
    SELECT sno,sname,student_grade.year,SUM(credit) as bx
    FROM student_grade
    WHERE property = '必修' and grade >=60
    group by sno,sname,student_grade.year
) as b
on stu.sno = b.sno AND stu.year = b.year
left JOIN (
    SELECT sno,sname,student_grade.year,SUM(credit) as xx
    FROM student_grade
    WHERE property = '限选' and grade >=60
    group by sno,sname,student_grade.year
)as x
on stu.sno = x.sno AND stu.year = x.year
left JOIN (
    SELECT sno,sname,student_grade.year,SUM(credit) as rx
    FROM student_grade
    WHERE property = '任选' and grade >=60
    group by sno,sname,student_grade.year 
)as r 
on stu.sno = r.sno AND stu.year = r.year
left JOIN (
    SELECT sno,sname,student_grade.year,SUM(credit) as z
    FROM student_grade
    where  grade >=60
    group by sno,sname,student_grade.year
)as z 
on stu.sno = z.sno AND stu.year = z.year
go

select * FROM student_pass_credit
GO

CREATE VIEW student_expel
as
SELECT student.sno,student.sname
from student_pass_credit,[plan],student,class,major,department
WHERE   student.sno = student_pass_credit.sno AND
        student.cno = class.cno and
        class.mno = major.mno AND
        major.dno = department.dno AND
        [plan].dno = major.dno AND
        [plan].mno = class.mno AND
        [plan].year = student_pass_credit.year AND(
        必修通过学分<[plan].[b-credit] -2 OR
        限选通过学分 < [plan].[x-credit] -2 OR
        任选通过学分 < [plan].[r-credit]-2 
        )
GO

drop view student_expel

SELECT * FROM student_expel
