DELIMITER //

CREATE PROCEDURE insert_or_update_curricular(
    IN p_stuId INT,
    IN p_courseId INT,
    IN p_grade FLOAT
)
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
//

DELIMITER ;



DELIMITER //

CREATE TRIGGER trg_check_flag_before_insert
BEFORE INSERT ON curricular_variable
FOR EACH ROW
BEGIN
    -- 如果已经有相同的 stuId 和 courseId 并且 flag=2，则抛出错误
    IF EXISTS (
        SELECT 1 FROM curricular_variable 
        WHERE stuId = NEW.stuId AND courseId = NEW.courseId AND flag = 2
    ) THEN
        SIGNAL SQLSTATE '46000' SET MESSAGE_TEXT = '考试次数已达上限，不允许再次补考';
    END IF;
END;
//

DELIMITER ;





-- 查看插入情况
SELECT * FROM curricular_variable WHERE stuId = 1;

-- 第一次插入（应成功）
CALL insert_or_update_curricular(1, 9, 85);

-- 再次插入相同课程记录，更新 flag 为 2
CALL insert_or_update_curricular(1, 9, 95);

-- 再次插入相同课程，预期报错
CALL insert_or_update_curricular(1, 9, 98);