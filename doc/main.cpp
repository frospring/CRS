
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




/*
    // 系统初始化（包含学生、课程、教师）
    system().initialize();

    // 原有逻辑：模拟学生选课
    system().studentEnrollsInCourse("S001", "CS101");
    system().studentEnrollsInCourse("S001", "CS201");
    system().studentEnrollsInCourse("S001", "MATH101");

    system().studentEnrollsInCourse("S002", "CS101");
    system().studentEnrollsInCourse("S002", "MATH101");

    system().studentEnrollsInCourse("S003", "CS201");
    system().studentEnrollsInCourse("S003", "MATH101");

    system().studentEnrollsInCourse("S004", "CS101");
    system().studentEnrollsInCourse("S004", "CS201");

    system().studentEnrollsInCourse("S005", "CS201");

    std::println();

    // 原有逻辑：查询课程花名册
    system().courseRoster("CS101");
    system().courseRoster("CS201");
    system().courseRoster("MATH101");

    // 原有逻辑：查询学生课表
    system().studentSchedule("S001");
    system().studentSchedule("S003");

    // 新增：查询教师授课汇总
    std::println("\n----- 教师授课信息汇总 -----");
    system().teacherTaughtCourses("T001");
    system().teacherTaughtCourses("T002");

*/
    return 0;

}

