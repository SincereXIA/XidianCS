DELIMITER //

CREATE PROCEDURE generate_curricular_variable_data()
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
//

DELIMITER ;



DROP PROCEDURE IF EXISTS generate_curricular_variable_data;


CALL generate_curricular_variable_data();


DELETE FROM curricular_variable;
ALTER TABLE curricular_variable AUTO_INCREMENT = 1;
