DELIMITER //

CREATE TRIGGER conduct_instead
BEFORE INSERT ON conduct
FOR EACH ROW
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
END//

DELIMITER ;


SELECT * FROM conduct;

-- 测试代码
INSERT INTO conduct (teacherId, courseId, classId)
VALUES (1, 2, 601); -- 一个老师给多个班代课。
INSERT INTO conduct (teacherId, courseId, classId)
VALUES (1, 3, 601); -- 一个老师给1个班代多门课。
