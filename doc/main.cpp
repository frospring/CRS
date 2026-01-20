
import studentCourse;

import std;



int main(){
            // File: main.cpp   Version: 0.1.0   License: AGPLv3
            // Created: pangwenhao      2026-01-17 16:03:13
            // Description:
            //
    // alias for static function Registrar::singleton
   auto &system = Registrar::singleton();
    system.initialize();


    // 原有逻辑：模拟学生选课
    system.studentEnrollsInCourse("2001", "101");
    system.studentEnrollsInCourse("2001", "201");
    system.studentEnrollsInCourse("2001", "301");

    system.studentEnrollsInCourse("2002", "101");
    system.studentEnrollsInCourse("2002", "301");

    system.studentEnrollsInCourse("2003", "201");
    system.studentEnrollsInCourse("2003", "301");

    system.studentEnrollsInCourse("2004", "101");
    system.studentEnrollsInCourse("2004", "201");

    system.studentEnrollsInCourse("2005", "201");

    std::println();

    // 原有逻辑：查询课程花名册
    system.courseRoster("101");
    system.courseRoster("201");
    system.courseRoster("301");

    // 原有逻辑：查询学生课表
    system.studentSchedule("2001");
    system.studentSchedule("2003");

    // 新增：查询教师授课汇总
    std::println("\n----- 教师授课信息汇总 -----");
    system.teacherTaughtCourses("1001");
    system.teacherTaughtCourses("1002");


   sqlFuncsystem(Stu);


/*

    // 系统初始化（包含学生、课程、教师）
    system.initialize();

    // 原有逻辑：模拟学生选课
    system.studentEnrollsInCourse("2001", "101");
    system.studentEnrollsInCourse("2001", "201");
    system.studentEnrollsInCourse("2001", "301");

    system.studentEnrollsInCourse("2002", "101");
    system.studentEnrollsInCourse("2002", "301");

    system.studentEnrollsInCourse("2003", "201");
    system.studentEnrollsInCourse("2003", "301");

    system.studentEnrollsInCourse("2004", "101");
    system.studentEnrollsInCourse("2004", "201");

    system.studentEnrollsInCourse("2005", "201");

    std::println();

    // 原有逻辑：查询课程花名册
    system.courseRoster("101");
    system.courseRoster("201");
    system.courseRoster("301");

    // 原有逻辑：查询学生课表
    system.studentSchedule("2001");
    system.studentSchedule("2003");

    // 新增：查询教师授课汇总
    std::println("\n----- 教师授课信息汇总 -----");
    system.teacherTaughtCourses("1001");
    system.teacherTaughtCourses("1002");
*/

    return 0;

}

