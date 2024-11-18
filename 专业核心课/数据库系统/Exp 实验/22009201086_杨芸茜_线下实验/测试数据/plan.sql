-- 首先确保临时表不存在
DROP TEMPORARY TABLE IF EXISTS temp_course;

-- 创建临时表（只创建一次）
CREATE TEMPORARY TABLE temp_course (
    courseId INT PRIMARY KEY
);

DELIMITER //

CREATE PROCEDURE generate_plan_data()
BEGIN
    -- 将所有变量声明放在存储过程的开头
    DECLARE od INT DEFAULT 1;
    DECLARE j INT;
    DECLARE i INT DEFAULT 1;
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
            SET od = od + 1;
            -- 增加 j 的值
            SET j = j + 1;
        END WHILE;
        SET i = i + 1;
    END WHILE;
END;
//
DELIMITER ;

-- 调用存储过程生成数据
CALL generate_plan_data();

-- 查看生成的数据
SELECT * FROM plan ORDER BY planId, courseId;


-- 1. 确保删除所有数据
DELETE FROM plan;

-- 2. 重置 AUTO_INCREMENT 值
ALTER TABLE plan AUTO_INCREMENT = 1;
DESC plan;
