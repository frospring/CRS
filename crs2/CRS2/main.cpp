import system;
import std;

using std::println;

int main() {
    println("选课系统");

    try {

        CourseSelectionSystem system;

        system.show_all_students();
        system.show_all_teachers();
        system.show_all_courses();

        println("\n---选课演示 ---");

        system.enroll_student("S001", "C001");
        system.enroll_student("S001", "C002");
        system.enroll_student("S002", "C001");

        system.show_all_enrollments();

        println("\n退课演示");
        system.drop_course("S001", "C002");
        system.show_all_enrollments();

        println("\n成绩录入演示");
        system.record_score("S001", "C001", 85.5);


        println("\n最终状态");
        system.show_all_students();
        system.show_all_courses();
        system.show_all_enrollments();

        println("\n系统运行完成");

    } catch (const std::exception& e) {
        println("系统错误: {}", e.what());
        return 1;
    }

    return 0;
}
