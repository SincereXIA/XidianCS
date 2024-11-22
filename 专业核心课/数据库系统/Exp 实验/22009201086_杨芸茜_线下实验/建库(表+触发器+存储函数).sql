
create table course
(
    courseId   int          not null
        primary key,
    courseName varchar(255) not null,
    credit     int          not null
);

create table department
(
    deptId   int          not null
        primary key,
    deptName varchar(255) not null
);

create table major
(
    majorId   int          not null
        primary key,
    majorName varchar(255) not null,
    deptId    int          null,
    constraint major_ibfk_1
        foreign key (deptId) references department (deptId)
);

create table class
(
    classId int not null
        primary key,
    majorId int null,
    constraint class_ibfk_1
        foreign key (majorId) references major (majorId)
);

create index majorId
    on class (majorId);

create index deptId
    on major (deptId);

create table plan
(
    planId   int                                                                                   not null
        primary key,
    majorId  int                                                                                   not null,
    courseId int                                                                                   not null,
    semester enum ('大一上', '大一下', '大二上', '大二下', '大三上', '大三下', '大四上', '大四下') not null comment '学期',
    property enum ('必修', '限选', '任选')                                                         not null comment '课程性质',
    constraint deptId
        unique (majorId, courseId),
    constraint plan_ibfk_1
        foreign key (courseId) references course (courseId),
    constraint plan_ibfk_3
        foreign key (majorId) references major (majorId)
);

create index courseId
    on plan (courseId);

create table student
(
    stuId   int         not null
        primary key,
    stuName varchar(20) not null,
    classId int         not null,
    constraint student_ibfk_1
        foreign key (classId) references class (classId)
);

create table curricular_variable
(
    curricularId int auto_increment
        primary key,
    stuId        int               not null,
    courseId     int               not null,
    grade        float             null,
    flag         tinyint default 1 null,
    constraint curricular_variable_ibfk_1
        foreign key (courseId) references course (courseId),
    constraint curricular_variable_ibfk_2
        foreign key (stuId) references student (stuId)
);

create index courseId
    on curricular_variable (courseId);

create definer = root@localhost trigger trg_check_flag_before_insert
    before insert
    on curricular_variable
    for each row
BEGIN
    -- 如果已经有相同的 stuId 和 courseId 并且 flag=2，则抛出错误
    IF EXISTS (
        SELECT 1 FROM curricular_variable 
        WHERE stuId = NEW.stuId AND courseId = NEW.courseId AND flag = 2
    ) THEN
        SIGNAL SQLSTATE '46000' SET MESSAGE_TEXT = '考试次数已达上限，不允许再次补考';
    END IF;
END;

create index classId
    on student (classId);

create table teacher
(
    teacherId   int         not null
        primary key,
    teacherName varchar(20) not null,
    deptId      int         null,
    constraint teacher_ibfk_1
        foreign key (deptId) references department (deptId)
);

create table conduct
(
    conduct_id int auto_increment
        primary key,
    teacherId  int not null,
    courseId   int not null,
    classId    int not null,
    constraint teacherId
        unique (teacherId, courseId, classId),
    constraint conduct_ibfk_1
        foreign key (classId) references class (classId),
    constraint conduct_ibfk_2
        foreign key (courseId) references course (courseId),
    constraint conduct_ibfk_3
        foreign key (teacherId) references teacher (teacherId)
);

create index classId
    on conduct (classId);

create index courseId
    on conduct (courseId);

create definer = root@localhost trigger conduct_instead
    before insert
    on conduct
    for each row
BEGIN
    -- 检查同一老师是否已经给该班级教授了其他课程
    IF EXISTS (
        SELECT 1 
        FROM conduct c
        WHERE c.teacherId = NEW.teacherId 
          AND c.classId = NEW.classId
          AND c.courseId != NEW.courseId
    ) THEN
        -- 如果违反约束，抛出错误
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = '同一教师不允许给同一个班级教授多门课程';
    END IF;
END;

create index deptId
    on teacher (deptId);

create table temp_flag_update
(
    stuId    int null,
    courseId int null
);

create definer = root@localhost view student_average_scores as
select `s`.`stuId`                                      AS `stuId`,
       `s`.`stuName`                                    AS `stuName`,
       round(avg((case when (`student_status`.`sci`.`property` = '必修') then `student_status`.`sci`.`grade` end)),
             4)                                         AS `必修课平均成绩`,
       round((sum((`student_status`.`sci`.`grade` * `student_status`.`sci`.`credit`)) /
              sum(`student_status`.`sci`.`credit`)), 4) AS `所有课程加权平均成绩`
from (`student_status`.`student_courses_info` `sci` join `student_status`.`student` `s`
      on ((`student_status`.`sci`.`stuId` = `s`.`stuId`)))
group by `s`.`stuId`, `s`.`stuName`
order by `s`.`stuId`;

create definer = root@localhost view student_baseinfo as
select `student_status`.`student`.`stuId`       AS `学号`,
       `student_status`.`student`.`stuName`     AS `姓名`,
       `student_status`.`class`.`classId`       AS `班级号`,
       `student_status`.`major`.`majorName`     AS `专业`,
       `student_status`.`department`.`deptName` AS `所在系`
from `student_status`.`student`
         join `student_status`.`class`
         join `student_status`.`major`
         join `student_status`.`department`
where ((`student_status`.`student`.`classId` = `student_status`.`class`.`classId`) and
       (`student_status`.`class`.`majorId` = `student_status`.`major`.`majorId`) and
       (`student_status`.`major`.`deptId` = `student_status`.`department`.`deptId`))
order by `student_status`.`student`.`stuId`, `student_status`.`class`.`classId`;

create definer = root@localhost view student_courses_info as
select `student_status`.`student`.`stuId`             AS `stuId`,
       `student_status`.`student`.`stuName`           AS `stuName`,
       `student_status`.`course`.`courseId`           AS `courseId`,
       `student_status`.`course`.`courseName`         AS `courseName`,
       `student_status`.`course`.`credit`             AS `credit`,
       `student_status`.`plan`.`property`             AS `property`,
       `student_status`.`plan`.`semester`             AS `semester`,
       `student_status`.`curricular_variable`.`grade` AS `grade`
from (((((`student_status`.`curricular_variable` join `student_status`.`student`
          on ((`student_status`.`curricular_variable`.`stuId` =
               `student_status`.`student`.`stuId`))) join `student_status`.`course`
         on ((`student_status`.`curricular_variable`.`courseId` =
              `student_status`.`course`.`courseId`))) join `student_status`.`class`
        on ((`student_status`.`student`.`classId` = `student_status`.`class`.`classId`))) join `student_status`.`major`
       on ((`student_status`.`class`.`majorId` = `student_status`.`major`.`majorId`))) join `student_status`.`plan`
      on (((`student_status`.`major`.`majorId` = `student_status`.`plan`.`majorId`) and
           (`student_status`.`curricular_variable`.`courseId` = `student_status`.`plan`.`courseId`))))
order by `student_status`.`student`.`stuId`, `student_status`.`course`.`courseId`;

-- comment on column student_courses_info.property not supported: 课程性质

-- comment on column student_courses_info.semester not supported: 学期

create definer = root@localhost view student_credit_summary as
select `s`.`stuId`           AS `stuId`,
       `s`.`stuName`         AS `stuName`,
       sum((case
                when ((`student_status`.`sci`.`property` = '必修') and (`student_status`.`sci`.`grade` >= 60))
                    then `student_status`.`sci`.`credit`
                else 0 end)) AS `必修通过学分`,
       sum((case
                when ((`student_status`.`sci`.`property` = '限选') and (`student_status`.`sci`.`grade` >= 60))
                    then `student_status`.`sci`.`credit`
                else 0 end)) AS `限选通过学分`,
       sum((case
                when ((`student_status`.`sci`.`property` = '任选') and (`student_status`.`sci`.`grade` >= 60))
                    then `student_status`.`sci`.`credit`
                else 0 end)) AS `任选通过学分`
from (`student_status`.`student_courses_info` `sci` join `student_status`.`student` `s`
      on ((`student_status`.`sci`.`stuId` = `s`.`stuId`)))
group by `s`.`stuId`, `s`.`stuName`
order by `s`.`stuId`;

create definer = root@localhost view student_failed_credits as
select `s`.`stuId`           AS `stuId`,
       `s`.`stuName`         AS `stuName`,
       sum((case
                when ((`student_status`.`sci`.`property` = '必修') and (`student_status`.`sci`.`grade` < 60))
                    then `student_status`.`sci`.`credit`
                else 0 end)) AS `failed_required_credits`,
       sum((case
                when (((`student_status`.`sci`.`property` = '限选') or (`student_status`.`sci`.`property` = '任选')) and
                      (`student_status`.`sci`.`grade` < 60)) then `student_status`.`sci`.`credit`
                else 0 end)) AS `failed_elective_credits`
from (`student_status`.`student_courses_info` `sci` join `student_status`.`student` `s`
      on ((`student_status`.`sci`.`stuId` = `s`.`stuId`)))
group by `s`.`stuId`, `s`.`stuName`;

create
    definer = root@localhost procedure generate_classes()
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE j INT; -- 将 j 的声明移到最前面
    
    WHILE i <= 65 DO
        SET j = 1; -- 每次外层循环重新初始化 j
        WHILE j <= 5 DO
            INSERT INTO class (classId, majorId)
            VALUES (i * 100 + j, i); 
            SET j = j + 1;
        END WHILE;
        SET i = i + 1;
    END WHILE;
END;

create
    definer = root@localhost procedure generate_conduct_data()
BEGIN
    DECLARE teacherId INT;
    DECLARE courseId INT;
    DECLARE majorId INT;
    DECLARE classId INT;
    DECLARE done INT DEFAULT FALSE;
    DECLARE i INT DEFAULT 1;
    DECLARE class_cursor CURSOR FOR 
        SELECT c.classId
        FROM class c
        WHERE c.majorId = majorId;  -- 根据 majorId 查找班级
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    -- 遍历 teacherId，从 1 到 50
    WHILE i <= 50 DO
        -- 获取当前 teacherId
        SET teacherId = i;
        -- 随机选择一门课程（从 1 到 27，直接选择一个 courseId）
        SET courseId = FLOOR(RAND() * 27) + 1;
        -- 根据 courseId 查找该课程的 majorId
        SELECT p.majorId INTO majorId
        FROM plan p
        WHERE p.courseId = courseId
        LIMIT 1;  -- 获取一个对应的 majorId
        -- 打开游标，获取该专业下的所有班级
        OPEN class_cursor;
        SET done = FALSE;
        -- 遍历班级
        simple_loop: LOOP
            FETCH class_cursor INTO classId;
            -- 如果游标没有找到更多的班级，退出循环
            IF done THEN
                CLOSE class_cursor;
                LEAVE simple_loop;
            END IF;
            -- 插入教师、课程和班级到 conduct 表
            INSERT INTO conduct (teacherId, courseId, classId)
            VALUES (teacherId, courseId, classId);
        END LOOP simple_loop;
        -- 继续下一个教师
        SET i = i + 1;
    END WHILE;
END;

create
    definer = root@localhost procedure generate_curricular_variable_data()
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE stuId INT;
    DECLARE classId INT;
    DECLARE majorId INT;
    DECLARE random_grade INT;
    DECLARE random_courseId INT;
    DECLARE done INT DEFAULT FALSE;
    
    -- 定义游标，游标内容会在每次循环时动态更新
    DECLARE course_cursor CURSOR FOR 
        SELECT p.courseId 
        FROM plan p
        WHERE p.majorId = majorId;  -- 通过专业查找课程
    
    -- 处理游标未找到数据的情况
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    -- 遍历学生数据
    WHILE i <= 230 DO
        -- 获取学生的 stuId
        SET stuId = i;
        -- 获取该学生的 classId
        SET classId = (SELECT s.classId FROM student s WHERE s.stuId = stuId LIMIT 1);
        -- 根据 classId 获取 majorId
        SET majorId = (SELECT c.majorId FROM class c WHERE c.classId = classId LIMIT 1);
        -- 在每次循环中动态绑定游标并打开
        OPEN course_cursor;
        SET done = FALSE;
        
        -- 选择课程并插入数据
        simple_loop: LOOP
            -- 随机选择一个课程，确保不重复
            FETCH course_cursor INTO random_courseId;
            IF done = TRUE THEN
                CLOSE course_cursor;
                LEAVE simple_loop;  -- 退出循环
            END IF;
            -- 生成一个随机成绩，0 到 100
            SET random_grade = FLOOR(RAND() * 101);
            -- 执行插入操作，插入该学生的课程和成绩
            INSERT INTO curricular_variable (stuId, courseId, grade)
            VALUES (stuId, random_courseId, random_grade);
        END LOOP simple_loop;
        -- 继续下一个学生
        SET i = i + 1;
    END WHILE;
END;

create
    definer = root@localhost procedure generate_plan_data()
BEGIN
    -- 将所有变量声明放在存储过程的开头
    DECLARE od INT DEFAULT 1;
    DECLARE j INT;
    declare i int default 1;
    DECLARE course_count INT;
    DECLARE random_courseId INT;
    DECLARE random_semester INT;
    DECLARE random_property INT;
    
    -- 外层循环，用于生成 65*5 个 planId 对应的 majorId
    WHILE od <= 65*5 DO
        -- 每个 planId 随机生成 5 门课程
        SET course_count = 5; 
        -- 清空临时表
        TRUNCATE TABLE temp_course;
        -- 初始化 j
        SET j = 1;
        -- 内层循环，用于为每个 planId 生成 courseId, semester, property
        WHILE j <= course_count DO
            -- 随机生成 courseId（确保唯一）
            course_loop: LOOP
                SET random_courseId = FLOOR(1 + RAND() * 27); -- 生成 1-27 的随机数
                
                -- 检查是否已经存在于 temp_course 表中
                IF (SELECT COUNT(*) FROM temp_course WHERE courseId = random_courseId) = 0 THEN
                    -- 如果不存在，则插入并退出循环
                    INSERT INTO temp_course (courseId) VALUES (random_courseId);
                    LEAVE course_loop;
                END IF;
            END LOOP course_loop;
            -- 随机生成 semester 和 property
            SET random_semester = FLOOR(1 + RAND() * 8); -- 生成 1-8 的随机数
            SET random_property = FLOOR(1 + RAND() * 3); -- 生成 1-3 的随机数
            -- 插入数据到 plan 表
            INSERT INTO plan (planId, majorId, courseId, semester, property)
            VALUES (od, i, random_courseId, random_semester, random_property);
            set od = od + 1;
            -- 增加 j 的值
            SET j = j + 1;
        END WHILE;
        SET i = i + 1;
    END WHILE;
END;

create
    definer = root@localhost procedure insert_or_update_curricular(IN p_stuId int, IN p_courseId int, IN p_grade float)
BEGIN
    DECLARE existing_flag INT DEFAULT 0;
    DECLARE existing_id INT DEFAULT 0;
    -- 查询是否有相同的 stuId 和 courseId 的记录
    SELECT flag, curricularId INTO existing_flag, existing_id
    FROM curricular_variable
    WHERE stuId = p_stuId AND courseId = p_courseId
    LIMIT 1;
    -- 情况1: 如果记录存在且 flag=2，抛出错误
    IF existing_flag = 2 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '考试次数已达上限，不允许再次补考';
    -- 情况2: 如果记录存在且 flag=1，更新成绩并将 flag 设为2
    ELSEIF existing_flag = 1 THEN
        UPDATE curricular_variable
        SET grade = p_grade, flag = 2
        WHERE curricularId = existing_id;
    -- 情况3: 如果没有记录，直接插入
    ELSE
        INSERT INTO curricular_variable (stuId, courseId, grade, flag)
        VALUES (p_stuId, p_courseId, p_grade, 1);
    END IF;
END;

create definer = root@localhost event clear_temp_flag_update on schedule
    every '1' DAY
        starts '2024-11-18 08:49:23'
    enable
    do
    DELETE FROM temp_flag_update;

