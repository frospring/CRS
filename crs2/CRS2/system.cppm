export module system;

import std;
export import database;
export import student;
export import course;
export import teacher;
export import enrollment;

using std::string;
using std::vector;
using std::print;
using std::println;

export class CourseSelectionSystem {
private:
    Database database;

public:

    CourseSelectionSystem();

    void show_all_students();

    void show_all_teachers();

    void show_all_courses();


    void show_all_enrollments();


    void enroll_student(string student_id, string course_id);


    void drop_course(string student_id, string course_id);


    void record_score(string student_id, string course_id, double score);
};


CourseSelectionSystem::CourseSelectionSystem() {
    if (!database.is_connected()) {
        println("数据库连接失败，系统退出");
        std::exit(1);
    }

    database.create_tables();
    database.load_sample_data();

    println("选课系统启动成功");
}

void CourseSelectionSystem::show_all_students() {
    println("\n学生列表");
    database.query("SELECT * FROM students ORDER BY id");
}

void CourseSelectionSystem::show_all_teachers() {
    println("\n教师列表");
    database.query("SELECT * FROM teachers ORDER BY id");
}

void CourseSelectionSystem::show_all_courses() {
    println("\n课程列表");
    database.query("SELECT * FROM courses ORDER BY id");
}

void CourseSelectionSystem::show_all_enrollments() {
    println("\n选课记录");
    database.query("SELECT * FROM enrolls ORDER BY stu_id, cou_id");
}

void CourseSelectionSystem::enroll_student(string student_id, string course_id) {
    string check_student = std::format("SELECT COUNT(*) FROM students WHERE id = '{}'", student_id);
    auto student_result = database.query(check_student);

    if (student_result.size() > 1 && student_result[1][0] == "0") {
        println("错误：学生 {} 不存在", student_id);
        return;
    }

    string check_course = std::format("SELECT COUNT(*) FROM courses WHERE id = '{}'", course_id);
    auto course_result = database.query(check_course);

    if (course_result.size() > 1 && course_result[1][0] == "0") {
        println("错误：课程 {} 不存在", course_id);
        return;
    }

    string check_enrollment = std::format(
        "SELECT COUNT(*) FROM enrolls WHERE stu_id = '{}' AND cou_id = '{}'",
        student_id, course_id
    );
    auto enrollment_result = database.query(check_enrollment);

    if (enrollment_result.size() > 1 && enrollment_result[1][0] != "0") {
        println("错误：学生已选修此课程");
        return;
    }

    string check_capacity = std::format(
        "SELECT capacity, selected_count FROM courses WHERE id = '{}'",
        course_id
    );
    auto capacity_result = database.query(check_capacity);

    if (capacity_result.size() > 1) {
        int capacity = std::stoi(capacity_result[1][0]);
        int selected = std::stoi(capacity_result[1][1]);

        if (selected >= capacity) {
            println("错误：课程 {} 已满", course_id);
            return;
        }
    }

    Enrollment enrollment(student_id, course_id);
    enrollment.save_to_database(database);

    string update_course = std::format(
        "UPDATE courses SET selected_count = selected_count + 1 WHERE id = '{}'",
        course_id
    );
    database.execute(update_course);

    println("选课成功：学生 {} 选修课程 {}", student_id, course_id);
}

void CourseSelectionSystem::drop_course(string student_id, string course_id) {
    Enrollment enrollment(student_id, course_id);
    enrollment.delete_from_database(database);

    string update_course = std::format(
        "UPDATE courses SET selected_count = selected_count - 1 WHERE id = '{}'",
        course_id
    );
    database.execute(update_course);

    println("退课成功：学生 {} 退选课程 {}", student_id, course_id);
}

void CourseSelectionSystem::record_score(string student_id, string course_id, double score) {
    string sql = std::format(
        "UPDATE enrolls SET score = {:.1f} WHERE stu_id = '{}' AND cou_id = '{}'",
        score, student_id, course_id
    );
    database.execute(sql);
    println("成绩录入成功：学生 {} 课程 {} 成绩: {:.1f}", student_id, course_id, score);
}
