DELIMITER //

CREATE PROCEDURE generate_conduct_data()
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
//

DELIMITER ;






CALL generate_conduct_data();
DROP PROCEDURE IF EXISTS generate_conduct_data;
SELECT * FROM conduct;
DELETE FROM conduct;
ALTER TABLE conduct AUTO_INCREMENT = 1;

SELECT 