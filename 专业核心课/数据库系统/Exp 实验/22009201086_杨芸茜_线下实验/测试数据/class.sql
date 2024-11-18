DELIMITER //

CREATE PROCEDURE generate_classes()
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
//
DELIMITER ;


CALL generate_classes();

-- 查看生成的班级数据
SELECT * FROM class;
