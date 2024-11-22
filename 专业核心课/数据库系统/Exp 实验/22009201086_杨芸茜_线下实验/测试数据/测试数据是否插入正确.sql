SELECT * FROM course;
SELECT * FROM department;
SELECT * FROM major;
SELECT * FROM class;
SELECT * FROM plan;
SELECT * FROM student;
SELECT * FROM curricular_variable;
SELECT * FROM teacher;
SELECT * FROM conduct;

SHOW TABLES;

















INSERT INTO department VALUES(18,'音乐系');
INSERT INTO major VALUES(66,'音乐表演',18);
INSERT INTO class VALUES(6601,66);-- 班级号 6601 ，专业号 66
INSERT INTO student VALUES (231,'张三',6601);
INSERT INTO course VALUES (28,'西方音乐简史',2);
INSERT INTO plan VALUES (326,66,28,1,1);
INSERT INTO teacher VALUES (51 ,'嵇康',1);
INSERT INTO conduct(teacherId,courseId,classId) VALUES (51,28,6601);
INSERT INTO curricular_variable (stuId,courseId,grade) VALUES (231,28,70);