use mytest

--创建一个游标，逐行显示选修了<数据库>课程的学生姓名、成绩和该课程的平均分

--定义变量及赋初值
declare @sName char(20)
declare @score smallint
declare @sumscore int, @countscore smallint
set @sumscore=0
set @countscore=0
--定义游标
declare mycur cursor for 
select Sname,Grade
from Student a,Course b,SC c
where a.Sno=c.Sno and b.Cno=c.Cno and b.Cname='数据库'
--打开游标
open mycur                                              

fetch mycur into @sName, @score        ---获取当前游标的值放到变量@sName @score
while(@@FETCH_STATUS=0)
begin
	select @sName 学生姓名, @score 课程成绩  
	set @sumscore=@sumscore+@score                      ---计算总分
	set @countscore=@countscore+1                       ---计算选课人数
	fetch mycur into @sName, @score                     ---获取下一个游标值
end
if @countscore>0
	select @sumscore/@countscore  课程平均分             
else
	select 0.00 课程平均分
--关闭游标
close mycur                                             ---关闭游标
--释放游标
deallocate mycur                                        ---释放游标