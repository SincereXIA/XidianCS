-- 创建`studetnt_baseinfo`，按学号、姓名、专业三种方式查询学生基本信息
CREATE VIEW student_baseinfo
AS
SELECT stuId '学号',stuName '姓名',class.classId '班级号',majorName '专业',deptName '所在系'
FROM student,class,major,department
WHERE student.classId = class.classId AND
      class.majorId = major.majorId AND
      major.deptId = department.deptId
ORDER BY stuId ASC,class.`classId`;

SELECT * FROM student_baseinfo WHERE `专业` = '通信工程';
-- 创建'student_courses_info'视图，查询一位学生所修的课程、性质（必修或选修）、学期、学分及成绩；
CREATE VIEW student_courses_info AS
SELECT 
    student.stuId,  -- 学生ID
    student.stuName,  -- 学生姓名
    course.courseId,  -- 课程ID
    course.courseName,  -- 课程名称
    course.credit,  -- 学分
    plan.property,  -- 课程性质（必修或选修）
    plan.semester,  -- 学期
    curricular_variable.grade  -- 成绩
FROM 
    curricular_variable
INNER JOIN 
    student ON curricular_variable.stuId = student.stuId  -- 关联学生
INNER JOIN 
    course ON curricular_variable.courseId = course.courseId  -- 关联课程
INNER JOIN 
    class ON student.classId = class.classId  -- 关联班级
INNER JOIN 
    major ON class.majorId = major.majorId  -- 关联专业
INNER JOIN 
    plan ON major.majorId = plan.majorId  -- 关联专业和课程
        AND curricular_variable.courseId = plan.courseId  -- 课程对应
ORDER BY 
    student.stuId, course.courseId;  -- 按学生ID和课程ID排序

SELECT *
FROM student_courses_info
WHERE stuId = 1;


-- 查询他的必修课平均成绩、所有课程平均成绩（平均成绩应按学分加权）
CREATE OR REPLACE VIEW student_average_scores AS
SELECT 
    s.stuId,
    s.stuName,

    -- 计算必修课的平均成绩，保留四位小数
    ROUND(AVG(CASE WHEN sci.property = '必修' THEN sci.grade END), 4) AS 必修课平均成绩,

    -- 计算所有课程的加权平均成绩，保留四位小数
    ROUND(SUM(sci.grade * sci.credit) / SUM(sci.credit), 4) AS 所有课程加权平均成绩

FROM 
    student_courses_info sci
INNER JOIN 
    student s ON sci.stuId = s.stuId

GROUP BY 
    s.stuId, s.stuName
ORDER BY 
    s.stuId;

SELECT * FROM student_average_scores WHERE stuId = 1;


-- 每个学生的必修、限选和任选课程通过学分统计
CREATE OR REPLACE VIEW student_credit_summary AS
SELECT 
    s.stuId,
    s.stuName,

    -- 计算必修课通过学分
    SUM(CASE WHEN sci.property = '必修' AND sci.grade >= 60 THEN sci.credit ELSE 0 END) AS 必修通过学分,

    -- 计算限选课通过学分
    SUM(CASE WHEN sci.property = '限选' AND sci.grade >= 60 THEN sci.credit ELSE 0 END) AS 限选通过学分,

    -- 计算任选课通过学分
    SUM(CASE WHEN sci.property = '任选' AND sci.grade >= 60 THEN sci.credit ELSE 0 END) AS 任选通过学分

FROM 
    student_courses_info sci
INNER JOIN 
    student s ON sci.stuId = s.stuId

GROUP BY 
    s.stuId, s.stuName
ORDER BY 
    s.stuId;
    
SELECT * FROM student_credit_summary;

-- 不及格学分
CREATE OR REPLACE VIEW student_failed_credits AS
SELECT 
    s.stuId,
    s.stuName,
    
    -- 统计不及格的必修课学分
    SUM(CASE WHEN sci.property = '必修' AND sci.grade < 60 THEN sci.credit ELSE 0 END) AS failed_required_credits,

    -- 统计不及格的选修课（包括限选和任选）学分
    SUM(CASE WHEN (sci.property = '限选' OR sci.property = '任选') AND sci.grade < 60 THEN sci.credit ELSE 0 END) AS failed_elective_credits

FROM 
    student_courses_info sci
INNER JOIN 
    student s ON sci.stuId = s.stuId

GROUP BY 
    s.stuId, s.stuName;

SELECT * FROM student_failed_credits;


-- 筛选出距开除差 3 学分以内的学生

SELECT 
    sfc.stuId,
    sfc.stuName,
    sfc.failed_required_credits,
    sfc.failed_elective_credits
FROM 
    student_failed_credits sfc
WHERE 
    -- 筛选必修课不及格累计 7 到 9 学分的学生
    (sfc.failed_required_credits BETWEEN 7 AND 9)
    
    OR
    
    -- 筛选选修课不及格累计 12 到 14 学分的学生
    (sfc.failed_elective_credits BETWEEN 12 AND 14)
ORDER BY 
    sfc.stuId;
    
    
    
SELECT 
    t.teacherId AS '老师工号',
    t.teacherName AS '老师姓名',
    t.deptId AS '所在系'
FROM 
    student_baseinfo sbi
INNER JOIN 
    student_courses_info sci ON sbi.`学号` = sci.stuId
INNER JOIN 
    conduct c ON c.classId = sbi.`班级号` AND c.courseId = sci.courseId
INNER JOIN 
    teacher t ON t.teacherId = c.teacherId
WHERE 
    sbi.`学号` = 1;  -- 这里替换为你要查询的学生ID



