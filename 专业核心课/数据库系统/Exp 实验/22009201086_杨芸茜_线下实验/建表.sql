create table student_status.course
(
    courseId   int          not null
        primary key,
    courseName varchar(255) not null,
    credit     int          not null
);

create table student_status.department
(
    deptId   int          not null
        primary key,
    deptName varchar(255) not null
);

create table student_status.major
(
    majorId   int          not null
        primary key,
    majorName varchar(255) not null,
    deptId    int          null,
    constraint major_ibfk_1
        foreign key (deptId) references student_status.department (deptId)
);

create table student_status.class
(
    classId int not null
        primary key,
    majorId int null,
    constraint class_ibfk_1
        foreign key (majorId) references student_status.major (majorId)
);

create index majorId
    on student_status.class (majorId);

create index deptId
    on student_status.major (deptId);

create table student_status.plan
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
        foreign key (courseId) references student_status.course (courseId),
    constraint plan_ibfk_3
        foreign key (majorId) references student_status.major (majorId)
);

create index courseId
    on student_status.plan (courseId);

create table student_status.student
(
    stuId   int         not null
        primary key,
    stuName varchar(20) not null,
    classId int         not null,
    constraint student_ibfk_1
        foreign key (classId) references student_status.class (classId)
);

create table student_status.curricular_variable
(
    curricularId int auto_increment
        primary key,
    stuId        int               not null,
    courseId     int               not null,
    grade        float             null,
    flag         tinyint default 1 null,
    constraint curricular_variable_ibfk_1
        foreign key (courseId) references student_status.course (courseId),
    constraint curricular_variable_ibfk_2
        foreign key (stuId) references student_status.student (stuId)
);

create index courseId
    on student_status.curricular_variable (courseId);

create index classId
    on student_status.student (classId);

create table student_status.teacher
(
    teacherId   int         not null
        primary key,
    teacherName varchar(20) not null,
    deptId      int         null,
    constraint teacher_ibfk_1
        foreign key (deptId) references student_status.department (deptId)
);

create table student_status.conduct
(
    conduct_id int auto_increment
        primary key,
    teacherId  int not null,
    courseId   int not null,
    classId    int not null,
    constraint teacherId
        unique (teacherId, courseId, classId),
    constraint conduct_ibfk_1
        foreign key (classId) references student_status.class (classId),
    constraint conduct_ibfk_2
        foreign key (courseId) references student_status.course (courseId),
    constraint conduct_ibfk_3
        foreign key (teacherId) references student_status.teacher (teacherId)
);

create index classId
    on student_status.conduct (classId);

create index courseId
    on student_status.conduct (courseId);

create index deptId
    on student_status.teacher (deptId);

