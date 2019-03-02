---创建触发器,自动修改班级表中的班级人数,
---一次仅能修改一个学生记录。

/*插入触发器，inserted表结构与Student表结构相同*/
create trigger classIns
on Student
for insert
as   
	--定义变量@classNo,用于接收所插入的学生所属班号
	declare @classNo char(8)
	--如果插入记录大于1条，则回滚
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--找出要插入学生的班号放入变量@classNo
			select @classNo=ClassNo from inserted 
			--更新班级表中对应班号为@classNo的班级人数
			update Class set StudentNum=StudentNum+1
			where ClassId=@classNo
		end

/*
/*删除触发器,deleted表结构与Student表结构相同*/
create trigger classDel
on Student
for delete
as
	--定义变量@classNo，用于接收所删除学生所属的班号
	declare @classNo char(8)
	--如果删除记录大于1条，则回滚
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--找出要删除学生的班号放入变量@classNo
			select @classNo=ClassNo from deleted 
			--更新班级表中对应班号为@classNo的班级人数
			update Class set StudentNum=StudentNum-1
			where ClassId=@classNo
		end
*/

/*
--更新触发器，deleted表，inserted表结构与Student表结构相同*/
create trigger classUpt
on Student
for update
as
	--定义变量@newclassNo，用于接收所更新学生所属的新班号
	--定义变量@oldclassNo，用于接收所更新学生所属的旧班号
	declare @newclassNo char(8)
	declare @oldclassNo char(8)
	--如果更新记录大于1条，则回滚
	if(select count(*) from inserted)>1
		rollback
	else
		begin
		--找出要更新学生的新班号放入变量@newclassNo
		--找出要更新学生的旧班号放入变量@oldclassNo
			select @newclassNo=ClassNo from inserted 
			select @oldclassNo=ClassNo from deleted
			--更新旧班级和新班级中的班级人数
			update Class set StudentNum=StudentNum-1
			where ClassId=@oldclassNo
			update Class set StudentNum=StudentNum+1
			where ClassId=@newclassNo
		end
*/
